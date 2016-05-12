//
//  selection.cpp
//  Sort
//
//  Created by Haochen Wang on 5/9/16.
//  Copyright © 2016 Haochen Wang. All rights reserved.
//

#include <stdio.h>
#include "interface.h"
//Selection sort
class Selection: public Sort{
private:
    std::vector<int> array;
    std::mutex mtx;
public:
    Selection(std::vector<int> &a):array(a){}
    void sorting(){
        locker l(mtx);
        for (int i=0; i<array.size(); i++) {
            int min=i;
            for(int j=i+1; j<array.size(); j++){
                if(array[j]<array[min])
                    min=j;
            }
            if (min!=i) std::swap(array[min], array[i]);
        }
        std::cout<<"Selection sort: ";
        for(std::vector<int>::iterator it=array.begin(); it!=array.end(); it++)
            std::cout<<*it<<" ";
        std::cout<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
};