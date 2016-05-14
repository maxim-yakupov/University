#pragma once



/* SimpleListElement class */


class SimpleListElement{
	public:
		SimpleListElement();
		SimpleListElement(SimpleListElement *prevElement, int number);
		virtual SimpleListElement *getNext();
		int getValue();
		void setNext(SimpleListElement *nextElement);
		void setValue(int number);
	private:
		int value;
		SimpleListElement *next;
};



/* DoubleListElement class */



class DoubleListElement : public SimpleListElement{

	public:
		DoubleListElement();
		DoubleListElement(DoubleListElement *prevElement, int number);
		DoubleListElement *getPrev();
		DoubleListElement *getNext();
		static DoubleListElement *toDoubleListElement(SimpleListElement *element);
		void setPrev(DoubleListElement *prevElement);
	private:
		DoubleListElement *prev;
};



/* SimpleList class */



class SimpleList{
	public:
		SimpleList();
		~SimpleList();
		virtual SimpleListElement* getHead();
		virtual void addElement(int number);
		virtual SimpleListElement *findPrevElement(int number);
		virtual void deleteElement(int number);
	protected:
		void setHead(SimpleListElement *element);
		SimpleListElement *head;
};



/* DoubleList class */



class DoubleList : public SimpleList{

	public:
		DoubleList();
		DoubleList* toDoubleList(SimpleList *list);
		virtual DoubleListElement* getHead();
		void addElement(int number);
		DoubleListElement *findPrevElement(int number);
		void deleteElement(int number);
};

