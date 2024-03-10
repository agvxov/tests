import timeit

# Using join()
start_time = timeit.default_timer()
for i in range(1, 1000):
	result = ''.join(['a', '/', 'b', '/', 'c'])
end_time = timeit.default_timer()
print(f'Using join(): {result}, time: {end_time - start_time}')

# Using format()
start_time = timeit.default_timer()
for i in range(1, 1000):
	result = '{}/{}/{}'.format('a', 'b', 'c')
end_time = timeit.default_timer()
print(f'Using format(): {result}, time: {end_time - start_time}')
