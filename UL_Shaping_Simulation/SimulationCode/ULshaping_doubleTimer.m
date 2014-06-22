%% ver. 20130328
% function: RRC state transition + RRC_connected DRX (Long cycle only) + UL shaping in RRC_idle state (three shaping schemes: T/D/K)
% consider uplink traffic only
clear all;
clc;

%% Time observation
timeObservation = 10^7;         % (ms)
numSim = 1;
%% Traffic model (Background application update)
%Periods of the updating applications in ms.
periodApp = [1000 30000 60000 120000 300000]; % (ms)

% Traffic model (Poisson process)
serviceRate = 1;                % (ms/packet) for the assumption in the paper of pimrc 2013 % (bytes/ms) if serviceRate = 1 pkt/me, just set serviceRate = 1 (although it actually means that serviceRate = 1 bytes/ms. In fact, any serviceRate < packet size works. It just has to make sure that this serviceRate is smaller than all packet size)
Lambda = 10^-2;                 % (packets/ms)

%% RRC connection control
% rrcReleaseTimer [0 100 500 1000 2500 5000 10000 15000 30000 60000] (ms) 
% 0s, 0.1s, 0.5s, 1s, 2.5s, 5s, 10s, 15s, 30s, 60s
rrcReleaseTimer = 5000;
figureTitle = 'Release timer: 5000 ms';
delayIdleToConn = 50;           % (ms)

%% DRX configuration
inactivityTimer = 4;
onDuration = 2;
% drxCycle = [10 20 128 256];
drxCycle = 40;

%% Shaping parameter setup
% On/off shaping mechanism timer in ms time scale.
T1 = linspace(500,5000,10);   %ms
T2 = linspace(500,5000,10);   %ms

shapingType = '';              % 'T': a timer, 'D': delay bound constraint, 'K': a fixed buffer size, 'N': no UL shaping [Disable this function in this version!!]
if strcmp(shapingType,'T')
    shapingIndex = [0.001 1/Lambda*(linspace(2,10,9)-1)];
elseif strcmp(shapingType,'D')
    shapingIndex = 1/Lambda*(linspace(1,10,10)-1);
elseif strcmp(shapingType,'K')
    shapingIndex = linspace(1,10,10);
else
    shapingIndex = 1;        % No UL shaping
end

%% Outputs format
activeDuration = zeros(length(T1),length(T2));       % active period in rrc connected state
sleepingDuration = zeros(length(T1),length(T2));     % sleeping period
rrcIdleDuration = zeros(length(T1),length(T2));      % rrc idle state

numActiveToSleeping = zeros(length(T1),length(T2));
numSleepingToActive = zeros(length(T1),length(T2));
numIdleToConn = zeros(length(T1),length(T2));
numConnToIdle = zeros(length(T1),length(T2));

powerOnRatioSim = zeros(length(T1),length(T2));      % powerOnRatio = activeDuration/(activeDuration + sleepingDuration + rrcIdleDuration);
numRRCcyclessSim = zeros(length(T1),length(T2));
DSim = zeros(length(T1),length(T2));                 % DSim = (pktDepartureTime - pktArrivalTime)/numTotalPkt;

%%  Traffic generator
% periodLCM = 1;
% for appPeriodOrder = 1:1:numel(periodApp);
%     periodLCM = lcm(periodLCM, periodApp(appPeriodOrder));
% end

% Initialize time array.
timeBGTraffic = 1;
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
% 
% load C:\Users\Bike\Desktop\UL_shaping_simulation_20140607\UL_shaping_simulation_20140607\UL_BG_trace\UL_BG_Mix4_AT.txt
% pktArrivalTime = UL_BG_Mix4_AT;
% pktArrivalTime = pktArrivalTime';

pktSize = ones(1,length(pktArrivalTime));	% fixed packet size

%% Recursion of simulation 
for n = 1:1:numSim
    for row = 1:1:length(T2)
        for col = 1:1:length(T1)
            %% Traffic shaping (Background application update)
            % T1 & T2 shaping timer.
            shapingTimerInterval = T1(col) + T2(row);
            pktArrivalTime_shaped = pktArrivalTime;
            for trafficTimeIndicator = 1:1:length(pktArrivalTime_shaped)
                timeModShapingInterval = mod(pktArrivalTime_shaped(trafficTimeIndicator) ,shapingTimerInterval);
                if timeModShapingInterval > T1(col)
                    shiftTime = T2(row) - (timeModShapingInterval - T1(col)) + 1;
                    pktArrivalTime_shaped(trafficTimeIndicator) = pktArrivalTime_shaped(trafficTimeIndicator) + shiftTime;
                elseif timeModShapingInterval == 0
                    pktArrivalTime_shaped(trafficTimeIndicator) = pktArrivalTime_shaped(trafficTimeIndicator) + 1;
                end
            end
            rrcReleaseTimerPrime = rrcReleaseTimer - inactivityTimer;      % remaining length of rrcReleaseTimer after inactivityTimer expires
            
            %% Reset records for calculating outputs
            bufferedPktArrivalTime = [];        % [20130202]
            bufferedPktSize = [];               % [20130202]
            pktDepartureTime_tmp = [];
            pktDepartureTime = [];
            pktTag = [];                        % 13: pkt arrive in EFB, 14: pkt arrive in Tsetup+EFB, 2: pkt arrive in BP's, 3: pkt arrive in sleeping state, 4: pkt arrive in idle state
            pktArrivalTime_copy = pktArrivalTime_shaped;
            pktSize_copy = pktSize;
            
            timeLeaveState = 0;
            activeDuration_tmp = 0;
            sleepingDuration_tmp = 0;
            rrcIdleDuration_tmp = 0;
            numActiveToSleeping_tmp = 0;
            numSleepingToActive_tmp = 0;
            numIdleToConn_tmp = 0;
            numConnToIdle_tmp = 0;
            %% Reset UE inital state
            state = 'RRC_idle';                 % current/initial UE state
            preState = 'RRC_idle';              % previous UE state
            %% RRC module
            while length(pktDepartureTime) ~= length(pktArrivalTime_shaped)
                %  Three UE states are defined, i.e. Active state, Sleeping state, and RRC_idle state.
                %%  UE states is Active.
                while strcmp(state,'Active')
                    endOfEFB = 0;                           % 0: false, 1: true
                    timeEnterState = timeLeaveState;
                    timeCurrent = timeEnterState;
                    timeLeaveState = timeCurrent + 1;
                    
                    while ~isempty(pktArrivalTime_copy) && pktArrivalTime_copy(1) < timeLeaveState       % [20130204][20121128] before serving the buffered pkt arrived in sleeping/RRC_idle, buffer packet arrived in the period of 'timeEnterState'
                        bufferedPktArrivalTime = [bufferedPktArrivalTime pktArrivalTime_copy(1)];
                        bufferedPktSize = [bufferedPktSize pktSize_copy(1)];
                        if strcmp(preState,'Sleeping')      % [20130207]
                            pktTag = [pktTag 13];
                        else
                            pktTag = [pktTag 14];
                        end
                        pktArrivalTime_copy(1) = [];
                        pktSize_copy(1) = [];
                    end
                    
                    while ~isempty(bufferedPktSize) || (~isempty(pktArrivalTime_copy) && pktArrivalTime_copy(1) < timeLeaveState)     % pkt transmission (EFB + BP's)
                        [pktDepartureTime_tmp] = bufferClean2(bufferedPktSize, serviceRate, timeCurrent);       % "each time" bufferClean2 will clean a batch of data with size <= serviceRate. => Check details in bufferClean2!
                        
                        pktDepartureTime = [pktDepartureTime pktDepartureTime_tmp];
                        timeLeaveState = pktDepartureTime(end) + inactivityTimer + 1;       % [20130204][20130206]  +1?
                        bufferedPktArrivalTime(1:length(pktDepartureTime_tmp)) = [];        % delete the served pkt
                        bufferedPktSize(1:length(pktDepartureTime_tmp)) = [];
                        pktDepartureTime_tmp = [];
                        if ~isempty(bufferedPktSize)
                            timeCurrent = timeCurrent + 1;
                        elseif isempty(bufferedPktSize) && ~isempty(pktArrivalTime_copy) && pktArrivalTime_copy(1) < timeLeaveState  %!!
                            endOfEFB = 1;
                            timeCurrent = pktArrivalTime_copy(1) + 1;       %!!!! [20121128] if buffer is empty for now (inactivityTimer has not expired yet), timeCurrent can 'jump' to pktArrivalTime_copy(1)+1 (time to serve new arrivals which arrive at pktArrivalTime_copy(1)). NOTE: When buffer is empty, pktArrivalTime_copy(1) is no way < timeCurrent, or there would be a bug!
                        end
                        
                        while ~isempty(pktArrivalTime_copy) && pktArrivalTime_copy(1) < timeCurrent      % Handle 2 situations of new arrivals: (1) If buffer is not empty: pkt arrive at the timeCurrent should be appended after the buffered data (those arrive at timeCurrent can't be served at the same time)
                            bufferedPktArrivalTime = [bufferedPktArrivalTime pktArrivalTime_copy(1)];    % (2) If buffer is empty: buffer new arrivals which arrive at pktArrivalTime_copy(1)
                            bufferedPktSize = [bufferedPktSize pktSize_copy(1)];
                            pktArrivalTime_copy(1) = [];
                            pktSize_copy(1) = [];
                            
                            if endOfEFB == 0
                                if strcmp(preState,'Sleeping')      % [20130207]
                                    pktTag = [pktTag 13];
                                else
                                    pktTag = [pktTag 14];
                                end
                            else
                                pktTag = [pktTag 2];
                            end
                        end
                    end
                    
                    activeDuration_tmp = activeDuration_tmp + timeLeaveState - timeEnterState;
                    numActiveToSleeping_tmp = numActiveToSleeping_tmp + 1;
                    state = 'Sleeping';
                    preState = 'Active';
                end     %% end of active state (or T1 or active period in the paper)
                %%  UE state is Sleeping.
                while ~isempty(pktArrivalTime_copy) && strcmp(state,'Sleeping')
                    timeEnterState = timeLeaveState;
                    timeCurrent = timeEnterState;           % [20130331]
                    timeLeaveState = timeEnterState + 1;
                    numOnDuration = 0;
                    
                    % [20130309] must exclude OnDurations in the sleepingDuration
                    if (pktArrivalTime_copy(1)-timeEnterState) > rrcReleaseTimerPrime
                        timeLeaveState = timeEnterState + rrcReleaseTimerPrime;
                        numOnDuration = ceil(rrcReleaseTimerPrime/drxCycle);
                        activeDuration_tmp = activeDuration_tmp + numOnDuration*onDuration;
                        sleepingDuration_tmp = sleepingDuration_tmp + rrcReleaseTimerPrime - numOnDuration*onDuration;
                        numConnToIdle_tmp = numConnToIdle_tmp + 1;
                        state = 'RRC_idle';
                    elseif (pktArrivalTime_copy(1)-timeEnterState) == rrcReleaseTimerPrime      % [20130206]
                        timeCurrent = pktArrivalTime_copy(1);
                        timeLeaveState = timeCurrent + 1;
                        
                        % [bufferedPktArrivalTime, bufferedPktSize, timeLeaveState, pktArrivalTime_copy, pktSize_copy] = ULShapingT(1, pktArrivalTime_copy, pktSize_copy, timeEnterState);
                        % pktTag_tmp = 3*ones(1,length(bufferedPktSize));
                        % pktTag = [pktTag pktTag_tmp];
                        while ~isempty(pktArrivalTime_copy) && pktArrivalTime_copy(1) < timeLeaveState       % [20130204][20121128] before serving the buffered pkt arrived in sleeping/RRC_idle, buffer packet arrived in the period of 'timeEnterState'
                            bufferedPktArrivalTime = [bufferedPktArrivalTime pktArrivalTime_copy(1)];
                            bufferedPktSize = [bufferedPktSize pktSize_copy(1)];
                            pktTag = [pktTag 3];
                            
                            pktArrivalTime_copy(1) = [];
                            pktSize_copy(1) = [];
                        end
                        
                        numOnDuration = ceil(rrcReleaseTimerPrime/drxCycle);
                        activeDuration_tmp = activeDuration_tmp + numOnDuration*onDuration;
                        sleepingDuration_tmp = sleepingDuration_tmp + rrcReleaseTimerPrime - numOnDuration*onDuration;      % (T redundant?)
                        numSleepingToActive_tmp = numSleepingToActive_tmp + 1;
                        state = 'Active';
                    else    % [20130331]
                        %                         timeCurrent = pktArrivalTime_copy(1);
                        %                         timeLeaveState = timeCurrent + 1;
                        
                        [bufferedPktArrivalTime, bufferedPktSize, timeLeaveState, pktArrivalTime_copy, pktSize_copy] = ULShapingT(1, pktArrivalTime_copy, pktSize_copy, timeEnterState);
                        pktTag_tmp = 3*ones(1,length(bufferedPktSize));
                        pktTag = [pktTag pktTag_tmp];
                        
                        numOnDuration = ceil((timeLeaveState - timeEnterState)/drxCycle);
                        activeDuration_tmp = activeDuration_tmp + numOnDuration*onDuration;
                        sleepingDuration_tmp = sleepingDuration_tmp + (timeLeaveState - timeEnterState) - numOnDuration*onDuration;
                        numSleepingToActive_tmp = numSleepingToActive_tmp + 1;
                        state = 'Active';
                    end
                    preState = 'Sleeping';
                end     %% end of sleeping state (or T2 or sleeping period in the paper)
                %%  UE state is RRC_idle.
                while ~isempty(pktArrivalTime_copy) && strcmp(state,'RRC_idle')
                    timeEnterState = timeLeaveState;
                    
                    % ======Tshaping======
                    if strcmp(shapingType, 'D')
                        [bufferedPktArrivalTime, bufferedPktSize, timeLeaveState, pktArrivalTime_copy, pktSize_copy] = ULShapingD(shapingIndex(col), pktArrivalTime_copy, pktSize_copy);
                    elseif strcmp(shapingType, 'T')
                        [bufferedPktArrivalTime, bufferedPktSize, timeLeaveState, pktArrivalTime_copy, pktSize_copy] = ULShapingT(shapingIndex(col), pktArrivalTime_copy, pktSize_copy, timeEnterState);
                    elseif strcmp(shapingType, 'K')
                        [bufferedPktArrivalTime, bufferedPktSize, timeLeaveState, pktArrivalTime_copy, pktSize_copy] = ULShapingK(shapingIndex(col), pktArrivalTime_copy, pktSize_copy);
                    else
                        [bufferedPktArrivalTime, bufferedPktSize, timeLeaveState, pktArrivalTime_copy, pktSize_copy] = ULShapingT(1, pktArrivalTime_copy, pktSize_copy, timeEnterState);
                    end
                    pktTag_tmp = 4*ones(1,length(bufferedPktSize));
                    pktTag = [pktTag pktTag_tmp];
                    rrcIdleDuration_tmp = rrcIdleDuration_tmp + timeLeaveState - timeEnterState;
                    
                    % ======Tsetup======
                    timeLeaveState = timeLeaveState + delayIdleToConn;      % +1?
                    while ~isempty(pktArrivalTime_copy) && pktArrivalTime_copy(1) < timeLeaveState       % [20130204][20121128] before serving the buffered pkt within S2/S3, buffer packet arrivals within the RRC connection setup period
                        bufferedPktArrivalTime = [bufferedPktArrivalTime pktArrivalTime_copy(1)];
                        bufferedPktSize = [bufferedPktSize pktSize_copy(1)];
                        pktTag = [pktTag 4];
                        pktArrivalTime_copy(1) = [];
                        pktSize_copy(1) = [];
                    end
                    activeDuration_tmp = activeDuration_tmp + delayIdleToConn;
                    
                    numIdleToConn_tmp = numIdleToConn_tmp + 1;
                    preState = 'RRC_idle';
                    state = 'Active';
                end     %% end of RRC_idle state (or T3)
            end    %% end of while totalServed <= totalArrival
            %% ======Performence metrics calculation======
            activeDuration(row,col) = activeDuration(row,col) + activeDuration_tmp;
            sleepingDuration(row,col) = sleepingDuration(row,col) + sleepingDuration_tmp;
            rrcIdleDuration(row,col) = rrcIdleDuration(row,col) + rrcIdleDuration_tmp;
            numActiveToSleeping(row,col) = numActiveToSleeping(row,col) + numActiveToSleeping_tmp;
            numSleepingToActive(row,col) = numSleepingToActive(row,col) + numSleepingToActive_tmp;
            numIdleToConn(row,col) = numIdleToConn(row,col) + numIdleToConn_tmp;
            numConnToIdle(row,col) = numConnToIdle(row,col) + numConnToIdle_tmp;
            
            powerOnRatioSim(row,col) = powerOnRatioSim(row,col) + activeDuration_tmp / (activeDuration_tmp + sleepingDuration_tmp + rrcIdleDuration_tmp);
            numRRCcyclessSim(row,col) = numRRCcyclessSim(row,col) + numConnToIdle_tmp / timeObservation;   % eqivalent to 'numIdleToConn_tmp / timeObservation'
            DSim(row,col) = DSim(row,col) + sum(pktDepartureTime - pktArrivalTime) / length(pktArrivalTime);
        end
    end
end

powerOnRatioSim = powerOnRatioSim/numSim;
numRRCcyclessSim = numRRCcyclessSim/numSim;
DSim = DSim/numSim;
% ======Simualtion ends======

%% Figures

figure;
surf( T1, T2, numRRCcyclessSim);
xlabel('Shaping timer T1 (ms)');
ylabel('Shaping timer T2 (ms)');
zlabel('Number of super cycle per unit time');
title(figureTitle);

figure;
surf(T1, T2, DSim);
xlabel('Shaping timer T1 (ms)');
ylabel('Shaping timer T2 (ms)');
zlabel('Average packet delay (ms)');
title(figureTitle);

figure;
surf(T1, T2, powerOnRatioSim);
xlabel('Shaping timer T1 (ms)');
ylabel('Shaping timer T2 (ms)');
zlabel('Power on ratio');
title(figureTitle);
