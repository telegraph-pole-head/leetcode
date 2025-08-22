#include <vector>

using namespace std;

class Solution {
public:
  int minCostClimbingStairs(vector<int> &cost) {
    int n = cost.size();
    vector<int> dp(n + 1, 0);
    for (int i = 2; i <= n; i++) {
      dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
    }
    return dp.back();
  }
};

class SolutionSpaceOpt {
public:
  int minCostClimbingStairs(vector<int> &cost) {
    for (int i = cost.size() - 3; i >= 0; i--) {
      cost[i] += min(cost[i + 1], cost[i + 2]);
    }
    return min(cost[0], cost[1]);
  }
};
