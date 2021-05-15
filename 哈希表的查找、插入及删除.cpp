/*
 * @Author: your name
 * @Date: 2021-05-14 23:09:46
 * @LastEditTime: 2021-05-15 22:34:31
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\哈希表的查找、插入及删除.cpp
 */

/* 217题存在重复元素 */
/* 利用哈希表判断是否重复出现 */
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> st;
        for (int i = 0; i < nums.size(); i++) {
            if (st.count(nums[i])) {
                return true;
            }
            st.insert(nums[i]);
        }
        return false;
    }
};

/* 633题平方之和 */
/* 双指针，从大到小遍历，注意和的范围 */
class Solution {
public:
    bool judgeSquareSum(int c) {
        int low = 0, high = sqrt(c);
        while (low <= high) {
            long long sum = pow(low, 2) + pow(high, 2);
            if (sum < c) {
                low++;
            } else if (sum > c) {
                high--;
            } else {
                return true;
            }
        }
        return false;
    }
};

/* 349题两个数组的交集 */
/* 哈希表存储数据，注意在找到相同元素后 */
/* 删除哈希表中对应元素，避免结果出现重复元素 */
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        vector<int> res;
        unordered_set<int> st;
        for (int i = 0; i < nums1.size(); i++) {
            if (st.count(nums1[i]) == 0) {
                st.insert(nums1[i]);
            }
        }
        for (int i = 0; i < nums2.size(); i++) {
            if (st.count(nums2[i])) {
                res.push_back(nums2[i]);
                st.erase(nums2[i]);
            }
        }
        return res;
    }
};
/* 排序，双指针 */
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        vector<int> res;
        for (int i = 0, j = 0; i < nums1.size() && j < nums2.size();) {
            int num1 = nums1[i], num2 = nums2[j];
            if (num1 == num2) {
                if (res.size() == 0 || num1 != res.back()) {
                    res.push_back(num1);
                }
                i++;
                j++;
            } else if (num1 < num2) {
                i++;
            } else {
                j++;
            }
        }
        return res;
    }
};

/* 128题最长连续序列 */
/* 排序，统计 */
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        int res = 0, length = 1;
        sort(nums.begin(), nums.end());
        int pre = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] - pre <= 1) {
                if (nums[i] - pre == 1) {
                    length++;
                    res = max(length, res);
                }
            } else {
                length = 1;
            }
            pre = nums[i];
        }
        res = max(res, length);
        return res;
    }
};
/* 哈希表，注意避免重复计算长度 */
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> st;
        for (int i = 0; i < nums.size(); i++) {
            st.insert(nums[i]);
        }
        int res = 0;
        for (unordered_set<int>::iterator it = st.begin(); it != st.end();
             it++) {
            if (!st.count(*it - 1)) {
                int currentnum = *it, currentlenth = 1;
                while (st.count(++currentnum)) {
                    currentlenth++;
                }
                res = max(res, currentlenth);
            }
        }
        return res;
    }
};

/* 202题快乐数 */
/* 哈希表存储曾经出现过的数 */
class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int> st;
        while (!st.count(n)) {
            st.insert(n);
            if (n == 1) {
                return true;
            }
            int New = 0;
            while (n > 0) {
                New += pow(n % 10, 2);
                n -= n % 10;
                n /= 10;
            }
            n = New;
        }
        return false;
    }
};

/* 291题单词规律 */
/* 哈希表建立联系 */
class Solution {
public:
    string getWord(string s, int& begin) {
        string word;
        while (begin < s.size() && s[begin] == ' ') {
            begin++;
        }
        while (begin < s.size() && s[begin] != ' ') {
            word += s[begin++];
        }
        return word;
    }
    bool wordPattern(string pattern, string s) {
        int end = s.size() - 1;
        while (end >= 0 && s[end] == ' ') {
            end--;
        }
        end++;
        unordered_map<char, string> mp;
        unordered_set<string> st;
        int i, j;
        for (i = 0, j = 0; i < pattern.size() && j < s.size(); i++) {
            string word = getWord(s, j);
            char c = pattern[i];
            if (!mp.count(c) && !st.count(word)) {
                mp.insert(make_pair(c, word));
                st.insert(word);
            } else if (mp.count(c) && st.count(word)) {
                if (mp[c] != word) {
                    return false;
                }
            } else {
                return false;
            }
        }
        return i == pattern.size() && j == end;
    }
};