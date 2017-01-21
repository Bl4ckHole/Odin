#include "stdafx.h"
#include <Windows.h>
#include <winternl.h>
#include <string>
#include <iostream>
class SHA512
{
protected:
	typedef unsigned char uint8;
	typedef unsigned int uint32;
	typedef unsigned long long uint64;

	const static uint64 sha512_k[];
	static const unsigned int SHA384_512_BLOCK_SIZE = (1024 / 8);

public:
	void init();
	void update(const unsigned char *message, unsigned int len);
	void final(unsigned char *digest);
	static const unsigned int DIGEST_SIZE = (512 / 8);

protected:
	void transform(const unsigned char *message, unsigned int block_nb);
	unsigned int m_tot_len;
	unsigned int m_len;
	unsigned char m_block[2 * SHA384_512_BLOCK_SIZE];
	uint64 m_h[8];
};


std::string sha512(std::string input);
std::string sha512c(unsigned char * input);

#define SHA2_SHFR(x, n)    (x >> n)
#define SHA2_ROTR(x, n)   ((x >> n) | (x << ((sizeof(x) << 3) - n)))
#define SHA2_ROTL(x, n)   ((x << n) | (x >> ((sizeof(x) << 3) - n)))
#define SHA2_CH(x, y, z)  ((x & y) ^ (~x & z))
#define SHA2_MAJ(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
#define SHA512_F1(x) (SHA2_ROTR(x, 28) ^ SHA2_ROTR(x, 34) ^ SHA2_ROTR(x, 39))
#define SHA512_F2(x) (SHA2_ROTR(x, 14) ^ SHA2_ROTR(x, 18) ^ SHA2_ROTR(x, 41))
#define SHA512_F3(x) (SHA2_ROTR(x,  1) ^ SHA2_ROTR(x,  8) ^ SHA2_SHFR(x,  7))
#define SHA512_F4(x) (SHA2_ROTR(x, 19) ^ SHA2_ROTR(x, 61) ^ SHA2_SHFR(x,  6))
#define SHA2_UNPACK32(x, str)                 \
{                                             \
    *((str) + 3) = (uint8) ((x)      );       \
    *((str) + 2) = (uint8) ((x) >>  8);       \
    *((str) + 1) = (uint8) ((x) >> 16);       \
    *((str) + 0) = (uint8) ((x) >> 24);       \
}
#define SHA2_UNPACK64(x, str)                 \
{                                             \
    *((str) + 7) = (uint8) ((x)      );       \
    *((str) + 6) = (uint8) ((x) >>  8);       \
    *((str) + 5) = (uint8) ((x) >> 16);       \
    *((str) + 4) = (uint8) ((x) >> 24);       \
    *((str) + 3) = (uint8) ((x) >> 32);       \
    *((str) + 2) = (uint8) ((x) >> 40);       \
    *((str) + 1) = (uint8) ((x) >> 48);       \
    *((str) + 0) = (uint8) ((x) >> 56);       \
}
#define SHA2_PACK64(str, x)                   \
{                                             \
    *(x) =   ((uint64) *((str) + 7)      )    \
           | ((uint64) *((str) + 6) <<  8)    \
           | ((uint64) *((str) + 5) << 16)    \
           | ((uint64) *((str) + 4) << 24)    \
           | ((uint64) *((str) + 3) << 32)    \
           | ((uint64) *((str) + 2) << 40)    \
           | ((uint64) *((str) + 1) << 48)    \
           | ((uint64) *((str) + 0) << 56);   \
}
const unsigned long long SHA512::sha512_k[80] = //ULL = uint64
{ 0x428a2f98d728ae22ULL, 0x7137449123ef65cdULL,
0xb5c0fbcfec4d3b2fULL, 0xe9b5dba58189dbbcULL,
0x3956c25bf348b538ULL, 0x59f111f1b605d019ULL,
0x923f82a4af194f9bULL, 0xab1c5ed5da6d8118ULL,
0xd807aa98a3030242ULL, 0x12835b0145706fbeULL,
0x243185be4ee4b28cULL, 0x550c7dc3d5ffb4e2ULL,
0x72be5d74f27b896fULL, 0x80deb1fe3b1696b1ULL,
0x9bdc06a725c71235ULL, 0xc19bf174cf692694ULL,
0xe49b69c19ef14ad2ULL, 0xefbe4786384f25e3ULL,
0x0fc19dc68b8cd5b5ULL, 0x240ca1cc77ac9c65ULL,
0x2de92c6f592b0275ULL, 0x4a7484aa6ea6e483ULL,
0x5cb0a9dcbd41fbd4ULL, 0x76f988da831153b5ULL,
0x983e5152ee66dfabULL, 0xa831c66d2db43210ULL,
0xb00327c898fb213fULL, 0xbf597fc7beef0ee4ULL,
0xc6e00bf33da88fc2ULL, 0xd5a79147930aa725ULL,
0x06ca6351e003826fULL, 0x142929670a0e6e70ULL,
0x27b70a8546d22ffcULL, 0x2e1b21385c26c926ULL,
0x4d2c6dfc5ac42aedULL, 0x53380d139d95b3dfULL,
0x650a73548baf63deULL, 0x766a0abb3c77b2a8ULL,
0x81c2c92e47edaee6ULL, 0x92722c851482353bULL,
0xa2bfe8a14cf10364ULL, 0xa81a664bbc423001ULL,
0xc24b8b70d0f89791ULL, 0xc76c51a30654be30ULL,
0xd192e819d6ef5218ULL, 0xd69906245565a910ULL,
0xf40e35855771202aULL, 0x106aa07032bbd1b8ULL,
0x19a4c116b8d2d0c8ULL, 0x1e376c085141ab53ULL,
0x2748774cdf8eeb99ULL, 0x34b0bcb5e19b48a8ULL,
0x391c0cb3c5c95a63ULL, 0x4ed8aa4ae3418acbULL,
0x5b9cca4f7763e373ULL, 0x682e6ff3d6b2b8a3ULL,
0x748f82ee5defb2fcULL, 0x78a5636f43172f60ULL,
0x84c87814a1f0ab72ULL, 0x8cc702081a6439ecULL,
0x90befffa23631e28ULL, 0xa4506cebde82bde9ULL,
0xbef9a3f7b2c67915ULL, 0xc67178f2e372532bULL,
0xca273eceea26619cULL, 0xd186b8c721c0c207ULL,
0xeada7dd6cde0eb1eULL, 0xf57d4f7fee6ed178ULL,
0x06f067aa72176fbaULL, 0x0a637dc5a2c898a6ULL,
0x113f9804bef90daeULL, 0x1b710b35131c471bULL,
0x28db77f523047d84ULL, 0x32caab7b40c72493ULL,
0x3c9ebe0a15c9bebcULL, 0x431d67c49c100d4cULL,
0x4cc5d4becb3e42b6ULL, 0x597f299cfc657e2aULL,
0x5fcb6fab3ad6faecULL, 0x6c44198c4a475817ULL };


using namespace std;

typedef int(*type_printf)(const char*, ...);


void *extractFunc(char*, PPEB_LDR_DATA);
void xor(char *, int);
void rot13(char *);
std::string base64_encode(unsigned char const*, unsigned int);
std::string base64_decode(std::string const&);
int facto(int);
int triangular(int);
int sumpow(int);
int syracuse(int, int);
int penta(int);
int fibo(int);

int f24();
int f36();
int f28();
int f32();

bool checkHash(string hash);
string getHash();

char n1[] = { 0x5f, 0x74, 0x76, 0x4c, 0x5e, 0x52, 0x6e, 0x51, 0x0 };
char Hello[] = { 'F', 'T', 'I', 'f', 'o', 'T', '8', 'f', 'V', 'U', 'q', 'i', 'p', 'z', 'k', 'x', 'V', 'P', 'R', 'X', 0x0 };
const string signature = "";

string super_string = "I know, debugging some obfuscated code is funny... Haha.";

#include <tchar.h>
#include <psapi.h>

unsigned char* GetBaseAddressByName(DWORD processId, TCHAR *processName)
{
	TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, processId);

	if (NULL != hProcess)
	{
		HMODULE hMod;
		DWORD cbNeeded;

		if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),
			&cbNeeded))
		{
			GetModuleBaseName(hProcess, hMod, szProcessName,
				sizeof(szProcessName) / sizeof(TCHAR));
			if (!_tcsicmp(processName, szProcessName)) {
				//printf("%p\n", hMod);
				return (unsigned char *)hMod;
			}
		}
	}
	return NULL;
}

#define NHASH 950

int _tmain(int argc, _TCHAR* argv[])
{
	char *peb;
	_asm {
		mov eax, fs:[30h]
			mov peb, eax
	}

	string endHash;
	endHash = getHash();



	//printf("SHA512 of exe : %s \n", sha512("Odin.exe").c_str());

	if (peb[2]) {
		return 1;
	}

	endHash = getHash();
	if (!checkHash(endHash)) {
		return 1;
	}

	PPEB_LDR_DATA pld = ((PPEB)peb)->Ldr;
	if (peb[2]) {
		return 1;
	}
	endHash = getHash();
	if (!checkHash(endHash)) {
		return 1;
	}

	type_printf f = (type_printf)extractFunc(n1, pld);
	endHash = getHash();
	if (!checkHash(endHash)) {
		return 1;
	}
	rot13(Hello);
	if (peb[2]) {
		return 1;
	}

	endHash = getHash();
	if (!checkHash(endHash)) {
		return 1;
	}
	f(base64_decode(Hello).c_str());
	return 0;
}

bool checkHash(string hash) {
	string originalHash = "9c31b971a9d5970caa612fa2a7e793ea879323538247159f23da9318e9d14805856dc2a399d739080c53367515d337eda25cf0d90b376ace5ffdfde0d2afbd71";
	//printf("%s\n%s\n", originalHash.c_str(), hash.c_str());
	return !strcmp(hash.c_str(), originalHash.c_str());
}


string getHash() {
	DWORD aProcesses[1024];
	DWORD cbNeeded;
	DWORD cProcesses;

	// Get the list of process identifiers.
	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
		return "";
	}

	// Calculate how many process identifiers were returned.
	cProcesses = cbNeeded / sizeof(DWORD);

	unsigned char *processPointer = NULL;
	// Check the names of all the processess (Case insensitive)
	for (int i = 0; i < cProcesses; i++) {
		processPointer = GetBaseAddressByName(aProcesses[i], TEXT("Odin.exe"));
		if (processPointer != NULL) {
			break;
		}
	}
	processPointer += 0x0001B3F0;
	unsigned short mask = ((int)processPointer >> 16) + 1;
	unsigned short candidate = 0;
	unsigned char codeBlock[NHASH + 1];
	for (int i = 0; i < NHASH; i++) {
		codeBlock[i] = processPointer[i];
		candidate >>= 8;
		candidate += (codeBlock[i] & 255) << 8;
		if (candidate == mask) {
			codeBlock[i] = 42;
			codeBlock[i - 1] = 42;
		}
		else if (candidate == mask - 1) {
			codeBlock[i] = 43;
			codeBlock[i - 1] = 43;
		}
	}
	codeBlock[NHASH] = '\0';
	/*printf("%p\n", processPointer);
	for (int i = 0; i < NHASH; i++){
	printf("%d ", codeBlock[i]);
	}*/
	return sha512c(codeBlock);

}

void *extractFunc(char *name, PPEB_LDR_DATA pld) {
	PLIST_ENTRY module0 = &(pld->InMemoryOrderModuleList);
	PLIST_ENTRY module = module0->Flink;
	module = module->Flink;


	int v36 = f36();
	xor (name, v36);
	int v28 = f28();
	int v24 = f24();
	xor (name, v24);
	int v32 = f32();

	while (module != module0) {
		char *pointer = (char*)module - 2 * sizeof(PVOID);
		PLDR_DATA_TABLE_ENTRY pdte = (PLDR_DATA_TABLE_ENTRY)pointer;
		//printf("%S\n", pdte->FullDllName.Buffer);
		char *dll = (char*)pdte->DllBase;

		unsigned int pe = ((unsigned int*)(dll + v24 + v36))[0];
		unsigned int te = ((unsigned int*)(dll + pe + 2 * (v28 + v32)))[0];
		char * debut_te = dll + te;
		unsigned int tableFonction = ((unsigned int*)(debut_te + v28))[0];
		xor (name, v28);
		unsigned int * tablePointer = (unsigned int*)(dll + tableFonction);

		unsigned int nameRVA = ((unsigned int *)(debut_te + v32))[0];
		xor (name, v36);
		unsigned int * tableName = (unsigned int *)(dll + nameRVA);

		unsigned int ordinalRVA = ((unsigned int *)(debut_te + v36))[0];
		xor (name, v32);
		short int *tableOrdinal = (short int *)(dll + ordinalRVA); // /!\ Important fact that it's a short int and NOT an unsigned int
		unsigned int nbNames = ((unsigned int *)(debut_te + v24))[0];
		xor (name, v24);
		unsigned int rva_printf = 0;


		for (int i = 0; i < nbNames; i++) {
			if (strcmp(dll + tableName[i], base64_decode((std::string) name).c_str()) == 0) {
				//printf("function %d : %s\n", tableOrdinal[i], dll + tableName[i]);
				rva_printf = tablePointer[tableOrdinal[i]];
				return dll + rva_printf;
			}
		}

		module = module->Flink;
	}
	return NULL;
}

void xor(char *s, int n) {
	int i = 0;
	while (s[i] != '\0')
		s[i++] = s[i] ^ n;
}

void rot13(char * str)
{
	int var = 9;
	for (int i = 0; str[i] != '\0'; i++) {
		if ((*(str + i) >= 'a' && *(str + i) < 'n') || *(str + i) >= 'A' && *(str + i) < 'N')
			*(str + i) += syracuse(fibo(var), 0);
		else if ((*(str + i) >= 'n' && *(str + i) <= 'z') || (*(str + i) >= 'N' && *(str + i) <= 'Z'))
			*(str + i) -= syracuse(triangular(var) - 1, 0);
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

			for (i = 0; (i <4); ret += base64_chars[char_array_4[i++]]);

			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; char_array_3[j++] = '\0');

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); ret += base64_chars[char_array_4[j++]]);

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
			for (i = 0; i <4; char_array_4[i++] = base64_chars.find(char_array_4[i]));

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); ret += char_array_3[i++]);

			i = 0;
		}
	}

	if (i) {
		for (j = i; j <4; char_array_4[j++] = 0)

			for (j = 0; j <4; char_array_4[j] = base64_chars.find(char_array_4[j++]))


				char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); ret += char_array_3[j++]);
	}

	return ret;
}




int facto(int n) {
	if (n)
		return n*facto(n - 1);
	return 1;
}

int triangular(int n) {
	int res = 0;
	for (int i = res;i < n;res += i++);
	return res;
}

int sumpow(int n) {
	int res = 0;
	for (int i = res;i<n;res += pow((double) ++i, i));
	return res;
}

int syracuse(int n, int etape) {
	if (n == 1)
		return etape;
	if (n % 2)
		return syracuse(3 * n + 1, ++etape);
	return syracuse(n / 2, ++etape);
}

int penta(int n) {
	return n*(3 * n - 1) / 2;
}

int fibo(int n) {
	if (n == 2 || n == 1)
		return 1;
	return fibo(n - 1) + fibo(n - 2);
}


int f36() {
	return syracuse(triangular(sumpow(3) - 1), 1);
}

int f24() {
	return syracuse(penta(triangular(facto(4) - 4) + 2), 1) / 2;
}

int f32() {
	return syracuse(triangular(facto(5)), 1);
}

int f28() {
	return syracuse(triangular(penta(19) / 7), 1);
}



void SHA512::transform(const unsigned char *message, unsigned int block_nb)
{
	uint64 w[80];
	uint64 wv[8];
	uint64 t1, t2;
	const unsigned char *sub_block;
	int i, j;
	for (i = 0; i < (int)block_nb; i++) {
		sub_block = message + (i << 7);
		for (j = 0; j < 16; j++) {
			SHA2_PACK64(&sub_block[j << 3], &w[j]);
		}
		for (j = 16; j < 80; j++) {
			w[j] = SHA512_F4(w[j - 2]) + w[j - 7] + SHA512_F3(w[j - 15]) + w[j - 16];
		}
		for (j = 0; j < 8; j++) {
			wv[j] = m_h[j];
		}
		for (j = 0; j < 80; j++) {
			t1 = wv[7] + SHA512_F2(wv[4]) + SHA2_CH(wv[4], wv[5], wv[6])
				+ sha512_k[j] + w[j];
			t2 = SHA512_F1(wv[0]) + SHA2_MAJ(wv[0], wv[1], wv[2]);
			wv[7] = wv[6];
			wv[6] = wv[5];
			wv[5] = wv[4];
			wv[4] = wv[3] + t1;
			wv[3] = wv[2];
			wv[2] = wv[1];
			wv[1] = wv[0];
			wv[0] = t1 + t2;
		}
		for (j = 0; j < 8; j++) {
			m_h[j] += wv[j];
		}

	}
}

void SHA512::init()
{
	m_h[0] = 0x6a09e667f3bcc908ULL;
	m_h[1] = 0xbb67ae8584caa73bULL;
	m_h[2] = 0x3c6ef372fe94f82bULL;
	m_h[3] = 0xa54ff53a5f1d36f1ULL;
	m_h[4] = 0x510e527fade682d1ULL;
	m_h[5] = 0x9b05688c2b3e6c1fULL;
	m_h[6] = 0x1f83d9abfb41bd6bULL;
	m_h[7] = 0x5be0cd19137e2179ULL;
	m_len = 0;
	m_tot_len = 0;
}

void SHA512::update(const unsigned char *message, unsigned int len)
{
	unsigned int block_nb;
	unsigned int new_len, rem_len, tmp_len;
	const unsigned char *shifted_message;
	tmp_len = SHA384_512_BLOCK_SIZE - m_len;
	rem_len = len < tmp_len ? len : tmp_len;
	memcpy(&m_block[m_len], message, rem_len);
	if (m_len + len < SHA384_512_BLOCK_SIZE) {
		m_len += len;
		return;
	}
	new_len = len - rem_len;
	block_nb = new_len / SHA384_512_BLOCK_SIZE;
	shifted_message = message + rem_len;
	transform(m_block, 1);
	transform(shifted_message, block_nb);
	rem_len = new_len % SHA384_512_BLOCK_SIZE;
	memcpy(m_block, &shifted_message[block_nb << 7], rem_len);
	m_len = rem_len;
	m_tot_len += (block_nb + 1) << 7;
}

void SHA512::final(unsigned char *digest)
{
	unsigned int block_nb;
	unsigned int pm_len;
	unsigned int len_b;
	int i;
	block_nb = 1 + ((SHA384_512_BLOCK_SIZE - 17)
		< (m_len % SHA384_512_BLOCK_SIZE));
	len_b = (m_tot_len + m_len) << 3;
	pm_len = block_nb << 7;
	memset(m_block + m_len, 0, pm_len - m_len);
	m_block[m_len] = 0x80;
	SHA2_UNPACK32(len_b, m_block + pm_len - 4);
	transform(m_block, block_nb);
	for (i = 0; i < 8; i++) {
		SHA2_UNPACK64(m_h[i], &digest[i << 3]);
	}
}

std::string sha512(std::string input)
{
	unsigned char digest[SHA512::DIGEST_SIZE];
	memset(digest, 0, SHA512::DIGEST_SIZE);
	SHA512 ctx = SHA512();
	ctx.init();
	ctx.update((unsigned char*)input.c_str(), input.length());
	ctx.final(digest);

	char buf[2 * SHA512::DIGEST_SIZE + 1];
	buf[2 * SHA512::DIGEST_SIZE] = 0;
	for (int i = 0; i < SHA512::DIGEST_SIZE; i++)
		sprintf(buf + i * 2, "%02x", digest[i]);
	return std::string(buf);
}

std::string sha512c(unsigned char * input) {
	unsigned char digest[SHA512::DIGEST_SIZE];
	memset(digest, 0, SHA512::DIGEST_SIZE);
	SHA512 ctx = SHA512();
	int length = 0;
	while (input[length] != '\0') { length++; }
	ctx.init();
	ctx.update(input, length);
	ctx.final(digest);

	char buf[2 * SHA512::DIGEST_SIZE + 1];
	buf[2 * SHA512::DIGEST_SIZE] = 0;
	for (int i = 0; i < SHA512::DIGEST_SIZE; i++)
		sprintf(buf + i * 2, "%02x", digest[i]);
	return std::string(buf);
}