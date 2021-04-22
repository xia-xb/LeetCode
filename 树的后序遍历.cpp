/*
 * @Author: your name
 * @Date: 2021-04-21 23:25:34
 * @LastEditTime: 2021-04-22 22:34:46
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\树的后序遍历.cpp
 */

/* 145题二叉树的后序遍历 */
/* 递归 */
class Solution {
public:
    vector<int> res;
    void post(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        post(root->left);
        post(root->right);
        res.push_back(root->val);
    }
    vector<int> postorderTraversal(TreeNode* root) {
        post(root);
        return res;
    }
};
/* 迭代 */
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        if (root == nullptr) {
            return res;
        }
        stack<TreeNode*> stk;
        TreeNode* pre = nullptr;
        while (!stk.empty() || root != nullptr) {
            while (root != nullptr) {
                stk.push(root);
                root = root->left;
            }
            root = stk.top();
            stk.pop();
            if (root->right == nullptr || root->right == pre) {
                res.push_back(root->val);
                pre = root;
                root = nullptr;
            } else {
                stk.push(root);
                root = root->right;
            }
        }
        return res;
    }
};

/* n叉树的后序遍历 */
/* 递归 */
class Solution {
public:
    vector<int> res;
    void post(Node* root) {
        if (root == nullptr) {
            return;
        }
        for (int i = 0; i < root->children.size(); i++) {
            post(root->children[i]);
        }
        res.push_back(root->val);
    }
    vector<int> postorder(Node* root) {
        post(root);
        return res;
    }
};
/* 迭代 */
class Solution {
public:
    vector<int> postorder(Node* root) {
        vector<int> res;
        if (root == nullptr) {
            return res;
        }
        stack<Node*> stk;
        stk.push(root);
        while (!stk.empty()) {
            root = stk.top();
            stk.pop();
            if (root != nullptr) {
                res.push_back(root->val);
                vector<Node*> tmp = root->children;
                if (!tmp.empty()) {
                    for (int i = 0; i < tmp.size(); i++) {
                        stk.push(tmp[i]);
                    }
                }
            }
        }
        reverse(res.begin(), res.end());
        return res;
    }
};