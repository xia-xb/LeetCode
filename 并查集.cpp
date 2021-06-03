/*
 * @Author: your name
 * @Date: 2021-06-03 22:40:05
 * @LastEditTime: 2021-06-03 23:32:30
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\并查集.cpp
 */

/* 547题省份数量 */
/* 并查集 */
/* 遍历时，j可以从i+1开始遍历 */
class Solution {
public:
    int UFfind(int p, vector<int>& index) {
        while (p != index[p]) {
            p = index[p];
        }
        return p;
    }
    int findCircleNum(vector<vector<int>>& isConnected) {
        if (isConnected.empty()) {
            return 0;
        }
        int n = isConnected.size();
        int num = n;
        vector<int> index(n, 0);
        for (int i = 0; i < n; i++) {
            index[i] = i;
        }
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (isConnected[i][j]) {
                    int p = UFfind(i, index), q = UFfind(j, index);
                    if (p != q) {
                        index[p] = q;
                        num--;
                    }
                }
            }
        }
        return num;
    }
};