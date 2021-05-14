/*
 * @Author: your name
 * @Date: 2021-05-14 22:26:30
 * @LastEditTime: 2021-05-14 22:59:42
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LeetCode\高精度加法.cpp
 */


/* 2题两数相加 */
/* 直接相加，注意进位 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* sum=new ListNode();
        ListNode* p=sum;
        int carry=0;
        while(l1!=nullptr && l2!=nullptr){
            int s=l1->val+l2->val+carry;
            p->next=new ListNode(s%10);
            p=p->next;
            carry=s>=10 ? 1:0;
            l1=l1->next;
            l2=l2->next;
        }
        while(l1!=nullptr){
            int s=l1->val+carry;
            p->next=new ListNode(s%10);
            p=p->next;
            carry=s>=10 ? 1:0;
            l1=l1->next;
        }
        while(l2!=nullptr){
            int s=l2->val+carry;
            p->next=new ListNode(s%10);
            p=p->next;
            carry=s>=10 ? 1:0;
            l2=l2->next;
        }
        if(carry==1){
            p->next=new ListNode(carry);
        }
        return sum->next;
    }
};


/* 445题两数相加II */
/* 先将两个链表反转，之后相加， */
/* 相加结果直接头插法，即为倒序链表 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* newl1=new ListNode();
        ListNode* newl2=new ListNode();
        ListNode* next;
        while(l1!=NULL){
            next=l1->next;
            l1->next=newl1->next;
            newl1->next=l1;
            l1=next;
        }
        while(l2!=NULL){
            next=l2->next;
            l2->next=newl2->next;
            newl2->next=l2;
            l2=next;
        }
        l1=newl1->next;
        l2=newl2->next;
        ListNode* res=new ListNode();
        int carry=0;
        int sum;
        while(l1!=NULL && l2!=NULL){
            sum=l1->val+l2->val+carry;
            res->next=new ListNode(sum%10,res->next);
            carry=sum/10;
            l1=l1->next;
            l2=l2->next;
        }
        while(l1!=NULL){
            sum=l1->val+carry;
            res->next=new ListNode(sum%10,res->next);
            carry=sum/10;
            l1=l1->next;
        }
        while(l2!=NULL){
            sum=l2->val+carry;
            res->next=new ListNode(sum%10,res->next);
            carry=sum/10;
            l2=l2->next;
        }
        if(carry){
            res->next=new ListNode(carry,res->next);
        }        
        return res->next;
    }
};
/* 利用栈存储两个链表中的数字 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        stack<int>s1,s2;
        while(l1!=NULL){
            s1.push(l1->val);
            l1=l1->next;
        }
        while(l2!=NULL){
            s2.push(l2->val);
            l2=l2->next;
        }
        ListNode* res=new ListNode();
        int carry=0;
        int sum;
        while(!s1.empty() && !s2.empty()){
            sum=s1.top()+s2.top()+carry;
            res->next=new ListNode(sum%10,res->next);
            carry=sum/10;
            s1.pop();
            s2.pop();
        }
        while(!s1.empty()){
            sum=s1.top()+carry;
            res->next=new ListNode(sum%10,res->next);
            carry=sum/10;
            s1.pop();
        }
        while(!s2.empty()){
            sum=s2.top()+carry;
            res->next=new ListNode(sum%10,res->next);
            carry=sum/10;
            s2.pop();
        }
        if(carry){
            res->next=new ListNode(carry,res->next);
        }        
        return res->next;
    }
};