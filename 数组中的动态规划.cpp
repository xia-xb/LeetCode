/*
 * @Author: 夏玄兵
 * @Date: 2021-07-07 22:17:09
 * @LastEditors: 夏玄兵
 * @LastEditTime: 2021-07-08 22:45:42
 * @Description: file content
 * @FilePath: \LeetCode\数组中的动态规划.cpp
 */

/* 509题斐波那契数列 */
/* 递归 */
class Solution {
public:
    int fib(int n) {
        if (n == 0) {
            return 0;
        } else if (n == 1) {
            return 1;
        }
        return fib(n - 1) + fib(n - 2);
    }
};
/* 数组动态规划 */
class Solution {
public:
    int fib(int n) {
        if (n == 0) {
            return 0;
        }
        if (n == 1) {
            return 1;
        }
        vector<int> dp(n + 1, 0);
        dp[1] = dp[2] = 1;
        for (int i = 3; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
};
/* 状态压缩 */
class Solution {
public:
    int fib(int n) {
        if (n == 0) {
            return 0;
        }
        if (n == 1) {
            return 1;
        }
        int prev = 1, curr = 1;
        for (int i = 3; i <= n; i++) {
            int sum = prev + curr;
            prev = curr;
            curr = sum;
        }
        return curr;
    }
};

/* 70题爬楼梯 */
/* 动态规划 */
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) {
            return n;
        }
        vector<int> dp(n + 1, 0);
        dp[1] = 1;
        dp[2] = 2;
        for (int i = 3; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
};
/* 压缩状态 */
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) {
            return n;
        }
        int prev = 1, curr = 2;
        for (int i = 3; i <= n; i++) {
            int sum = prev + curr;
            prev = curr;
            curr = sum;
        }
        return curr;
    }
};

/* 338题比特位计数 */
/* 动态规划 */
/* dp0=0 */
/* dp(i)=dp(i/2)    i为偶 */
/* dp(i)=dp(i-1)+1  i为奇 */
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> dp(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            if (i & 1) {
                dp[i] = dp[i - 1] + 1;
            } else {
                dp[i] = dp[i / 2];
            }
        }
        return dp;
    }
};

/* 45题跳跃游戏II */
/* 暴力搜索 */
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, INT_MAX);
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            for (int k = 1; k <= nums[i] && k + i < n; k++) {
                if (dp[k + i] != INT_MAX) {
                    continue;
                }
                dp[k + i] = min(dp[k + i], 1 + dp[i]);
            }
        }
        return dp.back();
    }
};