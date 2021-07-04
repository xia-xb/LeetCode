/*
 * @Author: 夏玄兵
 * @Date: 2021-07-02 21:59:43
 * @LastEditors: 夏玄兵
 * @LastEditTime: 2021-07-04 23:31:07
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

/* 461题汉明距离 */
/* 先将两个数求异或 */
/* 再求汉明距离即可 */
class Solution {
public:
    int hammingDistance(int x, int y) {
        int nums = x ^ y;
        int res = 0;
        while (nums != 0) {
            nums = nums & (nums - 1);
            res++;
        }
        return res;
    }
};
/* 通过左移计算汉明距离 */
class Solution {
public:
    int hammingDistance(int x, int y) {
        int nums = x ^ y;
        int res = 0;
        while (nums != 0) {
            res += nums & 1;
            nums >>= 1;
        }
        return res;
    }
};
/* 左移 */
class Solution {
public:
    int hammingDistance(int x, int y) {
        int nums = x ^ y;
        int res = 0;
        for (int i = 0; i < 31; i++) {
            res += (nums >> i) & 1;
        }
        return res;
    }
};

/* 477题汉明距离总和 */
/* 通过左移取出元素各位的数 */
/* 对于每一位，汉明距离总和为c*(n-c) */
/* c为数为1的个数，n为总个数 */
class Solution {
public:
    int totalHammingDistance(vector<int>& nums) {
        int ans = 0, n = nums.size();
        for (int i = 0; i < 30; ++i) {
            int c = 0;
            for (int val : nums) {
                c += (val >> i) & 1;
            }
            ans += c * (n - c);
        }
        return ans;
    }
};

/* 693题交替位二进制数 */
/* 不断左移判断1，0 */
class Solution {
public:
    bool hasAlternatingBits(int n) {
        int pre = (n >> 0) & 1;
        while (n != 0) {
            n >>= 1;
            int c = n & 1;
            if (c == pre) {
                return false;
            }
            pre = c;
        }
        return true;
    }
};

/* 258题各位相加 */
/* 递归 */
/* 注意除以10以后得到的结果还要再递归 */
class Solution {
public:
    int addDigits(int num) {
        if (num < 10) {
            return num;
        }
        return addDigits(num % 10 + addDigits(num / 10));
    }
};

/* 171题Excel表列序号 */
/* 遍历每一个字符，计算权值 */
class Solution {
public:
    int titleToNumber(string columnTitle) {
        long res = 0;
        long weight = 1;
        for (int i = columnTitle.size() - 1; i >= 0; i--) {
            res += weight * (columnTitle[i] - 'A' + 1);
            weight *= 26;
        }
        return res;
    }
};

/* 168题Excel表列名称 */
/* 类似于进制换算 */
/* 需要注意的是不同于10进制 */
/* 它是从1开始的，所以需要先减一 */
class Solution {
public:
    string convertToTitle(int columnNumber) {
        string res;
        while (columnNumber > 0) {
            columnNumber--;
            res += columnNumber % 26 + 'A';
            columnNumber /= 26;
        }
        reverse(res.begin(), res.end());
        return res;
    }
};