classdef MockMPU < handle
    %UNTITLED9 Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        lastAngle;
    end
    
    methods
        function obj = MockMPU()
            obj.lastAngle = 0;
        end
        function close(obj)
        end
        function [readStr] = getString(obj) 
            readStr = sprintf('Tx=%4.1f,Ty=%4.1f,Tz=%4.1f',0,0,obj.lastAngle);
            obj.lastAngle = obj.lastAngle + 10;
        end
    end
end

