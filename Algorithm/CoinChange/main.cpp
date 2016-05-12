#include <iostream>
#include <vector>

class Solution{
public:
	int coinChange(std::vector<int>& coins, int amount){
		if (coins.empty() || amount==0) return 0;
		//std::sort(coins.begin(), coins.end());
		std::vector<int> dp(amount+1, INT_MAX);
		dp[0]=0;
		for (int i=1; i<=amount; i++){
			for (int j=0; j<n; j++){
				if (coins[j]<=i){
					int rest=dp[i-coins[j]];
					if (rest!=INT_MAX && rest+1<dp[i]) dp[i]=rest+1;
				}
			}
		}
		return dp[amount]==INT_MAX?-1:dp[amount];
	}
};

int main(int argc, char* argv[]){
	std::vector<int> coins={1,2,5};
	int amount=11;
	Solution sol;
	std::cout<<sol.coinChange(coins,amount)<<std::endl;
}