/*
 * @Author: your name
 * @Date: 2021-08-18 20:07:13
 * @LastEditTime: 2021-08-18 23:30:34
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /LeetCode/动态规划.cpp
 */

/* 300 最长递增子序列 */
/* 动态规划 */
/* dp[i]:以nums[i]结尾的最长递增子序列 */
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int res = 1;
        vector<int> dp(nums.size(), 1);
        for (int i = 1; i < nums.size(); i++) {
            int val = nums[i];
            for (int j = 0; j < i; j++) {
                dp[i] = nums[j] < val && dp[j] + 1 > dp[i] ? dp[j] + 1 : dp[i];
            }
            res = max(res, dp[i]);
        }
        return res;
    }
};
/* 二分查找 */
/* 注意tail必须严格递增 */
/* 所以tail[mid]==target时 */
/* 直接跳出，并且忽略 */
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> tail;
        for (int i = 0; i < nums.size(); i++) {
            int target = nums[i];
            if (tail.empty() || tail.back() < target) {
                tail.push_back(target);
                continue;
            }
            int left = 0, right = tail.size() - 1;
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (tail[mid] == target) {
                    left = mid;
                    break;
                } else if (tail[mid] < target) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            if (left >= tail.size() || tail[left] <= target) {
                continue;
            } else {
                tail[left] = target;
            }
        }
        return tail.size();
    }
};

/* 72 编辑距离 */
/* 动态规划 */
/* dp[i][j] */
/* s1[0~i],s2[0~j]的最小编辑距离 */
class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 0; i <= m; i++) {
            dp[i][0] = i;
        }
        for (int i = 0; i <= n; i++) {
            dp[0][i] = i;
        }
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1);
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1);
                }
            }
        }
        return dp[m][n];
    }
};