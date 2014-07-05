;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 2.9.0 #5416 (Jul 24 2010) (UNIX)
; This file was generated Sun Aug  8 12:38:54 2010
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
	.file	"delay.c"
	list	p=16f628a
	radix dec
	include "p16f628a.inc"
;--------------------------------------------------------
; external declarations
;--------------------------------------------------------

	extern PSAVE
	extern SSAVE
	extern WSAVE
	extern STK12
	extern STK11
	extern STK10
	extern STK09
	extern STK08
	extern STK07
	extern STK06
	extern STK05
	extern STK04
	extern STK03
	extern STK02
	extern STK01
	extern STK00
;--------------------------------------------------------
; global declarations
;--------------------------------------------------------
	global	_delay_s
	global	_delay_ms

;--------------------------------------------------------
; global definitions
;--------------------------------------------------------
;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
;--------------------------------------------------------
; compiler-defined variables
;--------------------------------------------------------
UDL_delay_0	udata
r0x1000	res	1
r0x1001	res	1
r0x1002	res	1
r0x1003	res	1
r0x1004	res	1
;--------------------------------------------------------
; initialized data
;--------------------------------------------------------
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
;	udata_ovr
;--------------------------------------------------------
; code
;--------------------------------------------------------
code_delay	code
;***
;  pBlock Stats: dbName = C
;***
;entry:  _delay_s	;Function start
; 2 exit points
;has an exit
;functions called:
;   _delay_ms
;   _delay_ms
;2 compiler assigned registers:
;   r0x1003
;   r0x1004
;; Starting pCode block
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2283:genFunction *{*
;; ***	genFunction  2285 curr label offset=4previous max_key=14 
_delay_s	;Function start
; 2 exit points
;; gen.c:2261:resultRemat *{*
;; gen.c:6739:genReceive *{*
;; ***	genReceive  6740
;;	721 register type nRegs=1
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x104B, size=1, right -=-, size=0
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x104B 
	.line	30; "delay.c"	void delay_s (unsigned char cnt) {
	BANKSEL	r0x1003
	MOVWF	r0x1003
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;;	721 register type nRegs=1
;;	721 register type nRegs=1
;; 	line = 6342 result AOP_REG=r0x104B, size=1, left -=-, size=0, right AOP_REG=r0x104B, size=1
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;;	721 register type nRegs=1
;; 	line = 6342 result AOP_REG=r0x104C, size=1, left -=-, size=0, right AOP_LIT=0x04, size=1
;; ***	genAssign  6434
; >>> gen.c:6439:genAssign
_00131_DS_
	.line	34; "delay.c"	do { delay_ms(250); } while(--i);
	MOVLW	0x04
; >>> gen.c:6441:genAssign
;;	1109 rIdx = r0x104C 
	BANKSEL	r0x1004
	MOVWF	r0x1004
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
;; 	2079 left AOP_LIT
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
_00123_DS_
	MOVLW	0xfa
; >>> gen.c:2118:genCall
	CALL	_delay_ms
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:6695:genDjnz *{*
;; ***	genDjnz  6696
;;	721 register type nRegs=1
; >>> gen.c:6726:genDjnz
;;	1109 rIdx = r0x104C 
	BANKSEL	r0x1004
	DECFSZ	r0x1004,F
; >>> gen.c:6727:genDjnz
;; ***	popGetLabel  key=1, label offset 22
	GOTO	_00123_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:6695:genDjnz *{*
;; ***	genDjnz  6696
;;	721 register type nRegs=1
; >>> gen.c:6726:genDjnz
;;	1109 rIdx = r0x104B 
	.line	36; "delay.c"	while (--cnt);
	DECFSZ	r0x1003,F
; >>> gen.c:6727:genDjnz
;; ***	popGetLabel  key=9, label offset 22
	GOTO	_00131_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2435:genEndFunction *{*
;; ***	genEndFunction  2437
	RETURN	
; exit point of _delay_s

;***
;  pBlock Stats: dbName = C
;***
;entry:  _delay_ms	;Function start
; 2 exit points
;has an exit
;3 compiler assigned registers:
;   r0x1000
;   r0x1001
;   r0x1002
;; Starting pCode block
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2283:genFunction *{*
;; ***	genFunction  2285 curr label offset=0previous max_key=0 
_delay_ms	;Function start
; 2 exit points
;; gen.c:2261:resultRemat *{*
;; gen.c:6739:genReceive *{*
;; ***	genReceive  6740
;;	721 register type nRegs=1
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x1048, size=1, right -=-, size=0
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1048 
	.line	15; "delay.c"	void delay_ms (unsigned char cnt) {
	BANKSEL	r0x1000
	MOVWF	r0x1000
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;;	721 register type nRegs=1
;;	721 register type nRegs=1
;; 	line = 6342 result AOP_REG=r0x1048, size=1, left -=-, size=0, right AOP_REG=r0x1048, size=1
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;;	721 register type nRegs=1
;; 	line = 6342 result AOP_REG=r0x1049, size=1, left -=-, size=0, right AOP_LIT=0x04, size=1
;; ***	genAssign  6434
; >>> gen.c:6439:genAssign
_00118_DS_
	.line	19; "delay.c"	do { delay_us(250); } while(--i);
	MOVLW	0x04
; >>> gen.c:6441:genAssign
;;	1109 rIdx = r0x1049 
	BANKSEL	r0x1001
	MOVWF	r0x1001
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;;	721 register type nRegs=1
;; 	line = 6342 result AOP_REG=r0x104A, size=1, left -=-, size=0, right AOP_LIT=0x53, size=1
;; ***	genAssign  6434
; >>> gen.c:6439:genAssign
_00116_DS_
	MOVLW	0x53
; >>> gen.c:6441:genAssign
;;	1109 rIdx = r0x104A 
	BANKSEL	r0x1002
	MOVWF	r0x1002
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:6695:genDjnz *{*
;; ***	genDjnz  6696
;;	721 register type nRegs=1
; >>> gen.c:6726:genDjnz
;;	1109 rIdx = r0x104A 
_00105_DS_
	BANKSEL	r0x1002
	DECFSZ	r0x1002,F
; >>> gen.c:6727:genDjnz
;; ***	popGetLabel  key=1, label offset 4
	GOTO	_00105_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:6695:genDjnz *{*
;; ***	genDjnz  6696
;;	721 register type nRegs=1
; >>> gen.c:6726:genDjnz
;;	1109 rIdx = r0x1049 
	DECFSZ	r0x1001,F
; >>> gen.c:6727:genDjnz
;; ***	popGetLabel  key=12, label offset 4
	GOTO	_00116_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:6695:genDjnz *{*
;; ***	genDjnz  6696
;;	721 register type nRegs=1
; >>> gen.c:6726:genDjnz
;;	1109 rIdx = r0x1048 
	.line	21; "delay.c"	while (--cnt);
	DECFSZ	r0x1000,F
; >>> gen.c:6727:genDjnz
;; ***	popGetLabel  key=14, label offset 4
	GOTO	_00118_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2435:genEndFunction *{*
;; ***	genEndFunction  2437
	RETURN	
; exit point of _delay_ms
;; gen.c:6803:genpic14Code *{*


;	code size estimation:
;	   22+    7 =    29 instructions (   72 byte)

	end
