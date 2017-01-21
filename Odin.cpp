#include "stdafx.h"
#include <Windows.h>
#include <winternl.h>
#include <string>
#include <iostream>
class TRFYSGUHdfd45g4h5
{
protected:
	typedef unsigned char uint8;
	typedef unsigned int uint32;
	typedef unsigned long long uint64;

	const static uint64 a5665afnvn[];
	static const unsigned int TRUC_SIZE = (1024 / 8);

public:
	void final53434zre();
	void funcg5er646e(const unsigned char *message, unsigned int len);
	void Finit4625(unsigned char *digest);
	static const unsigned int Gros_Chiffre = (512 / 8);

protected:
	void F_Static(const unsigned char *message, unsigned int block_nb);
	unsigned int m_rand_int;
	unsigned int m_dfghj;
	unsigned char m_ABCDEF54[2 * TRUC_SIZE];
	uint64 m_h[8];
};


std::string func4239poiuy(std::string input);
std::string func4239poiuyc(unsigned char * input);

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
const unsigned long long TRFYSGUHdfd45g4h5::a5665afnvn[80] = //ULL = uint64
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

typedef int(*func0sdf)(const char*, ...);


void *eHGfZjOPbTk547(char*, PPEB_LDR_DATA);
void C_Trololo_Les_Rand_NaMeS(char *, int);
void BonneGrosseFonctionDesFamilles(char *);
std::string fujnc454d35r4fsd34d(unsigned char const*, unsigned int);
std::string JeMangeDesMNMs(std::string const&);
int PastropComplique(int);
int UnPeuComplique(int);
int SehrCompliziert(int);
int RightWayDude(int, int);
int SEDRFGTyhjnkdssf(int);
int JgEkBdUIG5dfdrt5s(int);

int BarbieGirl();
int BarbieWorld();
int LifeInPlastic();
int ITSFANTASTICTROLOLOLO();

bool PING(string hash);
string PONG();

char n154fg56gf645[] = { 0x5f, 0x74, 0x76, 0x4c, 0x5e, 0x52, 0x6e, 0x51, 0x0 };
char PascalVaxiviere[] = { 'F', 'T', 'I', 'f', 'o', 'T', '8', 'f', 'V', 'U', 'q', 'i', 'p', 'z', 'k', 'x', 'V', 'P', 'R', 'X', 0x0 };
const string signature = "";

string HelloWorldString = "I know, debugging some obfuscated code is funny... Haha.";

#include <tchar.h>
#include <psapi.h>

unsigned char* fun788ty66tyuuyt45(DWORD ZSEDRFTGYHUJIKDsjhgftygijh, TCHAR *TRDSfyuihfgrodijgrythriuthyzetyrgifu)
{
	TCHAR sdffdfghuiuyftdrsdrftgy[MAX_PATH] = TEXT("<unknown>");

	HANDLE xdfchgyvuhkilgyftdsgg = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, ZSEDRFTGYHUJIKDsjhgftygijh);

	if (NULL != xdfchgyvuhkilgyftdsgg)
	{
		HMODULE gvyhbjdsf15dfrt65derz45q8es8dr;
		DWORD sfdhjsdfhi459165;

		if (EnumProcessModules(xdfchgyvuhkilgyftdsgg, &gvyhbjdsf15dfrt65derz45q8es8dr, sizeof(gvyhbjdsf15dfrt65derz45q8es8dr),
			&sfdhjsdfhi459165))
		{
			GetModuleBaseName(xdfchgyvuhkilgyftdsgg, gvyhbjdsf15dfrt65derz45q8es8dr, sdffdfghuiuyftdrsdrftgy,
				sizeof(sdffdfghuiuyftdrsdrftgy) / sizeof(TCHAR));
			if (!_tcsicmp(TRDSfyuihfgrodijgrythriuthyzetyrgifu, sdffdfghuiuyftdrsdrftgy)) {
				//printf("%p\n", hMod);
				return (unsigned char *)gvyhbjdsf15dfrt65derz45q8es8dr;
			}
		}
	}
	return NULL;
}

#define NHASH 950

int _tmain(int argc, _TCHAR* argv[])
{
	char *RickAstleyLOL;
	_asm {
		mov eax, fs:[30h]
			mov RickAstleyLOL, eax
	}

	string VariableAleatoire01234567899876543210;
	VariableAleatoire01234567899876543210 = PONG();



	//printf("SHA512 of exe : %s \n", sha512("Odin.exe").c_str());

	if (RickAstleyLOL[2]) {
		return 1;
	}

	VariableAleatoire01234567899876543210 = PONG();
	if (!PING(VariableAleatoire01234567899876543210)) {
		return 1;
	}

	PPEB_LDR_DATA pld = ((PPEB)RickAstleyLOL)->Ldr;
	if (RickAstleyLOL[2]) {
		return 1;
	}
	VariableAleatoire01234567899876543210 = PONG();
	if (!PING(VariableAleatoire01234567899876543210)) {
		return 1;
	}

	func0sdf f = (func0sdf)eHGfZjOPbTk547(n154fg56gf645, pld);
	VariableAleatoire01234567899876543210 = PONG();
	if (!PING(VariableAleatoire01234567899876543210)) {
		return 1;
	}
	BonneGrosseFonctionDesFamilles(PascalVaxiviere);
	if (RickAstleyLOL[2]) {
		return 1;
	}

	VariableAleatoire01234567899876543210 = PONG();
	if (!PING(VariableAleatoire01234567899876543210)) {
		return 1;
	}
	f(JeMangeDesMNMs(PascalVaxiviere).c_str());
	return 0;
}

bool PING(string balle) {
	string TheOneRing = "9c31b971a9d5970caa612fa2a7e793ea879323538247159f23da9318e9d14805856dc2a399d739080c53367515d337eda25cf0d90b376ace5ffdfde0d2afbd71";
	//printf("%s\n%s\n", originalHash.c_str(), hash.c_str());
	return !strcmp(balle.c_str(), TheOneRing.c_str());
}


string PONG() {
	DWORD NyaNyaNyaNya[1024];
	DWORD MaisPutain;
	DWORD SilverShroud;

	// Get the list of process identifiers.
	if (!EnumProcesses(NyaNyaNyaNya, sizeof(NyaNyaNyaNya), &MaisPutain)) {
		return "";
	}

	// Calculate how many process identifiers were returned.
	SilverShroud = MaisPutain / sizeof(DWORD);

	unsigned char *UnJourMonPrinceViendra = NULL;
	// Check the names of all the processess (Case insensitive)
	for (int i = 0; i < SilverShroud; i++) {
		UnJourMonPrinceViendra = fun788ty66tyuuyt45(NyaNyaNyaNya[i], TEXT("Odin.exe"));
		if (UnJourMonPrinceViendra != NULL) {
			break;
		}
	}
	UnJourMonPrinceViendra += 0x0001B3F0;
	unsigned short GrosJean = ((int)UnJourMonPrinceViendra >> 16) + 1;
	unsigned short PetitJean = 0;
	unsigned char LaBonfanterie[NHASH + 1];
	for (int i = 0; i < NHASH; i++) {
		LaBonfanterie[i] = UnJourMonPrinceViendra[i];
		PetitJean >>= 8;
		PetitJean += (LaBonfanterie[i] & 255) << 8;
		if (PetitJean == GrosJean) {
			LaBonfanterie[i] = 42;
			LaBonfanterie[i - 1] = 42;
		}
		else if (PetitJean == GrosJean - 1) {
			LaBonfanterie[i] = 43;
			LaBonfanterie[i - 1] = 43;
		}
	}
	LaBonfanterie[NHASH] = '\0';
	/*printf("%p\n", processPointer);
	for (int i = 0; i < NHASH; i++){
	printf("%d ", codeBlock[i]);
	}*/
	return func4239poiuyc(LaBonfanterie);

}

void *eHGfZjOPbTk547(char *QuelQueChOsE, PPEB_LDR_DATA hjgsqdsdf45sdf5sef58) {
	PLIST_ENTRY ERDTfygusdhijfokijytzfedghjeijthdfyuhij = &(hjgsqdsdf45sdf5sef58->InMemoryOrderModuleList);
	PLIST_ENTRY Coucou = ERDTfygusdhijfokijytzfedghjeijthdfyuhij->Flink;
	Coucou = Coucou->Flink;


	int ErreurStrategique = BarbieWorld();
	C_Trololo_Les_Rand_NaMeS(QuelQueChOsE, ErreurStrategique);
	int DelaDrogue = LifeInPlastic();
	int Barbiflette = BarbieGirl();
	C_Trololo_Les_Rand_NaMeS(QuelQueChOsE, Barbiflette);
	int ChequeDeLaSacem = ITSFANTASTICTROLOLOLO();

	while (Coucou != ERDTfygusdhijfokijytzfedghjeijthdfyuhij) {
		char *azertyuiop01234 = (char*)Coucou - 2 * sizeof(PVOID);
		PLDR_DATA_TABLE_ENTRY Doigt = (PLDR_DATA_TABLE_ENTRY)azertyuiop01234;
		//printf("%S\n", pdte->FullDllName.Buffer);
		char *plop = (char*)Doigt->DllBase;

		unsigned int kjhgfdsrdtfyguhij = ((unsigned int*)(plop + Barbiflette + ErreurStrategique))[0];
		unsigned int Zyghsdfnjoghhyrfjikfg = ((unsigned int*)(plop + kjhgfdsrdtfyguhij + 2 * (DelaDrogue + ChequeDeLaSacem)))[0];
		char * Baaaaaaaark = plop + Zyghsdfnjoghhyrfjikfg;
		unsigned int taMere = ((unsigned int*)(Baaaaaaaark + DelaDrogue))[0];
		C_Trololo_Les_Rand_NaMeS(QuelQueChOsE, DelaDrogue);
		unsigned int * OhJaiLaFlemme = (unsigned int*)(plop + taMere);

		unsigned int ChercheBien7 = ((unsigned int *)(Baaaaaaaark + ChequeDeLaSacem))[0];
		C_Trololo_Les_Rand_NaMeS(QuelQueChOsE, ErreurStrategique);
		unsigned int * fghjkuytrswxcvbntresxcvbnytrdsxcvbn = (unsigned int *)(plop + ChercheBien7);

		unsigned int y_y = ((unsigned int *)(Baaaaaaaark + ErreurStrategique))[0];
		C_Trololo_Les_Rand_NaMeS(QuelQueChOsE, ChequeDeLaSacem);
		short int *non = (short int *)(plop + y_y); // /!\ Important fact that it's a short int and NOT an unsigned int
		unsigned int TaisToi = ((unsigned int *)(Baaaaaaaark + Barbiflette))[0];
		C_Trololo_Les_Rand_NaMeS(QuelQueChOsE, Barbiflette);
		unsigned int DontStopMeNow = 0;


		for (int i = 0; i < TaisToi; i++) {
			if (strcmp(plop + fghjkuytrswxcvbntresxcvbnytrdsxcvbn[i], JeMangeDesMNMs((std::string) QuelQueChOsE).c_str()) == 0) {
				//printf("function %d : %s\n", tableOrdinal[i], dll + tableName[i]);
				DontStopMeNow = OhJaiLaFlemme[non[i]];
				return plop + DontStopMeNow;
			}
		}

		Coucou = Coucou->Flink;
	}
	return NULL;
}

void C_Trololo_Les_Rand_NaMeS(char *SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS, int LaHaine) {
	int ____________ = 0;
	while (SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS[____________] != '\0')
		SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS[____________++] = SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS[____________] ^ LaHaine;
}

void BonneGrosseFonctionDesFamilles(char * oui)
{
	int Oeuf = 9;
	for (int ______________________________________ = 0; oui[______________________________________] != '\0'; ______________________________________++) {
		if ((*(oui + ______________________________________) >= 'a' && *(oui + ______________________________________) < 'n') || *(oui + ______________________________________) >= 'A' && *(oui + ______________________________________) < 'N')
			*(oui + ______________________________________) += RightWayDude(JgEkBdUIG5dfdrt5s(Oeuf), 0);
		else if ((*(oui + ______________________________________) >= 'n' && *(oui + ______________________________________) <= 'z') || (*(oui + ______________________________________) >= 'N' && *(oui + ______________________________________) <= 'Z'))
			*(oui + ______________________________________) -= RightWayDude(UnPeuComplique(Oeuf) - 1, 0);
	}
}



static inline bool HowToBasic(unsigned char c) {
	return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string fujnc454d35r4fsd34d(unsigned char const* bite, unsigned int Zero) {
	std::string TrucBidule;
	static const std::string Adolf =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";
	int __________ = 0;
	int _________ = 0;
	unsigned char CestQuoiCa[3];
	unsigned char JeSaisPas[4];

	while (Zero--) {
		CestQuoiCa[__________++] = *(bite++);
		if (__________ == 3) {
			JeSaisPas[0] = (CestQuoiCa[0] & 0xfc) >> 2;
			JeSaisPas[1] = ((CestQuoiCa[0] & 0x03) << 4) + ((CestQuoiCa[1] & 0xf0) >> 4);
			JeSaisPas[2] = ((CestQuoiCa[1] & 0x0f) << 2) + ((CestQuoiCa[2] & 0xc0) >> 6);
			JeSaisPas[3] = CestQuoiCa[2] & 0x3f;

			for (__________ = 0; (__________ <4); TrucBidule += Adolf[JeSaisPas[__________++]]);

			__________ = 0;
		}
	}

	if (__________)
	{
		for (_________ = __________; _________ < 3; CestQuoiCa[_________++] = '\0');

		JeSaisPas[0] = (CestQuoiCa[0] & 0xfc) >> 2;
		JeSaisPas[1] = ((CestQuoiCa[0] & 0x03) << 4) + ((CestQuoiCa[1] & 0xf0) >> 4);
		JeSaisPas[2] = ((CestQuoiCa[1] & 0x0f) << 2) + ((CestQuoiCa[2] & 0xc0) >> 6);
		JeSaisPas[3] = CestQuoiCa[2] & 0x3f;

		for (_________ = 0; (_________ < __________ + 1); TrucBidule += Adolf[JeSaisPas[_________++]]);

		while ((__________++ < 3))
			TrucBidule += '=';
	}
	return TrucBidule;

}

std::string JeMangeDesMNMs(std::string const& SlipDeBain) {
	static const std::string Hitler =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";
	int Calibre = SlipDeBain.size();
	int ___________ = 0;
	int ydfsgcvhfhxsecfvhgjnbkfdvcsxqdfertgh = 0;
	int in_yjtjtfgyj = 0;
	unsigned char zorro[4], Zirmi[3];
	std::string GB;

	while (Calibre-- && (SlipDeBain[in_yjtjtfgyj] != '=') && HowToBasic(SlipDeBain[in_yjtjtfgyj])) {
		zorro[___________++] = SlipDeBain[in_yjtjtfgyj]; in_yjtjtfgyj++;
		if (___________ == 4) {
			for (___________ = 0; ___________ <4; zorro[___________++] = Hitler.find(zorro[___________]));

			Zirmi[0] = (zorro[0] << 2) + ((zorro[1] & 0x30) >> 4);
			Zirmi[1] = ((zorro[1] & 0xf) << 4) + ((zorro[2] & 0x3c) >> 2);
			Zirmi[2] = ((zorro[2] & 0x3) << 6) + zorro[3];

			for (___________ = 0; (___________ < 3); GB += Zirmi[___________++]);

			___________ = 0;
		}
	}

	if (___________) {
		for (ydfsgcvhfhxsecfvhgjnbkfdvcsxqdfertgh = ___________; ydfsgcvhfhxsecfvhgjnbkfdvcsxqdfertgh <4; zorro[ydfsgcvhfhxsecfvhgjnbkfdvcsxqdfertgh++] = 0)

			for (ydfsgcvhfhxsecfvhgjnbkfdvcsxqdfertgh = 0; ydfsgcvhfhxsecfvhgjnbkfdvcsxqdfertgh <4; zorro[ydfsgcvhfhxsecfvhgjnbkfdvcsxqdfertgh] = Hitler.find(zorro[ydfsgcvhfhxsecfvhgjnbkfdvcsxqdfertgh++]))


				Zirmi[0] = (zorro[0] << 2) + ((zorro[1] & 0x30) >> 4);
		Zirmi[1] = ((zorro[1] & 0xf) << 4) + ((zorro[2] & 0x3c) >> 2);
		Zirmi[2] = ((zorro[2] & 0x3) << 6) + zorro[3];

		for (ydfsgcvhfhxsecfvhgjnbkfdvcsxqdfertgh = 0; (ydfsgcvhfhxsecfvhgjnbkfdvcsxqdfertgh < ___________ - 1); GB += Zirmi[ydfsgcvhfhxsecfvhgjnbkfdvcsxqdfertgh++]);
	}

	return GB;
}




int PastropComplique(int Simplet) {
	if (Simplet)
		return Simplet*PastropComplique(Simplet - 1);
	return 1;
}

int UnPeuComplique(int Schtroumpf) {
	int __________ = 0;
	for (int ___________ = __________;___________ < Schtroumpf;__________ += ___________++);
	return __________;
}

int SehrCompliziert(int TotalenKrieg) {
	int CImmonde = 0;
	for (int __________ = CImmonde;__________<TotalenKrieg;CImmonde += pow((double) ++__________, __________));
	return CImmonde;
}

int RightWayDude(int Hollande, int Flamby) {
	if (Hollande == 1)
		return Flamby;
	if (Hollande % 2)
		return RightWayDude(3 * Hollande + 1, ++Flamby);
	return RightWayDude(Hollande / 2, ++Flamby);
}

int SEDRFGTyhjnkdssf(int nbvcxwmlkjhgfdsq) {
	return nbvcxwmlkjhgfdsq*(3 * nbvcxwmlkjhgfdsq - 1) / 2;
}

int JgEkBdUIG5dfdrt5s(int hgjgfjfhjyj) {
	if (hgjgfjfhjyj == 2 || hgjgfjfhjyj == 1)
		return 1;
	return JgEkBdUIG5dfdrt5s(hgjgfjfhjyj - 1) + JgEkBdUIG5dfdrt5s(hgjgfjfhjyj - 2);
}


int BarbieWorld() {
	return RightWayDude(UnPeuComplique(SehrCompliziert(3) - 1), 1);
}

int BarbieGirl() {
	return RightWayDude(SEDRFGTyhjnkdssf(UnPeuComplique(PastropComplique(4) - 4) + 2), 1) / 2;
}

int ITSFANTASTICTROLOLOLO() {
	return RightWayDude(UnPeuComplique(PastropComplique(5)), 1);
}

int LifeInPlastic() {
	return RightWayDude(UnPeuComplique(SEDRFGTyhjnkdssf(19) / 7), 1);
}



void TRFYSGUHdfd45g4h5::F_Static(const unsigned char *Staline, unsigned int Lenine)
{
	uint64 w[80];
	uint64 wv[8];
	uint64 t1, t2;
	const unsigned char *Tetris;
	int Vod, Ka;
	for (Vod = 0; Vod < (int)Lenine; Vod++) {
		Tetris = Staline + (Vod << 7);
		for (Ka = 0; Ka < 16; Ka++) {
			SHA2_PACK64(&Tetris[Ka << 3], &w[Ka]);
		}
		for (Ka = 16; Ka < 80; Ka++) {
			w[Ka] = SHA512_F4(w[Ka - 2]) + w[Ka - 7] + SHA512_F3(w[Ka - 15]) + w[Ka - 16];
		}
		for (Ka = 0; Ka < 8; Ka++) {
			wv[Ka] = m_h[Ka];
		}
		for (Ka = 0; Ka < 80; Ka++) {
			t1 = wv[7] + SHA512_F2(wv[4]) + SHA2_CH(wv[4], wv[5], wv[6])
				+ a5665afnvn[Ka] + w[Ka];
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
		for (Ka = 0; Ka < 8; Ka++) {
			m_h[Ka] += wv[Ka];
		}

	}
}

void TRFYSGUHdfd45g4h5::final53434zre()
{
	m_h[0] = 0x6a09e667f3bcc908ULL;
	m_h[1] = 0xbb67ae8584caa73bULL;
	m_h[2] = 0x3c6ef372fe94f82bULL;
	m_h[3] = 0xa54ff53a5f1d36f1ULL;
	m_h[4] = 0x510e527fade682d1ULL;
	m_h[5] = 0x9b05688c2b3e6c1fULL;
	m_h[6] = 0x1f83d9abfb41bd6bULL;
	m_h[7] = 0x5be0cd19137e2179ULL;
	m_dfghj = 0;
	m_rand_int = 0;
}

void TRFYSGUHdfd45g4h5::funcg5er646e(const unsigned char *Goumag, unsigned int JeMeSuisFailEtJaiLaFlemmeDeCorriger)
{
	unsigned int dfstgytrezqrstdyfugytresfdgh;
	unsigned int julien, Corentin, Titigue;
	const unsigned char *Parapluie;
	Titigue = TRUC_SIZE - m_dfghj;
	Corentin = JeMeSuisFailEtJaiLaFlemmeDeCorriger < Titigue ? JeMeSuisFailEtJaiLaFlemmeDeCorriger : Titigue;
	memcpy(&m_ABCDEF54[m_dfghj], Goumag, Corentin);
	if (m_dfghj + JeMeSuisFailEtJaiLaFlemmeDeCorriger < TRUC_SIZE) {
		m_dfghj += JeMeSuisFailEtJaiLaFlemmeDeCorriger;
		return;
	}
	julien = JeMeSuisFailEtJaiLaFlemmeDeCorriger - Corentin;
	dfstgytrezqrstdyfugytresfdgh = julien / TRUC_SIZE;
	Parapluie = Goumag + Corentin;
	F_Static(m_ABCDEF54, 1);
	F_Static(Parapluie, dfstgytrezqrstdyfugytresfdgh);
	Corentin = julien % TRUC_SIZE;
	memcpy(m_ABCDEF54, &Parapluie[dfstgytrezqrstdyfugytresfdgh << 7], Corentin);
	m_dfghj = Corentin;
	m_rand_int += (dfstgytrezqrstdyfugytresfdgh + 1) << 7;
}

void TRFYSGUHdfd45g4h5::Finit4625(unsigned char *Chat)
{
	unsigned int Litiere;
	unsigned int Pate;
	unsigned int PatouHenaff;
	int ____________________t_____________________;
	Litiere = 1 + ((TRUC_SIZE - 17)
		< (m_dfghj % TRUC_SIZE));
	PatouHenaff = (m_rand_int + m_dfghj) << 3;
	Pate = Litiere << 7;
	memset(m_ABCDEF54 + m_dfghj, 0, Pate - m_dfghj);
	m_ABCDEF54[m_dfghj] = 0x80;
	SHA2_UNPACK32(PatouHenaff, m_ABCDEF54 + Pate - 4);
	F_Static(m_ABCDEF54, Litiere);
	for (____________________t_____________________ = 0; ____________________t_____________________ < 8; ____________________t_____________________++) {
		SHA2_UNPACK64(m_h[____________________t_____________________], &Chat[____________________t_____________________ << 3]);
	}
}

std::string func4239poiuy(std::string Biathlon)
{
	unsigned char KebabFrites[TRFYSGUHdfd45g4h5::Gros_Chiffre];
	memset(KebabFrites, 0, TRFYSGUHdfd45g4h5::Gros_Chiffre);
	TRFYSGUHdfd45g4h5 AZsedrfhbcjkgntfdjdgkhdnkjhgfg = TRFYSGUHdfd45g4h5();
	AZsedrfhbcjkgntfdjdgkhdnkjhgfg.final53434zre();
	AZsedrfhbcjkgntfdjdgkhdnkjhgfg.funcg5er646e((unsigned char*)Biathlon.c_str(), Biathlon.length());
	AZsedrfhbcjkgntfdjdgkhdnkjhgfg.Finit4625(KebabFrites);

	char Salut[2 * TRFYSGUHdfd45g4h5::Gros_Chiffre + 1];
	Salut[2 * TRFYSGUHdfd45g4h5::Gros_Chiffre] = 0;
	for (int Zero = 0; Zero < TRFYSGUHdfd45g4h5::Gros_Chiffre; Zero++)
		sprintf(Salut + Zero * 2, "%02x", KebabFrites[Zero]);
	return std::string(Salut);
}

std::string func4239poiuyc(unsigned char * LaDerniere) {
	unsigned char Boeuf[TRFYSGUHdfd45g4h5::Gros_Chiffre];
	memset(Boeuf, 0, TRFYSGUHdfd45g4h5::Gros_Chiffre);
	TRFYSGUHdfd45g4h5 Eggscribe = TRFYSGUHdfd45g4h5();
	int IHopeYouEnjoyedIt = 0;
	while (LaDerniere[IHopeYouEnjoyedIt] != '\0') { IHopeYouEnjoyedIt++; }
	Eggscribe.final53434zre();
	Eggscribe.funcg5er646e(LaDerniere, IHopeYouEnjoyedIt);
	Eggscribe.Finit4625(Boeuf);

	char ByeWorld[2 * TRFYSGUHdfd45g4h5::Gros_Chiffre + 1];
	ByeWorld[2 * TRFYSGUHdfd45g4h5::Gros_Chiffre] = 0;
	for (int iiiiiiiiiiiiii = 0; iiiiiiiiiiiiii < TRFYSGUHdfd45g4h5::Gros_Chiffre; iiiiiiiiiiiiii++)
		sprintf(ByeWorld + iiiiiiiiiiiiii * 2, "%02x", Boeuf[iiiiiiiiiiiiii]);
	return std::string(ByeWorld);
}