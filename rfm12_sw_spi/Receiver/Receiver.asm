;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 2.9.0 #5416 (Jul 24 2010) (UNIX)
; This file was generated Sun Aug  8 12:38:54 2010
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
	.file	"Receiver.c"
	list	p=16f628a
	radix dec
	include "p16f628a.inc"
;--------------------------------------------------------
; config word 
;--------------------------------------------------------
	__config 0x3f50
;--------------------------------------------------------
; external declarations
;--------------------------------------------------------
	extern	_delay_ms
	extern	_delay_s
	extern	_rfm12_init
	extern	_rfm12_ena_rx
	extern	_rfm12_dis_rx
	extern	_rfm12_snd_msg
	extern	_rfm12_rcv_msg
	extern	_CCP1CON_bits
	extern	_CMCON_bits
	extern	_EECON1_bits
	extern	_INTCON_bits
	extern	_OPTION_REG_bits
	extern	_PCON_bits
	extern	_PIE1_bits
	extern	_PIR1_bits
	extern	_PORTA_bits
	extern	_PORTB_bits
	extern	_RCSTA_bits
	extern	_STATUS_bits
	extern	_T1CON_bits
	extern	_T2CON_bits
	extern	_TRISA_bits
	extern	_TRISB_bits
	extern	_TXSTA_bits
	extern	_VRCON_bits
	extern	_INDF
	extern	_TMR0
	extern	_PCL
	extern	_STATUS
	extern	_FSR
	extern	_PORTA
	extern	_PORTB
	extern	_PCLATH
	extern	_INTCON
	extern	_PIR1
	extern	_TMR1L
	extern	_TMR1H
	extern	_T1CON
	extern	_TMR2
	extern	_T2CON
	extern	_CCPR1L
	extern	_CCPR1H
	extern	_CCP1CON
	extern	_RCSTA
	extern	_TXREG
	extern	_RCREG
	extern	_CMCON
	extern	_OPTION_REG
	extern	_TRISA
	extern	_TRISB
	extern	_PIE1
	extern	_PCON
	extern	_PR2
	extern	_TXSTA
	extern	_SPBRG
	extern	_EEDATA
	extern	_EEADR
	extern	_EECON1
	extern	_EECON2
	extern	_VRCON
	extern	___sdcc_saved_fsr
	extern	__sdcc_gsinit_startup
;--------------------------------------------------------
; global declarations
;--------------------------------------------------------
	global	_isr
	global	_main
	global	_rxbuf

	global PSAVE
	global SSAVE
	global WSAVE
	global STK12
	global STK11
	global STK10
	global STK09
	global STK08
	global STK07
	global STK06
	global STK05
	global STK04
	global STK03
	global STK02
	global STK01
	global STK00

sharebank udata_ovr 0x0070
PSAVE	res 1
SSAVE	res 1
WSAVE	res 1
STK12	res 1
STK11	res 1
STK10	res 1
STK09	res 1
STK08	res 1
STK07	res 1
STK06	res 1
STK05	res 1
STK04	res 1
STK03	res 1
STK02	res 1
STK01	res 1
STK00	res 1

;--------------------------------------------------------
; global definitions
;--------------------------------------------------------
UD_Receiver_0	udata
_rxbuf	res	19

;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
;--------------------------------------------------------
; compiler-defined variables
;--------------------------------------------------------
UDL_Receiver_0	udata
r0x1015	res	1
r0x1014	res	1
;--------------------------------------------------------
; initialized data
;--------------------------------------------------------
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
;	udata_ovr
;--------------------------------------------------------
; reset vector 
;--------------------------------------------------------
STARTUP	code 0x0000
	nop
	pagesel __sdcc_gsinit_startup
	goto	__sdcc_gsinit_startup
;--------------------------------------------------------
; interrupt and initialization code
;--------------------------------------------------------
c_interrupt	code	0x4
__sdcc_interrupt
;***
;  pBlock Stats: dbName = I
;***
;entry:  _isr	;Function start
; 0 exit points
;functions called:
;   _rfm12_rcv_msg
;   _rfm12_rcv_msg
;7 compiler assigned registers:
;   r0x1014
;   r0x1015
;   r0x1016
;   STK03
;   STK02
;   STK01
;   STK00
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
	.line	55; "Receiver.c"	void isr() interrupt 0 {                                                        
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
	BANKSEL	___sdcc_saved_fsr
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
	.line	58; "Receiver.c"	INTF = 0;     // clear PB0 interrupt so it can happen again
	BANKSEL	_INTCON_bits
	BCF	_INTCON_bits,1
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 5965 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:5720:genPackBits
	.line	59; "Receiver.c"	RB6=1;
	BSF	_PORTB_bits,6
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6521:genCast *{*
;; ***	genCast  6522
;;	641
;;	aopForRemat 425
;;	446: rname _rxbuf, val 0, const = 0
;;	721 register type nRegs=3
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_rxbuf
;; 	line = 6530 result AOP_REG=r0x1048, size=3, left -=-, size=0, right AOP_PCODE=_rxbuf, size=2
;; ***	genCast  6563
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	.line	60; "Receiver.c"	rfm12_rcv_msg(rxbuf,5);
	MOVLW	high (_rxbuf + 0)
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1049 
	BANKSEL	r0x1014
	MOVWF	r0x1014
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	(_rxbuf + 0)
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1048 
	MOVWF	r0x1015
; >>> gen.c:6618:genCast
;;	1109 rIdx = r0x104A 
;;1	CLRF	r0x1016
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
;;	1109 rIdx = r0x1048 
	MOVF	r0x1015,W
;; 	2079 left AOP_REG
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7e
	MOVWF	STK01
;; gen.c:1324:mov2w_op *{*
;; ***	mov2w  1356  offset=1
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1049 
	MOVF	r0x1014,W
;; 	2079 left AOP_REG
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
;; ***	mov2w  1356  offset=2
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x104A 
	MOVLW	0x00
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_rcv_msg
; >>> gen.c:2118:genCall
	CALL	_rfm12_rcv_msg
; >>> gen.c:2123:genCall
	PAGESEL	$
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2435:genEndFunction *{*
;; ***	genEndFunction  2437
;; gen.c:1975:unsaverbank *{*
;; ***	unsaverbank  1977 - WARNING no code generated
; >>> gen.c:2508:genEndFunction
	BANKSEL	___sdcc_saved_fsr
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

;--------------------------------------------------------
; code
;--------------------------------------------------------
code_Receiver	code
;***
;  pBlock Stats: dbName = M
;***
;entry:  _main	;Function start
; 2 exit points
;has an exit
;functions called:
;   _rfm12_init
;   _rfm12_ena_rx
;   _delay_ms
;   _delay_ms
;   _rfm12_init
;   _rfm12_ena_rx
;   _delay_ms
;   _delay_ms
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
;;	361 sym->rname = _CMCON, size = 1
;; 	line = 6342 result AOP_DIR=_CMCON, size=1, left -=-, size=0, right AOP_LIT=0x07, size=1
;; ***	genAssign  6434
; >>> gen.c:6439:genAssign
	.line	79; "Receiver.c"	CMCON=0x07;       // comparators off, enable I/O ports
	MOVLW	0x07
; >>> gen.c:6441:genAssign
;;	1013
;;	1029  _CMCON   offset=0
	BANKSEL	_CMCON
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
	.line	83; "Receiver.c"	TRISB=0x00;     // all out
	BANKSEL	_TRISB
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
	.line	84; "Receiver.c"	PORTB=0x00;
	BANKSEL	_PORTB
	CLRF	_PORTB
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;; ***	aopForSym 350
;;	361 sym->rname = _INTCON, size = 1
;; 	line = 6342 result AOP_DIR=_INTCON, size=1, left -=-, size=0, right AOP_LIT=0x00, size=1
;; ***	genAssign  6434
; >>> gen.c:6443:genAssign
;;	1013
;;	1027  _INTCON   offset=0 - had to alloc by reg name
	.line	86; "Receiver.c"	INTCON=0;       // clear interupt register complitelly
	CLRF	_INTCON
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
;; 	line = 5965 result AOP_PCODE=_INTCON_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_INTCON_bits
; >>> gen.c:5720:genPackBits
	.line	87; "Receiver.c"	INTE=1;         // set only PORTB/PB0 interrupt
	BSF	_INTCON_bits,4
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _OPTION_REG_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_OPTION_REG_bits
;; 	line = 5965 result AOP_PCODE=_OPTION_REG_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_OPTION_REG_bits
; >>> gen.c:5720:genPackBits
	.line	88; "Receiver.c"	INTEDG=0;       // interrupt on falling edge
	BANKSEL	_OPTION_REG_bits
	BCF	_OPTION_REG_bits,6
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
;; 	line = 5965 result AOP_PCODE=_INTCON_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_INTCON_bits
; >>> gen.c:5720:genPackBits
	.line	89; "Receiver.c"	GIE=1;          // globally enable interrupts
	BANKSEL	_INTCON_bits
	BSF	_INTCON_bits,7
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
; >>> gen.c:2116:genCall
	.line	92; "Receiver.c"	rfm12_init();
	PAGESEL	_rfm12_init
; >>> gen.c:2118:genCall
	CALL	_rfm12_init
; >>> gen.c:2123:genCall
	PAGESEL	$
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
; >>> gen.c:2116:genCall
	.line	93; "Receiver.c"	rfm12_ena_rx();
	PAGESEL	_rfm12_ena_rx
; >>> gen.c:2118:genCall
	CALL	_rfm12_ena_rx
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
	.line	95; "Receiver.c"	delay_ms(200);
	MOVLW	0xc8
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
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
;; 	2079 left AOP_LIT
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
_00110_DS_
	.line	102; "Receiver.c"	delay_ms(1);
	MOVLW	0x01
; >>> gen.c:2116:genCall
	PAGESEL	_delay_ms
; >>> gen.c:2118:genCall
	CALL	_delay_ms
; >>> gen.c:2123:genCall
	PAGESEL	$
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 5965 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:5720:genPackBits
	.line	103; "Receiver.c"	RB6=0;
	BANKSEL	_PORTB_bits
	BCF	_PORTB_bits,6
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


;	code size estimation:
;	   52+   20 =    72 instructions (  184 byte)

	end
