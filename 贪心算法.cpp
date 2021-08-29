/*
 * @Author: your name
 * @Date: 2021-08-29 22:13:25
 * @LastEditTime: 2021-08-29 23:18:08
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /LeetCode/贪心算法.cpp
 */

/* 435 无重叠区间 */
/* 贪心算法 */
/* 区间调度问题 */
class mycompare {
public:
    bool operator()(vector<int>& a, vector<int>& b) { return a[1] < b[1]; }
};

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) {
            return 0;
        }
        int n = intervals.size();
        sort(intervals.begin(), intervals.end(), mycompare());
        int count = 1;
        int x_end = intervals[0][1];
        for (int i = 0; i < n; i++) {
            int start = intervals[i][0];
            if (start >= x_end) {
                count++;
                x_end = intervals[i][1];
            }
        }
        return n - count;
    }
};
/* 动态规划，超出时间限制 */
/* dp[i] 以区间i为结尾的最多不重叠区间数 */
class mycompare {
public:
    bool operator()(vector<int>& a, vector<int>& b) { return a[0] < b[0]; }
};

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) {
            return 0;
        }
        int n = intervals.size();
        sort(intervals.begin(), intervals.end(), mycompare());
        vector<int> dp(n, 1);
        int count = 1;
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (intervals[j][1] <= intervals[i][0]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                    count = max(count, dp[i]);
                }
            }
        }
        return n - count;
    }
};

/* 452 用最少数量的箭引爆气球 */
/* 贪心算法 */
/* 实质是求最多不重叠区间 */
class mycompare {
public:
    bool operator()(const vector<int>& a, const vector<int>& b) {
        return a[1] < b[1];
    }
};
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.empty()) {
            return 0;
        }
        sort(points.begin(), points.end(), mycompare());
        int count = 1;
        int x_end = points[0][1];
        for (int i = 1; i < points.size(); i++) {
            int start = points[i][0];
            if (start > x_end) {
                count++;
                x_end = points[i][1];
            }
        }
        return count;
    }
};
