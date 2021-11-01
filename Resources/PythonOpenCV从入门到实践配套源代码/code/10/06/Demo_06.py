import cv2
import numpy as np
import math

image = cv2.imread("image.png")  # 读取原始图像
templ = cv2.imread("templ.png")  # 读取模板图像
height, width, c = templ.shape  # 获取模板图像的高度、宽度和通道数
results = cv2.matchTemplate(image, templ, cv2.TM_CCOEFF_NORMED)  # 按照标准相关系数匹配
point_X = []  # 用于存储最佳匹配结果左上角横坐标的列表
point_Y = []  # 用于存储最佳匹配结果左上角纵坐标的列表
for y in range(len(results)):  # 遍历结果数组的行
    for x in range(len(results[y])):  # 遍历结果数组的列
        if results[y][x] > 0.99:  # 如果相关系数大于0.99则认为匹配成功
            # 在最佳匹配结果位置绘制红色方框
            cv2.rectangle(image, (x, y), (x + width, y + height), (255, 0, 0), 2)
            point_X.extend([x])  # 把最佳匹配结果左上角的横坐标添加到列表中
            point_Y.extend([y])  # 把最佳匹配结果左上角的纵坐标添加到列表中
# 出发点的横、纵坐标
start_X = 62
start_Y = 150
# 计算出发点到人民广场地铁站的距离
place_Square = np.array([point_X[0], point_Y[0]])
place_Start = np.array([start_X, start_Y])
minus_SS = place_Start - place_Square
start_Square = math.hypot(minus_SS[0], minus_SS[1])
# 计算出发点到解放大路地铁站的距离
place_Highroad = np.array([point_X[1], point_Y[1]])
minus_HS = place_Highroad - place_Start
start_Highroad = math.hypot(minus_HS[0], minus_HS[1])
# 用绿色的线画出距离较短的路线
if start_Square < start_Highroad:
    cv2.line(image, (start_X, start_Y), (point_X[0], point_Y[0]), (0, 255, 0), 2)
else:
    cv2.line(image, (start_X, start_Y), (point_X[1], point_Y[1]), (0, 255, 0), 2)
cv2.imshow("result", image)  # 显示匹配的结果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体