#include <iostream>
#include <vector>
#include <numeric>
#include <string>

class Solution{
public:
	std::string largestNumber(std::vector<int> &nums){
		std::sort(nums.begin(), nums.end(), [](int a, int b){return std::to_string(a)+std::to_string(b)>std::to_string(b)+std::to_string(a);});
		std::string result=std::accumulate(nums.begin(), nums.end(), std::string(), [](const std::string &r, int a){return r+std::to_string(a);});
		return result[0]==0?"0":result;
	}
};

int main(int argc, char *argv[]){
	std::unique_ptr<Solution> s(new Solution());
	std::vector<int> nums={3,30,34,5,9};
	std::cout<<"Largest number is: "<<s->largestNumber(nums)<<std::endl;
	return 0;
}
