#include <algorithm>
#include <vector>

using namespace std;

// O(n^2) DP solution
// dp[i] means the longest increasing subsequence ends with nums[i]
class Solution {
public:
  int lengthOfLIS(vector<int> &nums) {
    vector<int> dp;
    size_t n = nums.size();
    int maxLen = 1;
    dp.reserve(n);
    dp.push_back(1);
    for (int i = 1; i < n; i++) {
      int maxLenI = 1;
      for (int j = i - 1; j >= 0; j--) {
        if (dp[j] < maxLenI) {
          continue;
        }
        if (nums[j] < nums[i]) {
          maxLenI = dp[j] + 1;
        }
      }
      maxLen = max(maxLen, maxLenI);
      dp.push_back(maxLenI);
    }
    return maxLen;
  }
};

// O(n log n) DP solution using binary search
// https://leetcode.com/problems/longest-increasing-subsequence/solutions/7011289/dp-bs-c-beats-100-runtime
// dp[i] will store the smallest possible tail value of an increasing
// subsequence (of any length) with length i.
class Solution2 {
public:
  int lengthOfLIS(vector<int> &nums) {
    if (nums.empty())
      return 0;
    int n = nums.size();
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = INT_MIN;
    for (int i = 0; i < n; ++i) {
      int idx = lower_bound(dp.begin(), dp.end(), nums[i]) - dp.begin();
      dp[idx] = nums[i];
    }
    return lower_bound(dp.begin(), dp.end(), INT_MAX) - dp.begin() - 1;
  }
};
