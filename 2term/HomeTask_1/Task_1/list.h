#pragma once

/*
 * List abstract class
 */

class List
{
public:
    List();
    virtual ~List();
    //commented, cause you said, that it is unnesessary :(
    /*
     * +struct ListElement
     * 1
     * Timofey Bryksin
     * jzuken added a note a day ago
     * а он нужен кому за пределами List и его потомков? перенесите его лучше внутрь List
     */
    //ListElement* getPos(int pos);//returns pointer on the element of the list
    unsigned int length();//returns length of list
    virtual void addValue(int value) = 0;//adds last element
    virtual void addPos(int pos, int value) = 0;//adds on position or last element
    virtual void deletePos(int pos) = 0;//deletes element from position or last element
    void print();//prints list
protected:
    struct ListElement
    {
        int elemValue;
        ListElement* next;
    };
    ListElement* head;
    unsigned int size;
};
