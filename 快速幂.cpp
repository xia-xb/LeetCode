/*
 * @Author: 夏玄兵
 * @Date: 2021-07-06 22:34:28
 * @LastEditors: 夏玄兵
 * @LastEditTime: 2021-07-06 23:10:08
 * @Description: file content
 * @FilePath: \LeetCode\快速幂.cpp
 */

/* 50题Pow(x,n) */
/* 快速幂 */
class Solution {
public:
    double quickMul(double x, long long N) {
        double ans = 1.0;
        double xContribute = x;
        while (N > 0) {
            if (N % 2 == 1) {
                ans *= xContribute;
            }
            xContribute *= xContribute;
            N /= 2;
        }
        return ans;
    }
    double myPow(double x, int n) {
        long long N = n;
        return N > 0 ? quickMul(x, N) : 1.0 / quickMul(x, -N);
    }
};

/* 372题超级次方 */
/* 快速幂，递归 */
/* 取模运算简化 */
/* (a*b)%k=(a%k)(b%k)%k */
class Solution {
public:
    int base = 1337;
    int mypow(int a, int k) {
        a %= base;
        int res = 1;
        for (int i = 0; i < k; i++) {
            res *= a;
            res %= base;
        }
        return res;
    }
    int superPow(int a, vector<int>& b) {
        if (b.empty()) {
            return 1;
        }
        int last = b.back();
        b.pop_back();
        int part1 = mypow(a, last);
        int part2 = mypow(superPow(a, b), 10);
        return (part1 * part2) % base;
    }
};