import numpy as np # 导入Python中的numpy模块
import cv2

# np.zeros()：创建了一个画布
# (300, 300, 3)：一个300 x 300，具有3个颜色空间（即Red、Green和Blue）的画布
# np.uint8：OpenCV中的灰度图像和RGB图像都是以uint8存储的，因此这里的类型也是uint8
canvas = np.zeros((300, 300, 3), np.uint8)
# 在画布上绘制一个左上角坐标为(50,50)，右下角坐标为(200,150)，青色的，线条宽度为20的矩形边框
canvas = cv2.rectangle(canvas, (50, 50), (200, 150), (255, 255, 0), 20)
cv2.imshow("Rectangle", canvas) # 显示画布
cv2.waitKey()
cv2.destroyAllWindows()
