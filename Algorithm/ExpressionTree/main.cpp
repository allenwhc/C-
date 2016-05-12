#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

struct ExpressionTreeNode
{
	string symbol;
	ExpressionTreeNode *left, *right;
	ExpressionTreeNode(string s):symbol(s),left(NULL),right(NULL){}
};

class Solution{
private:
	bool is_number(const string &s){
		return !s.empty() && find_if(s.begin(), s.end(), [](const char c){return !isdigit(c);})==s.end();
	}
	
	int getPriority(string &e){
		if(e==")" || e=="(") return 0;
		else if(e=="+" || e=="-") return 1;
		else if(e=="*" || e=="/") return 2;
		else return INT_MAX;
	}
	
	ExpressionTreeNode *buildTree(vector<string> &preorder, vector<string> &inorder, int s, int e, int index){
		if(s>e) return NULL;
		ExpressionTreeNode* root=new ExpressionTreeNode(preorder[index]);
		int i=0;
		for(;i<inorder.size(); i++){
			if(inorder[i]==preorder[index]) break;
		}

		root->left=buildTree(preorder,inorder,s,i-1,index+1);
		root->right=buildTree(preorder, inorder, i+1, e, index+1+i-s);
		return root;
	}
	
	vector<string> convertToPreorder(vector<string> &expression){
		vector<string> res;
		stack<string> stk;
		reverse(expression.begin(), expression.end());
		for(auto &e: expression){
			if(is_number(e)) res.push_back(e);
			else if(e=="("){
				while(!stk.empty()){
					string s=stk.top();
					stk.pop();
					if(s==")") break;
					res.push_back(s);
				}
			}
			else if(e==")") stk.push(e);
			else{
				while(!stk.empty() && getPriority(e)<getPriority(stk.top())){
					res.push_back(stk.top());
					stk.pop();
				}
				stk.push(e);
			}
		}
		while(!stk.empty()){
			res.push_back(stk.top());
			stk.pop();
		}
		reverse(res.begin(),res.end());
		return res;
	}
	
public:
	ExpressionTreeNode *build(vector<string> &expression){
		if(expression.size()==0) return NULL;
		vector<string> inorder;
		for(auto &e: expression){
			if(e!="(" and e!=")") inorder.push_back(e);
		}
		cout<<inorder.size();
		for(auto &i: inorder) cout<<i<<" ";
		vector<string> preorder=convertToPreorder(expression);
		return buildTree(preorder, inorder, 0, (int)preorder.size()-1, 0);
	}
};

void printExpressionTree(ExpressionTreeNode *root, string indent){
	if(!root) return;
	printExpressionTree(root->right, indent+"   ");
	cout<<indent+root->symbol;
	printExpressionTree(root->left, indent+"   ");
}

int main(int argc, char *argv[]){
	vector<string> expression={"2","*","6","-","(", "23", "+", "7", ")", "/", "(", "1", "+", "2", ")"};
	Solution sol;
	cout<<"Expression tree of ";
	for (vector<string>::iterator it = expression.begin(); it != expression.end(); ++it)
	{
		cout<<*it<<" ";
	}
	cout<<" is: "<<endl;
	ExpressionTreeNode *root=sol.build(expression);
	printExpressionTree(root,"");
	return 0;
}