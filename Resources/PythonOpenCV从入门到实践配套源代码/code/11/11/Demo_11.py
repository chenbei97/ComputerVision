import cv2

capture = cv2.VideoCapture(0, cv2.CAP_DSHOW) # 打开笔记本内置摄像头
fourcc = cv2.VideoWriter_fourcc('X', 'V', 'I', 'D') # 确定视频被保存后的编码格式
fps = 20 # 帧速率
# 创建VideoWriter类对象
output = cv2.VideoWriter("ten_Seconds.avi", fourcc, fps, (640, 480))
frame_Num = 10 * fps # 时长为10秒的摄像头视频含有的帧数
# 笔记本内置摄像头被打开且时长为10秒的摄像头视频含有的帧数大于0
while (capture.isOpened() and frame_Num > 0):
    retval, frame = capture.read() # 从摄像头中实时读取视频
    if retval == True: # 读取到摄像头视频后
        output.write(frame) # 在VideoWriter类对象中写入读取到的帧
        cv2.imshow("frame", frame) # 在窗口中显示摄像头视频
    key = cv2.waitKey(1) # 窗口的图像刷新时间为1毫秒
    frame_Num -= 1 # 时长为10秒的摄像头视频含有的帧数减少一帧
capture.release() # 关闭笔记本内置摄像头
output.release() # 释放VideoWriter类对象
cv2.destroyAllWindows() # 销毁显示摄像头视频的窗口
