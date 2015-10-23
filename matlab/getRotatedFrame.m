function [ rotatedFrame, originalFrame] = getRotatedFrame( theta )
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here
originalFrame = eye(3);
theta_rad = theta * (pi/180);

theta_x = theta_rad(1);
theta_y = theta_rad(2);
theta_z = theta_rad(3);


rotation_x = [1,0,0;
    0,cos(theta_x),-sin(theta_x)
    0,sin(theta_x),cos(theta_x)];
rotation_y = [cos(theta_y),0,sin(theta_y);
    0,1,0;
    -sin(theta_y),0,cos(theta_y)];
rotation_z = [ cos(theta_z), -sin(theta_z), 0;
    sin(theta_z), cos(theta_z), 0;
    0, 0, 1];

rotatedFrame = rotation_z*rotation_y*rotation_x*originalFrame;
end