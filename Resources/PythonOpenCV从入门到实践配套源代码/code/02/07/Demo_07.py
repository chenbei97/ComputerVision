import cv2

rgb_image = cv2.imread("D:/2.1.jpg")
b, g, r = cv2.split(rgb_image) # 拆分图2.1中的通道
bgr = cv2.merge([b, g, r]) # 按B→G→R的顺序合并通道
cv2.imshow("BGR", bgr)
rgb = cv2.merge([r, g, b]) # 按R→G→B的顺序合并通道
cv2.imshow("RGB", rgb)
cv2.waitKey()
cv2.destroyAllWindows()
