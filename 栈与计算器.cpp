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
/* 代码优化 */
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        for (int i = 0; i < tokens.size(); i++) {
            string& c = tokens[i];
            if (c != "+" && c != "-" && c != "*" && c != "/") {
                st.push(atoi(c.c_str()));
                continue;
            }
            int top1 = st.top();
            st.pop();
            int top2 = st.top();
            st.pop();
            switch (c[0]) {
            case '+':
                st.push(top1 + top2);
                break;
            case '-':
                st.push(top2 - top1);
                break;
            case '*':
                st.push(top2 * top1);
                break;
            case '/':
                st.push(top2 / top1);
                break;
            }
        }
        return st.top();
    }
};

/* 227题基本计算器II */
/* 通过栈存储数值 */
/* 只计算乘除，不计算加减 */
class Solution {
public:
    bool isNum(char c) { return c >= '0' && c <= '9'; }
    int calculate(string s) {
        stack<long> stk;
        char preSign = '+';
        long num = 0;
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (isNum(c)) {
                num = num * 10 + c - '0';
            }
            if (!isNum(c) && c != ' ' || i == s.size() - 1) {
                int newtop;
                switch (preSign) {
                case '+':
                    stk.push(num);
                    break;
                case '-':
                    stk.push(-num);
                    break;
                case '*':
                    newtop = num * stk.top();
                    stk.pop();
                    stk.push(newtop);
                    break;
                case '/':
                    newtop = stk.top() / num;
                    stk.pop();
                    stk.push(newtop);
                    break;
                }
                num = 0;
                preSign = c;
            }
        }
        long sum = 0;
        while (!stk.empty()) {
            sum += stk.top();
            stk.pop();
        }
        return sum;
    }
};