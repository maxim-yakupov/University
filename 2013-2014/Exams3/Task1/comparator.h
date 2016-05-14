#pragma once

template<class T>
/**
 * @brief The Comparator class
 */
class Comparator
{
public:
    /**
     * @brief compare Criterium of sort
     * @param a First comparable element
     * @param b Second comparable element
     * @return Result of compare
     */
    virtual bool compare(T a, T b) const;
};

template<class T>
bool Comparator<T>::compare(T a, T b) const
{
    return a < b;
}
