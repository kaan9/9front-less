	TEXT	memchr(SB), $0

MOVW	R7, 0(FP)
	MOVW	n+8(FP), R7
	SUBCC	R0,R7, R0
	BE	ret
	MOVW	s1+0(FP), R8
	MOVBU	c+7(FP), R9
	ADD	R7,R8, R11

l1:
	MOVBU	(R8), R10
	SUBCC	R9,R10, R0
	ADD	$1, R8
	BE	eq
	SUBCC	R8,R11, R0
	BNE	l1

	MOVW	R0, R7
	RETURN

eq:
	SUB	$1,R8, R7

ret:
	RETURN
