/*
 * @Author: your name
 * @Date: 2021-05-19 20:24:35
 * @LastEditTime: 2021-05-19 22:23:55
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\哈希表与统计.cpp
 */

/* 18题四数之和 */
/* 双指针，思路类似三数之和 */
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        if (nums.size() < 4) {
            return res;
        }
        sort(nums.begin(), nums.end());
        int length = nums.size();
        for (int first = 0; first < length; first++) {
            if (first > 0 && nums[first] == nums[first - 1]) {
                continue;
            }
            for (int second = first + 1; second < length; second++) {
                if (second > first + 1 && nums[second] == nums[second - 1]) {
                    continue;
                }
                int NewTarget = target - nums[first] - nums[second];
                int third = second + 1, fourth = length - 1;
                while (third < fourth) {
                    if (third > second + 1 && nums[third] == nums[third - 1]) {
                        third++;
                        continue;
                    }
                    int sum = nums[third] + nums[fourth];
                    if (sum > NewTarget) {
                        fourth--;
                    } else if (sum < NewTarget) {
                        third++;
                    } else {
                        res.push_back({nums[first], nums[second], nums[third],
                                       nums[fourth]});
                        third++;
                    }
                }
            }
        }
        return res;
    }
};
/* 注意剪枝 */
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        if (nums.size() < 4) {
            return res;
        }
        sort(nums.begin(), nums.end());
        int length = nums.size();
        for (int first = 0; first < length - 3; first++) {
            if (first > 0 && nums[first] == nums[first - 1]) {
                continue;
            }
            if (nums[first] + nums[first + 1] + nums[first + 2] +
                    nums[first + 3] >
                target) {
                break;
            }
            if (nums[first] + nums[length - 3] + nums[length - 2] +
                    nums[length - 1] <
                target) {
                continue;
            }
            for (int second = first + 1; second < length - 2; second++) {
                if (second > first + 1 && nums[second] == nums[second - 1]) {
                    continue;
                }
                if (nums[first] + nums[second] + nums[second + 1] +
                        nums[second + 2] >
                    target) {
                    break;
                }
                if (nums[first] + nums[second] + nums[length - 2] +
                        nums[length - 1] <
                    target) {
                    continue;
                }
                int NewTarget = target - nums[first] - nums[second];
                int third = second + 1, fourth = length - 1;
                while (third < fourth) {
                    if (third > second + 1 && nums[third] == nums[third - 1]) {
                        third++;
                        continue;
                    }
                    int sum = nums[third] + nums[fourth];
                    if (sum > NewTarget) {
                        fourth--;
                    } else if (sum < NewTarget) {
                        third++;
                    } else {
                        res.push_back({nums[first], nums[second], nums[third],
                                       nums[fourth]});
                        third++;
                    }
                }
            }
        }
        return res;
    }
};

/* 350题两个数组的交集II */
/* 排序，双指针 */
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        vector<int> res;
        if (nums1.empty() || nums2.empty()) {
            return res;
        }
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        for (int i = 0, j = 0; i < nums1.size() && j < nums2.size();) {
            if (nums1[i] > nums2[j]) {
                j++;
            } else if (nums1[i] < nums2[j]) {
                i++;
            } else {
                res.push_back(nums1[i]);
                i++;
                j++;
            }
        }
        return res;
    }
};
/* 哈希表存储元素以及出现次数 */
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        vector<int> res;
        if (nums1.empty() || nums2.empty()) {
            return res;
        }
        unordered_map<int, int> mp;
        for (int i = 0; i < nums1.size(); ++i) {
            ++mp[nums1[i]];
        }
        for (int i = 0; i < nums2.size(); ++i) {
            int n = nums2[i];
            if (mp.count(n) && mp[n] > 0) {
                res.push_back(n);
                --mp[n];
            }
        }
        return res;
    }
};

/* 454题四数相加II */
/* 哈希表存储两数相加之和、数量 */
class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3,
                     vector<int>& nums4) {
        int count = 0;
        if (nums1.empty() || nums2.empty() || nums3.empty() || nums4.empty()) {
            return count;
        }
        unordered_map<int, int> sum1, sum2;
        for (int i = 0; i < nums1.size(); ++i) {
            int n = nums1[i];
            for (int j = 0; j < nums2.size(); ++j) {
                ++sum1[n + nums2[j]];
            }
        }
        for (int i = 0; i < nums3.size(); ++i) {
            int n = nums3[i];
            for (int j = 0; j < nums4.size(); ++j) {
                ++sum2[n + nums4[j]];
            }
        }
        for (const auto& s : sum1) {
            if (sum2.count(-s.first)) {
                count += s.second * sum2[-s.first];
            }
        }
        return count;
    }
};

/* 594题最长和谐子序列 */
/* 哈希表存储元素以及其出现的次数 */
/* 需要注意的是，和谐数组最大值最小值的差为1， */
/* 故和谐数组只有最大值最小值组成，即是由两个相邻数组成 */
class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> mp;
        for (int i = 0; i < nums.size(); ++i) {
            ++mp[nums[i]];
        }
        int length = 0;
        for (const auto& m : mp) {
            if (mp.count(m.first - 1)) {
                length = max(length, m.second + mp[m.first - 1]);
            }
        }
        return length;
    }
};