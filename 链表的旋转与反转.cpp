/*
 * @Author: your name
 * @Date: 2021-05-13 22:32:33
 * @LastEditTime: 2021-05-13 23:33:18
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\链表的旋转与反转.cpp
 */

/* 61题旋转链表 */
/* 第一次遍历链表统计链表长度，同时将链表连成环状 */
/* 第二次遍历，根据旋转关系确定旋转后的头节点 */
/* 遍历至新的头节点前一节点，完成解环操作 */
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head) {
            return head;
        }
        ListNode* newhead = head;
        int length = 1;
        while (newhead->next) {
            length++;
            newhead = newhead->next;
        }
        newhead->next = head;
        newhead = head;
        for (int i = 1; i < length - k % length; i++) {
            newhead = newhead->next;
        }
        ListNode* result = newhead->next;
        newhead->next = nullptr;
        return result;
    }
};

/* 24题两两交换链表中的节点 */
/* 将链表按照奇偶分为两个子链表 */
/* 将两个子链表连接成一个新的链表 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode *newlist1 = new ListNode(), *newlist2 = new ListNode();
        ListNode *list1 = newlist1, *list2 = newlist2;
        while (head != nullptr) {
            list1->next = head;
            head = head->next;
            list1 = list1->next;
            if (head == nullptr) {
                break;
            }
            list2->next = head;
            head = head->next;
            list2 = list2->next;
        }
        list1->next = nullptr;
        list2->next = nullptr;
        list1 = newlist1->next;
        list2 = newlist2->next;
        ListNode* newhead = new ListNode();
        ListNode* p = newhead;
        while (list1 != nullptr && list2 != nullptr) {
            p->next = list2;
            list2 = list2->next;
            p = p->next;
            p->next = list1;
            list1 = list1->next;
            p = p->next;
        }
        if (list1 != nullptr) {
            p->next = list1;
        }
        if (list2 != nullptr) {
            p->next = list2;
        }
        return newhead->next;
    }
};
/* 递归 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode* newhead = head->next;
        head->next = swapPairs(newhead->next);
        newhead->next = head;
        return newhead;
    }
};