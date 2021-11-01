import cv2
import numpy as np

def encode(img, img_key): # 加密、解密方法
    result = img = cv2.bitwise_xor(img, img_key)  # 两图像做异或运算
    return result

flower = cv2.imread("amygdalus triloba.png")  # 花原始图像
rows, colmns, channel = flower.shape  # 原图像的行数、列数和通道数
# 创建与花图像大小相等的随机像素图像，作为密钥图像
img_key = np.random.randint(0, 256, (rows, colmns, 3), np.uint8)

cv2.imshow("1", flower)  # 展示花图像
cv2.imshow("2", img_key)  # 展示秘钥图像

result = encode(flower, img_key)  # 对花图像进行加密
cv2.imshow("3", result)  # 展示加密图像
result = encode(result, img_key)  # 对花图像进行解密
cv2.imshow("4", result)  # 展示加密图像
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
