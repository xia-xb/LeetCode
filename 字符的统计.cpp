/*
 * @Author: your name
 * @Date: 2021-05-11 23:11:21
 * @LastEditTime: 2021-05-12 22:20:25
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

/* 242题有效的字母异位词 */
/* 通过数组记录字符个数 */
class Solution {
public:
    bool isAnagram(string s, string t) {
        vector<int> countS(26, 0), countT(26, 0);
        for (int i = 0; i < s.size(); i++) {
            countS[s[i] - 'a']++;
        }
        for (int i = 0; i < t.size(); i++) {
            countT[t[i] - 'a']++;
        }
        for (int i = 0; i < 26; i++) {
            if (countS[i] != countT[i]) {
                return false;
            }
        }
        return true;
    }
};

/* 49题字母异位词分组 */
/* 排序，哈希表统计 */
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> mp;
        for (int i = 0; i < strs.size(); i++) {
            string str = strs[i];
            sort(str.begin(), str.end());
            mp[str].push_back(strs[i]);
        }
        vector<vector<string>> res;
        for (unordered_map<string, vector<string>>::iterator it = mp.begin();
             it != mp.end(); it++) {
            res.push_back(it->second);
        }
        return res;
    }
};