/*
 * @Author: your name
 * @Date: 2021-06-21 22:25:16
 * @LastEditTime: 2021-06-21 23:24:09
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /LeetCode/栈与括号匹配.cpp
 */

/* 20题有效的括号 */
/* 通过栈存储符号 */
/* 注意栈为空的情况 */
class Solution {
public:
    bool isValid(string s) {
        if (s.size() == 1) {
            return false;
        }
        stack<char> stk;
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (c == ')') {
                if (stk.empty() || stk.top() != '(') {
                    return false;
                }
                stk.pop();
            } else if (c == ']') {
                if (stk.empty() || stk.top() != '[') {
                    return false;
                }
                stk.pop();
            } else if (c == '}') {
                if (stk.empty() || stk.top() != '{') {
                    return false;
                }
                stk.pop();
            } else {
                stk.push(c);
            }
        }
        return stk.empty();
    }
};
