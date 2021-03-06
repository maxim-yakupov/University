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
    void add(const T &value);
    /**
     * @brief remove Removes value from Bag
     * @param value Removing value
     */
    void remove(const T &value);
    /**
     * @brief contains Checks if value contains in Bag
     * @param value Checking value
     * @return true if contains, false if not
     */
    bool contains(const T &value) const;
    /**
     * @brief quantityOfElement Returns quantity of element 'value' in Bag
     * @param value Element
     * @return Quantity of element 'value'
     */
    unsigned int quantity(const T &value) const;
    /**
     * @brief intersectionSet Makes intersection of 2 Bags
     * @param secondSet Another Bag
     * @return Set, consists with intersection of this & secondBag Bags
     */
    Bag<T> intersectionBag(const Bag<T> &secondBag) const;
    /**
     * @brief unionBag Makes union of 2 Bags
     * @param secondBag Another Bag
     * @return Set, consists with union of this & secondBag Bags
     */
    Bag<T> unionBag(const Bag<T> &secondBag) const;
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
void Bag<T>::add(const T &value)
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
void Bag<T>::remove(const T &value)
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
bool Bag<T>::contains(const T &value) const
{
    return map.contains(value);
}

template<class T>
unsigned int Bag<T>::quantity(const T &value) const
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
Bag<T> Bag<T>::intersectionBag(const Bag<T> &secondBag) const
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
Bag<T> Bag<T>::unionBag(const Bag<T> &secondBag) const
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
