/*
 * @Author: your name
 * @Date: 2021-06-04 20:55:58
 * @LastEditTime: 2021-06-04 22:03:37
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
