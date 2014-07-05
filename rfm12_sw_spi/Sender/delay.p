pcode dump


	New pBlock

code, dbName =C
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

	New pBlock

code, dbName =C
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
