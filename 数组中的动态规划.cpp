/*
 * @Author: 夏玄兵
 * @Date: 2021-07-07 22:17:09
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2021-07-16 23:22:39
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

/* 198题打家劫舍 */
/* 动态规划 */
/* dp[i]打劫第i家的最大金额 */
/* dp[0]=nums[0],dp[i]=nums[1] */
/* dp[i]=nums[i]+max(dp[j])  (0<=j<i-1) */

class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        }
        if (nums.size() == 2) {
            return max(nums[0], nums[1]);
        }
        vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        dp[1] = nums[1];
        int res = -1;
        int maxPre = dp[0];
        for (int i = 2; i < nums.size(); i++) {
            dp[i] = nums[i] + maxPre;
            res = max(dp[i], dp[i - 1]);
            maxPre = max(dp[i - 1], maxPre);
        }
        return res;
    }
};
/* 优化内存空间 */
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        }
        if (nums.size() == 2) {
            return max(nums[0], nums[1]);
        }
        int res = -1;
        int maxPre = nums[0], pre = nums[1];
        for (int i = 2; i < nums.size(); i++) {
            int curr = nums[i] + maxPre;
            res = max(curr, pre);
            maxPre = max(pre, maxPre);
            pre = curr;
        }
        return res;
    }
};
/* dp[i]表示前i+1间房能打劫的最大金额 */
/* 对于dp[i]打劫则为nums[i]+dp[i-2] */
/* 不打劫为dp[i-1] */
/* 所以为两个的最大值 */
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        if (nums.size() == 1) {
            return nums[0];
        }
        if (nums.size() == 2) {
            return max(nums[0], nums[1]);
        }
        vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2; i < nums.size(); i++) {
            dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
        }
        return max(dp.back(), dp[dp.size() - 2]);
    }
};
/* 内存优化 */
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        if (nums.size() == 1) {
            return nums[0];
        }
        if (nums.size() == 2) {
            return max(nums[0], nums[1]);
        }
        int first = nums[0], second = max(nums[0], nums[1]);
        for (int i = 2; i < nums.size(); i++) {
            int cur = max(first + nums[i], second);
            first = second;
            second = cur;
        }
        return max(first, second);
    }
};

/* 213题打家劫舍II */
/* 两次动态规划，分为0打劫或不打劫 */
class Solution {
public:
    int maxAmount(vector<int>& nums, vector<int>& dp) {
        int n = nums.size();
        if (dp[0] >= 0) {
            dp[1] = max(nums[0], nums[1]);
            for (int i = 2; i < n - 1; i++) {
                dp[i] = max(nums[i] + dp[i - 2], dp[i - 1]);
            }
            return max(dp[n - 2], dp[n - 3]);
        } else {
            dp[1] = nums[1];
            dp[2] = max(nums[1], nums[2]);
            for (int i = 3; i < n; i++) {
                dp[i] = max(nums[i] + dp[i - 2], dp[i - 1]);
            }
            return max(dp[n - 2], dp[n - 1]);
        }
    }
    int rob(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        if (nums.size() == 1) {
            return nums[0];
        }
        if (nums.size() == 2) {
            return max(nums[0], nums[1]);
        }
        vector<int> dp(nums.size(), -1);
        int res1 = maxAmount(nums, dp);
        vector<int> dp1(nums.size(), -1);
        dp1[0] = nums[0];
        int res2 = maxAmount(nums, dp1);
        return max(res1, res2);
    }
};
/* 内存优化 */
class Solution {
public:
    int maxAmount(vector<int>& nums, int first) {
        int n = nums.size();
        if (first >= 0) {
            int second = max(nums[0], nums[1]);
            for (int i = 2; i < n - 1; i++) {
                int cur = max(nums[i] + first, second);
                first = second;
                second = cur;
            }
            return max(first, second);
        } else {
            first = nums[1];
            int second = max(nums[1], nums[2]);
            for (int i = 3; i < n; i++) {
                int cur = max(nums[i] + first, second);
                first = second;
                second = cur;
            }
            return max(first, second);
        }
    }
    int rob(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        if (nums.size() == 1) {
            return nums[0];
        }
        if (nums.size() == 2) {
            return max(nums[0], nums[1]);
        }
        return max(maxAmount(nums, nums[0]), maxAmount(nums, -1));
    }
};

/* 650题只有两个健的键盘 */
/* 素数分解 */
class Solution {
public:
    int minSteps(int n) {
        int res = 0, d = 2;
        while (n > 1) {
            while (n % d == 0) {
                res += d;
                n /= d;
            }
            d++;
        }
        return res;
    }
};

/* 91题解码方法 */
/* 动态规划 */
/* dp[i]表示解码0～i的方法总数 */
/* 两种方式，单独s[i]，以及s[i-1],s[i]一起解码 */
/* 同时设置判断是都合法函数 */
class Solution {
public:
    bool isVaild(int first, int second) {
        if (first == 0) {
            return false;
        }
        int sum = first * 10 + second;
        return sum >= 1 && sum <= 26;
    }
    int numDecodings(string s) {
        if (s.empty() || s[0] == '0') {
            return 0;
        }
        if (s.size() == 1) {
            return 1;
        }
        vector<int> dp(s.size(), 0);
        dp[0] = 1;
        if (s[1] != '0') {
            dp[1]++;
        }
        if (isVaild(s[0] - '0', s[1] - '0')) {
            dp[1]++;
        }
        for (int i = 2; i < dp.size(); i++) {
            if (s[i] != '0') {
                dp[i] += dp[i - 1];
            }
            dp[i] += isVaild(s[i - 1] - '0', s[i] - '0') ? dp[i - 2] : 0;
        }
        return dp.back();
    }
};
/* 内存优化 */
class Solution {
public:
    bool isVaild(int first, int second) {
        if (first == 0) {
            return false;
        }
        int sum = first * 10 + second;
        return sum >= 1 && sum <= 26;
    }
    int numDecodings(string s) {
        if (s.empty() || s[0] == '0') {
            return 0;
        }
        if (s.size() == 1) {
            return 1;
        }
        int pre = 1, cur = 0;
        if (s[1] != '0') {
            cur++;
        }
        if (isVaild(s[0] - '0', s[1] - '0')) {
            cur++;
        }
        for (int i = 2; i < s.size(); i++) {
            int tmp = 0;
            if (s[i] != '0') {
                tmp += cur;
            }
            tmp += isVaild(s[i - 1] - '0', s[i] - '0') ? pre : 0;
            pre = cur;
            cur = tmp;
        }
        return cur;
    }
};
/* 修改，空字符串可以解码，解码为一个空字符串 */
class Solution {
public:
    bool isVaild(int first, int second) {
        if (first == 0) {
            return false;
        }
        int sum = first * 10 + second;
        return sum >= 1 && sum <= 26;
    }
    int numDecodings(string s) {
        if (s[0] == '0') {
            return 0;
        }
        if (s.empty() || s.size() == 1) {
            return 1;
        }
        int pre = 1, cur = 0;
        if (s[1] != '0') {
            cur++;
        }
        if (isVaild(s[0] - '0', s[1] - '0')) {
            cur++;
        }
        for (int i = 2; i < s.size(); i++) {
            int tmp = 0;
            if (s[i] != '0') {
                tmp += cur;
            }
            tmp += isVaild(s[i - 1] - '0', s[i] - '0') ? pre : 0;
            pre = cur;
            cur = tmp;
        }
        return cur;
    }
};

/* 32题最长有效括号 */
/* 栈 */
/* 主要问题是如何判断连续 */
class Solution {
public:
    int longestValidParentheses(string s) {
        if (s.size() < 2) {
            return 0;
        }
        int res = 0;
        stack<int> stk;
        stk.push(-1);
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (c == '(') {
                stk.push(i);
            } else {
                stk.pop();
                if (stk.empty()) {
                    stk.push(i);
                } else {
                    res = max(i - stk.top(), res);
                }
            }
        }
        return res;
    }
};
/* 动态规划 */
/* dp[i]字符s[i]结尾的最长有效长度 */
/* j=i-1-dp[i-1] */
/* j>=0 && s[j]='(' */
/* j==0  dp[i]=i-j+1 */
/* dp[i]=dp[j-1]+i-j=1 */
class Solution {
public:
    int longestValidParentheses(string s) {
        if (s.size() < 2) {
            return 0;
        }
        int res = 0;
        vector<int> dp(s.size(), 0);
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (c == '(' || i == 0) {
                continue;
            }
            int j = i - 1 - dp[i - 1];
            if (j >= 0 && s[j] == '(') {
                if (j == 0) {
                    dp[i] = i - j + 1;
                } else {
                    dp[i] = dp[j - 1] + i - j + 1;
                }
            }
            res = max(res, dp[i]);
        }
        return res;
    }
};

/* 121题买卖股票的最佳时机 */
/* 记录前0~i-1天的最低价格 */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() <= 1) {
            return 0;
        }
        int res = 0;
        int minPrice = prices[0];
        for (int i = 1; i < prices.size(); i++) {
            res = max(res, prices[i] - minPrice);
            minPrice = min(minPrice, prices[i]);
        }
        return res;
    }
};

/* 122题买卖股票的最佳时机II */
/* dp[i]前i天的最大利润 */
/* dp[i]=dp[i-1] price[i]=price[i-1] */
/* dp[i]=dp[i-1]+price[i]-price[i-1] */
/* price[i]>price[i-1] */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() <= 1) {
            return 0;
        }
        vector<int> dp(prices.size(), 0);
        for (int i = 1; i < dp.size(); i++) {
            dp[i] = dp[i - 1] +
                    (prices[i] > prices[i - 1] ? prices[i] - prices[i - 1] : 0);
        }
        return dp.back();
    }
};
/* 内存优化 */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() <= 1) {
            return 0;
        }
        int res = 0;
        for (int i = 1; i < prices.size(); i++) {
            res = res +
                  (prices[i] > prices[i - 1] ? prices[i] - prices[i - 1] : 0);
        }
        return res;
    }
};

/* 123题买卖股票的最佳时机III */
/* 动态规划，主要是设置状态 */
/* 每一天有5种状态 */
/* 什么也没干，买过1次股票 */
/* 卖过1次股票，卖过1次股票且买过2次股票 */
/* 卖过2次股票 */
/* 对于什么也没干其状态为0，不用设 */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(4, vector<int>(prices.size(), 0));
        dp[0][0] = -prices[0];
        dp[2][0] = -prices[0];
        for (int i = 1; i < prices.size(); i++) {
            dp[0][i] = max(dp[0][i - 1], -prices[i]);
            dp[1][i] = max(dp[1][i - 1], prices[i] + dp[0][i - 1]);
            dp[2][i] = max(dp[2][i - 1], dp[1][i - 1] - prices[i]);
            dp[3][i] = max(dp[3][i - 1], prices[i] + dp[2][i - 1]);
        }
        return dp[3].back();
    }
};
/* 内存优化 */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int buy1 = -prices[0], sell1 = 0, buy2 = -prices[0], sell2 = 0;
        for (int i = 1; i < prices.size(); i++) {
            buy1 = max(buy1, -prices[i]);
            sell1 = max(sell1, prices[i] + buy1);
            buy2 = max(buy2, sell1 - prices[i]);
            sell2 = max(sell2, prices[i] + buy2);
        }
        return sell2;
    }
};

/* 309题最佳买卖股票时机含冷冻期 */
/* 动态规划 */
/* 主要问题是准确确定状态 */
/* 持有股票 */
/* 不持有股票，处于冷冻期 */
/* 不持有股票，处于非冷冻期 */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() <= 1) {
            return 0;
        }
        vector<vector<int>> dp(3, vector<int>(prices.size(), 0));
        dp[1][0] = -prices[0];
        for (int i = 1; i < prices.size(); i++) {
            dp[0][i] = max(dp[0][i - 1], dp[2][i - 1]);
            dp[1][i] = max(dp[1][i - 1], dp[0][i - 1] - prices[i]);
            dp[2][i] = dp[1][i - 1] + prices[i];
        }
        return max(dp[0].back(), dp[2].back());
    }
};