#include <algorithm>
#include <vector>
#include <map>


using namespace std;

// O(n^2) DP solution
// dp[i] means the longest increasing subsequence ends with nums[i]
// TLE
class Solution {
public:
  int lengthOfLIS(vector<int> &nums, int k) {
    if (nums.empty())
      return 0;
    size_t n = nums.size();
    vector<int> dp(n, 1);
    for (int i = 0; i < n; i++) {
      for (int j = i; j >= 0; j--) {
        if (nums[i] > nums[j] && nums[i] <= nums[j] + k) {
          dp[i] = max(dp[i], dp[j] + 1);
        }
      }
    }
    return *max_element(dp.begin(), dp.end());
  }
};

// TLE
class Solution1 {
public:
  int lengthOfLIS(vector<int> &nums, int k) {
    if (nums.empty())
      return 0;
    size_t n = nums.size();
    vector<vector<int>> dp(n + 1, vector<int>(1, INT_MAX));
    vector<int> dp0(n + 1, INT_MAX);
    dp0[0] = INT_MIN;
    dp0[1] = nums[0];
    dp[1].insert(dp[1].begin(), nums[0]);
    for (int i = 1; i < n; i++) {
      int idx = lower_bound(dp0.begin(), dp0.end(), nums[i]) - dp0.begin();
      int min_prev = nums[i] - k;
      int idxInsert = 1;
      if (dp0[idx - 1] >= min_prev || idx - 1 == 0) {
        idxInsert = idx;
      } else {
        for (int j = idx; j > 1; j--) {
          std::vector<int>::iterator pos =
              lower_bound(dp[j - 1].begin(), dp[j - 1].end(), min_prev);
          if (*pos < nums[i]) {
            idxInsert = j;
            break;
          }
        }
      }
      std::vector<int>::iterator rp =
          lower_bound(dp[idxInsert].begin(), dp[idxInsert].end(), nums[i]);
      if (*rp != nums[i]) {
        dp[idxInsert].insert(rp, nums[i]);
        dp0[idxInsert] = dp[idxInsert][0];
      }
    }
    return lower_bound(dp0.begin(), dp0.end(), INT_MAX) - dp0.begin() - 1;
  }
};

// TLE
class Solution3 {
public:
  int lengthOfLIS(vector<int> &nums, int k) {
    if (nums.empty())
      return 0;
    size_t n = nums.size();
    map<int, int> dp;
    dp[nums[0]] = 1;

    for (int i = 1; i < n; i++) {
      auto it = dp.lower_bound(nums[i] - k);
      int maxLen = 0;

      while (it != dp.end() && it->first < nums[i]) {
        maxLen = max(it->second + 1, maxLen);
        it++;
      }

      if (maxLen > 0) {
        dp[nums[i]] = maxLen;
      } else {
        dp[nums[i]] = 1;
      }
    }

    auto maxValIt =
        max_element(dp.begin(), dp.end(), [](const auto &a, const auto &b) {
          return a.second < b.second;
        });
    return maxValIt->second;
  }
};

// Segment tree solution
// https://leetcode.com/problems/longest-increasing-subsequence-ii/solutions/2560010/c-segment-tree-with-illustration-explanation
class MaxSegmentTree {
public:
  int n;
  vector<int> tree;
  MaxSegmentTree(int n_) : n(n_) {
    int size = (int)(ceil(log2(n)));
    size = (2 * pow(2, size)) - 1;
    tree = vector<int>(size);
  }

  int max_value() { return tree[0]; }

  int query(int l, int r) { return query_util(0, l, r, 0, n - 1); }

  int query_util(int i, int qL, int qR, int l, int r) {
    if (l >= qL && r <= qR)
      return tree[i];
    if (l > qR || r < qL)
      return INT_MIN;

    int m = (l + r) / 2;
    return max(query_util(2 * i + 1, qL, qR, l, m),
               query_util(2 * i + 2, qL, qR, m + 1, r));
  }

  void update(int i, int val) { update_util(0, 0, n - 1, i, val); }
  void update_util(int i, int l, int r, int pos, int val) {
    if (pos < l || pos > r)
      return;
    if (l == r) {
      tree[i] = max(val, tree[i]);
      return;
    }

    int m = (l + r) / 2;
    update_util(2 * i + 1, l, m, pos, val);
    update_util(2 * i + 2, m + 1, r, pos, val);
    tree[i] = max(tree[2 * i + 1], tree[2 * i + 2]);
  }
};

class Solution4 {
public:
  int lengthOfLIS(vector<int> &nums, int k) {
    MaxSegmentTree tree(1e5 + 1);
    for (int i : nums) {
      int lower = max(0, i - k);
      int cur = 1 + tree.query(lower, i - 1);
      tree.update(i, cur);
    }

    return tree.max_value();
  }
};
