function [ tokens ] = tokenizeLine( line )
%UNTITLED Summary of this function goes here
%   Detailed explanat
tokens = regexp(line,'(\w+)\s*=\s*(+?-?\d+\.?\d*)','tokens');
end
