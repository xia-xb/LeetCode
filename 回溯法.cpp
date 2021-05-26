/*
 * @Author: your name
 * @Date: 2021-05-22 22:09:13
 * @LastEditTime: 2021-05-26 23:56:34
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\回溯法.cpp
 */

/* 51题N皇后 */
/* 回溯法 */
class Solution {
public:
    vector<vector<string>> res;
    bool isvaild(vector<string>& board, int row, int col) {
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 'Q') {
                return false;
            }
        }
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }
        for (int i = row - 1, j = col + 1; i >= 0 && j < board.size();
             i--, j++) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }
        return true;
    }
    void trackback(vector<string>& board, int row) {
        if (row == board.size()) {
            res.push_back(board);
            return;
        }
        for (int i = 0; i < board[row].size(); i++) {
            if (!isvaild(board, row, i)) {
                continue;
            }
            board[row][i] = 'Q';
            trackback(board, row + 1);
            board[row][i] = '.';
        }
        return;
    }
    vector<vector<string>> solveNQueens(int n) {
        vector<string> board(n, string(n, '.'));
        trackback(board, 0);
        return res;
    }
};
/* 对于判断函数，可以通过设置三个哈希表来快速判断 */
class Solution {
public:
    vector<vector<string>> res;
    unordered_set<int> columns;
    unordered_set<int> diagonals1, diagonals2;
    bool isvaild(vector<string>& board, int row, int col) {
        return !(columns.count(col) || diagonals1.count(row + col) ||
                 diagonals2.count(row - col));
    }
    void trackback(vector<string>& board, int row) {
        if (row == board.size()) {
            res.push_back(board);
            return;
        }
        for (int i = 0; i < board[row].size(); i++) {
            if (!isvaild(board, row, i)) {
                continue;
            }
            board[row][i] = 'Q';
            columns.insert(i);
            diagonals1.insert(row + i);
            diagonals2.insert(row - i);
            trackback(board, row + 1);
            board[row][i] = '.';
            columns.erase(i);
            diagonals1.erase(row + i);
            diagonals2.erase(row - i);
        }
        return;
    }
    vector<vector<string>> solveNQueens(int n) {
        vector<string> board(n, string(n, '.'));
        trackback(board, 0);
        return res;
    }
};

/* 52题N皇后II */
/* 与51题相类似 */
/* 回溯法，注意判断位置是否可以放置函数的编写 */
class Solution {
public:
    int count = 0;
    bool isvaild(vector<string>& board, int row, int col) {
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 'q') {
                return false;
            }
        }
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'q') {
                return false;
            }
        }
        for (int i = row - 1, j = col + 1; i >= 0 && j < board.size();
             i--, j++) {
            if (board[i][j] == 'q') {
                return false;
            }
        }
        return true;
    }
    void trackback(vector<string>& board, int row) {
        if (row == board.size()) {
            count++;
            return;
        }
        for (int i = 0; i < board[row].size(); i++) {
            if (!isvaild(board, row, i)) {
                continue;
            }
            board[row][i] = 'q';
            trackback(board, row + 1);
            board[row][i] = '.';
        }
    }
    int totalNQueens(int n) {
        vector<string> board(n, string(n, '.'));
        trackback(board, 0);
        return count;
    }
};

/* 526题优美排列 */
/* 回溯法，注意判断整数是否已经使用 */
/* 除了使用哈希表，还由于候选数是确定的 */
/* 可以考虑数组，从而减少内存 */
class Solution {
public:
    int count = 0;
    void trackback(int n, vector<bool>& visited, int index) {
        if (index > n) {
            count++;
            return;
        }
        for (int i = 1; i <= n; i++) {
            if (visited[i]) {
                continue;
            }
            if (i % index == 0 || index % i == 0) {
                visited[i] = true;
                trackback(n, visited, index + 1);
                visited[i] = false;
            }
        }
    }
    int countArrangement(int n) {
        vector<bool> visited(n, false);
        trackback(n, visited, 1);
        return count;
    }
};


/* 39题组合总和 */
/* 回溯法 */
/* 注意先将数组candidates排序，当和大于target时 */
/* 该组合不会再满足，直接去除 */
/* 实际情况是，不排序也可以😒😒😒😒 */
class Solution {
public:
    vector<vector<int>> res;
    void trackback(vector<int>& candidates, int target,
                   vector<int>& combination, int sum, int position) {
        if (sum == target) {
            res.push_back(combination);
            return;
        } else if (sum > target) {
            return;
        }
        for (int i = position; i < candidates.size(); i++) {
            combination.push_back(candidates[i]);
            trackback(candidates, target, combination, sum + candidates[i], i);
            combination.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<int> combination;
        trackback(candidates, target, combination, 0, 0);
        return res;
    }
};
/* 对上面代码优化 */
/* 不使用参数sum，直接利用target */
/* target=0即为满足，且注意是值传递，不是引用传递 */
/* 所以在递归前后，不用对target做改变，直接参数改变 */
class Solution {
public:
    vector<vector<int>> res;
    void trackback(vector<int>& candidates, int target,
                   vector<int>& combination, int position) {
        if (target == 0) {
            res.push_back(combination);
            return;
        } else if (target < 0) {
            return;
        }
        for (int i = position; i < candidates.size(); i++) {
            combination.push_back(candidates[i]);
            trackback(candidates, target - candidates[i], combination, i);
            combination.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> combination;
        trackback(candidates, target, combination, 0);
        return res;
    }
};
/* 剪枝 */
/* 首先对将数组candidates排序 */
/* 当target-candidites[position]<0时 */
/* 由于排序，后面的选择中其值也小于0，不用循环 */
class Solution {
public:
    vector<vector<int>> res;
    void trackback(vector<int>& candidates, int target,
                   vector<int>& combination, int position) {
        if (target == 0) {
            res.push_back(combination);
            return;
        } else if (target < 0) {
            return;
        }
        for (int i = position; i < candidates.size(); i++) {
            combination.push_back(candidates[i]);
            trackback(candidates, target - candidates[i], combination, i);
            combination.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> combination;
        trackback(candidates, target, combination, 0);
        return res;
    }
};


/* 40题组合总和II */
/* 回溯法 */
/* 与39题不同的是，每个元素只能使用1次 */
/* 同时去除重复组合 */
/* 注意，在for循环中对应的元素位于决策树的同一层 */
/* 去除重复组合，只要同一层中，相同元素只出现一次即可 */
class Solution {
public:
    vector<vector<int>> res;
    void trackback(vector<int>& candidates, int target, vector<int> combination,
                   int index) {
        if (target == 0) {
            res.push_back(combination);
            return;
        } else if (target < 0) {
            return;
        }
        for (int i = index;
             i < candidates.size() && target - candidates[i] >= 0; i++) {
            if (i > index && candidates[i] == candidates[i - 1]) {
                continue;
            }
            combination.push_back(candidates[i]);
            trackback(candidates, target - candidates[i], combination, i + 1);
            combination.pop_back();
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<int> combination;
        trackback(candidates, target, combination, 0);
        return res;
    }
};


/* 46题全排列 */
/* 回溯法，注意由于是排列 */
/* 通过设置数组visited判断元素是否使用 */
class Solution {
public:
    vector<vector<int>> res;
    void trackback(vector<int>& nums, vector<int>& arrangement,
                   vector<bool>& visited) {
        if (arrangement.size() == nums.size()) {
            res.push_back(arrangement);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (visited[i]) {
                continue;
            }
            arrangement.push_back(nums[i]);
            visited[i] = true;
            trackback(nums, arrangement, visited);
            arrangement.pop_back();
            visited[i] = false;
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<bool> visited(nums.size(), false);
        vector<int> arrangement;
        trackback(nums, arrangement, visited);
        return res;
    }
};
/* 直接在原数组上交换元素，实现排列 */
class Solution {
public:
    vector<vector<int>> res;
    void trackback(vector<int>& nums, int index) {
        if (index == nums.size()) {
            res.push_back(nums);
            return;
        }
        for (int i = index; i < nums.size(); i++) {
            swap(nums[index], nums[i]);
            trackback(nums, index + 1);
            swap(nums[index], nums[i]);
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        trackback(nums, 0);
        return res;
    }
};


/* 47题全排列II */
/* 回溯法，直接在原数组上交换，实现排列 */
/* 需要注意的是，包含重复数字，去除重复排列时 */
/* 不能简单通过排序，之后跳过相邻相等的元素 */
/* 原因是由于原数组上交换，会改变其有序状态 */
/* 通过哈希表即可 */
class Solution {
public:
    vector<vector<int>> res;
    void trackback(vector<int>& nums, int index) {
        if (index == nums.size()) {
            res.push_back(nums);
            return;
        }
        unordered_set<int> st;
        for (int i = index; i < nums.size(); i++) {
            if (st.count(nums[i])) {
                continue;
            }
            st.insert(nums[i]);
            swap(nums[i], nums[index]);
            trackback(nums, index + 1);
            swap(nums[i], nums[index]);
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        trackback(nums, 0);
        return res;
    }
};
/* 避免上面方法中需要哈希表 */
/* 直接新建新数组保存排列 */
/* 同时设置visited数组记录是否使用 */
public:
vector<vector<int>> res;
void trackback(vector<int>& nums, vector<int>& arrangement,
               vector<bool> visited) {
    if (arrangement.size() == nums.size()) {
        res.push_back(arrangement);
        return;
    }
    for (int i = 0; i < nums.size(); i++) {
        if (visited[i] ||
            (i > 0 && nums[i] == nums[i - 1] && !visited[i - 1])) {
            continue;
        }
        visited[i] = true;
        arrangement.push_back(nums[i]);
        trackback(nums, arrangement, visited);
        arrangement.pop_back();
        visited[i] = false;
    }
}
vector<vector<int>> permuteUnique(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<bool> visited(nums.size(), false);
    vector<int> arrangement;
    trackback(nums, arrangement, visited);
    return res;
};


/* 77题组合 */
/* 回溯法，注意剪枝条件的推导 */
class Solution {
public:
    vector<vector<int>>res;
    void track(int n,int k,vector<int>& path,int index){
        if(path.size()==k){
            res.push_back(path);
            return;
        }
        for(int i=index;i<=n+path.size()-k+1;i++){
            path.push_back(i);
            track(n,k,path,i+1);
            path.pop_back();
        }

    }
    vector<vector<int>> combine(int n, int k) {
        vector<int>path;
        track(n,k,path,1);
        return res;
    }
};


/* 78题子集 */
/* 回溯法 */
class Solution {
public:
    vector<vector<int>>res;
    void trackback(vector<int>& nums, vector<int>& path,int index){
        res.push_back(path);
        if(index==nums.size()){return;}
        for(int i=index;i<nums.size();i++){
            path.push_back(nums[i]);
            trackback(nums,path,i+1);
            path.pop_back();
        }
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int>path;
        trackback(nums,path,0);
        return res;
    }
};


/* 90题子集II */
/* 回溯法，注意同一层循环中同意元素只使用一次 */
class Solution {
public:
    vector<vector<int>>res;
    void trackback(vector<int>& nums,vector<int>& path, int index){
        res.push_back(path);
        if(index==nums.size()){return;}
        for(int i=index;i<nums.size();i++){
            if(i>index && nums[i]==nums[i-1]){continue;}
            path.push_back(nums[i]);
            trackback(nums,path,i+1);
            path.pop_back();
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<int>path;
        trackback(nums,path,0);
        return res;
    }
};


/* 单词搜索 */
/* 回溯法 */
class Solution {
public:
    bool res=false;
    void trackback(vector<vector<char>>& board,vector<vector<int>>& visited,string word,int length,int row,int col){
        if(length==word.size()){
            res=true;
            return;
        }
        if(row-1>=0 && visited[row-1][col]==0 && board[row-1][col]==word[length]){
            visited[row-1][col]=1;
            trackback(board,visited,word,length+1,row-1,col);
            visited[row-1][col]=0;
        }
        if(res){return;}
        if(row+1<board.size() && visited[row+1][col]==0 && board[row+1][col]==word[length]){
            visited[row+1][col]=1;
            trackback(board,visited,word,length+1,row+1,col);
            visited[row+1][col]=0;
        }
        if(res){return;}
        if(col-1>=0 && visited[row][col-1]==0 && board[row][col-1]==word[length]){
            visited[row][col-1]=1;
            trackback(board,visited,word,length+1,row,col-1);
            visited[row][col-1]=0;
        }
        if(res){return;}
        if(col+1<board[row].size() && visited[row][col+1]==0 && board[row][col+1]==word[length]){
            visited[row][col+1]=1;
            trackback(board,visited,word,length+1,row,col+1);
            visited[row][col+1]=0;
        }
    }
    bool exist(vector<vector<char>>& board, string word) {
        if(board.empty()){return false;}
        vector<vector<int>>visited(board.size(),vector<int>(board[0].size(),0));
        for(int row=0;row<board.size();row++){
            for(int col=0;col<board[row].size();col++){
                if(board[row][col]==word[0]){
                    visited[row][col]=1;
                    trackback(board,visited,word,1,row,col);
                    visited[row][col]=0;
                }
                if(res){break;}
            }
            if(res){break;}
        }
        return res;        

    }
};