import cv2

img = cv2.imread("peoples.png")  # 读取人脸图像
# 加载识别眼睛的级联分类器
eyeCascade = cv2.CascadeClassifier("cascades\\haarcascade_eye.xml")
eyes = eyeCascade.detectMultiScale(img, 1.15)  # 识别出所有眼睛
for (x, y, w, h) in eyes:  # 遍历所有眼睛的区域
    cv2.rectangle(img, (x, y), (x + w, y + h), (0, 0, 255), 4)  # 在图像中眼睛的位置绘制方框
cv2.imshow("img", img)  # 显示最终处理的效果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
