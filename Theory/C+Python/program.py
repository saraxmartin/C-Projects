"""
How to use functions from C in Python
"""
import ctypes
import sys

my_library = "C:/Users/sara0/Desktop/uni/programming II/C/Theory/C+Python/my_lib.so"
print(my_library)

try:
    print("y")
    my_functions = ctypes.CDLL(my_library)
    print(type(my_functions))
    print(my_functions.bubbleSort([7,5,4],3))
except OSError:
    print("Error with C library")
    sys.exit()