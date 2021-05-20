/*
 * @Author: your name
 * @Date: 2021-05-20 22:47:57
 * @LastEditTime: 2021-05-20 23:41:21
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\前缀和与哈希表.cpp
 */

/* 523题连续的子数组和 */
/* 利用前缀和，同时通过哈希表存储前缀和 */
/* 注意利用取余的操作 */
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        mp[0] = -1;
        int sum = 0;
        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
            if (k != 0) {
                sum %= k;
            }
            if (mp.count(sum)) {
                if (i - mp[sum] >= 2) {
                    return true;
                }
            } else {
                mp[sum] = i;
            }
        }
        return false;
    }
};

/* 525题连续数组 */
/* 前缀和，哈希表 */
/* 注意前缀和概念可以扩展，为0，1个数的差值 */
/* 之后利用哈希表记录前缀和，前缀和相等则0，1个数相等 */
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> mp;
        mp[0] = -1;
        int res = 0, count = 0;
        for (int i = 0; i < nums.size(); ++i) {
            count += nums[i] == 1 ? 1 : -1;
            if (mp.count(count)) {
                res = max(res, i - mp[count]);
            } else {
                mp[count] = i;
            }
        }
        return res;
    }
};

/* 560题和为K的子数组 */
/* 前缀和，哈希表，注意前缀和性质、初始值 */
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        mp[0] = 1;
        int sum = 0, count = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            if (mp.count(sum - k)) {
                count += mp[sum - k];
            }
            mp[sum]++;
        }
        return count;
    }
};