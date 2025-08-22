#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() {
  map<int, int> m = {{1, 2}, {2, 3}};
  cout << distance(m.lower_bound(2), m.end()) << endl;
  cout << (m.lower_bound(3) == m.end()) << endl;
  cout << m.lower_bound(2)->second;
  return 0;
}
