/*
 * @Author: your name
 * @Date: 2021-06-30 23:19:17
 * @LastEditTime: 2021-06-30 23:24:20
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\快慢指针.cpp
 */

/* 环形链表 */
/* 快慢指针 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode* head) {
        ListNode *fast = head, *slow = head;
        while (fast != nullptr) {
            fast = fast->next;
            if (fast != nullptr) {
                fast = fast->next;
            }
            if (fast == slow) {
                return true;
            }
            slow = slow->next;
        }
        return false;
    }
};
