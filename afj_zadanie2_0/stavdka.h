#ifndef STAVDKA_H
#define STAVDKA_H
#include <string>
#include <set>
#include <iostream>
#include <vector>
#include "stavNKA.h"

using namespace std;

class stavDKA
{
public:
    set<string> names;
    set<stavNKA*> podstavy;
    bool pociatocny;
    bool akceptacny;
    set <pair <char, stavDKA*>> prechody;


    stavDKA();
    stavDKA(set<string> names, bool poc, bool akc);

    void add_prechod(char vs_sym, stavDKA *stavu);

    set<string> getNames() const;
    void setNames(const set<string> &value);

    bool getPociatocny() const;
    void setPociatocny(bool value);

    set<pair<char, stavDKA *> > getPrechody() const;
    void setPrechody(const set<pair<char, stavDKA *> > &value);
};

#endif // STAVDKA_H
