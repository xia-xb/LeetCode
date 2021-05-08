/*
 * @Author: your name
 * @Date: 2021-05-04 21:22:10
 * @LastEditTime: 2021-05-04 22:21:56
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\字符.cpp
 */

/* 520题检测大写字母 */
/* 直接根据定义判断 */
public:
bool isGreat(char c) { return c >= 65 && c <= 90; }
bool detectCapitalUse(string word) {
    if (word.size() == 0 || word.size() == 1) {
        return true;
    }
    bool res = true;
    if (isGreat(word[0])) {
        if (isGreat(word[1])) {
            for (int i = 2; i < word.size(); i++) {
                if (!isGreat(word[i])) {
                    res = false;
                    break;
                }
            }
        } else {
            for (int i = 2; i < word.size(); i++) {
                if (isGreat(word[i])) {
                    res = false;
                    break;
                }
            }
        }
    } else {
        for (int i = 1; i < word.size(); i++) {
            if (isGreat(word[i])) {
                res = false;
                break;
            }
        }
    }
    return res;
}
}
;
/* 统计大写字母个数 */
class Solution {
public:
    bool isGreat(char c) { return c >= 65 && c <= 90; }
    bool detectCapitalUse(string word) {
        int count = 0, length = word.size();
        for (int i = 0; i < word.size(); i++) {
            if (isGreat(word[i])) {
                count++;
            }
        }
        if (count == 0 || count == length || (count == 1 && isGreat(word[0]))) {
            return true;
        }
        return false;
    }
};
