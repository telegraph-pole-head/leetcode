#include <stack>
#include <vector>
using namespace std;

class Solution {
public:
  vector<int> dailyTemperatures(vector<int> &temperatures) {
    int n = temperatures.size();
    vector<int> answer(n, 0);
    stack<pair<int, int>> st;
    for (int i = 0; i < n; i++) {
      int temp = temperatures[i];
      while (!st.empty() && st.top().first < temp) {
        int j = st.top().second;
        answer[j] = i - j;
        st.pop();
      }
      st.push({temp, i});
    }
    return answer;
  }
};

class SolutionDP {
public:
  vector<int> dailyTemperatures(vector<int> &temperatures) {
    int n = temperatures.size();
    vector<int> res(n, 0);

    for (int i = n - 2; i >= 0; i--) {
      int j = i + 1;
      while (j < n && temperatures[j] <= temperatures[i]) {
        if (res[j] == 0) {
          j = n;
          break;
        }
        j += res[j];
      }

      if (j < n) {
        res[i] = j - i;
      }
    }
    return res;
  }
};
