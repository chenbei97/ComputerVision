import cv2

video = cv2.VideoCapture("公司宣传.avi") # 打开视频文件
while (video.isOpened()): # 视频文件被打开后
    retval, img_Color = video.read() # 读取视频文件
    # 设置“Video”窗口的宽为420，高为300
    cv2.namedWindow("Gray", 0)
    cv2.resizeWindow("Gray", 420, 300)
    if retval == True: # 读取到视频文件后
        # 把“公司宣传.avi”由彩色视频转换为灰度视频
        img_Gray = cv2.cvtColor(img_Color, cv2.COLOR_BGR2GRAY)
        cv2.imshow("Gray", img_Gray) # 在窗口中显示读取到的视频文件
    else: # 没有读取到视频文件
        break
    key = cv2.waitKey(1) # 窗口的图像刷新时间为1毫秒
    if key == 27: # 如果按下Esc键
        break
video.release() # 关闭视频文件
cv2.destroyAllWindows() # 销毁显示视频文件的窗口
