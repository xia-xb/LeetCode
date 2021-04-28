/*
 * @Author: your name
 * @Date: 2021-04-28 22:58:44
 * @LastEditTime: 2021-04-28 23:01:42
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\数组的改变、移动.cpp
 */

/* 453题最小操作次数使数组元素相等 */
/* 排序，所有非最大数加一，等价于最大数减一 */
/* 于是，所有数相等即为所有数最后都等于最小数 */
class Solution {
public:
    int minMoves(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int minNum = nums[0];
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
        }
        return sum - minNum * nums.size();
    }
};
/* 改进 */
class Solution {
public:
    int minMoves(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int minNum = nums[0];
        int count = 0;
        for (int i = 0; i < nums.size(); i++) {
            count += nums[i] - minNum;
        }
        return count;
    }
};
