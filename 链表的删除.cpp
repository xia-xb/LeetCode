/*
 * @Author: your name
 * @Date: 2021-05-12 23:37:27
 * @LastEditTime: 2021-05-12 23:39:02
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\链表的删除.cpp
 */

/* 19题删除链表的倒数第N个结点 */
/* 遍历两次，统计链表长度 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* tmp = head;
        int length = 0;
        while (tmp) {
            length++;
            tmp = tmp->next;
        }
        ListNode* result = new ListNode(0, head);
        tmp = result;
        for (int i = 0; i < length - n; i++) {
            tmp = tmp->next;
        }
        tmp->next = tmp->next->next;
        return result->next;
    }
};
/* 遍历一次 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* newhead = new ListNode(0, head);
        ListNode *p = newhead, *q = newhead;
        while (n-- >= 0) {
            q = q->next;
        }
        while (q != nullptr) {
            p = p->next;
            q = q->next;
        }
        q = p->next;
        p->next = q->next;
        delete q;
        return newhead->next;
    }
};