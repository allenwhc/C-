#include <iostream>

class Rectangle{
private:
	int width;
	int length;
public:
	Rectangle(){}
	Rectangle(int x, int y):width(x),length(y){}
	int girth(){return 2*(length+width);}
	int area(){return length*width;}
};

int main(void){
	//Raw pointer
	Rectangle *r1=new Rectangle(2,3);

	//Smart pointer
	std::unique_ptr<Rectangle> r2(new Rectangle(2,3));

	//print
	std::cout<<"Girth of rectangle: "<<r1->girth()<<std::endl;
	std::cout<<"Area of rectangle: "<<r2->area()<<std::endl;

	delete r1;	//Raw pointer needs release
	return 0;
}