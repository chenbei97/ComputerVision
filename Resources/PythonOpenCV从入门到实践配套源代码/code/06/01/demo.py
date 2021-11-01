import cv2
import numpy as np

# 创建宽150、高150、3通道，像素类型为无符号8位数字的零值图像
mask = np.zeros((150, 150, 3), np.uint8)
mask[50:100, 20:80, :] = 255;  # 50~100行、20~80列的像素改为纯白像素
cv2.imshow("mask1", mask)  # 展示掩模
mask[:, :, :] = 255;  # 全部改为纯白像素
mask[50:100, 20:80, :] = 0;  # 50~100行、20~80列的像素改为纯黑像素
cv2.imshow("mask2", mask)  # 展示掩模
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
