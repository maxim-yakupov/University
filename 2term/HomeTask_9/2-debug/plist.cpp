#include <stdio.h>
#include "plist.h"

PList::PList()
{
}

PList::~PList()
{
	removeList();
	delete head;
}

int PList::length()
{
	return head->value;
}

void PList::add(int value, int num)
{
	if (num <= head->value)
		{
			int k = 1;
			Node *tmp = head;
			while (k < num)
			{
				tmp = tmp->next;
				k++;
			}
			Node *tmp2 = new Node;
			tmp2->value = value;
			tmp2->next = tmp->next->next;
			tmp->next->next = tmp2;
			k++;
		}
	else
		{
			Node *tmp = head;
			while (tmp->next)
			{
				tmp = tmp->next;
			}
			Node *tmp2 = new Node;
			tmp2->value = value;
			tmp2->next = tmp->next;
			tmp->next = tmp2;
		}
}

void PList::del(int num)
{
	if ((num <= head->value) && (num > 0))
		{
			int k = 1;
			Node *tmp = head;
			while (k < num)
			{
				tmp = tmp->next;
				k++;
			}
			Node *tmp2 = tmp->next;
			tmp->next = tmp->next->next;
			delete tmp2;
			head->value--;
		}
}

void PList::removeList()
{
	while (head->next == NULL)
		del(1);
	head->value = 0;
}

int PList::returnValue(int num)
{
	if ((num <= head->value) && (num > 0))
	{
		int k = 1;
		Node *tmp = head;
		while (k < num)
		{
			tmp = tmp->next;
			k++;
		}
		return tmp->next->next->value;
	}
	else
		return -32000;
}

void PList::printList()
{
	Node *tmp = head;
	while(tmp->next)
	{
		tmp = tmp->next;
		printf("%i ", tmp->value);
	}
}

void PList::swap(int i, int j)
{
	if ((i <= head->value) && (i > 0) && (j <= head->value) && (j > 0))
	{
		int k = 1;
		Node *tmp = head;
		while (k <= i)
		{
			tmp = tmp->next;
			k++;
		}
		k = 1;
		Node *tmp2 = head;
		while (k < j)
		{
			tmp2 = tmp2->next;
			k++;
		}
		int a = tmp->next->value;
		tmp->next->value = tmp2->next->value;
		tmp2->next->value = a;
	}
}
