#RX B11
#TX B10

ball_threshold=(0, 100, 50, 127, -128, 127)#色彩阙值
area=[0,60,320,40]#ROI
area_HD=[0,70,30,30]
length_and_width_difference=20#图像的长宽差，限制阙值


#图像数据
img=0
blob=0
prioblob=0
flag=0 #运行标志位
prioprioblob=0

#初始化阶段
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
sensor.set_contrast(+3)

clock = time.clock() # 跟踪FPS帧率
uart = UART(3, 19200) #初始化串口三

def find_ball():
    #引入和声明数据
    global fps
    global img
    target_ball=0
    target_ball_size=0
    #先查找色块
    img = sensor.snapshot().lens_corr(strength=1.1, zoom=1.0)
    blobs = img.find_blobs([ball_threshold], roi=area,pixels_threshold=30)
    for i in blobs:
        i_size=i[2]*i[3]
        print(i_size)
        if i_size>target_ball_size and (i[2]+length_and_width_difference>i[3]) and (i[2]-length_and_width_difference<i[3])and (i_size<400):
            target_ball=i
            target_ball_size=i_size

    if(target_ball_size==0):
        return 0

    print(target_ball)
    return target_ball


def init_data():
    global area
    global prioblob
    global prioprioblob
    global blob
    while prioblob==0:
        blob=find_ball()
        prioblob=blob
        prioprioblob=blob

def location1(blob):
    area_HD[0]=blob[5]-15
#    for c in img.find_circles(threshold = 1000, x_margin = 10, y_margin = 10, r_margin = 10,r_min = 3, r_max =5, r_step = 2,area=area_HD):
#        if(c.x()+2>blob[5]) and (c.x()-2<blob[5]):
    #最简单的根据小球中心点坐标判定偏移
    x=blob[5]
    length=305  #单位为毫米
    x=305*(x/320)
    h=str(int(x))
    uart.write(h+"\r\n")
    #""+"\r\n"
    #print(h+"\r\n")
    print(h)
    return x



def draw_figure():
    x = blob[0]-3
    y = blob[1]-3
    w = blob[2]+6
    h = blob[3]+6
    outside_rect = (x,y,w,h)
    #img.draw_rectangle(blob[0:4])  # rect
    #img.draw_rectangle(outside_rect[0:4])  # rect
    img.draw_cross(blob[5], blob[6])  # cx,cy

def process_current_frame():
    global blob
    global prioblob
    global prioprioblob
    blob=find_ball()
    if blob!=0:
        location=location1(blob)   #选取位置计算方式和验证
        draw_figure()
        #img.draw_string(blob[5]+4, blob[6]+4, "location="+"%.3f" %location,color=(255,0,0))
        prioprioblob=prioblob
        prioblob=blob
        #没输出就是没有找到小球




while(True):
    clock.tick()
    process_current_frame()
    print("FPS:", clock.fps())
    print("*****************************************")
