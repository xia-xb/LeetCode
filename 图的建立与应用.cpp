/*
 * @Author: your name
 * @Date: 2021-05-21 22:09:41
 * @LastEditTime: 2021-05-21 22:32:57
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\图的建立与应用.cpp
 */

/* 565题数组嵌套 */
class Solution {
public:
    int arrayNesting(vector<int>& nums) {
        int res = 0, count = 0;
        unordered_set<int> st;
        for (int i = 0; i < nums.size(); i++) {
            int n = nums[i];
            count = 0;
            st.clear();
            while (!st.count(n)) {
                st.insert(n);
                count++;
                n = nums[n];
            }
            res = max(res, count);
        }
        return res;
    }
};
/* 通过visited数组，剔除已经访问过的元素 */
class Solution {
public:
    int arrayNesting(vector<int>& nums) {
        int res = 0;
        vector<bool> visited(nums.size(), false);
        for (int i = 0; i < nums.size(); i++) {
            if (!visited[i]) {
                visited[i] = true;
                int count = 1, n = nums[i];
                while (n != i) {
                    visited[n] = true;
                    n = nums[n];
                    count++;
                }
                res = max(res, count);
            }
        }
        return res;
    }
};
/* 对原数组的元素进行修改，标记其已经访问过 */
class Solution {
public:
    int arrayNesting(vector<int>& nums) {
        int res = 0;
        int length = nums.size();
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] < length) {
                int count = 1, n = nums[i];
                nums[i] += length;
                while (n != i) {
                    n = nums[n] % length;
                    nums[n] += length;
                    count++;
                }
                res = max(res, count);
            }
        }
        return res;
    }
};
/* dfs，注意visited数组 */
/* 以及res刷新的条件 */
class Solution {
public:
    int res = 0;
    vector<bool> visited;
    void dfs(vector<int>& nums, int index, int count) {
        if (visited[index]) {
            res = max(res, count);
            return;
        }
        visited[index] = true;
        dfs(nums, nums[index], count + 1);
    }
    int arrayNesting(vector<int>& nums) {
        visited.resize(nums.size());
        if (nums.size() == 0) {
            return 0;
        }
        for (int i = 0; i < nums.size(); i++) {
            dfs(nums, i, 0);
        }
        return res;
    }
};
