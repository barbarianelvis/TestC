function [bufferedPktArrivalTime, bufferedPktSize, timeLeaveState, pktArrivalTime_copy, pktSize_copy] = ULShapingT(shapingTimer, pktArrivalTime_copy, pktSize_copy, timeEnterState)

    % shapingTimer = 1 (ms) means "no shaping"
    bufferedPktArrivalTime = [];
    bufferedPktSize = [];

%     timeLeaveState = max(timeEnterState + shapingTimer*max(ceil((pktArrivalTime_copy(1)-timeEnterState)/shapingTimer),1), pktArrivalTime_copy(1)+1);    %!! "pktArrivalTime_copy(1)+1" is used for the case of shapingTimer = 1
    timeLeaveState = timeEnterState + shapingTimer*(floor((pktArrivalTime_copy(1)-timeEnterState)/shapingTimer)+1);    % [20130204]
    
    while ~isempty(pktArrivalTime_copy) & pktArrivalTime_copy(1) < timeLeaveState
        bufferedPktArrivalTime = [bufferedPktArrivalTime pktArrivalTime_copy(1)];
        bufferedPktSize = [bufferedPktSize pktSize_copy(1)];
        pktArrivalTime_copy(1) = [];
        pktSize_copy(1) = [];
    end

end