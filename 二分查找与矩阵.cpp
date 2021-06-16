/*
 * @Author: 夏玄兵
 * @Date: 2021-06-16 21:52:07
 * @LastEditTime: 2021-06-16 23:27:41
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /LeetCode/二分查找与矩阵.cpp
 */

/* 74题搜索二维矩阵 */
/* 二分查找 */
/* 分别通过两次二分查找确定行，列 */
/* 需要注意的是查找行时要找到最接近且小于目标值的行 */
/* 列搜索和普通二分查找一样 */
class Solution {
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target) {
        int lowRol = 0, highRol = matrix.size() - 1;
        while (lowRol <= highRol) {
            int mid = lowRol + (highRol - lowRol) / 2;
            if (matrix[mid][0] == target) {
                return true;
            } else if (matrix[mid][0] < target) {
                lowRol = mid + 1;
            } else {
                highRol = mid - 1;
            }
        }
        if (highRol < 0 || matrix[highRol][0] > target) {
            return false;
        } else {
            int left = 0, right = matrix[highRol].size() - 1;
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (matrix[highRol][mid] == target) {
                    return true;
                } else if (matrix[highRol][mid] < target) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        return false;
    }
};
/* 将二维数组所有行拼起来看作是一个数组 */
/* 之后就是普通二分查找 */
/* 值得关注的是通过mid推断出对应的行/列 */
class Solution {
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        int left = 0, right = m * n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int midValue = matrix[mid / n][mid % n];
            if (midValue == target) {
                return true;
            } else if (midValue < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return false;
    }
};

/* 240题搜索二维数组II */
/* 通过两次二分查找找到小于目标值的行、列 */
/* 在行、列范围内查找 */
/* 注意每行遍历时，先通过最后一个元素判断，来进行减枝 */
class Solution {
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target) {
        int lowCol = 0, highCol = matrix.size() - 1;
        while (lowCol <= highCol) {
            int mid = lowCol + (highCol - lowCol) / 2;
            if (matrix[mid][0] == target) {
                return true;
            } else if (matrix[mid][0] < target) {
                lowCol = mid + 1;
            } else {
                highCol = mid - 1;
            }
        }
        if (highCol < 0) {
            return false;
        }
        int lowROw = 0, highRow = matrix[0].size() - 1;
        while (lowROw <= highRow) {
            int mid = lowROw + (highRow - lowROw) / 2;
            if (matrix[0][mid] == target) {
                return true;
            } else if (matrix[0][mid] < target) {
                lowROw = mid + 1;
            } else {
                highRow = mid - 1;
            }
        }
        if (highRow < 0) {
            return false;
        }
        for (int i = 0; i <= highCol; i++) {
            if (matrix[i][highRow] < target) {
                continue;
            }
            for (int j = 0; j <= highRow; j++) {
                if (matrix[i][j] == target) {
                    return true;
                }
            }
        }
        return false;
    }
};
/* 直接搜索，从左下角或者右上角开始搜索 */
/* 注意必须从左下角或右上角开始搜索 */
/* 因为需要保证为行最大、列最小或者 */
/* 行最小、列最大 */
/* 否则不能利用矩阵的性质 */
class Solution {
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target) {
        int row = matrix.size() - 1, col = 0;
        while (row >= 0 && col < matrix[0].size()) {
            if (matrix[row][col] == target) {
                return true;
            } else if (matrix[row][col] < target) {
                col++;
            } else {
                row--;
            }
        }
        return false;
    }
};