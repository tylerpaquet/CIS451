; The base address of array a is in r1 
; The base address of array b is in r2
; The base address of array c is in r3

	  lw r5, 0(r1)		; Load from a into r5
      lw r6, 0(r2)		; Load from b into r6
      lw r8, 4(r1)		; Load from a into r8
      lw r9, 4(r2)		; Load from b into r9
      lw r10, 8(r1)		; Load from a into r10
      lw r11, 8(r2)		; Load from b into r11
      lw r12, 12(r1)	; Load from a into r12
      lw r13, 12(r2)	; Load from b into r13
      add r7, r5, r6	; r7 = r5 + r6
      sw  0(r3), r7		; store result back in array c  
      add r7, r8, r9	; r7 = r8 + r9
      sw  4(r3), r7		; store result back in array c
      add r7, r10, r11	; r7 = r10 + r11
      sw  8(r3), r7		; store result back in array c
      add r7, r12, r13	; r7 = r12 + r13
      sw  12(r3), r7	; store result back in array c
      sw 0(r3), r0 		; set c[0] to 0.
      nop;
      nop; 
      nop;
      nop;	
      trap #0;
