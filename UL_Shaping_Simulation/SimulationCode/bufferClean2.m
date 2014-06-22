function [pktDepartureTime_tmp] = bufferClean2(bufferedPktSize, serviceRate, timeCurrent)
%   Detailed explanation goes here
% (T) improve efficiency 

    pktDepartureTime_tmp = [];

    a = find(bufferedPktSize>=serviceRate);
 
    if ~isempty(a) & a(1) == 1
        pktDepartureTime_tmp(1,1) = timeCurrent;
    else
        if ~isempty(a)
            bufferedPktSize2 = bufferedPktSize(1:a(1)-1);
        else
            bufferedPktSize2 = bufferedPktSize;
        end
        
        L = length(bufferedPktSize2);
        bufferedPktSize_cum = bufferedPktSize2*triu(ones(L,L));
        bufferedPktSize_cum = mod(bufferedPktSize_cum, serviceRate);
        bufferedPktSize_cum(find(bufferedPktSize_cum==0)) = serviceRate;

        A = diag(-1*ones(1,L));    A(L,L) = 1;   A([find(A==-1)+1]) = 1;                % matrix A: 
        bufferedPktSize_cum = bufferedPktSize_cum*A + [zeros(1,L-1) -serviceRate];      % handle the last element of bufferedPktSize_cum

        b = find(bufferedPktSize_cum<=0);       % b(1): 
        pktDepartureTime_tmp(1:b(1)) = timeCurrent;  %!!
    end
    
end
