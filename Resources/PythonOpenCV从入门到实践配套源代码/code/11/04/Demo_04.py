import cv2

cap_Inner = cv2.VideoCapture(0, cv2.CAP_DSHOW) # 打开笔记本内置摄像头
cap_Outer = cv2.VideoCapture(1, cv2.CAP_DSHOW) # 打开一个连接笔记本的外置摄像头
while (cap_Inner.isOpened() & cap_Outer.isOpened()): # 两个摄像头都被打开后
    retval, img_Inner = cap_Inner.read() # 从笔记本内置摄像头中实时读取视频
    ret, img_Outer = cap_Outer.read() # 从连接笔记本的外置摄像头中实时读取视频
    # 在窗口中显示笔记本内置摄像头读取到的视频
    cv2.imshow("Video_Inner", img_Inner)
    # 在窗口中显示连接笔记本的外置摄像头读取到的视频
    cv2.imshow("Video_Outer", img_Outer)
    key = cv2.waitKey(1) # 窗口的图像刷新时间为1毫秒
    if key == 32: # 如果按下空格键
        break
cap_Inner.release() # 关闭笔记本内置摄像头
cap_Outer.release() # 关闭连接笔记本的外置摄像头
cv2.destroyAllWindows() # 销毁显示摄像头视频的窗口
