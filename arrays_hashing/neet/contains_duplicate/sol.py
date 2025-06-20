import random
from typing import List


def hasDuplicate(nums: List[int]) -> bool:
    """
    Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.
    """
    return len(nums) > len(set(nums))


def main():
    test_cases = [
        ([1, 2, 3, 1], True),
        ([1, 2, 3, 4], False),
        ([1, 1, 1, 3, 3, 4, 3, 2, 4, 2], True),
        # ([random.randint(1, 1000) for _ in range(1000)], False),
    ]
    for test, expected in test_cases:
        assert hasDuplicate(test) == expected


if __name__ == "__main__":
    main()
