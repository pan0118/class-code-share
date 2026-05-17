#include "print.h"
#include "trap.h"

void trap_test(){
    printf("*(int *)0x00000000 = 100\n");

	/*
	 * Synchronous exception code = 7
	 * Store/AMO access fault
	 */
	*(int *)0x00000000 = 100;
	print_string("Yeah! I'm return back from trap!\n");
}


void test_interrupts() {
    print_string("Testing interrupts...\n");
    trap_test();
    print_string("Interrupt test completed.\n");
}

void main(void) {
    print_string("RISC-V Bootloader\n");
    print_string("Hello XOS!\n");

    // 初始化中断处理
    init_interrupt();


    // 测试中断
    test_interrupts();

    // 进入无限循环
    while (1) {
        // 无限循环
    }
}