/*
 * @Author: your name
 * @Date: 2021-06-25 21:31:42
 * @LastEditTime: 2021-06-26 00:07:12
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /LeetCode/同向指针、滑动窗口.cpp
 */

/* 27题移除元素 */
/* 双指针，让右指针指向不是val */
/* 当左指针等于val时交换 */
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if (nums.empty()) {
            return 0;
        }
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            while (left < right && nums[right] == val) {
                right--;
            }
            if (left < right && nums[left] == val) {
                swap(nums[left], nums[right]);
            }
            left++;
        }
        return nums[right] == val ? right : right + 1;
    }
};
/* 优化 */
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int left = 0, right = nums.size();
        while (left < right) {
            if (nums[left] == val) {
                nums[left] = nums[--right];
            } else {
                left++;
            }
        }
        return left;
    }
};

/* 26题删除有序数组中的重复项 */
/* 同向双指针 */
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int left = -1, right = 0;
        while (right < nums.size()) {
            if (left >= 0 && nums[right] == nums[left]) {
                right++;
            } else {
                nums[++left] = nums[right];
            }
        }
        return left + 1;
    }
};

/* 80题删除有序数组中的重复项II */
/* 同向双指针，通过map记录出现次数 */
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() <= 2) {
            return nums.size();
        }
        int slow = 0, fast = 1;
        unordered_map<int, int> mp;
        mp[nums[0]]++;
        while (fast < nums.size()) {
            if (nums[fast] != nums[slow] ||
                (nums[fast] == nums[slow] && mp[nums[slow]] < 2)) {
                nums[++slow] = nums[fast];
                mp[nums[slow]]++;
            }
            fast++;
        }
        return slow + 1;
    }
};
/* 优化 */
/* 通过数组前后关系，避免使用map */
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() <= 2) {
            return nums.size();
        }
        int slow = 0, fast = 1;
        while (fast < nums.size()) {
            if (nums[fast] != nums[slow] ||
                (nums[fast] == nums[slow] && slow == 0 ||
                 nums[slow] != nums[slow - 1])) {
                nums[++slow] = nums[fast];
            }
            fast++;
        }
        return slow + 1;
    }
};
/* 对上面判断逻辑进行优化 */
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() <= 2) {
            return nums.size();
        }
        int slow = 2, fast = 2;
        while (fast < nums.size()) {
            if (nums[slow - 2] != nums[fast]) {
                nums[slow++] = nums[fast];
            }
            fast++;
        }
        return slow;
    }
};

/* 83题删除排序链表中的重复元素 */
/* 双指针 */
/* 注意最后尾指针的next需要指向空 */
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
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr) {
            return head;
        }
        ListNode *tail = head, *p = head;
        while (p != nullptr) {
            if (tail->val != p->val) {
                tail->next = p;
                tail = tail->next;
            }
            p = p->next;
        }
        tail->next = nullptr;
        return head;
    }
};

/* 82题删除排序链表中的重复元素II */
/* 双指针 */
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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* newhead = new ListNode();
        ListNode *tail = newhead, *p = head, *q = head;
        while (p != nullptr) {
            q = p->next;
            if (q == nullptr || p->val != q->val) {
                tail->next = p;
                tail = tail->next;
                p = p->next;
            } else {
                while (q != nullptr && q->val == p->val) {
                    q = q->next;
                }
                p = q;
            }
        }
        tail->next = nullptr;
        return newhead->next;
    }
};
