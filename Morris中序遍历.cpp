/*
 * @Author: your name
 * @Date: 2021-04-28 11:32:49
 * @LastEditTime: 2021-04-28 20:50:00
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\Morris中序遍历.cpp
 */

/* 501题二叉搜索树中的众数 */
/* 二叉搜索树中序遍历为不减序列 */
class Solution {
public:
    vector<int> findMode(TreeNode* root) {
        vector<int> res;
        TreeNode* base = root;
        int count = 0;
        int maxcount = 0;
        stack<TreeNode*> stk;
        while (!stk.empty() || root != nullptr) {
            while (root != nullptr) {
                stk.push(root);
                root = root->left;
            }
            root = stk.top();
            stk.pop();
            if (root->val == base->val) {
                count++;
            } else {
                base = root;
                count = 1;
            }
            if (count > maxcount) {
                res.clear();
                res.push_back(root->val);
                maxcount = count;
            } else if (count == maxcount) {
                res.push_back(root->val);
            }
            root = root->right;
        }
        return res;
    }
};
/* Morris中序遍历 */
class Solution {
public:
    vector<int> res;
    int base;
    int maxcount = 0, count = 0;

    void update(int curVal) {
        if (curVal == base) {
            count++;
        } else {
            base = curVal;
            count = 1;
        }
        if (count > maxcount) {
            res.clear();
            res.push_back(curVal);
            maxcount = count;
        } else if (count == maxcount) {
            res.push_back(curVal);
        }
    }
    vector<int> findMode(TreeNode* root) {
        TreeNode *cur = root, *pre = nullptr;
        // base=root->val;
        while (cur != nullptr) {
            if (cur->left == nullptr) {
                update(cur->val);
                cur = cur->right;
            } else {
                pre = cur->left;
                while (pre->right != nullptr && pre->right != cur) {
                    pre = pre->right;
                }
                if (pre->right == nullptr) {
                    pre->right = cur;
                    cur = cur->left;
                } else {
                    pre->right = nullptr;
                    update(cur->val);
                    cur = cur->right;
                }
            }
        }
        return res;
    }
};

/* 99题恢复二叉搜索树 */
