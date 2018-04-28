#include "stavNKA.h"

string stavNKA::getName() const
{
    return name;
}

void stavNKA::setName(const string &value)
{
    name = value;
}

set<pair<char, stavNKA *> > stavNKA::getPrechody() const
{
    return prechody;
}

void stavNKA::setPrechody(const set<pair<char, stavNKA *> > &value)
{
    prechody = value;
}

bool stavNKA::getPociatocny() const
{
    return pociatocny;
}

void stavNKA::setPociatocny(bool value)
{
    pociatocny = value;
}

bool stavNKA::getAkceptacny() const
{
    return akceptacny;
}

void stavNKA::setAkceptacny(bool value)
{
    akceptacny = value;
}

stavNKA::stavNKA(string name, bool poc, bool akc)
{
    this->name = name;
    this->pociatocny = poc;
    this->akceptacny = akc;
}

stavNKA::stavNKA()
{
}

void stavNKA::add_prechod(char vs_sym, stavNKA *stavu)
{
    pair <char, stavNKA*> prechod;
    prechod = make_pair(vs_sym,stavu);
    this->prechody.insert(prechod);
}
