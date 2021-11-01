import numpy as np # 导入Python中的numpy模块
import cv2

# np.zeros()：创建了一个画布
# (100, 300, 3)：一个100 x 300，具有3个颜色空间（即Red、Green和Blue）的画布
# np.uint8：OpenCV中的灰度图像和RGB图像都是以uint8存储的，因此这里的类型也是uint8
canvas = np.zeros((100, 300, 3), np.uint8)
# 字体样式为FONT_HERSHEY_TRIPLEX和FONT_ITALIC
fontStyle = cv2.FONT_HERSHEY_TRIPLEX + cv2.FONT_ITALIC
# 在画布上绘制文字“mrsoft”，文字左下角的坐标为(20, 70)
# 字体样式为fontStyle，字体大小为2，线条颜色是绿色，线条宽度为5
cv2.putText(canvas, "mrsoft", (20, 70), fontStyle, 2, (0, 255, 0), 5)
cv2.imshow("Text", canvas) # 显示画布
cv2.waitKey()
cv2.destroyAllWindows()
