/*
 * @Author: your name
 * @Date: 2021-05-30 21:19:20
 * @LastEditTime: 2021-05-31 23:36:11
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\广度优先搜索.cpp
 */

/* 133题客隆图 */
/* 广度优先搜索 */
/* 注意是克隆，所以需要new新的对象 */
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (node == NULL) {
            return node;
        }
        unordered_map<Node*, Node*> visited;
        queue<Node*> que;
        que.push(node);
        visited[node] = new Node(node->val);
        while (!que.empty()) {
            Node* n = que.front();
            que.pop();
            for (auto& neighbor : n->neighbors) {
                if (!visited.count(neighbor)) {
                    visited[neighbor] = new Node(neighbor->val);
                    que.push(neighbor);
                }
                visited[n]->neighbors.push_back(visited[neighbor]);
            }
        }
        return visited[node];
    }
};
/* 深度优先搜索方法 */
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    unordered_map<Node*, Node*> visited;
    Node* cloneGraph(Node* node) {
        if (node == nullptr) {
            return node;
        }
        if (visited.find(node) != visited.end()) {
            return visited[node];
        }
        Node* newNode = new Node(node->val);
        visited[node] = newNode;
        for (auto& neighbor : node->neighbors) {
            newNode->neighbors.push_back(cloneGraph(neighbor));
        }
        return newNode;
    }
};

/* 130题被围绕的区域 */
/* 深度优先搜索 */
/* 并查集，通过一次搜索将区域分为 */
/* 与边界'O'相连的'O',和其他部分 */
/* 第二次搜索，将搜索结果中第一种转换为'O' */
/* 另一部分转换为'X' */
class Solution {
public:
    void dfs(vector<vector<char>>& board, int row, int col) {
        if (row < 0 || row >= board.size() || col < 0 ||
            col >= board[0].size() || board[row][col] != 'O') {
            return;
        }
        board[row][col] = 'A';
        dfs(board, row - 1, col);
        dfs(board, row + 1, col);
        dfs(board, row, col - 1);
        dfs(board, row, col + 1);
    }
    void solve(vector<vector<char>>& board) {
        int n = board.size();
        if (n <= 1) {
            return;
        }
        int m = board[0].size();
        for (int r = 0; r < n; r++) {
            dfs(board, r, 0);
            dfs(board, r, m - 1);
        }
        for (int c = 0; c < m; c++) {
            dfs(board, 0, c);
            dfs(board, n - 1, c);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == 'A') {
                    board[i][j] = 'O';
                } else {
                    board[i][j] = 'X';
                }
            }
        }
    }
};
/* 广度优先搜索 */
class Solution {
public:
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    void solve(vector<vector<char>>& board) {
        if (board.empty()) {
            return;
        }
        int n = board.size(), m = board[0].size();
        queue<pair<int, int>> que;

        for (int i = 0; i < n; i++) {
            if (board[i][0] == 'O') {
                que.push(make_pair(i, 0));
            }
            if (board[i][m - 1] == 'O') {
                que.push(make_pair(i, m - 1));
            }
        }
        for (int i = 0; i < m; i++) {
            if (board[0][i] == 'O') {
                que.push(make_pair(0, i));
            }
            if (board[n - 1][i] == 'O') {
                que.push(make_pair(n - 1, i));
            }
        }
        while (!que.empty()) {
            auto it = que.front();
            que.pop();
            board[it.first][it.second] = 'A';
            for (int i = 0; i < 4; i++) {
                int row = it.first + dr[i], col = it.second + dc[i];
                if (row >= 0 && row < n && col >= 0 && col < m &&
                    board[row][col] == 'O') {
                    que.push(make_pair(row, col));
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == 'A') {
                    board[i][j] = 'O';
                } else {
                    board[i][j] = 'X';
                }
            }
        }
    }
};

/* 200题岛屿数量 */
/* 广度优先搜索 */
/* 注意在找到'1'元素时，需要立即改为'0' */
/* 而不是将其加入队列，之后出队时改为'0' */
/* 那样会重复加入很多的位置， */
/* 原因是图的几何位置关系 */
class Solution {
public:
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) {
            return 0;
        }
        int n = grid.size(), m = grid[0].size();
        int count = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '1') {
                    count++;
                    queue<pair<int, int>> que;
                    que.push(make_pair(i, j));
                    grid[i][j] = '0';
                    while (!que.empty()) {
                        auto it = que.front();
                        que.pop();
                        for (int k = 0; k < 4; k++) {
                            int row = it.first + dx[k], col = it.second + dy[k];
                            if (row >= 0 && row < n && col >= 0 && col < m) {
                                if (grid[row][col] == '1') {
                                    grid[row][col] = '0';
                                    que.push(make_pair(row, col));
                                }
                            }
                        }
                    }
                }
            }
        }
        return count;
    }
};
/* 深度优先搜索 */
/* 思路与广度优先搜索类似 */
class Solution {
public:
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    void dfs(vector<vector<char>>& grid, int row, int col) {
        if (row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size()) {
            return;
        }
        if (grid[row][col] == '0') {
            return;
        }
        grid[row][col] = '0';
        for (int i = 0; i < 4; i++) {
            dfs(grid, row + dx[i], col + dy[i]);
        }
    }
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) {
            return 0;
        }
        int n = grid.size(), m = grid[0].size();
        int count = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '1') {
                    count++;
                    dfs(grid, i, j);
                }
            }
        }
        return count;
    }
};

/* 417题太平洋大西洋水流问题 */
/* 广度优先搜索 */
class Solution {
public:
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        vector<vector<int>> res;
        if (heights.empty()) {
            return res;
        }
        int n = heights.size(), m = heights[0].size();
        vector<vector<char>> type1(n, vector<char>(m, '0')),
            type2(n, vector<char>(m, '0'));
        for (int i = 0; i < m; i++) {
            type1[0][i] = 'a';
            type2[n - 1][i] = 'b';
        }
        for (int i = 0; i < n; i++) {
            type1[i][0] = 'a';
            type2[i][m - 1] = 'b';
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (type1[i][j] == 'a') {
                    queue<pair<int, int>> que;
                    que.push(make_pair(i, j));
                    type1[i][j] = 'a';
                    while (!que.empty()) {
                        auto it = que.front();
                        que.pop();
                        for (int k = 0; k < 4; k++) {
                            int row = it.first + dx[k], col = it.second + dy[k];
                            if (row >= 0 && row < n && col >= 0 && col < m) {
                                if (heights[row][col] >=
                                        heights[it.first][it.second] &&
                                    type1[row][col] != 'a') {
                                    type1[row][col] = 'a';
                                    que.push(make_pair(row, col));
                                }
                            }
                        }
                    }
                }
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                if (type2[i][j] == 'b') {
                    queue<pair<int, int>> que;
                    que.push(make_pair(i, j));
                    type2[i][j] = 'b';
                    while (!que.empty()) {
                        auto it = que.front();
                        que.pop();
                        for (int k = 0; k < 4; k++) {
                            int row = it.first + dx[k], col = it.second + dy[k];
                            if (row >= 0 && row < n && col >= 0 && col < m) {
                                if (heights[row][col] >=
                                        heights[it.first][it.second] &&
                                    type2[row][col] != 'b') {
                                    type2[row][col] = 'b';
                                    que.push(make_pair(row, col));
                                }
                            }
                        }
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (type1[i][j] == 'a' && type2[i][j] == 'b') {
                    res.push_back({i, j});
                }
            }
        }
        return res;
    }
};
/* 深度优先搜索 */
class Solution {
public:
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    void dfs1(vector<vector<int>>& heights, vector<vector<char>>& type1,
              int row, int col) {
        if (row < 0 || row >= heights.size() || col < 0 ||
            col >= heights[0].size()) {
            return;
        }
        type1[row][col] = 'a';
        for (int i = 0; i < 4; i++) {
            int r = row + dx[i], c = col + dy[i];
            if (r >= 0 && r < heights.size() && c >= 0 &&
                c < heights[0].size()) {
                if (heights[r][c] >= heights[row][col] && type1[r][c] != 'a') {
                    dfs1(heights, type1, r, c);
                }
            }
        }
    }
    void dfs2(vector<vector<int>>& heights, vector<vector<char>>& type2,
              int row, int col) {
        if (row < 0 || row >= heights.size() || col < 0 ||
            col >= heights[0].size()) {
            return;
        }
        type2[row][col] = 'b';
        for (int i = 0; i < 4; i++) {
            int r = row + dx[i], c = col + dy[i];
            if (r >= 0 && r < heights.size() && c >= 0 &&
                c < heights[0].size()) {
                if (heights[r][c] >= heights[row][col] && type2[r][c] != 'b') {
                    dfs2(heights, type2, r, c);
                }
            }
        }
    }
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        vector<vector<int>> res;
        if (heights.empty()) {
            return res;
        }
        int n = heights.size(), m = heights[0].size();
        vector<vector<char>> type1(n, vector<char>(m, '0')),
            type2(n, vector<char>(m, '0'));
        for (int i = 0; i < m; i++) {
            type1[0][i] = 'a';
            type2[n - 1][i] = 'b';
        }
        for (int i = 0; i < n; i++) {
            type1[i][0] = 'a';
            type2[i][m - 1] = 'b';
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (type1[i][j] == 'a') {
                    dfs1(heights, type1, i, j);
                }
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                if (type2[i][j] == 'b') {
                    dfs2(heights, type2, i, j);
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (type1[i][j] == 'a' && type2[i][j] == 'b') {
                    res.push_back({i, j});
                }
            }
        }
        return res;
    }
};