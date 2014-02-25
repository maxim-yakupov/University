#include "polynome.h"

namespace Polynomes
{
    Polynome* createPolynome()
    {
        return new Polynome {nullptr};
    }

    void addMember(Polynome* polynome, int mult, int exp)
    {
        if (!polynome->highExp)
        {
            polynome->highExp = new Member {mult, exp, nullptr};
            return;
        }
        if (polynome->highExp->exp < exp)
        {
            polynome->highExp = new Member {mult, exp, polynome->highExp};
            return;
        }
        if (polynome->highExp->exp == exp)
        {
            polynome->highExp->multiplier += mult;
            return;
        }
        Member* current = polynome->highExp;
        while (current->next && (current->next->exp > exp))
        {
            current = current->next;
        }
        if (!current->next)
        {
            current->next = new Member {mult, exp, nullptr};
        }
        else if (current->next->exp == exp)
        {
            current->next->multiplier += mult;
        }
        else
        {
            current->next = new Member {mult, exp, current->next};
        }
    }

    double pow(int x, int exp)
    {
        if (!exp)
        {
            return 1;
        }
        else if (exp > 0)
        {
            double result = x;
            for (int i = 1; i < exp; i++)
            {
                result *= x;
            }
            return result;
        }
        else
        {
            double result = 1 / (double) x;
            for (int i = exp; i < -1; i++)
            {
                result /= x;
            }
            return result;
        }
    }

    double value(Polynome* polynome, int x)//!!
    {
        Member* current = polynome->highExp;
        double result = 0;
        while (current)
        {
            result += current->multiplier * pow(x, current->exp);
            current = current->next;
        }
        return result;
    }

    void add(Polynome* p, Polynome* q, Polynome* r)//!!
    {
        Member* current = p->highExp;
        while (current)
        {
            addMember(r, current->multiplier, current->exp);
            current = current->next;
        }
        current = q->highExp;
        while (current)
        {
            addMember(r, current->multiplier, current->exp);
            current = current->next;
        }
    }

    bool equals(Polynome* polynomeOne, Polynome* polynomeTwo)//!!
    {
        Member* firstCurrent = polynomeOne->highExp;
        Member* secondCurrent = polynomeTwo->highExp;
        while (firstCurrent && secondCurrent)
        {
            if (!(firstCurrent->exp == secondCurrent->exp && firstCurrent->multiplier == secondCurrent->multiplier))
            {
                return false;
            }
            firstCurrent = firstCurrent->next;
            secondCurrent = secondCurrent->next;
        }
        if (firstCurrent || secondCurrent)
        {
            return false;
        }
        return true;
    }

    void deletePolynome(Polynome* polynome)
    {
        while (polynome->highExp)
        {
            Member* next = polynome->highExp->next;
            delete polynome->highExp;
            polynome->highExp = next;
        }
        delete polynome;
    }
}
