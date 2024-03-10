import difflib

# Example list of strings
strings = [
    "apple pie",
    "apple cider",
    "apple juice",
    "banana bread",
    "banana split",
    "banana smoothie"
]

# Create a dictionary to store the groups
groups = {}

# Iterate through the strings to find the longest common substrings
for i in range(len(strings)):
    for j in range(i+1, len(strings)):
        match = difflib.SequenceMatcher(None, strings[i], strings[j]).find_longest_match(0, len(strings[i]), 0, len(strings[j]))
        common_substring = strings[i][match.a: match.a + match.size]
        if common_substring:
            if common_substring not in groups:
                groups[common_substring] = [strings[i], strings[j]]
            else:
                groups[common_substring].extend([strings[i], strings[j]])

# Print the groups
for key, value in groups.items():
    print(f"Group: {key}")
    print(value)
    print()
