#include "print.h"
#include "trap.h"
#include "sbi.h"
#include <stdint.h>

static inline uint64_t read_time() {
    uint64_t time;
    asm volatile ("rdtime %0" : "=r"(time));
    return time;
}

static inline void set_timer(uint64_t time) {
    asm volatile(
        "li a7, 0x54494d45\n"
        "li a6, 0\n"
        "mv a0, %0\n"
        "ecall"
        ::"r"(time)
        : "a0","a6","a7"
    );
}

static inline void delay(uint64_t count) {
    for (uint64_t i = 0; i < count; i++) {
        asm volatile ("nop");
    }
}

void test_store_fault() {
    printf("\n[Test 1] Store Access Fault\n");
    *(int *)0x00000000 = 123;
}

void test_load_misalign() {
    printf("\n[Test 2] Load Address Misaligned\n");
    int val = *(int *)0x123;
    (void)val;
}

void test_illegal_inst() {
    printf("\n[Test 3] Illegal Instruction\n");
    asm volatile (".word 0x00000001");
}

void test_breakpoint() {
    printf("\n[Test 4] Breakpoint Exception\n");
    asm volatile ("ebreak");
}

void trap_test() {
    printf("=== Exception Test Start ===\n");

    test_store_fault();
    test_load_misalign();
    test_illegal_inst();
    test_breakpoint();

    printf("\n=== All exceptions handled successfully ===\n");
}

void test_interrupts() {
    printf("=== Timer Interrupt Test ===\n");
    trap_test();
}

void main(void) {
    printf("RISC-V Bootloader\n");
    printf("Hello Extended OS!\n");

    init_interrupt();
    set_timer(read_time() + 1000000);

    test_interrupts();

    while (1) {
        printf("System running...\n");
        delay(10000000);
    }
}