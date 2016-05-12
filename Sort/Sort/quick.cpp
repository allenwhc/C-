//
//  quick.cpp
//  Sort
//
//  Created by Haochen Wang on 5/9/16.
//  Copyright © 2016 Haochen Wang. All rights reserved.
//

#include <stdio.h>
#include "interface.h"

class Quick: public Sort{
    std::vector<int> array;
    std::mutex mtx;
    int partition(std::vector<int>& array, int s, int e){
        int i=s,j=e;
        int pivot=array[(s+e)/2];
        while (i<j) {
            while (array[i]<pivot) i++;
            while (array[j]>pivot) j--;
            if (i<=j) std::swap(array[i], array[j]);
        }
        return i;
    }
    void quickSort(std::vector<int>& array, int s, int e){
        if (s<e) {
            int idx=partition(array, s, e);
            quickSort(array, s, idx-1);
            quickSort(array, idx+1, e);
        }
    }
public:
    Quick(std::vector<int> &a):array(a){}
    void sorting(){
        locker l(mtx);
        quickSort(array, 0, array.size()-1);
        std::cout<<"Quick sort: ";
        for(std::vector<int>::iterator it=array.begin(); it!=array.end(); it++)
            std::cout<<*it<<" ";
        std::cout<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
};