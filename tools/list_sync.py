import os
import json
import sys

# --- 配置 ---
PROBLEMS_DIR = "problems"
README_FILE = "README.md"
MARKER_BEGIN = "<!--problemlist-begins-->"
MARKER_END = "<!--problemlist-ends-->"


class Colors:
    HEADER = "\033[95m"
    OKBLUE = "\033[94m"
    OKGREEN = "\033[92m"
    WARNING = "\033[93m"
    FAIL = "\033[91m"
    ENDC = "\033[0m"


def get_stars(difficulty):
    """将数字难度转换为星星"""
    try:
        val = int(difficulty)
        val = max(1, min(5, val))
        return "★" * val + "☆" * (5 - val)
    except:
        return difficulty


def load_problems():
    """扫描题目目录并提取信息"""
    problems = []

    if not os.path.exists(PROBLEMS_DIR):
        print(f"{Colors.FAIL}Error: '{PROBLEMS_DIR}' directory not found.{Colors.ENDC}")
        return []

    # 遍历 problems 下的所有子文件夹
    for entry in os.listdir(PROBLEMS_DIR):
        full_path = os.path.join(PROBLEMS_DIR, entry)

        if not os.path.isdir(full_path):
            continue

        json_path = os.path.join(full_path, "requirement.json")
        if not os.path.exists(json_path):
            continue

        try:
            with open(json_path, "r", encoding="utf-8") as f:
                data = json.load(f)

            # 检查解法文件是否存在
            has_c = os.path.exists(os.path.join(full_path, "solutions", "solution.c"))
            has_cpp = os.path.exists(
                os.path.join(full_path, "solutions", "solution.cpp")
            )

            problems.append(
                {
                    "id": data.get("id", 0),
                    "title": data.get("title", entry),
                    "difficulty": data.get("difficulty", "1"),
                    "path": f"{PROBLEMS_DIR}/{entry}",  # 相对 README 的路径
                    "has_c": has_c,
                    "has_cpp": has_cpp,
                }
            )
        except Exception as e:
            print(
                f"{Colors.WARNING}Warning: Failed to process {entry}: {e}{Colors.ENDC}"
            )

    # 按 ID 排序
    problems.sort(key=lambda x: x["id"])
    return problems


def generate_markdown_table(problems):
    """生成 Markdown 表格字符串"""
    if not problems:
        return "\n*暂无题目*\n"

    # 表头
    md = "| ID | 标题 | 难度 | C 版本 | C++ 版本 |\n"
    md += "|:--:|:---|:---|:--:|:--:|\n"

    for p in problems:
        stars = get_stars(p["difficulty"])

        # 构造标题链接（指向题目文件夹）
        title_link = f"[{p['title']}]({p['path']})"

        # 构造代码链接
        # 注意：这里使用 HTML 实体 ✓ 或简单的文本
        c_link = f"[跳转]({p['path']}/solutions/solution.c)" if p["has_c"] else "-"
        cpp_link = (
            f"[跳转]({p['path']}/solutions/solution.cpp)" if p["has_cpp"] else "-"
        )

        md += f"| {p['id']} | {title_link} | {stars} | {c_link} | {cpp_link} |\n"

    return md


def update_readme():
    if not os.path.exists(README_FILE):
        print(f"{Colors.FAIL}Error: {README_FILE} not found.{Colors.ENDC}")
        return

    with open(README_FILE, "r", encoding="utf-8") as f:
        content = f.read()

    # 检查标记是否存在
    if MARKER_BEGIN not in content or MARKER_END not in content:
        print(f"{Colors.FAIL}Error: Markers not found in {README_FILE}.{Colors.ENDC}")
        print(f"Please ensure '{MARKER_BEGIN}' and '{MARKER_END}' are in the file.")
        return

    # 1. 获取题目数据
    problems = load_problems()
    print(f"{Colors.OKBLUE}Found {len(problems)} problems.{Colors.ENDC}")

    # 2. 生成新表格
    new_table = "\n" * 2 + generate_markdown_table(problems) + "\n"

    # 3. 替换内容
    # 使用 split 分割，保留开头和结尾，只替换中间
    part_before = content.split(MARKER_BEGIN)[0]
    part_after = content.split(MARKER_END)[1]

    new_content = part_before + MARKER_BEGIN + new_table + MARKER_END + part_after

    # 4. 写回文件
    with open(README_FILE, "w", encoding="utf-8") as f:
        f.write(new_content)

    print(f"{Colors.OKGREEN}Success! README.md has been updated.{Colors.ENDC}")


if __name__ == "__main__":
    update_readme()
