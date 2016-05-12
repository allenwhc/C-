#include <iostream>
#include <stack>

class MinStack{
	std::stack<int> minStack;
	std::stack<int> actualStack;
public:
	MinStack(){}
	void push(int x){
		actualStack.push(x);
		if(x<=getMin()) minStack.push(x);
	}
	void pop(){
		if(!actualStack.empty()){
			if(!minStack.empty() && minStack.top()==actualStack.top()) minStack.pop();
			actualStack.pop();
		}else{
			std::cout<<"Empty stack!"<<std::endl;
		}
	}
	int top(){
		return actualStack.empty()?INT_MAX:actualStack.top();
	}
	int getMin(){
		return minStack.empty()?INT_MAX:minStack.top();
	}
};

int main(int argc, char *argv[]){
	MinStack minStack;
	minStack.push(0);
	minStack.push(1);
	minStack.push(0);
	std::cout<<minStack.getMin()<<std::endl;   
	minStack.pop();
	//std::cout<<minStack.top()<<std::endl;      
	std::cout<<minStack.getMin()<<std::endl;   
}

