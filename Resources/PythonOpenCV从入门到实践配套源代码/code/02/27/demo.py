import numpy as np

# 创建3行3列的二维数组
n = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
print(n[:2, 1:])
print(n[1, :2])
print(n[:2, 2])
print(n[:, :1])
