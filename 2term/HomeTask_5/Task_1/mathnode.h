#pragma once

class MathNode
{
public:
    virtual ~MathNode(){}
    virtual double compute(){}
    virtual void print(){}
protected:
    MathNode* left;
    MathNode* right;
};
