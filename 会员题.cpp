/*
 * @Author: your name
 * @Date: 2021-08-21 21:25:59
 * @LastEditTime: 2021-08-21 23:25:07
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /LeetCode/会员题.cpp
 */

/* 252 会议室 */
/* 自定义排序 二元谓词 */
/* 根据开始时间升序排序 */
/* 若开始时间小于前一个结束时间则false */
class myCompare {
public:
    bool operator()(vector<int>& v1, vector<int>& v2) { return v1[0] < v2[0]; }
};

class Solution {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), myCompare());
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] < intervals[i - 1][1]) {
                return false;
            }
        }
        return true;
    }
};

/* 253 会议室II */
/* 自定义排序 */
/* 定义数组保存每个会议室最后使用的会议 */
/* 新的会议与每个会议室比较 */
/* 若时间不冲突，则插入，替换在原来位置即可 */
/* 冲突则新建，即push_back */
/* 因为提前排序了，所以不会出现后面的会议在前面两会议间隔时间内的情况 */
class myCompare {
public:
    bool operator()(vector<int>& v1, vector<int>& v2) { return v1[0] < v2[0]; }
};

class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), myCompare());
        vector<vector<int>> res;
        for (int i = 0; i < intervals.size(); i++) {
            if (res.empty()) {
                res.push_back(intervals[i]);
            } else {
                int start = intervals[i][0];
                int j = 0;
                for (; j < res.size(); j++) {
                    if (res[j][1] <= start) {
                        res[j] = intervals[i];
                        break;
                    }
                }
                if (j == res.size()) {
                    res.push_back(intervals[i]);
                }
            }
        }
        return res.size();
    }
};
/* 最小堆存储每个会议室的结束时间 */
class myCompare {
public:
    bool operator()(vector<int>& v1, vector<int>& v2) { return v1[0] < v2[0]; }
};

class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        if (intervals.empty()) {
            return 0;
        }
        sort(intervals.begin(), intervals.end(), myCompare());
        priority_queue<int, vector<int>, greater<int>> que;
        que.push(intervals[0][1]);
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] >= que.top()) {
                que.pop();
            }
            que.push(intervals[i][1]);
        }
        return que.size();
    }
};

/* 159 至多包含两个字符的最长子串 */
/* 滑动窗口 */
class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        int n = s.size();
        if (n <= 2) {
            return n;
        }
        unordered_map<char, int> window;
        int left = 0, right = 0, res = 0;
        while (right < n) {
            window[s[right++]]++;
            while (window.size() > 2) {
                char c = s[left++];
                window[c]--;
                if (window[c] == 0) {
                    window.erase(c);
                }
            }
            res = max(res, right - left);
        }
        return res;
    }
};
