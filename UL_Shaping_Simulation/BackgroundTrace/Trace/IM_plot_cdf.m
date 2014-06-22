figure
hold on

p = cdfplot(IM_Skype_DL_IAT);
set(p,'Color',[0 0.6 0.2],'LineWidth',2);

p = cdfplot(IM_Skype2_DL_IAT);
set(p,'Color',[0.2 0.8 0.3],'LineWidth',2);

p = cdfplot(IM_MSNeBuddy_DL_IAT);
set(p,'Color',[0.30588236451149 0.396078437566757 0.580392181873322],'LineWidth',2);

p = cdfplot(IM_MSNeBuddy2_DL_IAT);
set(p,'Color',[0 0 1],'LineWidth',2);

p = cdfplot(IM_FacebookMessenger_DL_IAT);
set(p,'Color',[0 0.69803923368454 0.69803923368454],'LineWidth',2);

p = cdfplot(IM_Whatsapp_DL_IAT);
set(p,'Color',[0.87 0.49 0],'LineWidth',2);

p = cdfplot(IM_Whatsapp2_DL_IAT);
set(p,'Color',[0.682352960109711 0.466666668653488 0],'LineWidth',2);

p = cdfplot(IM_LINE_DL_IAT);
set(p,'Color',[1 0.600000023841858 0.7843137383461],'LineWidth',2);

% p = cdfplot(IM_WhatsappBackground2_DL_IAT);
% set(p,'Color',[1 0.09 0.4],'LineWidth',2);

% p = cdfplot(Mix_Background_DL_IAT);
% set(p,'Color',[0.6 0.2 0],'LineWidth',2);

% legend('Skype','SkypeBackground','MSN(eBuddy)','MSN(eBuddy)2','FacebookMessenger','Whatsapp','Whatsapp2','WhasappBackground','WhasappBackground2','Location','SouthEast');
legend('Skype','Skype2','MSN(eBuddy)','MSN(eBuddy)2','FacebookMessenger','Whatsapp','Whatsapp2','LINE','Location','SouthEast');

%IAT cdfplot
set(gca,'Xscale','Log');
axis([1e-3 1e3 0 1]);
title('IM: DL Inter-Arrival Time Distribution');
xlabel('Packet Inter-Arrival Time (seconds)');
ylabel('CDF');

%Size cdfplot
% axis([0 1600 0 1]);
% title('IM: DL Packet Size Distribution');
% xlabel('Packet Size (bytes)');
% ylabel('CDF');


hold off