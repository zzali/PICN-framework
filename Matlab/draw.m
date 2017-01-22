file_name = 'E:\Zeinab\PHD-thesis\MyPapers\ICNX\Implementation\Matlab\log\log.txt';
fileID = fopen(file_name);
lineText=  fgetl(fileID);
picn=1;
lpicn=1;
http=1;
notsupported=1;
type = zeros(4,1000);
hash = zeros(4,1000);
size = zeros(4,1000);
time = zeros(4,1000);
dspeed = zeros(4,1000);
while ischar(lineText)
    if (length(findstr('.non',lineText))>0)
        n = sscanf(lineText,'%s %d %d');
        size(1,notsupported) = n(2);
        time(1,notsupported) = n(3);
        notsupported = notsupported+1;
    elseif (length(findstr('LPICN',lineText))>0)
            n = sscanf(lineText,'LPICN %s %d %d %d');
            type(2,lpicn) = n(1);
            hash(2,lpicn) = n(2);
            size(2,lpicn) = n(3);
            time(2,lpicn) = n(4);
            dspeed(2,lpicn) = n(3)/n(4);
            lpicn = lpicn+1;
    elseif (length(findstr('PICN',lineText))>0)
            n = sscanf(lineText,'PICN %s %d %d %d');
            type(3,picn) = n(1);
            hash(3,picn) = n(2);
            size(3,picn) = n(3);
            time(3,picn) = n(4);
            dspeed(3,picn) = n(3)/n(4);
            picn = picn+1;
    elseif (length(findstr('HTTP',lineText))>0)
            n = sscanf(lineText,'HTTP %s %d %d %d');
            type(4,http) = n(1);
            hash(4,http) = n(2);
            size(4,http) = n(3);
            time(4,http) = n(4);
            dspeed(4,http) = n(3)/n(4);
            http = http+1;
    end;
    lineText = fgetl(fileID);
end;
total = picn + lpicn + http + notsupported; 
httpPercent = http/total*100;
picnPercent = picn/total*100;
lpicnPercent = lpicn/total*100;
notsupportedPercent = notsupported/total*100;

httpRT = 0;
% figure('name','Average Ritrived Time');
% plot(b(:,1),b(:,2),'color','g');
% hold on;
% plot(b_noController(:,1),b_noController(:,2),'color','r');
% hold off;