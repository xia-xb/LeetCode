/*
 * @Author: your name
 * @Date: 2021-08-18 20:07:13
 * @LastEditTime: 2021-08-28 16:13:58
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

/* 887 鸡蛋掉落 */
/* 动态规划 */
class Solution {
public:
    int dp(vector<vector<int>>& mem, int k, int n) {
        if (k == 1) {
            mem[k][n] = n;
            return n;
        }
        if (n == 0) {
            mem[k][n] = 0;
            return 0;
        }
        if (mem[k][n] != -1) {
            return mem[k][n];
        }
        int res = INT_MAX;
        int left = 1, right = n;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int broken = dp(mem, k - 1, mid - 1);
            int notBroken = dp(mem, k, n - mid);
            if (broken == notBroken) {
                res = min(res, broken + 1);
                break;
            } else if (broken > notBroken) {
                right = mid - 1;
                res = min(res, broken + 1);
            } else {
                left = mid + 1;
                res = min(res, notBroken + 1);
            }
        }
        mem[k][n] = res;
        return res;
    }
    int superEggDrop(int k, int n) {
        vector<vector<int>> mem(k + 1, vector<int>(n + 1, -1));
        return dp(mem, k, n);
    }
};

/* 1884 鸡蛋掉落-两枚鸡蛋 */
/* 动态规划 */
class Solution {
public:
    int dp(vector<vector<int>>& mem, int k, int n) {
        if (k == 1) {
            mem[k][n] = n;
            return n;
        }
        if (n == 0) {
            mem[k][n] = 0;
            return 0;
        }
        if (mem[k][n] != -1) {
            return mem[k][n];
        }
        int res = INT_MAX;
        int left = 1, right = n;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int broken = dp(mem, k - 1, mid - 1);
            int notBroken = dp(mem, k, n - mid);
            if (broken == notBroken) {
                res = min(res, broken + 1);
                break;
            } else if (broken > notBroken) {
                res = min(res, broken + 1);
                right = mid - 1;
            } else {
                res = min(res, notBroken + 1);
                left = mid + 1;
            }
        }
        mem[k][n] = res;
        return res;
    }
    int twoEggDrop(int n) {
        vector<vector<int>> mem(3, vector<int>(n + 1, -1));
        return dp(mem, 2, n);
    }
};

/* 1143 最长公共子序列 */
/* 二维动态规划 */
/* dp[i][j] s1[0~i] s2[0~j]最长公共子序列 */
/* 注意相等时的状态转移 */
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(), n = text2.size();
        if (m == 0 || n == 0) {
            return 0;
        }
        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = text1[0] == text2[0] ? 1 : 0;
        for (int i = 1; i < m; i++) {
            dp[i][0] = text1[i] == text2[0] ? 1 : dp[i - 1][0];
        }
        for (int i = 1; i < n; i++) {
            dp[0][i] = text1[0] == text2[i] ? 1 : dp[0][i - 1];
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (text1[i] != text2[j]) {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                } else {
                    dp[i][j] = max(dp[i - 1][j - 1] + 1,
                                   max(dp[i - 1][j], dp[i][j - 1]));
                    dp[i][j] = min(dp[i][j], min(i + 1, j + 1));
                }
            }
        }
        return dp[m - 1][n - 1];
    }
};
/* 动态转移方程 */
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(), n = text2.size();
        if (m == 0 || n == 0) {
            return 0;
        }
        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = text1[0] == text2[0] ? 1 : 0;
        for (int i = 1; i < m; i++) {
            dp[i][0] = text1[i] == text2[0] ? 1 : dp[i - 1][0];
        }
        for (int i = 1; i < n; i++) {
            dp[0][i] = text1[0] == text2[i] ? 1 : dp[0][i - 1];
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (text1[i] != text2[j]) {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                } else {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
            }
        }
        return dp[m - 1][n - 1];
    }
};
/* 状态dp[i][j]定义为 text1[0~i-1] text2[0~j-1]的 */
/* 从而包括空字符串情况，为0 */
/* 不用单独设置初始条件，简化代码 */
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(), n = text2.size();
        if (m == 0 || n == 0) {
            return 0;
        }
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i - 1] != text2[j - 1]) {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                } else {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
            }
        }
        return dp[m][n];
    }
};

/* 5 最长回文子串 */
/* 动态规划 */
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        if (n < 2) {
            return s;
        }
        vector<vector<int>> dp(n, vector<int>(n, 0));
        int begin = 0;
        int maxLen = 1;
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
        }
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i < n; i++) {
                int j = i + len - 1;
                if (j >= n) {
                    break;
                }
                if (s[i] != s[j]) {
                    dp[i][j] = 0;
                } else {
                    if (j - i < 3) {
                        dp[i][j] = 1;
                    } else {
                        dp[i][j] = dp[i + 1][j - 1];
                    }
                }
                if (dp[i][j] == 1 && len > maxLen) {
                    maxLen = len;
                    begin = i;
                }
            }
        }
        return s.substr(begin, maxLen);
    }
};

/* 516 最长回文子序列 */
/* 动态规划 */
/* 从下到上，从左到右遍历 */
/* 注意不相等时，取dp[i+1][j],dp[i][j-1] */
/* 较大的，即将s[i],s[j]分别加入dp[i+1][j-1]中 */
/* 得到较长的回文子序列 */
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
        }
        int res = 1;
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                if (s[i] == s[j]) {
                    if (j - i + 1 <= 3) {
                        dp[i][j] = j - i + 1;
                    } else {
                        dp[i][j] = dp[i + 1][j - 1] + 2;
                    }
                } else {
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
                res = max(res, dp[i][j]);
            }
        }
        return res;
    }
};
/* 由于不合法位置初始化为0，所以可以不考虑dp[i+1][j-1]不合法情况 */
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
        }
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                } else {
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[0][n - 1];
    }
};

/* 1140 石子游戏II */
/* 动态规划 */
/* dp[i][m]，从i开始，最多m堆 */
/* 注意问题转换 */
/* 状态转换时，取对手在剩下中取最少的 */
class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        vector<vector<int>> dp(n, vector<int>(n + 1, 0));
        int sum = 0;
        for (int i = n - 1; i >= 0; i--) {
            sum += piles[i];
            for (int m = 1; m <= n; m++) {
                if (i + 2 * m >= n) {
                    dp[i][m] = sum;
                } else {
                    for (int j = 1; j <= 2 * m; j++) {
                        dp[i][m] = max(dp[i][m], sum - dp[i + j][max(j, m)]);
                    }
                }
            }
        }
        return dp[0][1];
    }
};

/* 1406 石子游戏III */
/* 动态规划 */
/* dp[i] i~n先手能获得最多石子数 */
/* 后缀和，减去对手能在剩下的获得最少的石子即可 */
class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();
        vector<int> sum(n);
        int total = stoneValue[n - 1];
        sum[n - 1] = stoneValue[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            sum[i] = sum[i + 1] + stoneValue[i];
            total += stoneValue[i];
        }

        vector<int> dp(n + 1);
        dp[n] = 0;
        for (int i = n - 1; i >= 0; i--) {
            int bestj = dp[i + 1];
            for (int j = i + 2; j <= i + 3 && j <= n; j++) {
                bestj = min(bestj, dp[j]);
            }
            dp[i] = sum[i] - bestj;
        }
        if (dp[0] * 2 == total) {
            return "Tie";
        } else {
            return dp[0] * 2 > total ? "Alice" : "Bob";
        }
    }
};