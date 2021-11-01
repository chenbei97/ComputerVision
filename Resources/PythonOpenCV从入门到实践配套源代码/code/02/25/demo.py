import numpy as np
n = np.array([0,1,2,3,4,5,6,7,8,9])
print(n)
print(n[:3])          # 1 2
print(n[3:6])         # 3 4 5
print(n[6:])          # 6 7 8 9
print(n[::])          # 0 1 2 3 4 5 6 7 8 9
print(n[:])           # 1 2 3 4 5 6 7 8 9
print(n[::2])         # 0 2 4 6 8
print(n[1::5])        # 1 6
print(n[2::6])        # 2 8
#start、stop、step为负数时
print(n[::-1])        # 9 8 7 6 5 4 3 2 1 0
print(n[:-3:-1])      # 9 8
print(n[-3:-5:-1])    # 7 6
print(n[-5::-1])      # 5 4 3 2 1 0
