function [ ] = plot3DFrames(base_frame, rotated_frame, axis_handle)
%UNTITLED8 Summary of this function goes here
%   Detailed explanation goes here
origin = [0 0 0];
axes(axis_handle);
hold off
quiver3(origin,origin,origin,base_frame(1,:),base_frame(2,:),base_frame(3,:));
hold on
az = 115;
el = 22;
view(az, el);
axis_handle.XLim=[-1 1];
axis_handle.YLim=[-1 1];
axis_handle.ZLim=[-1 1];
quiver3(origin,origin,origin,rotated_frame(1,:),rotated_frame(2,:),rotated_frame(3,:));
axis on
hold off
end

