from typing import List


class Solution:
    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
        ROWS, COLS = len(matrix), len(matrix[0])

        l, r = 0, ROWS * COLS - 1
        while l <= r:
            m = l + (r - l) // 2
            row, col = m // COLS, m % COLS
            if target > matrix[row][col]:
                l = m + 1
            elif target < matrix[row][col]:
                r = m - 1
            else:
                return True
        return False

# class Solution:
#     def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
#         ROWS, COLS = len(matrix), len(matrix[0])

#         l, r = 0, ROWS * COLS - 1
#         while l <= r:
#             m = l + (r - l) // 2
#             row, col = m // COLS, m % COLS
#             if target > matrix[row][col]:
#                 l = m + 1
#             elif target < matrix[row][col]:
#                 r = m - 1
#             else:
#                 return True
#         return False

if __name__ == "__main__":
    sol = Solution()
    matrix = [[1,3,5],[7,9,11],[12,13,15]]
    target = 11
    print(sol.searchMatrix(matrix, target))  # Output: True

    target = 4
    print(sol.searchMatrix(matrix, target))  # Output: False

    target = 1
    print(sol.searchMatrix(matrix, target))  # Output: True

    target = 15
    print(sol.searchMatrix(matrix, target))  # Output: True

    target = 16
    print(sol.searchMatrix(matrix, target))  # Output: False
