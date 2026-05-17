#ifndef TRAP_H
#define TRAP_H
#include "defs.h"
#include "types.h"

struct pushregs {
    uintptr zero;  // Hard-wired zero
    uintptr ra;    // Return address
    uintptr sp;    // Stack pointer
    uintptr gp;    // Global pointer
    uintptr tp;    // Thread pointer
    uintptr t0;    // Temporary
    uintptr t1;    // Temporary
    uintptr t2;    // Temporary
    uintptr s0;    // Saved register/frame pointer
    uintptr s1;    // Saved register
    uintptr a0;    // Function argument/return value
    uintptr a1;    // Function argument/return value
    uintptr a2;    // Function argument
    uintptr a3;    // Function argument
    uintptr a4;    // Function argument
    uintptr a5;    // Function argument
    uintptr a6;    // Function argument
    uintptr a7;    // Function argument
    uintptr s2;    // Saved register
    uintptr s3;    // Saved register
    uintptr s4;    // Saved register
    uintptr s5;    // Saved register
    uintptr s6;    // Saved register
    uintptr s7;    // Saved register
    uintptr s8;    // Saved register
    uintptr s9;    // Saved register
    uintptr s10;   // Saved register
    uintptr s11;   // Saved register
    uintptr t3;    // Temporary
    uintptr t4;    // Temporary
    uintptr t5;    // Temporary
    uintptr t6;    // Temporary
};

struct trapframe {
    struct pushregs gpr;
    uintptr status;
    uintptr epc;
    uintptr stval;
    uintptr cause;
};

// 函数声明
void kernel_trap_init(void);
void init_interrupt(void);
void print_trapframe(struct trapframe *tf);
void print_regs(struct pushregs *gpr);
void handle_interrupt(struct trapframe *tf);
void handle_exception(struct trapframe *tf);
void trap(struct trapframe *tf);



enum Exception {
	InstructionMisaligned = 0,
	InstructionAccessFault = 1,
	IllegalInstruction = 2,
	Breakpoint = 3,
	LoadMisaligned = 4,
	LoadAccessFault = 5,
	StoreMisaligned = 6,
	StoreAccessFault = 7,
	UserEnvCall = 8,
	SupervisorEnvCall = 9,
	MachineEnvCall = 11,
	InstructionPageFault = 12,
	LoadPageFault = 13,
	StorePageFault = 15,
};

enum Interrupt {
	UserSoft = 0,
	SupervisorSoft,
	UserTimer = 4,
	SupervisorTimer,
	UserExternal = 8,
	SupervisorExternal,
};

#endif // TRAP_H