/*
 * @Author: your name
 * @Date: 2021-05-16 22:20:35
 * @LastEditTime: 2021-05-16 22:40:30
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\哈希表与索引.cpp
 */

/* 1题两数之和 */
/* 利用map存储数据和下标 */
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> mp;
        vector<int> res;
        for (int i = 0; i < nums.size(); i++) {
            int num = nums[i];
            if (mp.count(target - num)) {
                res.push_back(i);
                res.push_back(mp[target - num]);
                break;
            } else {
                mp[num] = i;
            }
        }
        return res;
    }
};

/* 两数字和II-输入有序数组 */
/* 可以用哈希表解决 */
/* 但是利用升序排列特性，直接双指针 */
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int low = 0, high = numbers.size() - 1;
        vector<int> res;
        while (low < high) {
            int sum = numbers[low] + numbers[high];
            if (sum > target) {
                high--;
            } else if (sum < target) {
                low++;
            } else {
                res.push_back(low + 1);
                res.push_back(high + 1);
                break;
            }
        }
        return res;
    }
};

/* 219题存在重复元素II */
/* map存储元素和索引 */
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        for (int i = 0; i < nums.size(); i++) {
            int num = nums[i];
            if (mp.count(num) && i - mp[num] <= k) {
                return true;
            }
            mp[num] = i;
        }
        return false;
    }
};
