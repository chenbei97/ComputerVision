import numpy as np # 导入Python中的numpy模块
import cv2

# np.zeros()：创建了一个画布
# (300, 300, 3)：一个300 x 300，具有3个颜色空间（即Red、Green和Blue）的画布
# np.uint8：OpenCV中的灰度图像和RGB图像都是以uint8存储的，因此这里的类型也是uint8
canvas = np.zeros((300, 300, 3), np.uint8)
# 按顺时针给出等腰梯形4个顶点的坐标
# 这4个顶点的坐标构成了一个大小等于“顶点个数 * 1 * 2”的数组
# 这个数组的数据类型为np.int32
pts = np.array([[100, 50], [200, 50], [250, 250], [50, 250]], np.int32)
# 在画布上根据4个顶点的坐标，绘制一个闭合的，红色的，线条宽度为5的等腰梯形边框
canvas = cv2.polylines(canvas, [pts], True, (0, 0, 255), 5)
cv2.imshow("Polylines", canvas) # 显示画布
cv2.waitKey()
cv2.destroyAllWindows()
