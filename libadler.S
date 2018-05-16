#define zero		$0	/* wired zero */
#define at		$1	/* assembler temp */
#define v0		$2	/* return value */
#define v1		$3
#define a0		$4	/* argument registers */
#define a1		$5
#define a2		$6
#define a3		$7
#define t0		$8	/* caller saved */
#define t1		$9
#define t2		$10
#define t3		$11
#define t4		$12
#define t5		$13
#define t6		$14
#define t7		$15
#define s0		$16	/* callee saved */
#define s1		$17
#define s2		$18
#define s3		$19
#define s4		$20
#define s5		$21
#define s6		$22
#define s7		$23
#define t8		$24	/* code generator */
#define t9		$25
#define k0		$26	/* kernel temporary */
#define k1		$27
#define gp		$28	/* global pointer */
#define sp		$29	/* stack pointer */
#define fp		$30	/* frame pointer */
#define ra		$31	/* return address */


	.set	noreorder
	.set	noat

	.text
	.global	Adler32

	.ent	Adler32

//J ADLER-32計算
// unsigned int Adler32(unsigned int uiAdler, const unsigned char *pSrc, unsigned int uiSize);
Adler32:
		andi		v0, a0, 0xFFFF		// v0 = a0 & 0xFFFF = s1
		srl			v1, a0, 16			// v1 = a0>>16      = s2
		beq			a2, zero, _adler32_end
		ori			t2, zero, 65521		// t2 = 65521 = BASE	65536より小さい最大の素数

	//J ループ回数を最大NMAX回に制限
_adler32_lop1:
		addiu		t1, zero, 5552		// t1 = 5552 = NMAX
		slti		t0, a2, 5552		// t0 = (a2 < 5552) = (a2 < NMAX)
		movn		t1, a2, t0			// t1 = t0 ? a2 : 5552 = (a2 < NMAX) ? a2 : NMAX = min(a2, NMAX)
		subu		a2, a2, t1			// a2 = a2 - t1

	//J 最大NMAX回数分の加算ループ
_adler32_lop2:
		lbu			t0, 0(a1)			// t0 = *(a1)   = s1
		addiu		a1, a1, 1			// a1 = a1 + 1
		addiu		t1, t1, -1			// t1 = t1 - 1
		addu		v0, v0, t0			// v0 = v0 + t0 = s1
		nop
		nop
		bne			t1, zero, _adler32_lop2	
		addu		v1, v1, v0			// v1 = v1 + v0 = s2

	//J s1,s2のBASE剰余をとって正規化
		divu		v0, t2				// HI0 = v0 % t2 = s1 % BASE
		mfhi		v0					// v0 = HI0 = s1
		divu		v1, t2				// HI1 = v1 % t2 = s2 % BASE
		mfhi		v1					// v1 = HI1 = s2

		bne			a2, zero, _adler32_lop1
		nop								// ディレイスロット

	//J ADLER-32計算終了
_adler32_end:
		sll			v1, v1, 16			// v1 = v1<<16 
		j			ra
		or			v0, v0, v1			// v0 = v0 | v1

	.end	Adler32

