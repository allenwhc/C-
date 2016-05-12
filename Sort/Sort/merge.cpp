//
//  merge.cpp
//  Sort
//
//  Created by Haochen Wang on 5/9/16.
//  Copyright © 2016 Haochen Wang. All rights reserved.
//

#include <stdio.h>
#include "interface.h"
//Merge sort
class Merge: public Sort{
private:
    std::vector<int> array;
    std::mutex mtx;
    std::vector<int> mergeSort(std::vector<int>& array){
        std::vector<int> res=array;
        if(array.size()>1){
            int mid=array.size()/2;
            std::vector<int> left(array.begin(), array.begin()+mid);
            std::vector<int> right(array.begin()+mid, array.end());
            left=mergeSort(left);
            right=mergeSort(right);
            int i=0, j=0, p=0;
            while(i!=left.size() && j!=right.size()){
                if(left[i]<right[j]){res[p]=left[i];i++;}
                else {res[p]=right[j];j++;}
                p++;
            }
            while (i!=left.size()) {res[p]=left[i];i++;p++;}
            while (j!=right.size()) {res[p]=right[j];j++;p++;}
        }
        return res;
    }
public:
    Merge(std::vector<int>& a):array(a){}
    void sorting(){
        locker l(mtx);
        std::vector<int> res=mergeSort(array);
        std::cout<<"Merge sort: ";
        for(std::vector<int>::iterator it=res.begin(); it!=res.end(); it++)
            std::cout<<*it<<" ";
        std::cout<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    
};