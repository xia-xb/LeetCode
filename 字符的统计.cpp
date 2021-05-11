/*
 * @Author: your name
 * @Date: 2021-05-11 23:11:21
 * @LastEditTime: 2021-05-11 23:26:28
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\字符的统计.cpp
 */

/* 387题字符串中的第一个唯一字符 */
/* 利用哈希表统计 */
class Solution {
public:
    int firstUniqChar(string s) {
        int res = -1;
        unordered_map<char, int> m;
        for (int i = 0; i < s.size(); i++) {
            m[s[i]]++;
        }
        for (int i = 0; i < s.size(); i++) {
            if (m[s[i]] == 1) {
                res = i;
                break;
            }
        }
        return res;
    }
};

/* 389题找不同 */
/* 哈希表 */
class Solution {
public:
    char findTheDifference(string s, string t) {
        unordered_map<char, int> m;
        for (int i = 0; i < s.size(); i++) {
            m[s[i]]++;
        }
        char res;
        unordered_map<char, int> tmp;
        for (int i = 0; i < t.size(); i++) {
            tmp[t[i]]++;
            if (m.count(t[i]) == 0 || m[t[i]] < tmp[t[i]]) {
                res = t[i];
                break;
            }
        }
        return res;
    }
};