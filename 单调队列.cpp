/*
 * @Author: your name
 * @Date: 2021-08-30 19:00:07
 * @LastEditTime: 2021-08-30 19:15:40
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /LeetCode/单调队列.cpp
 */

/* 239 滑动窗口最大值 */
/* 单调队列 */
class monotonicQueue {
private:
    deque<int> data;

public:
    void push(int n) {
        while (!data.empty() && data.back() < n) {
            data.pop_back();
        }
        data.push_back(n);
    }
    int max() { return data.front(); }
    void pop(int n) {
        if (!data.empty() && data.front() == n) {
            data.pop_front();
        }
    }
};
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        monotonicQueue window;
        vector<int> res;
        for (int i = 0; i < nums.size(); i++) {
            if (i < k - 1) {
                window.push(nums[i]);
            } else {
                window.push(nums[i]);
                res.push_back(window.max());
                window.pop(nums[i - k + 1]);
            }
        }
        return res;
    }
};
/* 优先队列 */
/* 存储元素值及对应下标 */
/* 取最大值时判断是否在窗口内 */
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        priority_queue<pair<int, int>> que;
        vector<int> res;
        for (int i = 0; i < nums.size(); i++) {
            if (i < k - 1) {
                que.push({nums[i], i});
            } else {
                que.push({nums[i], i});
                while (que.top().second <= i - k) {
                    que.pop();
                }
                res.push_back(que.top().first);
            }
        }
        return res;
    }
};