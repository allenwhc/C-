//
//  bubble.cpp
//  Sort
//
//  Created by Haochen Wang on 5/9/16.
//  Copyright © 2016 Haochen Wang. All rights reserved.
//

#include "interface.h"
class Bubble: public Sort{
private:
    std::vector<int> array;
    std::mutex mtx;
    std::condition_variable cond;
public:
    Bubble(std::vector<int> &a);
    void sorting();
};

Bubble::Bubble(std::vector<int>& a):array(a){}

void Bubble::sorting(){
    locker l(mtx);
    for (int i=0; i<array.size(); i++) {
        for(int j=i+1; j<array.size(); j++){
            if (array[j]<array[i]) {
                int temp=array[i];
                array[i]=array[j];
                array[j]=temp;
            }
        }
    }
    std::cout<<"Bubble sort: ";
    for(std::vector<int>::iterator it=array.begin(); it!=array.end(); it++)
        std::cout<<*it<<" ";
    std::cout<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}