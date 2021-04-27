/*
 * @Author: your name
 * @Date: 2021-04-27 18:53:04
 * @LastEditTime: 2021-04-27 19:27:07
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\二叉树的展开.cpp
 */


/* 114题二叉树展开为链表 */
/* 前序遍历，注意保存右子树 */
class Solution {
public:
    void flatten(TreeNode* root) {
        if(root==nullptr){return;}
        stack<TreeNode*>stk;
        TreeNode* newroot=root;
        TreeNode* pre=nullptr;
        stk.push(newroot);
        while(!stk.empty()){
            newroot=stk.top();
            stk.pop();
            if(pre!=nullptr){
                pre->left=nullptr;
                pre->right=newroot;
            }
            if(newroot->right!=nullptr){stk.push(newroot->right);}
            if(newroot->left!=nullptr){stk.push(newroot->left);}
            pre=newroot;
        }
    }
};
/* 前驱结点 */
/* 若结点左子树不为空，则需要找到右子树的前驱结点 */
/* 前驱结点即为左子树中最右的结点 */
class Solution {
public:
    void flatten(TreeNode* root) {
        if(root==nullptr){return;}
        TreeNode* current=root;
        while(current!=nullptr){
            if(current->left!=nullptr){
                TreeNode* next=current->left;
                TreeNode* precessor=next;
                while(precessor->right!=nullptr){
                    precessor=precessor->right;
                }
                precessor->right=current->right;
                current->right=next;
                current->left=nullptr;
            }
            current=current->right;
        }
    }
};
/* 递归 */
class Solution {
public:
    void flatten(TreeNode* root) {
        if(root==nullptr){return;}
        TreeNode* right=root->right;
        flatten(root->left);
        root->right=root->left;
        root->left=nullptr;
        while(root->right!=nullptr){
            root=root->right;
        }
        flatten(right);
        root->right=right;      
    }
};