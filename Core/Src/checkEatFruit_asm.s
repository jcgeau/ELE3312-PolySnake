    .syntax unified
    .thumb
    .text
    .align  2

    .global checkEatFruit_asm
    .type   checkEatFruit_asm, %function

checkEatFruit_asm:
    push    {r4, r5, lr}
    sub     sp, #12
    add     r3, sp, #8
    stmdb   r3, {r1, r2}

    @ for (int i = 0; i < fruitCount_; i++)
    ldr.w   r1, [r0, #808]      @ fruitCount_
    cmp     r1, #0
    ble     no_fruits            @ if fruitCount_ <= 0

    ldrh.w  lr, [sp]             @ headTile.x
    ldrh.w  r5, [sp, #2]         @ headTile.y
    movs    r3, #0               @ i = 0
    add.w   r12, r0, #8          @ base address fruits_[].x
    add.w   r4, r0, #10          @ base address fruits_[].y
    b       loop_start           @ start loop

loop_increment:
    adds    r3, #1
    cmp     r3, r1
    beq     no_match
    b       loop_start

loop_start:
    ldrh.w  r2, [r12, r3, lsl #3]
    cmp     r2, lr
    bne     loop_increment
    ldrh.w  r2, [r4, r3, lsl #3]
    cmp     r2, r5
    bne     loop_increment

    @ fruits_[i].id = tileType::BACKGROUND
    adds    r3, #1
    add.w   r0, r0, r3, lsl #3
    movs    r3, #0
    str     r3, [r0, #4]

    @ return true
    movs    r0, #1
    b       return_value

no_match:
    movs    r0, #0
    b       return_value

no_fruits:
    movs    r0, #0
    b       return_value

return_value:
    add     sp, #12
    pop     {r4, r5, pc}


    .size   checkEatFruit_asm, .-checkEatFruit_asm
