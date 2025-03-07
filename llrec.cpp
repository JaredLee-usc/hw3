#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************


void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot){
    smaller = nullptr;
    larger = nullptr;

    // base case
    if(head == nullptr){
        return;
    }

    // store the head node in a temp variable and move the head to the next node
    Node* temp = head;
    head = head -> next;
    temp -> next = nullptr;

    // check if value is less than or equal to pivot
    if(temp->val <= pivot){
        // add to smaller list
        smaller = temp;
        llpivot(head, smaller->next, larger, pivot);
    }
    else {
        // add to larger list
        larger = temp;
        llpivot(head, smaller, larger->next, pivot);
    }
}

