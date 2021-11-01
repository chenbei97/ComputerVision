import cv2

cap = cv2.VideoCapture(0, cv2.CAP_DSHOW) # 打开笔记本内置摄像头
while (cap.isOpened()): # 笔记本内置摄像头被打开后
    ret, frame = cap.read() # 从摄像头中实时读取视频
    cv2.imshow("Video", frame) # 在窗口中显示视频
    k = cv2.waitKey(1) # 图像的刷新时间为1毫秒
    if k == 32: # 按下空格键
        cap.release() # 关闭笔记本内置摄像头
        cv2.destroyWindow("Video") # 销毁名为Video的窗口
        cv2.imwrite("D:/copy.png", frame) # 保存按下空格键时摄像头视频中的图像
        cv2.imshow('img', frame) # 显示按下空格键时摄像头视频中的图像
        cv2.waitKey() # 刷新图像
        break
cv2.destroyAllWindows() # 销毁显示图像的窗口
