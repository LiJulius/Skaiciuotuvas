#include "EilAnalizator.hpp"
#include <iostream>
#include <string>
#include <stack>

using namespace std;


int main(int argc, char** argv)
{
   // testing::InitGoogleTest(&argc, argv);
   // return RUN_ALL_TESTS();
    
    string mat_israiska;
    Rusiavimas* rusiav{};
    Konvertavimas* konv{};
    Skaiciavimas* skaic{};
    stack <duomens_tipas> surusiuotiElem;
    stack <inv_duomenys_konvertuoti> inv_conv_duom;
    float rezult = 0;

    cout << "--------------------------------------------------------------------------------------" << endl;
    cout << "Iveskite matematine israiska ir paspauskite 'Enter'." << endl;
    cout << "Norint iseiti, spauskite 2 kartus 'Enter' nieko neivedus." << endl;

    getline(cin, mat_israiska);

    surusiuotiElem = rusiav->rusiuoti(mat_israiska);
    if (!surusiuotiElem.empty())
    {
        inv_conv_duom = konv->konvertuoti(surusiuotiElem);
        if (!inv_conv_duom.empty())
        {
            rezult = skaic->skaiciuoti(inv_conv_duom);

            // Išvesti gautą rezultatą
            cout << "Atsakymas: " << rezult << endl;
            cout << "--------------------------------------------------------------------------------------\r\n" << endl;
        }
    }

    return 0;
}
