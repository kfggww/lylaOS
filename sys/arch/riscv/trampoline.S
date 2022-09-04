
.section .trampoline
.global trampoline
.global uservec
.p2align 12
trampoline:
uservec:
    /*save user mode context*/
    csrrw a0, sscratch, a0
    sd ra, 0(a0)
    sd sp, 8(a0)
    sd gp, 16(a0)
    sd tp, 24(a0)
    sd t0, 32(a0)
    sd t1, 40(a0)
    sd t2, 48(a0)
    sd s0, 56(a0)
    sd s1, 64(a0)
    sd a1, 80(a0)
    sd a2, 88(a0)
    sd a3, 96(a0)
    sd a4, 104(a0)
    sd a5, 112(a0)
    sd a6, 120(a0)
    sd a7, 128(a0)
    sd s2, 136(a0)
    sd s3, 144(a0)
    sd s4, 152(a0)
    sd s5, 160(a0)
    sd s6, 168(a0)
    sd s7, 176(a0)
    sd s8, 184(a0)
    sd s9, 192(a0)
    sd s10, 200(a0)
    sd s11, 208(a0)
    sd t3, 216(a0)
    sd t4, 224(a0)
    sd t5, 232(a0)
    sd t6, 240(a0)
    /*save register a0 and sepc*/
    csrr t0, sscratch
    sd t0, 72(a0)
    csrr t0, sepc
    sd t0, 248(a0)

    /*switch to kernel stack*/
    ld sp, 256(a0)

    /*swtich to kernel page table*/
    ld t0, 264(a0)
    ld t1, 272(a0)
    csrw satp, t0
    sfence.vma zero, zero

    /*jump to usertrap function, NEVER use 'call' here*/
    jr t1

.global uservec_ret
uservec_ret:
    /*switch back to user process page table. it must 
    be done here, because this section has the same 
    mapping in both kernel and user process, so after
    switching the following lines of instructions can
    still be executed correctly*/
    csrw satp, a0
    # sfence.vma zero, zero

    /*load user mode context from trap frame*/
    ld ra, 0(a1)
    ld sp, 8(a1)
    ld gp, 16(a1)
    ld tp, 24(a1)
    ld t0, 32(a1)
    ld t1, 40(a1)
    ld t2, 48(a1)
    ld s0, 56(a1)
    ld s1, 64(a1)
    ld a0, 72(a1)
    ld a2, 88(a1)
    ld a3, 96(a1)
    ld a4, 104(a1)
    ld a5, 112(a1)
    ld a6, 120(a1)
    ld a7, 128(a1)
    ld s2, 136(a1)
    ld s3, 144(a1)
    ld s4, 152(a1)
    ld s5, 160(a1)
    ld s6, 168(a1)
    ld s7, 176(a1)
    ld s8, 184(a1)
    ld s9, 192(a1)
    ld s10, 200(a1)
    ld s11, 208(a1)
    ld t3, 216(a1)
    ld t4, 224(a1)
    ld t5, 232(a1)
    ld t6, 240(a1)
    ld a1, 80(a1)

    /*retrun to user mode*/
    sret
