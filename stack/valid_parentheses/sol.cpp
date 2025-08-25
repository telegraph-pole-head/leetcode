#include <stack>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
  bool isValid(string s) {
    stack<char> st;
    unordered_map<char, char> mp = {{'(', ')'}, {'[', ']'}, {'{', '}'}};
    for (int i = 0; i < s.size(); i++) {
      char c = s[i];
      if (mp.count(c)) {
        st.push(c);
      } else {
        if (!st.empty() && mp[st.top()] == c)
          st.pop();
        else
          return false;
      }
    }
    return st.empty();
  }
};
