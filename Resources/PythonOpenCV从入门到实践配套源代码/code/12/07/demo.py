
import cv2
import numpy as np

photos = list()  # 样本图像列表
lables = list()  # 标签列表
photos.append(cv2.imread("face\\summer1.png", 0))  # 记录第1张人脸图像
lables.append(0)  # 第1张图像对应的标签
photos.append(cv2.imread("face\\summer2.png", 0))  # 记录第2张人脸图像
lables.append(0)  # 第2张图像对应的标签
photos.append(cv2.imread("face\\summer3.png", 0))  # 记录第3张人脸图像
lables.append(0)  # 第3张图像对应的标签

photos.append(cv2.imread("face\\Elvis1.png", 0))  # 记录第4张人脸图像
lables.append(1)  # 第4张图像对应的标签
photos.append(cv2.imread("face\\Elvis2.png", 0))  # 记录第5张人脸图像
lables.append(1)  # 第5张图像对应的标签
photos.append(cv2.imread("face\\Elvis3.png", 0))  # 记录第6张人脸图像
lables.append(1)  # 第6张图像对应的标签

names = {"0": "Summer", "1": "Elvis"}  # 标签对应的名称字典

recognizer = cv2.face.EigenFaceRecognizer_create()  # 创建特征脸识别器
recognizer.train(photos, np.array(lables))  # 识别器开始训练

i = cv2.imread("face\\summer4.png", 0)  # 待识别的人脸图像
label, confidence = recognizer.predict(i)  # 识别器开始分析人脸图像
print("confidence = " + str(confidence))  # 打印评分
print(names[str(label)])  # 数组字典里标签对应的名字
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
