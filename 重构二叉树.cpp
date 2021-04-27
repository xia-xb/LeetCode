/*
 * @Author: your name
 * @Date: 2021-04-25 23:12:52
 * @LastEditTime: 2021-04-27 16:05:13
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\重构二叉树.cpp
 */

/* 105题从前序和中序遍历序列构造二叉树 */
/* 根据前、中序序列性质
前序  【根，【左子树】，【右子树】】
中序  【【左子树】，根，【右子树】】
根据前序确定根，再在中序中找到根，
由此可以确定左、右子树的序列，
从而递归构造二叉树*/
class Solution {
public:
    unordered_map<int, int> index;
    TreeNode* build(vector<int>& preorder, vector<int>& inorder,
                    int preorderLeft, int preorderRight, int inorderLeft,
                    int inorderRight) {
        if (preorderLeft > preorderRight) {
            return nullptr;
        }
        int preorderRoot = preorderLeft;
        int inorderRoot = index[preorder[preorderRoot]];

        TreeNode* root = new TreeNode(preorder[preorderRoot]);
        int leftsubtreeSize = inorderRoot - inorderLeft;
        root->left =
            build(preorder, inorder, preorderLeft + 1,
                  preorderLeft + leftsubtreeSize, inorderLeft, inorderRoot - 1);
        root->right =
            build(preorder, inorder, preorderLeft + leftsubtreeSize + 1,
                  preorderRight, inorderRoot + 1, inorderRight);
        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        for (int i = 0; i < n; i++) {
            index.insert(make_pair(inorder[i], i));
        }
        TreeNode* root = build(preorder, inorder, 0, n - 1, 0, n - 1);
        return root;
    }
};
/* 迭代 */

/* 106题从中序与后序遍历序列构造二叉树 */
/* 思路与105题前、中序构造二叉树类似 */
class Solution {
public:
    unordered_map<int, int> index;
    TreeNode* build(vector<int>& inorder, vector<int>& postorder,
                    int inorderLeft, int inorderRight, int postorderLeft,
                    int postorderRight) {
        if (inorderLeft > inorderRight) {
            return nullptr;
        }
        int postorderRoot = postorderRight;
        int inorderRoot = index[postorder[postorderRoot]];

        TreeNode* root = new TreeNode(postorder[postorderRoot]);
        int leftsubtreeSize = inorderRoot - inorderLeft;
        root->left = build(inorder, postorder, inorderLeft, inorderRoot - 1,
                           postorderLeft, postorderLeft + leftsubtreeSize - 1);
        root->right = build(inorder, postorder, inorderRoot + 1, inorderRight,
                            postorderLeft + leftsubtreeSize, postorderRoot - 1);
        return root;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = inorder.size();
        for (int i = 0; i < n; i++) {
            index[inorder[i]] = i;
        }
        return build(inorder, postorder, 0, n - 1, 0, n - 1);
    }
};
/* 迭代 */
