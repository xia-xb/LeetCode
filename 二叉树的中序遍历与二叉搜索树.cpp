/*
 * @Author: your name
 * @Date: 2021-04-22 22:44:08
 * @LastEditTime: 2021-04-25 23:12:09
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

/* 173题二叉搜索树迭代器 */
/* 中序遍历 */
class BSTIterator {
public:
    vector<TreeNode*> vec;
    int position = 0;
    BSTIterator(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        stack<TreeNode*> stk;
        while (!stk.empty() || root != nullptr) {
            while (root != nullptr) {
                stk.push(root);
                root = root->left;
            }
            root = stk.top();
            stk.pop();
            vec.push_back(root);
            root = root->right;
        }
    }

    int next() {
        int pos = position;
        position++;
        return vec[pos]->val;
    }

    bool hasNext() { return position < vec.size(); }
};

/* 669题修剪二叉搜索树 */
/* 递归 */
class Solution {
public:
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if (root == nullptr) {
            return root;
        }
        if (root->val < low) {
            return trimBST(root->right, low, high);
        } else if (root->val > high) {
            return trimBST(root->left, low, high);
        } else {
            root->left = trimBST(root->left, low, high);
            root->right = trimBST(root->right, low, high);
            return root;
        }
    }
};

/* 450题删除二叉搜索树中的节点 */
/* 递归，需要实现删除最小结点，以及寻找最小结点 */
class Solution {
public:
    TreeNode* findmin(TreeNode* root) {
        if (root == nullptr) {
            return root;
        }
        if (root->left == nullptr) {
            return root;
        }
        return findmin(root->left);
    }
    TreeNode* findmax(TreeNode* root) {
        if (root == nullptr) {
            return root;
        }
        while (root->right != nullptr) {
            root = root->right;
        }
        return root;
    }
    TreeNode* deletedmin(TreeNode* root) {
        if (root == nullptr) {
            return root;
        }
        if (root->left == nullptr) {
            TreeNode* tmp = root->right;
            delete root;
            return tmp;
        } else {
            root->left = deletedmin(root->left);
            return root;
        }
    }
    TreeNode* deletemax(TreeNode* root) {
        if (root == nullptr) {
            return root;
        }
        if (root->right == nullptr) {
            TreeNode* tmp = root->left;
            delete root;
            return tmp;
        } else {
            root->right = deletemax(root->right);
            return root;
        }
    }
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) {
            return root;
        }
        if (root->val > key) {
            root->left = deleteNode(root->left, key);
        } else if (root->val < key) {
            root->right = deleteNode(root->right, key);
        } else {
            if (root->left == nullptr) {
                TreeNode* tmp = root->right;
                delete root;
                root = tmp;
            } else if (root->right == nullptr) {
                TreeNode* tmp = root->left;
                delete root;
                root = tmp;
            } else {
                root->val = findmin(root->right)->val;
                root->right = deletedmin(root->right);
            }
        }
        return root;
    }
};
/* 删除最大结点，寻找最大节点 */
class Solution {
public:
    TreeNode* findmin(TreeNode* root) {
        if (root == nullptr) {
            return root;
        }
        if (root->left == nullptr) {
            return root;
        }
        return findmin(root->left);
    }
    TreeNode* findmax(TreeNode* root) {
        if (root == nullptr) {
            return root;
        }
        while (root->right != nullptr) {
            root = root->right;
        }
        return root;
    }
    TreeNode* deletedmin(TreeNode* root) {
        if (root == nullptr) {
            return root;
        }
        if (root->left == nullptr) {
            TreeNode* tmp = root->right;
            delete root;
            return tmp;
        } else {
            root->left = deletedmin(root->left);
            return root;
        }
    }
    TreeNode* deletemax(TreeNode* root) {
        if (root == nullptr) {
            return root;
        }
        if (root->right == nullptr) {
            TreeNode* tmp = root->left;
            delete root;
            return tmp;
        } else {
            root->right = deletemax(root->right);
            return root;
        }
    }
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) {
            return root;
        }
        if (root->val > key) {
            root->left = deleteNode(root->left, key);
        } else if (root->val < key) {
            root->right = deleteNode(root->right, key);
        } else {
            if (root->left == nullptr) {
                TreeNode* tmp = root->right;
                delete root;
                root = tmp;
            } else if (root->right == nullptr) {
                TreeNode* tmp = root->left;
                delete root;
                root = tmp;
            } else {
                root->val = findmax(root->left)->val;
                root->left = deletemax(root->left);
            }
        }
        return root;
    }
};

/* 110题平衡二叉树 */
/* 递归 */
class Solution {
public:
    int high(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        return max(high(root->left), high(root->right)) + 1;
    }
    bool isBalanced(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }
        return isBalanced(root->left) && isBalanced(root->right) &&
               (abs(high(root->left) - high(root->right)) <= 1);
    }
};
/* 自底向上，避免重复计算子树高度 */
class Solution {
public:
    int height(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int leftheight = height(root->left);
        int rightheight = height(root->right);
        if (leftheight == -1 || rightheight == -1 ||
            abs(leftheight - rightheight) > 1) {
            return -1;
        } else {
            return max(leftheight, rightheight) + 1;
        }
    }
    bool isBalanced(TreeNode* root) { return height(root) != -1; }
};

/* 108题将有序数组转换为二叉搜索树 */
/* 平衡二叉树，递归 */
class Solution {
public:
    TreeNode* creatBST(vector<int> nums, int low, int high) {
        int length = high - low + 1;
        if (length <= 0) {
            return nullptr;
        } else if (length == 1) {
            return new TreeNode(nums[low], nullptr, nullptr);
        } else if (length == 2) {
            TreeNode* l = new TreeNode(nums[low], nullptr, nullptr);
            return new TreeNode(nums[high], l, nullptr);
        } else if (length == 3) {
            TreeNode* l = new TreeNode(nums[low], nullptr, nullptr);
            TreeNode* h = new TreeNode(nums[high], nullptr, nullptr);
            return new TreeNode(nums[low + 1], l, h);
        } else {
            TreeNode* l = creatBST(nums, low, low + length / 2 - 1);
            TreeNode* h = creatBST(nums, low + length / 2 + 1, high);
            return new TreeNode(nums[low + length / 2], l, h);
        }
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return creatBST(nums, 0, nums.size() - 1);
    }
};
/* 递归 */
class Solution {
public:
    TreeNode* creatBST(vector<int> nums, int low, int high) {
        if (low > high) {
            return nullptr;
        }
        int mid = (low + high) / 2;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = creatBST(nums, low, mid - 1);
        root->right = creatBST(nums, mid + 1, high);
        return root;
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return creatBST(nums, 0, nums.size() - 1);
    }
};

/* 109题有序链表转换二叉搜索树 */
/* 将链表存到数组 */
class Solution {
public:
    TreeNode* creatBST(vector<int> vec, int low, int high) {
        if (low > high) {
            return nullptr;
        }
        int mid = (low + high) / 2;
        TreeNode* root = new TreeNode(vec[mid]);
        root->left = creatBST(vec, low, mid - 1);
        root->right = creatBST(vec, mid + 1, high);
        return root;
    }
    TreeNode* sortedListToBST(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }
        vector<int> vec;
        while (head != nullptr) {
            vec.push_back(head->val);
            head = head->next;
        }
        return creatBST(vec, 0, vec.size() - 1);
    }
};
/* 分治，递归 */
/* 注意递归后干好指向中间结点，主要原因是左子树递归left,mid-1范围内，
且递归跳出的条件为left>right，从而left>mid-1,即left=mid，mid即为head */
class Solution {
public:
    int getLength(ListNode* head) {
        int length = 0;
        while (head != nullptr) {
            length++;
            head = head->next;
        }
        return length;
    }
    TreeNode* creatBST(ListNode*& head, int left, int right) {
        if (left > right) {
            return nullptr;
        }
        int mid = (left + right) / 2;
        TreeNode* root = new TreeNode();
        root->left = creatBST(head, left, mid - 1);
        root->val = head->val;
        head = head->next;
        root->right = creatBST(head, mid + 1, right);
        return root;
    }
    TreeNode* sortedListToBST(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }
        int length = getLength(head);
        return creatBST(head, 0, length - 1);
    }
};