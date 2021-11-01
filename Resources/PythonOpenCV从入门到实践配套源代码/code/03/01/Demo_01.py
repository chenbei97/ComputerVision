import numpy as np # 导入Python中的numpy模块
import cv2

# np.zeros()：创建了一个画布
# (300, 300, 3)：一个300 x 300，具有3个颜色空间（即Red、Green和Blue）的画布
# np.uint8：OpenCV中的灰度图像和RGB图像都是以uint8存储的，因此这里的类型也是uint8
canvas = np.zeros((300, 300, 3), np.uint8)
# 在画布上，绘制一条起点坐标为(50, 50)、终点坐标为(250, 50)，蓝色的，线条宽度为5的线段
canvas = cv2.line(canvas, (50, 50), (250, 50), (255, 0, 0), 5)
# 在画布上，绘制一条起点坐标为(50, 150)、终点坐标为(250, 150)，绿色的，线条宽度为10的线段
canvas = cv2.line(canvas, (50, 150), (250, 150), (0, 255, 0), 10)
# 在画布上，绘制一条起点坐标为(50, 250)、终点坐标为(250, 250)，红色的，线条宽度为15的线段
canvas = cv2.line(canvas, (50, 250), (250, 250), (0, 0, 255), 15)
# 在画布上，绘制一条起点坐标为(150, 50)、终点坐标为(150, 250)，黄色的，线条宽度为20的线段
canvas = cv2.line(canvas, (150, 50), (150, 250), (0, 255, 255), 20)
cv2.imshow("Lines", canvas) # 显示画布
cv2.waitKey()
cv2.destroyAllWindows()
