/*
 * @Author: 夏玄兵
 * @Date: 2021-06-18 21:59:09
 * @LastEditTime: 2021-06-20 14:45:03
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /LeetCode/用栈访问最后若干元素.cpp
 */

/* 682题 */
/* 定义一个栈，存储所有得分 */
class Solution {
public:
    int calPoints(vector<string>& ops) {
        stack<int> st;
        for (int i = 0; i < ops.size(); i++) {
            string s = ops[i];
            if (s == "+") {
                int top1 = st.top();
                st.pop();
                int top2 = st.top();
                st.push(top1);
                st.push(top1 + top2);
            } else if (s == "D") {
                st.push(2 * st.top());
            } else if (s == "C") {
                st.pop();
            } else {
                st.push(atoi(s.c_str()));
            }
        }
        int sum = 0;
        while (!st.empty()) {
            sum += st.top();
            st.pop();
        }
        return sum;
    }
};
/* 代码简单优化 */
class Solution {
public:
    int calPoints(vector<string>& ops) {
        stack<int> st;
        for (int i = 0; i < ops.size(); i++) {
            string s = ops[i];
            if (s == "+") {
                int top1 = st.top();
                st.pop();
                int newtop = top1 + st.top();
                st.push(top1);
                st.push(newtop);
            } else if (s == "D") {
                st.push(2 * st.top());
            } else if (s == "C") {
                st.pop();
            } else {
                st.push(atoi(s.c_str()));
            }
        }
        int sum = 0;
        while (!st.empty()) {
            sum += st.top();
            st.pop();
        }
        return sum;
    }
};



