#pragma once
#include <QMap>
#include <QMapIterator>

template<class T>
class Bag
{
public:
    Bag();
    ~Bag();
    /**
     * @brief add Adds value to Bag
     * @param value Adding value
     */
    void add(T value);
    /**
     * @brief remove Removes value from Bag
     * @param value Removing value
     */
    void remove(T value);
    /**
     * @brief contains Checks if value contains in Bag
     * @param value Checking value
     * @return true if contains, false if not
     */
    bool contains(T value);
    /**
     * @brief quantityOfElement Returns quantity of element 'value' in Bag
     * @param value Element
     * @return Quantity of element 'value'
     */
    unsigned int quantity(T value);
    /**
     * @brief intersectionSet Makes intersection of 2 Bags
     * @param secondSet Another Bag
     * @return Set, consists with intersection of this & secondBag Bags
     */
    Bag<T> intersectionBag(Bag<T> secondBag);
    /**
     * @brief unionBag Makes union of 2 Bags
     * @param secondBag Another Bag
     * @return Set, consists with union of this & secondBag Bags
     */
    Bag<T> unionBag(Bag<T> secondBag);
private:
    QMap<T, unsigned int> map;
};

template<class T>
Bag<T>::Bag()
{
    map.clear();
}

template<class T>
Bag<T>::~Bag()
{
    map.clear();
}

template<class T>
void Bag<T>::add(T value)
{
    if (!contains(value))
    {
        map.insert(value, 1);
    }
    else
    {
        map[value]++;
    }
}

template<class T>
void Bag<T>::remove(T value)
{
    if (contains(value))
    {
        if (map[value] == 1)
        {
            map.remove(value);
        }
        else
        {
            map[value]--;
        }
    }
}

template<class T>
bool Bag<T>::contains(T value)
{
    return map.contains(value);
}

template<class T>
unsigned int Bag<T>::quantity(T value)
{
    if (contains(value))
    {
        return map[value];
    }
    else
    {
        return 0;
    }
}

template<class T>
Bag<T> Bag<T>::intersectionBag(Bag<T> secondBag)
{
    Bag<T> resultBag;
    QMapIterator<T, unsigned int> element(map);
    while (element.hasNext())
    {
        if (secondBag.contains(element.peekNext().key()))
        {
            T addValue = element.next().key();
            unsigned int q1 = quantity(addValue);
            unsigned int q2 = secondBag.quantity(addValue);
            unsigned int addCounter = (q1 < q2 ? q1 : q2);
            for (unsigned int i = 0; i < addCounter; i++)
            {
                resultBag.add(addValue);
            }
        }
        else
        {
            element.next();
        }
    }
    return resultBag;
}

template<class T>
Bag<T> Bag<T>::unionBag(Bag<T> secondBag)
{
    Bag<T> resultBag = secondBag;
    QMapIterator<T, unsigned int> element(map);
    while (element.hasNext())
    {
        T addValue = element.next().key();
        for (unsigned int i = 0; i < quantity(addValue); i++)
        {
            resultBag.add(addValue);
        }
    }
    return resultBag;
}
