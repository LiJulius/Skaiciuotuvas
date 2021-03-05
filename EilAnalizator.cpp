#include "EilAnalizator.hpp"
#include <string>
#include <iostream>
#include <stack>

using namespace std;

stack <duomens_tipas> Rusiavimas::rusiuoti(string str)
{
	stack <duomens_tipas> dt_mas;
	duomens_tipas dt = {};

	int i = 0;
	int j = 0;
	size_t l = str.length();

	while (i<l)
	{
		if (ar_rom_sk(str[i]))
		{
			dt.reiksme[j++] = str[i];
			dt.tipas = R_SKAICIUS;
			i++;
			while (ar_rom_sk(str[i]))
			{
				dt.reiksme[j++] = str[i];
				i++;
				if (i == MAX_SK_LENGHT)
				{
					cout << "Suvestas skaièius turi per daug þenklø! " << endl;
					cout << "--------------------------------------------------------------------------------------\r\n" << endl;
					dt_mas.empty();
					return dt_mas;
				}
			}
			if (isdigit(str[i]))
			{
				cout << "Trûksta operatoriaus! " << endl;
				cout << "--------------------------------------------------------------------------------------\r\n" << endl;
				dt_mas.empty();
				return dt_mas;
			}
		}
		else if ((isdigit(str[i])) || (str[i] == '.'))
		{
			dt.reiksme[j++] = str[i];
			dt.tipas = ARAB_SKAICIUS_ASCII;
			i++;
			while ((isdigit(str[i])) || (str[i] == '.'))
			{
				dt.reiksme[j++] = str[i];
				i++;
				if (i == MAX_SK_LENGHT)
				{
					cout << "Suvestas skaièius turi per daug þenklø! " << endl;
					cout << "--------------------------------------------------------------------------------------\r\n" << endl;
					dt_mas.empty();
					return dt_mas;
				}
			}
			if (ar_rom_sk(str[i]))
			{
				cout << "Truksta operatoriaus! " << endl;
				cout << "--------------------------------------------------------------------------------------\r\n" << endl;
				dt_mas.empty();
				return dt_mas;
			}
		}
		else if (ar_oper(str[i]))
		{
			dt.reiksme[j] = str[i];
			dt.tipas = OPERATORIUS;
			i++;
			if (ar_oper(str[i]))
			{
				{
					cout << "Du operatoriai is eiles! " << endl;
					cout << "--------------------------------------------------------------------------------------\r\n" << endl;
					dt_mas.empty();
					return dt_mas;
				}
			}
		}
		else if ((str[i]) == '(')
		{
			if (i)
				if (!ar_oper(str[i - 1]) || (str[i - 1] == ')'))
				{
					dt.reiksme[j] = '*';
					dt.tipas = OPERATORIUS;
					dt_mas.push(dt);
				}
			
			dt.reiksme[j] = str[i];
			dt.tipas = SKLIAUSTAI;
			i++;
		}
		else if ((str[i]) == ')')
		{
			if (i<l)
				if (!ar_oper(str[i + 1]) && (!str[i + 1] == ')'))
				{
					dt.reiksme[j] = str[i];
					dt.tipas = SKLIAUSTAI;
					dt_mas.push(dt);

					dt.reiksme[j] = '*';
					dt.tipas = OPERATORIUS;
				}
				else
				{
					dt.reiksme[j] = str[i];
					dt.tipas = SKLIAUSTAI;
				}
			i++;
		}
		else if ((str[i]) == ' ') // Jei tarpas
		{
			i++;
			continue;
		}
		else // Ávestos kitos raidës ar kintamieji, kurios ðiai versijai dar nëra palaikomos
		{
			cout << "Naudojamas simbolis: " << str[i] << " negali buti atpazintas. Patikslinkite matematine israiska!" << endl;
			cout << "--------------------------------------------------------------------------------------\r\n" << endl;
			dt_mas.empty();
			return dt_mas;
		}

		dt_mas.push(dt);
		memset(&dt, 0, sizeof(dt));
		j = 0;
	}
	return dt_mas;
}

bool Rusiavimas::ar_oper(char check_char)
{
	switch (check_char)
	{
	case '^': case '*': case '/':
	case '+': case '-':
		return 1;
		break;
	default:
		return 0;
		break;
	}
}

bool Rusiavimas::ar_rom_sk(char sign)
{
	switch (sign)
	{
	case '_': case 'I': case 'V':
	case 'X': case 'L': case 'C':
	case 'D': case 'M':
		return 1;
		break;
	default:
		return 0;
		break;
	}
}


int Konvertavimas::rom_sk_conv(char r_sk)
{
	switch (r_sk) {
	case 'I':
		return 1;
		break;
	case 'V':
		return 5;
		break;
	case 'X':
		return 10;
		break;
	case 'L':
		return 50;
		break;
	case 'C':
		return 100;
		break;
	case 'D':
		return 500;
		break;
	case 'M':
		return 1000;
		break;
	default:
		cout << "Neatpazintas romeniskas zenklas! Programa siame taske normaliomis salygomis neatsiduria! " << endl;
		cout << "--------------------------------------------------------------------------------------\r\n" << endl;
		return 0;
		break;
	}
}

stack <inv_duomenys_konvertuoti> Konvertavimas::konvertuoti(stack <duomens_tipas> duom)
{
	stack <inv_duomenys_konvertuoti>  konv_d = {};      // Graþinami duomenys
	inv_duomenys_konvertuoti raw_konv = {};             // Raw duoemø struktûra
	duomens_tipas raw_dt = {};

	while (!duom.empty())
	{
		raw_dt = duom.top();
		duom.pop();

		switch (raw_dt.tipas) {
		case ARAB_SKAICIUS_ASCII:
			raw_konv.tipas = SKAICIUS;
			raw_konv.Skreiksme = arab_sk_process(raw_dt.reiksme);
			break;
		case R_SKAICIUS:
			raw_konv.tipas = SKAICIUS;
			raw_konv.Skreiksme = (float)rom_sk_process(raw_dt.reiksme);
			if (raw_konv.Skreiksme == -1)
			{
				konv_d.empty();
				return konv_d;
			}
			break;
	
		default: // Skliaustai, operatorius ir kt
			raw_konv.tipas = raw_dt.tipas;
			raw_konv.Chreiksme = raw_dt.reiksme[0];
			break;
		}

		konv_d.push(raw_konv);
		memset(&raw_dt, 0, sizeof(raw_dt));
		memset(&raw_konv, 0, sizeof(raw_konv));
	}

	return konv_d;
}

int Konvertavimas::rom_sk_process(char* inPtr)
{
	int rawSk = 0;
	int i = 0;

	// Sekantys du parametrai naudojami nusakyti tokiems skaiciams kaip: IX, IXV ir kt.
	// Kuriems reikalinga panaudoti atimti
	int currentSk = 0;
	int prevSk = 10000000;   // Uþsiduodamas skaièius, didesnis uþ didþiausia realizuota þnekla

	while ((*inPtr) && (i < MAX_SK_LENGHT))
	{
		if (*inPtr == '_')
		{
			inPtr++;
			i++;
			if (*inPtr)
			{
				currentSk = 1000 * rom_sk_conv(*inPtr++);
				i++;

				if (currentSk > prevSk)
				{
					rawSk += currentSk - 2 * prevSk;
					prevSk = currentSk;
					currentSk = 0;
				}
				else
				{
					rawSk += currentSk;
					prevSk = currentSk;
					currentSk = 0;
				}
			}
			else
			{
				cout << "Matematine israiska klaidinga! Po romenisko zenklo _ nebuvo romenisko skaiciaus atitikmens! " << endl;
				cout << "--------------------------------------------------------------------------------------\r\n" << endl;
			}
		}
		else
		{
			currentSk = rom_sk_conv(*inPtr++);
			i++;

			if (currentSk > prevSk)
			{
				rawSk += currentSk - 2 * prevSk;
				prevSk = currentSk;
				currentSk = 0;
			}
			else
			{
				rawSk += currentSk;
				prevSk = currentSk;
				currentSk = 0;
			}
		}
	}
	return -1;
}


float Konvertavimas::arab_sk_process(char* inPtr)
{
	float raw_sk = 0;
	int i = 0;
	char decPow = 1;
	bool dec = false;

	while ((*inPtr) && (i < MAX_SK_LENGHT)) //  // Tikrinamas sekantis narys yra ir ar nevirsytas didziausias ilgis
	{
		if ((*inPtr) && (!dec) && (!(*inPtr == '.')))      // Tikrinama ar skaièiai eina prieð kablelá
			raw_sk = raw_sk * 10 + (*inPtr - '0');
		else if ((*inPtr) && (dec) && (!(*inPtr == '.'))) // Tikrinama ar skaièiai eina po kablelio
		{
			raw_sk = raw_sk + (*inPtr - '0') / ((float)pow(10, double(decPow)));
			decPow++;                                 // Kiekvieno skaièiaus po kablelio, vertë sumaþinama 10 kartø
		}
		else if ((*inPtr == '.') && (!dec))  // Ar prasideda skaièius verës po kablelio
			dec = true;
		else if ((*inPtr == '.') && (dec))  // Tikrinama ar skaièius neturi daugiau nei 1 taðkà
		{
			cout << "Matematine israiska klaidinga! Vienas skaicius turi du kablelio zenklus! Skaicius pilyginamas 0." << endl;
			cout << "--------------------------------------------------------------------------------------\r\n" << endl;
			return 0;
		}
		inPtr++;
		i++;
	}
	return raw_sk;
}

float Skaiciavimas::skaiciuoti(stack <inv_duomenys_konvertuoti> duom)
{
	// Stack reiksmiu saugojimui
	stack <float> val;

	// Stack operatoriu saugojimui
	stack <char> op;

	inv_duomenys_konvertuoti raw_dt = {};

	while (!duom.empty())
	{
		raw_dt = duom.top();
		duom.pop();

		if (raw_dt.tipas == SKAICIUS)
			val.push(raw_dt.Skreiksme);
		else if (raw_dt.tipas == SKLIAUSTAI)
		{
			if (raw_dt.Chreiksme == '(')
				op.push(raw_dt.Chreiksme);
			else if (raw_dt.Chreiksme == ')')
			{
				while (!op.empty() && op.top() != '(')
				{
					float val2 = val.top();
					val.pop();

					float val1 = val.top();
					val.pop();

					char oper = op.top();
					op.pop();

					val.push(atliktiVeiksmus(val1, val2, oper));
				}

				if (!op.empty()) // Pasalinti atidarymo skliaustus jei tuokius randame
					op.pop();
				else
				{
					cout << "Truksta atidarymo skliaustu! Patikslinkite matematine israiska!" << endl;
					cout << "--------------------------------------------------------------------------------------\r\n" << endl;
				}
			}
		}
		else if (raw_dt.tipas == OPERATORIUS)// Ar dabartinis elementas yra operatorius
		{
			// Dël matematiniø veiksmø pirmenybës, atliekamas perrikiavimas
			while (!op.empty() && pirmumas(op.top()) >= pirmumas(raw_dt.Chreiksme))
			{
				float val2 = val.top();
				val.pop();

				float val1 = val.top();
				val.pop();

				char oper = op.top();
				op.pop();

				val.push(atliktiVeiksmus(val1, val2, oper));
			}

			// Dabartinis operatorius perkeliamas á operatoriø eilæ
			op.push(raw_dt.Chreiksme);
		}
	}

	// Atlikti likusius sudëties ir atimptie veiksmus
	while (!op.empty()) 
	{
		float val2 = val.top();
		val.pop();

		float val1 = val.top();
		val.pop();

		char oper = op.top();
		op.pop();

		val.push(atliktiVeiksmus(val1, val2, oper));
	}

	return val.top();
}

int Skaiciavimas::pirmumas(char op)
{
	switch (op)
	{
	case '^':
		return 4;
		break;
	case '*': case '/':
		return 3;
		break;
	case '+': case '-':
		return 2;
		break;
	default:
		return 0;
		break;
	}
}

float Skaiciavimas::atliktiVeiksmus(float a, float b, char op) {
	switch (op) {
	case '+':
		return a + b;
		break;
	case '-':
		return a - b;
		break;
	case '*':
		return a * b;
		break;
	case '/':
		return a / b;
		break;
	case '^':
		return (float)pow(double(a), double(b));
		break;
	default:
		cout << "Operatorius blogas! Programa siame taske normaliomis salygomis neatsiduria! " << endl;
		cout << "--------------------------------------------------------------------------------------\r\n" << endl;
		return 0;
		break;
	}
}