# 指定默认使用的 python 解释器
PYTHON := python

# 默认目标（直接输入 make 时显示帮助）
.PHONY: help
help:
	@echo "可用命令："
	@echo "  make new               - 交互式创建一个新题目"
	@echo "  make test P=<path>     - 运行指定题目的测试脚本"
	@echo "  make test-all          - 运行 problems/ 下所有题目的测试"
	@echo "  make clean             - 删除所有目录下的 .out 文件"
	@echo "  make list              - 扫描 problems/ 并更新 README.md 中的表格"
	@echo ""
	@echo "示例："
	@echo "  make new"
	@echo "  make test P=problems/242-score-statistics"

# --- 新建题目 ---
# 调用 tools/new_problem.py
.PHONY: new
new:
	@$(PYTHON) tools/new_problem.py

# --- 运行测试 ---
# 使用方法: make test P=problems/xxx
# 如果用户忘记加 P= 参数，报错提示
.PHONY: test
test:
ifndef P
	$(error 请指定题目路径，例如: make test P=problems/242-score-statistics)
endif
	@$(PYTHON) tools/run_test.py $(P)

# --- (可选) 批量运行所有测试 ---
# 自动寻找 problems/ 下的所有子文件夹并依次运行测试
.PHONY: test-all
test-all:
	@for dir in problems/*; do \
		if [ -d "$$dir" ]; then \
			$(PYTHON) tools/run_test.py "$$dir"; \
		fi \
	done

# --- 清理临时文件 (可选) ---
# 删除所有目录下的 .out 文件
.PHONY: clean
clean:
	@echo "正在清理临时 .out 文件..."
	@find . -name "*.out" -type f -delete
	@echo "清理完成。"

# --- 更新题目列表 ---
# 扫描 problems/ 并更新 README.md 中的表格
.PHONY: list
list:
	@$(PYTHON) tools/list_sync.py
