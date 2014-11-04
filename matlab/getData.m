% function getData(board)
% % Acquisition
% data_in = fread(board);
% d=data_in(1)
% fread(board);
% figure(1); 
% stripchart(d);
% a='allo';
% end


function getData(board)
data = fread(board,32);
[b,a] = butter(3,0.00167, 'high');

%datefiltre = filter(b,a,data);
% read 10 bytes
%
% clear the buffer
% update the stripchart
figure(1); 
stripchart(data(1:end));
