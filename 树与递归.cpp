/*
 * @Author: your name
 * @Date: 2021-07-12 21:21:23
 * @LastEditTime: 2021-07-12 21:58:16
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /LeetCode/树与递归.cpp
 */

/* 100题相同的树 */
/* 递归 */
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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == nullptr && q == nullptr) {
            return true;
        }
        if (p == nullptr || q == nullptr) {
            return false;
        }
        if (p->val != q->val) {
            return false;
        }
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};
/* 广度优先搜索 */
/* 队列 */
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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == nullptr && q == nullptr) {
            return true;
        }
        if (p == nullptr || q == nullptr) {
            return false;
        }
        queue<TreeNode*> que1, que2;
        que1.push(p);
        que2.push(q);
        while (!que1.empty() && !que2.empty()) {
            p = que1.front();
            que1.pop();
            q = que2.front();
            que2.pop();
            if (p->val != q->val) {
                return false;
            }
            TreeNode *left1 = p->left, *right1 = p->right, *left2 = q->left,
                     *right2 = q->right;
            if ((left1 == nullptr) ^ (left2 == nullptr)) {
                return false;
            }
            if ((right1 == nullptr) ^ (right2 == nullptr)) {
                return false;
            }
            if (left1 != nullptr) {
                que1.push(left1);
                que2.push(left2);
            }
            if (right1 != nullptr) {
                que1.push(right1);
                que2.push(right2);
            }
        }
        return que1.empty() && que2.empty();
    }
};

/* 222题完全二叉树的节点个数 */
/* 深度优先搜索 */
/* 递归 */
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
    int countNodes(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};
/* 广度优先搜索，队列 */
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
    int countNodes(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int res = 0;
        queue<TreeNode*> que;
        que.push(root);
        while (!que.empty()) {
            root = que.front();
            que.pop();
            res++;
            if (root->left != nullptr) {
                que.push(root->left);
            }
            if (root->right != nullptr) {
                que.push(root->right);
            }
        }
        return res;
    }
};

/* 101题对称二叉树 */
/* 深度优先搜索，递归 */
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
    bool isSymmetricTwoTreeNode(TreeNode* root1, TreeNode* root2) {
        if (root1 == nullptr && root2 == nullptr) {
            return true;
        }
        if (root1 == nullptr || root2 == nullptr) {
            return false;
        }
        if (root1->val != root2->val) {
            return false;
        }
        return isSymmetricTwoTreeNode(root1->left, root2->right) &&
               isSymmetricTwoTreeNode(root1->right, root2->left);
    }
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }
        return isSymmetricTwoTreeNode(root->left, root->right);
    }
};
