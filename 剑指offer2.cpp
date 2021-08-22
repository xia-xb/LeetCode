/*
 * @Author: your name
 * @Date: 2021-08-18 23:31:07
 * @LastEditTime: 2021-08-22 23:55:19
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /LeetCode/剑指offer2.cpp
 */

/* 2 二进制加法 */
/* 模拟 */
class Solution {
public:
    char ans(char c1, char c2, int flag) {
        bool a1 = c1 == '1', a2 = c2 == '1', a3 = flag == 1;
        if (a1 ^ a2 ^ a3) {
            return '1';
        }
        return '0';
    }
    int carry(char c1, char c2, int flag) {
        bool a1 = c1 == '1', a2 = c2 == '1', a3 = flag == 1;
        if ((a1 && a2) || (a2 && a3) || (a1 && a3)) {
            return 1;
        }
        return 0;
    }
    string addBinary(string a, string b) {
        int i = a.size() - 1, j = b.size() - 1;
        int flag = 0;
        string res;
        while (i >= 0 && j >= 0) {
            char c1 = a[i--], c2 = b[j--];
            res += ans(c1, c2, flag);
            flag = carry(c1, c2, flag);
        }
        while (i >= 0) {
            res += ans(a[i], '0', flag);
            flag = carry(a[i--], '0', flag);
        }
        while (j >= 0) {
            res += ans(b[j], '0', flag);
            flag = carry(b[j--], '0', flag);
        }
        if (flag) {
            res += '1';
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
/* 代码优化 */
class Solution {
public:
    string addBinary(string a, string b) {
        int i = a.size() - 1, j = b.size() - 1;
        int carry = 0;
        string res;
        while (i >= 0 || j >= 0 || carry == 1) {
            int num1 = i >= 0 ? a[i] - '0' : 0;
            int num2 = j >= 0 ? b[j] - '0' : 0;
            int sum = num1 + num2 + carry;
            res += '0' + sum % 2;
            carry = sum / 2;
            i--;
            j--;
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

/* 3 前n个数字二进制中1的个数 */
/* 动态规划 */
/* 根据奇偶数的性质 */
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> dp(n + 1, 0);
        bool flag = true;
        for (int i = 1; i <= n; i++) {
            dp[i] = flag ? dp[i - 1] + 1 : dp[i / 2];
            flag = !flag;
        }
        return dp;
    }
};

/* 4 只出现一次的数字 */
/* 哈希表 */
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unordered_map<int, int> mp;
        for (int i = 0; i < nums.size(); i++) {
            mp[nums[i]]++;
        }
        for (auto it : mp) {
            if (it.second == 1) {
                return it.first;
            }
        }
        return 0;
    }
};
/* 统计各位1的个数，之后对3取余 */
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        int count[32] = {0};
        for (int i = 0; i < nums.size(); i++) {
            int num = nums[i];
            for (int j = 0; j < 32; j++) {
                count[j] += num & 1;
                num >>= 1;
            }
        }
        for (int i = 0; i < 32; i++) {
            res <<= 1;
            res |= count[31 - i] % 3;
        }
        return res;
    }
};

/* 43 往完全二叉树添加节点 */
/* 数组存储完全二叉树 */
/* 根据完全二叉树性质添加节点，得到父节点 */
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
class CBTInserter {
public:
    vector<TreeNode*> vec;
    CBTInserter(TreeNode* root) {
        queue<TreeNode*> que;
        if (root != nullptr) {
            que.push(root);
        }
        while (!que.empty()) {
            root = que.front();
            que.pop();
            vec.push_back(root);
            if (root->left != nullptr) {
                que.push(root->left);
            }
            if (root->right != nullptr) {
                que.push(root->right);
            }
        }
    }

    int insert(int v) {
        TreeNode* tmp = new TreeNode(v);
        vec.push_back(tmp);
        int length = vec.size();
        if (length % 2 == 1) {
            vec[length / 2 - 1]->right = tmp;
        } else {
            vec[length / 2 - 1]->left = tmp;
        }
        return vec[length / 2 - 1]->val;
    }

    TreeNode* get_root() { return vec.empty() ? nullptr : vec[0]; }
};
/* 队列存储左右节点存在空节点的节点 */
class CBTInserter {
public:
    TreeNode* rt;
    queue<TreeNode*> que;
    CBTInserter(TreeNode* root) {
        if (root == nullptr) {
            rt = nullptr;
            return;
        }
        rt = root;
        que.push(root);
        while (!que.empty()) {
            root = que.front();
            if (root->left == nullptr || root->right == nullptr) {
                if (root->left != nullptr) {
                    que.push(root->left);
                }
                break;
            }
            que.pop();
            que.push(root->left);
            que.push(root->right);
        }
    }

    int insert(int v) {
        TreeNode* newNode = new TreeNode(v);
        if (que.empty()) {
            rt = newNode;
            que.push(newNode);
            return 0;
        }
        que.push(newNode);
        TreeNode* it = que.front();
        if (it->left == nullptr) {
            it->left = newNode;
        } else {
            it->right = newNode;
            que.pop();
        }
        return it->val;
    }

    TreeNode* get_root() { return rt; }
};

/* 44 二叉树每层的最大值 */
/* 广度优先搜索 */
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
    vector<int> largestValues(TreeNode* root) {
        vector<int> res;
        queue<TreeNode*> que;
        if (root != nullptr) {
            que.push(root);
        }
        while (!que.empty()) {
            int num = que.size();
            int val = INT_MIN;
            while (num--) {
                TreeNode* it = que.front();
                que.pop();
                if (it->left != nullptr) {
                    que.push(it->left);
                }
                if (it->right != nullptr) {
                    que.push(it->right);
                }
                val = max(val, it->val);
            }
            res.push_back(val);
        }
        return res;
    }
};

/* 45 二叉树最底层最左边的值 */
/* 广度优先搜索 */
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
    int findBottomLeftValue(TreeNode* root) {
        int res;
        queue<TreeNode*> que;
        if (root != nullptr) {
            que.push(root);
        }
        while (!que.empty()) {
            int num = que.size();
            res = que.front()->val;
            while (num--) {
                TreeNode* it = que.front();
                que.pop();
                if (it->left != nullptr) {
                    que.push(it->left);
                }
                if (it->right != nullptr) {
                    que.push(it->right);
                }
            }
        }
        return res;
    }
};

/* 46 二叉树的右侧视图 */
/* 广度优先搜索 */
/* 每一层最右侧节点 */
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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        queue<TreeNode*> que;
        if (root != nullptr) {
            que.push(root);
        }
        while (!que.empty()) {
            int num = que.size();
            res.push_back(que.back()->val);
            while (num--) {
                TreeNode* it = que.front();
                que.pop();
                if (it->left != nullptr) {
                    que.push(it->left);
                }
                if (it->right != nullptr) {
                    que.push(it->right);
                }
            }
        }
        return res;
    }
};

/* 47 二叉树剪枝 */
/* 深度优先搜索 */
/* 注意在搜索的同时进行剪枝 */
/* 避免两次搜索 */
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
    bool isAviable(TreeNode* root) {
        if (root == nullptr) {
            return false;
        }
        bool left = isAviable(root->left);
        bool right = isAviable(root->right);
        if (!left) {
            root->left = nullptr;
        }
        if (!right) {
            root->right = nullptr;
        }
        return left || right || root->val == 1;
    }
    TreeNode* pruneTree(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }
        return isAviable(root) ? root : nullptr;
    }
};
/* 深度优先搜索 */
/* 后序遍历 */
class Solution {
public:
    TreeNode* pruneTree(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }
        root->left = pruneTree(root->left);
        root->right = pruneTree(root->right);
        if (root->val == 0 && root->left == nullptr && root->right == nullptr) {
            return nullptr;
        }
        return root;
    }
};

/* 48 序列化与反序列化二叉树 */
/* 深度优先搜索 */
class Codec {
public:
    void dfs(TreeNode* root, string& s) {
        if (root == NULL) {
            s += "null,";
        } else {
            s += to_string(root->val) + ',';
            dfs(root->left, s);
            dfs(root->right, s);
        }
    }
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string res;
        dfs(root, res);
        return res;
    }

    TreeNode* deser(queue<string>& que) {
        if (que.empty() || que.front() == "null") {
            que.pop();
            return NULL;
        }
        TreeNode* root = new TreeNode(stoi(que.front()));
        que.pop();
        root->left = deser(que);
        root->right = deser(que);
        return root;
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.empty()) {
            return NULL;
        }
        queue<string> que;
        string str;
        for (int i = 0; i < data.size(); i++) {
            if (data[i] == ',') {
                que.push(str);
                str.clear();
            } else {
                str += data[i];
            }
        }
        if (!str.empty()) {
            que.push(str);
            str.clear();
        }
        return deser(que);
    }
};
/* 广度优先搜索 */
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string res;
        if (root == NULL) {
            return res;
        }
        queue<TreeNode*> que;
        que.push(root);
        while (!que.empty()) {
            TreeNode* it = que.front();
            que.pop();
            if (it == NULL) {
                res += "null,";
            } else {
                res += to_string(it->val) + ',';
                que.push(it->left);
                que.push(it->right);
            }
        }
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.empty()) {
            return NULL;
        }
        queue<string> que;
        string str;
        for (int i = 0; i < data.size(); i++) {
            if (data[i] == ',') {
                que.push(str);
                str.clear();
            } else {
                str += data[i];
            }
        }
        if (!str.empty()) {
            que.push(str);
            str.clear();
        }
        TreeNode* root = new TreeNode(stoi(que.front()));
        que.pop();
        queue<TreeNode*> res;
        res.push(root);
        while (!res.empty()) {
            TreeNode* it = res.front();
            res.pop();
            if (que.front() != "null") {
                TreeNode* left = new TreeNode(stoi(que.front()));
                it->left = left;
                res.push(left);
            }
            que.pop();
            if (que.front() != "null") {
                TreeNode* right = new TreeNode(stoi(que.front()));
                it->right = right;
                res.push(right);
            }
            que.pop();
        }
        return root;
    }
};

/* 49 从根节点到叶节点的路径数字之和 */
/* 深度优先搜索 */
/* 注意结果保存在公共变量中 */
class Solution {
public:
    int res;
    void dfs(TreeNode* root, int sum) {
        if (root == nullptr) {
            res += sum;
            return;
        }
        sum *= 10;
        sum += root->val;
        if (root->left != nullptr) {
            dfs(root->left, sum);
        }
        if (root->right != nullptr) {
            dfs(root->right, sum);
        }
        if (root->left == nullptr && root->right == nullptr) {
            res += sum;
            return;
        }
    }
    int sumNumbers(TreeNode* root) {
        res = 0;
        dfs(root, 0);
        return res;
    }
};