function [ rotatedFrame, originalFrame ,angles ] = getReferenceFrame( imuStruct )
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here
originalFrame = eye(3);

accelVector = [imuStruct.ax imuStruct.ay imuStruct.az];
normAccelVector = accelVector/sqrt(sum(accelVector.^2));

nacc_x = normAccelVector(1);
nacc_y = normAccelVector(2);
nacc_z = normAccelVector(3);

theta_x = -real(atan(-nacc_y/nacc_z));
theta_y = -real(asin(nacc_x));

if(isnan(theta_x))
    theta_x = 0;
end

if (nacc_x >= 0 && nacc_y >= 0 && nacc_z >=0 )
elseif (nacc_x >= 0 && nacc_y >= 0 && nacc_z < 0 )
    theta_x = pi + theta_x;
    theta_y = -theta_y;
elseif (nacc_x >= 0 && nacc_y < 0 && nacc_z >=0 )
elseif (nacc_x >= 0 && nacc_y < 0 && nacc_z < 0 )
    theta_x = -pi + theta_x ;
elseif (nacc_x < 0 && nacc_y >= 0 && nacc_z >=0 )
    theta_y = theta_y;
elseif (nacc_x < 0 && nacc_y >= 0 && nacc_z < 0 )
    theta_y = -theta_y;
    theta_x = pi + theta_x;
elseif (nacc_x < 0 && nacc_y < 0 && nacc_z >=0 )
    theta_y = theta_y;
    theta_x = theta_x;
elseif (nacc_x < 0 && nacc_y < 0 && nacc_z < 0 )    
    theta_x = -pi + theta_x ;
end
% elseif(nacc_x < 0 && nacc_y > 0)
%    
% elseif(nacc_x < 0 && nacc_z < 0)
%     theta_y = pi - theta_y;
% elseif (nacc_x > 0 && nacc_z < 0)
%      theta_y = -pi - theta_y ;
% end
angles = [theta_x theta_y 0];

rotation_x = [1,0,0;
    0,cos(theta_x),-sin(theta_x)
    0,sin(theta_x),cos(theta_x)];
rotation_y = [cos(theta_y),0,sin(theta_y);
    0,1,0;
    -sin(theta_y),0,cos(theta_y)];

rotatedFrame = rotation_y*rotation_x*originalFrame;

end

function [sx, sy] = saturate_norm(x,y)
xy = [x  y];
vector_size = sqrt(sum(xy.^2));
if(vector_size > 1)
    sxy = xy/vector_size; 
else
    sxy =xy;
end
sx = sxy(1);
sy = sxy(2);
end