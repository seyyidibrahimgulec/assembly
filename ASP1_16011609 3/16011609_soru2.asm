        PAGE 60,80
        TITLE ornek____
        
STACKSG SEGMENT PARA STACK 'STACK'
        DW 32 DUP(?)
STACKSG ENDS

DATASG  SEGMENT PARA 'DATA'
CR	EQU 13
LF	EQU 10
MSG1	DB 'Dizinin eleman sayisini giriniz: ', 0
MSG2	DB CR, LF, 'Eleman giriniz :', 0
HATA	DB CR, LF, 'Dikkat sayi vermediniz yeniden giris yapiniz.!!!!', 0
HATA2	DB CR, LF, 'Dikkat girdiginiz sayi [-128,127] araasinda degil!!', 0
SIRALI	DB CR, LF, 'Siralanmis dizi :', 0
ILKHAL	DB CR, LF, 'Girdiginiz dizi :', 0
BOSLUK	DB CR, LF, 44, 0
FIRST	DW ?
LAST	DW ?
ESAYISI	DB ?
DIZI	DB 100 DUP(?)
DATASG ENDS

CODESG  SEGMENT PARA 'CODE'
        ASSUME CS:CODESG, DS:DATASG, SS:STACKSG

ANA	PROC FAR
        PUSH DS
        XOR AX,AX
        PUSH AX

        MOV AX, DATASG
        MOV DS, AX

;--------------------------------
;	OKUMA ISLEMLERI		|
;--------------------------------
	MOV AX, OFFSET MSG1
	CALL PUT_STR
	CALL GETN
	MOV ESAYISI, AL
	MOV CX, AX
	LEA SI, DIZI

L1:	MOV AX, OFFSET MSG2
	CALL PUT_STR
	CALL GETN
	CMP AX, 127
	JG H1
	CMP AX, -128
	JL H1
	MOV [SI], AL
	INC SI
	LOOP L1
	JMP HATA_ATLA
;----------------------
;	  HATA        |
;----------------------
H1:	MOV AX, OFFSET HATA2
	CALL PUT_STR
	JMP L1

;------------------------------------
;	DIZIYI EKRANA YAZDIRMA 	    |
;------------------------------------
HATA_ATLA:
	XOR CX, CX
	MOV CL, ESAYISI
	MOV AX, OFFSET ILKHAL 
	CALL PUT_STR
	LEA SI, DIZI
L2:	MOV AL, [SI]
	CBW 
	CALL PUTN
	CALL PUTC
	INC SI
	LOOP L2


;-----------------------
;	QUICKSORT      |  
;-----------------------
	XOR AX, AX
	MOV AL, ESAYISI
	DEC AX
	
	LEA SI, DIZI; i
	MOV DI, SI
	ADD DI, AX; j
	MOV FIRST, SI
	MOV LAST, DI
	CALL QUICK

;------------------------------------
;	DIZIYI EKRANA YAZDIRMA 	    |
;------------------------------------
	XOR CX, CX
	MOV CL, ESAYISI
	MOV AX, OFFSET SIRALI 
	CALL PUT_STR
	LEA SI, DIZI
L3:	MOV AL, [SI] 
	CBW
	CALL PUTN
	CALL PUTC
	INC SI
	LOOP L3


        RETF
ANA	ENDP

GETC	PROC NEAR
	MOV AH, 1h
	INT 21H
	RET
GETC	ENDP

PUTC	PROC NEAR
	PUSH AX
	PUSH DX
	MOV DL, AL
	MOV AH, 2
	INT 21H
	POP DX
	POP AX
	RET
PUTC	ENDP

GETN	PROC NEAR
	PUSH BX
	PUSH CX
	PUSH DX
GETN_START:
	MOV DX, 1
	XOR BX, BX
	XOR CX, CX
NEW:
	CALL GETC
	CMP AL, CR
	JE FIN_READ
	CMP AL, '-'
	JNE CTRL_NUM
NEGATIVE:
	MOV DX, -1
	JMP NEW
CTRL_NUM:
	CMP AL, '0'
	JB error
	CMP AL, '9'
	JA error
	SUB AL, '0'
	MOV BL, AL
	MOV AX, 10
	PUSH DX
	MUL CX
	POP DX
	MOV CX, AX
	ADD CX, BX
	JMP NEW
ERROR:
	MOV AX, OFFSET HATA
	CALL PUT_STR
	JMP GETN_START
FIN_READ:
	MOV AX, CX
	CMP DX, 1
	JE FIN_GETN
	NEG AX
FIN_GETN:
	POP DX
	POP CX
	POP BX
	RET
GETN	ENDP

PUTN	PROC NEAR
	PUSH CX
	PUSH DX
	XOR DX, DX
	PUSH DX
	

	MOV CX, 10
	CMP AX, 0
	JGE CALC_DIGITS
	NEG AX
	PUSH AX
	MOV AL, '-'
	CALL PUTC
	POP AX
CALC_DIGITS:
	DIV CX
	ADD DX, '0'
	PUSH DX
	XOR DX, DX
	CMP AX, 0
	JNE CALC_DIGITS
DISP_LOOP:
	POP AX
	CMP AX, 0
	JE END_DISP_LOOP
	CALL PUTC
	JMP DISP_LOOP
END_DISP_LOOP:
	POP DX
	POP CX
	RET
PUTN	ENDP

PUT_STR	PROC NEAR
	PUSH BX
	MOV BX, AX
	MOV AL, BYTE PTR[BX]
PUT_LOOP:
	CMP AL, 0
	JE PUT_FIN
	CALL PUTC
	INC BX
	MOV AL, BYTE PTR[BX]
	JMP PUT_LOOP
PUT_FIN:
	POP BX
	RET
PUT_STR	ENDP

QUICK	PROC NEAR
	MOV SI, FIRST
	MOV DI, LAST
	MOV BX, SI
	CMP SI, DI
	JAE SON

DONGU1:	MOV CL, [SI]
	MOV CH, [BX]
	CMP CL, CH
	JG ATLA1
	MOV DX, LAST 	
	CMP SI, DX
	JAE ATLA1
	INC SI
	JMP DONGU1
ATLA1:	MOV CL, [DI]
	MOV CH, [BX]
	CMP CL, CH
	JLE ATLA2
	DEC DI
	JMP ATLA1
ATLA2:	CMP SI, DI
	JAE ATLA3
	MOV CL, [SI]
	MOV CH, [DI]
	MOV [SI], CH
	MOV [DI], CL
ATLA3:	CMP SI, DI
	JB DONGU1 
	MOV CL, [BX]
	MOV CH, [DI]
	MOV [BX], CH
	MOV [DI], CL
	
	PUSH DI 
	MOV DX, LAST
	PUSH DX
	DEC DI
	MOV LAST, DI
	CALL QUICK
	POP DX
	MOV LAST, DX
	POP DI
	INC DI
	MOV FIRST, DI
	CALL QUICK

SON:	RET
QUICK	ENDP

CODESG  ENDS
        END ANA