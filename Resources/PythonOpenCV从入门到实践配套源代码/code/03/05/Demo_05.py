import numpy as np # 导入Python中的numpy模块
import cv2

# np.zeros()：创建了一个画布
# (300, 300, 3)：一个300 x 300，具有3个颜色空间（即Red、Green和Blue）的画布
# np.uint8：OpenCV中的灰度图像和RGB图像都是以uint8存储的，因此这里的类型也是uint8
canvas = np.zeros((300, 300, 3), np.uint8)
# shape[1]表示画布的宽度，center_X表示圆心的横坐标
# 圆心的横坐标等于画布的宽度的一半
center_X = int(canvas.shape[1] / 2)
# shape[0]表示画布的高度，center_X表示圆心的纵坐标
# 圆心的纵坐标等于画布的高度的一半
center_Y = int(canvas.shape[0] / 2)
# r表示半径；其中，r的值分别为0、30、60、90和120
for r in range(0, 150, 30):
    # 绘制一个圆心坐标为(center_X, center_Y)，半径为r，绿色的，线条宽度为5的圆形
    cv2.circle(canvas, (center_X, center_Y), r, (0, 255, 0), 5)
cv2.imshow("Circles", canvas) # 显示画布
cv2.waitKey()
cv2.destroyAllWindows()
