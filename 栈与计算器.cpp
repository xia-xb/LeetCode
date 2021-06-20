/*
 * @Author: your name
 * @Date: 2021-06-20 22:06:32
 * @LastEditTime: 2021-06-20 23:44:15
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /LeetCode/栈与计算器.cpp
 */

/* 150题逆波兰表达式求值 */
/* 通过栈存储值 */
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        for (int i = 0; i < tokens.size(); i++) {
            string c = tokens[i];
            if (c == "+") {
                int top1 = st.top();
                st.pop();
                int newtop = top1 + st.top();
                st.pop();
                st.push(newtop);
            } else if (c == "-") {
                int top1 = st.top();
                st.pop();
                int newtop = st.top() - top1;
                st.pop();
                st.push(newtop);
            } else if (c == "*") {
                int top1 = st.top();
                st.pop();
                int newtop = top1 * st.top();
                st.pop();
                st.push(newtop);
            } else if (c == "/") {
                int top1 = st.top();
                st.pop();
                int newtop = st.top() / top1;
                st.pop();
                st.push(newtop);
            } else {
                st.push(atoi(c.c_str()));
            }
        }
        return st.top();
    }
};