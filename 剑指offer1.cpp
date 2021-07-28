/*
 * @Author: 夏玄兵
 * @Date: 2021-07-23 23:19:42
 * @LastEditors: 夏玄兵
 * @LastEditTime: 2021-07-28 23:28:52
 * @Description: file content
 * @FilePath: \LeetCode\剑指offer1.cpp
 */

/* 03数组中重复的数字 */
/* 哈希表set */
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        unordered_set<int> st;
        for (int i = 0; i < nums.size(); i++) {
            if (st.count(nums[i])) {
                return nums[i];
            } else {
                st.insert(nums[i]);
            }
        }
        return -1;
    }
};
/* 数组构成哈希表 */
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        vector<int> vec(nums.size(), 0);
        for (int i = 0; i < nums.size(); i++) {
            if (vec[nums[i]]) {
                return nums[i];
            } else {
                vec[nums[i]] = 1;
            }
        }
        return -1;
    }
};

/* 04二维数组中的查找 */
/* 从数组左下角开始查找 */
/* 小于目标值，列自增 */
/* 大于目标值，行自减 */
class Solution {
public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        if (matrix.empty()) {
            return false;
        }
        int n = matrix.size(), m = matrix[0].size();
        int row = n - 1, col = 0;
        while (row >= 0 && col < m) {
            int value = matrix[row][col];
            if (value == target) {
                return true;
            } else if (value > target) {
                row--;
            } else {
                col++;
            }
        }
        return false;
    }
};

/* 5替换空格 */
/* string方法replace */
class Solution {
public:
    string replaceSpace(string s) {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == ' ') {
                s.replace(i, 1, "%20");
            }
        }
        return s;
    }
};

/* 6从尾到头打印链表 */
/* 遍历链表，反转vector */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        vector<int> res;
        while (head != NULL) {
            res.push_back(head->val);
            head = head->next;
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

/* 9重建二叉树 */
/* 关键是寻找中序遍历中的根结点 */
/* 由此区分左右子树 */
/* 递归重建即可 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* buildChildTree(vector<int>& preorder, vector<int>& inorder,
                             int startPre, int startIn, int endIn) {
        if (startIn > endIn) {
            return NULL;
        }
        TreeNode* root = new TreeNode(preorder[startPre]);
        int rootVal = preorder[startPre];
        int rootIndex = startIn;
        for (; rootIndex <= endIn; rootIndex++) {
            if (inorder[rootIndex] == rootVal) {
                break;
            }
        }
        root->left = buildChildTree(preorder, inorder, startPre + 1, startIn,
                                    rootIndex - 1);
        root->right = buildChildTree(preorder, inorder,
                                     startPre + 1 + rootIndex - startIn,
                                     rootIndex + 1, endIn);
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return buildChildTree(preorder, inorder, 0, 0, inorder.size() - 1);
    }
};

/* 9用两个栈实现队列 */
/* 先压入第一个栈 */
/* 输出时再从第一个栈弹出压入第二个栈 */
/* 从而输出顺序对应队列 */
class CQueue {
private:
    stack<int> stk1, stk2;

public:
    CQueue() {}

    void appendTail(int value) { stk1.push(value); }

    int deleteHead() {
        if (stk1.empty() && stk2.empty()) {
            return -1;
        }
        if (stk2.empty()) {
            while (!stk1.empty()) {
                stk2.push(stk1.top());
                stk1.pop();
            }
        }
        int res = stk2.top();
        stk2.pop();
        return res;
    }
};

/**
 * Your CQueue object will be instantiated and called as such:
 * CQueue* obj = new CQueue();
 * obj->appendTail(value);
 * int param_2 = obj->deleteHead();
 */

/* 10II-青蛙跳台阶问题 */
/* 动态规划 */
class Solution {
public:
    int numWays(int n) {
        if (n <= 1) {
            return 1;
        }
        int base = pow(10, 9) + 7;
        int pre = 1, cur = 1;
        for (int i = 2; i <= n; i++) {
            int temp = cur;
            cur = (pre + cur) % base;
            pre = temp;
        }
        return cur;
    }
};

/* 10I-斐波那契数列 */
/* 动态规划 */
class Solution {
public:
    int fib(int n) {
        if (n < 2) {
            return n;
        }
        int base = pow(10, 9) + 7;
        vector<int> dp(n + 1);
        dp[0] = 0;
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            dp[i] = (dp[i - 1] + dp[i - 2]) % base;
        }
        return dp.back();
    }
};
/* 内存优化 */
class Solution {
public:
    int fib(int n) {
        if (n < 2) {
            return n;
        }
        int base = pow(10, 9) + 7;
        int pre = 0, cur = 1;
        for (int i = 2; i <= n; i++) {
            int temp = cur;
            cur = (cur + pre) % base;
            pre = temp;
        }
        return cur;
    }
};

/* 11旋转数组的最小数字 */
/* 遍历，寻找比前一个数小的元素 */
/* 找不到则为数组第一个元素 */
class Solution {
public:
    int minArray(vector<int>& numbers) {
        int res = numbers[0];
        for (int i = 1; i < numbers.size(); i++) {
            if (numbers[i] < numbers[i - 1]) {
                res = numbers[i];
                break;
            }
        }
        return res;
    }
};

/* 12矩阵中的路径 */
/* 回溯法 */
/* 注意是在相邻4个中一个满足即可 */
/* 以及在开始回溯之前 */
/* 需要确定匹配第一个元素 */
class Solution {
public:
    int dx[4] = {-1, 0, 0, 1};
    int dy[4] = {0, -1, 1, 0};
    bool backtrack(string& word, int position, vector<vector<char>>& board,
                   vector<vector<int>>& visited, int row, int col) {
        if (position == word.size()) {
            return true;
        }
        char c = word[position];
        for (int i = 0; i < 4; i++) {
            int x = row + dx[i], y = col + dy[i];
            if (x < 0 || x >= board.size() || y < 0 || y >= board[0].size() ||
                visited[x][y] || board[x][y] != c) {
                continue;
            }
            visited[x][y] = 1;
            if (backtrack(word, position + 1, board, visited, x, y)) {
                return true;
            }
            visited[x][y] = 0;
        }
        return false;
    }
    bool exist(vector<vector<char>>& board, string word) {
        vector<vector<int>> visited(board.size(),
                                    vector<int>(board[0].size(), 0));
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (board[i][j] == word[0]) {
                    visited[i][j] = 1;
                    if (backtrack(word, 1, board, visited, i, j)) {
                        return true;
                    }
                    visited[i][j] = 0;
                }
            }
        }
        return false;
    }
};
/* 回溯法 */
/* 判断位置不同 */
class Solution {
public:
    int dx[4] = {-1, 0, 0, 1};
    int dy[4] = {0, -1, 1, 0};
    int Row, Col;
    bool backtrack(string& word, int position, vector<vector<char>>& board,
                   vector<vector<int>>& visited, int row, int col) {
        if (row < 0 || row >= Row || col < 0 || col >= Col ||
            visited[row][col] || board[row][col] != word[position]) {
            return false;
        }
        if (position == word.size() - 1) {
            return true;
        }
        visited[row][col] = 1;
        bool res =
            backtrack(word, position + 1, board, visited, row - 1, col) ||
            backtrack(word, position + 1, board, visited, row, col - 1) ||
            backtrack(word, position + 1, board, visited, row, col + 1) ||
            backtrack(word, position + 1, board, visited, row + 1, col);
        visited[row][col] = 0;
        return res;
    }
    bool exist(vector<vector<char>>& board, string word) {
        Row = board.size(), Col = board[0].size();
        vector<vector<int>> visited(board.size(),
                                    vector<int>(board[0].size(), 0));
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (backtrack(word, 0, board, visited, i, j)) {
                    return true;
                }
            }
        }
        return false;
    }
};

/* 13机器人的运动范围 */
/* 深度优先搜索 */
class Solution {
public:
    int limit;
    int dx[4] = {-1, 0, 0, 1};
    int dy[4] = {0, -1, 1, 0};
    bool isAviable(int m, int n, int row, int col,
                   vector<vector<int>>& visited) {
        if (row < 0 || row >= m || col < 0 || col >= n || visited[row][col]) {
            return false;
        }
        visited[row][col] = 1;
        int sum = 0;
        while (row > 0) {
            sum += row % 10;
            row /= 10;
        }
        while (col > 0) {
            sum += col % 10;
            col /= 10;
        }
        return sum <= limit;
    }
    int dfs(int m, int n, vector<vector<int>>& visited, int row, int col) {
        if (!isAviable(m, n, row, col, visited)) {
            return 0;
        }
        int res = 1;
        for (int i = 0; i < 4; i++) {
            int x = row + dx[i], y = col + dy[i];
            res += dfs(m, n, visited, x, y);
        }
        return res;
    }
    int movingCount(int m, int n, int k) {
        if (k < 0) {
            return 0;
        }
        if (k == 0) {
            return 1;
        }
        limit = k;
        vector<vector<int>> visited(m, vector<int>(n, 0));
        return dfs(m, n, visited, 0, 0);
    }
};
/* 优化代码，只需要搜索向下和向右方向 */
class Solution {
public:
    int limit;
    bool isAviable(int m, int n, int row, int col,
                   vector<vector<int>>& visited) {
        if (row < 0 || row >= m || col < 0 || col >= n || visited[row][col]) {
            return false;
        }
        visited[row][col] = 1;
        int sum = 0;
        while (row > 0) {
            sum += row % 10;
            row /= 10;
        }
        while (col > 0) {
            sum += col % 10;
            col /= 10;
        }
        return sum <= limit;
    }
    int dfs(int m, int n, vector<vector<int>>& visited, int row, int col) {
        if (!isAviable(m, n, row, col, visited)) {
            return 0;
        }
        int res = 1;
        res +=
            dfs(m, n, visited, row, col + 1) + dfs(m, n, visited, row + 1, col);
        return res;
    }
    int movingCount(int m, int n, int k) {
        if (k < 0) {
            return 0;
        }
        if (k == 0) {
            return 1;
        }
        limit = k;
        vector<vector<int>> visited(m, vector<int>(n, 0));
        return dfs(m, n, visited, 0, 0);
    }
};
/* 广度优先搜索 */
/* 注意入队，以及判断满足条件的时机 */
/* 不要重复判断 */
class Solution {
public:
    int limit;
    int dx[2] = {0, 1};
    int dy[2] = {1, 0};
    bool isAviable(int m, int n, int row, int col,
                   vector<vector<int>>& visited) {
        if (row < 0 || row >= m || col < 0 || col >= n || visited[row][col]) {
            return false;
        }
        visited[row][col] = 1;
        int sum = 0;
        while (row > 0) {
            sum += row % 10;
            row /= 10;
        }
        while (col > 0) {
            sum += col % 10;
            col /= 10;
        }
        return sum <= limit;
    }
    int movingCount(int m, int n, int k) {
        limit = k;
        int count = 0;
        queue<pair<int, int>> que;
        vector<vector<int>> visited(m, vector<int>(n, 0));
        if (isAviable(m, n, 0, 0, visited)) {
            que.push({0, 0});
        }
        while (!que.empty()) {
            auto it = que.front();
            que.pop();
            count++;
            for (int i = 0; i < 2; i++) {
                int x = it.first + dx[i], y = it.second + dy[i];
                if (isAviable(m, n, x, y, visited)) {
                    que.push({x, y});
                }
            }
        }
        return count;
    }
};