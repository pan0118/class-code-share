#include "defs.h"
#include "trap.h"
#include "sbi.h"
#include <stdint.h>

extern void trap_vector();
uint32_t interrupt_count = 0;

void kernel_trap_init() {
    w_stvec((uint64_t)trap_vector);
    intr_on();
}

void init_interrupt() {
    kernel_trap_init();
}

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

void handle_interrupt(struct trapframe *tf) {
    uint64_t cause_code = tf->cause & 0x3FF;
    interrupt_count++;

    if (cause_code == 5) { // Supervisor Timer
        printf("[Timer] Interrupt! Count: %d\n", interrupt_count);
        set_timer(read_time() + 1000000);
    }
}

void handle_exception(struct trapframe *tf) {
    tf->epc += 4; // Skip bad instruction
}

static inline void trap_handler(struct trapframe *tf) {
    if (tf->cause & (1ULL << 63)) {
        handle_interrupt(tf);
    } else {
        handle_exception(tf);
    }
}

void trap(struct trapframe *tf) {
    trap_handler(tf);
}