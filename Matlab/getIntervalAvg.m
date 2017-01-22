function avg_vector = getIntervalAvg(maxX,x_vector,y_vector,vector_len,intervalNum)

interval=zeros(intervalNum);
maxX=75000000;
for i=1:intervalNum
    %interval(i)=12*i;
    interval(i)=maxX/intervalNum*i;
    %disp(num2str(interval(i)));
end


sum=zeros(intervalNum);
num=zeros(intervalNum);
for i=1:vector_len
    for j=1:intervalNum
        if(x_vector(i)<=interval(j))
            
            sum(j) = sum(j)+y_vector(i);
            num(j) = num(j)+1;
            break;
        end
    end
end

for i=1:intervalNum
    %disp(strcat('number of requests in interval',num2str(i),': ',num2str(num(i))));
    if(num(i)>0)
        avg_vector(i)=sum(i)/num(i);
    else
        avg_vector(i)=0;
    end
        
end