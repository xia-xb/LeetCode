/*
 * @Author: your name
 * @Date: 2021-05-03 14:42:45
 * @LastEditTime: 2021-05-03 16:04:53
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\数组的旋转.cpp
 */


/* 189题旋转数组 */
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int position=k%nums.size();
        vector<int>tmp=nums;
        for(int i=0;i<nums.size();i++){
            nums[(i+position)%nums.size()]=tmp[i];
        }
    }
};
/* 数组翻转 */
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        reverse(nums.begin(),nums.end());
        vector<int>::iterator it=nums.begin();
        for(int i=0;i<k%nums.size();i++,it++){}
        reverse(nums.begin(),it);
        reverse(it,nums.end());
    }
};