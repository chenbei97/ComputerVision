import cv2

video = cv2.VideoCapture("公司宣传.avi") # 打开视频文件
fps = video.get(cv2.CAP_PROP_FPS) # 获取视频文件的帧速率
# 获取视频文件的帧大小
size = (int(video.get(cv2.CAP_PROP_FRAME_WIDTH)),
        int(video.get(cv2.CAP_PROP_FRAME_HEIGHT)))
fourcc = cv2.VideoWriter_fourcc('X', 'V', 'I', 'D') # 确定视频被保存后的编码格式
output = cv2.VideoWriter("ten_Seconds.avi", fourcc, fps, size) # 创建VideoWriter类对象
frame_Num = 10 * fps # 视频文件的前10秒视频含有的帧数
# 视频文件被打开后且视频文件的前10秒视频含有的帧数大于0
while (video.isOpened() and frame_Num > 0):
    retval, frame = video.read() # 读取视频文件
    if retval == True: # 读取到视频文件后
        output.write(frame) # 在VideoWriter类对象中写入读取到的帧
    frame_Num -= 1 # 视频文件的前10秒视频含有的帧数减少一帧
# 控制台输出提示信息
print("公司宣传.avi的前10s视频已经保存为PyCharm当前项目路径下的ten_Seconds.avi。")
video.release() # 关闭视频文件
output.release() # 释放VideoWriter类对象
