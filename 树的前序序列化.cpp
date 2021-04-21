/*
 * @Author: your name
 * @Date: 2021-04-21 21:53:46
 * @LastEditTime: 2021-04-21 22:23:23
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\树的前序序列化.cpp
 */
/* 606题根据二叉树创建字符串 */
/* 递归 */
class Solution {
public:
    string res;
    void tree(TreeNode* t){
        if(t==NULL){return;}
        res+=to_string(t->val);
        if(t->left!=NULL || t->right!=NULL){
            res+='(';
            tree(t->left);
            res+=')';
            if(t->right!=NULL){
                res+='(';
                tree(t->right);
                res+=')';
            }
        }
    }
    string tree2str(TreeNode* t) {
        tree(t);
        return res;
    }
};
