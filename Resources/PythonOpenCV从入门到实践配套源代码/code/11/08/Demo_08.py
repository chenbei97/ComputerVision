import cv2

video = cv2.VideoCapture("公司宣传.avi") # 打开视频文件
fps = video.get(cv2.CAP_PROP_FPS) # 获取视频文件的帧速率
frame_Count = video.get(cv2.CAP_PROP_FRAME_COUNT) # 获取视频文件的帧数
frame_Width = int(video.get(cv2.CAP_PROP_FRAME_WIDTH)) # 获取视频文件的帧宽度
frame_Height = int(video.get(cv2.CAP_PROP_FRAME_HEIGHT)) # 获取视频文件的帧高度
# 输出获取到的属性值
print("帧速率:", fps)
print("帧数:", frame_Count)
print("帧宽度:", frame_Width)
print("帧高度:", frame_Height)
