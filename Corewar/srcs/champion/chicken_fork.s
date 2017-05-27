#by cpoulet, classic imp
#MOD 043: 1879310379-0
#MOD 050: 1879310386-15

.name		"mychicken_fork"
.comment	"one is good, two is better..."

		ld	%34341294, r16
		sti r1, %:live, %1
		ld	%1879310801, r3
		ld	%65540, r1
		ld	62, r4
		ld	61, r5
		ld	60, r6
		ld	59, r7
		ld	58, r8
		ld	57, r9
		ld	56, r10
		ld	55, r11
		ld	54, r12
		ld	53, r13
		ld	52, r14
		ld	%34144686, r15
loop:	add r1, r3, r3
val:	st r4, 465
		st r3, -4
		and	r3, %1048576, r2
		zjmp %:loop
live:	live %1
		ld	%1879310801, r3
		ld %0, r2
fork:	fork %430
		ld %52, r2
		sub r16, r2, r16
		st r16, -16
		sub r3, r2, r3
		st r3, -64
		st r3, -42
		ld %0, r2
		zjmp %:loop
