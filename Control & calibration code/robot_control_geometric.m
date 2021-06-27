close all
clear
clc


%% calculate angles 
axis equal

a0 = 0.017;
d0 = 0.085;
length = 0.1;
x = 0.15 + a0;
y = 0.0;
z = 0.15 - d0;

d1 = 0.115;
d2 = 0.115;

base = atan(y/(x-a0));
r = sqrt((x-a0+a0*cos(base))^2 + (y+a0*sin(base))^2 + z^2);
elbow = acos(((r^2)-(d1^2)-(d2^2))/(2*d1*d2));
shoulder = asin(z/r) + atan((d2*sin(elbow))/(d1+d2*cos(elbow)));


%% plot arms
L1 = d1*cos(shoulder);
L2 = d2*cos(shoulder-elbow);

p0 = [0,0,0];
p1 = [-a0*cos(base), -a0*sin(base), d0];
p2 = p1 + [L1*cos(base), L1*sin(base), d1*sin(shoulder)];
p3 = round(p2 + [L2*cos(base), L2*sin(base), d2*sin(shoulder-elbow)], 4);

plot3([0,x-a0], [0, y], [0, z+d0], 'k-o'); hold on % The original targets
plot3([0,p1(1)], [0,p1(2)], [0,p1(3)], 'b-o'); 
plot3([p1(1),p2(1)], [p1(2),p2(2)], [p1(3),p2(3)], 'm-o'); 
plot3([p2(1),p3(1)], [p2(2),p3(2)], [p2(3),p3(3)], 'r-o'); 

plot_limit = 0.2;
xlim([-plot_limit,plot_limit])
ylim([-plot_limit,plot_limit])
zlim([-plot_limit,plot_limit])


