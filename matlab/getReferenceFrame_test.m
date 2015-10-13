% Test input parser

% Preconditions

%% Test 1: When no Rotation 
imuStruct = struct('ax',0,'ay',0,'az',9.8);
assert(isequal(getReferenceFrame(imuStruct),eye(3)));
%% Test 2: When rotated 90 degrees in theta_y
imuStruct = struct('ax',9.8,'ay',0,'az',0);
[rotatedFrame, originalFrame, angles] = getReferenceFrame(imuStruct);
assert(isequal(angles,[0 pi/2 0]));
expectedRotatedFrame  = [0.0 0 1.0;
                         0 1.0 0;
                         -1.0 0 0.0];   
assert((sum(sum((expectedRotatedFrame - rotatedFrame).^2)) < 0.001));                     
%% Test 3: When rotated -90 degrees in theta_x
imuStruct = struct('ax',0,'ay',9.8,'az',0);
[rotatedFrame, originalFrame, angles] = getReferenceFrame(imuStruct);
expectedRotatedFrame  = [1 0 0;
                         0 0 1;
                         0 -1 0];
assert(isequal(angles,[-pi/2 0 0]));
assert((sum(sum((expectedRotatedFrame - rotatedFrame).^2)) < 0.001));
%% Test 3: When rotated -90 degrees in theta_x and 45 degrees in theta_x
imuStruct = struct('ax',9.8,'ay',9.8,'az',0);
[rotatedFrame, originalFrame, angles] = getReferenceFrame(imuStruct);
expectedRotatedFrame  = [sqrt(1/2) -sqrt(1/2) 0;
                         0 0 1;
                         -sqrt(1/2) -sqrt(1/2) 0];
assert((sum(sum(((angles - [-pi/2 pi/4 0]).^2))) < 0.001));
assert((sum(sum((expectedRotatedFrame - rotatedFrame).^2)) < 0.001));    