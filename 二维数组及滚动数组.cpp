/*
 * @Author: your name
 * @Date: 2021-04-29 21:39:51
 * @LastEditTime: 2021-05-03 14:42:29
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\二维数组及滚动数组.cpp
 */


/* 118题杨辉三角 */
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>>res;
        if(numRows==0){return res;}
        for(int i=0;i<numRows;i++){
            if(i==0){res.push_back({1});continue;}
            vector<int>vec={1};
            for(int j=0;j<res[i-1].size()-1;j++){
                vec.push_back(res[i-1][j]+res[i-1][j+1]);
            }
            vec.push_back(1);
            res.push_back(vec);
        }
        return res;
    }
};
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>>res;
        res.resize(numRows);
        for(int i=0;i<numRows;i++){
            res[i].resize(i+1);
            res[i][0]=res[i][i]=1;
            for(int j=1;j<i;j++){
                res[i][j]=res[i-1][j-1]+res[i-1][j];
            }
        }
        return res;
    }
};


/* 119题杨辉三角2 */
/* 根据组合的性质 */
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int>res;
        res.resize(rowIndex+1);
        res[0]=res[rowIndex]=1;
        for(int i=1;i<=rowIndex/2;i++){
            res[i]=res[rowIndex-i]=1LL*res[i-1]*(rowIndex-i+1)/i;
        }
        return res;
    }
};
