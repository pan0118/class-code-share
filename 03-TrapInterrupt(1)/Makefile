.PHONY: all build clean run

# 工具链前缀
TOOLPREFIX = riscv64-unknown-elf-
CC = $(TOOLPREFIX)gcc
LD = $(TOOLPREFIX)ld
OBJCOPY = $(TOOLPREFIX)objcopy

# 构建目录
BUILDDIR = out

# 源文件
C_SRCS = src/main.c src/print.c src/sbi.c src/trap.c 
AS_SRCS = kernel.S src/trapentry.S

# 对象文件
C_OBJS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(C_SRCS))))
AS_OBJS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(AS_SRCS))))
OBJS = $(C_OBJS) $(AS_OBJS)

# 编译器标志
CFLAGS = -Wall -Werror -O -fno-omit-frame-pointer -ggdb -march=rv64imafdc_zicsr -Iinclude
CFLAGS += -MD
CFLAGS += -mcmodel=medany
CFLAGS += -ffreestanding -fno-common -nostdlib -mno-relax
CFLAGS += -D MAXNUM_CPU=4  # 定义最大CPU数量为4
CFLAGS += -Wno-unused-variable

# 链接器标志
LDFLAGS = -T linker.ld -nostdlib 

# SBI位置
BOOTLOADER := ./lib/rustsbi-qemu/rustsbi-qemu.bin

# 默认目标
all: build

# 构建目标
build: $(BUILDDIR)/kernel.elf

# 生成 C 对象文件
$(C_OBJS): $(BUILDDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# 生成汇编对象文件
$(AS_OBJS): $(BUILDDIR)/%.o: %.S
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# 链接生成 ELF 文件
$(BUILDDIR)/kernel.elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

# 清理构建目录
clean:
	rm -rf $(BUILDDIR)

# 运行内核
run: build
	qemu-system-riscv64 -machine virt -nographic -bios none -kernel $(BUILDDIR)/kernel.elf -bios $(BOOTLOADER) 