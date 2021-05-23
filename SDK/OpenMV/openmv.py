import sensor,image,time,lcd
from pyb import UART
import math

#RX B11
#TX B10
ball_threshold = (30, 49, 27, 60, 0, 60)  # 色彩阙值
length_and_width_difference = 20  # 图像的长宽差，限制阙值
area = [0,35,160,10]#ROI
MAX_Size = 80  # 最大面积
MIN_Size = 10  # 最小面积

# 初始化摄像头
clock = time.clock()# 跟踪FPS帧率
sensor.reset()  # 初始化光感元件
if sensor.get_id() == sensor.OV7725:
    sensor.set_hmirror(True)  # 水平方向翻转
    sensor.set_vflip(True)  # 垂直方向翻转
sensor.set_pixformat(sensor.RGB565)  # 设置为rgb
sensor.set_framesize(sensor.QQVGA)  # 设置图像大小
sensor.skip_frames(20)  # 跳过前20帧
sensor.set_auto_exposure(False,2000)
sensor.set_auto_whitebal(False)  # 关闭自动白平衡
sensor.set_auto_gain(False)  # 关闭自动增益

sensor.set_brightness(3)
sensor.set_contrast(3)
sensor.set_saturation(3)

uart = UART(3, 19200) #初始化串口三


def process_current_frame():
    global blob
    blob=find_ball()

    if blob!=0:
        area[0] = blob[0] - 20
        area[2] = blob[2] + 40
        location=location1(blob)   #选取位置计算方式和验证
        draw_figure()
        prioblob=blob
        #没输出就是没有找到小球
    else:
        area[0] = 0
        area[2] = 160


def find_ball():
    global img
    target_ball = 0
    img = sensor.snapshot().lens_corr(strength=0.5, zoom=1.0)
    blobs = img.find_blobs([ball_threshold], roi=area, pixels_threshold=5)
    #print(blobs)

    for i in blobs:
        i_MAXSize = 0
        i_size = i[2]*i[3]
        if i_size > i_MAXSize and i_size > MIN_Size and math.fabs(i[2] - i[3]) < length_and_width_difference and i_size < MAX_Size:
            i_MAXSize = i_size
            target_ball = i
            print(target_ball)
    return target_ball

def location1(blob):
    #最简单的根据小球中心点坐标判定偏移
    x = blob[5]
    length = 305  #单位为毫米
    x = 305 * ( x / 160)
    h = str(int(x))
    if h != 0:
        uart.write(h+"\r\n")
    print(h)
    return x

def draw_figure():
    img.draw_cross(blob[5], blob[6])  # cx,cy


while(True):
    clock.tick()
    process_current_frame()
    print("FPS:", clock.fps())
    print("*****************************************")
