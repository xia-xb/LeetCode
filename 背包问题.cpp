/*
 * @Author: your name
 * @Date: 2021-09-02 16:35:13
 * @LastEditTime: 2021-09-02 22:33:29
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /LeetCode/01背包.cpp
 */

/* 416 分割等和子集 */
/* 动态规划 */
/* 01背包问题 */
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (int it : nums) {
            sum += it;
        }
        if ((sum & 1) == 1) {
            return false;
        }
        int target = sum / 2;
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(target + 1, 0));
        if (nums[0] <= target) {
            dp[0][nums[0]] = 1;
        }
        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= target; j++) {
                dp[i][j] = dp[i - 1][j];
                if (nums[i] == j) {
                    dp[i][j] = 1;
                    continue;
                }
                if (nums[i] < j) {
                    dp[i][j] = dp[i][j] || dp[i - 1][j - nums[i]];
                }
            }
        }
        return dp[n - 1][target] == 1;
    }
};
/* 优化，使用一维数组 */
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (int it : nums) {
            sum += it;
        }
        if ((sum & 1) == 1) {
            return false;
        }
        int target = sum / 2;
        int n = nums.size();
        vector<int> dp(target + 1, 0);
        if (nums[0] <= target) {
            dp[nums[0]] = 1;
        }
        for (int i = 1; i < n; i++) {
            for (int j = target; j >= 0; j--) {
                if (nums[i] == j) {
                    dp[j] = 1;
                    continue;
                }
                if (nums[i] < j) {
                    dp[j] = dp[j] || dp[j - nums[i]];
                }
            }
        }
        return dp[target] == 1;
    }
};

/* 474 一和零 */
/* 动态规划 */
/* 转化为01背包问题 */
/* dp[i][j][k]前i个字符串，最多j个0,k个1的最大子集 */
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        int length = strs.size();
        vector<vector<int>> vec(length, vector<int>(2, 0));
        for (int i = 0; i < length; i++) {
            int count = 0;
            for (int j = 0; j < strs[i].size(); j++) {
                if (strs[i][j] == '0') {
                    count++;
                }
            }
            vec[i][0] = count;
            vec[i][1] = strs[i].size() - count;
        }
        vector<vector<vector<int>>> dp(
            length + 1, vector<vector<int>>(m + 1, vector<int>(n + 1, 0)));
        for (int i = 1; i <= length; i++) {
            int zeros = vec[i - 1][0], ones = vec[i - 1][1];
            for (int j = 0; j <= m; j++) {
                for (int k = 0; k <= n; k++) {
                    dp[i][j][k] = dp[i - 1][j][k];
                    if (zeros <= j && ones <= k) {
                        dp[i][j][k] = max(dp[i][j][k],
                                          dp[i - 1][j - zeros][k - ones] + 1);
                    }
                }
            }
        }
        return dp[length][m][n];
    }
};

/* 494 目标和 */
/* 动态规划 */
/* 转化为01背包问题 */
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(2001, 0));
        dp[0][nums[0] + 1000]++;
        dp[0][-nums[0] + 1000]++;
        for (int i = 1; i < n; i++) {
            int num = nums[i];
            for (int j = -1000; j <= 1000; j++) {
                if (j - num >= -1000) {
                    dp[i][j + 1000] += dp[i - 1][j - num + 1000];
                }
                if (j + num <= 1000) {
                    dp[i][j + 1000] += dp[i - 1][j + num + 1000];
                }
            }
        }
        return dp[n - 1][target + 1000];
    }
};

/* 879 盈利计划 */
/* 动态规划 01背包问题 */
/* 有两个容量，分别为工作人数，以及利润 */
/* 状态转移方程根据工作人数能否完成对应工作确定 */
class Solution {
public:
    int base = pow(10, 9) + 7;
    int profitableSchemes(int n, int minProfit, vector<int>& group,
                          vector<int>& profit) {
        int count = profit.size();
        vector<vector<vector<int>>> dp(
            count + 1,
            vector<vector<int>>(n + 1, vector<int>(minProfit + 1, 0)));
        dp[0][0][0] = 1;
        for (int i = 1; i <= count; i++) {
            int num = group[i - 1], eran = profit[i - 1];
            for (int j = 0; j <= n; j++) {
                for (int k = 0; k <= minProfit; k++) {
                    if (j < num) {
                        dp[i][j][k] = dp[i - 1][j][k];
                    } else {
                        dp[i][j][k] = (dp[i - 1][j][k] +
                                       dp[i - 1][j - num][max(0, k - eran)]) %
                                      base;
                    }
                }
            }
        }
        int res = 0;
        for (int i = 0; i <= n; i++) {
            res = (res + dp[count][i][minProfit]) % base;
        }
        return res;
    }
};

/* 322 零钱兑换 */
/* 动态规划 完全背包问题 */
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<vector<int>> dp(n + 1, vector<int>(amount + 1, -1));
        for (int i = 0; i <= n; i++) {
            dp[i][0] = 0;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= amount; j++) {
                for (int k = 0; k < i; k++) {
                    if (j >= coins[k]) {
                        if (dp[i][j] == -1) {
                            dp[i][j] = dp[i][j - coins[k]] == -1
                                           ? -1
                                           : dp[i][j - coins[k]] + 1;
                        } else {
                            dp[i][j] =
                                dp[i][j - coins[k]] == -1
                                    ? dp[i][j]
                                    : min(dp[i][j], dp[i][j - coins[k]] + 1);
                        }
                    }
                }
            }
        }
        return dp[n][amount];
    }
};
/* 一维dp数组替换 */
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<int> dp(amount + 1, -1);
        dp[0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= amount; j++) {
                dp[j] = -1;
                for (int k = 0; k < i; k++) {
                    if (j >= coins[k]) {
                        if (dp[j] == -1) {
                            dp[j] = dp[j - coins[k]] == -1
                                        ? -1
                                        : dp[j - coins[k]] + 1;
                        } else {
                            dp[j] = dp[j - coins[k]] == -1
                                        ? dp[j]
                                        : min(dp[j], dp[j - coins[k]] + 1);
                        }
                    }
                }
            }
        }
        return dp[amount];
    }
};
/* 动态规划 */
/* 不考虑硬币面额的限制 */
/* 注意最多只会是amount个硬币，初始化为amount+1 */
/* 从而标记为不能组合，最后根据是否为amount+1 */
/* 判断能否组合 */
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        int Max = amount + 1;
        vector<int> dp(amount + 1, Max);
        dp[0] = 0;
        for (int i = 1; i <= amount; i++) {
            for (int it : coins) {
                if (i >= it) {
                    dp[i] = min(dp[i], dp[i - it] + 1);
                }
            }
        }
        return dp[amount] == Max ? -1 : dp[amount];
    }
};