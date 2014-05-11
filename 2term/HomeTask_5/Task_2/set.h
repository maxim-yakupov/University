#pragma once
#include <QList>
#include <QListIterator>

template<class T>
class Set
{
public:
    Set();
    ~Set();
    /**
     * @brief add Adds value to set
     * @param value Adding value
     */
    void add(T value);
    /**
     * @brief remove Removes value from set
     * @param value Removing value
     */
    void remove(T value);
    /**
     * @brief contains Checks if value contains in set
     * @param value Checking value
     * @return true if contains, false if not
     */
    bool contains(T value) const;
    /**
     * @brief intersectionSet Makes intersection of 2 sets
     * @param secondSet Another set
     * @return Set, consists with intersection of this & seconSet sets
     */
    Set<T> intersectionSet(const Set<T> &secondSet);
    /**
     * @brief unionSet Makes union of 2 sets
     * @param secondSet Another set
     * @return Set, consists with union of this & seconSet sets
     */
    Set<T> unionSet(const Set<T> &secondSet);
private:
    QList<T> list;
};

template<class T>
Set<T>::Set()
{
    list.clear();
}

template<class T>
Set<T>::~Set()
{
    list.clear();
}

template<class T>
void Set<T>::add(T value)
{
    if (!contains(value))
    {
        list.append(value);
    }
}

template<class T>
void Set<T>::remove(T value)
{
    if (contains(value))
    {
        list.removeOne(value);
    }
}

template<class T>
bool Set<T>::contains(T value) const
{
    return list.contains(value);
}

template<class T>
Set<T> Set<T>::intersectionSet(const Set<T> &secondSet)
{
    Set<T> resultSet;
    QListIterator<T> element(list);
    while (element.hasNext())
    {
        if (secondSet.contains(element.peekNext()))
        {
            resultSet.add(element.next());
        }
        else
        {
            element.next();
        }
    }
    return resultSet;
}

template<class T>
Set<T> Set<T>::unionSet(const Set<T> &secondSet)
{
    Set<T> resultSet = secondSet;
    QListIterator<T> element(list);
    while (element.hasNext())
    {
        if (!resultSet.contains(element.peekNext()))
        {
            resultSet.add(element.next());
        }
        else
        {
            element.next();
        }
    }
    return resultSet;
}
