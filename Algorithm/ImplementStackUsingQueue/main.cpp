#include <iostream>
#include <queue>


class Stack{
private:
	std::queue<int> q1;	//Actual stack
	std::queue<int> q2;	//Supplementary queue
public:
	// Push element x onto stack.
    void push(int x) {
        q2.push(x);
        while(!q1.empty()){
        	q2.push(q1.front());
        	q1.pop();
        }
        std::queue<int> temp=q2;
        q2=q1;
        q1=temp;
    }

    // Removes the element on top of the stack.
    void pop() {
        if(q1.size()>0) q1.pop();
        else if(q2.size()>0) q2.pop();
    }

    // Get the top element.
    int top() {
        if(q1.size()>0) return q1.front();
        else if(q2.size()>0) return q2.front();
        else return 0;
    }

    // Return whether the stack is empty.
    bool empty() {
        return q1.empty() && q2.empty();
    }
};

int main(int argc, char *argv[]){


	return 0;
}