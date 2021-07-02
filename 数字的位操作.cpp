/*
 * @Author: 夏玄兵
 * @Date: 2021-07-02 21:59:43
 * @LastEditors: 夏玄兵
 * @LastEditTime: 2021-07-02 22:30:22
 * @Description: file content
 * @FilePath: \LeetCode\数字的位操作.cpp
 */

/* 9题回文数 */
/* 转换为字符串，之后通过双指针判断 */
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        }
        string s = to_string(x);
        int left = 0, right = s.size() - 1;
        while (left < right) {
            if (s[left++] != s[right--]) {
                return false;
            }
        }
        return true;
    }
};

/* 231题2的幂 */
/* 2的幂，则二进制表示只有1个1 */
/* 通过n&(n-1)即可判断 */
class Solution {
public:
    bool isPowerOfTwo(int n) {
        if (n <= 0) {
            return false;
        }
        return (n & (n - 1)) == 0;
    }
};

/* 342题4的幂 */
/* 不断除以4 */
class Solution {
public:
    bool isPowerOfFour(int n) {
        if (n <= 0) {
            return false;
        }
        while (n != 1) {
            if (n % 4 != 0) {
                return false;
            }
            n /= 4;
        }
        return true;
    }
};

/* 3的幂 */
/* 不断除以3 */
class Solution {
public:
    bool isPowerOfThree(int n) {
        if (n <= 0) {
            return false;
        }
        while (n != 1) {
            if (n % 3 != 0) {
                return false;
            }
            n /= 3;
        }
        return true;
    }
};

/* 位1的个数 */
/* 利用n&(n-1)不断清除最后一个1 */
/* 同时记录1的个数 */
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int res = 0;
        while (n != 0) {
            n = n & (n - 1);
            res++;
        }
        return res;
    }
};
