function cdf_vectors = CDF_Vectors(log_file,n)

x_intervals=70;
statistics(log_file,n);
sample_name='http';
file_name = strcat('D:\PHD-thesis\MyPapers\PICN\Implementation\Matlab\log\',sample_name,'.txt');
fileID = fopen(file_name);
lineText =  fgetl(fileID);
n = 1;
max = 0;
sum = 0;
while ischar(lineText)
    line = sscanf(lineText,'%d');
    y(n) = line(1)/1000;
    sum = sum + y(n);
    if (y(n)>max)
        max = y(n);
    end
    lineText=  fgetl(fileID);
    n = n + 1;
end

disp(strcat('Average B/s for Http: ',num2str(sum/n)));
disp(strcat('Maximum B/s for Http: ',num2str(max)));

cdf_http = zeros(x_intervals,2);
x =[0:max/x_intervals:max];
cdf_vector = cdfCalculator(y,x);
cdf_http(1:x_intervals+1,1) = x(1:x_intervals+1); 
cdf_http(2:size(cdf_vector)+1,2) = cdf_vector;
cdf_http(1,2) = 0;
fclose(fileID);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
sample_name='picn';
file_name = strcat('D:\PHD-thesis\MyPapers\PICN\Implementation\Matlab\log\',sample_name,'.txt');
fileID = fopen(file_name);
lineText =  fgetl(fileID);
n = 1;
max = 0;
sum =0;
while ischar(lineText)
    line = sscanf(lineText,'%d %d');
    y(n) = line(1)/1000;
    sum = sum + y(n);
    if (y(n)>max)
        max = y(n);
    end
    lineText=  fgetl(fileID);
    n = n + 1;
end
disp(strcat('Average B/s for PICN: ',num2str(sum/n)));
disp(strcat('Maximum B/s for PICN: ',num2str(max)));
cdf_picn = zeros(x_intervals,2);
x =[0:max/x_intervals:max];
cdf_vector = cdfCalculator(y,x);
cdf_picn(1:x_intervals+1,1) = x(1:x_intervals+1); 
cdf_picn(2:size(cdf_vector)+1,2) = cdf_vector;
cdf_picn(1,2) = 0;
fclose(fileID);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
sample_name='lpicn';
file_name = strcat('D:\PHD-thesis\MyPapers\PICN\Implementation\Matlab\log\',sample_name,'.txt');
fileID = fopen(file_name);
lineText =  fgetl(fileID);
n = 1;
max = 0;
sum =0;
while ischar(lineText)
    line = sscanf(lineText,'%d');
    y(n) = line(1)/1000;
    sum = sum + y(n);
    if (y(n)>max)
        max = y(n);
    end
    lineText=  fgetl(fileID);
    n = n + 1;
end
disp(strcat('Average B/s for LPICN: ',num2str(sum/n)));
disp(strcat('Maximum B/s for LPICN: ',num2str(max)));
cdf_lpicn = zeros(x_intervals,2);
x =[0:max/x_intervals:max];
cdf_vector = cdfCalculator(y,x);
cdf_lpicn(1:x_intervals+1,1) = x(1:x_intervals+1); 
cdf_lpicn(2:size(cdf_vector)+1,2) = cdf_vector;
cdf_lpicn(1,2) = 0;
fclose(fileID);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%set(gca, 'YTick', [0:0.2:1]);
plot(cdf_http(:,1),cdf_http(:,2),'color','r');
%set(gca, 'XTick', [0:1:17]);
%set(gca, 'YTick', [0:0.2:1]);
hold on
plot(cdf_picn(:,1),cdf_picn(:,2),'color','g');
hold on
plot(cdf_lpicn(:,1),cdf_lpicn(:,2),'color','b');
legend('main web server','PICN', 'local');
hold off
