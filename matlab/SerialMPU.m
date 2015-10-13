classdef SerialMPU < handle
    %UNTITLED9 Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        serial_file
    end
    
    methods
        function obj =SerialMPU()
            obj.serial_file = serial('COM4');
            fopen(obj.serial_file);
            obj.getString();
        end
        function close(obj)
            fclose(obj.serial_file);
        end
        function [readStr] = getString(obj) 
            readStr =fgetl(obj.serial_file);
        end
    end
end

