#include "stdafx.h"
#include <Windows.h>
#include <winternl.h>
#include <string>
#include <iostream>

using namespace std;

typedef int(*type_printf)(const char*, ...);

std::string base64_encode(unsigned char const*, unsigned int len);
std::string base64_decode(std::string const& s);
void *extractFunc(char*, PPEB_LDR_DATA);
void xor(char *, int);
int f24();
int f36();
int f28();
int f32();
int fibo(int);
int triangular(int);
int sumpow(int);
int syracuse(int,int);
int penta(int);


char n1[] = { 0x5f, 0x74, 0x76, 0x4c, 0x5e, 0x52, 0x6e, 0x51, 0x0 };

string super_string = "Alright... I know, debugging some obfuscated code is funny... Haha.";




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
	f(base64_decode("SGVsbG8sIHdvcmxkICEK").c_str());

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
		xor(name, v36);
		unsigned int * tableName = (unsigned int *)(dll + nameRVA);

		unsigned int ordinalRVA = ((unsigned int *)(debut_te + v36))[0];
		xor(name, v32);
		short int *tableOrdinal = (short int *)(dll + ordinalRVA); // /!\ Important fact that it's a short int and NOT an unsigned int
		unsigned int nbNames = ((unsigned int *)(debut_te + v24))[0];
		xor(name, v24); 
		unsigned int rva_printf = 0;

		
		for (int i = 0; i < nbNames; i++){
			if (strcmp(dll + tableName[i], base64_decode((std::string) name).c_str()) == 0){
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



static inline bool is_base64(unsigned char c) {
	return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
	std::string ret;
	static const std::string base64_chars =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	while (in_len--) {
		char_array_3[i++] = *(bytes_to_encode++);
		if (i == 3) {
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i <4); i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while ((i++ < 3))
			ret += '=';
	}
	return ret;

}

std::string base64_decode(std::string const& encoded_string) {
	static const std::string base64_chars =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";
	int in_len = encoded_string.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];
	std::string ret;

	while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
		char_array_4[i++] = encoded_string[in_]; in_++;
		if (i == 4) {
			for (i = 0; i <4; i++)
				char_array_4[i] = base64_chars.find(char_array_4[i]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				ret += char_array_3[i];
			i = 0;
		}
	}

	if (i) {
		for (j = i; j <4; j++)
			char_array_4[j] = 0;

		for (j = 0; j <4; j++)
			char_array_4[j] = base64_chars.find(char_array_4[j]);

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
	}

	return ret;
}




int fibo(int n) {
	if (n)
		return n*fibo(n-1);
	return 1;
}

int triangular(int n) {
	int res=0;
	for (int i = res;i < n;res += i++);
	return res;
}

int sumpow(int n) {
	int res=0;
	for(int i=res;i<n;res+=pow(++i,i));
	return res;
}

int syracuse(int n, int etape){
	if (n == 1) 
		return etape;
	if (n%2)
		return syracuse(3*n+1,++etape);
	return syracuse(n/2,++etape);
}

int penta(int n) {
	return n*(3*n-1)/2;
}



int f36(){
	return syracuse(triangular(sumpow(3)-1),1);
}

int f24(){
	return syracuse(penta(triangular(fibo(4)-4)+2), 1) / 2;
}

int f32(){
	return syracuse(triangular(fibo(5)),1);
}

int f28(){
	return syracuse(triangular(penta(19) / 7),1);
}