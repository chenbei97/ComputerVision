import cv2

image = cv2.imread("D:/2.1.jpg") # 读取D盘根目录下的2.1.jpg
# 字体样式为FONT_HERSHEY_TRIPLEX
fontStyle = cv2.FONT_HERSHEY_TRIPLEX
# 在2.1.jpg上绘制文字“mrsoft”，文字左下角的坐标为(20, 90)
# 字体样式为fontStyle，字体大小为1，线条颜色是黄色
cv2.putText(image, "Flower", (20, 90), fontStyle, 1, (0, 255, 255))
cv2.imshow("Text", image) # 显示画布
cv2.waitKey()
cv2.destroyAllWindows()
