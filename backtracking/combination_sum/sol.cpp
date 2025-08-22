#include <vector>

using namespace std;


class SolutionMine {
public:
  vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
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
      if (nsum <= target) {
        path.push_back(cand);
        backtrack(candidates, target, i, nsum, path);
        path.pop_back();
      } else {
        return; // the following also > target
      }
    }
  }
};
