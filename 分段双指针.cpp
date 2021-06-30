/*
 * @Author: your name
 * @Date: 2021-06-28 22:40:23
 * @LastEditTime: 2021-06-30 23:16:56
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

/* 328题奇偶链表 */
/* 双指针 */
/* 一个指向奇链表，一个指向偶链表 */
/* 同86题一样需要注意最后偶链表尾结点需要置为nullptr */
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
    ListNode* oddEvenList(ListNode* head) {
        ListNode* oddhead = new ListNode;
        ListNode* evenhead = new ListNode;
        ListNode *oddtail = oddhead, *eventail = evenhead;
        bool isOdd = true;
        while (head != nullptr) {
            if (isOdd) {
                oddtail->next = head;
                oddtail = oddtail->next;
            } else {
                eventail->next = head;
                eventail = eventail->next;
            }
            head = head->next;
            isOdd = !isOdd;
        }
        oddtail->next = evenhead->next;
        eventail->next = nullptr;
        return oddhead->next;
    }
};

/* 160题相交链表 */
/* 首先确定两个链表的长度 */
/* 之后通过双指针，相遇即为相交起始节点 */
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
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        int lena = 0, lenb = 0;
        ListNode *p = headA, *q = headB;
        while (p || q) {
            if (p) {
                lena++;
                p = p->next;
            }
            if (q) {
                lenb++;
                q = q->next;
            }
        }
        p = headA;
        q = headB;
        int i;
        if (lenb > lena) {
            for (i = 0; i < lenb - lena; i++) {
                q = q->next;
            }
        } else if (lena > lenb) {
            for (i = 0; i < lena - lenb; i++) {
                p = p->next;
            }
        }
        while (p && q) {
            if (p == q) {
                return p;
            }
            p = p->next;
            q = q->next;
        }
        return NULL;
    }
};

/* 88题合并两个有序数组 */
/* 双指针 */
/* 注意为了提高速度，原地合并 */
/* 从而从尾结点开始合并，而不是从头节点开始合并 */
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int tail1 = m - 1, tail2 = n - 1, tail = m + n - 1;
        while (tail1 >= 0 && tail2 >= 0) {
            if (nums1[tail1] >= nums2[tail2]) {
                nums1[tail--] = nums1[tail1--];
            } else {
                nums1[tail--] = nums2[tail2--];
            }
        }
        while (tail1 >= 0) {
            nums1[tail--] = nums1[tail1--];
        }
        while (tail2 >= 0) {
            nums1[tail--] = nums2[tail2--];
        }
    }
};

/* 475题供暖器 */
/* 双指针，分别指向房子和供暖器 */
/* 二分查找寻找供暖器中最接近指定房子的 */
/* 由于都是有序的 */
/* 所以每次二分查找的左边界可以不从0开始 */
/* 而是设置1个变量，每次遍历时相应改变 */
class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        int houseIter = 0, heatersIter = 0;
        int r = 0;
        while (houseIter < houses.size()) {
            int left = heatersIter, right = heaters.size() - 1;
            int target = houses[houseIter++];
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (heaters[mid] == target) {
                    heatersIter = mid;
                    break;
                } else if (heaters[mid] < target) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            if (left - right == 1) {
                if (right < 0) {
                    r = max(r, abs(target - heaters[left]));
                    heatersIter = left;
                } else if (left >= heaters.size()) {
                    r = max(r, abs(target - heaters[right]));
                    heatersIter = right;
                } else {
                    int r1 = abs(target - heaters[left]),
                        r2 = abs(target - heaters[right]);
                    r = max(r, min(r1, r2));
                    heatersIter = r2 <= r1 ? right : left;
                }
            }
        }
        return r;
    }
};
