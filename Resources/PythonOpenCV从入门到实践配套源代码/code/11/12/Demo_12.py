import cv2

video = cv2.VideoCapture("公司宣传.avi") # 打开视频文件
fps = video.get(cv2.CAP_PROP_FPS) # 获取视频文件的帧速率
# 获取视频文件的帧大小
size = (int(video.get(cv2.CAP_PROP_FRAME_WIDTH)),
        int(video.get(cv2.CAP_PROP_FRAME_HEIGHT)))
fourcc = cv2.VideoWriter_fourcc('X', 'V', 'I', 'D') # 确定视频被保存后的编码格式
output = cv2.VideoWriter("copy.avi", fourcc, fps, size) # 创建VideoWriter类对象
while (video.isOpened()): # 视频文件被打开后
    retval, frame = video.read() # 读取视频文件
    if retval == True: # 读取到视频文件后
        output.write(frame) # 在VideoWriter类对象中写入读取到的帧
    else:
        break
print("公司宣传.avi已经保存为PyCharm当前项目路径下的copy.avi。") # 控制台输出提示信息
video.release() # 关闭视频文件
output.release() # 释放VideoWriter类对象
