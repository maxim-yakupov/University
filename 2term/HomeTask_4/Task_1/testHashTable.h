#pragma once

#include <QtTest/QTest>
#include <QtCore/QObject>

#include "hashtable.h"

class TestHashTable : public QObject
{
    Q_OBJECT
public:
    explicit TestHashTable(QObject *parent = 0) : QObject(parent) {}
private:
    HashTable *table;
private slots:
    void init()
    {
        table = new HashTable(20);
    }
    void testEmptyHashTableAdd()
    {
        table->add("1");
        QCOMPARE(table->operator []("1"), "1");
    }
    void testEmptyHashTableRemove()
    {
        table->remove("1");
        QCOMPARE((table->operator []("1") ? true : false), false);
    }
    void testEmptyHashTableSize()
    {
        QCOMPARE(static_cast<int>(table->size()), 20);
    }
    void testHashTableNumberOfUniqueElements()
    {
        table->add("1");
        table->add("1");
        table->add("1");
        table->add("2");
        table->add("2");
        table->add("3");
        QCOMPARE(static_cast<int>(table->numberOfUniqueElements()), 3);
    }
    void testHashTableNumberOfConflicts()
    {
        table->add("char");
        table->add("egg");
        table->add("qdjkw;");
        table->add("!!!");
        table->add("iluhyrg");
        table->add("wevv wev");
        table->add("iluhyrg");
        table->add("egg");
        table->add("1");
        table->add("2");
        table->add("3");
        table->add("4");
        table->add("5");
        QCOMPARE(static_cast<int>(table->numberOfConflicts()), 4);
    }
    void testHashTableBiggestLengthOfConflict()
    {
        table->add("char");
        table->add("egg");
        table->add("qdjkw;");
        table->add("!!!");
        table->add("iluhyrg");
        table->add("wevv wev");
        table->add("iluhyrg");
        table->add("egg");
        table->add("1");
        table->add("2");
        table->add("3");
        table->add("4");
        table->add("5");
        QCOMPARE(static_cast<int>(table->biggestLengthOfConflict()), 3);
    }
    void testHashTableLoadFactor()
    {
        table->add("char");
        table->add("egg");
        table->add("qdjkw;");
        table->add("!!!");
        table->add("iluhyrg");
        table->add("wevv wev");
        table->add("iluhyrg");
        table->add("egg");
        table->add("1");
        table->add("2");
        table->add("3");
        table->add("4");
        table->add("5");
        QCOMPARE(table->loadFactor(), static_cast<double>(11)/20);
    }
    void testHashTableChangeHashFunction()
    {
        table->add("char");
        table->add("egg");
        table->add("qdjkw;");
        table->add("!!!");
        table->add("iluhyrg");
        table->add("wevv wev");
        table->add("iluhyrg");
        table->add("egg");
        table->add("1");
        table->add("2");
        table->add("3");
        table->add("4");
        table->add("5");
        QCOMPARE(table->operator []("1"), "1");
        QCOMPARE(table->operator []("2"), "2");
        QCOMPARE(table->operator []("3"), "3");
        QCOMPARE(table->operator []("4"), "4");
        QCOMPARE(table->operator []("5"), "5");
        QCOMPARE(table->operator []("egg"), "egg");
        QCOMPARE(table->operator []("char"), "char");
        table->operator ()(
                              [](char* str)
                              {
                                  int res = 0;
                                  while(str[0])
                                  {
                                      res = (res * 3 - 100 + str[0] - '0') % 3;
                                      str++;
                                  };
                                  return res;
                              }
                          );
        QCOMPARE(table->operator []("1"), "1");
        QCOMPARE(table->operator []("2"), "2");
        QCOMPARE(table->operator []("3"), "3");
        QCOMPARE(table->operator []("4"), "4");
        QCOMPARE(table->operator []("5"), "5");
        QCOMPARE(table->operator []("egg"), "egg");
        QCOMPARE(table->operator []("char"), "char");
    }
    void cleanup()
    {
        delete table;
    }
};
