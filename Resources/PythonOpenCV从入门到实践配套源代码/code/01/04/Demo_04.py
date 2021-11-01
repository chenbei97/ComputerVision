import cv2

image_Color = cv2.imread("1.1.jpg") # 读取1.1.jpg
print("获取彩色图像的属性：")
print("shape =", image_Color.shape) # 打印彩色图像的（垂直像素，水平像素，通道数）
print("size =", image_Color.size) # 打印彩色图像包含的像素个数
print("dtype =", image_Color.dtype) # 打印彩色图像的数据类型
image_Gray = cv2.imread("1.1.jpg", 0) # 读取与1.1.jpg（彩色图像）对应的灰度图像
print("获取灰度图像的属性：")
print("shape =", image_Gray.shape) # 打印灰度图像的（垂直像素，水平像素）
print("size =", image_Gray.size) # 打印灰度图像包含的像素个数
print("dtype =", image_Gray.dtype) # 打印灰度图像的数据类型
