#include <vector>

using namespace std;

class Solution {
public:
  int rob(vector<int> &nums) {
    int n = nums.size();
    if (n == 1)
      return nums[0];
    // dp[i]: end by stealing i
    vector<int> dp(n, 0);
    dp[0] = nums[0];
    dp[1] = nums[1];
    if (n > 2)
      dp[2] = nums[2] + dp[0];
    for (int i = 3; i < n; i++) {
      dp[i] = max(dp[i - 3], dp[i - 2]) + nums[i];
    }
    return max(dp[n - 1], dp[n - 2]);
  }
};

class SolutionSpaceOpt {
public:
  int rob(vector<int> &nums) {
    int rob1 = 0, rob2 = 0;

    for (int num : nums) {
      int temp = max(num + rob1, rob2);
      rob1 = rob2;
      rob2 = temp;
    }
    return rob2;
  }
};
