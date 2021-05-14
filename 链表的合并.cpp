/*
 * @Author: your name
 * @Date: 2021-05-14 23:00:04
 * @LastEditTime: 2021-05-14 23:06:51
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\链表的合并.cpp
 */


/* 21题合并两个有序链表 */
/* 直接合并 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* head=new ListNode(-1);
        ListNode* tail=head;
        while(l1 && l2){
            if((l1->val)<=(l2->val)){
                tail->next=l1;
                l1=l1->next;
            }else{
                tail->next=l2;
                l2=l2->next;
            }
            tail=tail->next;
        }
        if(l1 || l2){
            tail->next=l1 ? l1:l2;
        }
        return head->next;
    }
};
/* 修改 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* res=new ListNode();
        ListNode* tail=res;
        while(l1!=nullptr && l2!=nullptr){
            while(l1!=nullptr && l1->val <=l2->val){
                tail->next=l1;
                tail=tail->next;
                l1=l1->next;
            }
            tail->next=l2;
            tail=tail->next;
            l2=l2->next;
        }
        if(l1!=nullptr){tail->next=l1;}
        if(l2!=nullptr){tail->next=l2;}
        return res->next;
    }
};