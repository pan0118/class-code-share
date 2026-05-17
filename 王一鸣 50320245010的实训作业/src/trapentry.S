#define LOAD		ld
#define STORE		sd
#define SIZE_REG	8

.macro save_all  
    csrw sscratch, sp
    addi sp, sp, -36 * SIZE_REG
    # save registers
    STORE x0, 0*SIZE_REG(sp)
    STORE x1, 1*SIZE_REG(sp)
    STORE x3, 3*SIZE_REG(sp)
    STORE x4, 4*SIZE_REG(sp)
    STORE x5, 5*SIZE_REG(sp)
    STORE x6, 6*SIZE_REG(sp)
    STORE x7, 7*SIZE_REG(sp)
    STORE x8, 8*SIZE_REG(sp)
    STORE x9, 9*SIZE_REG(sp)
    STORE x10, 10*SIZE_REG(sp)
    STORE x11, 11*SIZE_REG(sp)
    STORE x12, 12*SIZE_REG(sp)
    STORE x13, 13*SIZE_REG(sp)
    STORE x14, 14*SIZE_REG(sp)
    STORE x15, 15*SIZE_REG(sp)
    STORE x16, 16*SIZE_REG(sp)
    STORE x17, 17*SIZE_REG(sp)
    STORE x18, 18*SIZE_REG(sp)
    STORE x19, 19*SIZE_REG(sp)
    STORE x20, 20*SIZE_REG(sp)
    STORE x21, 21*SIZE_REG(sp)
    STORE x22, 22*SIZE_REG(sp)
    STORE x23, 23*SIZE_REG(sp)
    STORE x24, 24*SIZE_REG(sp)
    STORE x25, 25*SIZE_REG(sp)
    STORE x26, 26*SIZE_REG(sp)
    STORE x27, 27*SIZE_REG(sp)
    STORE x28, 28*SIZE_REG(sp)
    STORE x29, 29*SIZE_REG(sp)
    STORE x30, 30*SIZE_REG(sp)
    STORE x31, 31*SIZE_REG(sp)

    # save status, sepc, stval, scause,sp
    csrrw s0, sscratch, x0
    csrr s1, sstatus
    csrr s2, sepc
    csrr s3, stval
    csrr s4, scause

    STORE s0, 2*SIZE_REG(sp)
    STORE s1, 32*SIZE_REG(sp)
    STORE s2, 33*SIZE_REG(sp)
    STORE s3, 34*SIZE_REG(sp)
    STORE s4, 35*SIZE_REG(sp)
.endm


.macro restore_all 
    LOAD s1, 32*SIZE_REG(sp)
    LOAD s2, 33*SIZE_REG(sp)
    csrw sstatus, s1
    csrw sepc, s2
	
	# restore registers

LOAD x1, 1*SIZE_REG(sp)
    LOAD x3, 3*SIZE_REG(sp)
    LOAD x4, 4*SIZE_REG(sp)
    LOAD x5, 5*SIZE_REG(sp)
    LOAD x6, 6*SIZE_REG(sp)
    LOAD x7, 7*SIZE_REG(sp)
    LOAD x8, 8*SIZE_REG(sp)
    LOAD x9, 9*SIZE_REG(sp)
    LOAD x10, 10*SIZE_REG(sp)
    LOAD x11, 11*SIZE_REG(sp)
    LOAD x12, 12*SIZE_REG(sp)
    LOAD x13, 13*SIZE_REG(sp)
    LOAD x14, 14*SIZE_REG(sp)
    LOAD x15, 15*SIZE_REG(sp)
    LOAD x16, 16*SIZE_REG(sp)
    LOAD x17, 17*SIZE_REG(sp)
    LOAD x18, 18*SIZE_REG(sp)
    LOAD x19, 19*SIZE_REG(sp)
    LOAD x20, 20*SIZE_REG(sp)
    LOAD x21, 21*SIZE_REG(sp)
    LOAD x22, 22*SIZE_REG(sp)
    LOAD x23, 23*SIZE_REG(sp)
    LOAD x24, 24*SIZE_REG(sp)
    LOAD x25, 25*SIZE_REG(sp)
    LOAD x26, 26*SIZE_REG(sp)
    LOAD x27, 27*SIZE_REG(sp)
    LOAD x28, 28*SIZE_REG(sp)
    LOAD x29, 29*SIZE_REG(sp)
    LOAD x30, 30*SIZE_REG(sp)
    LOAD x31, 31*SIZE_REG(sp)
    # restore sp last
    LOAD x2, 2*SIZE_REG(sp)
    #addi sp, sp, 36 * SIZE_REG
.endm



.section .text
.align 4
.globl trap_vector
trap_vector:
	# save context.
    save_all
    move  a0, sp
    jal trap
    # sp should be the same as before "jal trap"
    .globl __trapret

__trapret:
    restore_all
    # return from supervisor call
    sret

