/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode * reverseList(struct ListNode* head)
{
    if (!head || !head->next) return head;
    
    struct ListNode * prev = NULL;
    struct ListNode * cur = head;
    struct ListNode * next = head->next;
    
    while (next)
    {
        cur->next = prev;
        prev = cur;
        cur = next;
        next = next->next;
    }
    cur->next = prev;
    
    return cur;
}

struct ListNode * mergeLists(struct ListNode * listA, struct ListNode * listB)
{
    if (!listA) return listB;
    if (!listB) return listA;

    struct ListNode * i, * j, *temp;
    i = listA;
    j = listB;
    struct ListNode newHead;
    temp = &newHead;
    
    while (i && j)
    {
        temp->next = i;
        i = i->next;
        temp = temp->next;
        
        temp->next = j;
        j = j->next;
        temp = temp->next;
    }
    if (!i) temp->next = j;
    else if (!j) temp->next = i;
    
    return newHead.next;
    
}

void reorderList(struct ListNode* head) {
    if (!head || !head->next) return;
    
    struct ListNode * fast = head;
    struct ListNode * slow = head;
    
    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    fast = head;
    while (fast->next != slow)
    {
        fast = fast->next;
    }
    
    fast->next = reverseList(slow);
    slow = fast->next;
    fast->next = NULL;
    head = mergeLists(head, slow); 
}
