;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 2.9.0 #5416 (Jul 24 2010) (UNIX)
; This file was generated Sun Aug  8 12:38:54 2010
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
	.file	"eeprom.c"
	list	p=16f628a
	radix dec
	include "p16f628a.inc"
;--------------------------------------------------------
; external declarations
;--------------------------------------------------------
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
	extern	__gptrget1
	extern	__gptrput1

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
	global	_eeprom_read
	global	_eeprom_write

;--------------------------------------------------------
; global definitions
;--------------------------------------------------------
;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
;--------------------------------------------------------
; compiler-defined variables
;--------------------------------------------------------
UDL_eeprom_0	udata
r0x100F	res	1
r0x100E	res	1
r0x1012	res	1
r0x1011	res	1
r0x1010	res	1
r0x1014	res	1
r0x1013	res	1
r0x1015	res	1
r0x1016	res	1
r0x1017	res	1
r0x1018	res	1
r0x1019	res	1
r0x1001	res	1
r0x1000	res	1
r0x1004	res	1
r0x1003	res	1
r0x1002	res	1
r0x1006	res	1
r0x1005	res	1
r0x1007	res	1
r0x1008	res	1
r0x1009	res	1
r0x100A	res	1
r0x100B	res	1
r0x100C	res	1
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
code_eeprom	code
;***
;  pBlock Stats: dbName = C
;***
;entry:  _eeprom_read	;Function start
; 2 exit points
;has an exit
;functions called:
;   __gptrput1
;   __gptrput1
;20 compiler assigned registers:
;   r0x1000
;   STK00
;   r0x1001
;   STK01
;   r0x1002
;   STK02
;   r0x1003
;   STK03
;   r0x1004
;   STK04
;   r0x1005
;   STK05
;   r0x1006
;   r0x1007
;   r0x1008
;   r0x1009
;   r0x100A
;   r0x100B
;   r0x100C
;   r0x100D
;; Starting pCode block
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2283:genFunction *{*
;; ***	genFunction  2285 curr label offset=4previous max_key=18 
_eeprom_read	;Function start
; 2 exit points
;; gen.c:2261:resultRemat *{*
;; gen.c:6739:genReceive *{*
;; ***	genReceive  6740
;;	721 register type nRegs=2
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x1054, size=2, right -=-, size=0
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1055 
	.line	45; "eeprom.c"	void eeprom_read(int pos,char *str,int len){
	BANKSEL	r0x1000
	MOVWF	r0x1000
; >>> gen.c:1393:get_returnvalue
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVF	STK00,W
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1054 
	MOVWF	r0x1001
;; gen.c:2261:resultRemat *{*
;; gen.c:6739:genReceive *{*
;; ***	genReceive  6740
;;	721 register type nRegs=3
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x1056, size=3, right -=-, size=0
; >>> gen.c:1393:get_returnvalue
;; ***	popRegFromIdx,1043  , rIdx=0x7e
	MOVF	STK01,W
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1058 
	MOVWF	r0x1002
; >>> gen.c:1393:get_returnvalue
;; ***	popRegFromIdx,1043  , rIdx=0x7d
	MOVF	STK02,W
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1057 
	MOVWF	r0x1003
; >>> gen.c:1393:get_returnvalue
;; ***	popRegFromIdx,1043  , rIdx=0x7c
	MOVF	STK03,W
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1056 
	MOVWF	r0x1004
;; gen.c:2261:resultRemat *{*
;; gen.c:6739:genReceive *{*
;; ***	genReceive  6740
;;	721 register type nRegs=2
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x1059, size=2, right -=-, size=0
; >>> gen.c:1393:get_returnvalue
;; ***	popRegFromIdx,1043  , rIdx=0x7b
	MOVF	STK04,W
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x105A 
	MOVWF	r0x1005
; >>> gen.c:1393:get_returnvalue
;; ***	popRegFromIdx,1043  , rIdx=0x7a
	MOVF	STK05,W
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1059 
	MOVWF	r0x1006
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;;	721 register type nRegs=2
;;	721 register type nRegs=2
;; 	line = 6342 result AOP_REG=r0x1054, size=2, left -=-, size=0, right AOP_REG=r0x1054, size=2
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;;	721 register type nRegs=2
;; 	line = 6342 result AOP_REG=r0x105B, size=2, left -=-, size=0, right AOP_LIT=0x00, size=2
;; ***	genAssign  6434
; >>> gen.c:6443:genAssign
;;	1109 rIdx = r0x105B 
	.line	48; "eeprom.c"	for(i=0;i<len;i++){             // each char in str
	CLRF	r0x1007
;; ***	genAssign  6434
; >>> gen.c:6443:genAssign
;;	1109 rIdx = r0x105C 
	CLRF	r0x1008
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:3357:genCmpLt *{*
;; ***	genCmpLt  3358
;;	721 register type nRegs=2
;;	721 register type nRegs=2
;; gen.c:3126:genCmp *{*
;; ***	mov2w  1356  offset=1
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x105C 
_00127_DS_
	BANKSEL	r0x1008
	MOVF	r0x1008,W
; >>> gen.c:3256:genCmp
	ADDLW	0x80
; >>> gen.c:3257:genCmp
	MOVWF	r0x1009
;; ***	mov2w  1356  offset=1
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x105A 
	MOVF	r0x1005,W
; >>> gen.c:3259:genCmp
	ADDLW	0x80
; >>> gen.c:3260:genCmp
	SUBWF	r0x1009,W
; >>> gen.c:3270:genCmp
	BTFSS	STATUS,2
; >>> gen.c:3271:genCmp
;; ***	popGetLabel  key=10, label offset 26
	GOTO	_00136_DS_
; >>> gen.c:3101:pic14_mov2w_regOrLit
;;	1109 rIdx = r0x1059 
	MOVF	r0x1006,W
; >>> gen.c:3273:genCmp
;;	1109 rIdx = r0x105B 
	SUBWF	r0x1007,W
;; gen.c:3073:genSkipc *{*
; >>> gen.c:3078:genSkipc
_00136_DS_
	BTFSC	STATUS,0
; >>> gen.c:3082:genSkipc
;; ***	popGetLabel  key=5, label offset 26
	GOTO	_00131_DS_
;genSkipc:3083: created from rifx:0xbfde11e0
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; ***	genPlus  547
;; genarith.c:548:genPlus *{*
;;	721 register type nRegs=3
;;	721 register type nRegs=2
;;	721 register type nRegs=3
;; 	line = 554 result AOP_REG=r0x105D, size=3, left AOP_REG=r0x1056, size=3, right AOP_REG=r0x105B, size=2
;; ***	pic14_getDataSize  1426
;; ***	pic14_getDataSize  1446
;; genarith.c:142:genPlusIncr *{*
;; ***	genPlusIncr  144
;; 	result AOP_REG, left AOP_REG, right AOP_REG
;; ***	pic14_getDataSize  1426
;; ***	pic14_getDataSize  1446
;; ***	genPlus  653
; >>> genarith.c:662:genPlus
;;	1109 rIdx = r0x105B 
	.line	49; "eeprom.c"	str[i]=EEPROM_READ(pos++);    // fill str with EEPROM data at position pos
	BANKSEL	r0x1007
	MOVF	r0x1007,W
; >>> genarith.c:671:genPlus
;;	1109 rIdx = r0x1056 
	ADDWF	r0x1004,W
; >>> genarith.c:672:genPlus
;;	1109 rIdx = r0x105D 
	MOVWF	r0x1009
; >>> genarith.c:707:genPlus
;;	1109 rIdx = r0x1057 
	MOVF	r0x1003,W
; >>> genarith.c:708:genPlus
;;	1109 rIdx = r0x105E 
	MOVWF	r0x100A
; >>> genarith.c:710:genPlus
;;	1109 rIdx = r0x105C 
	MOVF	r0x1008,W
; >>> genarith.c:711:genPlus
	BTFSC	STATUS,0
; >>> genarith.c:712:genPlus
;;	1109 rIdx = r0x105C 
	INCFSZ	r0x1008,W
; >>> genarith.c:713:genPlus
;;	1109 rIdx = r0x105E 
	ADDWF	r0x100A,F
; >>> genarith.c:735:genPlus
;;	1109 rIdx = r0x1058 
	MOVF	r0x1002,W
; >>> genarith.c:736:genPlus
	BTFSC	STATUS,0
; >>> genarith.c:737:genPlus
	ADDLW	0x01
; >>> genarith.c:738:genPlus
;;	1109 rIdx = r0x105F 
	MOVWF	r0x100B
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;;	721 register type nRegs=2
;;	721 register type nRegs=2
;; 	line = 6342 result AOP_REG=r0x1060, size=2, left -=-, size=0, right AOP_REG=r0x1054, size=2
;; ***	genAssign  6434
;; gen.c:1324:mov2w_op *{*
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1054 
	MOVF	r0x1001,W
; >>> gen.c:6453:genAssign
;;	1109 rIdx = r0x1060 
	MOVWF	r0x100C
;; ***	genAssign  6434
;; gen.c:1324:mov2w_op *{*
;; ***	mov2w  1356  offset=1
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1055 
	MOVF	r0x1000,W
; >>> gen.c:6453:genAssign
;;	1109 rIdx = r0x1061 
;;1	MOVWF	r0x100D
;; gen.c:2261:resultRemat *{*
;; ***	genPlus  547
;; genarith.c:548:genPlus *{*
;;	721 register type nRegs=2
;;	606
;; 	line = 554 result AOP_REG=r0x1054, size=2, left AOP_REG=r0x1054, size=2, right AOP_LIT=0x01, size=1
;; ***	pic14_getDataSize  1426
;; genarith.c:142:genPlusIncr *{*
;; ***	genPlusIncr  144
;; 	result AOP_REG, left AOP_REG, right AOP_LIT
;; 	genPlusIncr  156
; >>> genarith.c:168:genPlusIncr
;;	1109 rIdx = r0x1054 
	INCF	r0x1001,F
; >>> genarith.c:172:genPlusIncr
	BTFSC	STATUS,2
; >>> genarith.c:173:genPlusIncr
;;	1109 rIdx = r0x1055 
	INCF	r0x1000,F
;; gen.c:2261:resultRemat *{*
;; gen.c:6521:genCast *{*
;; ***	genCast  6522
;;	721 register type nRegs=2
;; ***	aopForSym 350
;;	361 sym->rname = _EEADR, size = 1
;; 	line = 6530 result AOP_DIR=_EEADR, size=1, left -=-, size=0, right AOP_REG=r0x1060, size=2
;; ***	genCast  6636
; >>> gen.c:6656:genCast
;;	1109 rIdx = r0x1060 
	MOVF	r0x100C,W
; >>> gen.c:6657:genCast
;;	1013
;;	1029  _EEADR   offset=0
	BANKSEL	_EEADR
	MOVWF	_EEADR
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _EECON1_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_EECON1_bits
;; 	line = 5965 result AOP_PCODE=_EECON1_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_EECON1_bits
; >>> gen.c:5720:genPackBits
	BSF	_EECON1_bits,0
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:6050:genGenPointerSet *{*
;; ***	genGenPointerSet  6051
;; ***	aopForSym 350
;;	361 sym->rname = _EEDATA, size = 1
;;	721 register type nRegs=3
;; 	line = 6056 result AOP_REG=r0x105D, size=3, left AOP_DIR=_EEDATA, size=1, right -=-, size=0
;; gen.c:1324:mov2w_op *{*
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1013
;;	1029  _EEDATA   offset=0
	MOVF	_EEDATA,W
; >>> gen.c:6090:genGenPointerSet
;; ***	popRegFromIdx,1043  , rIdx=0x7d
	MOVWF	STK02
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x105D 
	BANKSEL	r0x1009
	MOVF	r0x1009,W
; >>> gen.c:6097:genGenPointerSet
;; ***	popRegFromIdx,1043  , rIdx=0x7e
	MOVWF	STK01
;; ***	mov2w  1356  offset=1
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x105E 
	MOVF	r0x100A,W
; >>> gen.c:6099:genGenPointerSet
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; ***	mov2w  1356  offset=2
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x105F 
	MOVF	r0x100B,W
; >>> gen.c:1402:call_libraryfunc
	PAGESEL	__gptrput1
; >>> gen.c:1404:call_libraryfunc
	CALL	__gptrput1
; >>> gen.c:1406:call_libraryfunc
	PAGESEL	$
;; gen.c:2261:resultRemat *{*
;; ***	genPlus  547
;; genarith.c:548:genPlus *{*
;;	721 register type nRegs=2
;;	606
;; 	line = 554 result AOP_REG=r0x105B, size=2, left AOP_REG=r0x105B, size=2, right AOP_LIT=0x01, size=1
;; ***	pic14_getDataSize  1426
;; genarith.c:142:genPlusIncr *{*
;; ***	genPlusIncr  144
;; 	result AOP_REG, left AOP_REG, right AOP_LIT
;; 	genPlusIncr  156
; >>> genarith.c:168:genPlusIncr
;;	1109 rIdx = r0x105B 
	.line	48; "eeprom.c"	for(i=0;i<len;i++){             // each char in str
	BANKSEL	r0x1007
	INCF	r0x1007,F
; >>> genarith.c:172:genPlusIncr
	BTFSC	STATUS,2
; >>> genarith.c:173:genPlusIncr
;;	1109 rIdx = r0x105C 
	INCF	r0x1008,F
;; gen.c:2261:resultRemat *{*
;; gen.c:2614:genGoto *{*
; >>> gen.c:2616:genGoto
;; ***	popGetLabel  key=1, label offset 26
	GOTO	_00127_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2435:genEndFunction *{*
;; ***	genEndFunction  2437
_00131_DS_
	RETURN	
; exit point of _eeprom_read

;***
;  pBlock Stats: dbName = C
;***
;entry:  _eeprom_write	;Function start
; 2 exit points
;has an exit
;functions called:
;   __gptrget1
;   __gptrget1
;18 compiler assigned registers:
;   r0x100E
;   STK00
;   r0x100F
;   STK01
;   r0x1010
;   STK02
;   r0x1011
;   STK03
;   r0x1012
;   STK04
;   r0x1013
;   STK05
;   r0x1014
;   r0x1015
;   r0x1016
;   r0x1017
;   r0x1018
;   r0x1019
;; Starting pCode block
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2283:genFunction *{*
;; ***	genFunction  2285 curr label offset=0previous max_key=0 
_eeprom_write	;Function start
; 2 exit points
;; gen.c:2261:resultRemat *{*
;; gen.c:6739:genReceive *{*
;; ***	genReceive  6740
;;	721 register type nRegs=2
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x1048, size=2, right -=-, size=0
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1049 
	.line	24; "eeprom.c"	void eeprom_write(int pos,char *str,int len){
	BANKSEL	r0x100E
	MOVWF	r0x100E
; >>> gen.c:1393:get_returnvalue
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVF	STK00,W
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1048 
	MOVWF	r0x100F
;; gen.c:2261:resultRemat *{*
;; gen.c:6739:genReceive *{*
;; ***	genReceive  6740
;;	721 register type nRegs=3
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x104A, size=3, right -=-, size=0
; >>> gen.c:1393:get_returnvalue
;; ***	popRegFromIdx,1043  , rIdx=0x7e
	MOVF	STK01,W
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x104C 
	MOVWF	r0x1010
; >>> gen.c:1393:get_returnvalue
;; ***	popRegFromIdx,1043  , rIdx=0x7d
	MOVF	STK02,W
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x104B 
	MOVWF	r0x1011
; >>> gen.c:1393:get_returnvalue
;; ***	popRegFromIdx,1043  , rIdx=0x7c
	MOVF	STK03,W
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x104A 
	MOVWF	r0x1012
;; gen.c:2261:resultRemat *{*
;; gen.c:6739:genReceive *{*
;; ***	genReceive  6740
;;	721 register type nRegs=2
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x104D, size=2, right -=-, size=0
; >>> gen.c:1393:get_returnvalue
;; ***	popRegFromIdx,1043  , rIdx=0x7b
	MOVF	STK04,W
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x104E 
	MOVWF	r0x1013
; >>> gen.c:1393:get_returnvalue
;; ***	popRegFromIdx,1043  , rIdx=0x7a
	MOVF	STK05,W
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x104D 
	MOVWF	r0x1014
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;;	721 register type nRegs=2
;;	721 register type nRegs=2
;; 	line = 6342 result AOP_REG=r0x1048, size=2, left -=-, size=0, right AOP_REG=r0x1048, size=2
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;;	721 register type nRegs=2
;; 	line = 6342 result AOP_REG=r0x104F, size=2, left -=-, size=0, right AOP_LIT=0x00, size=2
;; ***	genAssign  6434
; >>> gen.c:6443:genAssign
;;	1109 rIdx = r0x104F 
	.line	27; "eeprom.c"	for(i=0;i<len;i++){     // each char in str
	CLRF	r0x1015
;; ***	genAssign  6434
; >>> gen.c:6443:genAssign
;;	1109 rIdx = r0x1050 
	CLRF	r0x1016
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:3357:genCmpLt *{*
;; ***	genCmpLt  3358
;;	721 register type nRegs=2
;;	721 register type nRegs=2
;; gen.c:3126:genCmp *{*
;; ***	mov2w  1356  offset=1
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1050 
_00111_DS_
	BANKSEL	r0x1016
	MOVF	r0x1016,W
; >>> gen.c:3256:genCmp
	ADDLW	0x80
; >>> gen.c:3257:genCmp
	MOVWF	r0x1017
;; ***	mov2w  1356  offset=1
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x104E 
	MOVF	r0x1013,W
; >>> gen.c:3259:genCmp
	ADDLW	0x80
; >>> gen.c:3260:genCmp
	SUBWF	r0x1017,W
; >>> gen.c:3270:genCmp
	BTFSS	STATUS,2
; >>> gen.c:3271:genCmp
;; ***	popGetLabel  key=18, label offset 4
	GOTO	_00122_DS_
; >>> gen.c:3101:pic14_mov2w_regOrLit
;;	1109 rIdx = r0x104D 
	MOVF	r0x1014,W
; >>> gen.c:3273:genCmp
;;	1109 rIdx = r0x104F 
	SUBWF	r0x1015,W
;; gen.c:3073:genSkipc *{*
; >>> gen.c:3078:genSkipc
_00122_DS_
	BTFSC	STATUS,0
; >>> gen.c:3082:genSkipc
;; ***	popGetLabel  key=11, label offset 4
	GOTO	_00115_DS_
;genSkipc:3083: created from rifx:0xbfde11e0
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;;	721 register type nRegs=2
;;	721 register type nRegs=2
;; 	line = 6342 result AOP_REG=r0x1051, size=2, left -=-, size=0, right AOP_REG=r0x1048, size=2
;; ***	genAssign  6434
;; gen.c:1324:mov2w_op *{*
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1048 
	.line	28; "eeprom.c"	EEADR=pos++;          // EEPROM position
	BANKSEL	r0x100F
	MOVF	r0x100F,W
; >>> gen.c:6453:genAssign
;;	1109 rIdx = r0x1051 
	MOVWF	r0x1017
;; ***	genAssign  6434
;; gen.c:1324:mov2w_op *{*
;; ***	mov2w  1356  offset=1
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1049 
	MOVF	r0x100E,W
; >>> gen.c:6453:genAssign
;;	1109 rIdx = r0x1052 
	MOVWF	r0x1018
;; gen.c:2261:resultRemat *{*
;; ***	genPlus  547
;; genarith.c:548:genPlus *{*
;;	721 register type nRegs=2
;;	606
;; 	line = 554 result AOP_REG=r0x1048, size=2, left AOP_REG=r0x1048, size=2, right AOP_LIT=0x01, size=1
;; ***	pic14_getDataSize  1426
;; genarith.c:142:genPlusIncr *{*
;; ***	genPlusIncr  144
;; 	result AOP_REG, left AOP_REG, right AOP_LIT
;; 	genPlusIncr  156
; >>> genarith.c:168:genPlusIncr
;;	1109 rIdx = r0x1048 
	INCF	r0x100F,F
; >>> genarith.c:172:genPlusIncr
	BTFSC	STATUS,2
; >>> genarith.c:173:genPlusIncr
;;	1109 rIdx = r0x1049 
	INCF	r0x100E,F
;; gen.c:2261:resultRemat *{*
;; gen.c:6521:genCast *{*
;; ***	genCast  6522
;;	721 register type nRegs=2
;; ***	aopForSym 350
;;	361 sym->rname = _EEADR, size = 1
;; 	line = 6530 result AOP_DIR=_EEADR, size=1, left -=-, size=0, right AOP_REG=r0x1051, size=2
;; ***	genCast  6636
; >>> gen.c:6656:genCast
;;	1109 rIdx = r0x1051 
	MOVF	r0x1017,W
; >>> gen.c:6657:genCast
;;	1013
;;	1029  _EEADR   offset=0
	BANKSEL	_EEADR
	MOVWF	_EEADR
;; gen.c:2261:resultRemat *{*
;; ***	genPlus  547
;; genarith.c:548:genPlus *{*
;;	721 register type nRegs=3
;;	721 register type nRegs=2
;;	721 register type nRegs=3
;; 	line = 554 result AOP_REG=r0x1051, size=3, left AOP_REG=r0x104A, size=3, right AOP_REG=r0x104F, size=2
;; ***	pic14_getDataSize  1426
;; ***	pic14_getDataSize  1446
;; genarith.c:142:genPlusIncr *{*
;; ***	genPlusIncr  144
;; 	result AOP_REG, left AOP_REG, right AOP_REG
;; ***	pic14_getDataSize  1426
;; ***	pic14_getDataSize  1446
;; ***	genPlus  653
; >>> genarith.c:662:genPlus
;;	1109 rIdx = r0x104F 
	.line	29; "eeprom.c"	EEDATA=str[i];        // set the data to write
	BANKSEL	r0x1015
	MOVF	r0x1015,W
; >>> genarith.c:671:genPlus
;;	1109 rIdx = r0x104A 
	ADDWF	r0x1012,W
; >>> genarith.c:672:genPlus
;;	1109 rIdx = r0x1051 
	MOVWF	r0x1017
; >>> genarith.c:707:genPlus
;;	1109 rIdx = r0x104B 
	MOVF	r0x1011,W
; >>> genarith.c:708:genPlus
;;	1109 rIdx = r0x1052 
	MOVWF	r0x1018
; >>> genarith.c:710:genPlus
;;	1109 rIdx = r0x1050 
	MOVF	r0x1016,W
; >>> genarith.c:711:genPlus
	BTFSC	STATUS,0
; >>> genarith.c:712:genPlus
;;	1109 rIdx = r0x1050 
	INCFSZ	r0x1016,W
; >>> genarith.c:713:genPlus
;;	1109 rIdx = r0x1052 
	ADDWF	r0x1018,F
; >>> genarith.c:735:genPlus
;;	1109 rIdx = r0x104C 
	MOVF	r0x1010,W
; >>> genarith.c:736:genPlus
	BTFSC	STATUS,0
; >>> genarith.c:737:genPlus
	ADDLW	0x01
; >>> genarith.c:738:genPlus
;;	1109 rIdx = r0x1053 
	MOVWF	r0x1019
;; gen.c:2261:resultRemat *{*
;; gen.c:5608:genPointerGet *{*
;; ***	genPointerGet  5609
;; gen.c:5496:genGenPointerGet *{*
;; ***	genGenPointerGet  5497
;;	721 register type nRegs=3
;; ***	aopForSym 350
;;	361 sym->rname = _EEDATA, size = 1
;; 	line = 5502 result AOP_DIR=_EEDATA, size=1, left AOP_REG=r0x1051, size=3, right -=-, size=0
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1051 
	MOVF	r0x1017,W
; >>> gen.c:5521:genGenPointerGet
;; ***	popRegFromIdx,1043  , rIdx=0x7e
	MOVWF	STK01
;; ***	mov2w  1356  offset=1
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1052 
	MOVF	r0x1018,W
; >>> gen.c:5523:genGenPointerGet
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; ***	mov2w  1356  offset=2
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1053 
	MOVF	r0x1019,W
; >>> gen.c:1402:call_libraryfunc
	PAGESEL	__gptrget1
; >>> gen.c:1404:call_libraryfunc
	CALL	__gptrget1
; >>> gen.c:1406:call_libraryfunc
	PAGESEL	$
; >>> gen.c:1367:movwf
;;	1013
;;	1029  _EEDATA   offset=0
	BANKSEL	_EEDATA
	MOVWF	_EEDATA
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _EECON1_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_EECON1_bits
;; 	line = 5965 result AOP_PCODE=_EECON1_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_EECON1_bits
; >>> gen.c:5720:genPackBits
	.line	30; "eeprom.c"	WREN=1;               // enable writes
	BSF	_EECON1_bits,2
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;; ***	aopForSym 350
;;	361 sym->rname = _EECON2, size = 1
;; 	line = 6342 result AOP_DIR=_EECON2, size=1, left -=-, size=0, right AOP_LIT=0x00, size=1
;; ***	genAssign  6434
; >>> gen.c:6443:genAssign
;;	1013
;;	1029  _EECON2   offset=0
	.line	31; "eeprom.c"	EEPROM_WRITE();       // write a byte
	CLRF	_EECON2
;; gen.c:2261:resultRemat *{*
;; gen.c:4425:genInline *{*
;; ***	genInline  4426
	MOVLW 0x55 
;; gen.c:2261:resultRemat *{*
;; gen.c:4425:genInline *{*
;; ***	genInline  4426
	MOVWF EECON2 
;; gen.c:2261:resultRemat *{*
;; gen.c:4425:genInline *{*
;; ***	genInline  4426
	MOVLW 0xaa 
;; gen.c:2261:resultRemat *{*
;; gen.c:4425:genInline *{*
;; ***	genInline  4426
	MOVWF EECON2 
;; gen.c:2261:resultRemat *{*
;; gen.c:4425:genInline *{*
;; ***	genInline  4426
	BSF EECON1,1; 
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:5608:genPointerGet *{*
;; ***	genPointerGet  5609
;; gen.c:5397:genNearPointerGet *{*
;; ***	genNearPointerGet  5398
;;	641
;;	aopForRemat 425
;;	446: rname _EECON1_bits, val 0, const = 0
;; ***	genNearPointerGet  5414
;;	721 register type nRegs=1
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:5240:genUnpackBits *{*
;; ***	genUnpackBits  5241
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_EECON1_bits
; >>> gen.c:5257:genUnpackBits
_00108_DS_
	.line	32; "eeprom.c"	while(WR);            // wait for write to finish
	BANKSEL	_EECON1_bits
	BTFSC	_EECON1_bits,1
; >>> gen.c:5258:genUnpackBits
;; ***	popGetLabel  key=4, label offset 4
	GOTO	_00108_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _EECON1_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_EECON1_bits
;; 	line = 5965 result AOP_PCODE=_EECON1_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_EECON1_bits
; >>> gen.c:5720:genPackBits
	.line	33; "eeprom.c"	WREN=0;               // disable writes
	BCF	_EECON1_bits,2
;; gen.c:2261:resultRemat *{*
;; ***	genPlus  547
;; genarith.c:548:genPlus *{*
;;	721 register type nRegs=2
;;	606
;; 	line = 554 result AOP_REG=r0x104F, size=2, left AOP_REG=r0x104F, size=2, right AOP_LIT=0x01, size=1
;; ***	pic14_getDataSize  1426
;; genarith.c:142:genPlusIncr *{*
;; ***	genPlusIncr  144
;; 	result AOP_REG, left AOP_REG, right AOP_LIT
;; 	genPlusIncr  156
; >>> genarith.c:168:genPlusIncr
;;	1109 rIdx = r0x104F 
	.line	27; "eeprom.c"	for(i=0;i<len;i++){     // each char in str
	BANKSEL	r0x1015
	INCF	r0x1015,F
; >>> genarith.c:172:genPlusIncr
	BTFSC	STATUS,2
; >>> genarith.c:173:genPlusIncr
;;	1109 rIdx = r0x1050 
	INCF	r0x1016,F
;; gen.c:2261:resultRemat *{*
;; gen.c:2614:genGoto *{*
; >>> gen.c:2616:genGoto
;; ***	popGetLabel  key=7, label offset 4
	GOTO	_00111_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2435:genEndFunction *{*
;; ***	genEndFunction  2437
_00115_DS_
	RETURN	
; exit point of _eeprom_write
;; gen.c:6803:genpic14Code *{*


;	code size estimation:
;	  128+   18 =   146 instructions (  328 byte)

	end
