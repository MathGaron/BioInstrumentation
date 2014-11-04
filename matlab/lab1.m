%% Create a serial object
board = serial('COM5', 'BaudRate', 115200, 'DataBits',8);
fopen(board);



% Initialize the stripchart
clf
Fs = 100;
AxesWidth = 1; % Axes Width (s)
figure(1); stripchart(Fs,AxesWidth);

%Setup a timer
% The timer has a callback that reads the serial port and updates the
% stripchart
t = timer('TimerFcn', @(x,y)getData(board), 'Period', 0.001);
set(t,'ExecutionMode','fixedRate');
start(t);



% disp('COM INIT');
% Port = 'COM5';
% baudrate = 115200;
% board = serial(Port,'BaudRate', baudrate,'DataBits',8);
% BUFFERIN=256;
% set(board,'InputBufferSize', BUFFERIN);
% fopen(board);
% 
% 
% disp('Graph INIT');
% Fs = 1000;
% %sampling frequency
% ScopeWidth = 2;
% %defines the stripchart's scope width
% Nb_curves = 2;
% %number of curves plotted in the stripchart
% figure(1)
% stripchart(Fs, ScopeWidth, Nb_curves)
% 
% 
% 
% 
% disp('TMIER CONFIG INIT');
% TMR_PERIOD = .003;%period in s
% t = timer('TimerFcn', @(x,y)getData(board),'Period', TMR_PERIOD);
% %t = timer('TimerFcn', @(x,y)disp('ALLO'),'Period', TMR_PERIOD);
% set(t,'ExecutionMode','fixedRate');







