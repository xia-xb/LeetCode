/*
 * @Author: your name
 * @Date: 2021-05-04 22:02:35
 * @LastEditTime: 2021-05-04 22:02:35
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\回文串的定义.cpp
 */

/* 125题验证回文串 */
/* 双指针 */
/* 注意在判断大小字符差为32时，注意字符0与'P'的差也为32 */
class Solution {
public:
    bool isType(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
               (c >= '0' && c <= '9');
    }
    bool isChar(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }
    bool isSame(char c1, char c2) {
        return c1 == c2 ||
               (abs(c1 - c2) == 'a' - 'A' && isChar(c1) && isChar(c2));
    }
    bool isPalindrome(string s) {
        int left = 0, right = s.size() - 1;
        while (left < right) {
            while (left < right && !isType(s[left])) {
                left++;
            }
            while (left < right && !isType(s[right])) {
                right--;
            }
            if (left >= right) {
                return true;
            }
            if (!isSame(s[left++], s[right--])) {
                return false;
            }
        }
        return true;
    }
};
