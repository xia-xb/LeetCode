/*
 * @Author: 夏玄兵
 * @Date: 2021-07-05 21:51:05
 * @LastEditors: 夏玄兵
 * @LastEditTime: 2021-07-05 22:57:13
 * @Description: file content
 * @FilePath: \LeetCode\简单的数学题.cpp
 */

/* 492题构造矩形 */
/* 从中间开始计算 */
/* 类似滑动窗口 */
class Solution {
public:
    vector<int> constructRectangle(int area) {
        int l = sqrt(area);
        int w = l;
        int product = l * w;
        while (product != area) {
            if (product < area) {
                l++;
            } else {
                w--;
            }
            product = l * w;
        }
        return {l, w};
    }
};
/* 线性搜索 */
/* 注意是宽度变化，而不是长度变化 */
/* 长度变化有问题，因为取平方根后其值是小于等于真实平方根 */
class Solution {
public:
    vector<int> constructRectangle(int area) {
        int w = sqrt(area);
        while (area % w != 0) {
            w--;
        }
        return {area / w, w};
    }
};

/* 29题两数相除 */
/* 快速乘+二分查找 */
class Solution {
public:
    long mul(long a, long b) {
        long ans = 0;
        while (b > 0) {
            if (b & 1) {
                ans += a;
            }
            b >>= 1;
            a += a;
        }
        return ans;
    }
    int divide(int dividend, int divisor) {
        if (dividend == 0) {
            return 0;
        }
        if (divisor == 1) {
            return dividend;
        }
        if (divisor == -1) {
            if (dividend == INT_MIN) {
                return INT_MAX;
            }
            return -dividend;
        }
        long dividendAbs = abs(dividend), divisorAbs = abs(divisor);
        long left = 0, right = dividendAbs;
        while (left < right) {
            long mid = left + right + 1 >> 1;
            if (mul(mid, divisorAbs) <= dividendAbs) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }
        long ans =
            (dividend > 0 && divisor > 0) || (dividend < 0 && divisor < 0)
                ? left
                : -left;
        if (ans > INT_MAX || ans < INT_MIN) {
            return INT_MAX;
        }
        return (int)ans;
    }
};
/* 修改二分查找部分程序 */
/* 改为一般的模板类型 */
class Solution {
public:
    long mul(long a, long b) {
        long ans = 0;
        while (b > 0) {
            if (b & 1) {
                ans += a;
            }
            b >>= 1;
            a += a;
        }
        return ans;
    }
    int divide(int dividend, int divisor) {
        if (dividend == 0) {
            return 0;
        }
        if (divisor == 1) {
            return dividend;
        }
        if (divisor == -1) {
            if (dividend == INT_MIN) {
                return INT_MAX;
            }
            return -dividend;
        }
        long dividendAbs = abs(dividend), divisorAbs = abs(divisor);
        long left = 0, right = dividendAbs;
        while (left <= right) {
            long mid = left + right + 1 >> 1;
            long product = mul(mid, divisorAbs);
            if (product == dividendAbs) {
                right = mid;
                break;
            } else if (product < dividendAbs) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        long ans =
            (dividend > 0 && divisor > 0) || (dividend < 0 && divisor < 0)
                ? right
                : -right;
        if (ans > INT_MAX || ans < INT_MIN) {
            return INT_MAX;
        }
        return (int)ans;
    }
};

/* 507题完美数 */
/* 遍历因数 */
class Solution {
public:
    bool checkPerfectNumber(int num) {
        if (num == 1) {
            return false;
        }
        int upLimit = sqrt(num);
        int sum = 1;
        for (int i = 2; i <= upLimit; i++) {
            if (num % i == 0) {
                if (i == sqrt(num)) {
                    sum += upLimit;
                } else {
                    sum += i + num / i;
                }
            }
        }
        return sum == num;
    }
};