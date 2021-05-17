/*
 * @Author: your name
 * @Date: 2021-05-17 23:42:56
 * @LastEditTime: 2021-05-17 23:57:03
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\头尾指针.cpp
 */

/* 15题三数之和 */
/* 双指针 */
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        if (nums.size() < 3) {
            return res;
        }
        sort(nums.begin(), nums.end());
        int length = nums.size();
        for (int first = 0; first < length; first++) {
            if (first > 0 && nums[first] == nums[first - 1]) {
                continue;
            }
            int targert = -nums[first];
            int second = first + 1, third = length - 1;
            while (second < third) {
                if (second > first + 1 && nums[second] == nums[second - 1]) {
                    second++;
                    continue;
                }
                int sum = nums[second] + nums[third];
                if (sum > targert) {
                    third--;
                } else if (sum < targert) {
                    second++;
                } else {
                    res.push_back({nums[first], nums[second], nums[third]});
                    second++;
                }
            }
        }
        return res;
    }
};
/* 循环换一种写法 */
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        if (nums.size() < 3) {
            return res;
        }
        sort(nums.begin(), nums.end());
        int length = nums.size();
        for (int first = 0; first < length; first++) {
            if (first > 0 && nums[first] == nums[first - 1]) {
                continue;
            }
            int targert = -nums[first];
            int third = length - 1;
            for (int second = first + 1; second < length;) {
                if (second > first + 1 && nums[second] == nums[second - 1]) {
                    second++;
                    continue;
                }
                if (second >= third) {
                    break;
                }
                int sum = nums[second] + nums[third];
                if (sum > targert) {
                    third--;
                } else if (sum < targert) {
                    second++;
                } else {
                    res.push_back({nums[first], nums[second], nums[third]});
                    second++;
                }
            }
        }
        return res;
    }
};