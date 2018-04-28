#ifndef STAVNKA_H
#define STAVNKA_H
#include <string>
#include <set>
#include <iostream>

using namespace std;


class stavNKA
{

public:
    string name;
    bool pociatocny;
    bool akceptacny;
    set<pair <char, stavNKA*>> prechody;


    stavNKA(string name, bool poc, bool akc);
    stavNKA();

    void add_prechod(char vs_sym, stavNKA *stavu);

    string getName() const;
    void setName(const string &value);

    set<pair<char, stavNKA *> > getPrechody() const;
    void setPrechody(const set<pair<char, stavNKA*> > &value);

    bool getPociatocny() const;
    void setPociatocny(bool value);

    bool getAkceptacny() const;
    void setAkceptacny(bool value);
};

#endif // STAV_H
