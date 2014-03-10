#pragma once

/**
 * @brief The SimpleCalc class
 * @detailed Class, which consists with implementation of evaluator
 */
class SimpleCalc
{
public:
    /**
     * @brief compute Evaluates expression 'result operator secondField'
     * @param result First value
     * @param secondField Second value
     * @param operation Operator
     * @return Result of expression
     */
    int compute(int result, int secondField, int operation);
};
