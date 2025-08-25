#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
  int longestConsecutive(vector<int> &nums) {
    unordered_map<int, int> mp;
    int maxLen = 0;
    for (int num : nums) {
      if (!mp[num]) {
        mp[num] = mp[num - 1] + mp[num + 1] + 1;
        mp[num - mp[num - 1]] = mp[num];
        mp[num + mp[num + 1]] = mp[num];
        maxLen = max(maxLen, mp[num]);
      }
    }
    return maxLen;
  }
};

// Union-Find solution
class SolutionMine {
public:
  int longestConsecutive(vector<int> &nums) {
    if (nums.empty()) {
      return 0;
    }
    for (int i = 0; i < nums.size(); i++) {
      int num = nums[i];
      if (p.find(num) != p.end()) {
        continue;
      }
      p[num] = num;
      cnt[p[num]] = 1;
      if (p.find(num - 1) != p.end()) {
        merge(num, num - 1);
      }
      if (p.find(num + 1) != p.end()) {
        merge(num, num + 1);
      }
    }
    return maxSize;
  }

private:
  unordered_map<int, int> p;
  unordered_map<int, int> cnt;
  int maxSize = 1;

  int find(int target) {
    if (p[target] == target) {
      return target;
    } else {
      return p[target] = find(p[target]);
    }
  }

  void merge(int a, int b) {
    int aRoot = find(a);
    int bRoot = find(b);
    if (cnt[aRoot] > cnt[bRoot]) {
      p[bRoot] = aRoot;
      cnt[aRoot] += cnt[bRoot];
      maxSize = max(cnt[aRoot], maxSize);
    } else {
      p[aRoot] = bRoot;
      cnt[bRoot] += cnt[aRoot];
      maxSize = max(cnt[bRoot], maxSize);
    }
  }
};
