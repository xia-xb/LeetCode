/*
 * @Author: 夏玄兵
 * @Date: 2021-06-17 21:35:41
 * @LastEditTime: 2021-06-17 23:50:43
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /LeetCode/二分答案法.cpp
 */

/* 378题有序矩阵中第K小的元素 */
/* 二分查找 */
/* 利用矩阵的性质 */
class Solution {
public:
    int countLessN(vector<vector<int>> &matrix, int m, int n, int mid) {
        int i = m - 1, j = 0, sum = 0;
        while (i >= 0 && j < n) {
            if (matrix[i][j] <= mid) {
                sum += i + 1;
                j++;
            } else {
                i--;
            }
        }
        return sum;
    }
    int kthSmallest(vector<vector<int>> &matrix, int k) {
        int m = matrix.size(), n = matrix[0].size();
        int left = matrix[0][0], right = matrix[m - 1][n - 1];
        while (left < right) {
            int mid = left + (right - left) / 2;
            int count = countLessN(matrix, m, n, mid);
            if (count < k) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }
};
