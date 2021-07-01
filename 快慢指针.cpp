/*
 * @Author: your name
 * @Date: 2021-06-30 23:19:17
 * @LastEditTime: 2021-07-01 23:32:14
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

/* 142题环形链表II */
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
    ListNode* detectCycle(ListNode* head) {
        ListNode* newHead = new ListNode(0, head);
        ListNode *fast = newHead, *slow = newHead;
        while (fast != NULL) {
            fast = fast->next;
            if (fast != NULL) {
                fast = fast->next;
            }
            slow = slow->next;
            if (fast == slow) {
                break;
            }
        }
        if (fast == NULL) {
            return NULL;
        }
        slow = newHead;
        while (fast != slow) {
            fast = fast->next;
            slow = slow->next;
        }
        return fast;
    }
};

/* 143题重排链表 */
/* 快慢指针 */
/* 找到链表中点，从而分为两个子链表 */
/* 后一个链表反转 */
/* 合并两个链表 */
/* 注意最后的结点next需要保证为nullptr */
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
    void reorderList(ListNode* head) {
        ListNode* newHead = new ListNode(0, head);
        ListNode *fast = newHead, *slow = newHead;
        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
        }
        ListNode* slowListHead = new ListNode(0, nullptr);
        while (slow != nullptr) {
            ListNode* nextNode = slow->next;
            slow->next = slowListHead->next;
            slowListHead->next = slow;
            slow = nextNode;
        }
        fast = head;
        slow = slowListHead->next;
        while (fast != nullptr && slow != nullptr) {
            ListNode* nextSlow = slow->next;
            slow->next = fast->next;
            fast->next = slow;
            fast = fast->next->next;
            slow = nextSlow;
        }
        if (fast != nullptr) {
            fast->next = nullptr;
        }
    }
};

/* 234题回文链表 */
/* 快慢指针，找到中间结点 */
/* 将后一个子链表反转 */
/* 判断两个子链表值是否相等 */
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
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) {
            return true;
        }
        ListNode *fast = head, *slow = head;
        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
        }
        ListNode* newSlow = new ListNode(0, nullptr);
        while (slow != nullptr) {
            ListNode* tmp = slow->next;
            slow->next = newSlow->next;
            newSlow->next = slow;
            slow = tmp;
        }
        fast = head;
        slow = newSlow->next;
        while (fast != nullptr && slow != nullptr) {
            if (fast->val != slow->val) {
                return false;
            }
            fast = fast->next;
            slow = slow->next;
        }
        return true;
    }
};

/* 287题寻找重复数 */
/* 哈希表 */
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        unordered_set<int> st;
        for (int it : nums) {
            if (st.count(it)) {
                return it;
            }
            st.insert(it);
        }
        return 0;
    }
};
/* 快慢指针 */
/* 类似于链表环问题 */
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int fast = nums[nums[0]], slow = nums[0];
        while (fast != slow) {
            fast = nums[nums[fast]];
            slow = nums[slow];
        }
        slow = 0;
        while (fast != slow) {
            fast = nums[fast];
            slow = nums[slow];
        }
        return fast;
    }
};
