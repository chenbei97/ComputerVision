
import cv2

img = cv2.imread("car.jpg")  # 读取车的图像
# 加载识别车牌的级联分类器
plateCascade = cv2.CascadeClassifier("cascades\\haarcascade_russian_plate_number.xml")
plates = plateCascade.detectMultiScale(img, 1.15, 4)  # 识别出所有车牌
for (x, y, w, h) in plates:  # 遍历所有车牌区域
    cv2.rectangle(img, (x, y), (x + w, y + h), (0, 0, 255), 5)  # 在图像中车牌的位置绘制方框
cv2.imshow("img", img)  # 显示最终处理的效果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
