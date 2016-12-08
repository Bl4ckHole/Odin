#include "stdafx.h"
#include <Windows.h>
#include <winternl.h>

using namespace std;

typedef int(*type_printf)(const char*, ...);


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
	PLIST_ENTRY module0 = &pld->InMemoryOrderModuleList;
	PLIST_ENTRY module = module0->Flink;

	char *msvcr = NULL;

	while (module != module0){
		char *pointer = (char*)module - 2 * sizeof(PVOID);
		PLDR_DATA_TABLE_ENTRY pdte = (PLDR_DATA_TABLE_ENTRY)pointer;
		//printf("%S\n", pdte->FullDllName.Buffer);

		if (wcscmp(L"C:\\WINDOWS\\SYSTEM32\\MSVCR120D.dll", pdte->FullDllName.Buffer) == 0){
			msvcr = (char*)pdte->DllBase;
			break;
		}
		module = module->Flink;
	}

	if (msvcr == NULL){
		printf("Failed to find msvcr pointer\n");
		return -1;
	}

	unsigned int pe = ((unsigned int*)(msvcr + 60))[0];
	unsigned int te = ((unsigned int*)(msvcr + pe + 120))[0];
	char * debut_te = msvcr + te;
	unsigned int tableFonction = ((unsigned int*)(debut_te + 28))[0];
	unsigned int * tablePointer = (unsigned int*)(msvcr + tableFonction);

	unsigned int nameRVA = ((unsigned int *)(debut_te + 32))[0];
	unsigned int * tableName = (unsigned int *)(msvcr + nameRVA);

	unsigned int ordinalRVA = ((unsigned int *)(debut_te + 36))[0];
	short int *tableOrdinal = (short int *)(msvcr + ordinalRVA); // /!\ Important fact that it's a short int and NOT an unsigned int
	unsigned int nbFunc = ((unsigned int *)(debut_te + 24))[0];
	unsigned int rva_printf = 0;
	

	for (int i = 0; i < nbFunc; i++){
		if (strcmp(msvcr + tableName[i], "printf") == 0){
			//printf("function %d : %s\n", tableOrdinal[i], msvcr + tableName[i]);
			rva_printf = tablePointer[tableOrdinal[i]];
		}
	}

	type_printf f = (type_printf)(msvcr + rva_printf);
	f("Hello, world !\n");


	return 0;
}