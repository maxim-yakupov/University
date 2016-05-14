#include "list.h"



/* SimpleListElement Interface */



void SimpleListElement::setNext(SimpleListElement *nextElement) {
	this->next = nextElement;
}

void SimpleListElement::setValue(int number) {
	this->value = number;
}

SimpleListElement* SimpleListElement::getNext() {
	return this->next;
}

int SimpleListElement::getValue() {
	return this->value;
}

SimpleListElement::SimpleListElement() {
	this->setNext(nullptr);
	this->setValue(0);
}

SimpleListElement::SimpleListElement(SimpleListElement *prevElement, int number) {
	this->setNext(prevElement->getNext());
	prevElement->setNext(this);
	this->setValue(number);
}

/* DoubleListElement Interface */



void DoubleListElement::setPrev(DoubleListElement *prevElement) {
	this->prev = prevElement;
}

DoubleListElement* DoubleListElement::getPrev() {
	return this->prev;
}

DoubleListElement* DoubleListElement::getNext() {
	return toDoubleListElement(this->SimpleListElement::getNext());
}

DoubleListElement::DoubleListElement() : SimpleListElement() {
	this->setPrev(nullptr);
}

DoubleListElement* DoubleListElement::toDoubleListElement(SimpleListElement *element) {
	return dynamic_cast<DoubleListElement*>(element);
}

DoubleListElement::DoubleListElement(DoubleListElement *prevElement, int number) : SimpleListElement(prevElement, number) {
	this->setPrev(prevElement);
	if (this->getNext() != nullptr)
		toDoubleListElement(this->getNext())->setPrev(this);
}



/* SimpleList Interface */



void SimpleList::setHead(SimpleListElement *element) {
	this->head = element;
}

SimpleList::SimpleList() {
	SimpleListElement *newElement = new SimpleListElement();
	this->setHead(newElement);
}

SimpleList::~SimpleList() {
	SimpleListElement *currentElement = this->getHead()->getNext();
	while (currentElement != nullptr) {
		this->deleteElement(currentElement->getValue());
		currentElement = this->getHead()->getNext();
	}
	delete this->getHead();
}

SimpleListElement* SimpleList::getHead() {
	return this->head;
}

void SimpleList::addElement(int number) {
	SimpleListElement *newElement = new SimpleListElement(this->getHead(), number);
}

void SimpleList::deleteElement(int number) {
	SimpleListElement *prevElement = findPrevElement(number);
	if (prevElement->getNext() != nullptr) {
		SimpleListElement *toDelete = prevElement->getNext();
		prevElement->setNext(prevElement->getNext()->getNext());
		delete toDelete;
	}
}

SimpleListElement* SimpleList::findPrevElement(int number) {
	SimpleListElement *currentElement = this->getHead();

	while (currentElement->getNext() != nullptr && currentElement->getNext()->getValue() != number)
		currentElement = currentElement->getNext();

	if (currentElement->getNext() == nullptr)
		return nullptr;
	else
		return currentElement;
}

/* DoubleList interface */



DoubleList::DoubleList() {
	DoubleListElement *newElement = new DoubleListElement();
	this->setHead(newElement);
}

DoubleListElement* DoubleList::getHead() {
	return DoubleListElement::toDoubleListElement(this->SimpleList::getHead());
}

void DoubleList::addElement(int number) {
	DoubleListElement *newElement = new DoubleListElement(this->getHead(), number);
}

DoubleListElement* DoubleList::findPrevElement(int number) {
	return DoubleListElement::toDoubleListElement(this->SimpleList::findPrevElement(number));
}

void DoubleList::deleteElement(int number) {
	DoubleListElement *prevElement = this->findPrevElement(number);
	if (prevElement->getNext() != nullptr) {
		DoubleListElement *nextElement = prevElement->getNext()->getNext();
		if (nextElement != nullptr)
			nextElement->setPrev(prevElement);
	}
	this->SimpleList::deleteElement(number);
}
