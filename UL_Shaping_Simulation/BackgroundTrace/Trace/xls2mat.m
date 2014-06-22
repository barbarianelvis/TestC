temp = xlsread('Background_Mix4.xlsx', 'Total_CDF');
Background_Mix4_Size = temp(:,3);
Background_Mix4_IAT = temp(1:length(temp)-1,5);

% temp = xlsread('Background_Mix4.xlsx', 'Uplink_CDF');
% Background_Mix4_UL_Size = temp(:,3);
% Background_Mix4_UL_IAT = temp(1:length(temp)-1,5);

temp = xlsread('Background_Mix4.xlsx', 'Downlink_CDF');
Background_Mix4_DL_Size = temp(:,3);
Background_Mix4_DL_IAT = temp(1:length(temp)-1,5);
