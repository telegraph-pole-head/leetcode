#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<int> path;
    backtrack(candidates, target, 0, 0, path);
    return res;
  }

private:
  vector<vector<int>> res;
  void backtrack(vector<int> &candidates, int target, int start, int sum,
                 vector<int> &path) {
    if (sum == target) {
      res.push_back(path);
      return;
    }
    for (int i = start; i < candidates.size(); i++) {
      int cand = candidates[i];
      int nsum = sum + cand;
      if (i > start && candidates[i] == candidates[i - 1]) {
        continue; // avoid duplicate sibling
      }
      if (nsum <= target) {
        path.push_back(cand);
        backtrack(candidates, target, i + 1, nsum,
                  path); // avoid duplicate sibling
        path.pop_back();
      } else {
        return; // the following also > target
      }
    }
  }
};
