# @BAKE python3 $@

# Imagine all this, but as generated(!) C code

# These are all our options, we would like to precompute them for reasons such as
#  1) imagine this is SQL; (while it should be hard to break) debugging dynamic SQL is horrid
#  2) C strings are painful
#  3) some bullshit reason appealing to speed autism or something
#  4) some bullshit on compile time guarantees
options = [
	["a", "b", "c"],
	["A", "B"],
	["1", "2", "3", "4"],
]

# This leaves us with a single array of all combinations
def combinator(options):
	r = []
	indexes = [0] * len(options)
	max_add_index = len(options) - 1
	add_index = max_add_index
	while True:
		ri = ""
		for i in range(len(options)):
			ri += options[i][indexes[i]]
		r.append(ri)

		while True:
			if indexes[add_index] != len(options[add_index])-1:
				indexes[add_index] += 1
				add_index = max_add_index
				break
			else:
				if add_index == 0: return r
				indexes[add_index] = 0
				add_index -= 1

# This would use enums and the shape would be compile time
def combination_lookup(combinations, shape, element):
	index = 0
	for i in range(len(element)):
		c = 1
		c *= element[i]
		for h in range(i+1, len(shape)):
			c *= shape[h]
		index += c
	return combinations[index]

combinations = combinator(options)
print(combinations)
print(combination_lookup(combinations, [3, 2, 4], [1, 0, 2])) # expected outout: "bA3"
print(combination_lookup(combinations, [3, 2, 4], [2, 1, 3])) # expected outout: "cB4"

# The thing is, the more i think about it the more retarded it seems,
#  but it does have a sense of "cleaness".
# However, if go with dynamic generation anyways, bison would be reasonably clean too.
