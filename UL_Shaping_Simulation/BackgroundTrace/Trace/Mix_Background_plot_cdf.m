figure
hold on

p = cdfplot(Background_Mix_DL_IAT);
set(p,'Color',[0 0.6 0.2],'LineWidth',2);

p = cdfplot(Background_Mix2_DL_IAT);
set(p,'Color',[0.2 0.8 0.3],'LineWidth',2);

p = cdfplot(Background_Mix3_DL_IAT);
set(p,'Color',[0.87 0.49 0],'LineWidth',2);

p = cdfplot(Background_Mix4_DL_IAT);
set(p,'Color',[1 0.5 1],'LineWidth',2);

p = cdfplot(Intel_Mix_Background1_DL_IAT);
set(p,'Color',[1 0.09 0.4],'LineWidth',2);

p = cdfplot(Intel_Mix_Background2_DL_IAT);
set(p,'Color',[0 0 1],'LineWidth',2);

p = cdfplot(Intel_Mix_Background3_DL_IAT);
set(p,'Color',[0.2 0.3 0.4],'LineWidth',2);

p = cdfplot(Intel_Mix_Background4_DL_IAT);
set(p,'Color',[0 0.7 0.7],'LineWidth',2);

p = cdfplot(Intel_Mix_Background5_DL_IAT);
set(p,'Color',[0.6 0.2 0],'LineWidth',2);

% p = cdfplot(Background_Mix2_IAT);
% set(p,'Color',[0.04 0.52 0.78],'LineWidth',2);
% 
% p = cdfplot(Background_Mix3_IAT);
% set(p,'Color',[0.12 0.39 0.91],'LineWidth',2);
% 
% p = cdfplot(Background_Whatsapp2_IAT);
% set(p,'Color',[0.73 0.83 0.96],'LineWidth',2);
% 
% p = cdfplot(Background_Skype_IAT);
% set(p,'Color',[0.48 0.06 0.89],'LineWidth',2);
% 
% p = cdfplot(Background_Mix4_IAT);
% set(p,'Color',[0.3 0.3 0.3],'LineWidth',2);

legend('Mix1','Mix2','Mix3','Mix4','Intel Mix1','Intel Mix2','Intel Mix3','Intel Mix4','Intel Mix5');

%IAT cdfplot
set(gca,'Xscale','Log');
axis([1e-3 1e3 0 1]);
title('Mix Background: DL Inter-Arrival Time Distribution');
xlabel('Packet Inter-Arrival Time (seconds)');
ylabel('CDF');

%Size cdfplot
% axis([0 1600 0 1]);
% title('Background: DL Packet Size Distribution');
% xlabel('Packet Size (bytes)');
% ylabel('CDF');


hold off