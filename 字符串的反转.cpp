/*
 * @Author: your name
 * @Date: 2021-05-10 22:08:08
 * @LastEditTime: 2021-05-11 23:10:59
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\字符串的反转.cpp
 */

/* 344题反转字符串 */
/* 利用reversse */
class Solution {
public:
    void reverseString(vector<char>& s) { reverse(s.begin(), s.end()); }
};
/* 双指针 */
class Solution {
public:
    void reverseString(vector<char>& s) {
        int i = 0, j = s.size() - 1;
        while (i < j) {
            swap(s[i++], s[j--]);
        }
    }
};

/* 541题反转字符串II */
/* 原地直接反转 */
class Solution {
public:
    void reverseS(string& s, int left, int right) {
        while (left < right && right < s.size()) {
            swap(s[left++], s[right--]);
        }
    }
    string reverseStr(string s, int k) {
        int position = 0, length = s.size();
        for (; position < length; position += 2 * k) {
            int left = position, right = min(position + k - 1, length - 1);
            reverseS(s, left, right);
        }
        return s;
    }
};

/* 557题反转字符串中的单词III */
/* 直接反转 */
class Solution {
public:
    void reverseW(string& s, int left, int right) {
        right--;
        while (left < right && right < s.size()) {
            swap(s[left++], s[right--]);
        }
    }
    string reverseWords(string s) {
        int start = 0, end = 0, length = s.size();
        while (end < length) {
            while (start < length && s[start] == ' ') {
                start++;
            }
            end = start;
            while (end < length && s[end] != ' ') {
                end++;
            }
            reverseW(s, start, end);
            start = end;
        }
        return s;
    }
};

/* 151题翻转字符串里的单词 */
/* 直接翻转从后向前遍历 */
class Solution {
public:
    string reverseWords(string s) {
        string res;
        for (int position = s.size() - 1; position >= 0; position--) {
            while (position >= 0 && s[position] == ' ') {
                position--;
            }
            int start = position - 1;
            while (start >= 0 && s[start] != ' ') {
                start--;
            }
            start++;
            if (start < 0) {
                break;
            }
            if (!res.empty()) {
                res += ' ';
            }
            res += s.substr(start, position - start + 1);
            position = start;
        }
        return res;
    }
};