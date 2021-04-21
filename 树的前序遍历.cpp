/*
 * @Author: your name
 * @Date: 2021-04-21 20:52:44
 * @LastEditTime: 2021-04-21 21:53:27
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\树的前序遍历.cpp
 */

/* 144题二叉树的前序遍历 */
/* 递归 */
class Solution {
public:
    vector<int> res;
    void pre(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        res.push_back(root->val);
        pre(root->left);
        pre(root->right);
    }
    vector<int> preorderTraversal(TreeNode* root) {
        pre(root);
        return res;
    }
};
/* 迭代 */
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        if (root == nullptr) {
            return res;
        }
        stack<TreeNode*> stk;
        while (!stk.empty() || root != nullptr) {
            while (root != nullptr) {
                res.push_back(root->val);
                stk.push(root);
                root = root->left;
            }
            root = stk.top();
            stk.pop();
            root = root->right;
        }
        return res;
    }
};



/* 589题n叉树的前序遍历 */
/* 递归 */
class Solution {
public:
    vector<int> res;
    void pre(Node* root) {
        if (root == nullptr) {
            return;
        }
        res.push_back(root->val);
        for (vector<Node*>::iterator it = root->children.begin();
             it != root->children.end(); it++) {
            pre(*it);
        }
    }
    vector<int> preorder(Node* root) {
        pre(root);
        return res;
    }
};
/* 迭代 */
class Solution {
public:
    vector<int> preorder(Node* root) {
        vector<int> res;
        if (root == nullptr) {
            return res;
        }
        stack<Node*> stk;
        stk.push(root);
        while (!stk.empty()) {
            root = stk.top();
            stk.pop();
            res.push_back(root->val);
            for (int i = root->children.size() - 1; i >= 0; i--) {
                stk.push(root->children[i]);
            }
        }
        return res;
    }
};

