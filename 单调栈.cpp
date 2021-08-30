/*
 * @Author: your name
 * @Date: 2021-08-30 15:41:28
 * @LastEditTime: 2021-08-30 17:05:44
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /LeetCode/单调栈.cpp
 */

/* 496 下一个更大元素I */
/* 对nums2进行单调栈 */
/* 结果存在哈希表中 */
/* 遍历nums1确定对应元素 */
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size(), n2 = nums2.size();
        stack<int> stk;
        unordered_map<int, int> mp;
        for (int i = n2 - 1; i >= 0; i--) {
            int num = nums2[i];
            while (!stk.empty() && stk.top() <= num) {
                stk.pop();
            }
            mp[num] = stk.empty() ? -1 : stk.top();
            stk.push(num);
        }
        vector<int> res;
        for (int i = 0; i < n1; i++) {
            res.push_back(mp[nums1[i]]);
        }
        return res;
    }
};

/* 739 每日温度 */
/* 单调栈 */
/* 不同的是栈中存储元素下标 */
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> res(n, -1);
        stack<int> stk;
        for (int i = n - 1; i >= 0; i--) {
            while (!stk.empty() && temperatures[stk.top()] <= temperatures[i]) {
                stk.pop();
            }
            res[i] = stk.empty() ? 0 : stk.top() - i;
            stk.push(i);
        }
        return res;
    }
};

/* 503 下一个更大元素II */
/* 单调栈 */
/* 环形数组，通过扩大一倍处理 */
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, -1);
        stack<int> stk;
        for (int i = 2 * n - 1; i >= 0; i--) {
            while (!stk.empty() && stk.top() <= nums[i % n]) {
                stk.pop();
            }
            res[i % n] = stk.empty() ? -1 : stk.top();
            stk.push(nums[i % n]);
        }
        return res;
    }
};

/* 556 下一个更大元素III */
/* 从右向左遍历，寻找第一个变小的元素 */
/* 然后从右边寻找大于该元素的最小元素 */
/* 交换两元素 */
/* 逆序右边元素，使得结果最小 */
public:
int nextGreaterElement(int n) {
    string s = to_string(n);
    int length = s.size();
    int i = length - 2;
    while (i >= 0 && s[i] >= s[i + 1]) {
        i--;
    }
    if (i == -1) {
        return -1;
    }
    int j = length - 1;
    while (j > i && s[j] <= s[i]) {
        j--;
    }
    swap(s[i], s[j]);
    reverse(s.begin() + i + 1, s.end());
    long res = stol(s);
    if (res > INT_MAX) {
        return -1;
    }
    return stoi(s);
}
}
;