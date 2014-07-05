pcode dump


	New pBlock

internal pblock, dbName =M
;; Starting pCode block
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2283:genFunction *{*
;; ***	genFunction  2285 curr label offset=4previous max_key=0 
_main	;Function start
; 2 exit points
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;; ***	aopForSym 350
;;	361 sym->rname = _OSCCON, size = 1
;; 	line = 6342 result AOP_DIR=_OSCCON, size=1, left -=-, size=0, right AOP_LIT=0x60, size=1
;; ***	genAssign  6434
; >>> gen.c:6439:genAssign
	.line	65; "Sender.c"	OSCCON=0x60;      // internal RC set to 4MHz
	MOVLW	0x60
; >>> gen.c:6441:genAssign
;;	1013
;;	1029  _OSCCON   offset=0
	MOVWF	_OSCCON
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;; ***	aopForSym 350
;;	361 sym->rname = _CMCON, size = 1
;; 	line = 6342 result AOP_DIR=_CMCON, size=1, left -=-, size=0, right AOP_LIT=0x07, size=1
;; ***	genAssign  6434
; >>> gen.c:6439:genAssign
	.line	66; "Sender.c"	CMCON=0x07;       // comparators off, enable I/O ports
	MOVLW	0x07
; >>> gen.c:6441:genAssign
;;	1013
;;	1029  _CMCON   offset=0
	MOVWF	_CMCON
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;; ***	aopForSym 350
;;	361 sym->rname = _TRISB, size = 1
;; 	line = 6342 result AOP_DIR=_TRISB, size=1, left -=-, size=0, right AOP_LIT=0x00, size=1
;; ***	genAssign  6434
; >>> gen.c:6443:genAssign
;;	1013
;;	1029  _TRISB   offset=0
	.line	73; "Sender.c"	TRISB=0x00;     // all out
	CLRF	_TRISB
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;; ***	aopForSym 350
;;	361 sym->rname = _PORTB, size = 1
;; 	line = 6342 result AOP_DIR=_PORTB, size=1, left -=-, size=0, right AOP_LIT=0x00, size=1
;; ***	genAssign  6434
; >>> gen.c:6443:genAssign
;;	1013
;;	1029  _PORTB   offset=0
	.line	74; "Sender.c"	PORTB=0x00;
	CLRF	_PORTB
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
; >>> gen.c:2116:genCall
	.line	83; "Sender.c"	rfm12_init();
	PAGESEL	_rfm12_init
; >>> gen.c:2118:genCall
	CALL	_rfm12_init
; >>> gen.c:2123:genCall
	PAGESEL	$
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
;; 	2079 left AOP_LIT
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	.line	84; "Sender.c"	delay_ms(500);
	MOVLW	0xf4
; >>> gen.c:2116:genCall
	PAGESEL	_delay_ms
; >>> gen.c:2118:genCall
	CALL	_delay_ms
; >>> gen.c:2123:genCall
	PAGESEL	$
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6521:genCast *{*
;; ***	genCast  6522
;;	641
;;	aopForRemat 425
;;	446: rname __str_0, val 0, const = 0
;;	721 register type nRegs=3
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	__str_0
;; 	line = 6530 result AOP_REG=r0x1049, size=3, left -=-, size=0, right AOP_PCODE=__str_0, size=2
;; ***	genCast  6563
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
_00110_DS_
	.line	87; "Sender.c"	rfm12_snd_msg("Kaila",5);
	MOVLW	high (__str_0 + 0)
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x104A 
	MOVWF	r0x1001
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	(__str_0 + 0)
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1049 
	MOVWF	r0x1002
; >>> gen.c:6620:genCast
	MOVLW	0x80
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x104B 
	MOVWF	r0x1003
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
;;	721 register type nRegs=3
;; 	2079 left AOP_LIT
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0x05
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7c
	MOVWF	STK03
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0x00
;;	721 register type nRegs=3
;; 	2079 left AOP_REG
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7d
	MOVWF	STK02
;; gen.c:1324:mov2w_op *{*
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1049 
	MOVF	r0x1002,W
;; 	2079 left AOP_REG
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7e
	MOVWF	STK01
;; gen.c:1324:mov2w_op *{*
;; ***	mov2w  1356  offset=1
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x104A 
	MOVF	r0x1001,W
;; 	2079 left AOP_REG
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
;; ***	mov2w  1356  offset=2
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x104B 
	MOVF	r0x1003,W
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_snd_msg
; >>> gen.c:2118:genCall
	CALL	_rfm12_snd_msg
; >>> gen.c:2123:genCall
	PAGESEL	$
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
;; 	2079 left AOP_LIT
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	.line	88; "Sender.c"	delay_ms(10);
	MOVLW	0x0a
; >>> gen.c:2116:genCall
	PAGESEL	_delay_ms
; >>> gen.c:2118:genCall
	CALL	_delay_ms
; >>> gen.c:2123:genCall
	PAGESEL	$
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:2614:genGoto *{*
; >>> gen.c:2616:genGoto
;; ***	popGetLabel  key=2, label offset 8
	GOTO	_00110_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2435:genEndFunction *{*
;; ***	genEndFunction  2437
	RETURN	
; exit point of _main

	New pBlock

internal pblock, dbName =I
;; Starting pCode block
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2283:genFunction *{*
;; ***	genFunction  2285 curr label offset=0previous max_key=0 
_isr	;Function start
; 0 exit points
; >>> gen.c:2340:genFunction
	.line	47; "Sender.c"	void isr() interrupt 0 {                                                        
	MOVWF	WSAVE
; >>> gen.c:2341:genFunction
	SWAPF	STATUS,W
; >>> gen.c:2346:genFunction
	CLRF	STATUS
; >>> gen.c:2347:genFunction
	MOVWF	SSAVE
; >>> gen.c:2349:genFunction
	MOVF	PCLATH,W
; >>> gen.c:2351:genFunction
	CLRF	PCLATH
; >>> gen.c:2352:genFunction
	MOVWF	PSAVE
; >>> gen.c:2354:genFunction
	MOVF	FSR,W
; >>> gen.c:2355:genFunction
	MOVWF	___sdcc_saved_fsr
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _INTCON_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_INTCON_bits
;; 	line = 5965 result AOP_PCODE=_INTCON_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_INTCON_bits
; >>> gen.c:5720:genPackBits
	.line	50; "Sender.c"	INTF = 0;     // clear PB0 interrupt so it can happen again
	BCF	_INTCON_bits,1
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:3981:genOr *{*
;; ***	genOr  3982
;; ***	aopForSym 350
;;	361 sym->rname = _PORTB, size = 1
;;	606
;; 	line = 3988 result AOP_DIR=_PORTB, size=1, left AOP_DIR=_PORTB, size=1, right AOP_LIT=0x40, size=1
;; 	line = 4013 result AOP_DIR=_PORTB, size=1, left AOP_DIR=_PORTB, size=1, right AOP_LIT=0x40, size=1
; >>> gen.c:4145:genOr
	.line	52; "Sender.c"	SET_BIT(PORTB,6);
	BSF	_PORTB,6
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2435:genEndFunction *{*
;; ***	genEndFunction  2437
; >>> gen.c:2508:genEndFunction
	MOVF	___sdcc_saved_fsr,W
; >>> gen.c:2509:genEndFunction
	MOVWF	FSR
; >>> gen.c:2511:genEndFunction
	MOVF	PSAVE,W
; >>> gen.c:2512:genEndFunction
	MOVWF	PCLATH
; >>> gen.c:2513:genEndFunction
	CLRF	STATUS
; >>> gen.c:2515:genEndFunction
	SWAPF	SSAVE,W
; >>> gen.c:2516:genEndFunction
	MOVWF	STATUS
; >>> gen.c:2517:genEndFunction
	SWAPF	WSAVE,F
; >>> gen.c:2518:genEndFunction
	SWAPF	WSAVE,W
END_OF_INTERRUPT
	RETFIE	
;; gen.c:6803:genpic14Code *{*
