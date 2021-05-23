/*
 * @Author: your name
 * @Date: 2021-05-22 22:09:13
 * @LastEditTime: 2021-05-23 22:17:38
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
