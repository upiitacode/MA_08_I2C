function [ rotatedFrame, originalFrame ,angles ] = getReferenceFrame( imuStruct )
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here
originalFrame = eye(3);

accelVector = [imuStruct.ax imuStruct.ay imuStruct.az];
normAccelVector = accelVector/sqrt(sum(accelVector.^2));

nacc_x = normAccelVector(1);
nacc_y = normAccelVector(2);

theta_y = real(asin(nacc_x));
theta_x = real(asin(-nacc_y/cos(theta_y)));

angles = [theta_x theta_y 0];

rotation_x = [1,0,0;
    0,cos(theta_x),-sin(theta_x)
    0,sin(theta_x),cos(theta_x)];
rotation_y = [cos(theta_y),0,sin(theta_y);
    0,1,0;
    -sin(theta_y),0,cos(theta_y)];

rotatedFrame = rotation_y*rotation_x*originalFrame;

end

