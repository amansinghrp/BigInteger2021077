#ifndef bigint_h
#define bigint_h

typedef struct node
{
    int data;
    struct node *next;
}node;

typedef struct BigInteger
{
    node *head;
}BigInteger;

BigInteger initialize(char* str);
void rev_display(node *head);
void display(BigInteger num);
BigInteger add(BigInteger a, BigInteger b);
node * reverse(node *head);
node * createNode(int data);
void insertAtEnd(node** head, int data);
BigInteger sub(BigInteger a, BigInteger b);
BigInteger mul(BigInteger a, BigInteger b);
void append(BigInteger* num, int digit);
int length(BigInteger a);

#endif
