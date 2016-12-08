#include "stdafx.h"
#include <Windows.h>
#include <winternl.h>
#include <string>

using namespace std;

typedef int(*type_printf)(const char*, ...);

void *extractFunc(char*, PPEB_LDR_DATA);
void xor(char *, int);
int f24();
int f36();
int f28();
int f32();

char n1[] = { 0x4c, 0x4e, 0x55, 0x52, 0x48, 0x5a, 0x0 };



int _tmain(int argc, _TCHAR* argv[])
{
	char *peb;
	_asm{
		mov eax, fs:[30h]
			mov peb, eax
	}

	/*if (peb[2]){
	printf("Debug !\n");
	}
	else {
	printf("Not Debug\n");
	}

	if (peb[0x68] & 0x70){
	printf("Debug :(\n");
	}
	else {
	printf("No debug\n");
	}*/

	PPEB_LDR_DATA pld = ((PPEB)peb)->Ldr;

	type_printf f = (type_printf)extractFunc(n1,pld);
	f("Hello, world !\n");

	return 0;
}

void *extractFunc(char *name, PPEB_LDR_DATA pld){
	PLIST_ENTRY module0 = &(pld->InMemoryOrderModuleList);
	PLIST_ENTRY module = module0->Flink;
	module = module->Flink;

	
	int v36 = f36();
	xor(name, v36);
	int v28 = f28();
	int v24 = f24();
	xor(name, v24);
	int v32 = f32();

	while (module != module0){
		char *pointer = (char*)module - 2 * sizeof(PVOID);
		PLDR_DATA_TABLE_ENTRY pdte = (PLDR_DATA_TABLE_ENTRY)pointer;
		//printf("%S\n", pdte->FullDllName.Buffer);
		char *dll = (char*)pdte->DllBase;

		unsigned int pe = ((unsigned int*)(dll + v24+v36))[0];
		unsigned int te = ((unsigned int*)(dll + pe + 2*(v28+v32)))[0];
		char * debut_te = dll + te;
		unsigned int tableFonction = ((unsigned int*)(debut_te + v28))[0];
		xor(name, v28);
		unsigned int * tablePointer = (unsigned int*)(dll + tableFonction);

		unsigned int nameRVA = ((unsigned int *)(debut_te + v32))[0];
		xor(name, v32);
		unsigned int * tableName = (unsigned int *)(dll + nameRVA);

		unsigned int ordinalRVA = ((unsigned int *)(debut_te + v36))[0];
		xor(name, v36);
		short int *tableOrdinal = (short int *)(dll + ordinalRVA); // /!\ Important fact that it's a short int and NOT an unsigned int
		unsigned int nbNames = ((unsigned int *)(debut_te + v24))[0];
		xor(name, v24);
		unsigned int rva_printf = 0;


		for (int i = 0; i < nbNames; i++){
			if (strcmp(dll + tableName[i], name) == 0){
				//printf("function %d : %s\n", tableOrdinal[i], dll + tableName[i]);
				rva_printf = tablePointer[tableOrdinal[i]];
				return dll+rva_printf;
			}
		}

		module = module->Flink;
	}
	return NULL;
}

void xor(char *s, int n){
	int i = 0;
	while (s[i] != '\0'){
		s[i] = s[i] ^ n;
		i++;
	}
}

int f36(){
	return 36;
}

int f24(){
	return 24;
}

int f32(){
	return 32;
}

int f28(){
	return 28;
}