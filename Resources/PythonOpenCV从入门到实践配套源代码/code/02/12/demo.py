import numpy as np  # 导入numpy模块

list = [1, 2, 3]  # 列表
# 创建浮点型数组
n1 = np.array(list, dtype=np.float_)
# 或者
n1 = np.array(list, dtype=float)
print(n1)
print(n1.dtype)
print(type(n1[0]))
