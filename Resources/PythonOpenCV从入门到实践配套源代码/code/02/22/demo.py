import numpy as np
n1 = np.array([1, 2])  # 创建一维数组
n2 = n1.copy()  # 创建复制第一个数组
print(n1 == n2)  # 比较两个数组是否相同
n2[0] = 9  # 副本数组修改第一个元素
print(n1)  # 输出两个数组的元素值
print(n2)
print(n1 == n2)  # 比较两个数组是否相同
