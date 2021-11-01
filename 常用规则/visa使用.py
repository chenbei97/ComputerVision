#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : visa使用.py
@Author : chenbei
@Date : 2021/8/27 8:02
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
from matplotlib.font_manager import FontProperties
import numpy as np
import pandas as pd
import os
import time
plt.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
mpl.rcParams['font.size'] = 10.5  # 图片字体大小
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
mpl.rcParams['agg.path.chunksize'] = 10000
plt.rcParams['figure.figsize'] = (7.8, 3.8)  # 设置figure_size尺寸
plt.rcParams['savefig.dpi'] = 600  # 图片像素
plt.rcParams['figure.dpi'] = 600  # 分辨率
font_set = FontProperties(fname=r"C:\Windows\Fonts\simsun.ttc", size=10.5)

'''
常见命令：
（1）print("读取数据的模式：",inst.query(":WAVeform:MODE?"))返回 NORM、MAX 或 RAW
NORM：读取当前屏幕显示的波形数据、
MAX：运行状态下，读取屏幕显示的波形数据；停止状态下，读取内存中的波形数据、
RAW：读取内存中的波形数据。注意：内存中的数据必须在示波器停止状态下进行读取，且读取过程中不可操作示波器
<设置读取模式为NORM> ":WAV:MODE NORM"，默认NORM

（2）print("读取数据的模式：",inst.query(":WAVeform:SOURce?"))设置或查询波形数据读取的通道源
查询返回 D0、D1、D2、D3、D4、D5、D6、D7、D8、D9、D10、D11、D12、D13、D14、D15、CHAN1、CHAN2、CHAN3、CHAN4 或 MATH
<设置通道源为CH2> ":WAVeform:SOURce CHANnel2" 默认CHANnel1

（3）print("读取数据的格式：",inst.query(":WAVeform:FORMat?"))设置或查询读取数据的模式 查询返回 WORD、BYTE 或 ASC
WORD：一个波形点占两个字节（即 16 位），低 8 位有效，高 8 位为 0
BYTE：一个波形点占一个字节（即 8 位）使用公式(0x8E - YORigin - YREFerence) × YINCrement将读取的波形数据转换为波形中每一点的电压值
WORD 或 BYTE 格式：返回的数据由两部分组成，分别是 TMC 数据描述头和波形数据，分批次读取时也是两个组成
ASCii：以科学计数形式返回各波形点的实际电压值，各电压值之间以逗号分隔(常用)
注：源（:WAVeform:SOURce）设为数字通道（D0 至 D15）时，查询固定以 BYTE 格式返回波形数据 见P208页
<设置波形数据的返回格式为 WORD> ":WAVeform:FORMat WORD"

（4）:WAVeform:XINCrement 查询当前选中通道源 X 方向上相邻两点之间的时间间隔
NORMal 模式下，XINCrement = TimeScale/100
RAW 模式下，XINCrement = 1/SampleRate
MAX 模式下，仪器处于运行状态时，XINCrement = TimeScale/100；仪器处于停止状态时，XINCrement = 1/SampleRate
单位与当前的通道源相关：
通道源为 CHANnel1 至 CHANnel4、D0 至 D15 时，单位为 s
通道源为 MATH 且运算为 FFT 时，单位为 Hz

（5）:WAVeform:XORigin 查询当前选中通道源 X 方向上波形数据的起始时间
NORMal 模式下，返回屏幕显示的波形数据的起始时间
RAW 模式下，返回内存中波形数据的起始时间
MAX 模式下，仪器处于运行状态时，返回屏幕显示的波形数据的起始时间；仪器处于停止状态时，返回内存中波形数据的起始时间
通道源为 CHANnel1 至 CHANnel4、D0 至 D15 时，单位为 s
通道源为 MATH 且运算为 FFT 时，单位为 Hz

（6）:WAVeform:XREFerence 查询当前选中通道源 X 方向上波形点的时间参考基准
查询返回 0（即屏幕或内存中第一个波形点）

（7）:WAVeform:YINCrement 查询当前通道源 Y 方向上波形的步进值，单位与当前幅度单位一致
NORMal 模式下，YINCrement = VerticalScale/25
RAW 模式下，YINCrement 与内存波形的 Verticalscale 和当前选择的 Verticalscale 有关
MAX 模式下，仪器处于运行状态时，YINCrement = VerticalScale/25；仪器处于停止状态时，YINCrement 与内存波形的 Verticalscale 和当前选择的 Verticalscale 有关

（8）:WAVeform:YORigin 查询当前选中通道源 Y 方向上相对于垂直参考位置的垂直偏移
NORMal 模式下，YORigin = VerticalOffset/YINCrement
RAW 模式下，YORigin 与内存波形的 Verticalscale 和当前选择的 Verticalscale 有关
MAX 模式下，仪器处于运行状态时，YORigin = VerticalOffset/YINCrement；仪器处于停止状态时，YORigin与内存波形的 Verticalscale 和当前选择的 Verticalscale 有关

（9）:WAVeform:YREFerence 查询当前选中通道源 Y 方向的垂直参考位置
NORMal 模式下，YREFerence 固定为 127（屏幕底端为 0，顶端为 255）
RAW 模式下，YREFerence 与内存波形的 Verticalscale 和当前选择的 Verticalscale 有关
MAX 模式下，仪器处于运行状态时，YREFerence 固定为 127（屏幕底端为 0，顶端为 255）；仪器处于停止状态时，YREFerence 与内存波形的 Verticalscale 和当前选择的 Verticalscale 有 关

（10）:WAV:STAR and :WAV:STOP 在RAW模式下读取数据时设置读取的波形起始和结束位置
<设置波形数据读取的起始点为第1个波形点 > ":WAV:STAR 1"
<设置波形数据读取的终止点为第120000个波形点> ":WAV:STOP 120000"

（11） :WAV:DATA?  分为读取屏幕数据和内存数据
    ① 读取屏幕数据，:WAVeform:MODE NORM 结合（1）-（3）的设置读取读取屏幕波形数据
    ② 读取内存数据，:WAVeform:MODE RAW
    单次可读取波形点数的最大值与当前波形数据返回格式有关 {BYTE：250000 WORD：125000 ASCii：15625}
    根据示波器存储深度和当前单次可读取波形点数的最大值判断是可以一次性读取还是需要分批次读取
        1）示波器的存储深度小于或等于当前单次可读取波形点数的最大值时，可以一次性读取内存波形数据
        example：存储深度=120kpts=120,000，format=byte <250000
         :STOP   # 内存波形数据必须在示波器处于停止状态时进行读取
         :WAV:SOUR CHAN1  # 设置通道源为 CH1
         :WAV:MODE RAW # 设置波形读取模式为 RAW
         :WAV:FORM BYTE # 设置波形数据的返回格式为 BYTE
         :WAV:STAR 1 # 设置波形数据读取的起始点为第1个波形点 
         :WAV:STOP 120000 # 设置波形数据读取的终止点为第120000个波形点
         :WAV:DATA? 读取内存波形数据（所有点）
        2）示波器的存储深度大于当前单次可读取波形点数的最大值时，需要分批次读取内存波形数据
           每次仅读取内存中一块区域的波形数据，然后将多次读取的数据按顺序进行拼接即可
        example：存储深度=300kpts=300,000，format=word >125000
                 内存波形数据至少需要分 3 次 （300000/125000=2.4）进行读取
                 :STOP 
                 :WAV:SOUR CHAN1 
                 :WAV:MODE RAW 
                 :WAV:FORM WORD 
                 :WAV:STAR 1 # 设置第1次读取的起始点为第1个波形点
                 :WAV:STOP # 125000 设置第1次读取的终止点为第125000个波形点 
                 :WAV:DATA? # 读取内存中第1个至第125000个波形点的数据
                 :WAV:STAR 125001 # 设置第2次读取的起始点为第125001个波形点 
                 :WAV:STOP 250000 # 设置第2次读取的终止点为第250000个波形点 
                 :WAV:DATA? 
                 :WAV:STAR 250001 
                 :WAV:STOP 300000
                 :WAV:DATA?   
<读取通道1的屏幕波形数据> ":WAV:DATA? CHAN1"

（12）inst.query(':WAVeform:PREamble?').split(',') 查询并返回全部的波形参数
<format>,<type>,<points>,<count>,<xincrement><xorigin>,<xreference>,<yincrement>,<yorigin>,<yreference>
<format> 数据返回格式0（BYTE）、1（WORD）或 2（ASC√）
<type> 数据读取模式0（NORMal√）、1（MAXimum）或 2（RAW）
<points>：1 至 12000000 之间的整数，安装存储深度选件后，<points>为 1 至 24000000 之间的整数
<count>：平均采样方式(type=1)下为平均的次数，其它方式下为 1
<xincrement><yincrement>：X/Y 方向上的相邻两点之间的时间差 
    NORM格式 xincrement=time_scale/100 yincrement=vertical_scale/25
    RAW格式 xincrement=1/sample_rate yincrement与内存波形的vertical_scale和当前选择的vertical_scale有关
<xorigin><yorigin>：X/Y的波形初始点位置
<xreference><yreference>：X/Y的基准线位置

（14）":ACQuire:MDEPth" 设置或查询示波器的存储深度（即在一次触发采集中所能存储的波形点数）
存储深度=采样率×波形长度   其中波形长度=水平时基×屏幕水平格数
<设置存储深度12000pts> ":ACQuire:MDEPth 12000"   默认AUTO 示波器根据当前的采样率自动选择存储深度
注：
<采样率设置> ":ACQuire:SRATe?"
<水平时基> ":TIMebase[:MAIN]:SCALe"
<屏幕水平格数> 对于MSO1000Z/DS1000Z，屏幕水平格数为 12

（15）print("采样率：" ,float(inst.query(":ACQuire:SRATe?")))查询当前的采样率，每秒采样的波形点数

（16）":TIMebase[:MAIN]:SCALe?" 设置或查询主时基档位，默认单位为 s/div, 屏幕水平轴上每格所代表的时间长度
YT 模式：5ns/div 至 50s/div，1-2-5 步进 ,YT模式继续分为普通、滚动、单/双ZOOM、插值模式
    普通模式：采样是分次且独立的，采样之间存在死区，适用于观察周期性信号，水平时基较大时采样时间变长，波形刷新较慢
    滚动模式：采样实时显示，没有死区，测量低频信号时可以实时观察信号是否存在异常 采集到的波形从右往左滚动显示
    XY模式：将时基关闭，而使用另外一个通道的输入作为水平信号，以便观察这两个信号的关系
Roll 模式：200ms/div 至 50s/div，1-2-5 步进
注：当水平时基模式为 YT，水平时基为 200ms/div 或更大 示波器在停止过程中该命令不可用
<设置主时基档位为 200μs/div> ":TIMebase:MAIN:SCALe 0.0002"

（17）":TIMebase:MODE?" 设置或查询水平时基模式 有MAIN(YT)、XY和ROLL模式
<设置水平时基模式为 XY 模式> ":TIMebase:MODE XY"

（18）
'''
import pyvisa as visa
Address = 'USB0::0x1AB1::0x04CE::DS1ZC231101081::INSTR'
Equipment_type = "DS1104ZPlus"
class VisaIOError(Exception):
    def __init__(self):
        super().__init__()
    def __str__(self):
        # 打印错误信息
        return "Instrument connection failed, please reconnect..."
rm = visa.ResourceManager()
rm.InputBufferSize = 2048
try :
    inst = rm.open_resource(resource_name=Address)
except Exception :
    print(VisaIOError())
else:
    print(f"The instrument has been successfully connected !")
    inst.write("*IDN?")
    print(f"*IDN return : {inst.read()}")
    inst.write(" :RUN")
    inst.write("*TST?") # 执行一次自检并返回自检结果
    inst.write("*WAI") # 当前操作命令已执行完后才可以进行后续命令
    # inst.write(":DISPlay:CLEar")
    # inst.write(":CALibrate:STARt") # 自校准
finally:
    print(f"The instrument {Equipment_type} address you are trying to connect to is {Address}")
# inst.read_bytes() # 字节流
#  时基长度*12*采样率=存储深度 所有通道共用 最小12K=12000 最大2400,0000=24M
#  深度只有5个可选值 {12000、12,0000、120,0000、1200,0000、2400,0000} = {12k,120k,1200k,12M,24M}
inst.write(":CHANnel1:DISPlay ON") # 打开channel_1
for channel in range(3):
    # 关闭其他通道
    inst.write(":CHANnel"+str(channel+2)+":DISPlay OFF")
MDEPTH = 12000
inst.write(":ACQuire:MDEPth "+str(MDEPTH)) # 只能单通道去调整,多通道不能调整！！！一旦设定即通道均分
inst.write(":CHANnel2:DISPlay ON")
inst.write(":FUNCtion:WRECord:OPERate RUN") # 启动波形录制
print(f"当前可录制的最大帧数：{inst.query(':FUNCtion:WRECord:FMAX?')}")
# 若当前正在录制，返回RUN；若录制完成，返回STOP
print(f"波形正在录制？：{inst.query(':FUNCtion:WRECord:OPERate?')}")
print(f"波形录制帧数：{inst.query(':FUNCtion:WRECord:FEND?')}")

def set_and_return_waveform_para(which_channel=1,format=3,mode=1,time_scale=0.001,
                                 probe=1,couple="DC",bandlimit="20M",invert="OFF",unit="V"):
    # time_scale * 12 * sample_rate = depth  eg : 1e-4 * 12 * 5e6 = 6k pts
    # default format=Ascii , mode = Norm ,y_reference=127
    formats_str = ["WORD","BYTE","ASCii"]
    modes_str  = ["NORM","MAXimum","RAW"]
    unit_dict = {"V":"VOLTage","W":"WATT","A":"AMPere","U":"UNKNown"}
    inst.write(":WAV:SOUR CHAN" + str(which_channel))
    inst.write(":TIMebase:MAIN:SCALe " + str(time_scale))
    inst.write(":WAV:FORMAT "+ formats_str[format-1])
    inst.write(f":CHANnel{which_channel}:PROBe {str(probe)}") # 探头比
    inst.write(f":CHANnel{which_channel}:COUPling {couple}")  # 耦合方式
    inst.write(f":CHANnel{which_channel}::BWLimit {bandlimit}")  # 带宽限制
    inst.write(f":CHANnel{which_channel}:INVert {invert}")  # 是否反相
    inst.write(f":CHANnel{which_channel}:UNITs {unit_dict[unit]}")  # 单位
    if mode == 3:
        inst.write(" :STOP")
        inst.write(" :WAV:MODE RAW") # 内存模式读取
        inst.write(":WAV: STAR 1")
        if (inst.query(":WAVeform:FORMat?")=="BYTE" and MDEPTH<=250000 ) \
            or (inst.query(":WAVeform:FORMat?")=="WORD" and MDEPTH<=125000) \
            or (inst.query(":WAVeform:FORMat?")=="ASCii" and MDEPTH<=15625) :
            inst.write(":WAV: STAR "+str(MDEPTH))
        inst.write(":WAV:DATA?")
        data = inst.read()
    else:
        inst.write(":WAV:MODE " + modes_str[mode - 1])
        inst.write(":WAV:DATA?")
        data = inst.read()  # 普通模式读取

    print(f"channel{which_channel}_sample_rate：{float(inst.query(':ACQuire:SRATe?'))}" ) # 查询当前采样率 最大采样率<1GHz=5e8Hz

    Waveform_paras_value = inst.query(':WAV:PREamble?').split(',')  # P213
    Waveform_paras_dict = {}
    # x_increment = time_scale/100 y_increment = vertical_scale/25
    Waveform_paras = ["format", "type", "point", "count", "x_increment",
                      "x_origin", "x_reference", "y_increment", "y_origin", "y_reference"]
    for index, element in enumerate(Waveform_paras):
        Waveform_paras_dict[Waveform_paras[index]] = Waveform_paras_value[index]

    return  data , Waveform_paras_dict
data_chan1,Waveform_paras_dict1 = set_and_return_waveform_para(which_channel=1,time_scale=0.001,probe=10,mode=1,invert="ON")
time.sleep(1)
data_chan2,Waveform_paras_dict2 = set_and_return_waveform_para(which_channel=2,time_scale=0.001,probe=5,mode=1,invert="OFF")
rm.close()
def plot_and_return_data(data_str,label,TMC_length=10):
    data_str = data_str.split(',')
    data_str[0] = data_str[0][TMC_length]
    data = [float(element) for element in data_str]
    # data_ave = ( min(data) + max(data) ) / 2
    # color = [int(1) if element > data_ave  else 0 for element in data]
    plt.plot(data,label=label,color='r')
    plt.legend(loc='upper right')
    plt.show()
    return data
data_chan1 = plot_and_return_data(data_str=data_chan1,label='channel_1')
data_chan2 = plot_and_return_data(data_str=data_chan2,label='channel_2')
# rm.list_resources()
# rm.list_resources_info()
# rm.list_opened_resources()
# rm.resource_info(resource_name=address)
# rm.get_instrument(resource_name=address)