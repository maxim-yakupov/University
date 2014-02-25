#pragma once

namespace Polynomes
{
    struct Member
    {
        int multiplier;
        int exp;
        Member* next;
    };

    struct Polynome
    {
        Member* highExp;
    };

    Polynome* createPolynome();
    void addMember(Polynome* polynome, int mult, int exp);
    double value(Polynome* polynome, int x);
    void add(Polynome* p, Polynome* q, Polynome* r);
    bool equals(Polynome* polynomeOne, Polynome* polynomeTwo);
    void deletePolynome(Polynome* polynome);
}
