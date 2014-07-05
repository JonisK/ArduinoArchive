pcode dump


	New pBlock

code, dbName =C
;; Starting pCode block
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2283:genFunction *{*
;; ***	genFunction  2285 curr label offset=91previous max_key=23 
_rfm12_spi16	;Function start
; 2 exit points
;; gen.c:2261:resultRemat *{*
;; gen.c:6739:genReceive *{*
;; ***	genReceive  6740
;;	721 register type nRegs=2
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x106A, size=2, right -=-, size=0
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x106B 
	.line	225; "rfm12.c"	unsigned int rfm12_spi16(unsigned int dout){
	MOVWF	r0x1000
; >>> gen.c:1393:get_returnvalue
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVF	STK00,W
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x106A 
	MOVWF	r0x1001
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;;	721 register type nRegs=2
;; 	line = 6342 result AOP_REG=r0x106C, size=2, left -=-, size=0, right AOP_LIT=0x00, size=2
;; ***	genAssign  6434
; >>> gen.c:6443:genAssign
;;	1109 rIdx = r0x106C 
	.line	226; "rfm12.c"	unsigned int dsdo=0;
	CLRF	r0x1002
;; ***	genAssign  6434
; >>> gen.c:6443:genAssign
;;	1109 rIdx = r0x106D 
	CLRF	r0x1003
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
	.line	229; "rfm12.c"	nSEL=0;               // activate rfm12
	BCF	_PORTB_bits,3
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;;	721 register type nRegs=1
;; 	line = 6342 result AOP_REG=r0x106E, size=1, left -=-, size=0, right AOP_LIT=0x00, size=1
;; ***	genAssign  6434
; >>> gen.c:6443:genAssign
;;	1109 rIdx = r0x106E 
	.line	230; "rfm12.c"	for(i=0;i<16;i++){    // bit by bit...
	CLRF	r0x1004
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:3357:genCmpLt *{*
;; ***	genCmpLt  3358
;;	721 register type nRegs=1
;; gen.c:3126:genCmp *{*
;unsigned compare: left < lit(0x10=16), size=1
; >>> gen.c:3099:pic14_mov2w_regOrLit
_00227_DS_
	MOVLW	0x10
; >>> gen.c:3234:genCmp
;;	1109 rIdx = r0x106E 
	SUBWF	r0x1004,W
;; gen.c:3073:genSkipc *{*
; >>> gen.c:3078:genSkipc
	BTFSC	STATUS,0
; >>> gen.c:3082:genSkipc
;; ***	popGetLabel  key=12, label offset 118
	GOTO	_00230_DS_
;genSkipc:3083: created from rifx:0xbf877470
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:3719:genAnd *{*
;; ***	genAnd  3720
;;	721 register type nRegs=2
;; 	line = 3754 result AOP_CRY=0x00, size=0, left AOP_REG=r0x106A, size=2, right AOP_LIT=0x00, size=2
;; gen.c:3646:isLiteralBit *{*
;; ***	isLiteralBit  3647
; >>> gen.c:3823:genAnd
	.line	231; "rfm12.c"	if(dout&0x8000){    // is data out lsb 1???
	BTFSS	r0x1000,7
; >>> gen.c:3824:genAnd
;; ***	popGetLabel  key=2, label offset 118
	GOTO	_00220_DS_
;; gen.c:2261:resultRemat *{*
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
	.line	232; "rfm12.c"	SDO=1;            // yes, SDO high
	BSF	_PORTB_bits,2
;; gen.c:2261:resultRemat *{*
;; gen.c:2614:genGoto *{*
; >>> gen.c:2616:genGoto
;; ***	popGetLabel  key=3, label offset 118
	GOTO	_00221_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
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
_00220_DS_
	.line	234; "rfm12.c"	SDO=0;            // no, SDO low
	BCF	_PORTB_bits,2
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:4988:genGenericShift *{*
;; ***	genGenericShift  4992
;;	721 register type nRegs=2
;;	606
; >>> gen.c:4780:shiftLeft_Left2ResultLit
_00221_DS_
	.line	236; "rfm12.c"	dsdo<<=1;           // next bit of data in!
	BCF	STATUS,0
; >>> gen.c:4783:shiftLeft_Left2ResultLit
;;	1109 rIdx = r0x106C 
	RLF	r0x1002,F
; >>> gen.c:4783:shiftLeft_Left2ResultLit
;;	1109 rIdx = r0x106D 
	.line	237; "rfm12.c"	if(SDI){            // is SDI high (rfm12 has been received data)?
	RLF	r0x1003,F
	.line	238; "rfm12.c"	dsdo|=1;          // set corresponding bit of data in
	BTFSC	_PORTB_bits,1
	.line	240; "rfm12.c"	SCK=1;              // positive edge of clk
	BSF	r0x1002,0
	BSF	_PORTB_bits,4
	.line	241; "rfm12.c"	dout<<=1;           // next bit of data out
	BCF	STATUS,0
; >>> gen.c:4783:shiftLeft_Left2ResultLit
;;	1109 rIdx = r0x106A 
	RLF	r0x1001,F
; >>> gen.c:4783:shiftLeft_Left2ResultLit
;;	1109 rIdx = r0x106B 
	RLF	r0x1000,F
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;;	721 register type nRegs=1
;; 	line = 6342 result AOP_REG=r0x106F, size=1, left -=-, size=0, right AOP_LIT=0x01, size=1
;; ***	genAssign  6434
; >>> gen.c:6439:genAssign
	.line	242; "rfm12.c"	delay_us(5);
	MOVLW	0x01
; >>> gen.c:6441:genAssign
;;	1109 rIdx = r0x106F 
	MOVWF	r0x1005
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
;;	1109 rIdx = r0x106F 
_00224_DS_
	DECFSZ	r0x1005,F
; >>> gen.c:6727:genDjnz
;; ***	popGetLabel  key=6, label offset 118
	GOTO	_00224_DS_
;; gen.c:2261:resultRemat *{*
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
	.line	243; "rfm12.c"	SCK=0;              // negative edge of clk
	BCF	_PORTB_bits,4
;; gen.c:2261:resultRemat *{*
;; ***	genPlus  547
;; genarith.c:548:genPlus *{*
;;	721 register type nRegs=1
;;	606
;; 	line = 554 result AOP_REG=r0x106E, size=1, left AOP_REG=r0x106E, size=1, right AOP_LIT=0x01, size=1
;; ***	pic14_getDataSize  1426
;; genarith.c:142:genPlusIncr *{*
;; ***	genPlusIncr  144
;; 	result AOP_REG, left AOP_REG, right AOP_LIT
;; 	genPlusIncr  156
; >>> genarith.c:168:genPlusIncr
;;	1109 rIdx = r0x106E 
	.line	230; "rfm12.c"	for(i=0;i<16;i++){    // bit by bit...
	INCF	r0x1004,F
;; gen.c:2261:resultRemat *{*
;; gen.c:2614:genGoto *{*
; >>> gen.c:2616:genGoto
;; ***	popGetLabel  key=9, label offset 118
	GOTO	_00227_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
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
_00230_DS_
	.line	245; "rfm12.c"	nSEL=1;               // deactivate rfm12
	BSF	_PORTB_bits,3
;; gen.c:2261:resultRemat *{*
;; gen.c:2561:genRet *{*
;; ***	genRet  2563
;;	721 register type nRegs=2
;; gen.c:1324:mov2w_op *{*
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x106C 
	.line	246; "rfm12.c"	return dsdo;          // return data in
	MOVF	r0x1002,W
; >>> gen.c:1387:pass_argument
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
;; ***	mov2w  1356  offset=1
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x106D 
	MOVF	r0x1003,W
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2435:genEndFunction *{*
;; ***	genEndFunction  2437
	RETURN	
; exit point of _rfm12_spi16

	New pBlock

code, dbName =C
;; Starting pCode block
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2283:genFunction *{*
;; ***	genFunction  2285 curr label offset=87previous max_key=0 
_rfm12_wait	;Function start
; 2 exit points
;; gen.c:2261:resultRemat *{*
;; gen.c:6739:genReceive *{*
;; ***	genReceive  6740
;;	721 register type nRegs=2
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x1065, size=2, right -=-, size=0
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1066 
	.line	203; "rfm12.c"	unsigned char rfm12_wait(unsigned int tout){
	MOVWF	r0x1006
; >>> gen.c:1393:get_returnvalue
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVF	STK00,W
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1065 
	MOVWF	r0x1007
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
	.line	206; "rfm12.c"	nSEL=0;
	BCF	_PORTB_bits,3
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;;	721 register type nRegs=2
;; 	line = 6342 result AOP_REG=r0x1067, size=2, left -=-, size=0, right AOP_LIT=0x00, size=2
;; ***	genAssign  6434
; >>> gen.c:6443:genAssign
;;	1109 rIdx = r0x1067 
	.line	207; "rfm12.c"	do{
	CLRF	r0x1008
;; ***	genAssign  6434
; >>> gen.c:6443:genAssign
;;	1109 rIdx = r0x1068 
	CLRF	r0x1009
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; ***	genPlus  547
;; genarith.c:548:genPlus *{*
;;	721 register type nRegs=2
;;	606
;; 	line = 554 result AOP_REG=r0x1067, size=2, left AOP_REG=r0x1067, size=2, right AOP_LIT=0x01, size=1
;; ***	pic14_getDataSize  1426
;; genarith.c:142:genPlusIncr *{*
;; ***	genPlusIncr  144
;; 	result AOP_REG, left AOP_REG, right AOP_LIT
;; 	genPlusIncr  156
; >>> genarith.c:168:genPlusIncr
;;	1109 rIdx = r0x1067 
_00196_DS_
	.line	208; "rfm12.c"	to++;
	INCF	r0x1008,F
; >>> genarith.c:172:genPlusIncr
	BTFSC	STATUS,2
; >>> genarith.c:173:genPlusIncr
;;	1109 rIdx = r0x1068 
	INCF	r0x1009,F
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;;	721 register type nRegs=1
;; 	line = 6342 result AOP_REG=r0x1069, size=1, left -=-, size=0, right AOP_LIT=0x21, size=1
;; ***	genAssign  6434
; >>> gen.c:6439:genAssign
	.line	209; "rfm12.c"	delay_us(100);
	MOVLW	0x21
; >>> gen.c:6441:genAssign
;;	1109 rIdx = r0x1069 
	MOVWF	r0x100A
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
;;	1109 rIdx = r0x1069 
_00192_DS_
	DECFSZ	r0x100A,F
; >>> gen.c:6727:genDjnz
;; ***	popGetLabel  key=1, label offset 91
	GOTO	_00192_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:5608:genPointerGet *{*
;; ***	genPointerGet  5609
;; gen.c:5397:genNearPointerGet *{*
;; ***	genNearPointerGet  5398
;;	641
;;	aopForRemat 425
;;	446: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerGet  5414
;;	721 register type nRegs=1
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:5240:genUnpackBits *{*
;; ***	genUnpackBits  5241
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:5257:genUnpackBits
	.line	210; "rfm12.c"	}while((!SDI)&&(to<tout));
	BTFSC	_PORTB_bits,1
; >>> gen.c:5258:genUnpackBits
;; ***	popGetLabel  key=7, label offset 91
	GOTO	_00198_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:3357:genCmpLt *{*
;; ***	genCmpLt  3358
;;	721 register type nRegs=2
;;	721 register type nRegs=2
;; gen.c:3126:genCmp *{*
; >>> gen.c:3101:pic14_mov2w_regOrLit
;;	1109 rIdx = r0x1066 
	MOVF	r0x1006,W
; >>> gen.c:3234:genCmp
;;	1109 rIdx = r0x1068 
	SUBWF	r0x1009,W
; >>> gen.c:3270:genCmp
	BTFSS	STATUS,2
; >>> gen.c:3271:genCmp
;; ***	popGetLabel  key=22, label offset 91
	GOTO	_00213_DS_
; >>> gen.c:3101:pic14_mov2w_regOrLit
;;	1109 rIdx = r0x1065 
	MOVF	r0x1007,W
; >>> gen.c:3273:genCmp
;;	1109 rIdx = r0x1067 
	SUBWF	r0x1008,W
;; gen.c:3073:genSkipc *{*
; >>> gen.c:3080:genSkipc
_00213_DS_
	BTFSS	STATUS,0
; >>> gen.c:3082:genSkipc
;; ***	popGetLabel  key=5, label offset 91
	GOTO	_00196_DS_
;genSkipc:3083: created from rifx:0xbf877470
;; gen.c:2261:resultRemat *{*
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
; >>> gen.c:3101:pic14_mov2w_regOrLit
;;	1109 rIdx = r0x1066 
_00198_DS_
	.line	212; "rfm12.c"	if(to<tout){
	MOVF	r0x1006,W
; >>> gen.c:3234:genCmp
;;	1109 rIdx = r0x1068 
	SUBWF	r0x1009,W
; >>> gen.c:3270:genCmp
	BTFSS	STATUS,2
; >>> gen.c:3271:genCmp
;; ***	popGetLabel  key=23, label offset 91
	GOTO	_00214_DS_
; >>> gen.c:3101:pic14_mov2w_regOrLit
;;	1109 rIdx = r0x1065 
	MOVF	r0x1007,W
; >>> gen.c:3273:genCmp
;;	1109 rIdx = r0x1067 
	SUBWF	r0x1008,W
;; gen.c:3073:genSkipc *{*
; >>> gen.c:3078:genSkipc
_00214_DS_
	BTFSC	STATUS,0
; >>> gen.c:3082:genSkipc
;; ***	popGetLabel  key=9, label offset 91
	GOTO	_00200_DS_
;genSkipc:3083: created from rifx:0xbf877470
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2561:genRet *{*
;; ***	genRet  2563
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	.line	213; "rfm12.c"	return 1;
	MOVLW	0x01
; >>> gen.c:2587:genRet
;; ***	popGetLabel  key=11, label offset 91
	GOTO	_00202_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2561:genRet *{*
;; ***	genRet  2563
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
_00200_DS_
	.line	215; "rfm12.c"	return 0; 
	MOVLW	0x00
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2435:genEndFunction *{*
;; ***	genEndFunction  2437
_00202_DS_
	RETURN	
; exit point of _rfm12_wait
;; gen.c:6803:genpic14Code *{*

	New pBlock

code, dbName =C
;; Starting pCode block
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2283:genFunction *{*
;; ***	genFunction  2285 curr label offset=83previous max_key=0 
_rfm12_dis_rx	;Function start
; 2 exit points
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
;; 	2079 left AOP_LIT
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	.line	192; "rfm12.c"	rfm12_spi16(0x8208);
	MOVLW	0x08
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0x82
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
;; 	line = 5965 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:5720:genPackBits
	.line	193; "rfm12.c"	nSEL=1;
	BSF	_PORTB_bits,3
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2435:genEndFunction *{*
;; ***	genEndFunction  2437
	RETURN	
; exit point of _rfm12_dis_rx
;; gen.c:6803:genpic14Code *{*

	New pBlock

code, dbName =C
;; Starting pCode block
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2283:genFunction *{*
;; ***	genFunction  2285 curr label offset=54previous max_key=25 
_rfm12_ena_rx	;Function start
; 2 exit points
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
	.line	179; "rfm12.c"	nSEL=0;
	BCF	_PORTB_bits,3
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
;; 	2079 left AOP_LIT
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	.line	180; "rfm12.c"	rfm12_spi16(0xca80);
	MOVLW	0x80
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0xca
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
	.line	181; "rfm12.c"	rfm12_spi16(0xca83);
	MOVLW	0x83
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0xca
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
	.line	182; "rfm12.c"	rfm12_spi16(0x82c8);
	MOVLW	0xc8
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0x82
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
	RETURN	
; exit point of _rfm12_ena_rx
;; gen.c:6803:genpic14Code *{*

	New pBlock

code, dbName =C
;; Starting pCode block
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2283:genFunction *{*
;; ***	genFunction  2285 curr label offset=8previous max_key=42 
_rfm12_rcv_msg	;Function start
; 2 exit points
;; gen.c:2261:resultRemat *{*
;; gen.c:6739:genReceive *{*
;; ***	genReceive  6740
;;	721 register type nRegs=3
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x1057, size=3, right -=-, size=0
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1059 
	.line	140; "rfm12.c"	unsigned char rfm12_rcv_msg(unsigned char *msg,int len){
	MOVWF	r0x100B
; >>> gen.c:1393:get_returnvalue
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVF	STK00,W
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1058 
	MOVWF	r0x100C
; >>> gen.c:1393:get_returnvalue
;; ***	popRegFromIdx,1043  , rIdx=0x7e
	MOVF	STK01,W
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1057 
	MOVWF	r0x100D
;; gen.c:2261:resultRemat *{*
;; gen.c:6739:genReceive *{*
;; ***	genReceive  6740
;;	721 register type nRegs=2
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x105A, size=2, right -=-, size=0
; >>> gen.c:1393:get_returnvalue
;; ***	popRegFromIdx,1043  , rIdx=0x7d
	MOVF	STK02,W
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x105B 
	MOVWF	r0x100E
; >>> gen.c:1393:get_returnvalue
;; ***	popRegFromIdx,1043  , rIdx=0x7c
	MOVF	STK03,W
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x105A 
	MOVWF	r0x100F
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;;	721 register type nRegs=2
;; 	line = 6342 result AOP_REG=r0x105C, size=2, left -=-, size=0, right AOP_LIT=0x00, size=2
;; ***	genAssign  6434
; >>> gen.c:6443:genAssign
;;	1109 rIdx = r0x105C 
	.line	141; "rfm12.c"	unsigned int d, chksum=0;
	CLRF	r0x1010
;; ***	genAssign  6434
; >>> gen.c:6443:genAssign
;;	1109 rIdx = r0x105D 
	CLRF	r0x1011
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
	.line	144; "rfm12.c"	nSEL=0;
	BCF	_PORTB_bits,3
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;;	721 register type nRegs=1
;; 	line = 6342 result AOP_REG=r0x105E, size=1, left -=-, size=0, right AOP_LIT=0x00, size=1
;; ***	genAssign  6434
; >>> gen.c:6443:genAssign
;;	1109 rIdx = r0x105E 
	.line	147; "rfm12.c"	for(i=0;i<len;i++){
	CLRF	r0x1012
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:6521:genCast *{*
;; ***	genCast  6522
;;	721 register type nRegs=1
;;	721 register type nRegs=2
;; 	line = 6530 result AOP_REG=r0x105F, size=2, left -=-, size=0, right AOP_REG=r0x105E, size=1
; >>> gen.c:6676:genCast
;;	1109 rIdx = r0x105E 
_00164_DS_
	MOVF	r0x1012,W
; >>> gen.c:6677:genCast
;;	1109 rIdx = r0x105F 
	MOVWF	r0x1013
;; ***	pic14_getDataSize  1426
;; ***	addSign  797
;; genarith.c:798:addSign *{*
; >>> genarith.c:817:addSign
;;	1109 rIdx = r0x1060 
	CLRF	r0x1014
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
;;	1109 rIdx = r0x1060 
	MOVF	r0x1014,W
; >>> gen.c:3256:genCmp
	ADDLW	0x80
; >>> gen.c:3257:genCmp
	MOVWF	r0x1015
;; ***	mov2w  1356  offset=1
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x105B 
	MOVF	r0x100E,W
; >>> gen.c:3259:genCmp
	ADDLW	0x80
; >>> gen.c:3260:genCmp
	SUBWF	r0x1015,W
; >>> gen.c:3270:genCmp
	BTFSS	STATUS,2
; >>> gen.c:3271:genCmp
;; ***	popGetLabel  key=24, label offset 54
	GOTO	_00178_DS_
; >>> gen.c:3101:pic14_mov2w_regOrLit
;;	1109 rIdx = r0x105A 
	MOVF	r0x100F,W
; >>> gen.c:3273:genCmp
;;	1109 rIdx = r0x105F 
	SUBWF	r0x1013,W
;; gen.c:3073:genSkipc *{*
; >>> gen.c:3078:genSkipc
_00178_DS_
	BTFSC	STATUS,0
; >>> gen.c:3082:genSkipc
;; ***	popGetLabel  key=13, label offset 54
	GOTO	_00167_DS_
;genSkipc:3083: created from rifx:0xbf877470
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
;; 	2079 left AOP_LIT
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	.line	148; "rfm12.c"	d=rfm12_spi16(0xb000);
	MOVLW	0x00
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0xb0
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
; >>> gen.c:2123:genCall
	PAGESEL	$
;;	721 register type nRegs=2
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x105F, size=2, right -=-, size=0
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1060 
	MOVWF	r0x1014
; >>> gen.c:1393:get_returnvalue
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVF	STK00,W
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x105F 
	MOVWF	r0x1013
;; 	2138 left AOP_REG
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
	.line	149; "rfm12.c"	if(0==rfm12_wait(RFM12_TOUT))
	MOVLW	0xe8
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0x03
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_wait
; >>> gen.c:2118:genCall
	CALL	_rfm12_wait
; >>> gen.c:2123:genCall
	PAGESEL	$
;;	721 register type nRegs=1
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x1061, size=1, right -=-, size=0
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1061 
	MOVWF	r0x1015
;; 	2138 left AOP_REG
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:3388:genCmpEq *{*
;; ***	genCmpEq  3389
;; ifx is non-null
;;	721 register type nRegs=1
;; 	line = 3400 result AOP_CRY=0x00, size=0, left AOP_LIT=0x00, size=1, right AOP_REG=r0x1061, size=1
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1061 
	MOVF	r0x1015,W
; >>> gen.c:3443:genCmpEq
	BTFSS	STATUS,2
; >>> gen.c:3445:genCmpEq
;; ***	popGetLabel  key=2, label offset 54
	GOTO	_00156_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2561:genRet *{*
;; ***	genRet  2563
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	.line	150; "rfm12.c"	return 0; 
	MOVLW	0x00
; >>> gen.c:2587:genRet
;; ***	popGetLabel  key=14, label offset 54
	GOTO	_00168_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; ***	genPlus  547
;; genarith.c:548:genPlus *{*
;;	721 register type nRegs=3
;;	721 register type nRegs=1
;;	721 register type nRegs=3
;; 	line = 554 result AOP_REG=r0x1061, size=3, left AOP_REG=r0x1057, size=3, right AOP_REG=r0x105E, size=1
;; ***	pic14_getDataSize  1426
;; ***	pic14_getDataSize  1446
;; genarith.c:142:genPlusIncr *{*
;; ***	genPlusIncr  144
;; 	result AOP_REG, left AOP_REG, right AOP_REG
;; ***	pic14_getDataSize  1426
;; ***	pic14_getDataSize  1446
;; ***	genPlus  653
; >>> genarith.c:662:genPlus
;;	1109 rIdx = r0x105E 
_00156_DS_
	.line	151; "rfm12.c"	msg[i]=(unsigned char)d;
	MOVF	r0x1012,W
; >>> genarith.c:671:genPlus
;;	1109 rIdx = r0x1057 
	ADDWF	r0x100D,W
; >>> genarith.c:672:genPlus
;;	1109 rIdx = r0x1061 
	MOVWF	r0x1015
; >>> genarith.c:735:genPlus
;;	1109 rIdx = r0x1058 
	MOVF	r0x100C,W
; >>> genarith.c:736:genPlus
	BTFSC	STATUS,0
; >>> genarith.c:737:genPlus
	ADDLW	0x01
; >>> genarith.c:738:genPlus
;;	1109 rIdx = r0x1062 
	MOVWF	r0x1016
; >>> genarith.c:735:genPlus
;;	1109 rIdx = r0x1059 
	MOVF	r0x100B,W
; >>> genarith.c:736:genPlus
	BTFSC	STATUS,0
; >>> genarith.c:737:genPlus
	ADDLW	0x01
; >>> genarith.c:738:genPlus
;;	1109 rIdx = r0x1063 
	MOVWF	r0x1017
;; gen.c:2261:resultRemat *{*
;; gen.c:6521:genCast *{*
;; ***	genCast  6522
;;	721 register type nRegs=2
;;	721 register type nRegs=1
;; 	line = 6530 result AOP_REG=r0x1064, size=1, left -=-, size=0, right AOP_REG=r0x105F, size=2
;; ***	genCast  6636
; >>> gen.c:6656:genCast
;;	1109 rIdx = r0x105F 
	MOVF	r0x1013,W
	MOVWF	r0x1018
	MOVWF	STK02
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1061 
	MOVF	r0x1015,W
; >>> gen.c:6097:genGenPointerSet
;; ***	popRegFromIdx,1043  , rIdx=0x7e
	MOVWF	STK01
;; ***	mov2w  1356  offset=1
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1062 
	MOVF	r0x1016,W
; >>> gen.c:6099:genGenPointerSet
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; ***	mov2w  1356  offset=2
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1063 
	MOVF	r0x1017,W
; >>> gen.c:1402:call_libraryfunc
	PAGESEL	__gptrput1
; >>> gen.c:1404:call_libraryfunc
	CALL	__gptrput1
; >>> gen.c:1406:call_libraryfunc
	PAGESEL	$
;; gen.c:2261:resultRemat *{*
;; gen.c:6521:genCast *{*
;; ***	genCast  6522
;;	721 register type nRegs=1
;;	721 register type nRegs=2
;; 	line = 6530 result AOP_REG=r0x1061, size=2, left -=-, size=0, right AOP_REG=r0x1064, size=1
; >>> gen.c:6676:genCast
;;	1109 rIdx = r0x1064 
	.line	152; "rfm12.c"	chksum+=msg[i];
	MOVF	r0x1018,W
; >>> gen.c:6677:genCast
;;	1109 rIdx = r0x1061 
	MOVWF	r0x1015
;; ***	pic14_getDataSize  1426
;; ***	addSign  797
;; genarith.c:798:addSign *{*
; >>> genarith.c:817:addSign
;;	1109 rIdx = r0x1062 
	CLRF	r0x1016
;; gen.c:2261:resultRemat *{*
;; ***	genPlus  547
;; genarith.c:548:genPlus *{*
;;	721 register type nRegs=2
;;	721 register type nRegs=2
;;	606
;; 	line = 554 result AOP_REG=r0x105C, size=2, left AOP_REG=r0x105C, size=2, right AOP_REG=r0x1061, size=2
;; ***	pic14_getDataSize  1426
;; genarith.c:142:genPlusIncr *{*
;; ***	genPlusIncr  144
;; 	result AOP_REG, left AOP_REG, right AOP_REG
;; ***	pic14_getDataSize  1426
;; ***	genPlus  653
; >>> genarith.c:662:genPlus
;;	1109 rIdx = r0x1061 
	MOVF	r0x1015,W
; >>> genarith.c:665:genPlus
;;	1109 rIdx = r0x105C 
	ADDWF	r0x1010,F
; >>> genarith.c:710:genPlus
;;	1109 rIdx = r0x1062 
	MOVF	r0x1016,W
; >>> genarith.c:711:genPlus
	BTFSC	STATUS,0
; >>> genarith.c:712:genPlus
;;	1109 rIdx = r0x1062 
	INCFSZ	r0x1016,W
; >>> genarith.c:713:genPlus
;;	1109 rIdx = r0x105D 
	ADDWF	r0x1011,F
;; gen.c:2261:resultRemat *{*
;; ***	genPlus  547
;; genarith.c:548:genPlus *{*
;;	721 register type nRegs=1
;;	606
;; 	line = 554 result AOP_REG=r0x105E, size=1, left AOP_REG=r0x105E, size=1, right AOP_LIT=0x01, size=1
;; ***	pic14_getDataSize  1426
;; genarith.c:142:genPlusIncr *{*
;; ***	genPlusIncr  144
;; 	result AOP_REG, left AOP_REG, right AOP_LIT
;; 	genPlusIncr  156
; >>> genarith.c:168:genPlusIncr
;;	1109 rIdx = r0x105E 
	.line	147; "rfm12.c"	for(i=0;i<len;i++){
	INCF	r0x1012,F
;; gen.c:2261:resultRemat *{*
;; gen.c:2614:genGoto *{*
; >>> gen.c:2616:genGoto
;; ***	popGetLabel  key=10, label offset 54
	GOTO	_00164_DS_
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
_00167_DS_
	.line	155; "rfm12.c"	d=rfm12_spi16(0xb000);
	MOVLW	0x00
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0xb0
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
; >>> gen.c:2123:genCall
	PAGESEL	$
;;	721 register type nRegs=2
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x105F, size=2, right -=-, size=0
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1060 
	MOVWF	r0x1014
; >>> gen.c:1393:get_returnvalue
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVF	STK00,W
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x105F 
	MOVWF	r0x1013
;; 	2138 left AOP_REG
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
	.line	156; "rfm12.c"	if(0==rfm12_wait(RFM12_TOUT))
	MOVLW	0xe8
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0x03
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_wait
; >>> gen.c:2118:genCall
	CALL	_rfm12_wait
; >>> gen.c:2123:genCall
	PAGESEL	$
;;	721 register type nRegs=1
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x1057, size=1, right -=-, size=0
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1057 
	MOVWF	r0x100D
;; 	2138 left AOP_REG
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:3388:genCmpEq *{*
;; ***	genCmpEq  3389
;; ifx is non-null
;;	721 register type nRegs=1
;; 	line = 3400 result AOP_CRY=0x00, size=0, left AOP_LIT=0x00, size=1, right AOP_REG=r0x1057, size=1
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1057 
	MOVF	r0x100D,W
; >>> gen.c:3443:genCmpEq
	BTFSS	STATUS,2
; >>> gen.c:3445:genCmpEq
;; ***	popGetLabel  key=4, label offset 54
	GOTO	_00158_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2561:genRet *{*
;; ***	genRet  2563
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	.line	157; "rfm12.c"	return 0;
	MOVLW	0x00
; >>> gen.c:2587:genRet
;; ***	popGetLabel  key=14, label offset 54
	GOTO	_00168_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; NULL :(	3526
;; gen.c:3719:genAnd *{*
;; ***	genAnd  3720
;;	721 register type nRegs=2
;;	606
;; 	line = 3754 result AOP_REG=r0x105C, size=2, left AOP_REG=r0x105C, size=2, right AOP_LIT=0xff, size=2
; >>> gen.c:3887:genAnd
;;	1109 rIdx = r0x105D 
_00158_DS_
	.line	159; "rfm12.c"	chksum&=0x0ff;
	CLRF	r0x1011
;; gen.c:2261:resultRemat *{*
;; gen.c:6521:genCast *{*
;; ***	genCast  6522
;;	721 register type nRegs=2
;;	721 register type nRegs=1
;; 	line = 6530 result AOP_REG=r0x1057, size=1, left -=-, size=0, right AOP_REG=r0x105F, size=2
;; ***	genCast  6636
; >>> gen.c:6656:genCast
;;	1109 rIdx = r0x105F 
	.line	160; "rfm12.c"	if(chksum!=(unsigned char)d){   // last byte is checksum
	MOVF	r0x1013,W
	MOVWF	r0x100D
	MOVWF	r0x1013
;; ***	pic14_getDataSize  1426
;; ***	addSign  797
;; genarith.c:798:addSign *{*
; >>> genarith.c:817:addSign
;;	1109 rIdx = r0x1060 
	CLRF	r0x1014
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:3388:genCmpEq *{*
;; ***	genCmpEq  3389
;; ifx is non-null
;;	721 register type nRegs=2
;;	721 register type nRegs=2
;; 	line = 3400 result AOP_CRY=0x00, size=0, left AOP_REG=r0x105C, size=2, right AOP_REG=r0x105F, size=2
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x105F 
	MOVF	r0x1013,W
; >>> gen.c:3469:genCmpEq
;;	1109 rIdx = r0x105C 
	XORWF	r0x1010,W
; >>> gen.c:3471:genCmpEq
	BTFSS	STATUS,2
; >>> gen.c:3473:genCmpEq
;; ***	popGetLabel  key=25, label offset 54
	GOTO	_00179_DS_
;; ***	mov2w  1356  offset=1
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1060 
	MOVF	r0x1014,W
; >>> gen.c:3469:genCmpEq
;;	1109 rIdx = r0x105D 
	.line	161; "rfm12.c"	RB7=1;                        // checksum error!!!
	XORWF	r0x1011,W
	.line	163; "rfm12.c"	rfm12_dis_rx();
	BTFSS	STATUS,2
_00179_DS_
	BSF	_PORTB_bits,7
	PAGESEL	_rfm12_dis_rx
	CALL	_rfm12_dis_rx
; >>> gen.c:2123:genCall
	PAGESEL	$
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;;	721 register type nRegs=1
;; 	line = 6342 result AOP_REG=r0x1057, size=1, left -=-, size=0, right AOP_LIT=0x01, size=1
;; ***	genAssign  6434
; >>> gen.c:6439:genAssign
	.line	164; "rfm12.c"	delay_us(5);
	MOVLW	0x01
; >>> gen.c:6441:genAssign
;;	1109 rIdx = r0x1057 
	MOVWF	r0x100D
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
;;	1109 rIdx = r0x1057 
_00161_DS_
	DECFSZ	r0x100D,F
; >>> gen.c:6727:genDjnz
;; ***	popGetLabel  key=7, label offset 54
	GOTO	_00161_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
; >>> gen.c:2116:genCall
	.line	165; "rfm12.c"	rfm12_ena_rx();
	PAGESEL	_rfm12_ena_rx
; >>> gen.c:2118:genCall
	CALL	_rfm12_ena_rx
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
_00168_DS_
	RETURN	
; exit point of _rfm12_rcv_msg
;; gen.c:6803:genpic14Code *{*

	New pBlock

code, dbName =C
;; Starting pCode block
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2283:genFunction *{*
;; ***	genFunction  2285 curr label offset=4previous max_key=0 
_rfm12_snd_msg	;Function start
; 2 exit points
;; gen.c:2261:resultRemat *{*
;; gen.c:6739:genReceive *{*
;; ***	genReceive  6740
;;	721 register type nRegs=3
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x1048, size=3, right -=-, size=0
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x104A 
	.line	78; "rfm12.c"	unsigned char rfm12_snd_msg(unsigned char *msg,int len){
	MOVWF	r0x1019
; >>> gen.c:1393:get_returnvalue
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVF	STK00,W
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1049 
	MOVWF	r0x101A
; >>> gen.c:1393:get_returnvalue
;; ***	popRegFromIdx,1043  , rIdx=0x7e
	MOVF	STK01,W
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1048 
	MOVWF	r0x101B
;; gen.c:2261:resultRemat *{*
;; gen.c:6739:genReceive *{*
;; ***	genReceive  6740
;;	721 register type nRegs=2
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x104B, size=2, right -=-, size=0
; >>> gen.c:1393:get_returnvalue
;; ***	popRegFromIdx,1043  , rIdx=0x7d
	MOVF	STK02,W
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x104C 
	MOVWF	r0x101C
; >>> gen.c:1393:get_returnvalue
;; ***	popRegFromIdx,1043  , rIdx=0x7c
	MOVF	STK03,W
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x104B 
	MOVWF	r0x101D
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;;	721 register type nRegs=2
;; 	line = 6342 result AOP_REG=r0x104D, size=2, left -=-, size=0, right AOP_LIT=0x00, size=2
;; ***	genAssign  6434
; >>> gen.c:6443:genAssign
;;	1109 rIdx = r0x104D 
	.line	79; "rfm12.c"	unsigned int d,chksum=0;
	CLRF	r0x101E
;; ***	genAssign  6434
; >>> gen.c:6443:genAssign
;;	1109 rIdx = r0x104E 
	CLRF	r0x101F
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
;; 	2079 left AOP_LIT
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	.line	82; "rfm12.c"	d=rfm12_spi16(0x8238);          // Tx on
	MOVLW	0x38
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0x82
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
	.line	83; "rfm12.c"	if(0==rfm12_wait(RFM12_TOUT))
	MOVLW	0xe8
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0x03
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_wait
; >>> gen.c:2118:genCall
	CALL	_rfm12_wait
; >>> gen.c:2123:genCall
	PAGESEL	$
;;	721 register type nRegs=1
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x104F, size=1, right -=-, size=0
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x104F 
	MOVWF	r0x1020
;; 	2138 left AOP_REG
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:3388:genCmpEq *{*
;; ***	genCmpEq  3389
;; ifx is non-null
;;	721 register type nRegs=1
;; 	line = 3400 result AOP_CRY=0x00, size=0, left AOP_LIT=0x00, size=1, right AOP_REG=r0x104F, size=1
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x104F 
	MOVF	r0x1020,W
; >>> gen.c:3443:genCmpEq
	BTFSS	STATUS,2
; >>> gen.c:3445:genCmpEq
;; ***	popGetLabel  key=2, label offset 8
	GOTO	_00110_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2561:genRet *{*
;; ***	genRet  2563
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	.line	84; "rfm12.c"	return 0;
	MOVLW	0x00
; >>> gen.c:2587:genRet
;; ***	popGetLabel  key=27, label offset 8
	GOTO	_00135_DS_
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
	.line	85; "rfm12.c"	d=rfm12_spi16(0xb8aa);          // Preamble
	MOVLW	0xaa
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0xb8
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
	.line	86; "rfm12.c"	if(0==rfm12_wait(RFM12_TOUT))
	MOVLW	0xe8
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0x03
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_wait
; >>> gen.c:2118:genCall
	CALL	_rfm12_wait
; >>> gen.c:2123:genCall
	PAGESEL	$
;;	721 register type nRegs=1
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x104F, size=1, right -=-, size=0
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x104F 
	MOVWF	r0x1020
;; 	2138 left AOP_REG
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:3388:genCmpEq *{*
;; ***	genCmpEq  3389
;; ifx is non-null
;;	721 register type nRegs=1
;; 	line = 3400 result AOP_CRY=0x00, size=0, left AOP_LIT=0x00, size=1, right AOP_REG=r0x104F, size=1
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x104F 
	MOVF	r0x1020,W
; >>> gen.c:3443:genCmpEq
	BTFSS	STATUS,2
; >>> gen.c:3445:genCmpEq
;; ***	popGetLabel  key=4, label offset 8
	GOTO	_00112_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2561:genRet *{*
;; ***	genRet  2563
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	.line	87; "rfm12.c"	return 0;
	MOVLW	0x00
; >>> gen.c:2587:genRet
;; ***	popGetLabel  key=27, label offset 8
	GOTO	_00135_DS_
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
_00112_DS_
	.line	88; "rfm12.c"	d=rfm12_spi16(0xb8aa);          // Preamble
	MOVLW	0xaa
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0xb8
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
	.line	89; "rfm12.c"	if(0==rfm12_wait(RFM12_TOUT))
	MOVLW	0xe8
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0x03
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_wait
; >>> gen.c:2118:genCall
	CALL	_rfm12_wait
; >>> gen.c:2123:genCall
	PAGESEL	$
;;	721 register type nRegs=1
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x104F, size=1, right -=-, size=0
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x104F 
	MOVWF	r0x1020
;; 	2138 left AOP_REG
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:3388:genCmpEq *{*
;; ***	genCmpEq  3389
;; ifx is non-null
;;	721 register type nRegs=1
;; 	line = 3400 result AOP_CRY=0x00, size=0, left AOP_LIT=0x00, size=1, right AOP_REG=r0x104F, size=1
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x104F 
	MOVF	r0x1020,W
; >>> gen.c:3443:genCmpEq
	BTFSS	STATUS,2
; >>> gen.c:3445:genCmpEq
;; ***	popGetLabel  key=6, label offset 8
	GOTO	_00114_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2561:genRet *{*
;; ***	genRet  2563
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	.line	90; "rfm12.c"	return 0;
	MOVLW	0x00
; >>> gen.c:2587:genRet
;; ***	popGetLabel  key=27, label offset 8
	GOTO	_00135_DS_
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
_00114_DS_
	.line	91; "rfm12.c"	d=rfm12_spi16(0xb8aa);          // Preamble
	MOVLW	0xaa
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0xb8
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
	.line	92; "rfm12.c"	if(0==rfm12_wait(RFM12_TOUT))
	MOVLW	0xe8
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0x03
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_wait
; >>> gen.c:2118:genCall
	CALL	_rfm12_wait
; >>> gen.c:2123:genCall
	PAGESEL	$
;;	721 register type nRegs=1
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x104F, size=1, right -=-, size=0
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x104F 
	MOVWF	r0x1020
;; 	2138 left AOP_REG
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:3388:genCmpEq *{*
;; ***	genCmpEq  3389
;; ifx is non-null
;;	721 register type nRegs=1
;; 	line = 3400 result AOP_CRY=0x00, size=0, left AOP_LIT=0x00, size=1, right AOP_REG=r0x104F, size=1
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x104F 
	MOVF	r0x1020,W
; >>> gen.c:3443:genCmpEq
	BTFSS	STATUS,2
; >>> gen.c:3445:genCmpEq
;; ***	popGetLabel  key=8, label offset 8
	GOTO	_00116_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2561:genRet *{*
;; ***	genRet  2563
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	.line	93; "rfm12.c"	return 0;
	MOVLW	0x00
; >>> gen.c:2587:genRet
;; ***	popGetLabel  key=27, label offset 8
	GOTO	_00135_DS_
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
_00116_DS_
	.line	94; "rfm12.c"	d=rfm12_spi16(0xb82d);          // Sync hi-byte
	MOVLW	0x2d
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0xb8
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
	.line	95; "rfm12.c"	if(0==rfm12_wait(RFM12_TOUT))
	MOVLW	0xe8
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0x03
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_wait
; >>> gen.c:2118:genCall
	CALL	_rfm12_wait
; >>> gen.c:2123:genCall
	PAGESEL	$
;;	721 register type nRegs=1
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x104F, size=1, right -=-, size=0
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x104F 
	MOVWF	r0x1020
;; 	2138 left AOP_REG
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:3388:genCmpEq *{*
;; ***	genCmpEq  3389
;; ifx is non-null
;;	721 register type nRegs=1
;; 	line = 3400 result AOP_CRY=0x00, size=0, left AOP_LIT=0x00, size=1, right AOP_REG=r0x104F, size=1
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x104F 
	MOVF	r0x1020,W
; >>> gen.c:3443:genCmpEq
	BTFSS	STATUS,2
; >>> gen.c:3445:genCmpEq
;; ***	popGetLabel  key=10, label offset 8
	GOTO	_00118_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2561:genRet *{*
;; ***	genRet  2563
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	.line	96; "rfm12.c"	return 0;
	MOVLW	0x00
; >>> gen.c:2587:genRet
;; ***	popGetLabel  key=27, label offset 8
	GOTO	_00135_DS_
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
_00118_DS_
	.line	97; "rfm12.c"	d=rfm12_spi16(0xb8d4);          // Sync low-byte
	MOVLW	0xd4
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0xb8
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
	.line	98; "rfm12.c"	if(0==rfm12_wait(RFM12_TOUT))
	MOVLW	0xe8
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0x03
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_wait
; >>> gen.c:2118:genCall
	CALL	_rfm12_wait
; >>> gen.c:2123:genCall
	PAGESEL	$
;;	721 register type nRegs=1
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x104F, size=1, right -=-, size=0
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x104F 
	MOVWF	r0x1020
;; 	2138 left AOP_REG
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:3388:genCmpEq *{*
;; ***	genCmpEq  3389
;; ifx is non-null
;;	721 register type nRegs=1
;; 	line = 3400 result AOP_CRY=0x00, size=0, left AOP_LIT=0x00, size=1, right AOP_REG=r0x104F, size=1
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x104F 
	MOVF	r0x1020,W
; >>> gen.c:3443:genCmpEq
	BTFSS	STATUS,2
; >>> gen.c:3445:genCmpEq
;; ***	popGetLabel  key=37, label offset 8
	GOTO	_00145_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2561:genRet *{*
;; ***	genRet  2563
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	.line	99; "rfm12.c"	return 0;
	MOVLW	0x00
; >>> gen.c:2587:genRet
;; ***	popGetLabel  key=27, label offset 8
	GOTO	_00135_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;;	721 register type nRegs=1
;; 	line = 6342 result AOP_REG=r0x104F, size=1, left -=-, size=0, right AOP_LIT=0x00, size=1
;; ***	genAssign  6434
; >>> gen.c:6443:genAssign
;;	1109 rIdx = r0x104F 
_00145_DS_
	.line	102; "rfm12.c"	for(i=0;i<len;i++){
	CLRF	r0x1020
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:6521:genCast *{*
;; ***	genCast  6522
;;	721 register type nRegs=1
;;	721 register type nRegs=2
;; 	line = 6530 result AOP_REG=r0x1050, size=2, left -=-, size=0, right AOP_REG=r0x104F, size=1
; >>> gen.c:6676:genCast
;;	1109 rIdx = r0x104F 
_00131_DS_
	MOVF	r0x1020,W
; >>> gen.c:6677:genCast
;;	1109 rIdx = r0x1050 
	MOVWF	r0x1021
;; ***	pic14_getDataSize  1426
;; ***	addSign  797
;; genarith.c:798:addSign *{*
; >>> genarith.c:817:addSign
;;	1109 rIdx = r0x1051 
	CLRF	r0x1022
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
;;	1109 rIdx = r0x1051 
	MOVF	r0x1022,W
; >>> gen.c:3256:genCmp
	ADDLW	0x80
; >>> gen.c:3257:genCmp
	MOVWF	r0x1023
;; ***	mov2w  1356  offset=1
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x104C 
	MOVF	r0x101C,W
; >>> gen.c:3259:genCmp
	ADDLW	0x80
; >>> gen.c:3260:genCmp
	SUBWF	r0x1023,W
; >>> gen.c:3270:genCmp
	BTFSS	STATUS,2
; >>> gen.c:3271:genCmp
;; ***	popGetLabel  key=42, label offset 8
	GOTO	_00150_DS_
; >>> gen.c:3101:pic14_mov2w_regOrLit
;;	1109 rIdx = r0x104B 
	MOVF	r0x101D,W
; >>> gen.c:3273:genCmp
;;	1109 rIdx = r0x1050 
	SUBWF	r0x1021,W
;; gen.c:3073:genSkipc *{*
; >>> gen.c:3078:genSkipc
_00150_DS_
	BTFSC	STATUS,0
; >>> gen.c:3082:genSkipc
;; ***	popGetLabel  key=26, label offset 8
	GOTO	_00134_DS_
;genSkipc:3083: created from rifx:0xbf877470
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; ***	genPlus  547
;; genarith.c:548:genPlus *{*
;;	721 register type nRegs=3
;;	721 register type nRegs=1
;;	721 register type nRegs=3
;; 	line = 554 result AOP_REG=r0x1050, size=3, left AOP_REG=r0x1048, size=3, right AOP_REG=r0x104F, size=1
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
	.line	103; "rfm12.c"	d=rfm12_spi16(0xb800|(msg[i]));
	MOVF	r0x1020,W
; >>> genarith.c:671:genPlus
;;	1109 rIdx = r0x1048 
	ADDWF	r0x101B,W
; >>> genarith.c:672:genPlus
;;	1109 rIdx = r0x1050 
	MOVWF	r0x1021
; >>> genarith.c:735:genPlus
;;	1109 rIdx = r0x1049 
	MOVF	r0x101A,W
; >>> genarith.c:736:genPlus
	BTFSC	STATUS,0
; >>> genarith.c:737:genPlus
	ADDLW	0x01
; >>> genarith.c:738:genPlus
;;	1109 rIdx = r0x1051 
	MOVWF	r0x1022
; >>> genarith.c:735:genPlus
;;	1109 rIdx = r0x104A 
	MOVF	r0x1019,W
; >>> genarith.c:736:genPlus
	BTFSC	STATUS,0
; >>> genarith.c:737:genPlus
	ADDLW	0x01
; >>> genarith.c:738:genPlus
;;	1109 rIdx = r0x1052 
	MOVWF	r0x1024
;; gen.c:2261:resultRemat *{*
;; gen.c:5608:genPointerGet *{*
;; ***	genPointerGet  5609
;; gen.c:5496:genGenPointerGet *{*
;; ***	genGenPointerGet  5497
;;	721 register type nRegs=3
;;	721 register type nRegs=1
;; 	line = 5502 result AOP_REG=r0x1053, size=1, left AOP_REG=r0x1050, size=3, right -=-, size=0
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1050 
	MOVF	r0x1021,W
; >>> gen.c:5521:genGenPointerGet
;; ***	popRegFromIdx,1043  , rIdx=0x7e
	MOVWF	STK01
;; ***	mov2w  1356  offset=1
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1051 
	MOVF	r0x1022,W
; >>> gen.c:5523:genGenPointerGet
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; ***	mov2w  1356  offset=2
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1052 
	MOVF	r0x1024,W
; >>> gen.c:1402:call_libraryfunc
	PAGESEL	__gptrget1
; >>> gen.c:1404:call_libraryfunc
	CALL	__gptrget1
; >>> gen.c:1406:call_libraryfunc
	PAGESEL	$
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1053 
	MOVWF	r0x1023
	MOVWF	r0x1025
;; ***	pic14_getDataSize  1426
;; ***	addSign  797
;; genarith.c:798:addSign *{*
; >>> genarith.c:817:addSign
;;	1109 rIdx = r0x1055 
	CLRF	r0x1026
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; NULL :(	3526
;; gen.c:3981:genOr *{*
;; ***	genOr  3982
;;	721 register type nRegs=2
;;	721 register type nRegs=2
;; 	line = 3988 result AOP_REG=r0x1053, size=2, left AOP_REG=r0x1054, size=2, right AOP_LIT=0x00, size=2
;; 	line = 4013 result AOP_REG=r0x1053, size=2, left AOP_REG=r0x1054, size=2, right AOP_LIT=0x00, size=2
; >>> gen.c:4192:genOr
;;	1109 rIdx = r0x1054 
	MOVF	r0x1025,W
; >>> gen.c:4193:genOr
;;	1109 rIdx = r0x1053 
	MOVWF	r0x1023
; >>> gen.c:4197:genOr
	MOVLW	0xb8
; >>> gen.c:4198:genOr
;;	1109 rIdx = r0x1055 
	IORWF	r0x1026,W
; >>> gen.c:4199:genOr
;;	1109 rIdx = r0x1056 
	MOVWF	r0x1027
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
;;	721 register type nRegs=2
;;	721 register type nRegs=2
;; 	2079 left AOP_REG
;; gen.c:1324:mov2w_op *{*
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1053 
	MOVF	r0x1023,W
;; 	2079 left AOP_REG
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
;; ***	mov2w  1356  offset=1
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1056 
	MOVF	r0x1027,W
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
	.line	104; "rfm12.c"	if(0==rfm12_wait(RFM12_TOUT))
	MOVLW	0xe8
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0x03
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_wait
; >>> gen.c:2118:genCall
	CALL	_rfm12_wait
; >>> gen.c:2123:genCall
	PAGESEL	$
;;	721 register type nRegs=1
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x1053, size=1, right -=-, size=0
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1053 
	MOVWF	r0x1023
;; 	2138 left AOP_REG
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:3388:genCmpEq *{*
;; ***	genCmpEq  3389
;; ifx is non-null
;;	721 register type nRegs=1
;; 	line = 3400 result AOP_CRY=0x00, size=0, left AOP_LIT=0x00, size=1, right AOP_REG=r0x1053, size=1
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1053 
	MOVF	r0x1023,W
; >>> gen.c:3443:genCmpEq
	BTFSS	STATUS,2
; >>> gen.c:3445:genCmpEq
;; ***	popGetLabel  key=14, label offset 8
	GOTO	_00122_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2561:genRet *{*
;; ***	genRet  2563
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	.line	105; "rfm12.c"	return 0;
	MOVLW	0x00
; >>> gen.c:2587:genRet
;; ***	popGetLabel  key=27, label offset 8
	GOTO	_00135_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:5608:genPointerGet *{*
;; ***	genPointerGet  5609
;; gen.c:5496:genGenPointerGet *{*
;; ***	genGenPointerGet  5497
;;	721 register type nRegs=3
;;	721 register type nRegs=1
;; 	line = 5502 result AOP_REG=r0x1053, size=1, left AOP_REG=r0x1050, size=3, right -=-, size=0
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1050 
_00122_DS_
	.line	106; "rfm12.c"	chksum+=msg[i];
	MOVF	r0x1021,W
; >>> gen.c:5521:genGenPointerGet
;; ***	popRegFromIdx,1043  , rIdx=0x7e
	MOVWF	STK01
;; ***	mov2w  1356  offset=1
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1051 
	MOVF	r0x1022,W
; >>> gen.c:5523:genGenPointerGet
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; ***	mov2w  1356  offset=2
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1052 
	MOVF	r0x1024,W
; >>> gen.c:1402:call_libraryfunc
	PAGESEL	__gptrget1
; >>> gen.c:1404:call_libraryfunc
	CALL	__gptrget1
; >>> gen.c:1406:call_libraryfunc
	PAGESEL	$
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1053 
	MOVWF	r0x1023
	MOVWF	r0x1021
;; ***	pic14_getDataSize  1426
;; ***	addSign  797
;; genarith.c:798:addSign *{*
; >>> genarith.c:817:addSign
;;	1109 rIdx = r0x1051 
	CLRF	r0x1022
;; gen.c:2261:resultRemat *{*
;; ***	genPlus  547
;; genarith.c:548:genPlus *{*
;;	721 register type nRegs=2
;;	721 register type nRegs=2
;;	606
;; 	line = 554 result AOP_REG=r0x104D, size=2, left AOP_REG=r0x104D, size=2, right AOP_REG=r0x1050, size=2
;; ***	pic14_getDataSize  1426
;; genarith.c:142:genPlusIncr *{*
;; ***	genPlusIncr  144
;; 	result AOP_REG, left AOP_REG, right AOP_REG
;; ***	pic14_getDataSize  1426
;; ***	genPlus  653
; >>> genarith.c:662:genPlus
;;	1109 rIdx = r0x1050 
	MOVF	r0x1021,W
; >>> genarith.c:665:genPlus
;;	1109 rIdx = r0x104D 
	ADDWF	r0x101E,F
; >>> genarith.c:710:genPlus
;;	1109 rIdx = r0x1051 
	MOVF	r0x1022,W
; >>> genarith.c:711:genPlus
	BTFSC	STATUS,0
; >>> genarith.c:712:genPlus
;;	1109 rIdx = r0x1051 
	INCFSZ	r0x1022,W
; >>> genarith.c:713:genPlus
;;	1109 rIdx = r0x104E 
	ADDWF	r0x101F,F
;; gen.c:2261:resultRemat *{*
;; ***	genPlus  547
;; genarith.c:548:genPlus *{*
;;	721 register type nRegs=1
;;	606
;; 	line = 554 result AOP_REG=r0x104F, size=1, left AOP_REG=r0x104F, size=1, right AOP_LIT=0x01, size=1
;; ***	pic14_getDataSize  1426
;; genarith.c:142:genPlusIncr *{*
;; ***	genPlusIncr  144
;; 	result AOP_REG, left AOP_REG, right AOP_LIT
;; 	genPlusIncr  156
; >>> genarith.c:168:genPlusIncr
;;	1109 rIdx = r0x104F 
	.line	102; "rfm12.c"	for(i=0;i<len;i++){
	INCF	r0x1020,F
;; gen.c:2261:resultRemat *{*
;; gen.c:2614:genGoto *{*
; >>> gen.c:2616:genGoto
;; ***	popGetLabel  key=23, label offset 8
	GOTO	_00131_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; NULL :(	3526
;; gen.c:3719:genAnd *{*
;; ***	genAnd  3720
;;	721 register type nRegs=2
;;	606
;; 	line = 3754 result AOP_REG=r0x104D, size=2, left AOP_REG=r0x104D, size=2, right AOP_LIT=0xff, size=2
; >>> gen.c:3887:genAnd
;;	1109 rIdx = r0x104E 
_00134_DS_
	.line	108; "rfm12.c"	chksum&=0x0ff;
	CLRF	r0x101F
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; NULL :(	3526
;; gen.c:3981:genOr *{*
;; ***	genOr  3982
;;	721 register type nRegs=2
;;	721 register type nRegs=2
;; 	line = 3988 result AOP_REG=r0x104D, size=2, left AOP_REG=r0x104D, size=2, right AOP_LIT=0x00, size=2
;; 	line = 4013 result AOP_REG=r0x104D, size=2, left AOP_REG=r0x104D, size=2, right AOP_LIT=0x00, size=2
; >>> gen.c:4148:genOr
	.line	111; "rfm12.c"	d=rfm12_spi16(0xb800|(chksum));
	MOVLW	0xb8
; >>> gen.c:4150:genOr
;;	1109 rIdx = r0x104E 
	IORWF	r0x101F,F
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
;;	721 register type nRegs=2
;;	721 register type nRegs=2
;; 	2079 left AOP_REG
;; gen.c:1324:mov2w_op *{*
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x104D 
	MOVF	r0x101E,W
;; 	2079 left AOP_REG
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
;; ***	mov2w  1356  offset=1
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x104E 
	MOVF	r0x101F,W
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
	.line	112; "rfm12.c"	if(0==rfm12_wait(RFM12_TOUT))
	MOVLW	0xe8
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0x03
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_wait
; >>> gen.c:2118:genCall
	CALL	_rfm12_wait
; >>> gen.c:2123:genCall
	PAGESEL	$
;;	721 register type nRegs=1
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x1048, size=1, right -=-, size=0
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1048 
	MOVWF	r0x101B
;; 	2138 left AOP_REG
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:3388:genCmpEq *{*
;; ***	genCmpEq  3389
;; ifx is non-null
;;	721 register type nRegs=1
;; 	line = 3400 result AOP_CRY=0x00, size=0, left AOP_LIT=0x00, size=1, right AOP_REG=r0x1048, size=1
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1048 
	MOVF	r0x101B,W
; >>> gen.c:3443:genCmpEq
	BTFSS	STATUS,2
; >>> gen.c:3445:genCmpEq
;; ***	popGetLabel  key=16, label offset 8
	GOTO	_00124_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2561:genRet *{*
;; ***	genRet  2563
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	.line	113; "rfm12.c"	return 0;
	MOVLW	0x00
; >>> gen.c:2587:genRet
;; ***	popGetLabel  key=27, label offset 8
	GOTO	_00135_DS_
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
_00124_DS_
	.line	115; "rfm12.c"	d=rfm12_spi16(0xb8aa);          // dummy bytes
	MOVLW	0xaa
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0xb8
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
	.line	116; "rfm12.c"	if(0==rfm12_wait(RFM12_TOUT))
	MOVLW	0xe8
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0x03
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_wait
; >>> gen.c:2118:genCall
	CALL	_rfm12_wait
; >>> gen.c:2123:genCall
	PAGESEL	$
;;	721 register type nRegs=1
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x1048, size=1, right -=-, size=0
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1048 
	MOVWF	r0x101B
;; 	2138 left AOP_REG
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:3388:genCmpEq *{*
;; ***	genCmpEq  3389
;; ifx is non-null
;;	721 register type nRegs=1
;; 	line = 3400 result AOP_CRY=0x00, size=0, left AOP_LIT=0x00, size=1, right AOP_REG=r0x1048, size=1
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1048 
	MOVF	r0x101B,W
; >>> gen.c:3443:genCmpEq
	BTFSS	STATUS,2
; >>> gen.c:3445:genCmpEq
;; ***	popGetLabel  key=18, label offset 8
	GOTO	_00126_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2561:genRet *{*
;; ***	genRet  2563
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	.line	117; "rfm12.c"	return 0;
	MOVLW	0x00
; >>> gen.c:2587:genRet
;; ***	popGetLabel  key=27, label offset 8
	GOTO	_00135_DS_
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
_00126_DS_
	.line	118; "rfm12.c"	d=rfm12_spi16(0xb8aa);
	MOVLW	0xaa
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0xb8
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
	.line	119; "rfm12.c"	if(0==rfm12_wait(RFM12_TOUT))
	MOVLW	0xe8
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0x03
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_wait
; >>> gen.c:2118:genCall
	CALL	_rfm12_wait
; >>> gen.c:2123:genCall
	PAGESEL	$
;;	721 register type nRegs=1
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x1048, size=1, right -=-, size=0
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1048 
	MOVWF	r0x101B
;; 	2138 left AOP_REG
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:3388:genCmpEq *{*
;; ***	genCmpEq  3389
;; ifx is non-null
;;	721 register type nRegs=1
;; 	line = 3400 result AOP_CRY=0x00, size=0, left AOP_LIT=0x00, size=1, right AOP_REG=r0x1048, size=1
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1048 
	MOVF	r0x101B,W
; >>> gen.c:3443:genCmpEq
	BTFSS	STATUS,2
; >>> gen.c:3445:genCmpEq
;; ***	popGetLabel  key=20, label offset 8
	GOTO	_00128_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2561:genRet *{*
;; ***	genRet  2563
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	.line	120; "rfm12.c"	return 0;
	MOVLW	0x00
; >>> gen.c:2587:genRet
;; ***	popGetLabel  key=27, label offset 8
	GOTO	_00135_DS_
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
_00128_DS_
	.line	121; "rfm12.c"	d=rfm12_spi16(0xb8aa);
	MOVLW	0xaa
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0xb8
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
	.line	122; "rfm12.c"	if(0==rfm12_wait(RFM12_TOUT))
	MOVLW	0xe8
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0x03
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_wait
; >>> gen.c:2118:genCall
	CALL	_rfm12_wait
; >>> gen.c:2123:genCall
	PAGESEL	$
;;	721 register type nRegs=1
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x1048, size=1, right -=-, size=0
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1048 
	MOVWF	r0x101B
;; 	2138 left AOP_REG
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:3388:genCmpEq *{*
;; ***	genCmpEq  3389
;; ifx is non-null
;;	721 register type nRegs=1
;; 	line = 3400 result AOP_CRY=0x00, size=0, left AOP_LIT=0x00, size=1, right AOP_REG=r0x1048, size=1
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1048 
	MOVF	r0x101B,W
; >>> gen.c:3443:genCmpEq
	BTFSS	STATUS,2
; >>> gen.c:3445:genCmpEq
;; ***	popGetLabel  key=22, label offset 8
	GOTO	_00130_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2561:genRet *{*
;; ***	genRet  2563
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	.line	123; "rfm12.c"	return 0;
	MOVLW	0x00
; >>> gen.c:2587:genRet
;; ***	popGetLabel  key=27, label offset 8
	GOTO	_00135_DS_
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
_00130_DS_
	.line	125; "rfm12.c"	d=rfm12_spi16(0x8208);          // Tx off
	MOVLW	0x08
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0x82
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
;; 	line = 5965 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:5720:genPackBits
	.line	127; "rfm12.c"	RB5=1;
	BSF	_PORTB_bits,5
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
;; 	2079 left AOP_LIT
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	.line	128; "rfm12.c"	delay_ms(100);
	MOVLW	0x64
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
	.line	129; "rfm12.c"	RB5=0;
	BCF	_PORTB_bits,5
;; gen.c:2261:resultRemat *{*
;; gen.c:2561:genRet *{*
;; ***	genRet  2563
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	.line	130; "rfm12.c"	return 1;
	MOVLW	0x01
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2435:genEndFunction *{*
;; ***	genEndFunction  2437
_00135_DS_
	RETURN	
; exit point of _rfm12_snd_msg
;; gen.c:6803:genpic14Code *{*

	New pBlock

code, dbName =C
;; Starting pCode block
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2283:genFunction *{*
;; ***	genFunction  2285 curr label offset=0previous max_key=0 
_rfm12_init	;Function start
; 2 exit points
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _TRISB_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_TRISB_bits
;; 	line = 5965 result AOP_PCODE=_TRISB_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_TRISB_bits
; >>> gen.c:5720:genPackBits
	.line	41; "rfm12.c"	nSEL_OUT();
	BCF	_TRISB_bits,3
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _TRISB_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_TRISB_bits
;; 	line = 5965 result AOP_PCODE=_TRISB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_TRISB_bits
; >>> gen.c:5720:genPackBits
	.line	42; "rfm12.c"	SDI_IN();
	BSF	_TRISB_bits,1
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _TRISB_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_TRISB_bits
;; 	line = 5965 result AOP_PCODE=_TRISB_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_TRISB_bits
; >>> gen.c:5720:genPackBits
	.line	43; "rfm12.c"	SDO_OUT();
	BCF	_TRISB_bits,2
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _TRISB_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_TRISB_bits
;; 	line = 5965 result AOP_PCODE=_TRISB_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_TRISB_bits
; >>> gen.c:5720:genPackBits
	.line	44; "rfm12.c"	SCK_OUT();
	BCF	_TRISB_bits,4
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _TRISB_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_TRISB_bits
;; 	line = 5965 result AOP_PCODE=_TRISB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_TRISB_bits
; >>> gen.c:5720:genPackBits
	.line	45; "rfm12.c"	nIRQ_IN();
	BSF	_TRISB_bits,0
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
	.line	48; "rfm12.c"	nSEL=1;
	BSF	_PORTB_bits,3
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
	.line	49; "rfm12.c"	SDO=1;
	BSF	_PORTB_bits,2
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
	.line	50; "rfm12.c"	SCK=0;
	BCF	_PORTB_bits,4
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
;; 	2079 left AOP_LIT
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	.line	52; "rfm12.c"	d=rfm12_spi16(0x80e7);          // El, Ef, 11.5pF, 868MHz band
	MOVLW	0xe7
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0x80
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
	.line	53; "rfm12.c"	d=rfm12_spi16(0x82d9);          // !er, !ebb, Et, Es, Ex, !eb, !ew, Dc
	MOVLW	0xd9
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0x82
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
	.line	54; "rfm12.c"	d=rfm12_spi16(0xa67c);          // 434,15MHz/868,3MHz
	MOVLW	0x7c
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0xa6
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
	.line	55; "rfm12.c"	d=rfm12_spi16(0xc647);          // 4,8kbps
	MOVLW	0x47
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0xc6
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
	.line	56; "rfm12.c"	d=rfm12_spi16(0x94a0);          // Vdi, fast, 134kHz, 0db,-103dbm
	MOVLW	0xa0
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0x94
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
	.line	57; "rfm12.c"	d=rfm12_spi16(0xc2ac);          // Al, !ml, Dig, Dqd4
	MOVLW	0xac
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0xc2
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
	.line	58; "rfm12.c"	d=rfm12_spi16(0xca80);          // fifo8, sync, !ff, Dr
	MOVLW	0x80
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0xca
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
	.line	59; "rfm12.c"	d=rfm12_spi16(0xca83);          // fifo8, sync, !ff, Dr
	MOVLW	0x83
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0xca
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
	.line	60; "rfm12.c"	d=rfm12_spi16(0xc483);          // @pwr, no restrict, !st, !fi, Oe, En
	MOVLW	0x83
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0xc4
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
	.line	62; "rfm12.c"	d=rfm12_spi16(0x9850);          // 90kHz, power - 0db
	MOVLW	0x50
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0x98
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
	.line	64; "rfm12.c"	d=rfm12_spi16(0xe000);          // not used (wake-up timer cmd)
	MOVLW	0x00
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0xe0
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
	.line	65; "rfm12.c"	d=rfm12_spi16(0xc800);          // not used (low duty-cycle cmd)
	MOVLW	0x00
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0xc8
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
	.line	67; "rfm12.c"	d=rfm12_spi16(0xc000);          // 1MHz, 2.2V (low bat detector and clk div)
	MOVLW	0x00
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0xc0
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
	.line	68; "rfm12.c"	d=rfm12_spi16(0x0000);          // read status word to clear fifos
	MOVLW	0x00
;; 	2079 left AOP_LIT
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	MOVLW	0x00
; >>> gen.c:2116:genCall
	PAGESEL	_rfm12_spi16
; >>> gen.c:2118:genCall
	CALL	_rfm12_spi16
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
	RETURN	
; exit point of _rfm12_init
;; gen.c:6803:genpic14Code *{*
