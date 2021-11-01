
import cv2
img = cv2.imread("cat.jpg")  # 读取猫脸图像
# 加载识别猫脸的级联分类器
catFaceCascade = cv2.CascadeClassifier("cascades\\haarcascade_frontalcatface_extended.xml")
catFace = catFaceCascade.detectMultiScale(img, 1.15, 4)  # 识别出所有猫脸
for (x, y, w, h) in catFace:  # 遍历所有猫脸的区域
    cv2.rectangle(img, (x, y), (x + w, y + h), (0, 0, 255), 5)# 在图像中猫脸的位置绘制方框
cv2.imshow("Where is your cat ?", img)  # 显示最终处理的效果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
