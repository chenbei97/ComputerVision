
import cv2
img = cv2.imread("monitoring.jpg")  # 读取图像
# 加载识别类人体的级联分类器
bodyCascade = cv2.CascadeClassifier("cascades\\haarcascade_fullbody.xml")
bodys = bodyCascade.detectMultiScale(img, 1.15, 4)  # 识别出所有人体
for (x, y, w, h) in bodys:  # 遍历所有人体区域
    cv2.rectangle(img, (x, y), (x + w, y + h), (0, 0, 255), 5)# 在图像中人体的位置绘制方框
cv2.imshow("img", img)  # 显示最终处理的效果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
