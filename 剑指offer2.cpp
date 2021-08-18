/*
 * @Author: your name
 * @Date: 2021-08-18 23:31:07
 * @LastEditTime: 2021-08-19 00:11:30
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /LeetCode/剑指offer2.cpp
 */

/* 2 二进制加法 */
/* 模拟 */
class Solution {
public:
    char ans(char c1, char c2, int flag) {
        bool a1 = c1 == '1', a2 = c2 == '1', a3 = flag == 1;
        if (a1 ^ a2 ^ a3) {
            return '1';
        }
        return '0';
    }
    int carry(char c1, char c2, int flag) {
        bool a1 = c1 == '1', a2 = c2 == '1', a3 = flag == 1;
        if ((a1 && a2) || (a2 && a3) || (a1 && a3)) {
            return 1;
        }
        return 0;
    }
    string addBinary(string a, string b) {
        int i = a.size() - 1, j = b.size() - 1;
        int flag = 0;
        string res;
        while (i >= 0 && j >= 0) {
            char c1 = a[i--], c2 = b[j--];
            res += ans(c1, c2, flag);
            flag = carry(c1, c2, flag);
        }
        while (i >= 0) {
            res += ans(a[i], '0', flag);
            flag = carry(a[i--], '0', flag);
        }
        while (j >= 0) {
            res += ans(b[j], '0', flag);
            flag = carry(b[j--], '0', flag);
        }
        if (flag) {
            res += '1';
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
/* 代码优化 */
class Solution {
public:
    string addBinary(string a, string b) {
        int i = a.size() - 1, j = b.size() - 1;
        int carry = 0;
        string res;
        while (i >= 0 || j >= 0 || carry == 1) {
            int num1 = i >= 0 ? a[i] - '0' : 0;
            int num2 = j >= 0 ? b[j] - '0' : 0;
            int sum = num1 + num2 + carry;
            res += '0' + sum % 2;
            carry = sum / 2;
            i--;
            j--;
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

/* 3 前n个数字二进制中1的个数 */
/* 动态规划 */
/* 根据奇偶数的性质 */
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> dp(n + 1, 0);
        bool flag = true;
        for (int i = 1; i <= n; i++) {
            dp[i] = flag ? dp[i - 1] + 1 : dp[i / 2];
            flag = !flag;
        }
        return dp;
    }
};
