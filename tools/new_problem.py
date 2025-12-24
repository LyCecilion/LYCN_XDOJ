import os
import json
import sys

# --- 配置 ---
PROBLEMS_ROOT = "problems"  # 题目根目录
DEFAULT_AUTHOR = "LyCecilion"


class Colors:
    HEADER = "\033[95m"
    BLUE = "\033[94m"
    GREEN = "\033[92m"
    YELLOW = "\033[93m"
    RED = "\033[91m"
    RESET = "\033[0m"
    BOLD = "\033[1m"


def get_input(prompt, default=None, val_type=str):
    """获取用户输入，支持默认值和类型转换"""
    if default is not None:
        prompt_text = f"{prompt} [{default}]: "
    else:
        prompt_text = f"{prompt}: "

    while True:
        user_input = input(f"{Colors.BLUE}{prompt_text}{Colors.RESET}").strip()

        if not user_input:
            if default is not None:
                return default
            else:
                print(f"{Colors.RED}此项不能为空，请重新输入。{Colors.RESET}")
                continue

        try:
            return val_type(user_input)
        except ValueError:
            print(
                f"{Colors.RED}输入类型错误，需要 {val_type.__name__} 类型。{Colors.RESET}"
            )


def create_file(path, content):
    """创建文件并写入内容"""
    try:
        with open(path, "w", encoding="utf-8") as f:
            f.write(content)
        print(f"  Created: {path}")
    except Exception as e:
        print(f"{Colors.RED}Error creating {path}: {e}{Colors.RESET}")


def main():
    print(f"{Colors.HEADER}=== 新建题目向导 ==={Colors.RESET}")

    # 1. 获取输入
    p_id = get_input("题目编号 (ID)", val_type=int)
    p_name = get_input("英文短名 (用于文件夹名，如 exam-ranking)")
    p_title = get_input("中文标题 (Title)")

    # --- 改动：难度输入验证 ---
    while True:
        p_difficulty = get_input("难度 (1-5)", default=1, val_type=int)
        if 1 <= p_difficulty <= 5:
            break
        print(f"{Colors.RED}难度必须是 1 到 5 之间的整数。{Colors.RESET}")

    p_time = get_input("时间限制 (ms)", default=1000, val_type=int)
    p_mem = get_input("内存限制 (KB)", default=256, val_type=int)

    # --- 改动：处理 README 显示逻辑 ---

    # 1. 难度转星星
    # 例如 p_difficulty=1 -> "★☆☆☆☆"
    stars = "★" * p_difficulty + "☆" * (5 - p_difficulty)

    # 2. 时间格式化
    seconds = p_time / 1000.0
    if seconds.is_integer():
        time_str = str(int(seconds))  # 1.0 -> "1"
    else:
        time_str = str(seconds)  # 0.5 -> "0.5"

    # ---------------------------

    # 2. 构造路径
    folder_name = f"{p_id}-{p_name}"

    # 定位 problems 目录
    base_dir = os.getcwd()
    if os.path.basename(base_dir) == "tools":
        base_dir = os.path.dirname(base_dir)

    target_dir = os.path.join(base_dir, PROBLEMS_ROOT, folder_name)

    print(f"\n即将创建题目目录: {Colors.YELLOW}{target_dir}{Colors.RESET}")

    if os.path.exists(target_dir):
        confirm = input(
            f"{Colors.RED}警告: 目录已存在！是否覆盖？(y/N): {Colors.RESET}"
        ).lower()
        if confirm != "y":
            print("操作已取消。")
            sys.exit(0)

    # 3. 创建文件夹
    os.makedirs(os.path.join(target_dir, "samples"), exist_ok=True)
    os.makedirs(os.path.join(target_dir, "solutions"), exist_ok=True)
    print(f"Directory structure created.")

    # 4. 生成 requirement.json (保留数字难度)
    req_data = {
        "id": p_id,
        "title": p_title,
        "difficulty": str(p_difficulty),
        "time_limit": p_time,
        "memory_limit": p_mem,
    }
    create_file(
        os.path.join(target_dir, "requirement.json"),
        json.dumps(req_data, indent=4, ensure_ascii=False),
    )

    # 5. 生成 README.md (使用星星和格式化后的时间)
    readme_content = f"""# {p_title}

编号：{p_id}<br/>
难度：{stars}<br/>
时间限制：{time_str} 秒<br/>
内存限制：{p_mem} KB

## 问题描述

## 输入说明

## 输出说明

## 输入样例

## 输出样例
"""
    create_file(os.path.join(target_dir, "README.md"), readme_content)

    # 6. 生成 solutions/solution.c
    c_content = f"""/* {p_title} for problem {p_id} on XDOJ by {DEFAULT_AUTHOR} - Pure C version */

#include <stdio.h>
#include <stdlib.h>

enum
{{
}};

int main(void)
{{
    return 0;
}}
"""
    create_file(os.path.join(target_dir, "solutions", "solution.c"), c_content)

    # 7. 生成 solutions/solution.cpp
    cpp_content = f"""/* {p_title} for problem {p_id} on XDOJ by {DEFAULT_AUTHOR} - C++ version */

#include <bits/stdc++.h>
using namespace std;

int main(void)
{{
    return 0;
}}
"""
    create_file(os.path.join(target_dir, "solutions", "solution.cpp"), cpp_content)

    print(f"\n{Colors.GREEN}成功！题目 {p_id} ({p_title}) 初始化完成。{Colors.RESET}")


if __name__ == "__main__":
    main()
