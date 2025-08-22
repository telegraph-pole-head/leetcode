#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

// iterative solution O(n * 2^n)
class Solution_Mine {
public:
  vector<vector<int>> subsetsWithDup(vector<int> &nums) {
    vector<vector<int>> res = {{}};
    unordered_map<int, int> cnt;
    sort(nums.begin(), nums.end()); // make sure duplicates are adjacent
    for (int i = 0; i < nums.size(); i++) {
      int num = nums[i];
      int res_size = res.size();
      cnt[num] = cnt.find(num) != cnt.end() ? cnt[num] + 1 : 1;
      for (int j = 0; j < res_size; j++) {
        int m = res[j].size();
        if (cnt[num] > 1 &&
            (m + 1 - cnt[num] < 0 || res[j][m + 1 - cnt[num]] != num))
          continue; // only add num for subsets already containing cnt-1 num
        vector<int> subset = res[j];
        subset.push_back(num);
        res.push_back(subset);
      }
    }
    return res;
  }
};

// iterative solution O(n * 2^n)
class SolutionIt {
public:
  vector<vector<int>> subsetsWithDup(vector<int> &nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> res = {{}};
    int prevIdx = 0;
    int idx = 0;

    for (int i = 0; i < nums.size(); i++) {
      idx =
          (i >= 1 && nums[i] == nums[i - 1])
              ? prevIdx
              : 0; // if current num is the same as previous, start from prevIdx
      prevIdx = res.size();
      for (int j = idx; j < prevIdx; j++) {
        std::vector<int> tmp = res[j];
        tmp.push_back(nums[i]);
        res.push_back(tmp);
      }
    }

    return res;
  }
};

// backtracking solution O(n * 2^n)
class SolutionBt {
public:
  vector<vector<int>> res;

  vector<vector<int>> subsetsWithDup(vector<int> &nums) {
    sort(nums.begin(), nums.end());
    backtrack(0, {}, nums);
    return res;
  }

  void backtrack(int i, vector<int> subset, vector<int> &nums) {
    res.push_back(subset);
    for (int j = i; j < nums.size(); j++) {
      if (j > i && nums[j] == nums[j - 1]) {
        continue;
      }
      subset.push_back(nums[j]);
      backtrack(j + 1, subset, nums);
      subset.pop_back();
    }
  }
};

// backtracking solution O(n * 2^n)
class SolutionBtMine {
public:
  vector<vector<int>> subsetsWithDup(vector<int> &nums) {
    vector<vector<int>> res;
    vector<int> subset;
    sort(nums.begin(), nums.end());
    dfs(subset, nums, 0, false);
    return res;
  }

private:
  vector<vector<int>> res;

  void dfs(vector<int> &subset,
           const vector<int> &nums, int idx, bool selected) {
    if (idx >= nums.size()) {
      res.push_back(subset);
      return;
    }
    if (idx == 0 || nums[idx] != nums[idx - 1] || selected) {
      subset.push_back(nums[idx]);
      dfs(subset, nums, idx + 1, true);
      subset.pop_back();
    }
    dfs(subset, nums, idx + 1, false);
  }
};
