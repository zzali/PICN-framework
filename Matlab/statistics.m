function Stat = statistics(file,n)
picn=1;
lpicn=1;
http=1;
notsupported=1;
type = cell(4,100000);  
hash = zeros(4,100000);
size = zeros(4,100000);
time = zeros(4,100000);
dspeed = zeros(4,100000);
maxSize=0;
minSize=0;
    
for i=1:n
    file_name = strcat('D:\PHD-thesis\MyPapers\PICN\Implementation\Matlab\log\',file{i});
    fileID = fopen(file_name);
    lineText=  fgetl(fileID);
    
    while ischar(lineText)
        if (length(findstr('.non',lineText))>0)
            out = regexp(lineText, '  +', 'split');
            size(1,notsupported) = str2double(out(3));
            time(1,notsupported) = str2double(out(4));
            dspeed(1,notsupported) = size(1,notsupported)/time(1,notsupported);
            if(maxSize<size(1,notsupported))
                maxSize = size(1,notsupported);
            end
            notsupported = notsupported+1;
        elseif (length(findstr('LPICN',lineText))>0)
            out = regexp(lineText, '  +', 'split');
            type(2,lpicn) = out(2);
            hash(2,lpicn) = str2double(out(3));
            size(2,lpicn) = str2double(out(4));
            time(2,lpicn) = str2double(out(5));
            dspeed(2,lpicn) = size(2,lpicn)/time(2,lpicn);
            if(maxSize<size(2,lpicn))
                maxSize = size(2,lpicn);
            end
            lpicn = lpicn+1;
        elseif (length(findstr('PICN',lineText))>0)
            out = regexp(lineText, '  +', 'split');
            type(3,picn) = out(2);
            hash(3,picn) = str2double(out(3));
            size(3,picn) = str2double(out(4));
            time(3,picn) = str2double(out(5));
            dspeed(3,picn) = size(3,picn)/time(3,picn);
            if(maxSize<size(3,picn))
                maxSize = size(3,picn);
            end
            picn = picn+1;
        elseif (length(findstr('HTTP',lineText))>0)
            out = regexp(lineText, '  +', 'split');
            type(4,http) = out(2);
            hash(4,http) = str2double(out(3));
            size(4,http) = str2double(out(4));
            time(4,http) = str2double(out(5));
            dspeed(4,http) = size(4,http)/time(4,http);
            if(maxSize<size(4,http))
                maxSize = size(4,http);
            end
            http = http+1;
        end;
        lineText = fgetl(fileID);
    end;
    fclose(fileID);
end
total = picn + lpicn + http + notsupported; 
httpPercent = http/total*100;
picnPercent = picn/total*100;
lpicnPercent = lpicn/total*100;
notsupportedPercent = notsupported/total*100;
disp(strcat('Total number of requests: ',num2str(total)));
disp(strcat('main server percent: ',num2str(httpPercent)));
disp(strcat('peer percent: ',num2str(picnPercent)));
disp(strcat('local percent: ',num2str(lpicnPercent)));
disp(strcat('not supported http percent: ',num2str(notsupportedPercent)));

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
disp(strcat('max size: ',num2str(maxSize)));
avg=zeros(4,5);
len=[notsupported-1,lpicn-1,picn-1,http-1];
for i=2:4
    avg(i,:)=getIntervalAvg(maxSize,size(i,:),dspeed(i,:),len(i),5);
    disp(strcat('average speed ',num2str(i),': ',num2str(avg(i,1)),', ',num2str(avg(i,2)),', ',num2str(avg(i,3)),', ',num2str(avg(i,4)),', ',num2str(avg(i,5))));%,',',num2str(avg(i,5))));
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

file_name = strcat('D:\PHD-thesis\MyPapers\PICN\Implementation\Matlab\log\lpicn.txt');
dlmwrite(file_name,dspeed(2,1:lpicn),'\n');

file_name = strcat('D:\PHD-thesis\MyPapers\PICN\Implementation\Matlab\log\picn.txt');
dlmwrite(file_name,dspeed(3,1:picn),'\n');

file_name = strcat('D:\PHD-thesis\MyPapers\PICN\Implementation\Matlab\log\http.txt');
dlmwrite(file_name,dspeed(4,1:http),'\n');

