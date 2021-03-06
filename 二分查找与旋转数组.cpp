/*
 * @Author: your name
 * @Date: 2021-06-15 20:43:59
 * @LastEditTime: 2021-06-16 21:51:27
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /LeetCode/二分查找与旋转数组.cpp
 */

/* 153题寻找旋转排序数组中的最小值 */
/* 二分查找 */
/* 通过比较中间元素与右侧元素 */
/* 小于右侧元素说明最小值在左侧 */
/* 反之最小值在右侧 */
class Solution {
public:
    int findMin(vector<int>& nums) {
        int left=0,right=nums.size()-1;
        while(left<right){
            int mid=left+(right-left)/2;
            if(nums[mid]<nums[right]){
                right=mid;
            }else{
                left=mid+1;
            }
        }
        return nums[left];
    }
};

/* 154题寻找旋转排序数组中的最小值II */
/* 思路同153题类似 */
/* 由于重复元素，当中间和右侧元素相等时 */
/* 考虑旋转和没有旋转两种情况 */
/* 只能说明最小元素在右侧元素的左侧 */
/* 故需要增加一条判断相等的分支 */
class Solution {
public:
    int findMin(vector<int>& nums) {
        int left=0,right=nums.size()-1;
        while(left<right){
            int mid=left+(right-left)/2;
            if(nums[mid]<nums[right]){
                right=mid;
            }else if(nums[mid]>nums[right]){
                left=mid+1;
            }else{
                right-=1;
            }
        }
        return nums[left];
    }
};


/* 33题搜索旋转排序数组 */
/* 二分查找 */
/* 首先通过中间元素与右侧元素区分类型 */
/* 之后在根据target来判断所在区间 */
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left=0,right=nums.size()-1;
        while(left<=right){
            int mid=left+(right-left)/2;
            if(nums[mid]==target){
                return mid;
            }else if(nums[mid]<nums[right]){
                if(target>nums[mid] && target<=nums[right]){
                    left=mid+1;
                }else{
                    right=mid-1;
                }
            }else{
                if(target>=nums[left] && target<nums[mid]){
                    right=mid-1;
                }else{
                    left=mid+1;
                }
            }
        }
        return -1;
    }
};


/* 81题搜索旋转排序数组II */
/* 二分查找 */
/* 思路与33题类似 */
/* 主要问题是由于存在重复值，需要仔细考虑每种情况 */
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int left=0,right=nums.size()-1;
        while(left<=right){
            int mid=left+(right-left)/2;
            if(nums[mid]==target){
                return true;
            }else if(nums[mid]<nums[right]){
                if(target>nums[mid] && target<=nums[right]){
                    left=mid+1;
                }else{
                    right=mid-1;
                }
            }else if(nums[mid]==nums[right]){
                if(target>=nums[left] && target<nums[mid]){
                    right=mid-1;
                }else{
                    right--;
                }
            }else{
                if(target>=nums[left] && target<nums[mid]){
                    right=mid-1;
                }else{
                    left=mid+1;
                }
            }
        }
        return false;
    }
};
/* 另一种思考方式 */
/* 主要原因是重复元素的存在使得中间元素与左右元素相等时 */
/* 难以判断判断连续序列，该情况特殊对待left++,right--即可 */
/* 其他情况相同 */
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int left=0,right=nums.size()-1;
        while(left<=right){
            int mid=left+(right-left)/2;
            if(nums[mid]==target){
                return true;
            }else if(nums[mid]==nums[right] && nums[mid]==nums[left]){
                left++;
                right--;
            }else if(nums[mid]<=nums[right]){
                if(target>nums[mid] && target<=nums[right]){
                    left=mid+1;
                }else{
                    right=mid-1;
                }
            }else{
                if(target>=nums[left] && target<nums[mid]){
                    right=mid-1;
                }else{
                    left=mid+1;
                }
            }
        }
        return false;
    }
};