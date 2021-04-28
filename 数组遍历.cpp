/*
 * @Author: your name
 * @Date: 2021-04-28 21:00:42
 * @LastEditTime: 2021-04-28 22:49:39
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\数组遍历.cpp
 */

/* 485题最大连续1的个数 */
/* 双指针，实时更新length */
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int left = 0, right = 0, length = 0;
        while (right < nums.size()) {
            if (nums[right] == 1) {
                right++;
            } else {
                length = max(length, right - left);
                right++;
                left = right;
            }
        }
        length = max(length, right - left);
        return length;
    }
};

/* 495题提莫攻击 */
class Solution {
public:
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        if (timeSeries.size() == 0) {
            return 0;
        }
        vector<int> length;
        length.resize(timeSeries.size());
        length[0] = duration;
        for (int i = 1; i < timeSeries.size(); i++) {
            if (timeSeries[i] >= timeSeries[i - 1] + duration) {
                length[i] = length[i - 1] + duration;
            } else {
                length[i] = length[i - 1] + timeSeries[i] - timeSeries[i - 1];
            }
        }
        return length[timeSeries.size() - 1];
    }
};

/* 414题第三大的数 */
/* 排序 */
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int res = nums[nums.size() - 1];
        int count = 1;
        for (int i = nums.size() - 1; i >= 0; i--) {
            if (nums[i] < res) {
                res = nums[i];
                count++;
                if (count == 3) {
                    break;
                }
            }
        }
        if (count == 3) {
            return res;
        } else {
            return nums[nums.size() - 1];
        }
    }
};

/* 628题三个数的最大乘积 */
/* 排序 */
class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        if (nums.size() <= 3) {
            int res = 1;
            for (int i = 0; i < nums.size(); i++) {
                res *= nums[i];
            }
            return res;
        }
        sort(nums.begin(), nums.end());
        int max1 = nums[nums.size() - 1], max2 = nums[nums.size() - 2];
        int max3 = nums[nums.size() - 3], min1 = nums[0];
        int min2 = nums[1];
        return max(max1 * max2 * max3, min1 * min2 * max1);
    }
};

/* 645题错误的集合 */
/* 直接统计出现次数 */
class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        vector<int> res;
        res.resize(2);
        vector<int> count(nums.size(), 0);
        for (int i = 0; i < nums.size(); i++) {
            count[nums[i] - 1]++;
        }
        for (int i = 0; i < count.size(); i++) {
            if (count[i] == 2) {
                res[0] = i + 1;
            }
            if (count[i] == 0) {
                res[1] = i + 1;
            }
        }
        return res;
    }
};
/* 排序，利用加和 */
class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        vector<int> res;
        res.resize(2);
        int sum = 0;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++) {
            if (i >= 1 && nums[i] == nums[i - 1]) {
                res[0] = nums[i];
            }
            sum += nums[i];
        }
        res[1] = res[0] - sum + (1 + nums.size()) * nums.size() / 2;
        return res;
    }
};

/* 697题数组的度 */
/* 遍历，哈希表记录 */
class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        unordered_map<int, vector<int>> mp;
        for (int i = 0; i < nums.size(); i++) {
            if (mp.count(nums[i]) == 0) {
                mp[nums[i]] = {1, i, i};
            } else {
                mp[nums[i]][0]++;
                mp[nums[i]][2] = i;
            }
        }
        unordered_map<int, vector<int>>::iterator it = mp.begin();
        int maxcount = it->second[0],
            minlength = it->second[2] - it->second[1] + 1;
        it++;
        for (; it != mp.end(); it++) {
            if (it->second[0] > maxcount) {
                maxcount = it->second[0];
                minlength = it->second[2] - it->second[1] + 1;
            } else if (it->second[0] == maxcount) {
                minlength = min(minlength, it->second[2] - it->second[1] + 1);
            }
        }
        return minlength;
    }
};
/* 后面遍历哈希表处，利用新特性auto */
class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        unordered_map<int, vector<int>> mp;
        for (int i = 0; i < nums.size(); i++) {
            if (mp.count(nums[i]) == 0) {
                mp[nums[i]] = {1, i, i};
            } else {
                mp[nums[i]][0]++;
                mp[nums[i]][2] = i;
            }
        }
        int maxcount = 0, minlength = 0;
        for (auto& [_, vec] : mp) {
            if (vec[0] > maxcount) {
                maxcount = vec[0];
                minlength = vec[2] - vec[1] + 1;
            } else if (vec[0] == maxcount) {
                minlength = min(minlength, vec[2] - vec[1] + 1);
            }
        }
        return minlength;
    }
};

/* 448题找到所有消失的数字 */
/* 原地建立哈希表 */
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int> res;
        for (int i = 0; i < nums.size(); i++) {
            int j = (nums[i] - 1) % nums.size();
            nums[j] += nums.size();
        }
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] <= nums.size()) {
                res.push_back(i + 1);
            }
        }
        return res;
    }
};

/* 442题数组中重复的数据 */
/* 思路类似原地哈希，只是建立标记 */
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> res;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[abs(nums[i]) - 1] > 0) {
                nums[abs(nums[i]) - 1] *= (-1);
            } else {
                res.push_back(abs(nums[i]));
            }
        }
        return res;
    }
};
