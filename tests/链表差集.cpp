#include <iostream>
using namespace std;

class listNode{
    public:
        int data;
        listNode* next;
        listNode(int value):data(value),next(nullptr){}
};

listNode* createList(int n)
{
    listNode* head = new listNode(0);
    listNode* tail = head;
    for(int i = 0;i < n;i++)
    {
        int val;
        cin >> val;
        tail->next = new listNode(val);
        tail =  tail->next;
    }
    return head;
}

pair<listNode*, int> difference(listNode* head1, listNode* head2)
{
    listNode* c = new listNode(0);
    listNode* tail = c;
    listNode* p1 = head1;
    listNode* p2 = head2;
    while(p1 && p2)// 遍历两个链表
    {
        if(p1->data < p2->data)
        {
            
        }
    }
}