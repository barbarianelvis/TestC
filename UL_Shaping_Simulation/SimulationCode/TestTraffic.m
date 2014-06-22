clear all;
periodApp = [2 3 5 6 8];
T1 = 5;
T2 = 5;
timeObservation = 10^4;

% Initialize time array.
timeBGTraffic = 1;
numPktArrival = 0;
pktArrivalTime = [];

% Retrieve orginal packet arrival time.
while timeBGTraffic < timeObservation
    for p = 1:1:numel(periodApp)
        if mod(timeBGTraffic,periodApp(p)) == 0
            pktArrivalTime = [pktArrivalTime timeBGTraffic];
        end
    end
    timeBGTraffic = timeBGTraffic + 1;
end

% T1 & T2 shaping timer.
shapingTimerInterval = T1 + T2;
pktArrivalTime_shaped = pktArrivalTime;
for trafficTimeIndicator = 1:1:length(pktArrivalTime_shaped)
    timeModShapingInterval = mod(pktArrivalTime_shaped(trafficTimeIndicator) ,shapingTimerInterval);
    if timeModShapingInterval > T1 
        shiftTime = T2 - (timeModShapingInterval - T1) + 1;
        pktArrivalTime_shaped(trafficTimeIndicator) = pktArrivalTime_shaped(trafficTimeIndicator) + shiftTime;
    elseif timeModShapingInterval == 0
        pktArrivalTime_shaped(trafficTimeIndicator) = pktArrivalTime_shaped(trafficTimeIndicator) + 1;
    end
end

DSim = sum(pktArrivalTime_shaped - pktArrivalTime) / length(pktArrivalTime);
