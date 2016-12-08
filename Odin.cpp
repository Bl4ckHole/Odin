#include "stdafx.h"
#include <Windows.h>
#include <winternl.h>
#include <string>

using namespace std;

typedef int(*type_printf)(const char*, ...);

void *extractFunc(string, PPEB_LDR_DATA);


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

	type_printf f = (type_printf)extractFunc("printf",pld);
	f("Hello, world !\n");

	return 0;
}

void *extractFunc(string name, PPEB_LDR_DATA pld){
	PLIST_ENTRY module0 = &(pld->InMemoryOrderModuleList);
	PLIST_ENTRY module = module0->Flink;
	module = module->Flink;

	while (module != module0){
		char *pointer = (char*)module - 2 * sizeof(PVOID);
		PLDR_DATA_TABLE_ENTRY pdte = (PLDR_DATA_TABLE_ENTRY)pointer;
		//printf("%S\n", pdte->FullDllName.Buffer);
		char *dll = (char*)pdte->DllBase;

		unsigned int pe = ((unsigned int*)(dll + 60))[0];
		unsigned int te = ((unsigned int*)(dll + pe + 120))[0];
		char * debut_te = dll + te;
		unsigned int tableFonction = ((unsigned int*)(debut_te + 28))[0];
		unsigned int * tablePointer = (unsigned int*)(dll + tableFonction);

		unsigned int nameRVA = ((unsigned int *)(debut_te + 32))[0];
		unsigned int * tableName = (unsigned int *)(dll + nameRVA);

		unsigned int ordinalRVA = ((unsigned int *)(debut_te + 36))[0];
		short int *tableOrdinal = (short int *)(dll + ordinalRVA); // /!\ Important fact that it's a short int and NOT an unsigned int
		unsigned int nbNames = ((unsigned int *)(debut_te + 24))[0];
		unsigned int rva_printf = 0;


		for (int i = 0; i < nbNames; i++){
			if (strcmp(dll + tableName[i], name.c_str()) == 0){
				//printf("function %d : %s\n", tableOrdinal[i], dll + tableName[i]);
				rva_printf = tablePointer[tableOrdinal[i]];
				return dll+rva_printf;
			}
		}

		module = module->Flink;
	}
	return NULL;
}