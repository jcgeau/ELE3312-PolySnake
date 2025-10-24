    .syntax unified
    .thumb
    .text
    .align  2

    .global checkColision_asm
    .type   checkColision_asm, %function

checkColision_asm:
    push    {r4, r5, lr}

    @ if(snake_[head_].x >= 320)
    ldr.w   r4, [r0, #808]      @ head index
    add.w   r3, r0, r4, lsl #3
    ldrh.w  r12, [r3, #8]       @ snake_[head_].x
    cmp.w   r12, #320
    bcs     collision_true       @ if x >= 320

    @ if(snake_[head_].y >= 240)
    ldrh    r5, [r3, #10]       @ snake_[head_].y
    cmp     r5, #239
    bhi     collision_true       @ if y >= 240

    @ for(int i = tail_; i != head_;)
    ldr.w   r3, [r0, #812]      @ i = tail_
    mov.w   lr, #0               @ temp 0

loop_start:
    @ i = (i >= 99) ? 0 : (i + 1)
    cmp     r3, #98
    ite     le
    addle   r3, #1
    movgt   r3, lr

    cmp     r4, r3               @ i == head_
    beq     collision_false

    @ if((snake_[head_].x == snake_[i].x) && (snake_[head_].y == snake_[i].y))
    add.w   r2, r0, r3, lsl #3
    ldrh    r1, [r2, #8]         @ snake_[i].x
    cmp     r1, r12
    bne     loop_start
    ldrh    r2, [r2, #10]        @ snake_[i].y
    cmp     r2, r5
    bne     loop_start

    @ return true (collision detected)
collision_true:
    movs    r0, #1
    b       function_end

collision_false:
    movs    r0, #0

function_end:
    pop     {r4, r5, pc}

    .size   checkColision_asm, .-checkColision_asm
