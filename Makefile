# 定义变量
BUILD_DIR := makebuild            # 构建目录
CMAKE_BUILD_TYPE := Release   # 构建类型，可以是 Release 或 Debug
BUILTIN_ASM := src/IR/builtin.s	# 内置汇编文件

# 默认目标
all: build

# 构建目标，调用CMake进行构建
build:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) -Wno-dev ..
	@cd $(BUILD_DIR) && $(MAKE) -j4

acturalrun:
	@cd $(BUILD_DIR) && ./zmxcc /dev/stdin -o /dev/stdout --optimize-all 2>/dev/null
# 运行目标，运行生成的可执行文件
run: acturalrun
	@cat $(BUILTIN_ASM) >>/dev/stdout

# 清理目标
clean:
	@rm -rf $(BUILD_DIR)

.PHONY: all build run clean
