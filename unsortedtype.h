#ifndef UNSORTEDTYPE_H
#define UNSORTEDTYPE_H

template <class T,class Y>
class UnsortedType
{
    public:
    struct Node
    {
        T data;
        Y edge;
        Node* next;
    };
    Node* head;
    Node* pointTo;
    int size;
    UnsortedType();
    ~UnsortedType();
    int Length();
    void Insert(T value,Y link);
    void Search(T value, bool &found);
    void Delete(T value);
    void MakeEmpty();
    void GetNext(T &value,Y &link);
    void Reset();
    Node* GetHead();
};
#endif // UNSORTEDTYPE_H
