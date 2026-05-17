#include "defs.h"
#include "trap.h"

extern void trap_vector();

void kernel_trap_init()
{
	w_stvec((uint64)trap_vector);
    intr_on();
}

void init_interrupt() {
    kernel_trap_init();
}

void print_trapframe(struct trapframe *tf) {
    printf("trapframe at %p\n", tf);
    print_regs(&tf->gpr);
    printf("  status   0x%08x\n", tf->status);
    printf("  epc      0x%08x\n", tf->epc);
    printf("  stval    0x%08x\n", tf->stval);  // 修复 staval → stval
    printf("  cause    0x%08x\n", tf->cause);
}

void print_csr(struct trapframe *tf) {
    printf("  status   0x%x\n", tf->status);
    printf("  epc      0x%x\n", tf->epc);
    printf("  stval    0x%x\n", tf->stval);   // 修复 staval → stval
    printf("  cause    0x%x\n", tf->cause);
}

void print_regs(struct pushregs *gpr) {
    printf("  zero     0x%x\n", gpr->zero);
    printf("  ra       0x%x\n", gpr->ra);
    printf("  sp       0x%x\n", gpr->sp);
    printf("  gp       0x%x\n", gpr->gp);
    printf("  tp       0x%x\n", gpr->tp);
    printf("  t0       0x%x\n", gpr->t0);
    printf("  t1       0x%x\n", gpr->t1);
    printf("  t2       0x%x\n", gpr->t2);
    printf("  s0       0x%x\n", gpr->s0);
    printf("  s1       0x%x\n", gpr->s1);
    printf("  a0       0x%x\n", gpr->a0);
    printf("  a1       0x%x\n", gpr->a1);
    printf("  a2       0x%x\n", gpr->a2);
    printf("  a3       0x%x\n", gpr->a3);
    printf("  a4       0x%x\n", gpr->a4);
    printf("  a5       0x%x\n", gpr->a5);
    printf("  a6       0x%x\n", gpr->a6);
    printf("  a7       0x%x\n", gpr->a7);
    printf("  s2       0x%x\n", gpr->s2);
    printf("  s3       0x%x\n", gpr->s3);
    printf("  s4       0x%x\n", gpr->s4);
    printf("  s5       0x%x\n", gpr->s5);
    printf("  s6       0x%x\n", gpr->s6);
    printf("  s7       0x%x\n", gpr->s7);
    printf("  s8       0x%x\n", gpr->s8);
    printf("  s9       0x%x\n", gpr->s9);
    printf("  s10      0x%x\n", gpr->s10);
    printf("  s11      0x%x\n", gpr->s11);
    printf("  t3       0x%x\n", gpr->t3);
    printf("  t4       0x%x\n", gpr->t4);
    printf("  t5       0x%x\n", gpr->t5);
    printf("  t6       0x%x\n", gpr->t6);
}

void handle_interrupt(struct trapframe *tf) {
    uint64 cause_code = tf->cause & SCAUSE_MASK_ECODE;
    switch (cause_code) {
        case SupervisorSoft:
            printf("Supervisor Software Interrupt!\n");
            break;
        case SupervisorTimer:
            printf("Supervisor Timer Interrupt!\n");
            break;
        case SupervisorExternal:
            printf("Supervisor External Interrupt!\n");
            break;
        default:
            printf("Unknown Interrupt! Code = %d\n", (int)cause_code);
            break;
    }
}

void handle_exception(struct trapframe *tf) {
    uint64 cause_code = tf->cause & SCAUSE_MASK_ECODE;
    printf("Exception occurred! Cause: %d (Store Access Fault)\n", (int)cause_code);
    print_csr(tf);
}

static inline void trap_handler(struct trapframe *tf) {
    if (tf->cause & SCAUSE_MASK_INTERRUPT) {
        handle_interrupt(tf);
    } else {
        handle_exception(tf);
        tf->epc += 4; // 跳过出错指令
    }
}

void trap(struct trapframe *tf) {
    trap_handler(tf);
}