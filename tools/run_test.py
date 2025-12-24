import os
import sys
import json
import glob
import subprocess
import time
import math
from pathlib import Path


# --- 颜色定义 ---
class Colors:
    HEADER = "\033[95m"
    OKBLUE = "\033[94m"
    OKCYAN = "\033[96m"
    OKGREEN = "\033[92m"
    WARNING = "\033[93m"
    FAIL = "\033[91m"
    ENDC = "\033[0m"
    BOLD = "\033[1m"
    UNDERLINE = "\033[4m"


# --- 退出代码定义 (优先级从低到高) ---
EXIT_CODES = {
    "AC": 0,
    "PC": 5,
    "WA": 1,
    "TLE": 2,
    "RE": 3,
    "MLE": 6,  # 预留
    "OLE": 7,  # 预留
    "CE": 4,
    "UKE": 9,
}

# 错误严重程度优先级，数值越大越严重，最终返回码将由最严重的错误决定
ERROR_SEVERITY = {
    "AC": 0,
    "PC": 1,
    "WA": 2,
    "TLE": 3,
    "RE": 4,
    "MLE": 5,
    "OLE": 6,
    "CE": 7,
    "UKE": 8,
}

global_worst_status = "AC"


def update_global_status(current_status):
    """更新全局最差状态"""
    global global_worst_status
    if ERROR_SEVERITY.get(current_status, 0) > ERROR_SEVERITY.get(
        global_worst_status, 0
    ):
        global_worst_status = current_status


def normalize_output(content):
    """
    标准化输出：
    1. 去除行尾空白
    2. 合并多余空行（将连续换行替换为单换行，并去除首尾空白）
    """
    if not content:
        return ""

    # 按行分割，去除每一行的右侧空白
    lines = [line.rstrip() for line in content.strip().splitlines()]

    # 过滤掉空行，或者保留特定逻辑。
    # 这里采用常规 OJ 逻辑：忽略行尾空格，忽略文件末尾空行
    # 若要严格合并中间空行，可以过滤空字符串，但通常保留中间空行结构
    # 这里简化为：去除每行末尾空格，去除整个文件首尾空行

    return "\n".join(lines).strip()


def run_test(problem_dir):
    problem_path = Path(problem_dir)

    # 1. 读取配置
    req_file = problem_path / "requirement.json"
    if not req_file.exists():
        print(
            f"{Colors.FAIL}[Error] requirement.json not found in {problem_dir}{Colors.ENDC}"
        )
        sys.exit(10)

    try:
        with open(req_file, "r", encoding="utf-8") as f:
            config = json.load(f)
    except Exception as e:
        print(
            f"{Colors.FAIL}[Error] Failed to parse requirement.json: {e}{Colors.ENDC}"
        )
        sys.exit(10)

    time_limit_ms = config.get("time_limit", 1000)
    time_limit_sec = time_limit_ms / 1000.0

    # 2. 寻找解决方案
    solutions_dir = problem_path / "solutions"
    samples_dir = problem_path / "samples"

    if not solutions_dir.exists():
        print(f"{Colors.FAIL}[Error] solutions directory not found.{Colors.ENDC}")
        sys.exit(10)

    # 获取所有 .c 和 .cpp 文件
    source_files = list(solutions_dir.glob("*.c")) + list(solutions_dir.glob("*.cpp"))

    if not source_files:
        print(
            f"{Colors.WARNING}[Warn] No .c or .cpp files found in solutions.{Colors.ENDC}"
        )
        sys.exit(0)  # 无文件不算错误，返回 0

    print(
        f"{Colors.HEADER}=== Testing Problem: {config.get('title', 'Unknown')} (ID: {config.get('id', 'N/A')}) ==={Colors.ENDC}"
    )
    print(f"Time Limit: {time_limit_ms}ms | Source Files: {len(source_files)}\n")

    for src_file in source_files:
        file_name = src_file.name
        print(f"{Colors.OKCYAN}>> Testing {file_name}...{Colors.ENDC}")

        exe_path = src_file.with_suffix(".out")

        # 3. 编译
        compile_cmd = []
        if src_file.suffix == ".c":
            compile_cmd = [
                "gcc",
                str(src_file),
                "-o",
                str(exe_path),
                "-std=c11",
                "-Wall",
                "-fno-asm",
                "-lm",
                "-march=native",
            ]
        else:  # .cpp
            compile_cmd = [
                "g++",
                str(src_file),
                "-o",
                str(exe_path),
                "-std=c++17",
                "-Wall",
                "-fno-asm",
                "-lm",
                "-march=native",
            ]

        try:
            result = subprocess.run(compile_cmd, capture_output=True, text=True)
            if result.returncode != 0:
                print(f"{Colors.FAIL}[CE] Compilation Error{Colors.ENDC}")
                print(result.stderr)
                update_global_status("CE")
                continue  # 编译失败，跳过此文件的运行，继续下一个文件
            elif result.stderr:
                # 即使编译成功，如果有 warning 也打印出来
                print(f"{Colors.WARNING}[Compile Warning]{Colors.ENDC}")
                print(result.stderr)
        except Exception as e:
            print(
                f"{Colors.FAIL}[SysError] Compilation failed to execute: {e}{Colors.ENDC}"
            )
            sys.exit(10)

        # 4. 运行测试样例
        input_files = sorted(list(samples_dir.glob("in*.txt")))
        file_status = "AC"  # 默认为 AC，遇到问题则降级

        total_cases = len(input_files)
        passed_cases = 0

        for in_file in input_files:
            # 构造对应的 out 文件名 (in1.txt -> out1.txt)
            case_name = in_file.name
            out_name = case_name.replace("in", "out")
            out_file = samples_dir / out_name

            if not out_file.exists():
                print(
                    f"  {Colors.WARNING}[Warn] Missing output file for {case_name}, skipping.{Colors.ENDC}"
                )
                continue

            # 读取标准答案
            with open(out_file, "r", encoding="utf-8") as f:
                expected_output = normalize_output(f.read())

            # 运行程序
            start_time = time.time()
            process_status = "AC"
            actual_output = ""

            try:
                with open(in_file, "r", encoding="utf-8") as fin:
                    # 运行时间限制稍微放宽一点点给 Python 的 overhead，但 strict mode 下应严格
                    # 使用 subprocess.run 的 timeout 参数
                    run_result = subprocess.run(
                        [str(exe_path)],
                        stdin=fin,
                        capture_output=True,
                        text=True,
                        timeout=time_limit_sec + 0.05,  # 给予 50ms 缓冲
                    )

                    elapsed = (time.time() - start_time) * 1000

                    if run_result.returncode != 0:
                        process_status = "RE"  # Runtime Error
                    else:
                        # 检查时间 (虽然 timeout 会抛异常，但为了精确也可以再次检查)
                        if elapsed > time_limit_ms:
                            process_status = "TLE"
                        else:
                            actual_output = normalize_output(run_result.stdout)
                            if actual_output == expected_output:
                                process_status = "AC"
                            else:
                                process_status = "WA"

            except subprocess.TimeoutExpired:
                process_status = "TLE"
            except Exception as e:
                process_status = "UKE"  # Unknown Error
                print(f"  SysError: {e}")

            # 打印单个 Case 结果
            color = Colors.OKGREEN if process_status == "AC" else Colors.FAIL
            print(
                f"  Case {case_name}: {color}{process_status}{Colors.ENDC} ({elapsed:.1f}ms)"
            )

            # 更新当前文件的状态
            if process_status != "AC":
                # 如果当前已经是错的，保留最严重的错误
                if ERROR_SEVERITY[process_status] > ERROR_SEVERITY[file_status]:
                    file_status = process_status
            else:
                passed_cases += 1

        # 5. 清理并汇总当前文件结果
        if exe_path.exists():
            exe_path.unlink()

        # 计算 Partial Correct
        if file_status != "AC" and passed_cases > 0 and file_status != "CE":
            file_status = "PC"

        # 打印文件最终结果
        final_color = (
            Colors.OKGREEN
            if file_status == "AC"
            else (Colors.WARNING if file_status == "PC" else Colors.FAIL)
        )
        print(
            f"  => Result: {final_color}{file_status}{Colors.ENDC} ({passed_cases}/{total_cases})\n"
        )

        # 更新全局状态
        update_global_status(file_status)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python run_test.py <problem_directory>")
        sys.exit(10)

    target_dir = sys.argv[1]
    if not os.path.exists(target_dir):
        print(f"Directory {target_dir} does not exist.")
        sys.exit(10)

    run_test(target_dir)

    final_code = EXIT_CODES.get(global_worst_status, 9)
    print(f"Final Return Code: {final_code} ({global_worst_status})")
    sys.exit(final_code)
