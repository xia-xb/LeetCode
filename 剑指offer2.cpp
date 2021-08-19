/*
 * @Author: your name
 * @Date: 2021-08-18 23:31:07
 * @LastEditTime: 2021-08-20 00:01:28
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
