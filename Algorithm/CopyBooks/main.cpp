#include <iostream>
#include <vector>
#include <numeric>

class Solution{
/*
*	Dynamic programming solution
*	Time complexity: O(n*k)
*	Extra space: O(n*k)
*/
public:
	int copyBooks(std::vector<int> &pages, int k){
		if(pages.empty() || k==0) return 0;
		int n=pages.size();
		k=std::min(n,k);
		std::vector<int> sum_from_start(n,0);
		std::partial_sum(pages.begin(), pages.end(),sum_from_start.begin());
		std::vector<std::vector<int>> minutes(k+1, std::vector<int>(n, INT_MAX));
		for(int j=0; j<n; j++) minutes[1][j]=sum_from_start[j];
		for(int i=2; i<=k; i++){
			minutes[i][0]=sum_from_start[1];
			int l=0, r=1;
			while(r<n){
				int curr=sum_from_start[r]-sum_from_start[l];
				minutes[i][r]=std::min(minutes[i][r], std::max(curr, minutes[i-1][l]));
				if(l<r && minutes[i-1][l]<curr) l++;
				else{
					r++;
					if(l>0) l--;
				}
			}
		}
		return minutes[k][n-1];
	}
};

int main(int argc, char* argv[]){
	std::vector<int> pages={1,2};
	int k=5;
	Solution sol;
	std::cout<<"Min total time is: "<<sol.copyBooks(pages,k)<<std::endl;
}