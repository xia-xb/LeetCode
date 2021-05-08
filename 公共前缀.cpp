/*
 * @Author: your name
 * @Date: 2021-05-04 22:16:53
 * @LastEditTime: 2021-05-04 22:21:48
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\公共前缀.cpp
 */

/* 最长公共前缀 */
/* 直接判断 */
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string res;
        int n = strs.size();
        for (int i = 0; i < strs[0].size(); i++) {
            char tmp = strs[0][i];
            for (int j = 1; j < n; j++) {
                if (i >= strs[j].size() || tmp != strs[j][i]) {
                    return res;
                }
            }
            res.push_back(tmp);
        }
        return res;
    }
};
