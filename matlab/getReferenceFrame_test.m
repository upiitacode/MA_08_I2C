% Test input parser

% Preconditions

%% Test 1: When no Rotation 
imuStruct = struct('ax',0,'ay',0,'az',9.8);
assert(isequal(getReferenceFrame(imuStruct),eye(3)));
%% Test 2: When rotated 90 degrees in theta_y
imuStruct = struct('ax',9.8,'ay',0,'az',0);
[rotatedFrame, originalFrame, angles] = getReferenceFrame(imuStruct);
assert((sum(sum(((angles - [0 (-1/2)*pi 0]).^2))) < 0.001));
%% Test 3: When rotated -90 degrees in theta_x
imuStruct = struct('ax',0,'ay',-9.8,'az',0);
[rotatedFrame, originalFrame, angles] = getReferenceFrame(imuStruct);
assert(isequal(angles,[-pi/2 0 0]));
%% Test 4: When rotated -90 degrees in theta_x and 45 degrees in theta_x
imuStruct = struct('ax',-9.8,'ay',-9.8,'az',0);
[rotatedFrame, originalFrame, angles] = getReferenceFrame(imuStruct);
assert((sum(sum(((angles - [-pi/2 pi/4 0]).^2))) < 0.001));
%% Test 5: When rotated 90 degrees in theta_x and 45 degrees in theta_x
imuStruct = struct('ax',0,'ay',9.8,'az',0);
[rotatedFrame, originalFrame, angles] = getReferenceFrame(imuStruct);
assert(isequal(angles,[pi/2 0 0]));
%% Test 5: When rotated 90 degrees in theta_x and 45 degrees in theta_x
imuStruct = struct('ax',-0.7071,'ay',0,'az',-0.7071);
[rotatedFrame, originalFrame, angles] = getReferenceFrame(imuStruct);
assert((sum(sum(((angles - [3.1416 (-1/4)*pi 0]).^2))) < 0.001));
