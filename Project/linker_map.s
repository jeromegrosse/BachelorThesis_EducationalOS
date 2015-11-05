.globl _start

// ;See ARM section 2-10: Program Status Register (PSR)

.equ    PSR_MODE_USER,         0x10
.equ    PSR_MODE_FIQ,          0x11
.equ    PSR_MODE_IRQ,          0x12
.equ    PSR_MODE_SVR,          0x13
.equ    PSR_MODE_ABORT,        0x17
.equ    PSR_MODE_UNDEFINED,    0x1B
.equ    PSR_MODE_SYSTEM,       0x1F


// See ARM section 2-10: Program Status Register (PSR)
.equ    CPSR_IRQ_DISABLE,       0x80
.equ    CPSR_FIQ_DISABLE,       0x40
.equ    CPSR_THUMB,             0x20


_start:
    ldr pc, _reset_handler
    ldr pc, _undefined_instruction_vector_handler
    ldr pc, _software_interrupt_vector_handler
    ldr pc, _prefetch_abort_vector_handler
    ldr pc, _data_abort_vector_handler
    ldr pc, _unused_handler_handler
    ldr pc, _interrupt_vector_handler
    ldr pc, _fast_interrupt_vector_handler

    _reset_handler:                           .word   _reset_
    _undefined_instruction_vector_handler:    .word   undefined_instruction_vector
    _software_interrupt_vector_handler:       .word   software_interrupt_vector
    _prefetch_abort_vector_handler:           .word   prefetch_abort_vector
    _data_abort_vector_handler:               .word   data_abort_vector
    _unused_handler_handler:                  .word   _reset_                       // not used
    _interrupt_vector_handler:                .word   interrupt_vector
    _fast_interrupt_vector_handler:           .word   fast_interrupt_vector

_reset_:
    mov     r0, #0x8000
    mov     r1, #0x0000
    ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
    stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}
    ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
    stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}


    //
    // Set up the stacks for the differents CPU modes
    //

    // Interrupt
    mov r0, #(PSR_MODE_IRQ | CPSR_IRQ_DISABLE | CPSR_FIQ_DISABLE )
    msr cpsr_c, r0
    mov sp, #0x8000


    // Fast interrupt
    mov r0, #(PSR_MODE_FIQ | CPSR_IRQ_DISABLE | CPSR_FIQ_DISABLE )
    msr cpsr_c,r0
    mov sp, #0x4000


    // Supervisor
    mov r0, #(PSR_MODE_SVR | CPSR_IRQ_DISABLE | CPSR_FIQ_DISABLE )
    msr cpsr_c,r0
    mov sp, #0x8000000

    bl kernel_main
hang: b hang


.globl ENABLE_IRQ
ENABLE_IRQ:
    mrs r0, cpsr
    bic r0, r0, #(CPSR_IRQ_DISABLE)
    msr cpsr_c, r0
    bx lr


.globl DISABLE_IRQ
DISABLE_IRQ:
    mrs r0, cpsr
    orr r0, r0, #(CPSR_IRQ_DISABLE)
    msr cpsr_c, r0
    bx lr
