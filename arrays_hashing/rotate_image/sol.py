from typing import List


def rotate(matrix: List[List[int]]) -> None:
    """
    Do not return anything, modify matrix in-place instead.
    """
    n = len(matrix)
    # horizontal flip
    for i in range(n):
        for j in range(n//2):
            temp = matrix[i][j]
            matrix[i][j] = matrix[i][n-1-j]
            matrix[i][n-1-j] = temp
    # anti diagonal flip
    for i in range(n):
        for j in range(n-1-i):
            temp = matrix[i][j]
            matrix[i][j] = matrix[n-1-j][n-1-i]
            matrix[n-1-j][n-1-i] = temp
