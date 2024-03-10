from ctypes import c_int
from memory_profiler import memory_usage

def create_ctypes_ints():
    ctypes_ints = [c_int(i) for i in range(10000)]
    return ctypes_ints

if __name__ == '__main__':
    mem_usage = memory_usage(create_ctypes_ints)
    print(f"Memory usage: {mem_usage[0]:.2f} MiB")
