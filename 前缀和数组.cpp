/*
 * @Author: your name
 * @Date: 2021-05-03 16:10:49
 * @LastEditTime: 2021-08-26 23:09:11
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\区域和检索-数组不可变.cpp
 */

/* 303题区域和检索-数组不可变 */
class NumArray {
public:
    vector<int> num;
    NumArray(vector<int>& nums) { num = nums; }

    int sumRange(int left, int right) {
        int sum = 0;
        for (int i = left; i <= right && i < num.size(); i++) {
            sum += num[i];
        }
        return sum;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */
/* 前缀和 */
class NumArray {
public:
    vector<int> sum;
    NumArray(vector<int>& nums) {
        sum.resize(nums.size());
        for (int i = 0; i < sum.size(); i++) {
            if (i == 0) {
                sum[i] = nums[i];
            } else {
                sum[i] = sum[i - 1] + nums[i];
            }
        }
    }

    int sumRange(int left, int right) {
        if (left == 0) return sum[right];
        return sum[right] - sum[left - 1];
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */
/* 前缀和模板 */
class NumArray {
public:
    vector<int> sum;
    NumArray(vector<int>& nums) {
        sum.resize(nums.size() + 1);
        sum[0] = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum[i + 1] = sum[i] + nums[i];
        }
    }

    int sumRange(int left, int right) { return sum[right + 1] - sum[left]; }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */

/* 304题二位区域和检索-矩阵不可变 */
/* 前缀和 */
/* 在对区域进行加减时，需要特别注意范围 */
class NumMatrix {
public:
    vector<vector<int>> sum;
    NumMatrix(vector<vector<int>>& matrix) {
        int row = matrix.size(), col = matrix[0].size();
        sum.resize(row + 1);
        sum[0].resize(col + 1);
        for (int i = 0; i < row; i++) {
            sum[i + 1].resize(col + 1);
            for (int j = 0; j < col; j++) {
                sum[i + 1][j + 1] =
                    sum[i + 1][j] + sum[i][j + 1] - sum[i][j] + matrix[i][j];
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return sum[row2 + 1][col2 + 1] - sum[row2 + 1][col1] -
               sum[row1][col2 + 1] + sum[row1][col1];
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */

/* 238题除自身以外数组的乘积 */
/* 前缀与后缀 */
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> res1, res2, res;
        res.resize(n);
        res1.resize(n);
        res2.resize(n);
        res1[0] = res2[n - 1] = 1;
        for (int i = 1; i < n; i++) {
            res1[i] = res1[i - 1] * nums[i - 1];
        }
        for (int i = n - 2; i >= 0; i--) {
            res2[i] = res2[i + 1] * nums[i + 1];
        }
        for (int i = 0; i < n; i++) {
            res[i] = res1[i] * res2[i];
        }
        return res;
    }
};
/* 将前后缀放到一个数组中进行 */
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> res;
        res.resize(n);
        res[0] = 1;
        for (int i = 1; i < n; i++) {
            res[i] = res[i - 1] * nums[i - 1];
        }
        int r = 1;  //注意该变量记录后缀
        for (int i = n - 1; i >= 0; i--) {
            res[i] *= r;
            r *= nums[i];
        }
        return res;
    }
};

/* 面试题17 24 最大子矩阵 */
/* 前缀和 */
/* 化二维为一维 */
class Solution {
public:
    vector<int> getMaxMatrix(vector<vector<int>>& matrix) {
        vector<int> res(4);
        int n = matrix.size(), m = matrix[0].size();
        vector<int> b(m, 0);
        int sum;
        int maxSum = INT_MIN;
        int bestr1, bestc1;
        for (int i = 0; i < n; i++) {
            for (int t = 0; t < m; t++) {
                b[t] = 0;
            }
            for (int j = i; j < n; j++) {
                sum = 0;
                for (int k = 0; k < m; k++) {
                    b[k] += matrix[j][k];

                    if (sum > 0) {
                        sum += b[k];
                    } else {
                        sum = b[k];
                        bestc1 = i;
                        bestr1 = k;
                    }
                    if (sum > maxSum) {
                        maxSum = sum;
                        res[0] = bestc1;
                        res[1] = bestr1;
                        res[2] = j;
                        res[3] = k;
                    }
                }
            }
        }
        return res;
    }
};