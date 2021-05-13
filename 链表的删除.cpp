/*
 * @Author: your name
 * @Date: 2021-05-12 23:37:27
 * @LastEditTime: 2021-05-13 22:30:24
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

/* 203题移除链表元素 */
/* 直接删除 */
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* newhead = new ListNode(0, head);
        ListNode* p = newhead;
        ListNode* tmp;
        while (p->next) {
            tmp = p->next;
            if (tmp->val == val) {
                p->next = tmp->next;
                delete tmp;
            } else {
                p = p->next;
            }
            if (!p) {
                break;
            }
        }
        return newhead->next;
    }
};

/* 237题删除链表中的节点 */
/* 从待删除节点开始删除 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        ListNode* tmp;
        while (node && node->next) {
            tmp = node->next;
            node->val = tmp->val;
            if (!tmp->next) {
                node->next = NULL;
                break;
            }
            node = tmp;
        }
    }
};
/* 将待删除节点复制为其下一个节点 */
/* 删除下一个节点即可 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        ListNode* tmp = node->next;
        node->val = tmp->val;
        node->next = tmp->next;
        delete tmp;
    }
};