# [N-Queens](https://neetcode.io/problems/n-queens?list=neetcode150)
[LeetCode 51](https://leetcode.com/problems/n-queens/)

The n-queens puzzle is the problem of placing `n` queens on an `n x n` chessboard so that no two queens can attack each other.

A queen in a chessboard can attack horizontally, vertically, and diagonally.

Given an integer `n`, return all distinct solutions to the n-queens puzzle.

Each solution contains a unique board layout where the queen pieces are placed. `'Q'` indicates a queen and `'.'` indicates an empty space.

You may return the answer in any order.

Example 1:
![](https://assets.leetcode.com/uploads/2020/11/13/queens.jpg)
```
Input: n = 4
Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above
```

Example 2:
```
Input: n = 1
Output: [["Q"]]
```

Constraints:
```
1 <= n <= 9
```
