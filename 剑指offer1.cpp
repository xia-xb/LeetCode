/*
 * @Author: 夏玄兵
 * @Date: 2021-07-23 23:19:42
 * @LastEditors: 夏玄兵
 * @LastEditTime: 2021-07-23 23:42:59
 * @Description: file content
 * @FilePath: \LeetCode\剑指offer1.cpp
 */

/* 03数组中重复的数字 */
/* 哈希表set */
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        unordered_set<int> st;
        for (int i = 0; i < nums.size(); i++) {
            if (st.count(nums[i])) {
                return nums[i];
            } else {
                st.insert(nums[i]);
            }
        }
        return -1;
    }
};
/* 数组构成哈希表 */
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        vector<int> vec(nums.size(), 0);
        for (int i = 0; i < nums.size(); i++) {
            if (vec[nums[i]]) {
                return nums[i];
            } else {
                vec[nums[i]] = 1;
            }
        }
        return -1;
    }
};

/* 04二维数组中的查找 */
/* 从数组左下角开始查找 */
/* 小于目标值，列自增 */
/* 大于目标值，行自减 */
class Solution {
public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        if (matrix.empty()) {
            return false;
        }
        int n = matrix.size(), m = matrix[0].size();
        int row = n - 1, col = 0;
        while (row >= 0 && col < m) {
            int value = matrix[row][col];
            if (value == target) {
                return true;
            } else if (value > target) {
                row--;
            } else {
                col++;
            }
        }
        return false;
    }
};