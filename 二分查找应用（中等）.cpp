/*
 * @Author: your name
 * @Date: 2021-06-05 21:02:55
 * @LastEditTime: 2021-06-09 22:40:38
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

/* 540题有序数组中的单一元素 */
/* 二分查找，通过子数组长度的奇偶 */
/* 判断单一元素位置 */
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        }
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            bool halvesAreEven = (right - mid) % 2;
            if (nums[mid] == nums[mid - 1]) {
                if (halvesAreEven) {
                    left = mid + 1;
                } else {
                    right = mid - 2;
                }
            } else if (nums[mid] == nums[mid + 1]) {
                if (halvesAreEven) {
                    right = mid - 1;
                } else {
                    left = mid + 2;
                }
            } else {
                return nums[mid];
            }
        }
        return nums[right];
    }
};

/* 658题找到K个最接近的元素 */
/* 二分查找找到元素位置 */
/* 若找不到，则从left,right直接开始 */
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int left = 0, right = arr.size() - 1;
        int position = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == x) {
                position = mid;
                break;
            } else if (arr[mid] < x) {
                left = mid + 1;
            } else if (arr[mid] > x) {
                right = mid - 1;
            }
        }
        if (position == -1) {
            if (right < 0) {
                position = -1;
            } else {
                position = right;
            }
        }
        vector<int> res;
        if (position == -1) {
            if (x < arr[0]) {
                return vector<int>(arr.begin(), arr.begin() + k);
            } else {
                return vector<int>(arr.end() - k, arr.end());
            }
        } else {
            int left = position, right = position + 1;
            while (k--) {
                if (left < 0) {
                    res.push_back(arr[right++]);
                } else if (right >= arr.size()) {
                    res.push_back(arr[left--]);
                } else {
                    if (abs(arr[left] - x) <= abs(arr[right] - x)) {
                        res.push_back(arr[left--]);
                    } else {
                        res.push_back(arr[right++]);
                    }
                }
            }
            sort(res.begin(), res.end());
            return res;
        }
    }
};

/* 436题寻找右区间 */
/* 首先定义一个数组记录个区间的起始值，并排序 */
/* 定义一个map记录各起始值对应的区间下标 */
/* 通过二分查找法寻找起始位置中大于等于该终止值的最小值 */
/* 找不到则为-1 */
/* 需要注意的是，二分查找中最后通过left判断返回 */
/* 因为left对应较大的起始值，且right对应的起始值永远小于终止值 */
/* （若没有找到刚好等于终止值的起始值） */
class Solution {
public:
    int findRightIntervalIndex(vector<int>& startNum,
                               unordered_map<int, int>& index, int endi) {
        int left = 0, right = startNum.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (startNum[mid] == endi) {
                return index[startNum[mid]];
            } else if (startNum[mid] < endi) {
                left = mid + 1;
            } else if (startNum[mid] > endi) {
                right = mid - 1;
            }
        }
        if (left >= startNum.size() || startNum[left] < endi) {
            return -1;
        } else {
            return index[startNum[left]];
        }
    }
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        vector<int> res;
        vector<int> startNum;
        unordered_map<int, int> index;
        for (int i = 0; i < intervals.size(); i++) {
            startNum.push_back(intervals[i][0]);
            index[intervals[i][0]] = i;
        }
        sort(startNum.begin(), startNum.end());
        for (int i = 0; i < intervals.size(); i++) {
            res.push_back(
                findRightIntervalIndex(startNum, index, intervals[i][1]));
        }
        return res;
    }
};

/* 300题最长递增子序列 */
/* 动态规划 */
class Solution {
public:
    int preLength(vector<int>& nums, vector<int>& length, int i, int num) {
        int ans = 0;
        for (int j = i; j >= 0; j--) {
            if (nums[j] < num) {
                ans = max(ans, length[j]);
            }
        }
        return ans;
    }
    int lengthOfLIS(vector<int>& nums) {
        vector<int> length(nums.size(), 0);
        for (int i = 0; i < nums.size(); i++) {
            length[i] = preLength(nums, length, i - 1, nums[i]) + 1;
        }
        sort(length.begin(), length.end());
        return length.back();
    }
};
/* 动态规划代码优化 */
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> length(nums.size(), 0);
        for (int i = 0; i < nums.size(); i++) {
            length[i] = 1;
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    length[i] = max(length[i], length[j] + 1);
                }
            }
        }
        sort(length.begin(), length.end());
        return length.back();
    }
};
