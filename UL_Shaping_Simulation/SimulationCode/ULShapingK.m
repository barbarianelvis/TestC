function [bufferedPktArrivalTime, bufferedPktSize, timeLeaveState, pktArrivalTime_copy, pktSize_copy] = ULShapingK(bufferSize, pktArrivalTime_copy, pktSize_copy)

%   bufferSize = 1 means "no shaping"
    bufferedPktArrivalTime = [];
    bufferedPktSize = [];
    remainBufferSize = bufferSize;
   
    while ~isempty(pktSize_copy) & remainBufferSize > 0
        bufferedPktArrivalTime = [bufferedPktArrivalTime pktArrivalTime_copy(1)];
        bufferedPktSize = [bufferedPktSize pktSize_copy(1)];
        
        remainBufferSize = remainBufferSize - pktSize_copy(1);
        pktArrivalTime_copy(1) = [];
        pktSize_copy(1) = [];
    end
    
    timeLeaveState = bufferedPktArrivalTime(end) + 1;
%     
%     timeLeaveState = bufferedPktArrivalTime(end) + 1;
%     while ~isempty(pktSize_copy) & length(bufferedPktSize) < bufferSize   
%         bufferedPktArrivalTime = [bufferedPktArrivalTime pktArrivalTime_copy(1)];
%         bufferedPktSize = [bufferedPktSize pktSize_copy(1)];
%         pktArrivalTime_copy(1) = [];
%         pktSize_copy(1) = [];
% %         bufferLengthAccumulate = bufferLengthAccumulate + pktSize_copy(1);
%     end
%     
%     timeLeaveState = bufferedPktArrivalTime(end) + 1;
end

