#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

class Solution{
public:
	/*
	*	Bucket sort solution
	*	Time complexity: 
	*	Extra space: O(n)
	*/
	int maximumGap(std::vector<int> &nums){
		if(nums.empty() || nums.size()==1) return 0;
		int n=nums.size();
		int upper=*std::max_element(nums.begin(), nums.end());
		int lower=*std::min_element(nums.begin(), nums.end());
		int bucket_size=(upper-lower)/(n-1)+1;
		int num_of_buckets=(upper-lower)/bucket_size+1;
		std::vector<std::vector<int>> bucket(num_of_buckets);
		for (auto &num:nums){
			int bucket_index=(num-lower)/bucket_size;
			if(bucket[bucket_index].empty()){
				bucket[bucket_index].reserve(2);
				bucket[bucket_index].push_back(num);
				bucket[bucket_index].push_back(num);
			}else{
				if(num<bucket[bucket_index][0]) bucket[bucket_index][0]=num;
				else if(num>bucket[bucket_index][1]) bucket[bucket_index][1]=num;
			}
		}
		int max_gap=0, prev_index=0;
		for (int i=0; i<bucket.size(); i++){
			if (!bucket[i].empty()){
				max_gap=std::max(max_gap, abs(bucket[i][0]-bucket[prev_index][1]));
				prev_index=i;
			}
		}
		return max_gap;
	}
};

int main(int argc, char* argv[]){
	std::vector<int> nums={INT_MAX};
	Solution sol;
	std::cout<<"Max gap:"<<sol.maximumGap(nums)<<std::endl;
}