import numpy as np # 导入Python中的numpy模块
import cv2

# np.zeros()：创建了一个画布
# (300, 300, 3)：一个300 x 300，具有3个颜色空间（即Red、Green和Blue）的画布
# np.uint8：OpenCV中的灰度图像和RGB图像都是以uint8存储的，因此这里的类型也是uint8
canvas = np.zeros((300, 300, 3), np.uint8)
# 绘制一个左上角坐标为(50,50)，右下角坐标为(250,250)，红色的，线条宽度为40的正方形边框
canvas = cv2.rectangle(canvas, (50, 50), (250, 250), (0, 0, 255), 40)
# 绘制一个左上角坐标为(90,90)，右下角坐标为(210,210)，绿色的，线条宽度为30的正方形边框
canvas = cv2.rectangle(canvas, (90, 90), (210, 210), (0, 255, 0), 30)
# 绘制一个左上角坐标为(120,120)，右下角坐标为(180,180)，蓝色的，线条宽度为20的正方形边框
canvas = cv2.rectangle(canvas, (120, 120), (180, 180), (255, 0, 0), 20)
# 绘制一个左上角坐标为(140,140)，右下角坐标为(160,160)，黄色的实心正方形
canvas = cv2.rectangle(canvas, (140, 140), (160, 160), (0, 255, 255), -1)
cv2.imshow("Square", canvas) # 显示画布
cv2.waitKey()
cv2.destroyAllWindows()
