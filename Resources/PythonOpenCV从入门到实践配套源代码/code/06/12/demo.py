import cv2

# 拼接图像方法
def overlay_img(img, img_over, img_over_x, img_over_y):
    img_h, img_w, img_p = img.shape  # 背景图像宽、高、通道数
    img_over_h, img_over_w, img_over_c = img_over.shape  # 覆盖图像宽、高、通道数
    if img_over_c <= 3:  # 通道数小于等于3
        img_over = cv2.cvtColor(img_over, cv2.COLOR_BGR2BGRA)  # 转换成4通道图像
    for w in range(0, img_over_w):  # 遍历列
        for h in range(0, img_over_h):  # 遍历行
            if img_over[h, w, 3] != 0:  # 如果不是全透明的像素
                for c in range(0, 3):  # 遍历三个通道
                    x = img_over_x + w  # 覆盖像素的横坐标
                    y = img_over_y + h  # 覆盖像素的纵坐标
                    if x >= img_w or y >= img_h:  # 如果坐标超出最大宽高
                        break
                    img[y, x, c] = img_over[h, w, c]  # 覆盖像素
    return img

smoking = cv2.imread("smoking.png", cv2.IMREAD_UNCHANGED)  # 吸烟图像，保持原格式
no_img = cv2.imread("no.png", cv2.IMREAD_UNCHANGED)  # 禁止图像，保持原格式
cv2.imshow("no", no_img)  # 展示禁止图像
cv2.imshow("smoking", smoking)  # 展示禁止图像
img = overlay_img(smoking, no_img, 95, 90)  # 将禁止图像覆盖到吸烟图像之上
cv2.imshow("no smoking", img)  # 展示覆盖结果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体