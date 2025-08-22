#include <vector>

using namespace std;

// backtracking solution O(n * 2^n)
// idea: increasing idx guarantees no duplicate subsets
// choices: add which idx to current subset
// res: valid paths of the tree
class Solution {
public:
  vector<vector<int>> subsets(vector<int> &nums) {
    vector<vector<int>> res;
    int n = nums.size();
    res.reserve(1 << n);     // 2^n
    vector<int> subset = {}; // current node of idx seq
    res.push_back(subset);
    backtrack(subset, n, res);
    for (int i = 0; i < res.size(); i++) {
      for (int j = 0; j < res[i].size(); j++) {
        res[i][j] = nums[res[i][j]];
      }
    }
    return res;
  }
private:
  void backtrack(vector<int> &subset, const int n, vector<vector<int>> &res) {
    for (int i = n - 1; i >= 0; i--) { // reversely, for early exit
      if (!subset.empty() && i <= subset.back())
        return; // strictly increasing idx
      subset.push_back(i);
      res.push_back(subset);
      backtrack(subset, n, res);
      subset.pop_back();
    }
  }
};

// backtracking solution O(n * 2^n)
// choices: add or not add current(i-th) element to the subset
// res: leaf nodes of the tree
//            []
//          /   \      --add 1 or not
//      [1]      []
//     /  \      / \   --add 2 or not
//  [1,2] [1]  [2] []
class Solution1 {
public:
  vector<vector<int>> subsets(vector<int> &nums) {
    vector<vector<int>> res;
    vector<int> subset;
    dfs(nums, 0, subset, res);
    return res;
  }

private:
  void dfs(const vector<int> &nums, int i, vector<int> &subset,
           vector<vector<int>> &res) {
    if (i >= nums.size()) { // base case: reached the leaf node
      res.push_back(subset);
      return;
    }
    subset.push_back(nums[i]);
    dfs(nums, i + 1, subset, res); // w/ nums[i]
    subset.pop_back();
    dfs(nums, i + 1, subset, res); // w/o nums[i]
  }
};

// iterative solution O(n * 2^n)
// [[]]
// [[]] + [[1]]
// [[],[1]] + [[2],[1,2]]
// [[],[1],[2],[1,2]] + [[3],[1,3],[2,3],[1,2,3]]
class Solution2 {
public:
  vector<vector<int>> subsets(vector<int> &nums) {
    vector<vector<int>> res = {{}};

    for (int num : nums) {
      int size = res.size();
      for (int i = 0; i < size; i++) {
        vector<int> subset = res[i];
        subset.push_back(num);
        res.push_back(subset);
      }
    }

    return res;
  }
};

// bit manipulation solution O(n * 2^n)
class Solution3 {
public:
  vector<vector<int>> subsets(vector<int> &nums) {
    int n = nums.size();
    vector<vector<int>> res;
    for (int i = 0; i < (1 << n); i++) {
      vector<int> subset;
      for (int j = 0; j < n; j++) {
        if (i & (1 << j)) {
          subset.push_back(nums[j]);
        }
      }
      res.push_back(subset);
    }
    return res;
  }
};
