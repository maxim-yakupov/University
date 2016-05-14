#pragma once

/**
 * @brief The MathNode class
 */
class MathNode
{
public:
    virtual ~MathNode(){}
    /**
     * @brief compute Computes node's value
     * @return Result of calculation
     */
    //
    MathNode(MathNode *l, MathNode *r)
    {
        left = l;
        right = r;
    }//
    virtual double compute(){ return 0; }
    /**
     * @brief print Writes expression from the node
     */
    virtual void print(){}
protected:
    MathNode* left;
    MathNode* right;
};
