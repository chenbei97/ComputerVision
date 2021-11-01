import numpy as np # 导入Python中的numpy模块
import cv2

# np.zeros()：创建了一个画布
# (300, 300, 3)：一个300 x 300，具有3个颜色空间（即Red、Green和Blue）的画布
# np.uint8：OpenCV中的灰度图像和RGB图像都是以uint8存储的，因此这里的类型也是uint8
canvas = np.zeros((300, 300, 3), np.uint8)
# 通过循环绘制27个实心圆
for numbers in range(0, 28):
    # 获得随机的圆心横坐标，这个横坐标在[0, 299]范围内取值
    center_X = np.random.randint(0, high = 300)
    # 获得随机的圆心纵坐标，这个纵坐标在[0, 299]范围内取值
    center_Y = np.random.randint(0, high = 300)
    # 获得随机的半径，这个半径在[11, 70]范围内取值
    radius = np.random.randint(11, high = 71)
    # 获得随机的线条颜色，这个颜色由3个在[0, 255]范围内的随机数组成的列表表示
    color = np.random.randint(0, high = 256, size = (3,)).tolist()
    # 绘制一个圆心坐标为(center_X, center_Y)，半径为radius，颜色为color的实心圆形
    cv2.circle(canvas, (center_X, center_Y), radius, color, -1)
cv2.imshow("Circles", canvas) # 显示画布
cv2.waitKey()
cv2.destroyAllWindows()
