function cdf = cdfCalculator(vector,x)
%x=[1:0.1:5];

y=zeros(size(x,2)-1,1);

for i=1:size(x,2)-1
   
 
    y(i)=size(find(vector>=x(i) & vector<x(i+1)),2);
    
    
end



cdf = cumsum(y)/sum(y);



end