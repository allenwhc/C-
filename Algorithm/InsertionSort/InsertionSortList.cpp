#include <iostream>

struct ListNode{
	int val;
	ListNode *next;
	ListNode(int x):val(x),next(NULL){}
};

class Solution{
private:
	ListNode *insert_node;
public:
	Solution(){
		insert_node=new ListNode(INT_MIN);
	}
	ListNode *insertionSortList(ListNode *head){
		if(!head || !head->next) return head;
		ListNode *curr=insert_node;
		ListNode *temp=NULL;
		while(head){
			if(curr->val > head->val) curr=insert_node;
			while(curr->next && curr->next->val < head->val) curr=curr->next;
			temp=head->next;
			head->next=curr->next;
			curr->next=head;
			head=temp;
		}
		return insert_node->next;
	}
	~Solution(){
		delete insert_node;
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
	ListNode *head=new ListNode(5);
	ListNode *tail=head, *print=head;
	ListNode *n1=new ListNode(-3);
	tail->next=n1;
	tail=tail->next;
	ListNode *n2=new ListNode(1);
	tail->next=n2;
	tail=tail->next;
	ListNode *n3=new ListNode(7);
	tail->next=n3;
	tail=tail->next;
	ListNode *n4=new ListNode(10);
	tail->next=n4;
	tail=tail->next;
	ListNode *n5=new ListNode(2);
	tail->next=n5;
	tail=tail->next;
	std::cout<<"Original linked list:";
	s.printList(print);
	std::cout<<"Sorted linked list:";
	s.printList(s.insertionSortList(head));
}