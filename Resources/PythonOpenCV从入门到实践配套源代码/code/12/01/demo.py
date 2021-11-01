import cv2

img = cv2.imread("peoples.png")  # 读取人脸图像
# 加载识别人脸的级联分类器
faceCascade = cv2.CascadeClassifier("cascades\\haarcascade_frontalface_default.xml")
faces = faceCascade.detectMultiScale(img, 1.3)  # 识别出所有人脸
for (x, y, w, h) in faces:  # 遍历所有人脸的区域
    cv2.rectangle(img, (x, y), (x + w, y + h), (0, 0, 255), 5)  # 在图像中人脸的位置绘制方框
cv2.imshow("img", img)  # 显示最终处理的效果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
