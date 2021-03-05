#ifndef EilAnalizator_hpp
#define EilAnalizator_hpp

using namespace std;
#include <string>
#include <stack>

#define ARAB_SKAICIUS_ASCII	1
#define R_SKAICIUS			2
#define OPERATORIUS			3
#define SKLIAUSTAI			4
#define SKAICIUS			5

#define MAX_SK_LENGHT    10

struct duomens_tipas{
	int tipas;
	char reiksme[MAX_SK_LENGHT];
};

struct inv_duomenys_konvertuoti
{
	int tipas;
	float Skreiksme;
	char  Chreiksme;
};

class Rusiavimas
{
public:
	stack <duomens_tipas> rusiuoti(string str);

private:
	bool ar_oper(char check_char);
	bool ar_rom_sk(char sign);
};

class Konvertavimas 
{
public:
	stack <inv_duomenys_konvertuoti> konvertuoti(stack <duomens_tipas> duom);
private:
	int rom_sk_conv(char r_sk);
	int rom_sk_process(char* inPtr);
	float arab_sk_process(char* inPtr);
};

class Skaiciavimas 
{
public:
	float skaiciuoti(stack <inv_duomenys_konvertuoti> duom);
private:
	float atliktiVeiksmus(float a, float b, char op);
	int   pirmumas(char op);

};

#endif // EilAnalizator_hpp