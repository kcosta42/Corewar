#by cpoulet, classic bomber

.name		"Chickabomb"
.comment	"tic, tac, tic, tac,...BOOM!"

		sti r1, %:live, %1
		ld	%12, r2
		ld	%252645135, r4
loop:	add r2, r3, r3
		sti	r4, %100, r3
live:	live %0
		ld	%0, r16
		zjmp %:loop
