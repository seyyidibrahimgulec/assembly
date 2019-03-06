#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include "image_processing.cpp"


using namespace std;

void sagaDondur(short n, int resim);
void solaDondur(short n, int resim);

int main(void) {
	int M, N, Q, i, j, k;
	bool type;
	int efile, islem;
	char resimadi[100], sonek[10];
	do {
		printf("Islem yapilacak resmin yolunu (path) giriniz:\n-> ");
		scanf("%s", &resimadi);
		system("CLS");
		efile = readImageHeader(resimadi, N, M, Q, type);
	} while (efile > 1);
	printf("%s\n", resimadi);
	int** resim = resimOku(resimadi);

	short *resimdizi;
	resimdizi = (short*) malloc(N*M * sizeof(short));

	for (i = 0; i < N; i++) 
		for (j = 0; j < M; j++) 
			resimdizi[i*N + j] = (short) resim[i][j];

	int resimadres = (int) resimdizi;

	do {
		system("CLS");
		printf("\t     ISLEMLER\n");
		printf("------------------------------------\n");
		printf("1)  Resmi saga dondur\n");
		printf("2)  Resmi sola dondur\n");
		printf("0)  Cikis\n\n");
		printf("\"%s\" yolundaki resim icin yapilacak islemi seciniz\n-> ", resimadi);
		scanf("%d", &islem);
	} while (islem > 2 || islem < 0);

	switch (islem) {
		case 0:
			exit(0);
		case 1:
			sagaDondur(N, resimadres);
			strcpy(sonek, "_sag.pgm");
			break;
		case 2:
			solaDondur(N , resimadres);
			strcpy(sonek, "_sol.pgm");
			break;
		default:
			strcpy(sonek, "_orj.pgm");
			break;
	}

	for (k = 0; k < N * M; k++) {
		j = k % N;
		i = k / N;
		resim[i][j] = (int)resimdizi[k];
	}
	
	string::size_type pos = string(resimadi).find_last_of(".");
	resimadi[pos] = '\0';
	strcat(resimadi, sonek);
	resimYaz(resimadi, resim, N, M, Q);
	printf("\nIslem basariyla tamamlandi :)\n\"%s\" yolunda resim olusturuldu.\n\n", resimadi);
	system("PAUSE");
	return 0;
}

void sagaDondur(short n, int resim) {
	//KODUNUZU BURADAN BASLAYARAK YAZINIZ
	__asm {
		XOR EDX,EDX
		MOV AX,n
		MOV BX,2
		DIV BX
		XOR ECX, ECX
		XOR ESI, ESI
		MOV CX,AX
		XOR EDI, EDI
		MOV EDI, resim
		XOR EAX, EAX
		XOR EBX, EBX
		XOR EDX, EDX
	L2: PUSH CX
		XOR EBX, EBX
		MOV EBX, EAX
		XOR ECX, ECX
		MOV CX, n
		SUB CX, AX
		DEC CX
	L1: PUSH CX
		PUSH EAX
		XOR ECX, ECX
		MOV CX, n
		MUL ECX
		ADD EAX, EBX
		ADD EAX, EAX
		MOV CX, WORD PTR[EDI+EAX]
		POP EAX

		PUSH EAX
		MOV EAX,EBX
		XOR ESI, ESI
		MOV SI, n
		MUL ESI
		MOV ESI, EAX
		XOR EAX, EAX
		MOV AX, n
		ADD ESI, EAX
		DEC ESI
		POP EAX
		SUB ESI, EAX
		ADD ESI, ESI
		MOV DX, WORD PTR[EDI+ESI]
		MOV WORD PTR[EDI+ESI], CX
		MOV CX, DX

		PUSH EAX
		XOR ESI, ESI
		MOV SI, n
		DEC ESI
		SUB ESI, EAX
		XOR EAX, EAX
		MOV AX, n
		MUL ESI
		MOV ESI, EAX
		XOR EAX, EAX
		MOV AX, n
		ADD ESI, EAX
		DEC ESI
		SUB ESI, EBX
		ADD ESI, ESI
		MOV DX, WORD PTR[EDI+ESI]
		MOV WORD PTR[EDI+ESI], CX
		MOV CX, DX
		POP EAX

		PUSH EAX
		XOR ESI, ESI
		MOV SI, n
		DEC ESI
		SUB ESI, EBX
		XOR EAX, EAX
		MOV AX, n
		MUL ESI
		MOV ESI, EAX
		POP EAX
		ADD ESI, EAX
		ADD ESI, ESI
		MOV DX, WORD PTR[EDI+ESI]
		MOV WORD PTR[EDI+ESI], CX
		MOV CX, DX


		PUSH EAX
		PUSH EBX
		XOR EBX, EBX
		MOV BX, n
		MUL EBX
		POP EBX
		ADD EAX,EBX
		ADD EAX,EAX
		MOV WORD PTR[EDI+EAX], CX
		POP EAX



		INC EBX
		POP CX
		CMP BX, CX
		JB L1
		POP CX
		INC EAX
		CMP AX,CX
		JB L2
	}
	//KODUNUZU YAZMAYI BURADA BITIRINIZ
}

void solaDondur(short n, int resim) {
	//KODUNUZU BURADAN BASLAYARAK YAZINIZ
	__asm {
		XOR EDX,EDX
		MOV AX,n
		MOV BX,2
		DIV BX
		XOR ECX, ECX
		XOR ESI, ESI
		MOV CX,AX
		XOR EDI, EDI
		MOV EDI, resim
		XOR EAX, EAX
		XOR EBX, EBX
		XOR EDX, EDX
	L2: PUSH CX
		XOR EBX, EBX
		MOV EBX, EAX
		XOR ECX, ECX
		MOV CX, n
		SUB CX, AX
		DEC CX
	L1: PUSH CX
		PUSH EAX
		XOR ECX, ECX
		MOV CX, n
		MUL ECX
		ADD EAX, EBX
		ADD EAX, EAX
		MOV CX, WORD PTR[EDI+EAX]
		POP EAX
		PUSH EAX
		XOR EAX, EAX
		XOR ESI, ESI
		MOV AX, n
		MOV SI, n
		DEC SI
		SUB SI, BX
		MUL ESI
		MOV ESI, EAX
		POP EAX
		ADD ESI, EAX
		ADD ESI, ESI
		MOV DX, WORD PTR[EDI+ESI]
		MOV WORD PTR[EDI+ESI], CX
		MOV CX, DX
		PUSH EAX
		XOR ESI, ESI
		MOV SI, n
		DEC ESI
		SUB ESI, EAX
		XOR EAX, EAX
		MOV AX, n
		MUL ESI
		MOV ESI, EAX
		XOR EAX, EAX
		MOV AX, n
		ADD ESI, EAX
		DEC ESI
		SUB ESI, EBX
		ADD ESI, ESI
		MOV DX, WORD PTR[EDI+ESI]
		MOV WORD PTR[EDI+ESI], CX
		MOV CX, DX
		POP EAX
		PUSH EAX
		XOR EAX, EAX
		MOV AX, n
		MUL EBX
		MOV ESI, EAX
		XOR EAX, EAX
		MOV AX, n
		ADD ESI, EAX
		DEC ESI
		POP EAX
		SUB ESI, EAX
		ADD ESI, ESI
		MOV DX, WORD PTR[EDI+ESI]
		MOV WORD PTR[EDI+ESI], CX
		MOV CX, DX
		PUSH EAX
		PUSH EBX
		XOR EBX, EBX
		MOV BX, n
		MUL EBX
		POP EBX
		ADD EAX, EBX
		MOV ESI, EAX
		ADD ESI, ESI
		POP EAX
		MOV WORD PTR[EDI+ESI], CX
		INC EBX
		POP CX
		CMP BX, CX
		JB L1
		POP CX
		INC EAX
		CMP AX,CX
		JB L2
	}
	//KODUNUZU YAZMAYI BURADA BITIRINIZ
}