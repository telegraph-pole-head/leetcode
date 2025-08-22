#include <string>
#include <vector>

using namespace std;

// We need to check: ROW COL DIAG
class Solution {
public:
  vector<vector<string>> solveNQueens(int n) {
    vector<int> rowIdices = {}; // COL: only one Q in one column
    vector<bool> rowIsOccupied(n, false);
    backtrack(rowIdices, n, rowIsOccupied);
    return res;
  }

private:
  vector<vector<string>> res = {};
  void backtrack(vector<int> &rowIdices, const int n,
                 vector<bool> &rowIsOccupied) {
    if (rowIdices.size() == n) {
      vector<string> str(n, string(n,'.'));
      for (int i = 0; i < n; i++) {
        str[i][rowIdices[i]] = 'Q';
      }
      res.push_back(str);
      return;
    }

    for (int i = 0; i < n; i++) {
      if (rowIsOccupied[i]) // ROW: only one Q in one row
        continue;
      bool available = true;
      int m = rowIdices.size();
      for (int j = 0; j < m; j++) {
        if (rowIdices[j] + m - j == i || rowIdices[j] - m + j == i)
          available = false; // DIAG: check if it's on any diag of others
      }
      if (available) {
        rowIdices.push_back(i);
        rowIsOccupied[i] = true;
        backtrack(rowIdices, n, rowIsOccupied);
        rowIdices.pop_back();
        rowIsOccupied[i] = false;
      }
    }
  }
};
