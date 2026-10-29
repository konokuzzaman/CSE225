#include "unsortedtype.h"
#include <iostream>
using namespace std;

template <class T,class Y>
UnsortedType<T,Y>::UnsortedType()
{
    head = NULL;
    pointTo = NULL;
    size = 0;
}

template <class T,class Y>
int UnsortedType<T,Y>::Length()
{
    return size;
}

template <class T,class Y>
void UnsortedType<T,Y>::Insert(T value,Y link)
{
Node* temp = new Node;
temp->data = value;
temp->edge =link;
temp->next = head;
head = temp;
size++;
}
template <class T,class Y>
void UnsortedType<T,Y>::Search(T value, bool &found)
{
found = false;
Node* i = head;
while(i != NULL)
{
if (value == i->data)
{
found  = true;
break;
}
else
{
i = i->next;
}
}
}
template <class T,class Y>
void UnsortedType<T,Y>::Delete(T value)
{
Node* i = head;
Node* prev = NULL;
bool found = false;
while(i != NULL)
{
if (value == i->data)
{
found = true;
break;
}
else
{
prev = i;
i = i->next;
}
}
if (found)
{
if (prev == NULL) // first node / no previous nodes
head = i->next;
else
prev->next = i->next;
delete i;
size--;
}
}
template <class T,class Y>
void UnsortedType<T,Y>::MakeEmpty()
{
    Node* i = head;
    Node* nextNode;

    while (i != NULL)
    {
        nextNode = i->next; // Store the next node
        delete i;           // Delete the current node
        i = nextNode;       // Move to the next node
    }

    head = NULL;
    size = 0;
}

template <class T,class Y>
UnsortedType<T,Y>::~UnsortedType()
{
    MakeEmpty();
}

template <class T,class Y>
void UnsortedType<T,Y>::GetNext(T &value,Y &link)
{
    if (pointTo == NULL)
    {
        pointTo = head;
        value = pointTo->data;
        link = pointTo->edge;
    }
    else
    {
        value = pointTo->data;
        link = pointTo->edge;
    }
    pointTo = pointTo->next;
}

template <class T,class Y>
void UnsortedType<T,Y>::Reset()
{
    pointTo = NULL;
}

