/*
 * @Author: your name
 * @Date: 2021-05-03 20:04:06
 * @LastEditTime: 2021-05-03 20:40:19
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\二维数组的变换.cpp
 */

/* 48题旋转图像 */
/* 旋转90度，相当于先竖直对称，之后斜对角线变换 */
/* 或者，先水平变换，然后沿对角线变换 */
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n / 2; j++) {
                swap(matrix[i][j], matrix[i][n - j - 1]);
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - i; j++) {
                swap(matrix[i][j], matrix[n - j - 1][n - i - 1]);
            }
        }
    }
};
/* 由内而外旋转 */
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int length = matrix.size();
        for (int i = 0; i < length / 2; i++) {
            for (int j = i; j < length - i - 1; j++) {
                int m = length - j - 1, n = length - i - 1;
                int tmp = matrix[i][j];
                matrix[i][j] = matrix[m][i];
                matrix[m][i] = matrix[n][m];
                matrix[n][m] = matrix[j][n];
                matrix[j][n] = tmp;
            }
        }
    }
};
