/*
 * @Author: your name
 * @Date: 2021-05-21 23:29:30
 * @LastEditTime: 2021-05-21 23:50:15
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\深度优先搜索.cpp
 */

/* 17题电话号码的字母组合 */
/* dfs */
class Solution {
public:
    vector<string> res;
    string begin = "_!adgjmptw";
    void dfs(string& digits, string s, int index) {
        if (index >= digits.size()) {
            res.push_back(s);
            return;
        }
        int n = digits[index] - '0';
        if (n == 7 || n == 9) {
            for (int i = 0; i < 4; i++) {
                char c = begin[n] + i;
                dfs(digits, s + c, index + 1);
            }
        } else {
            for (int i = 0; i < 3; i++) {
                char c = begin[n] + i;
                dfs(digits, s + c, index + 1);
            }
        }
    }
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) {
            return {};
        }
        dfs(digits, "", 0);
        return res;
    }
};
/* 优化 */
class Solution {
public:
    vector<string> res;
    vector<string> board = {"",    "",    "abc",  "def", "ghi",
                            "jkl", "mno", "pqrs", "tuv", "wxyz"};
    void dfs(string& digits, string& s, int index) {
        if (index >= digits.size()) {
            res.push_back(s);
            return;
        }
        int n = digits[index] - '0';
        for (int i = 0; i < board[n].size(); i++) {
            s.push_back(board[n][i]);
            dfs(digits, s, index + 1);
            s.pop_back();
        }
    }
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) {
            return {};
        }
        string s;
        dfs(digits, s, 0);
        return res;
    }
};
