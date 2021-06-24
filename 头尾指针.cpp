/*
 * @Author: your name
 * @Date: 2021-05-17 23:42:56
 * @LastEditTime: 2021-06-24 22:56:12
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\头尾指针.cpp
 */

/* 345题 */
/* 双指针 */
class Solution {
public:
    bool isVowels(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
               c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
    }
    string reverseVowels(string s) {
        int left = 0, right = s.size() - 1;
        while (left < right) {
            char cleft = s[left], cright = s[right];
            if (isVowels(cleft) && isVowels(cright)) {
                swap(s[left++], s[right--]);
            } else {
                if (!isVowels(cleft)) {
                    left++;
                }
                if (!isVowels(cright)) {
                    right--;
                }
            }
        }
        return s;
    }
};

/* 680题验证回文字符串II */
/* 双指针，递归 */
class Solution {
public:
    bool isPalindrome(string& s, int left, int right, int num) {
        if (left >= right) {
            return true;
        }
        if (s[left] == s[right]) {
            return isPalindrome(s, left + 1, right - 1, num);
        } else if (num == 0) {
            return isPalindrome(s, left, right - 1, 1) ||
                   isPalindrome(s, left + 1, right, 1);
        }
        return false;
    }
    bool validPalindrome(string s) {
        return isPalindrome(s, 0, s.size() - 1, 0);
    }
};

/* 167题两数之和II-输入有序数组 */
/* 双指针 */
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0, right = numbers.size() - 1;
        while (left < right) {
            int sum = numbers[left] + numbers[right];
            if (sum == target) {
                return {left + 1, right + 1};
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
        return {0, 0};
    }
};

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
/* 第一个代码优化 */
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        if (nums.size() < 3) {
            return res;
        }
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int first = 0; first < n; first++) {
            if (first > 0 && nums[first] == nums[first - 1]) {
                continue;
            }
            int target = -nums[first];
            int second = first + 1, third = n - 1;
            while (second < third) {
                int sum = nums[second] + nums[third];
                if (sum == target) {
                    res.push_back({nums[first], nums[second], nums[third]});
                    second++;  //特别注意，这里必须先加一，否则陷入死循环
                    while (second < third && second > first + 1 &&
                           nums[second] == nums[second - 1]) {
                        second++;
                    }
                } else if (sum < target) {
                    second++;
                } else {
                    third--;
                }
            }
        }
        return res;
    }
};

/* 16题最接近的三数之和 */
/* 双指针 */
/* 思路与三数之和类似，主要是逻辑判断 */
class Solution {
public:
    int dis(int sum, int target) { return abs(sum - target); }
    int threeSumClosest(vector<int>& nums, int target) {
        int res = 0;
        if (nums.size() <= 3) {
            for (int it : nums) {
                res += it;
            }
            return res;
        }
        res = nums[0] + nums[1] + nums[2];
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int first = 0; first < n; first++) {
            if (first > 0 && nums[first] == nums[first - 1]) {
                continue;
            }
            int newTarget = target - nums[first];
            int second = first + 1, third = n - 1;
            while (second < third) {
                if (second > first + 1 && nums[second] == nums[second - 1]) {
                    second++;
                    continue;
                }
                int sum = nums[second] + nums[third];
                if (sum == newTarget) {
                    return target;
                }
                if (dis(sum + nums[first], target) < dis(res, target)) {
                    res = sum + nums[first];
                }
                if (sum < newTarget) {
                    second++;
                } else {
                    third--;
                }
            }
        }
        return res;
    }
};
/* 代码优化 */
class Solution {
public:
    int dis(int sum, int target) { return abs(sum - target); }
    int threeSumClosest(vector<int>& nums, int target) {
        int res = 0;
        if (nums.size() <= 3) {
            for (int it : nums) {
                res += it;
            }
            return res;
        }
        res = nums[0] + nums[1] + nums[2];
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int first = 0; first < n; first++) {
            if (first > 0 && nums[first] == nums[first - 1]) {
                continue;
            }
            int second = first + 1, third = n - 1;
            while (second < third) {
                if (second > first + 1 && nums[second] == nums[second - 1]) {
                    second++;
                    continue;
                }
                if (third < n - 1 && nums[third] == nums[third + 1]) {
                    third--;
                    continue;
                }
                int sum = nums[first] + nums[second] + nums[third];
                if (dis(sum, target) < dis(res, target)) {
                    res = sum;
                }
                if (sum == target) {
                    return target;
                } else if (sum < target) {
                    second++;
                } else {
                    third--;
                }
            }
        }
        return res;
    }
};

/* 18题四数之和 */
/* 和三数之和类似 */
/* 多一层循环 */
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        if (nums.size() < 4) {
            return {};
        }
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<vector<int>> res;
        for (int first = 0; first < n - 3; first++) {
            if (first > 0 && nums[first] == nums[first - 1]) {
                continue;
            }
            for (int second = first + 1; second < n - 2; second++) {
                if (second > first + 1 && nums[second] == nums[second - 1]) {
                    continue;
                }
                int newTarget = target - nums[first] - nums[second];
                int third = second + 1, fourth = n - 1;
                while (third < fourth) {
                    int sum = nums[third] + nums[fourth];
                    if (sum == newTarget) {
                        res.push_back({nums[first], nums[second], nums[third],
                                       nums[fourth]});
                        third++;
                        while (third < fourth && third > second + 1 &&
                               nums[third] == nums[third - 1]) {
                            third++;
                        }
                    } else if (sum < newTarget) {
                        third++;
                        while (third < fourth && third > second + 1 &&
                               nums[third] == nums[third - 1]) {
                            third++;
                        }
                    } else {
                        fourth--;
                        while (third < fourth && fourth < n - 1 &&
                               nums[fourth] == nums[fourth + 1]) {
                            fourth--;
                        }
                    }
                }
            }
        }
        return res;
    }
};
/* 剪枝 */
/* 注意大于和小于时剪枝是不一样的 */
/* 一个是break,一个是continue */
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        if (nums.size() < 4) {
            return {};
        }
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<vector<int>> res;
        for (int first = 0; first < n - 3; first++) {
            if (first > 0 && nums[first] == nums[first - 1]) {
                continue;
            }
            if (nums[first] + nums[first + 1] + nums[first + 2] +
                    nums[first + 3] >
                target) {
                break;
            }
            if (nums[first] + nums[n - 3] + nums[n - 2] + nums[n - 1] <
                target) {
                continue;
            }
            for (int second = first + 1; second < n - 2; second++) {
                if (second > first + 1 && nums[second] == nums[second - 1]) {
                    continue;
                }
                if (nums[first] + nums[second] + nums[second + 1] +
                        nums[second + 2] >
                    target) {
                    break;
                }
                if (nums[first] + nums[second] + nums[n - 2] + nums[n - 1] <
                    target) {
                    continue;
                }
                int newTarget = target - nums[first] - nums[second];
                int third = second + 1, fourth = n - 1;
                while (third < fourth) {
                    int sum = nums[third] + nums[fourth];
                    if (sum == newTarget) {
                        res.push_back({nums[first], nums[second], nums[third],
                                       nums[fourth]});
                        third++;
                        while (third < fourth && third > second + 1 &&
                               nums[third] == nums[third - 1]) {
                            third++;
                        }
                    } else if (sum < newTarget) {
                        third++;
                        while (third < fourth && third > second + 1 &&
                               nums[third] == nums[third - 1]) {
                            third++;
                        }
                    } else {
                        fourth--;
                        while (third < fourth && fourth < n - 1 &&
                               nums[fourth] == nums[fourth + 1]) {
                            fourth--;
                        }
                    }
                }
            }
        }
        return res;
    }
};