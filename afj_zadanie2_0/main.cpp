#include <iostream>
#include <string>
#include <dirent.h>
#include <fstream>
#include <vector>

#include "stavNKA.h"
#include "stavDKA.h"

using namespace std;

bool load_rules(string file_name, int &nSize_X,int &nSize_Y, vector <char> &abeceda, vector <stavNKA*> &stavy) ;
void closeNKA(stavNKA* pole, stavDKA* &dka);
bool nextDKA(char pis, stavDKA* vstupny_stav, stavDKA* vystupny_stav, vector <stavDKA*> &stavy);


int main()
{
    string sFile_Path = "/Users/katka_pc/Desktop/rules4.txt";
    string vPravidla;

    vector<char> abeceda;
    vector<stavNKA*> stavyNKA;
    vector<stavDKA*> stavyDKA;

    int nSize_X;
    int nSize_Y;

    bool loaded = false;
    bool are_bal = false;

    loaded = load_rules(sFile_Path, nSize_X, nSize_Y, abeceda, stavyNKA);

    if(loaded==false)
    {
        cout<<"CHYBA - vstupny subor je nepovoleneho formatu, nacitanie sa nepodarilo"<<endl;
        return 0;
    }

    stavNKA* a;

    stavDKA* prvy = new stavDKA();
    for (std::vector<stavNKA*>::iterator it = stavyNKA.begin() ; it != stavyNKA.end(); ++it)
    {
        if((*it)->getPociatocny())
        {
            a = *it;

            closeNKA(a,prvy);
            prvy->setPociatocny(true);
            stavyDKA.push_back(prvy);
        }
    }

/*    int index = 0;
    stavDKA* stav1 = new stavDKA();
    if (nextDKA('a',prvy,stav1,stavyDKA)){
        cout<<"novy stav prvy->a"<<endl;
    }

    stavDKA* stav2 = new stavDKA();
    if (nextDKA('c',prvy,stav2,stavyDKA)){
        cout<<"novy stav prvy->c"<<endl;
    }

    /*set<string> ll = prvy->prechody.begin()->second->getNames();
    for(auto const &tmp : ll)
    {
        cout << tmp << endl;
    }*/

  /*  cout << "_____________________ VYPOCET PRE STAV 2 _____________________" << endl;
    stavDKA* stav3 = new stavDKA();
    if (nextDKA('a',stav2,stav3,stavyDKA)){
        cout<<"novy stav"<<endl;
    }
    else
    {
        cout << "dalsi stav neni alebo uz existuje" << endl;
    }

    set<string> llo = stav2->prechody.begin()->second->getNames();
    for(auto const &tmp : llo)
    {
        cout << tmp << endl;
    }
*/


    while(true){

        stavDKA* stav = new stavDKA();

        for(int i=0; i< abeceda.size();i++){
            if(nextDKA(abeceda[i],stavyDKA[index],stav)){
                stavyDKA.push_back(stav);
            }
        }

        index++;
        if(index == stavyDKA.size())
            break;
        delete stav;
    }


    //set <string> skuska;

    //for(auto const &tmp : stav->podstavy)
    //{
      //  cout << tmp->getName() << endl;

    //}

    //vector<pair<char,stav*>> k;
    //cout << a->getPrechody().size() << endl;
    //cout << a->getPrechody().begin()->first << endl;
    //cout << a->getPrechody().begin()->second->getName() << endl;

    //cout << k.at(0).first << endl;


    return 0;
}

bool nextDKA(char pis, stavDKA* vstupny_stav, stavDKA* vystupny_stav, vector <stavDKA*> &stavy)
{
    bool ma_stav = false;

    // create basic output dka without closure
    for(auto const &tmp : vstupny_stav->podstavy)
    {
        for(const pair<char,stavNKA*> &aa : tmp->getPrechody())
        {
            if(pis == aa.first)
            {
             vystupny_stav->podstavy.insert(aa.second);
             ma_stav = true;
            }
        }
    }
    if(!ma_stav)
        return false;

    // close dka and add other nka

    for(auto const &tmp : vystupny_stav->podstavy)
    {
        closeNKA(tmp,vystupny_stav);
    }

    if(vstupny_stav->names == vystupny_stav->names)
    {
        //cout << "zhodne stavy" << endl;
        vystupny_stav = nullptr;
        free(vystupny_stav);
        vstupny_stav->add_prechod(pis, vstupny_stav);
        return false;
    }
    else
    {

        for(auto const &tmp : stavy)
        {
            if(vystupny_stav->names == tmp->names)
              {
                vstupny_stav->add_prechod(pis,tmp);
                vystupny_stav = nullptr;
                free(vystupny_stav);
                return false;
            }
        }
    }

    stavy.push_back(vystupny_stav);
    vstupny_stav->add_prechod(pis,vystupny_stav);
    return true;

}

//pride prvy nka stav, a prvy dka stav, prebehne prechody najde e do nka, prida do dka
void closeNKA(stavNKA* PRVY, stavDKA* &dka)
{
    dka->names.insert(PRVY->getName());
    dka->podstavy.insert(PRVY);
    //cout << PRVY->getName() <<endl;

    for(const pair<char,stavNKA*> &aa : PRVY->getPrechody())
    {
        if(aa.first == 'e' && (dka->names.count(aa.second->getName()) == 0))
          {
           closeNKA(aa.second,dka);
        }
    }
}

bool load_rules(string file_name, int &nSize_X, int &nSize_Y,vector <char> &abeceda, vector <stavNKA*> &stavy)
{
    ifstream file;
    file.open(file_name);

    string str;
    string line1, line2, line3;
    int i=0;

    if(file){
        for( i=0; i < 2; i++ )
        {
            getline(file, str);
            if ( i == 0 )
            {
                try
                    {
                    nSize_X = stoi(str);
                    }
                catch (int e)
                    {
                    return false ;
                    }
            }
            if ( i == 1 )
            {
             try
                 {
                 nSize_Y = stoi(str);
                 }
             catch (int e)
                 {
                 return false ;
                 }
             }
        }


        for(int j = 0; j < nSize_X; j++)
        {
            size_t pos = 0;
            string delimiter = " ";
            bool poc = false;
            bool akc = false;
            string name;

            getline(file, str);


            if(str.find(delimiter) != std::string::npos)
            {
               pos = str.find(delimiter);
               name = str.substr(0, pos);

               if(str.at(pos+1) == 'I')
                {
                  poc = true;

                   if(str.at(pos+2) == 'F')
                   {
                       akc = true;
                   }
                }

               if(str.at(pos+1) == 'F' )
               {
                  akc=true;
               }
            }
            else
            {
                name=str;
            }

            //stav tmp;
            //stav *tmp(name,poc,akc);
            stavNKA *tmp = new stavNKA(name, poc, akc);
            //cout << "Nazov: " << name << endl;
            //cout << "Poc: " << poc <<  endl;
            //cout << "Akc: " << akc << endl;
            stavy.push_back(tmp);
        }

        for(int k=0 ; k < nSize_Y ; k++)
        {
           getline(file,str);
           abeceda.push_back(str.at(0));
        }


        while(getline(file,str))
        {
            size_t pos = 0;
            string delimiter = ",";

            string akt_name;
            string vs_sym;
            string nasl_name;

            pos = str.find(delimiter);
            akt_name = str.substr(0, pos);
            //cout << "AKT " << akt_name << endl;

            str.erase(0,pos+1);
            pos = str.find(delimiter);
            vs_sym = str.substr(0,pos);
            if(vs_sym.empty())
            {
                vs_sym = 'e';
            }
            //cout << "VS SYM " << vs_sym << endl;

            str.erase(0,pos+1);
            pos = str.find(delimiter);
            nasl_name = str.substr(0,pos);
            //cout << "NASL " << nasl_name << endl;

            stavNKA *a = nullptr;
            stavNKA *b = nullptr;

            for (std::vector<stavNKA*>::iterator it = stavy.begin() ; it != stavy.end(); ++it)
            {
                  //cout << "AKT " << akt_name << endl;
                  //cout << "NASL " << nasl_name << endl;
                  //cout << (*it)->getName() << endl;

                if((*it)->getName() == akt_name)
                {
                    a = *it;
                }
                if((*it)->getName() == nasl_name)
                {
                    b = *it;
                }
            }
            //cout << "A JE " << a->getName() << endl;
            //cout << "B JE " << b->getName() << endl << endl ;
            a->add_prechod(vs_sym.at(0),b);

        }

        return true;

    }
    else
        return false;
}
