#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node
{
    int data;
    struct node *next;
}node;

typedef struct BigInteger
{
    node *head;
}BigInteger;

BigInteger initializes(char* str) 
{
    BigInteger num;
    num.head = NULL;
    int length = strlen(str);
    for (int i = 0; i < length; i++) 
    {
        node* newNode = (node*)malloc(sizeof(node));
        newNode->data = str[i] - '0';
        newNode->next = num.head;
        num.head = newNode;
    }
    return num;
}

void rev_display(node *head)
{
    if(head == NULL)
    {
        return;
    }
    rev_display(head->next);
    printf("%d", head->data);
}

void display(BigInteger num)
{
    rev_display(num.head);
    printf("\n");
}

BigInteger add(BigInteger a, BigInteger b) 
{
    BigInteger result; // Create a new BigInteger for the result
    result.head = NULL; // Initialize the result's linked list to be empty
    node* resulthead = NULL; // Temporary pointer to the result's linked list
    node* itr1 = a.head;
    node* itr2 = b.head;
    int carry = 0;
    while (itr1 || itr2 || carry) 
    {
        int sum = carry;
        if (itr1) 
        {
            sum += itr1->data;
            itr1 = itr1->next;
        }
        if (itr2) 
        {
            sum += itr2->data;
            itr2 = itr2->next;
        }
        carry = sum / 10;
        sum = sum % 10;

        node* newnode = (node*)malloc(sizeof(node));
        newnode->data = sum;
        newnode->next = NULL;
        if (!resulthead) 
        {
            resulthead = newnode;
            result.head = resulthead; // Update the result's head
        } 
        else 
        {
            node* temp = resulthead;
            while (temp->next != NULL) 
            {
                temp = temp->next;
            }
            temp->next = newnode;
        }
    }
    return result;
}


node * reverse(node *head)
{
    node *prev = NULL;
    node *curr = head;
    while(curr)
    {
        node *temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }
    return prev;
}

node * createNode(int data)
{
    node *newnode = (node *)malloc(sizeof(node));
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}

void insertAtEnd(node** head, int data) 
{
    node* newNode = createNode(data);
    if (*head == NULL) 
    {
        *head = newNode;
    } 
    else 
    {
        node* current = *head;
        while (current->next != NULL) 
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

BigInteger sub(BigInteger a, BigInteger b) 
{
    BigInteger result; // Create a new BigInteger for the result
    result.head = NULL; // Initialize the result's linked list to be empty

    node* resulthead = NULL; // Temporary pointer to the result's linked list
    node* current1 = a.head;
    node* current2 = b.head;
    int borrow = 0;
    while (current1 || current2) 
    {
        int digit1 = (current1 != NULL) ? current1->data : 0;
        int digit2 = (current2 != NULL) ? current2->data : 0;

        int difference = digit1 - digit2 - borrow;
        if (difference < 0) 
        {
            difference += 10;
            borrow = 1;
        } 
        else 
        {
            borrow = 0;
        }

        node *newnode = (node *)malloc(sizeof(node));
        newnode->data = difference;
        newnode->next = NULL;
        if(!resulthead)
        {
            resulthead = newnode;
            result.head = resulthead; // Update the result's head
        }
        else
        {
            node *temp = resulthead;
            while(temp->next != NULL)
            {
                temp = temp->next;
            }   
            temp->next = newnode;
        }

        if (current1 != NULL) 
        {
            current1 = current1->next;
        }
        if (current2 != NULL) 
        {
            current2 = current2->next;
        }
    }
    return result;
}

BigInteger mul(BigInteger a, BigInteger b) 
{
    BigInteger result;
    result.head = NULL; // Initialize the result's linked list to be empty

    if (a.head == NULL || b.head == NULL) 
    {
        return result;
    }

    int position = 0;
    node* currentNum2 = b.head;

    while (currentNum2 != NULL) 
    {
        node* currentResult = NULL;
        int carry = 0;

        // Handle shifting left (multiplying by powers of 10)
        for (int i = 0; i < position; i++) 
        {
            insertAtEnd(&currentResult, 0);
        }

        node* currentNum1 = a.head;
        
        while (currentNum1 != NULL) 
        {
            int product = (currentNum1->data) * (currentNum2->data) + carry;
            carry = product / 10;
            insertAtEnd(&currentResult, product % 10);
            currentNum1 = currentNum1->next;
        }

        if (carry > 0) 
        {
            insertAtEnd(&currentResult, carry);
        }

        // Convert currentResult into a BigInteger and add it to the result
        BigInteger temp1;
        temp1.head = currentResult;
        result = add(result, temp1);

        currentNum2 = currentNum2->next;
        position++;
    }

    return result;
}

void append(BigInteger* num, int digit) {
    // Create a new node
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = digit;
    newNode->next = NULL;

    if (num->head == NULL) {
        num->head = newNode;
    } else {
        node* current = num->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

int length(BigInteger a)
{
    node *itr = a.head;
    int len =0;
    while(itr!=NULL)
    {
        len++;
        itr = itr->next;
    }
    return len;
}