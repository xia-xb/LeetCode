/*
 * @Author: your name
 * @Date: 2021-06-28 22:40:23
 * @LastEditTime: 2021-06-28 22:43:36
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\分段双指针.cpp
 */

/* 86题分隔链表 */
/* 双指针，分别对应较小，较大元素 */
/* 注意最后，较大链表的尾结点的next需要置为nullptr */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode *lessHead = new ListNode(), *moreHead = new ListNode();
        ListNode *lessTail = lessHead, *moreTail = moreHead;
        while (head != nullptr) {
            if (head->val < x) {
                lessTail->next = head;
                lessTail = lessTail->next;
            } else {
                moreTail->next = head;
                moreTail = moreTail->next;
            }
            head = head->next;
        }
        lessTail->next = moreHead->next;
        moreTail->next = nullptr;
        return lessHead->next;
    }
};
