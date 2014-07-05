;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 2.9.0 #5416 (Jul 24 2010) (UNIX)
; This file was generated Sun Aug  8 12:38:45 2010
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
	.file	"Sender.c"
	list	p=16f88
	radix dec
	include "p16f88.inc"
;--------------------------------------------------------
; config word 
;--------------------------------------------------------
	__config _CONFIG1, 0x3f10
	__config _CONFIG2, 0x3fff
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
	extern	_ADCON0_bits
	extern	_ADCON1_bits
	extern	_CCP1CON_bits
	extern	_CMCON_bits
	extern	_CVRCON_bits
	extern	_EECON1_bits
	extern	_INTCON_bits
	extern	_OPTION_REG_bits
	extern	_OSCCON_bits
	extern	_OSCTUNE_bits
	extern	_PCON_bits
	extern	_PIE1_bits
	extern	_PIE2_bits
	extern	_PIR1_bits
	extern	_PIR2_bits
	extern	_PORTA_bits
	extern	_PORTB_bits
	extern	_RCSTA_bits
	extern	_SSPCON_bits
	extern	_SSPSTAT_bits
	extern	_STATUS_bits
	extern	_T1CON_bits
	extern	_T2CON_bits
	extern	_TRISA_bits
	extern	_TRISB_bits
	extern	_TXSTA_bits
	extern	_WDTCON_bits
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
	extern	_PIR2
	extern	_TMR1L
	extern	_TMR1H
	extern	_T1CON
	extern	_TMR2
	extern	_T2CON
	extern	_SSPBUF
	extern	_SSPCON
	extern	_CCPR1L
	extern	_CCPR1H
	extern	_CCP1CON
	extern	_RCSTA
	extern	_TXREG
	extern	_RCREG
	extern	_ADRESH
	extern	_ADCON0
	extern	_OPTION_REG
	extern	_TRISA
	extern	_TRISB
	extern	_PIE1
	extern	_PIE2
	extern	_PCON
	extern	_OSCCON
	extern	_OSCTUNE
	extern	_PR2
	extern	_SSPADD
	extern	_SSPSTAT
	extern	_TXSTA
	extern	_SPBRG
	extern	_ANSEL
	extern	_CMCON
	extern	_CVRCON
	extern	_ADRESL
	extern	_ADCON1
	extern	_WDTCON
	extern	_EEDATA
	extern	_EEADR
	extern	_EEDATH
	extern	_EEADRH
	extern	_EECON1
	extern	_EECON2
	extern	___sdcc_saved_fsr
	extern	__sdcc_gsinit_startup
;--------------------------------------------------------
; global declarations
;--------------------------------------------------------
	global	_isr
	global	_main
	global	_cnt_tout
	global	_err_tout

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
UD_Sender_0	udata
_cnt_tout	res	2

UD_Sender_1	udata
_err_tout	res	2

;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
;--------------------------------------------------------
; compiler-defined variables
;--------------------------------------------------------
UDL_Sender_0	udata
r0x1002	res	1
r0x1001	res	1
r0x1003	res	1
;--------------------------------------------------------
; initialized data
;--------------------------------------------------------

ID_Sender_0	code
__str_0
	retlw 0x4b ; 'K'
	retlw 0x61 ; 'a'
	retlw 0x69 ; 'i'
	retlw 0x6c ; 'l'
	retlw 0x61 ; 'a'
	retlw 0x00 ; '.'
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
	.line	50; "Sender.c"	INTF = 0;     // clear PB0 interrupt so it can happen again
	BANKSEL	_INTCON_bits
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
code_Sender	code
;***
;  pBlock Stats: dbName = M
;***
;entry:  _main	;Function start
; 2 exit points
;has an exit
;functions called:
;   _rfm12_init
;   _delay_ms
;   _rfm12_snd_msg
;   _delay_ms
;   _rfm12_init
;   _delay_ms
;   _rfm12_snd_msg
;   _delay_ms
;7 compiler assigned registers:
;   r0x1001
;   r0x1002
;   r0x1003
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
	BANKSEL	_OSCCON
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
	BANKSEL	_PORTB
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
	BANKSEL	r0x1001
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


;	code size estimation:
;	   50+   14 =    64 instructions (  156 byte)

	end
