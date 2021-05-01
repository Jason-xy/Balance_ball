#TX B10
#RX B11

ball_threshold=(31, 60, 53, 127, 8, 54)
area=(0,0,320,240)
distance=300  #摄像头到杆的距离，单位毫米
redball_blob=100  #小球的初始色块大小，长*宽


#图像数据
img=0
fps=0
blob=0
prioblob=0
flag=0 #运行标志位

import sensor,image,time,lcd
from pyb import UART
import math

# 初始化摄像头
clock = time.clock()
sensor.reset()  # 初始化光感元件
if sensor.get_id() == sensor.OV7725:
    sensor.set_hmirror(True)  # 水平方向翻转
    sensor.set_vflip(True)  # 垂直方向翻转
sensor.set_pixformat(sensor.RGB565)  # 设置为rgb
sensor.set_framesize(sensor.QVGA)  # 设置图像大小
sensor.skip_frames(20)  # 跳过前20帧
sensor.set_auto_whitebal(False)  # 关闭自动白平衡
sensor.set_auto_gain(False)  # 关闭自动增益
#lcd.init() # Initialize the lcd screen.


#初始化串口3
uart = UART(3, 19200)


def process_current_frame():
    global flag
    global blob
    global prioblob
    blob=find_ball()
    if flag==0:
        prioblob=blob
        flag=1
    if blob!=0:
        location=location1(blob)   #选取位置计算方式
        draw_figure()
        img.draw_string(blob[5]+4, blob[6]+4, "location="+"%.3f" %location,color=(255,0,0))
        prioblob=blob



def find_ball():
    global fps
    global img
    max_blob=0
    max_size=0
    fps=clock.tick()
    img = sensor.snapshot().lens_corr(strength=1.3, zoom=1.0)
    blobs = img.find_blobs([ball_threshold], roi=area)
    for blob in blobs:
        blob_area = blob[2] * blob[3]
        if blob_area > max_size:
            max_blob = blob
            max_size = blob_area
    return max_blob



def location1(blob):
    #最简单的根据小球中心点坐标判定偏移
    x=blob[5]
    length=305  #单位为毫米
    x=305*(x/320)
    h=str(int(x))
    uart.write(h+"\r\n")
#""+"\r\n"
    print(h+"\r\n")
    return x

#def location2(blob):
    #根据小球的大小计算偏移量

#def location3(blob)
    #根据小球的速度计算偏移量


def draw_figure():
    x = blob[0]-3
    y = blob[1]-3
    w = blob[2]+6
    h = blob[3]+6
    outside_rect = (x,y,w,h)
    img.draw_rectangle(blob[0:4])  # rect
    img.draw_rectangle(outside_rect[0:4])  # rect
    img.draw_cross(blob[5], blob[6])  # cx,cy


while(True):
    time.sleep_ms(20)
    process_current_frame()
    #lcd.display(sensor.snapshot())
