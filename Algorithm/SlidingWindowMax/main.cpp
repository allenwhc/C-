#include <iostream>
#include <vector>
#include <deque>

class Solution {
	std::deque<int> dq;
public:
	/**
	 * @param nums: A list of integers.
	 * @return: The maximum number inside the window at each moving.
	 */
	std::vector<int> maxSlidingWindow(std::vector<int> &nums, int k) {
		if(nums.size()==0) return {};
		for (int i = 0; i < k; ++i)
		{
			while(!dq.empty() && nums[i]>nums[dq.back()]) dq.pop_back();
			dq.push_back(i);
		}

		std::vector<int> result;
		for (int i = k; i < nums.size(); ++i)
		{
			result.push_back(nums[dq.front()]);
			while(!dq.empty() && nums[i]>nums[dq.back()]) dq.pop_back();
			while(!dq.empty() && i-dq.front()>=k) dq.pop_front();
			dq.push_back(i);
		}
		result.push_back(nums[dq.front()]);
		return result;
	}
};

int main(int argc, char *argv[]){
	std::vector<int> nums={1,3,-1,-3,5,3,6,7};
	int k=3;
	Solution s;
	std::vector<int> v=s.maxSlidingWindow(nums,k);
	for (std::vector<int>::iterator it=v.begin(); it!=v.end(); ++it)
	{
		std::cout<<*it<<" ";
	}
	return 0;
}