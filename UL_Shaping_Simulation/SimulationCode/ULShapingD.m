function [bufferedPktArrivalTime, bufferedPktSize, timeLeaveState, pktArrivalTime_copy, pktSize_copy] = ULShapingD(delayBound, pktArrivalTime_copy, pktSize_copy)

%   delayBound - delayIdleToConn = 1 means "no shaping"
%   Constraint: delayBound >= 1 (ms) & delayBound - delayIdleToConn >= 1 (ms)
%   NOTE: A common delay bound is assumed for all packet arrivals. If there are different delay bound requirements, code should be modified!

    bufferedPktArrivalTime = [];
    bufferedPktSize = [];

%     timeLeaveState = pktArrivalTime_copy(1) + max(delayBound-delayIdleToConn, 1);
    timeLeaveState = pktArrivalTime_copy(1) + max(delayBound, 1);       % [20130304] To prevent the wrong assignment of 'delayBound', that is, the delayBound is unreasonable to be less than 1.
    
    while ~isempty(pktArrivalTime_copy) & pktArrivalTime_copy(1) < timeLeaveState
        bufferedPktArrivalTime = [bufferedPktArrivalTime pktArrivalTime_copy(1)];
        bufferedPktSize = [bufferedPktSize pktSize_copy(1)];
        pktArrivalTime_copy(1) = [];
        pktSize_copy(1) = [];
    end

end

