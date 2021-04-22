/*
 * @Author: your name
 * @Date: 2021-04-22 22:44:08
 * @LastEditTime: 2021-04-22 23:41:27
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\二叉树的中序遍历与二叉搜索树.cpp
 */
/* 94题二叉树的中序遍历 */
/* 递归 */
class Solution {
    void inorder(TreeNode* root, vector<int>& res) {
        if (!root) {
            return;
        }
        inorder(root->left, res);
        res.push_back(root->val);
        inorder(root->right, res);
    }

public:
    vector<int> inorderTraversal(TreeNode* root) {
        // if(!root){return null;}
        vector<int> res;
        inorder(root, res);
        return res;
    }
};
/* 迭代 */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        if (root == nullptr) {
            return res;
        }
        stack<TreeNode*> stk;
        while (!stk.empty() || root != nullptr) {
            while (root != nullptr) {
                stk.push(root);
                root = root->left;
            }
            root = stk.top();
            stk.pop();
            res.push_back(root->val);
            root = root->right;
        }
        return res;
    }
};


/* 二叉搜索树中的搜索 */
/* 递归 */
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if(root==nullptr){return root;}
        if(root->val<val){
            return searchBST(root->right,val);
        }else if(root->val>val){
            return searchBST(root->left,val);
        }else{
            return root;
        }
    }
};
/* 迭代 */
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if(root==nullptr){return root;}
        while(root!=nullptr && root->val!=val){
            if(root->val<val){
                root=root->right;
            }else{
                root=root->left;
            }
        }
        return root;
    }
};