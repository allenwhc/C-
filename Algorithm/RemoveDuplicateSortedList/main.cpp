#include <iostream>

struct ListNode
{
	int val;
	ListNode *next;
	ListNode(int x):val(x),next(NULL){}
};

class Solution{
public:
	ListNode* deleteDuplicates(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode *prev=head, *curr=head;
        while(curr){
        	while(curr->next && curr->next->val==curr->val) curr=curr->next;
        	prev->next=curr->next;
        	prev=prev->next;
        	curr=curr->next;
        }
        return head;
    }

    ListNode *deleteDuplicates2(ListNode *head){
    	if(!head || !head->next) return head;
    	ListNode *vHead=new ListNode(0);
    	vHead->next=head;
    	ListNode *curr=vHead;
    	while(curr->next and curr->next->next){
    		if(curr->next->val==curr->next->next->val){
    			int val=curr->next->val;
    			while(curr->next && curr->next->val==val) curr->next=curr->next->next;
    		}else{
    			curr=curr->next;
    		}
    	}
    	head=vHead->next;
    	delete vHead;
    	return head;
    }

    void printList(ListNode *head){
		while(head){
			std::cout<<head->val;
			head=head->next;
			if(head) std::cout<<"->";
		}
		std::cout<<std::endl;
	}
};

int main(int argc, char *argv[]){
	Solution s;
	ListNode *head=new ListNode(1);
	ListNode *tail=head, *print=head;
	ListNode *n1=new ListNode(2);
	tail->next=n1;
	tail=tail->next;
	ListNode *n2=new ListNode(2);
	tail->next=n2;
	tail=tail->next;
	// ListNode *n3=new ListNode(3);
	// tail->next=n3;
	// tail=tail->next;
	// ListNode *n4=new ListNode(3);
	// tail->next=n4;
	// tail=tail->next;
	std::cout<<"Original linked list:";
	s.printList(print);
	std::cout<<"Revised linked list:";
	s.printList(s.deleteDuplicates2(head));
	return 0;
}