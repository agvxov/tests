from memory_profiler import memory_usage

def create_base_ints():
    base_ints = [i for i in range(10000)]
    return base_ints

if __name__ == '__main__':
    mem_usage = memory_usage(create_base_ints)
    print(f"Memory usage: {mem_usage[0]:.2f} MiB")
