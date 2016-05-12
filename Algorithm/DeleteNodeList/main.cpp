#include <iostream>

struct ListNode
{
	int val;
	ListNode *next;
	ListNode(int x):val(x),next(NULL){}
};

class Solution{
public:
	void deleteNode(ListNode *node){
		if(!node) return;
		ListNode *temp=new ListNode(1);
		temp=node->next;
		node->val=temp->val;
		node->next=temp->next;		
		delete temp;
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
	ListNode *n2=new ListNode(3);
	tail->next=n2;
	tail=tail->next;
	ListNode *n3=new ListNode(4);
	tail->next=n3;
	tail=tail->next;
	std::cout<<"Original linked list:";
	s.printList(print);
	std::cout<<"Revised linked list:";
	s.deleteNode(n1);
	s.printList(head);
}