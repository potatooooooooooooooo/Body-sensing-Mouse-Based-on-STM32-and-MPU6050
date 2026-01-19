clear;clc;
%六组数据的顺序：X+,X-,Y+,Y-,Z+,Z-
X1 = load('X+.txt'); 
X2 = load('X-.txt'); 
Y1 = load('Y+.txt'); 
Y2 = load('Y-.txt'); 
Z1 = load('Z+.txt'); 
Z2 = load('Z-.txt'); 

axm = [mean(X1(:,1)) mean(X2(:,1)) mean(Y1(:,1)) mean(Y2(:,1)) mean(Z1(:,1)) mean(Z2(:,1))];
aym = [mean(X1(:,2)) mean(X2(:,2)) mean(Y1(:,2)) mean(Y2(:,2)) mean(Z1(:,2)) mean(Z2(:,2))];
azm = [mean(X1(:,3)) mean(X2(:,3)) mean(Y1(:,3)) mean(Y2(:,3)) mean(Z1(:,3)) mean(Z2(:,3))];

am=[axm',aym',azm']; %axm, aym, azm分别是采集的三轴加速度计数据，最好是6个面进行采集
G=[1 1 1 1 1 1]';
f=@(a,am)(a(1)*am(:,1)+a(2)).^2+(a(3)*am(:,2)+a(4)).^2+(a(5)*am(:,3)+a(6)).^2;
a0=[1 0 1 0 1 0];
a=lsqcurvefit(f,a0,am,G);
k = [a(1) a(3) a(5)]
b = [a(2) a(4) a(6)]
