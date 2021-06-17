/*
 * @Author: your name
 * @Date: 2021-05-14 23:00:04
 * @LastEditTime: 2021-06-17 23:55:38
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\链表的合并.cpp
 */

/* 21题合并两个有序链表 */
/* 直接合并 */
class Solution {
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        ListNode *head = new ListNode(-1);
        ListNode *tail = head;
        while (l1 && l2) {
            if ((l1->val) <= (l2->val)) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        if (l1 || l2) {
            tail->next = l1 ? l1 : l2;
        }
        return head->next;
    }
};
/* 修改 */
class Solution {
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        ListNode *res = new ListNode();
        ListNode *tail = res;
        while (l1 != nullptr && l2 != nullptr) {
            while (l1 != nullptr && l1->val <= l2->val) {
                tail->next = l1;
                tail = tail->next;
                l1 = l1->next;
            }
            tail->next = l2;
            tail = tail->next;
            l2 = l2->next;
        }
        if (l1 != nullptr) {
            tail->next = l1;
        }
        if (l2 != nullptr) {
            tail->next = l2;
        }
        return res->next;
    }
};

/* 23题合并K个升序链表 */
/* 按顺序合并 */
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
    ListNode *mergeLists(ListNode *plist, ListNode *qlist) {
        if ((!plist) || (!qlist)) {
            return plist ? plist : qlist;
        }
        ListNode *newhead = new ListNode();
        ListNode *tail = newhead;
        while (plist != nullptr && qlist != nullptr) {
            if (plist->val <= qlist->val) {
                tail->next = plist;
                plist = plist->next;
            } else {
                tail->next = qlist;
                qlist = qlist->next;
            }
            tail = tail->next;
        }
        if (plist != nullptr) {
            tail->next = plist;
        }
        if (qlist != nullptr) {
            tail->next = qlist;
        }
        return newhead->next;
    }
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        if (lists.empty()) {
            return nullptr;
        }
        for (int i = 1; i < lists.size(); i++) {
            lists[i] = mergeLists(lists[i], lists[i - 1]);
        }
        return lists.back();
    }
};
/* 分治合并 */
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
    ListNode *mergeTwoLists(ListNode *plist, ListNode *qlist) {
        if ((!plist) || (!qlist)) {
            return plist ? plist : qlist;
        }
        ListNode *newhead = new ListNode();
        ListNode *tail = newhead;
        while (plist != nullptr && qlist != nullptr) {
            if (plist->val <= qlist->val) {
                tail->next = plist;
                plist = plist->next;
            } else {
                tail->next = qlist;
                qlist = qlist->next;
            }
            tail = tail->next;
        }
        if (plist != nullptr) {
            tail->next = plist;
        }
        if (qlist != nullptr) {
            tail->next = qlist;
        }
        return newhead->next;
    }
    ListNode *mergeLists(vector<ListNode *> &lists, int left, int right) {
        if (left == right) {
            return lists[left];
        }
        if (left > right) {
            return nullptr;
        }
        int mid = left + (right - left) / 2;
        return mergeTwoLists(mergeLists(lists, left, mid),
                             mergeLists(lists, mid + 1, right));
    }
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        return mergeLists(lists, 0, lists.size() - 1);
    }
};
/* 通过有限队列进行合并 */
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
    struct Status {
        int val;
        ListNode *ptr;
        bool operator<(const Status &rhs) const { return val > rhs.val; }
    };
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        priority_queue<Status> que;
        for (int i = 0; i < lists.size(); i++) {
            if (lists[i] != nullptr) {
                que.push({lists[i]->val, lists[i]});
            }
        }
        ListNode *newhead = new ListNode(0);
        ListNode *tail = newhead;
        while (!que.empty()) {
            auto it = que.top();
            que.pop();
            tail->next = it.ptr;
            tail = tail->next;
            if (it.ptr->next != nullptr) {
                que.push({it.ptr->next->val, it.ptr->next});
            }
        }
        return newhead->next;
    }
};