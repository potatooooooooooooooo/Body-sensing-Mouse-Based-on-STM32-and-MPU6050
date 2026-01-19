## 项目简介
本项目是基于STM32和MPU6050的体感鼠标。项目通过使用Mahony算法实现姿态解算，利用无线模块实现数据传输，并最终实现了航姿仪姿态数据的实时解算与体感鼠标的姿态感应控制。

>本项目为本科课设，没想到过了近两年还有同学记得这个项目，于是直接开源到这里。
>当时做的比较简陋，欢迎大家在此基础上各显神通，做出更多好玩的东西。

## 项目功能
1.STM32采集传感器的数据，对姿态信息进行解算，并通过OLED屏幕进行显示，角度差小于1°。
2.按键控制LED灯的呼吸效果。
3.航姿仪系统发射端和体感鼠标接收端的板间通信，由无线模块接收姿态信息。
4.通过USB接口驱动电脑鼠标移动，实现左右键单双击等功能。

## 整体方案设计
STM32通过对传感器采集到的数据进行解算，得到当前姿态的数据，通过OLED屏幕对解算出的数据进行显示。通过按键来控制LED灯呼吸的效果。航姿仪系统方案设计设计总体框图如图：
<img width="511" height="312" alt="image" src="https://github.com/user-attachments/assets/a066953e-c979-45e9-b3bb-daf06ff3d179" />

在航姿仪的基础上，使用无线模块实现航姿仪与数据接收板之间的通信，数据接收板判断接收到的数据包合法后，与STM32之间采用SPI协议传输数据，然后根据传送的控制命令与PC进行USB HID交互，实现鼠标的上下左右移动以及单击双击效果。
<img width="736" height="253" alt="image" src="https://github.com/user-attachments/assets/6c71ad73-d736-45d4-9ef1-0bd85360f00a" />


本方案的设计思想是将航姿仪系统与无线通信技术相结合，通过数据解算和显示，以及无线传输，实现一个体感鼠标的功能。设计分为两个主要部分：航姿仪的发射端和数据接收板的接收端。

## 原理解析（硬件说明）
航姿仪电路主要包括STM32、电源模块、MPU6050模块、LED模块、OLED模块等几部分。航姿仪原理图如图：
<img width="666" height="469" alt="image" src="https://github.com/user-attachments/assets/37ab04bf-6070-4896-8b21-b9368998bc4f" />


数据接收板电路包括STM32、电源模块、无线模块和USB等几部分。数据接收板原理图如图：
<img width="642" height="454" alt="image" src="https://github.com/user-attachments/assets/3c3be9d0-2300-42ff-b66c-11b76bdc3d1c" />

硬件开源链接：
https://oshwhub.com/magic-stick/bang-bang-1-0
## 软件代码
<img width="1986" height="963" alt="image" src="https://github.com/user-attachments/assets/009072c7-8007-4b2d-8ad7-9a95eedfebaf" />
<img width="1923" height="954" alt="image" src="https://github.com/user-attachments/assets/577214ef-a340-426a-b296-c495d7033003" />
<img width="1947" height="965" alt="image" src="https://github.com/user-attachments/assets/1a278187-ecd6-45e3-acc0-d12a46a0e6f9" />


## 实物图
<img width="595" height="361" alt="image" src="https://github.com/user-attachments/assets/f7554155-90ea-4276-b084-67e0d739c658" />

<img width="473" height="192" alt="image" src="https://github.com/user-attachments/assets/673eba02-c004-4d9e-a124-1b6aa2841897" />

<img width="494" height="241" alt="image" src="https://github.com/user-attachments/assets/55066679-662f-45d3-9d1e-86495b61305b" />

<img width="367" height="207" alt="image" src="https://github.com/user-attachments/assets/c89c468f-00c5-4929-916c-4035a52b1f03" />

## 补充测试
我们对航姿仪解算的角度进行了转台测试
<img width="376" height="304" alt="image" src="https://github.com/user-attachments/assets/d90282fd-8cc9-421b-9e98-2a4f3f0b9c37" />

得到三轴的测试数据如下：
横滚角roll测试数据：
<img width="621" height="366" alt="image" src="https://github.com/user-attachments/assets/516fb8c5-de11-4345-972e-b5f5de7d88e1" />

俯仰角pitch测试数据：
<img width="604" height="388" alt="image" src="https://github.com/user-attachments/assets/46f7aa12-affa-4e8f-9d0a-8d1131f903b0" />

偏航角yaw测试数据：
<img width="675" height="402" alt="image" src="https://github.com/user-attachments/assets/485741a0-34e8-4cd3-a671-207f2d5fcb2d" />

造成航姿仪数据误差可能是因为MPU6050陀螺仪本身的三轴加速度计并不正交，因此在程序初始化时就有误差而经过六面校准算法后的测试数据就好了很多。
偏航角无法通过加速度计进行校正数据，因此有较大的偏差。另外就是受限于陀螺仪本身的精度问题。
