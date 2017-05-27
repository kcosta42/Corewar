#by cpoulet, classic imp

.name		"fork_hacking"
.comment	"cheating like a pinson..."

		ld	%525104, r1 
		fork %:modif
		st r1, 50
modif:	st r1, -7
