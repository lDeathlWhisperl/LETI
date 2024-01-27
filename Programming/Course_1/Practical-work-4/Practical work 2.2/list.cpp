#include "List.h"
#include <iostream>

List::List()
{
	head = tail = NULL;
	size = 0;
}

List::~List()
{
	erase();
}

int List::getSize()
{
	return size;
}

node* List::getElem(int index)
{
	node* temp = head;

	for(int i = 0; i < index; i++)
		temp = temp->next;

	if (!temp) return 0;
	else return temp;
}

void List::del(int index)
{
	node* del = getElem(index);

	node* PrevDel = del->prev;
	node* AfterDel = del->next;

	if (PrevDel != 0 && size != 1)
		PrevDel->next = AfterDel;
	if (AfterDel != 0 && size != 1)
		AfterDel->prev = PrevDel;

	if (index == 0)
		head = AfterDel;
	if (index == size-1)
		tail = PrevDel;

	delete del;
	size--;
}

void List::erase()
{
	while (size != 0) del(0);
}

void List::addTail(int num)
{
	node* temp = new node;
	temp->next = 0;
	temp->data = num;
	temp->prev = tail;

	if (tail != 0)
		tail->next = temp;

	if (size == 0)
		head = tail = temp;
	else
		tail = temp;
	size++;
}

void List::addHead(int num)
{
	node* temp = new node;

	temp->prev = 0;
	temp->data = num;
	temp->next = head;

	if (head != 0)
		head->prev = temp;

	if (size == 0)
		head = tail = temp;
	else
		head = temp;
	size++;
}

void List::insert(int index, int data)
{
	if (index == size)
	{
		addTail(data);
		return;
	}
	else if (index == 0)
	{
		addHead(data);
		return;
	}

	node* insert = getElem(index);

	node* prevIns = insert->prev;

	node* temp = new node;

	temp->data = data;

	if (prevIns != 0 && size != 1)
		prevIns->next = temp;

	temp->next = insert;
	temp->prev = prevIns;
	insert->prev = temp;

	size++;
}

void List::print(int index_1, int index_2)
{
	node* p = tail;
	int i = 0;
	while (p->prev != NULL)
		p = p->prev;
	do {
		if (i == index_1) std::cout << "\x1b[32m";
		if (i == index_2) std::cout << "\x1b[34m";
		std::cout << p->data << ' ';
		if (i == index_1 || i == index_2) std::cout << "\x1b[0m";
		p = p->next;
		i++;
	} while (p != NULL);
}

void List::print(unsigned int index)
{
	node* temp;

	if (index < size / 2)
	{
		temp = head;

		for (int i = 0; i < index; i++)
			temp = temp->next;
	}
	else
	{
		temp = tail;

		for (int i = 0; i < size - index-1; i++)
			temp = temp->prev;
	}

	std::cout << '[' << index << "] element: " << temp->data << '\n';
}

void List::swap(int index_1, int index_2)
{
	node* first = getElem(index_1);
	node* second = getElem(index_2);

	node
		* f_prev = first->prev,
		* f_next = first->next,
		* s_prev = second->prev,
		* s_next = second->next;

	if (abs(index_1 - index_2) == 1)
	{
		second->prev = f_prev;
		second->next = first;

		first->prev = second;
		first->next = s_next;

		if (s_next != NULL) s_next->prev = first;
		if (first != head) f_prev->next = second;
	}
	else
	{
		if (first != head)  f_prev->next = second;
		if (second != head) s_prev->next = first;
		
		second->next = f_next;
		first->next = s_next;

		second->prev = f_prev;
		first->prev = s_prev;

		if (s_next != NULL) s_next->prev = first;
		if (f_next != NULL) f_next->prev = second;
	}

	while (head->prev) head = head->prev;
	while (tail->next) tail = tail->next;
}