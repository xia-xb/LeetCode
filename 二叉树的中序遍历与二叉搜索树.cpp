/*
 * @Author: your name
 * @Date: 2021-04-22 22:44:08
 * @LastEditTime: 2021-04-23 22:42:56
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
        if (root == nullptr) {
            return root;
        }
        if (root->val < val) {
            return searchBST(root->right, val);
        } else if (root->val > val) {
            return searchBST(root->left, val);
        } else {
            return root;
        }
    }
};
/* 迭代 */
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if (root == nullptr) {
            return root;
        }
        while (root != nullptr && root->val != val) {
            if (root->val < val) {
                root = root->right;
            } else {
                root = root->left;
            }
        }
        return root;
    }
};

/* 530题二叉搜索树的最小绝对差 */
/* 迭代，利用二叉搜索树中序遍历递增性质 */
class Solution {
public:
    int getMinimumDifference(TreeNode* root) {
        int res;
        if (root->left != nullptr) {
            res = abs(root->val - root->left->val);
        }
        if (root->right != nullptr) {
            res = abs(root->val - root->right->val);
        }
        TreeNode* pre = nullptr;
        stack<TreeNode*> stk;
        while (!stk.empty() || root != nullptr) {
            while (root != nullptr) {
                stk.push(root);
                root = root->left;
            }
            root = stk.top();
            stk.pop();
            if (pre != nullptr) res = min(res, abs(pre->val - root->val));
            pre = root;
            root = root->right;
        }
        return res;
    }
};

/* 538题把二叉搜索树转换为累加树 */
/* 中序遍历二叉搜索树为递增序列 */
class Solution {
public:
    TreeNode* convertBST(TreeNode* root) {
        if (root == nullptr) {
            return root;
        }
        vector<TreeNode*> vec;
        stack<TreeNode*> stk;
        TreeNode* tmp = root;
        int sum = 0;
        while (!stk.empty() || tmp != nullptr) {
            while (tmp != nullptr) {
                stk.push(tmp);
                tmp = tmp->left;
            }
            tmp = stk.top();
            stk.pop();
            sum += tmp->val;
            vec.push_back(tmp);
            tmp = tmp->right;
        }
        int j;
        for (int i = 0; i < vec.size(); i++) {
            j = vec[i]->val;
            vec[i]->val = sum;
            sum -= j;
        }
        return root;
    }
};
/* 中序逆序遍历二叉搜索树为递减序列 */
class Solution {
public:
    int sum = 0;
    TreeNode* convertBST(TreeNode* root) {
        if (root == nullptr) {
            return root;
        }
        convertBST(root->right);
        sum += root->val;
        root->val = sum;
        convertBST(root->left);
        return root;
    }
};

/* 230题二叉搜索树中第k小的元素 */
/* 二叉搜索树中序遍历为递增序列 */
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> stk;
        int count = 0;
        int res;
        while (!stk.empty() || root != nullptr) {
            while (root != nullptr) {
                stk.push(root);
                root = root->left;
            }
            root = stk.top();
            stk.pop();
            count++;
            if (count == k) {
                res = root->val;
                break;
            }
            root = root->right;
        }
        return res;
    }
};
/* 递归 */
class Solution {
public:
    int res;
    void inorder(TreeNode* root, int& k) {
        if (root == nullptr) {
            return;
        }
        inorder(root->left, k);
        if (--k == 0) {
            res = root->val;
        } else {
            inorder(root->right, k);
        }
    }
    int kthSmallest(TreeNode* root, int k) {
        inorder(root, k);
        return res;
    }
};

/* 98题验证二叉搜索树 */
/* 中序遍历 */
class Solution {
public:
    bool res = true;
    TreeNode* pre = nullptr;
    void inorder(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        inorder(root->left);
        if (pre != nullptr && pre->val >= root->val) {
            res = false;
        }
        pre = root;
        inorder(root->right);
    }
    bool isValidBST(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }
        inorder(root);
        return res;
    }
};