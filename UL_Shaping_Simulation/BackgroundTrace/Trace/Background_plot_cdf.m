figure
hold on

p = cdfplot(Background_OS_DL_IAT);
set(p,'Color',[0 0.6 0.2],'LineWidth',2);

p = cdfplot(Background_NTP_DL_IAT);
set(p,'Color',[0.2 0.8 0.3],'LineWidth',2);

p = cdfplot(Background_GPS_DL_IAT);
set(p,'Color',[0.87 0.49 0],'LineWidth',2);

p = cdfplot(Background_Android_DL_IAT);
set(p,'Color',[0.7 0.8 0.4],'LineWidth',2);

p = cdfplot(Background_HTCWeather_DL_IAT);
set(p,'Color',[1 0.5 1],'LineWidth',2);

p = cdfplot(Background_HTCWeather2_DL_IAT);
set(p,'Color',[1 0.09 0.4],'LineWidth',2);

p = cdfplot(Background_Facebook_DL_IAT);
set(p,'Color',[0 0 1],'LineWidth',2);

p = cdfplot(Background_Facebook2_DL_IAT);
set(p,'Color',[0.2 0.3 0.4],'LineWidth',2);

p = cdfplot(Background_Facebook3_DL_IAT);
set(p,'Color',[0 0.7 0.7],'LineWidth',2);

p = cdfplot(Background_Mix_DL_IAT);
set(p,'Color',[0.6 0.2 0],'LineWidth',2);

p = cdfplot(Background_Mix2_DL_IAT);
set(p,'Color',[0.04 0.52 0.78],'LineWidth',2);

p = cdfplot(Background_Mix3_DL_IAT);
set(p,'Color',[0.12 0.39 0.91],'LineWidth',2);

p = cdfplot(Background_Mix4_DL_IAT);
set(p,'Color',[0.73 0.83 0.96],'LineWidth',2);

p = cdfplot(Background_Whatsapp2_DL_IAT);
set(p,'Color',[0.3 0.3 0.3],'LineWidth',2);

% p = cdfplot(Background_Skype_DL_IAT);
% set(p,'Color',[0.48 0.06 0.89],'LineWidth',2);


legend('OS','NTP','GPS','Android','Weather','Weather2','Facebook','Facebook2','Facebook3','Mix','Mix2','Mix3','Mix4','Whatsapp2','Location','SouthEast');

%IAT cdfplot
set(gca,'Xscale','Log');
axis([1e-3 1e3 0 1]);
title('Background: DL Inter-Arrival Time Distribution');
xlabel('Packet Inter-Arrival Time (seconds)');
ylabel('CDF');

%Size cdfplot
% axis([0 1600 0 1]);
% title('Background: DL Packet Size Distribution');
% xlabel('Packet Size (bytes)');
% ylabel('CDF');


hold off