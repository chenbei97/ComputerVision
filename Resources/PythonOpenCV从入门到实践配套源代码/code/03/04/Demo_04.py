import numpy as np # 导入Python中的numpy模块
import cv2

# np.zeros()：创建了一个画布
# (100, 300, 3)：一个100 x 300，具有3个颜色空间（即Red、Green和Blue）的画布
# np.uint8：OpenCV中的灰度图像和RGB图像都是以uint8存储的，因此这里的类型也是uint8
canvas = np.zeros((100, 300, 3), np.uint8)
# 在画布上，绘制一个圆心坐标为(50, 50)，半径为40，红色的实心圆形
canvas = cv2.circle(canvas, (50, 50), 40, (0, 0, 255), -1)
# 在画布上，绘制一个圆心坐标为(150, 50)，半径为40，黄色的实心圆形
canvas = cv2.circle(canvas, (150, 50), 40, (0, 255, 255), -1)
# 在画布上，绘制一个圆心坐标为(250, 50)，半径为40，绿色的实心圆形
canvas = cv2.circle(canvas, (250, 50), 40, (0, 255, 0), -1)
cv2.imshow("TrafficLights", canvas) # 显示画布
cv2.waitKey()
cv2.destroyAllWindows()
