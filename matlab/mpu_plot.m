function varargout = mpu_plot(varargin)
% MPU_PLOT MATLAB code for mpu_plot.fig
%      MPU_PLOT, by itself, creates a new MPU_PLOT or raises the existing
%      singleton*.
%
%      H = MPU_PLOT returns the handle to a new MPU_PLOT or the handle to
%      the existing singleton*.
%
%      MPU_PLOT('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in MPU_PLOT.M with the given input arguments.
%
%      MPU_PLOT('Property','Value',...) creates a new MPU_PLOT or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before mpu_plot_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to mpu_plot_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help mpu_plot

% Last Modified by GUIDE v2.5 13-Oct-2015 05:08:45

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @mpu_plot_OpeningFcn, ...
                   'gui_OutputFcn',  @mpu_plot_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before mpu_plot is made visible.
function mpu_plot_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to mpu_plot (see VARARGIN)

% Choose default command line output for mpu_plot
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes mpu_plot wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = mpu_plot_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in start_stop_button.
function start_stop_button_Callback(hObject, eventdata, handles)
% hObject    handle to start_stop_button (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of start_stop_button
hObject.String = 'Stop';
if  hObject.Value
    mpu = SerialMPU;
    while hObject.Value
        dataString = mpu.getString();
        tokens = tokenizeLine(dataString);
        mpuData = parseToken(tokens);
        theta = [mpuData.Tx mpuData.Ty mpuData.Tz];
        [rotatedFrame, baseFrame] = getRotatedFrame(theta);
        plot3DFrames(baseFrame,rotatedFrame,handles.main_axes);
        handles.box_ax.String = num2str(theta(1));
        handles.box_ay.String = num2str(theta(2));
        handles.box_az.String = num2str(theta(3));
        pause(0.01)
    end
    mpu.close()
end
hObject.String = 'Start';



function box_ax_Callback(hObject, eventdata, handles)
% hObject    handle to box_ax (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of box_ax as text
%        str2double(get(hObject,'String')) returns contents of box_ax as a double


% --- Executes during object creation, after setting all properties.
function box_ax_CreateFcn(hObject, eventdata, handles)
% hObject    handle to box_ax (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function box_ay_Callback(hObject, eventdata, handles)
% hObject    handle to box_ay (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of box_ay as text
%        str2double(get(hObject,'String')) returns contents of box_ay as a double


% --- Executes during object creation, after setting all properties.
function box_ay_CreateFcn(hObject, eventdata, handles)
% hObject    handle to box_ay (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function box_az_Callback(hObject, eventdata, handles)
% hObject    handle to box_az (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of box_az as text
%        str2double(get(hObject,'String')) returns contents of box_az as a double


% --- Executes during object creation, after setting all properties.
function box_az_CreateFcn(hObject, eventdata, handles)
% hObject    handle to box_az (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
