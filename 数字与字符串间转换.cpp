/*
 * @Author: your name
 * @Date: 2021-05-12 23:25:03
 * @LastEditTime: 2021-05-12 23:26:02
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\数字与字符串间转换.cpp
 */

/* 8题字符串转换整数（atoi） */
/* 直接转换，注意范围溢出问题 */
class Solution {
public:
    int myAtoi(string s) {
        long long res = 0;
        int i = 0;
        while (i < s.size() && s[i] == ' ') {
            i++;
        }
        int symbol = 1;
        if (s[i] == '-') {
            symbol = -1;
            i++;
        } else if (s[i] == '+') {
            symbol = 1;
            i++;
        } else if (s[i] >= '0' && s[i] <= '9') {
            symbol = 1;
        } else {
            return 0;
        }
        while (i < s.size() && (s[i] >= '0' && s[i] <= '9')) {
            res = res * 10 + s[i] - '0';
            if (symbol == 1 && res >= INT_MAX) {
                return INT_MAX;
            } else if (symbol == -1 && -1 * res <= INT_MIN) {
                return INT_MIN;
            }
            i++;
        }
        res *= symbol;
        return res;
    }
};
