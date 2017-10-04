;sum = 0(r1)
;item1 = 4(r1)
;item2 = 8(r1)
;total = 12(r1)
;tax = 16(r1)
;sum2 = 20(r1)
;item3 = 24(r1)
;item4 = 28(r1)

lw r3, 4(r1)    ;item1 to r3
lw r4, 8(r1)    ;item2 to r4
lw r6, 16(r1)   ;tax to r6
lw r8, 24(r1)   ;item3 to r8
lw r9, 28(r1)   ;item4 to r9
add r5, r3, r4  ;add item1 and item2
sw 0(r1), r5    ;store item1+item1 to sum
add r10, r8, r9 ;add item3 and item4
add r7, r5, r6  ;add sum and tax
sw 12(r1), r7   ;store sum+tax to total
sw 20(r1), r10  ;store item3+item4 to sum2
nop
nop
nop
nop
trap #0
