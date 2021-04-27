/*
 * @Author: your name
 * @Date: 2021-04-27 19:27:35
 * @LastEditTime: 2021-04-27 20:45:57
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\最近公共祖先.cpp
 */

/* 235题二叉搜索树的最近公共祖先 */
/* 确定各自路径 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr) {
            return nullptr;
        }
        vector<TreeNode*> pathtoP;
        vector<TreeNode*> pathtoQ;
        TreeNode* tmp = root;
        while (tmp != p) {
            pathtoP.push_back(tmp);
            tmp = tmp->val < p->val ? tmp->right : tmp->left;
        }
        pathtoP.push_back(p);
        tmp = root;
        while (tmp != q) {
            pathtoQ.push_back(tmp);
            tmp = tmp->val < q->val ? tmp->right : tmp->left;
        }
        pathtoQ.push_back(q);
        int i = 0;
        for (; i < pathtoP.size() && i < pathtoQ.size() &&
               pathtoP[i] == pathtoQ[i];
             i++) {
        }
        return pathtoP[i - 1];
    }
};
/* 一次遍历，利用二叉搜索树性质*/
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr) {
            return nullptr;
        }
        int pval = p->val, qval = q->val;
        while (1) {
            if (root->val < pval && root->val < qval) {
                root = root->right;
            } else if (root->val > pval && root->val > qval) {
                root = root->left;
            } else {
                break;
            }
        }
        return root;
    }
};

/* 236题二叉搜索树的最近公共祖先 */
/* 深度优先搜索DFS */
/* 最近公共祖先可以表示为 */
/* 左子树为p或q祖先，且右子树为p或q祖先 */
/* 或者可以表示为，自身即为p或q */
/* 左或右子树为q或p的祖先 */
/* 注意，p和q为不同结点 */
class Solution {
public:
    TreeNode* ans;
    bool dfs(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr) {
            return false;
        }
        bool inCurrentNode = root == p || root == q;
        bool inLeft = dfs(root->left, p, q);
        bool inRight = dfs(root->right, p, q);
        if ((inLeft && inRight) || (inCurrentNode && (inLeft || inRight))) {
            ans = root;
        }
        return inCurrentNode || inLeft || inRight;
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr) {
            return root;
        }
        dfs(root, p, q);
        return ans;
    }
};