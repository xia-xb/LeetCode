/*
 * @Author: your name
 * @Date: 2021-08-30 10:53:21
 * @LastEditTime: 2021-08-30 15:41:17
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /LeetCode/数组排序.cpp
 */

/* 56 合并区间 */
/* 以开始时间升序排列 */
class mycompare {
public:
    bool operator()(const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];
    }
};
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> res;
        if (intervals.empty()) {
            return res;
        }
        sort(intervals.begin(), intervals.end(), mycompare());
        int n = intervals.size();
        for (int i = 0; i < n; i++) {
            int start = intervals[i][0], end = intervals[i][1];
            if (res.empty() || start > res.back()[1]) {
                res.push_back({start, end});
            } else {
                res.back()[1] = max(res.back()[1], end);
            }
        }
        return res;
    }
};

/* 57 插入区间 */
/* 先插入区间，排序，在合并区间 */
class mycompare {
public:
    bool operator()(const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];
    }
};
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals,
                               vector<int>& newInterval) {
        intervals.push_back(newInterval);
        sort(intervals.begin(), intervals.end(), mycompare());
        vector<vector<int>> res;
        for (int i = 0; i < intervals.size(); i++) {
            int start = intervals[i][0], end = intervals[i][1];
            if (res.empty() || start > res.back()[1]) {
                res.push_back({start, end});
            } else {
                res.back()[1] = max(res.back()[1], end);
            }
        }
        return res;
    }
};
/* 一次遍历，判断是否相交 */
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals,
                               vector<int>& newInterval) {
        int start = newInterval[0], end = newInterval[1];
        vector<vector<int>> res;
        bool flag = false;
        for (vector<int> it : intervals) {
            if (it[0] > end) {
                if (!flag) {
                    flag = true;
                    res.push_back({start, end});
                }
                res.push_back(it);
            } else if (it[1] < start) {
                res.push_back(it);
            } else {
                start = min(start, it[0]);
                end = max(end, it[1]);
            }
        }
        if (!flag) {
            res.push_back({start, end});
        }
        return res;
    }
};
