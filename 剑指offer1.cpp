/*
 * @Author: 夏玄兵
 * @Date: 2021-07-23 23:19:42
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2021-08-15 00:09:55
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

/* 14I-剪绳子 */
/* 动态规划 */
/* dp[i]=max(dp[i],j*(i-j),j*dp[i-j]) */
/* 注意一定不要漏了j*(i-j) */
class Solution {
public:
    int cuttingRope(int n) {
        vector<int> dp(n + 1, 0);
        dp[2] = 1;
        for (int i = 3; i <= n; i++) {
            for (int j = 2; j < i; j++) {
                dp[i] = max(dp[i], j * (i - j));
                dp[i] = max(dp[i], j * dp[i - j]);
            }
        }
        return dp.back();
    }
};

/* 15二进制中1的个数 */
/* 位与操作判断最小为是否为1 */
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int res = 0;
        while (n > 0) {
            if (n & 1) {
                res++;
            }
            n >>= 1;
        }
        return res;
    }
};

/* 16数值的整数次方 */
/* 快速幂 */
/* 注意幂为负，以及范围问题 */
class Solution {
public:
    double qpow(double x, int n) {
        if (n == 0) {
            return 1.00;
        }
        if (n % 2) {
            return myPow(x, n - 1) * x;
        } else {
            double temp = myPow(x, n / 2);
            return temp * temp;
        }
    }
    double myPow(double x, int n) {
        if (x == 1.0) {
            return 1.0;
        }
        return n >= 0 ? qpow(x, n) : 1.0 / qpow(x, -(n + 1)) / x;
    }
};

/* 17打印从1到最大的n位数 */
/* 找到最大n位数，遍历 */
class Solution {
public:
    vector<int> printNumbers(int n) {
        int maxNum = pow(10, n) - 1;
        vector<int> res;
        for (int i = 1; i <= maxNum; i++) {
            res.push_back(i);
        }
        return res;
    }
};

/* 18删除链表的节点 */
/* 找到要删除节点的前一个节点 */
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
    ListNode* deleteNode(ListNode* head, int val) {
        ListNode* newHead = new ListNode(0, head);
        ListNode* tail = newHead;
        while (tail != NULL && tail->next != NULL) {
            if (tail->next->val == val) {
                tail->next = tail->next->next;
                break;
            }
            tail = tail->next;
        }
        return newHead->next;
    }
};

/* 21调整数组顺序使奇数位于偶数前面 */
/* 双指针 */
class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        int i = 0;
        while (i < nums.size()) {
            if (nums[i] % 2) {
                i++;
                continue;
            }
            int j = i + 1;
            while (j < nums.size() && nums[j] % 2 == 0) {
                j++;
            }
            if (j == nums.size() || nums[j] % 2 == 0) {
                break;
            }
            swap(nums[i], nums[j]);
            i++;
        }
        return nums;
    }
};
/* 双指针，偶数放到后面 */
class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        int i = 0, j = nums.size() - 1;
        while (i < j) {
            while (i < j && nums[i] % 2) {
                i++;
            }
            swap(nums[i], nums[j--]);
        }
        return nums;
    }
};
/* 双指针，指数放到前面 */
class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        int i = 0, j = 0;
        while (i < nums.size()) {
            while (i < nums.size() && nums[i] % 2 == 0) {
                i++;
            }
            if (i == nums.size()) {
                break;
            }
            swap(nums[i++], nums[j++]);
        }
        return nums;
    }
};

/* 22链表中倒数第K个节点 */
/* 双指针 */
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
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode *p = head, *q = head;
        while (k--) {
            q = q->next;
        }
        while (q != NULL) {
            p = p->next;
            q = q->next;
        }
        return p;
    }
};

/* 24反转链表 */
/* 头插法 */
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
    ListNode* reverseList(ListNode* head) {
        ListNode* newhead = NULL;
        ListNode* p = head;
        while (p != NULL) {
            ListNode* next = p->next;
            p->next = newhead;
            newhead = p;
            p = next;
        }
        return newhead;
    }
};
/* 另一种写法 */
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
    ListNode* reverseList(ListNode* head) {
        ListNode* newhead = new ListNode(-1, NULL);
        ListNode* p = head;
        while (p != NULL) {
            ListNode* next = p->next;
            p->next = newhead->next;
            newhead->next = p;
            p = next;
        }
        return newhead->next;
    }
};
/* 递归 */
/* 注意最后通过head->next找到head的前一节点 */
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
    ListNode* reverseList(ListNode* head) {
        if (head == NULL || head->next == NULL) {
            return head;
        }
        ListNode* newhead = reverseList(head->next);
        head->next->next = head;
        head->next = NULL;
        return newhead;
    }
};

/* 25合并两个排序的链表 */
/* 双指针 */
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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* newhead = new ListNode(-1, NULL);
        ListNode* tail = newhead;
        while (l1 != NULL && l2 != NULL) {
            if (l1->val <= l2->val) {
                tail->next = l1;
                tail = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                tail = l2;
                l2 = l2->next;
            }
        }
        if (l1 != NULL) {
            tail->next = l1;
        }
        if (l2 != NULL) {
            tail->next = l2;
        }
        return newhead->next;
    }
};

/* 26树的子结构 */
/* 与子树类似 */
/* 注意子结构和子树不同 */
/* 只要某一部分相同即可满足子结构 */
/* 重点是recur函数 */
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
    bool recur(TreeNode* p, TreeNode* q) {
        if (q == NULL) {
            return true;
        }
        if (p == NULL || p->val != q->val) {
            return false;
        }
        return recur(p->left, q->left) && recur(p->right, q->right);
    }
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if (A == NULL && B == NULL) {
            return true;
        }
        if ((A == NULL) || (B == NULL)) {
            return false;
        }
        bool res1 = recur(A, B);
        bool res2 = isSubStructure(A->left, B) || isSubStructure(A->right, B);
        return res1 || res2;
    }
};

/* 27二叉树的镜像 */
/* 递归，深度优先搜索 */
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
    TreeNode* mirrorTree(TreeNode* root) {
        if (root == NULL) {
            return root;
        }
        TreeNode* left = root->left;
        root->left = mirrorTree(root->right);
        root->right = mirrorTree(left);
        return root;
    }
};

/* 28对称的二叉树 */
/* 深度优先搜索 */
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
    bool isSym(TreeNode* left, TreeNode* right) {
        if (left == NULL && right == NULL) {
            return true;
        }
        if (left == NULL || right == NULL) {
            return false;
        }
        return left->val == right->val && isSym(left->left, right->right) &&
               isSym(left->right, right->left);
    }
    bool isSymmetric(TreeNode* root) {
        if (root == NULL) {
            return true;
        }
        return isSym(root->left, root->right);
    }
};
/* 代码优先 */
/* 先判断两个节点的值是否相等 */
/* 不等则跳过，实现剪枝 */
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
    bool isSym(TreeNode* left, TreeNode* right) {
        if (left == NULL && right == NULL) {
            return true;
        }
        if (left == NULL || right == NULL || left->val != right->val) {
            return false;
        }
        return isSym(left->left, right->right) &&
               isSym(left->right, right->left);
    }
    bool isSymmetric(TreeNode* root) {
        if (root == NULL) {
            return true;
        }
        return isSym(root->left, root->right);
    }
};

/* 29顺时针打印矩阵 */
/* 一层一层打印 */
/* 重点是做到顺时针，并且判断是否已访问过 */
class Solution {
public:
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    int row, col;
    bool isAviable(int r, int c, vector<vector<int>>& visited) {
        return r >= 0 && r < row && c >= 0 && c < col && !visited[r][c];
    }
    void dfs(vector<vector<int>>& matrix, vector<vector<int>>& visited,
             vector<int>& res, int r, int c) {
        for (int i = 0; i < 4; i++) {
            while (isAviable(r + dx[i], c + dy[i], visited)) {
                r += dx[i];
                c += dy[i];
                visited[r][c] = 1;
                res.push_back(matrix[r][c]);
            }
        }
    }
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        if (matrix.empty()) {
            return res;
        }
        row = matrix.size();
        col = matrix[0].size();
        vector<vector<int>> visited(row, vector<int>(col, 0));
        for (int i = 0; i <= min(row / 2, col / 2); i++) {
            if (!isAviable(i, i, visited)) {
                continue;
            }
            res.push_back(matrix[i][i]);
            visited[i][i] = 1;
            dfs(matrix, visited, res, i, i);
        }
        return res;
    }
};

/* 30包含min函数的栈 */
/* 栈和map */
class MinStack {
public:
    /** initialize your data structure here. */
    stack<int> stk;
    map<int, int> mp;
    MinStack() {}

    void push(int x) {
        stk.push(x);
        mp[x]++;
    }

    void pop() {
        if (--mp[stk.top()] <= 0) {
            mp.erase(stk.top());
        }
        stk.pop();
    }

    int top() { return stk.top(); }

    int min() { return mp.begin()->first; }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->min();
 */
/* 两个栈 */
class MinStack {
public:
    /** initialize your data structure here. */
    stack<int> stk1;
    stack<int> stk2;
    MinStack() {}

    void push(int x) {
        stk1.push(x);
        if (stk2.empty() || x <= stk2.top()) {
            stk2.push(x);
        }
    }

    void pop() {
        if (stk2.top() == stk1.top()) {
            stk2.pop();
        }
        stk1.pop();
    }

    int top() { return stk1.top(); }

    int min() { return stk2.top(); }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->min();
 */

/* 31栈的压入、弹出序列 */
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        int i = 0, length = pushed.size();
        stack<int> stk;
        for (int j = 0; j < length; j++) {
            int num = popped[j];
            if (stk.empty() || stk.top() != num) {
                while (i < length && pushed[i] != num) {
                    stk.push(pushed[i]);
                    i++;
                }
                if (i >= length || pushed[i] != num) {
                    return false;
                }
                i++;
            } else {
                stk.pop();
            }
        }
        return true;
    }
};
/* 模拟压栈、出栈 */
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> stk;
        int i = 0;
        for (int j = 0; j < pushed.size(); j++) {
            stk.push(pushed[j]);
            while (!stk.empty() && stk.top() == popped[i]) {
                stk.pop();
                i++;
            }
        }
        return stk.empty();
    }
};

/* 32I-从上到下打印二叉树 */
/* 层序遍历，队列 */
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
    vector<int> levelOrder(TreeNode* root) {
        vector<int> res;
        queue<TreeNode*> que;
        if (root != NULL) {
            que.push(root);
        }
        while (!que.empty()) {
            TreeNode* it = que.front();
            que.pop();
            res.push_back(it->val);
            if (it->left != NULL) {
                que.push(it->left);
            }
            if (it->right != NULL) {
                que.push(it->right);
            }
        }
        return res;
    }
};

/* 32II-从上到下打印二叉树II */
/* 层序遍历 */
/* 遍历每一层时确定队列size，即为该层节点个数 */
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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        queue<TreeNode*> que;
        if (root != NULL) {
            que.push(root);
        }
        while (!que.empty()) {
            int num = que.size();
            vector<int> temp;
            for (int i = 0; i < num; i++) {
                TreeNode* it = que.front();
                que.pop();
                temp.push_back(it->val);
                if (it->left != NULL) {
                    que.push(it->left);
                }
                if (it->right != NULL) {
                    que.push(it->right);
                }
            }
            res.push_back(temp);
        }
        return res;
    }
};

/* 32III-从上到下打印二叉树-III */
/* 两个栈交替压栈和出栈，且压栈的顺序不同 */
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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        stack<TreeNode*> stk1;
        stack<TreeNode*> stk2;
        if (root != NULL) {
            stk1.push(root);
        }
        while (!stk1.empty() || !stk2.empty()) {
            vector<int> temp;
            if (!stk1.empty()) {
                while (!stk1.empty()) {
                    TreeNode* it = stk1.top();
                    stk1.pop();
                    temp.push_back(it->val);
                    if (it->left != NULL) {
                        stk2.push(it->left);
                    }
                    if (it->right != NULL) {
                        stk2.push(it->right);
                    }
                }
            } else {
                while (!stk2.empty()) {
                    TreeNode* it = stk2.top();
                    stk2.pop();
                    temp.push_back(it->val);
                    if (it->right != NULL) {
                        stk1.push(it->right);
                    }
                    if (it->left != NULL) {
                        stk1.push(it->left);
                    }
                }
            }
            res.push_back(temp);
        }
        return res;
    }
};
/* 层序遍历，偶数层反转 */
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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        queue<TreeNode*> que;
        if (root != NULL) {
            que.push(root);
        }
        bool isOdd = true;
        while (!que.empty()) {
            int num = que.size();
            vector<int> temp;
            while (num--) {
                TreeNode* it = que.front();
                que.pop();
                temp.push_back(it->val);
                if (it->left != NULL) {
                    que.push(it->left);
                }
                if (it->right != NULL) {
                    que.push(it->right);
                }
            }
            if (!isOdd) {
                reverse(temp.begin(), temp.end());
            }
            isOdd = !isOdd;
            res.push_back(temp);
        }
        return res;
    }
};

/* 33二叉搜索树的后续遍历序列 */
/* 利用二叉搜索树中序遍历为递增的性质 */
/* 定义一个中序遍历数组 */
/* 从而转化为根据中序遍历和后序遍历数组 */
/* 能否构建树的问题 */
class Solution {
public:
    bool isTree(vector<int>& postorder, vector<int>& inorder, int postbegin,
                int postend, int inbegin, int inend) {
        if (postbegin > postend) {
            return true;
        }
        int index = inbegin, target = postorder[postend];
        for (; index <= inend; index++) {
            if (inorder[index] == target) {
                break;
            }
        }
        if (index > inend) {
            return false;
        }
        int length = index - inbegin;
        return isTree(postorder, inorder, postbegin, postbegin + length - 1,
                      inbegin, index - 1) &&
               isTree(postorder, inorder, postbegin + length, postend - 1,
                      index + 1, inend);
    }
    bool verifyPostorder(vector<int>& postorder) {
        vector<int> inorder = postorder;
        sort(inorder.begin(), inorder.end());
        return isTree(postorder, inorder, 0, postorder.size() - 1, 0,
                      postorder.size() - 1);
    }
};
/* 递归 */
/* 寻找第一个大于根节点元素，从而分为左子树和右子树 */
/* 左子树均小于根节点，已满足 */
/* 同时右子树均大于根节点，则为二叉搜索树 */
/* 由此不断递归 */
class Solution {
public:
    bool isBST(vector<int>& postorder, int begin, int end) {
        if (begin >= end) {
            return true;
        }
        int i = begin;
        while (postorder[i] < postorder[end]) {
            i++;
        }
        int m = i;
        while (postorder[i] > postorder[end]) {
            i++;
        }
        return i == end && isBST(postorder, begin, m - 1) &&
               isBST(postorder, m, end - 1);
    }
    bool verifyPostorder(vector<int>& postorder) {
        return isBST(postorder, 0, postorder.size() - 1);
    }
};

/* 34二叉树中和为某一值的路径 */
/* 深度优先搜索 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> res;
    void dfs(TreeNode* root, int target, vector<int> path, int sum) {
        path.push_back(root->val);
        sum += root->val;
        if (root->left == nullptr && root->right == nullptr && sum == target) {
            res.push_back(path);
            return;
        }
        if (root->left != nullptr) dfs(root->left, target, path, sum);
        if (root->right != nullptr) dfs(root->right, target, path, sum);
    }
    vector<vector<int>> pathSum(TreeNode* root, int target) {
        if (root == nullptr) {
            return res;
        }
        vector<int> path;
        int sum = 0;
        dfs(root, target, path, sum);
        return res;
    }
};

/* 35复杂链表的复制 */
/* 第一次遍历复制单链表，不管random */
/* 并将新建节点和旧节点的对应用哈希表存储起来 */
/* 第二次遍历确定每个节点的random */
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        Node* newhead = new Node(-1);
        Node *tail = newhead, *p = head;
        map<Node*, Node*> mp;
        while (p != NULL) {
            Node* temp = new Node(p->val);
            mp[p] = temp;
            tail->next = temp;
            tail = temp;
            p = p->next;
        }
        tail->next = NULL;
        p = head;
        tail = newhead->next;
        while (p != NULL) {
            tail->random = p->random != NULL ? mp[p->random] : NULL;
            p = p->next;
            tail = tail->next;
        }
        return newhead->next;
    }
};
/* 第一遍只建立哈希表对应关系 */
/* 第二遍确定新建链表的next,random */
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == NULL) {
            return NULL;
        }
        unordered_map<Node*, Node*> mp;
        Node* p = head;
        while (p != NULL) {
            mp[p] = new Node(p->val);
            p = p->next;
        }
        p = head;
        while (p != NULL) {
            mp[p]->next = mp[p->next];
            mp[p]->random = mp[p->random];
            p = p->next;
        }
        return mp[head];
    }
};
/* 拼接和拆分 */
/* 注意拆分的代码，并且确定random和拆分不能一起实现 */
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == NULL) {
            return NULL;
        }
        Node* p = head;
        while (p != NULL) {
            Node* node = new Node(p->val);
            node->next = p->next;
            p->next = node;
            p = node->next;
        }
        p = head;
        while (p != NULL) {
            if (p->random != NULL) {
                p->next->random = p->random->next;
            }
            p = p->next->next;
        }
        p = head;
        Node *res = head->next, *q = head->next;
        while (q->next != NULL) {
            p->next = p->next->next;
            q->next = q->next->next;
            p = p->next;
            q = q->next;
        }
        p->next = NULL;
        return res;
    }
};

/* 36二叉搜索树与双向链表 */
/* 中序遍历，迭代 */
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if (root == NULL) {
            return NULL;
        }
        stack<Node*> stk;
        Node *head = NULL, *pre = NULL;
        while (!stk.empty() || root != NULL) {
            while (root != NULL) {
                stk.push(root);
                root = root->left;
            }
            if (!stk.empty()) {
                root = stk.top();
                stk.pop();
                if (head == NULL) {
                    head = root;
                    pre = root;
                } else {
                    pre->right = root;
                    root->left = pre;
                    pre = root;
                }
                root = root->right;
            }
        }
        head->left = pre;
        pre->right = head;
        return head;
    }
};
/* 中序遍历，递归 */
/* 不考虑具体细节，定义双向链表的头尾节点 */
/* 然后，递归时不断将当前节点和尾结点连接 */
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if (root == NULL) {
            return NULL;
        }
        dfs(root);
        head->left = tail;
        tail->right = head;
        return head;
    }

private:
    Node *head, *tail;
    void dfs(Node* root) {
        if (root == NULL) {
            return;
        }
        dfs(root->left);
        if (tail != NULL) {
            tail->right = root;
        } else {
            head = root;
        }
        root->left = tail;
        tail = root;
        dfs(root->right);
    }
};

/* 38字符串的排列 */
/* 回溯法 */
/* 注意去重方法，同一层相同元素只能遍历一次 */
/* 注意条件为 i>0 && !visited[i-1] && s[i]==s[i-1] */
class Solution {
public:
    vector<string> res;
    void backtrack(string& s, string& path, vector<int>& visited) {
        int n = s.size();
        if (n == path.size()) {
            res.push_back(path);
            return;
        }
        for (int i = 0; i < n; ++i) {
            if (visited[i] || (i > 0 && !visited[i - 1] && s[i] == s[i - 1])) {
                continue;
            }
            path += s[i];
            visited[i] = 1;
            backtrack(s, path, visited);
            path.erase(path.size() - 1, 1);
            visited[i] = 0;
        }
    }
    vector<string> permutation(string s) {
        sort(s.begin(), s.end());
        string path;
        vector<int> visited(s.size(), 0);
        backtrack(s, path, visited);
        return res;
    }
};

/* 39数组中出现次数超过一半的数字 */
/* 先对数组排序 */
/* 双指针遍历，统计出现次数 */
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int res = nums[0], count = 0;
        ;
        for (int i = 0; i < nums.size();) {
            int num = nums[i], j = i + 1;
            while (j < nums.size() && nums[j] == num) {
                j++;
            }
            if (count < j - i) {
                count = j - i;
                res = num;
            }
            i = j;
        }
        return res;
    }
};

/* 40最小的k个数 */
/* 排序，遍历 */
public:
vector<int> getLeastNumbers(vector<int>& arr, int k) {
    if (k == 0) {
        return {};
    }
    sort(arr.begin(), arr.end());
    vector<int> res;
    for (int i = 0; i < arr.size(); i++) {
        res.push_back(arr[i]);
        if (res.size() == k) {
            break;
        }
    }
    return res;
}
}
;
/* 排序，使用vector构造函数 */
class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        sort(arr.begin(), arr.end());
        vector<int> res(arr.begin(), arr.begin() + k);
        return res;
    }
};

/* 42连续子数组的最大和 */
/* 动态规划 */
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int> dp = nums;
        int res = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            dp[i] = dp[i - 1] > 0 ? dp[i - 1] + nums[i] : nums[i];
            res = max(res, dp[i]);
        }
        return res;
    }
};

/* 43 1~n整数中1出现的次数 */
/* 重点关注如何计算每一位出现1的次数 */
class Solution {
public:
    int countDigitOne(int n) {
        long high = n / 10, cur = n % 10, low = 0, digit = 1;
        long res = 0;
        while (high != 0 || cur != 0) {
            if (cur == 1) {
                res += high * digit + low + 1;
            } else if (cur < 1) {
                res += high * digit;
            } else {
                res += (high + 1) * digit;
            }
            low += cur * digit;
            cur = high % 10;
            high /= 10;
            digit *= 10;
        }
        return int(res);
    }
};

/* 44数字序列中某一位的数字 */
/* 确定位数、数、数中对应的位置 */
/* 最后确定数中对应的位置注意转换为字符串 */
class Solution {
public:
    int findNthDigit(int n) {
        if (n < 10) {
            return n;
        }
        long count = 1, sum = 9, pre = 9;
        while (sum < n) {
            count++;
            pre *= 10;
            sum += pre * count;
        }
        if (sum == n) {
            return 9;
        }
        sum -= pre * count;
        n -= sum;
        int res = pre / 9 + (n - 1) / count;
        string s = to_string(res);
        return s[(n - 1) % count] - '0';
    }
};

/* 46把数字翻译成字符串 */
/* 动态规划 */
/* 先将int转为string */
/* dp[i]为0~i个字符的翻译方法 */
class Solution {
public:
    bool isAviable(char c1, char c2) {
        return (c1 - '0') > 0 && (c1 - '0') * 10 + c2 - '0' <= 25;
    }
    int translateNum(int num) {
        string s = to_string(num);
        vector<int> dp(s.size(), 0);
        dp[0] = 1;
        for (int i = 1; i < s.size(); i++) {
            dp[i] = dp[i - 1];
            if (isAviable(s[i - 1], s[i])) {
                if (i >= 2) {
                    dp[i] += dp[i - 2];
                } else {
                    dp[i]++;
                }
            }
        }
        return dp.back();
    }
};

/* 47礼物的最大价值 */
/* 递归或者回溯 */
/* 应该可以，提交超时 */
class Solution {
public:
    int dx[2] = {0, 1};
    int dy[2] = {1, 0};
    int value(vector<vector<int>>& grid, int row, int col) {
        if (row == grid.size() - 1 && col == grid[0].size() - 1) {
            return 0;
        }
        int res = 0;
        for (int i = 0; i < 2; i++) {
            int x = row + dx[i], y = col + dy[i];
            if (x < grid.size() && y < grid[0].size()) {
                res = max(res, grid[x][y] + value(grid, x, y));
            }
        }
        return res;
    }
    int maxValue(vector<vector<int>>& grid) {
        return grid[0][0] + value(grid, 0, 0);
    }
};
/* 动态规划 */
/* dp[i][j]为到达(i,j)时礼物最大价值 */
class Solution {
public:
    int dx[2] = {0, -1};
    int dy[2] = {-1, 0};
    int maxValue(vector<vector<int>>& grid) {
        vector<vector<int>> dp(grid.size(), vector<int>(grid[0].size(), 0));
        dp[0][0] = grid[0][0];
        int m = grid.size(), n = grid[0].size();
        for (int i = 0; i < m; i++) {
            int j = i == 0 ? 1 : 0;
            for (; j < n; j++) {
                for (int k = 0; k < 2; k++) {
                    int x = i + dx[k], y = j + dy[k];
                    if (x >= 0 && x < m && y >= 0 && y < n) {
                        dp[i][j] = max(dp[i][j], grid[i][j] + dp[x][y]);
                    }
                }
            }
        }
        return dp[m - 1][n - 1];
    }
};

/* 48最长不包含重复字符的子字符串 */
/* 哈希表统计字符出现次数 */
/* 滑动窗口 */
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> mp;
        int res = 0;
        int left = 0, right = 0;
        while (right < s.size()) {
            char c = s[right++];
            mp[c]++;
            while (mp[c] > 1) {
                mp[s[left]]--;
                left++;
            }
            res = max(res, right - left);
        }
        return res;
    }
};

/* 49丑数 */
/* 动态规划 */
class Solution {
public:
    int min(int num1, int num2, int num3) {
        int res = num1 <= num2 ? num1 : num2;
        return res <= num3 ? res : num3;
    }
    int nthUglyNumber(int n) {
        vector<int> dp(n, 0);
        dp[0] = 1;
        int a = 0, b = 0, c = 0;
        for (int i = 1; i < n; i++) {
            int num1 = dp[a] * 2, num2 = dp[b] * 3, num3 = dp[c] * 5;
            dp[i] = min(num1, num2, num3);
            if (dp[i] == num1) {
                a++;
            }
            if (dp[i] == num2) {
                b++;
            }
            if (dp[i] == num3) {
                c++;
            }
        }
        return dp.back();
    }
};

/* 50第一个只出现一次的字符 */
/* 哈希表，遍历 */
class Solution {
public:
    char firstUniqChar(string s) {
        unordered_map<char, int> mp;
        for (int i = 0; i < s.size(); i++) {
            mp[s[i]]++;
        }
        for (int i = 0; i < s.size(); i++) {
            if (mp[s[i]] == 1) {
                return s[i];
            }
        }
        return ' ';
    }
};

/* 52两个链表的第一个公共节点 */
/* 遍历 */
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
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        ListNode *p = headA, *q = headB;
        ListNode *heada = headA, *headb = headB;
        while (p != NULL && q != NULL) {
            p = p->next;
            q = q->next;
        }
        while (p != NULL) {
            heada = heada->next;
            p = p->next;
        }
        while (q != NULL) {
            headb = headb->next;
            q = q->next;
        }
        p = heada;
        q = headb;
        while (p != NULL && q != NULL) {
            if (p == q) {
                return p;
            }
            p = p->next;
            q = q->next;
        }
        return NULL;
    }
};

/* 53 I-在排序数组中查找数字I */
/* 分别查找左右位置 */
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right && nums[left] != target) {
            left++;
        }
        if (left > right) {
            return 0;
        }
        while (right >= left && nums[right] != target) {
            right--;
        }
        return right - left + 1;
    }
};
/* 二分查找确定左右边界 */
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int val = nums[mid];
            if (val == target) {
                right = mid - 1;
            } else if (val < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        if (left == nums.size() || nums[left] != target) {
            return 0;
        }
        int first = left;
        left = 0;
        right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int val = nums[mid];
            if (val == target) {
                left = mid + 1;
            } else if (val < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        int second = right;
        return second - first + 1;
    }
};

/* 53 II-o~n-1中缺失的数字 */
/* 遍历 */
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != i) {
                return i;
            }
        }
        return nums.size();
    }
};

/* 54二叉搜索树的第k大节点 */
/* 中序遍历，返回数组倒数第k个元素 */
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
    vector<int> num;
    void dfs(TreeNode* root) {
        if (root == NULL) {
            return;
        }
        dfs(root->left);
        num.push_back(root->val);
        dfs(root->right);
    }
    int kthLargest(TreeNode* root, int k) {
        dfs(root);
        return *(num.end() - k);
    }
};
/* 逆中序遍历，并且提前退出递归 */
/* 注意递归结束的条件 */
class Solution {
public:
    int res, count;
    void dfs(TreeNode* root) {
        if (root == NULL) {
            return;
        }
        dfs(root->right);
        if (count == 0) {
            return;
        }
        if (--count == 0) {
            res = root->val;
        }
        dfs(root->left);
    }
    int kthLargest(TreeNode* root, int k) {
        count = k;
        dfs(root);
        return res;
    }
};

/* 55 I-二叉树的深度 */
/* 层序遍历，队列 */
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
    int maxDepth(TreeNode* root) {
        int res = 0;
        queue<TreeNode*> que;
        if (root != NULL) {
            que.push(root);
        }
        while (!que.empty()) {
            int num = que.size();
            res++;
            while (num--) {
                TreeNode* it = que.front();
                que.pop();
                if (it->left != NULL) {
                    que.push(it->left);
                }
                if (it->right != NULL) {
                    que.push(it->right);
                }
            }
        }
        return res;
    }
};

/* 55 II-平衡二叉树 */
/* 后序遍历得到树的深度 */
/* 同时判断子树是否平衡 */
/* 若不平衡直接返回-1，表示不平衡 */
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
    int depth(TreeNode* root) {
        if (root == NULL) {
            return 0;
        }
        int leftDepth = depth(root->left);
        int rightDepth = depth(root->right);
        if (leftDepth == -1 || rightDepth == -1 ||
            abs(leftDepth - rightDepth) > 1) {
            return -1;
        }
        return max(leftDepth, rightDepth) + 1;
    }
    bool isBalanced(TreeNode* root) { return depth(root) != -1; }
};

/* 56 I-数组中数字出现的次数 */
/* 排序，遍历 */
/* 若为重复数字每两个遍历一次 */
class Solution {
public:
    vector<int> singleNumbers(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<int> res;
        for (int i = 0; i < nums.size() - 1; i++) {
            if (nums[i] == nums[i + 1]) {
                i++;
            } else {
                res.push_back(nums[i]);
                if (res.size() == 2) {
                    return res;
                }
            }
        }
        res.push_back(nums.back());
        return res;
    }
};
/* 分组异或 */
/* 注意整型异或的结果不一定是0或1，也有可能大于1 */
class Solution {
public:
    vector<int> singleNumbers(vector<int>& nums) {
        int m = 1, n = 0, x = 0, y = 0;
        for (int num : nums) {
            n ^= num;
        }
        while ((m & n) == 0) {
            m <<= 1;
        }
        for (int num : nums) {
            if ((num & m) == 0) {
                x ^= num;
            } else {
                y ^= num;
            }
        }
        return vector<int>{x, y};
    }
};

/* 56 II-数组中数字出现的次数II */
/* 哈希表 */
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unordered_map<int, int> mp;
        for (int num : nums) {
            mp[num]++;
        }
        for (auto it : mp) {
            if (it.second == 1) {
                return it.first;
            }
        }
        return 0;
    }
};

/* 57和为s的两个数字 */
/* 二分查找 */
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> res;
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int val = nums[left] + nums[right];
            if (val == target) {
                return vector<int>{nums[left], nums[right]};
            } else if (val < target) {
                left++;
            } else {
                right--;
            }
        }
        return res;
    }
};

/* 57 II-和为s的连续整数序列II */
/* 双指针 */
class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        vector<vector<int>> res;
        if (target == 1) {
            return res;
        }
        int right = 1, sum = 0;
        vector<int> tmp;
        while (right < target) {
            tmp.push_back(right);
            sum += right++;
            while (sum > target) {
                sum -= tmp[0];
                tmp.erase(tmp.begin());
            }
            if (sum == target) {
                res.push_back(tmp);
            }
        }
        return res;
    }
};
/* 另一种写法 */
class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        vector<vector<int>> res;
        if (target == 1) {
            return res;
        }
        int left = 0, right = 1, sum = 0;
        while (left < right && right < target) {
            sum += right;
            right++;
            while (sum > target) {
                left++;
                sum -= left;
            }
            if (sum == target) {
                vector<int> tmp;
                for (int i = left + 1; i < right; i++) {
                    tmp.push_back(i);
                }
                res.push_back(tmp);
            }
        }
        return res;
    }
};

/* 58 I-翻转单词顺序 */
/* 双指针 */
class Solution {
public:
    string reverseWords(string s) {
        string res;
        int left = s.size() - 1, right = s.size() - 1;
        while (left >= 0) {
            right = left;
            while (right >= 0 && s[right] == ' ') {
                right--;
            }
            if (right < 0) {
                break;
            }
            left = right - 1;
            while (left >= 0 && s[left] != ' ') {
                left--;
            }
            res += s.substr(left + 1, right - left) + " ";
        }
        res.pop_back();
        return res;
    }
};

/* 58 II-左旋转字符串 */
/* 字串，遍历 */
class Solution {
public:
    string reverseLeftWords(string s, int n) {
        if (n == 0) {
            return s;
        }
        string str = s.substr(0, n);
        int length = s.size();
        for (int i = 0; i < length; i++) {
            s[i] = i < length - n ? s[i + n] : str[i - length + n];
        }
        return s;
    }
};
/* 新建结果字符串 */
class Solution {
public:
    string reverseLeftWords(string s, int n) {
        string res = "";
        for (int i = n; i < s.size(); i++) {
            res += s[i];
        }
        for (int i = 0; i < n; i++) {
            res += s[i];
        }
        return res;
    }
};

/* 59 I-滑动窗口的最大值 */
/* 滑动窗口，优先队列，最大堆 */
/* 注意堆中放pair存储元素以及位置 */
/* 并且同时保证最大值在滑动窗口中 */
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        if (nums.empty()) {
            return res;
        }
        priority_queue<pair<int, int>> que;
        for (int i = 0; i < k; i++) {
            que.push({nums[i], i});
        }
        res.push_back(que.top().first);
        for (int i = k; i < nums.size(); i++) {
            que.push({nums[i], i});
            while (que.top().second <= i - k) {
                que.pop();
            }
            res.push_back(que.top().first);
        }
        return res;
    }
};
/* 单调队列 */
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        if (nums.empty()) {
            return res;
        }
        deque<int> deq;
        for (int i = 0; i < k; i++) {
            while (!deq.empty() && nums[deq.back()] <= nums[i]) {
                deq.pop_back();
            }
            deq.push_back(i);
        }
        res.push_back(nums[deq.front()]);
        for (int i = k; i < nums.size(); i++) {
            while (!deq.empty() && nums[deq.back()] <= nums[i]) {
                deq.pop_back();
            }
            deq.push_back(i);
            while (deq.front() <= i - k) {
                deq.pop_front();
            }
            res.push_back(nums[deq.front()]);
        }
        return res;
    }
};

/* 59 II-队列的最大值 */
/* 单调队列 */
/* 与上一题不同的事单调队列中可以保存重复值 */
class MaxQueue {
public:
    queue<int> que;
    deque<int> deq;
    MaxQueue() {}

    int max_value() {
        if (que.empty()) {
            return -1;
        }
        return deq.front();
    }

    void push_back(int value) {
        que.push(value);
        while (!deq.empty() && deq.back() < value) {
            deq.pop_back();
        }
        deq.push_back(value);
    }

    int pop_front() {
        if (que.empty()) {
            return -1;
        }
        int value = que.front();
        que.pop();
        int count = 0;
        while (!deq.empty() && deq.front() <= value && count == 0) {
            deq.pop_front();
            count++;
        }
        return value;
    }
};
/* 优化上面代码 */
class MaxQueue {
public:
    queue<int> que;
    deque<int> deq;
    MaxQueue() {}

    int max_value() {
        if (que.empty()) {
            return -1;
        }
        return deq.front();
    }

    void push_back(int value) {
        que.push(value);
        while (!deq.empty() && deq.back() < value) {
            deq.pop_back();
        }
        deq.push_back(value);
    }

    int pop_front() {
        if (que.empty()) {
            return -1;
        }
        int value = que.front();
        que.pop();
        if (deq.front() == value) {
            deq.pop_front();
        }
        return value;
    }
};

/* 60 n个骰子的点数 */
/* 动态规划 */
class Solution {
public:
    vector<double> dicesProbability(int n) {
        vector<double> dp(6, 1.0 / 6.0);
        for (int i = 2; i <= n; i++) {
            vector<double> tmp(5 * i + 1, 0.0);
            for (int j = 0; j < dp.size(); j++) {
                for (int k = 0; k < 6; k++) {
                    tmp[j + k] += dp[j] / 6.0;
                }
            }
            dp = tmp;
        }
        return dp;
    }
};