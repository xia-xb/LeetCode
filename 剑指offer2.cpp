/*
 * @Author: your name
 * @Date: 2021-08-18 23:31:07
 * @LastEditTime: 2021-08-26 20:38:36
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
/* 队列存储左右节点存在空节点的节点 */
class CBTInserter {
public:
    TreeNode* rt;
    queue<TreeNode*> que;
    CBTInserter(TreeNode* root) {
        if (root == nullptr) {
            rt = nullptr;
            return;
        }
        rt = root;
        que.push(root);
        while (!que.empty()) {
            root = que.front();
            if (root->left == nullptr || root->right == nullptr) {
                if (root->left != nullptr) {
                    que.push(root->left);
                }
                break;
            }
            que.pop();
            que.push(root->left);
            que.push(root->right);
        }
    }

    int insert(int v) {
        TreeNode* newNode = new TreeNode(v);
        if (que.empty()) {
            rt = newNode;
            que.push(newNode);
            return 0;
        }
        que.push(newNode);
        TreeNode* it = que.front();
        if (it->left == nullptr) {
            it->left = newNode;
        } else {
            it->right = newNode;
            que.pop();
        }
        return it->val;
    }

    TreeNode* get_root() { return rt; }
};

/* 44 二叉树每层的最大值 */
/* 广度优先搜索 */
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
    vector<int> largestValues(TreeNode* root) {
        vector<int> res;
        queue<TreeNode*> que;
        if (root != nullptr) {
            que.push(root);
        }
        while (!que.empty()) {
            int num = que.size();
            int val = INT_MIN;
            while (num--) {
                TreeNode* it = que.front();
                que.pop();
                if (it->left != nullptr) {
                    que.push(it->left);
                }
                if (it->right != nullptr) {
                    que.push(it->right);
                }
                val = max(val, it->val);
            }
            res.push_back(val);
        }
        return res;
    }
};

/* 45 二叉树最底层最左边的值 */
/* 广度优先搜索 */
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
    int findBottomLeftValue(TreeNode* root) {
        int res;
        queue<TreeNode*> que;
        if (root != nullptr) {
            que.push(root);
        }
        while (!que.empty()) {
            int num = que.size();
            res = que.front()->val;
            while (num--) {
                TreeNode* it = que.front();
                que.pop();
                if (it->left != nullptr) {
                    que.push(it->left);
                }
                if (it->right != nullptr) {
                    que.push(it->right);
                }
            }
        }
        return res;
    }
};

/* 46 二叉树的右侧视图 */
/* 广度优先搜索 */
/* 每一层最右侧节点 */
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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        queue<TreeNode*> que;
        if (root != nullptr) {
            que.push(root);
        }
        while (!que.empty()) {
            int num = que.size();
            res.push_back(que.back()->val);
            while (num--) {
                TreeNode* it = que.front();
                que.pop();
                if (it->left != nullptr) {
                    que.push(it->left);
                }
                if (it->right != nullptr) {
                    que.push(it->right);
                }
            }
        }
        return res;
    }
};

/* 47 二叉树剪枝 */
/* 深度优先搜索 */
/* 注意在搜索的同时进行剪枝 */
/* 避免两次搜索 */
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
    bool isAviable(TreeNode* root) {
        if (root == nullptr) {
            return false;
        }
        bool left = isAviable(root->left);
        bool right = isAviable(root->right);
        if (!left) {
            root->left = nullptr;
        }
        if (!right) {
            root->right = nullptr;
        }
        return left || right || root->val == 1;
    }
    TreeNode* pruneTree(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }
        return isAviable(root) ? root : nullptr;
    }
};
/* 深度优先搜索 */
/* 后序遍历 */
class Solution {
public:
    TreeNode* pruneTree(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }
        root->left = pruneTree(root->left);
        root->right = pruneTree(root->right);
        if (root->val == 0 && root->left == nullptr && root->right == nullptr) {
            return nullptr;
        }
        return root;
    }
};

/* 48 序列化与反序列化二叉树 */
/* 深度优先搜索 */
class Codec {
public:
    void dfs(TreeNode* root, string& s) {
        if (root == NULL) {
            s += "null,";
        } else {
            s += to_string(root->val) + ',';
            dfs(root->left, s);
            dfs(root->right, s);
        }
    }
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string res;
        dfs(root, res);
        return res;
    }

    TreeNode* deser(queue<string>& que) {
        if (que.empty() || que.front() == "null") {
            que.pop();
            return NULL;
        }
        TreeNode* root = new TreeNode(stoi(que.front()));
        que.pop();
        root->left = deser(que);
        root->right = deser(que);
        return root;
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.empty()) {
            return NULL;
        }
        queue<string> que;
        string str;
        for (int i = 0; i < data.size(); i++) {
            if (data[i] == ',') {
                que.push(str);
                str.clear();
            } else {
                str += data[i];
            }
        }
        if (!str.empty()) {
            que.push(str);
            str.clear();
        }
        return deser(que);
    }
};
/* 广度优先搜索 */
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string res;
        if (root == NULL) {
            return res;
        }
        queue<TreeNode*> que;
        que.push(root);
        while (!que.empty()) {
            TreeNode* it = que.front();
            que.pop();
            if (it == NULL) {
                res += "null,";
            } else {
                res += to_string(it->val) + ',';
                que.push(it->left);
                que.push(it->right);
            }
        }
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.empty()) {
            return NULL;
        }
        queue<string> que;
        string str;
        for (int i = 0; i < data.size(); i++) {
            if (data[i] == ',') {
                que.push(str);
                str.clear();
            } else {
                str += data[i];
            }
        }
        if (!str.empty()) {
            que.push(str);
            str.clear();
        }
        TreeNode* root = new TreeNode(stoi(que.front()));
        que.pop();
        queue<TreeNode*> res;
        res.push(root);
        while (!res.empty()) {
            TreeNode* it = res.front();
            res.pop();
            if (que.front() != "null") {
                TreeNode* left = new TreeNode(stoi(que.front()));
                it->left = left;
                res.push(left);
            }
            que.pop();
            if (que.front() != "null") {
                TreeNode* right = new TreeNode(stoi(que.front()));
                it->right = right;
                res.push(right);
            }
            que.pop();
        }
        return root;
    }
};

/* 49 从根节点到叶节点的路径数字之和 */
/* 深度优先搜索 */
/* 注意结果保存在公共变量中 */
class Solution {
public:
    int res;
    void dfs(TreeNode* root, int sum) {
        if (root == nullptr) {
            res += sum;
            return;
        }
        sum *= 10;
        sum += root->val;
        if (root->left != nullptr) {
            dfs(root->left, sum);
        }
        if (root->right != nullptr) {
            dfs(root->right, sum);
        }
        if (root->left == nullptr && root->right == nullptr) {
            res += sum;
            return;
        }
    }
    int sumNumbers(TreeNode* root) {
        res = 0;
        dfs(root, 0);
        return res;
    }
};
/* 另一种写法 */
class Solution {
public:
    int dfs(TreeNode* root, int path) {
        if (root == nullptr) {
            return 0;
        }
        path *= 10;
        path += root->val;
        if (root->left == nullptr && root->right == nullptr) {
            return path;
        }
        return dfs(root->left, path) + dfs(root->right, path);
    }
    int sumNumbers(TreeNode* root) { return dfs(root, 0); }
};

/* 50 向下的路径节点之和 */
/* 前缀和，深度优先搜索 */
class Solution {
public:
    int dfs(TreeNode* root, int path, int target, unordered_map<int, int>& mp) {
        if (root == nullptr) {
            return 0;
        }
        path += root->val;
        int res = 0;
        if (mp.count(path - target)) {
            res += mp[path - target];
        }
        mp[path]++;
        res += dfs(root->left, path, target, mp);
        res += dfs(root->right, path, target, mp);
        mp[path]--;
        return res;
    }
    int pathSum(TreeNode* root, int targetSum) {
        unordered_map<int, int> mp;
        mp[0] = 1;
        return dfs(root, 0, targetSum, mp);
    }
};

/* 52 展平二叉搜索树 */
/* 中序遍历，设置pre节点 */
class Solution {
public:
    TreeNode* increasingBST(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }
        stack<TreeNode*> stk;
        TreeNode *it = root, *pre = nullptr;
        TreeNode* res = nullptr;
        while (!stk.empty() || it != nullptr) {
            while (it != nullptr) {
                stk.push(it);
                it = it->left;
            }
            it = stk.top();
            stk.pop();
            if (pre == nullptr) {
                res = it;
                pre = it;
            } else {
                pre->right = it;
                it->left = nullptr;
                pre = it;
            }
            it = it->right;
        }
        return res;
    }
};

/* 53 二叉搜索树中的中序后继 */
/* 深度优先搜索 */
/* 迭代方法 */
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if (root == NULL || p == NULL) {
            return NULL;
        }
        stack<TreeNode*> stk;
        TreeNode* pre = NULL;
        while (!stk.empty() || root != NULL) {
            while (root != NULL) {
                stk.push(root);
                root = root->left;
            }
            root = stk.top();
            stk.pop();
            if (pre == p) {
                return root;
            }
            pre = root;
            root = root->right;
        }
        return NULL;
    }
};

/* 54 所有大于等于节点的值之和 */
/* 中序遍历 */
/* 遍历两次，第一次遍历统计所有节点之和 */
class Solution {
public:
    int Sum(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        return root->val + Sum(root->left) + Sum(root->right);
    }

    void dfs(TreeNode* root, int& sum) {
        if (root == nullptr) {
            return;
        }
        dfs(root->left, sum);
        int tmp = root->val;
        root->val = sum;
        sum -= tmp;
        dfs(root->right, sum);
    }
    TreeNode* convertBST(TreeNode* root) {
        int sum = Sum(root);
        dfs(root, sum);
        return root;
    }
};
/* 深度优先搜索 */
/* 设置变量保存节点之和 */
/* 与中序遍历不同，先遍历右子树 */
/* 改变根节点的值 */
/* 之后再遍历左子树 */
class Solution {
public:
    int sum = 0;
    TreeNode* convertBST(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }
        convertBST(root->right);
        sum += root->val;
        root->val = sum;
        convertBST(root->left);
        return root;
    }
};

/* 55 二叉搜索树迭代器 */
/* 中序遍历，迭代方法 */
/* 通过栈存储节点 */
class BSTIterator {
public:
    TreeNode* rt;
    stack<TreeNode*> stk;
    BSTIterator(TreeNode* root) {
        rt = root;
        while (rt != nullptr) {
            stk.push(rt);
            rt = rt->left;
        }
    }

    int next() {
        rt = stk.top();
        stk.pop();
        int res = rt->val;
        rt = rt->right;
        while (rt != nullptr) {
            stk.push(rt);
            rt = rt->left;
        }
        return res;
    }

    bool hasNext() { return !stk.empty(); }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
/* 优化代码 */
class BSTIterator {
public:
    TreeNode* rt;
    stack<TreeNode*> stk;
    BSTIterator(TreeNode* root) { rt = root; }

    int next() {
        while (rt != nullptr) {
            stk.push(rt);
            rt = rt->left;
        }
        rt = stk.top();
        stk.pop();
        int res = rt->val;
        rt = rt->right;
        return res;
    }

    bool hasNext() { return !stk.empty() || rt != nullptr; }
};

/* 56 二叉搜索树中两个节点之和 */
/* 中序遍历 */
/* set存储所有节点的值 */
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        if (root == nullptr) {
            return false;
        }
        unordered_set<int> st;
        stack<TreeNode*> stk;
        while (!stk.empty() || root != nullptr) {
            while (root != nullptr) {
                stk.push(root);
                root = root->left;
            }
            root = stk.top();
            stk.pop();
            if (st.count(k - root->val)) {
                return true;
            }
            st.insert(root->val);
            root = root->right;
        }
        return false;
    }
};

/* 59 数据流的第K大数值 */
/* 优先队列，最小堆存储前K个数据 */
class KthLargest {
public:
    priority_queue<int, vector<int>, greater<int>> que;
    int capacity;
    KthLargest(int k, vector<int>& nums) {
        capacity = k;
        if (nums.empty()) {
            return;
        }
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int i = 0; i < k && n - i - 1 >= 0; i++) {
            que.push(nums[n - i - 1]);
        }
    }

    int add(int val) {
        if (que.size() < capacity) {
            que.push(val);
            return que.top();
        }
        if (val <= que.top()) {
            return que.top();
        }
        que.pop();
        que.push(val);
        return que.top();
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
/* 简化代码 */
class KthLargest {
public:
    priority_queue<int, vector<int>, greater<int>> que;
    int capacity;
    KthLargest(int k, vector<int>& nums) {
        capacity = k;
        for (int i = 0; i < nums.size(); i++) {
            que.push(nums[i]);
        }
    }

    int add(int val) {
        que.push(val);
        while (que.size() > capacity) {
            que.pop();
        }
        return que.top();
    }
};

/* 6 排序数组中两个数字之和 */
/* 双指针 */
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0, right = numbers.size() - 1;
        while (left < right) {
            int val = numbers[left] + numbers[right];
            if (val == target) {
                return {left, right};
            } else if (val < target) {
                left++;
            } else {
                right--;
            }
        }
        return {-1, -1};
    }
};

/* 7 数组中和为0的三个数 */
/* 双指针 */
/* 注意每一层中同一个元素只能使用一次，从而避免重复 */
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int i = 0; i < n - 2; i++) {
            if (i >= 1 && nums[i] == nums[i - 1]) {
                continue;
            }
            int target = -nums[i];
            if (nums[i + 1] + nums[i + 2] > target ||
                nums[n - 1] + nums[n - 2] < target) {
                continue;
            }
            int left = i + 1, right = n - 1;
            while (left < right) {
                int val = nums[left] + nums[right];
                if (val == target) {
                    int tmp = nums[left];
                    res.push_back({-target, nums[left], nums[right]});
                    while (left < right && nums[left] == tmp) {
                        left++;
                    }
                } else if (val < target) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        return res;
    }
};
/* 简化部分代码 */
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int i = 0; i < n - 2; i++) {
            if (i >= 1 && nums[i] == nums[i - 1]) {
                continue;
            }
            int target = -nums[i];
            if (nums[i + 1] + nums[i + 2] > target ||
                nums[n - 1] + nums[n - 2] < target) {
                continue;
            }
            int left = i + 1, right = n - 1;
            while (left < right) {
                int val = nums[left] + nums[right];
                if (val == target) {
                    res.push_back({-target, nums[left], nums[right]});
                    left++;
                    while (left < right && nums[left] == nums[left - 1]) {
                        left++;
                    }
                } else if (val < target) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        return res;
    }
};

/* 14 字符串中的变位词 */
/* 定长滑动窗口 */
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n = s1.size();
        unordered_map<char, int> needs;
        unordered_map<char, int> window;
        for (int i = 0; i < n; i++) {
            needs[s1[i]]++;
        }
        int match = 0, length = needs.size();
        for (int i = 0; i < n - 1 && i < s2.size(); i++) {
            char c = s2[i];
            if (needs.count(c)) {
                window[c]++;
                if (window[c] == needs[c]) {
                    match++;
                }
            }
        }
        for (int i = n - 1; i < s2.size(); i++) {
            char c = s2[i];
            if (needs.count(c)) {
                window[c]++;
                if (window[c] == needs[c]) {
                    match++;
                    if (match == length) {
                        return true;
                    }
                }
            }
            c = s2[i - n + 1];
            if (window.count(c)) {
                if (window[c] == needs[c]) {
                    match--;
                }
                window[c]--;
            }
        }
        return false;
    }
};
/* 只使用一个map */
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n = s1.size();
        unordered_map<char, int> needs;
        for (int i = 0; i < n; i++) {
            needs[s1[i]]++;
        }
        int match = 0, length = needs.size();
        for (int i = 0; i < n - 1 && i < s2.size(); i++) {
            char c = s2[i];
            if (needs.count(c)) {
                needs[c]--;
                if (needs[c] == 0) {
                    match++;
                }
            }
        }
        for (int i = n - 1; i < s2.size(); i++) {
            char c = s2[i];
            if (needs.count(c)) {
                needs[c]--;
                if (needs[c] == 0) {
                    match++;
                    if (match == length) {
                        return true;
                    }
                }
            }
            c = s2[i - n + 1];
            if (needs.count(c)) {
                if (needs[c] == 0) {
                    match--;
                }
                needs[c]++;
            }
        }
        return false;
    }
};

/* 18 有效的回文 */
/* 双指针 */
/* 注意区分字母和数字 */
class Solution {
public:
    bool isAviable(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
               (c >= '0' && c <= '9');
    }
    bool isChar(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }
    int toNum(char c) {
        if (c >= 'a' && c <= 'z') {
            return c - 'a';
        } else if (c >= 'A' && c <= 'Z') {
            return c - 'A';
        }
        return c - '0';
    }
    bool isPalindrome(string s) {
        int left = 0, right = s.size() - 1;
        while (left < right) {
            while (left < right && !isAviable(s[left])) {
                left++;
            }
            while (left < right && !isAviable(s[right])) {
                right--;
            }
            char c1 = s[left++], c2 = s[right--];
            if (isChar(c1) ^ isChar(c2) || toNum(c1) != toNum(c2)) {
                return false;
            }
        }
        return true;
    }
};

/* 19 最多删除一个字符得到回文 */
/* 双指针，递归 */
class Solution {
public:
    bool isPalindrome(string& s, int left, int right, bool flag) {
        if (left >= right) {
            return true;
        }
        return s[left] == s[right]
                   ? isPalindrome(s, left + 1, right - 1, flag)
                   : flag && (isPalindrome(s, left + 1, right, false) ||
                              isPalindrome(s, left, right - 1, false));
    }
    bool validPalindrome(string s) {
        return isPalindrome(s, 0, s.size() - 1, true);
    }
};

/* 21 删除链表的倒数第n个节点 */
/* 双指针 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* newhead = new ListNode(0, head);
        ListNode *p = newhead, *q = newhead;
        while (n-- >= 0) {
            p = p->next;
        }
        while (p != nullptr) {
            p = p->next;
            q = q->next;
        }
        q->next = q->next->next;
        return newhead->next;
    }
};

/* 22 链表中环的入口节点 */
/* 双指针 */
class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        ListNode *p = head, *q = head;
        while (q != nullptr) {
            q = q->next;
            if (q != nullptr) {
                q = q->next;
            }
            p = p->next;
            if (p == q) {
                break;
            }
        }
        if (q == nullptr) {
            return nullptr;
        }
        p = head;
        while (p != q) {
            p = p->next;
            q = q->next;
        }
        return p;
    }
};

/* 23 两个链表的第一个重合节点 */
/* 双指针 */
class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        ListNode *p = headA, *q = headB;
        while (p != NULL && q != NULL) {
            p = p->next;
            q = q->next;
        }
        if (p == NULL) {
            p = headB;
            while (q != NULL) {
                p = p->next;
                q = q->next;
            }
            q = headA;
        } else {
            q = headA;
            while (p != NULL) {
                p = p->next;
                q = q->next;
            }
            p = headB;
        }
        while (p != NULL && q != NULL && p != q) {
            p = p->next;
            q = q->next;
        }
        return p;
    }
};

/* 26 重排链表 */
/* 双指针 */
/* 先将链表分为两个子链表 */
/* 后一个链表反序 */
/* 两个链表合并 */
/* 注意链表长度为1和2的情况 */
class Solution {
public:
    void reorderList(ListNode* head) {
        if (head->next == nullptr || head->next->next == nullptr) {
            return;
        }
        ListNode *p = head, *q = head;
        while (q != nullptr && q->next != nullptr) {
            p = p->next;
            q = q->next->next;
        }
        q = p->next;
        p->next = nullptr;
        p = q->next;
        q->next = nullptr;
        while (p != nullptr) {
            ListNode* tmp = p->next;
            p->next = q;
            q = p;
            p = tmp;
        }
        p = head;
        while (q != nullptr) {
            ListNode* tmp = q->next;
            q->next = p->next;
            p->next = q;
            p = p->next->next;
            q = tmp;
        }
    }
};

/* 77 链表排序 */
/* 链表归并排序 */
class Solution {
public:
    ListNode* sortList(ListNode* head) { return sortList(head, nullptr); }

    ListNode* sortList(ListNode* head, ListNode* tail) {
        if (head == nullptr) {
            return nullptr;
        }
        if (head->next == tail) {
            head->next = nullptr;
            return head;
        }
        ListNode *fast = head, *slow = head;
        while (fast != tail) {
            slow = slow->next;
            fast = fast->next;
            if (fast != tail) {
                fast = fast->next;
            }
        }
        ListNode* mid = slow;
        return merge(sortList(head, mid), sortList(mid, tail));
    }

    ListNode* merge(ListNode* head1, ListNode* head2) {
        ListNode* newhead = new ListNode();
        ListNode* tail = newhead;
        while (head1 != nullptr && head2 != nullptr) {
            if (head1->val <= head2->val) {
                tail->next = head1;
                head1 = head1->next;
            } else {
                tail->next = head2;
                head2 = head2->next;
            }
            tail = tail->next;
        }
        if (head1 != nullptr) {
            tail->next = head1;
        }
        if (head2 != nullptr) {
            tail->next = head2;
        }
        return newhead->next;
    }
};