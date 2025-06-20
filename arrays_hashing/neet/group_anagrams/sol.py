from typing import List, defaultdict

# def groupAnagrams(strs: List[str]) -> List[List[str]]:
#     cnt2ls = {}
#     for s in strs:
#         key = "".join(sorted(s))
#         if key in cnt2ls:
#             cnt2ls[key] = cnt2ls[key] + [s]
#         else:
#             cnt2ls[key] = [s]
#     return list(cnt2ls.values())

# O(m * n log n)

def groupAnagrams(strs: List[str]) -> List[List[str]]:
    res = defaultdict(list)
    for s in strs:
        count = [0] * 26
        for c in s:
            count[ord(c) - ord('a')] += 1
        res[tuple(count)].append(s)
    return list(res.values())

# O(m * n)
