#include <iostream>
#include "mathtree.h"
#include "div.h"
#include "sum.h"
#include "sub.h"
#include "num.h"
#include "mult.h"

void MathTree::operator()(char *inStr)
{
    unsigned int pos = 0;
    unsigned int length = strlen(inStr);
    char* strExpr = new char[length + 1];
    while (length)
    {
        strExpr[pos] = inStr[pos];
        ++pos;
        --length;
    }
    strExpr[pos] = '\0';

    delete root;
    root = nullptr;
    curPos = 0;

    root = makeTree(strExpr/*inStr*/);

    delete [] strExpr;
}

MathTree::MathTree()
{
    root = nullptr;
    curPos = 0;
    this->operator ()("0");
}

MathTree::MathTree(char *incomeExpr)
{
    root = nullptr;
    curPos = 0;
    this->operator ()(incomeExpr);
}

MathTree::~MathTree()
{
    delete root;
}

void MathTree::print()
{
    root->print();
}

double MathTree::compute()
{
    return root->compute();
}

int MathTree::strlen(char* str)
{
    int length = 0;
    while (*(str + length) != '\0')
    {
        length++;
    };
    return length;
}

double MathTree::readDoubleFromStr(char *str)
{
    bool minus = (str[curPos] == '-');
    if (minus)
    {
        curPos++;
    }
    double result = 0;
    while ((str[curPos] >= '0') && (str[curPos] <= '9'))
    {
        result = result * 10 + (str[curPos] - '0');
        curPos++;
    }
    if (str[curPos] == '.')
    {
        curPos++;
        double mult = 0.1;
        while ((str[curPos] >= '0') && (str[curPos] <= '9'))
        {
            result += (str[curPos] - '0') * mult;
            mult /= 10;
            curPos++;
        }
    }
    if (minus)
    {
        result *= -1;
    }
    return result;
}

MathNode *MathTree::makeTree(char *str)
{
//    unsigned int pos = curPos;
    MathNode* node;
    char ch = str[curPos];
    ++curPos;
    if (ch == '(')
    {
        ch = str[curPos];
        curPos++;
        curPos++;
        MathNode* l = makeTree(str);
        curPos++;
        MathNode* r = makeTree(str);
        switch (ch) {
        case '+':
        {
            node = new Sum(l, r);
            break;
        }
        case '-':
        {
            node = new Sub(l, r);
            break;
        }
        case '/':
        {
            node = new Div(l, r);
            break;
        }
        case '*':
        {
            node = new Mult(l, r);
            break;
        }
        default:
            break;
        }
        curPos++;
    }
    else
    {
        curPos--;
        node = new Num(readDoubleFromStr(str));
    }
    return node;
}
