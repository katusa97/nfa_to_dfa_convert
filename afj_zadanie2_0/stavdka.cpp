#include "stavDKA.h"

set<string> stavDKA::getNames() const
{
    return names;
}

void stavDKA::setNames(const set<string> &value)
{
    names = value;
}

bool stavDKA::getPociatocny() const
{
    return pociatocny;
}

void stavDKA::setPociatocny(bool value)
{
    pociatocny = value;
}

stavDKA::stavDKA()
{

}


stavDKA::stavDKA(set<string> namesx, bool poc, bool akc)
{
    //int i=0; i <= namesx.size(); i++
    for (const string& kk : namesx)
    {
       this->names.insert(kk);
    }

    this->pociatocny = poc;
    this->akceptacny = akc;
}

void stavDKA::add_prechod(char vs_sym, stavDKA *stavu)
{
    pair <char, stavDKA*> prechod;
    prechod = make_pair(vs_sym,stavu);
    this->prechody.insert(prechod);
}

set<pair<char, stavDKA *> > stavDKA::getPrechody() const
{
    return prechody;
}

void stavDKA::setPrechody(const set<pair<char, stavDKA *> > &value)
{
    prechody = value;
}
