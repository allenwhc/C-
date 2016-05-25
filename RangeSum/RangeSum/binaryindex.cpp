//
//  binaryindex.cpp
//  RangeSum
//
//  Created by Haochen Wang on 5/23/16.
//  Copyright © 2016 Haochen Wang. All rights reserved.
//

#include <stdio.h>
#include <stdint.h>
#include "interface.h"

class BinaryIndexTree: public RangeSum{
private:
    vector<int> arr;
    vector<int> fenwick_tree;
    uint8_t twosComplement(uint8_t x){
        return -(unsigned int) x;
    }
    
    int getParentNode(int x){
        /*
         *  1. two's complement
         *  2. AND with original number
         *  3. subtract from orignial number
         */
        int comp=twosComplement((uint8_t) x);
        comp &=x;
        return x-comp;
        
    }
    
    int getNextNode(int x){
        /*
         *  1. two's complement
         *  2. AND with original number
         *  3. add to original number
         */
        int comp=twosComplement((uint8_t) x);
        comp &= x;
        return x+comp;
    }
    
    void constructFenwickTree(){
        for (int i=0; i<arr.size(); i++) {
            fenwick_tree[i+1]+=arr[i];
            int next_index=getNextNode(i+1);
            while (next_index<=fenwick_tree.size()) {
                fenwick_tree[next_index]+=arr[i];
                next_index=getNextNode(next_index);
            }
        }
    }
public:
    BinaryIndexTree(vector<int> &array):arr(array){
        fenwick_tree.resize(array.size()+1);
        fill(fenwick_tree.begin(), fenwick_tree.end(), 0);
        constructFenwickTree();
    }
    ~BinaryIndexTree(){}
    void printFenwickTree(){
        for (vector<int>::iterator it=fenwick_tree.begin(); it!=fenwick_tree.end(); it++) {
            cout<<*it<<" ";
        }
        cout<<endl;
    }
    //Override
    int rangeSum(int start, int end){
        return 0;
    }
    void update(int i, int value){
        
    }
};

//int RangeSum::rangeSum(int start, int end){
//    return 0;
//}
//
//void RangeSum::update(int i, int value){
//    
//}

