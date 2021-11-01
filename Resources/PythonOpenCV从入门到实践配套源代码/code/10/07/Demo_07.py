import cv2

def myMatchTemplate(img, templ):  # 自定义方法：获取模板匹配成功后所有红框位置的坐标
    width, height, c = templ.shape  # 获取模板图像的宽度、高度和通道数
    results = cv2.matchTemplate(img, templ, cv2.TM_CCOEFF_NORMED)  # 按照标准相关系数匹配
    loc = list()  # 红框的坐标列表
    for i in range(len(results)):  # 遍历结果数组的行
        for j in range(len(results[i])):  # 遍历结果数组的列
            if results[i][j] > 0.99:  # 如果相关系数大于0.99则认为匹配成功
                # 在列表中添加匹配成功的红框对角线两点坐标
                loc.append((j, i, j + width, i + height))
    return loc

img = cv2.imread("background2.jpg")  # 读取原始图像
templs = list()  # 模板列表
templs.append(cv2.imread("template.png"))  # 添加模板1
templs.append(cv2.imread("template2.png"))  # 添加模板2
templs.append(cv2.imread("template3.png"))  # 添加模板3

loc = list()  # 所有模板匹配成功位置的红框坐标列表
for t in templs:  # 遍历所有模板
    loc += myMatchTemplate(img, t)  # 记录该模板匹配得出的

for i in loc:  # 遍历所有红框的坐标
    cv2.rectangle(img, (i[0], i[1]), (i[2], i[3]), (0, 0, 255), 2)  # 在图片中绘制红框

cv2.imshow("img", img)  # 显示匹配的结果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
