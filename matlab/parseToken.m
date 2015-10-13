function [ parsedStruct ] = parseToken( tokens )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here 
    parsedStruct = struct();
    for token = tokens
        parsedStruct.(token{1}{1}) = str2double(token{1}{2});
    end
end

