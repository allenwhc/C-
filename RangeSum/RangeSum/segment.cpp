//
//  segment.cpp
//  RangeSum
//
//  Created by Haochen Wang on 5/23/16.
//  Copyright © 2016 Haochen Wang. All rights reserved.
//

#include <stdio.h>
#include "interface.h"

class SegmentTree: public RangeSum{
    vector<int> arr, segment_tree;
    void construct(int l, int r, int pos){
        if(l==r){
            segment_tree[pos]=arr[l];
            return;
        }
        int mid=(l+r)/2;
        construct(l, mid, 2*pos+1);
        construct(mid+1, r, 2*pos+2);
        segment_tree[pos]=segment_tree[2*pos+1]+segment_tree[2*pos+2];
    }
    
    int search(int start, int end, int l, int r, int pos){
        if(start>r || end<l) return 0;
        if(start<=l && end>=r) return segment_tree[pos];
        int mid=(l+r)/2;
        return search(start, end, l, mid, 2*pos+1)+search(start, end, mid+1, r, 2*pos+2);
    }
    
    //Overload
    void update(int l, int r, int pos, int i, int value){
        if(i<l || i>r) return;
        if(i==l && i==r){
            segment_tree[pos]=value;
            return;
        }
        int mid=(l+r)/2;
        update(l, mid, 2*pos+1, i, value);
        update(mid+1, r, 2*pos+2, i, value);
        segment_tree[pos]=segment_tree[2*pos+1]+segment_tree[2*pos+2];
    }
    
public:
    SegmentTree(vector<int> &array):arr(array){
        segment_tree.reserve(4*array.size()-1);
        fill(segment_tree.begin(), segment_tree.end(), 0);
        construct(0, array.size()-1, 0);
    }
    ~SegmentTree(){}
    //Override
    int rangeSum(int start, int end);
    void update(int i, int value);
};

int SegmentTree::rangeSum(int start, int end){
    return search(start, end, 0, arr.size()-1, 0);
}

void SegmentTree::update(int i, int value){
    update(0, arr.size()-1, 0, i, value);
}