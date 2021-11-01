import cv2

video = cv2.VideoCapture("公司宣传.avi") # 打开视频文件
fps = video.get(cv2.CAP_PROP_FPS) # 获取视频文件的帧速率
frame_Num = 1 # 用于记录第几幅图像（即第几帧），初始值为1（即第1幅图像）
while (video.isOpened()): # 视频文件被打开后
   retval, frame = video.read() # 读取视频文件
   # 设置“Video”窗口的宽为420，高为300
   cv2.namedWindow("Video", 0)
   cv2.resizeWindow("Video", 420, 300)
   if retval == True: # 读取到视频文件后
      # 当前视频播放到第几帧
      cv2.putText(frame, "frame: " + str(frame_Num), (0, 100),
               cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 0, 255), 5)
      # 该帧对应着视频的第几秒
      cv2.putText(frame, "second: " + str(round(frame_Num / fps, 2)) + "s",
               (0, 200), cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 0, 255), 5)
      cv2.imshow("Video", frame) # 在窗口中显示读取到的视频文件
   else: # 没有读取到视频文件
      break
   key = cv2.waitKey(50) # 窗口的图像刷新时间为50毫秒
   frame_Num += 1 #
   if key == 27: # 如果按下Esc键
      break
video.release() # 关闭视频文件
cv2.destroyAllWindows() # 销毁显示视频文件的窗口
