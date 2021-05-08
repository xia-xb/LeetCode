/*
 * @Author: your name
 * @Date: 2021-05-08 22:32:22
 * @LastEditTime: 2021-05-08 23:24:16
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\单词.cpp
 */

/* 434题字符串中的单词数 */
class Solution {
public:
    int countSegments(string s) {
        if (s.size() == 0) {
            return 0;
        }
        int count = 0;
        bool flag = false;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] != ' ') {
                flag = true;
            } else if (flag) {
                count++;
                !flag;
            }
        }
        if (s[s.size() - 1] != ' ') {
            count++;
        }
        return count;
    }
};
/* 若该下标前为空格（或者为初始下标），
且自身不为空格，则其为单词开始的下标 */
class Solution {
public:
    int countSegments(string s) {
        int count = 0;
        for (int i = 0; i < s.size(); i++) {
            if ((i == 0 || s[i - 1] == ' ') && s[i] != ' ') {
                count++;
            }
        }
        return count;
    }
};

/* 58题最后一个单词的长度 */
/* 从第一个不为空开始计数，遇到空或者第二个空跳出 */
class Solution {
public:
    int lengthOfLastWord(string s) {
        int length = 0;
        for (int i = s.size() - 1; i >= 0; i--) {
            if (s[i] == ' ') {
                if (length == 0) {
                    continue;
                } else {
                    break;
                }
            }
            length++;
        }
        return length;
    }
};
