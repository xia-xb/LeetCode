/*
 * @Author: your name
 * @Date: 2021-06-04 20:55:58
 * @LastEditTime: 2021-06-05 21:02:34
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\二分查找应用（简单）.cpp
 */

/* 35题搜索插入位置 */
/* 循环遍历 */
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int res;
        for (res = 0; res < nums.size(); res++) {
            if (nums[res] >= target) {
                return res;
            }
        }
        return nums.size();
    }
};
/* 二分查找 */
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return nums[left] >= target ? left : left + 1;
    }
};
/* 注意区间细节 ，由此判定while条件*/
/* 上面代码不合适 */
class Solution {
public:
    int mySqrt(int x) {
        int left = 0, right = x;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            long long midValue = pow(mid, 2);
            if (midValue == x) {
                return mid;
            } else if (midValue < x) {
                left = mid + 1;
            } else if (midValue > x) {
                right = mid - 1;
            }
        }
        return left ? left - 1 : left;
    }
};
/* 二分查找优化 */
/* 由于小数部分舍去，则结果平方小于等于x */
/* 从而当midValue小于x时，将ans更新为mid */
/* 最后直接返回ans即可 */
class Solution {
public:
    int mySqrt(int x) {
        int left = 0, right = x, ans = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            long long midValue = pow(mid, 2);
            if (midValue == x) {
                return mid;
            } else if (midValue < x) {
                left = mid + 1;
                ans = mid;
            } else if (midValue > x) {
                right = mid - 1;
            }
        }
        return ans;
    }
};

/* 278题第一个错误版本 */
/* 二分查找 */
/* 类似于查找最左侧元素 */
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int left = 1, right = n;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (isBadVersion(mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return right == n ? -1 : right + 1;
    }
};

/* 367题有效的完全平方数 */
/* 二分查找法 */
class Solution {
public:
    bool isPerfectSquare(int num) {
        int left = 0, right = num;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            long long minValue = pow(mid, 2);
            if (minValue == num) {
                return true;
            } else if (minValue < num) {
                left = mid + 1;
            } else if (minValue > num) {
                right = mid - 1;
            }
        }
        return false;
    }
};
/* 单独考虑1的情况 */
/* 其他情况下，right=num/2，减少循环次数 */
class Solution {
public:
    bool isPerfectSquare(int num) {
        if (num < 2) {
            return true;
        }
        int left = 0, right = num / 2;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            long long minValue = pow(mid, 2);
            if (minValue == num) {
                return true;
            } else if (minValue < num) {
                left = mid + 1;
            } else if (minValue > num) {
                right = mid - 1;
            }
        }
        return false;
    }
};

/* 374题猜数字大小 */
/* 二分查找 */
/**
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is lower than the guess number
 *			      1 if num is higher than the guess number
 *               otherwise return 0
 * int guess(int num);
 */

class Solution {
public:
    int guessNumber(int n) {
        int left = 1, right = n;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (guess(mid) == 0) {
                return mid;
            } else if (guess(mid) > 0) {
                left = mid + 1;
            } else if (guess(mid) < 0) {
                right = mid - 1;
            }
        }
        return -1;
    }
};

/* 441题排列硬币 */
/* 二分查找 */
/* 注意数据类型的范围 */
class Solution {
public:
    int arrangeCoins(int n) {
        long left = 0, right = n;
        while (left <= right) {
            long mid = left + (right - left) / 2;
            long long midValue = mid * (1 + mid) / 2;
            if (midValue == n) {
                return mid;
            } else if (midValue < n) {
                left = mid + 1;
            } else if (midValue > n) {
                right = mid - 1;
            }
        }
        return left - 1;
    }
};