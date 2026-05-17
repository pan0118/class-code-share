#include "sbi.h"
#include "types.h"

enum sbi_call_type {
    SBI_SET_TIMER = 0,
    SBI_CONSOLE_PUTCHAR = 1,
    SBI_CONSOLE_GETCHAR = 2,
    SBI_CLEAR_IPI = 3,
    SBI_SEND_IPI = 4,
    SBI_REMOTE_FENCE_I = 5,
    SBI_REMOTE_SFENCE_VMA = 6,
    SBI_REMOTE_SFENCE_VMA_ASID = 7,
    SBI_SHUTDOWN = 8
};

// 加 static 修复编译错误
static inline int sbi_call(enum sbi_call_type which, uint64 arg0, uint64 arg1, uint64 arg2)
{
	register uint64 a0 asm("a0") = arg0;
	register uint64 a1 asm("a1") = arg1;
	register uint64 a2 asm("a2") = arg2;
	register uint64 a7 asm("a7") = which;
	int ret;

	asm volatile("ecall"
		     : "=r"(ret)
		     : "r"(a0), "r"(a1), "r"(a2), "r"(a7)
		     : "memory");

	if (ret < 0) {
        return -1;
    }
    return ret;
}

void console_putchar(int c)
{
	sbi_call(SBI_CONSOLE_PUTCHAR, c, 0, 0);
}

int console_getchar()
{
	return sbi_call(SBI_CONSOLE_GETCHAR, 0, 0, 0);
}

void shutdown()
{
	sbi_call(SBI_SHUTDOWN, 0, 0, 0);
}