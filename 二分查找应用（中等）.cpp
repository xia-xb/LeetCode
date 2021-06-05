/*
 * @Author: your name
 * @Date: 2021-06-05 21:02:55
 * @LastEditTime: 2021-06-05 22:29:45
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\二分查找应用（中等）.cpp
 */

/* 34题在排序数组中查找元素的第一个和最后一个位置 */
/* 通过两次二分查找 */
/* 找到元素最左侧和最右侧位置 */
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if (nums.empty()) {
            return {-1, -1};
        }
        int left = 0, right = nums.size() - 1;
        int begin = -1, end = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                right = mid - 1;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else if (nums[mid] > target) {
                right = mid - 1;
            }
        }
        if (left >= nums.size() || nums[left] != target) {
            begin = -1;
        } else {
            begin = left;
        }
        left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                left = mid + 1;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else if (nums[mid] > target) {
                right = mid - 1;
            }
        }
        if (right < 0 || nums[right] != target) {
            end = -1;
        } else {
            end = right;
        }
        return {begin, end};
    }
};
