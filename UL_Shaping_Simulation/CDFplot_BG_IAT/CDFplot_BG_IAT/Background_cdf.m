figure
hold on

load C:\Users\Bike\Desktop\UL_shaping_simulation_20140607\UL_shaping_simulation_20140607\CDFplot_BG_IAT\CDFplot_BG_IAT\UL_BG_FB_IAT.txt
load C:\Users\Bike\Desktop\UL_shaping_simulation_20140607\UL_shaping_simulation_20140607\CDFplot_BG_IAT\CDFplot_BG_IAT\UL_BG_NTP_IAT.txt
load C:\Users\Bike\Desktop\UL_shaping_simulation_20140607\UL_shaping_simulation_20140607\CDFplot_BG_IAT\CDFplot_BG_IAT\UL_BG_Mix4.txt
load C:\Users\Bike\Desktop\UL_shaping_simulation_20140607\UL_shaping_simulation_20140607\CDFplot_BG_IAT\CDFplot_BG_IAT\UL_BG_Weather_IAT.txt
load C:\Users\Bike\Desktop\UL_shaping_simulation_20140607\UL_shaping_simulation_20140607\CDFplot_BG_IAT\CDFplot_BG_IAT\UL_BG_Whatsapp2_IAT.txt

% 
% p = cdfplot(UL_BG_FB_IAT);
% set(p,'Color',[0.7 0.2 0.4],'LineWidth',2);
% 
% p = cdfplot(UL_BG_NTP_IAT);
% set(p,'Color',[0.2 0.4 0.7],'LineWidth',2);

p = cdfplot(UL_BG_Mix4);
set(p,'Color',[1 0.6 0.1],'LineWidth',3.5);

% p = cdfplot(UL_BG_Weather_IAT);
% set(p,'Color',[0.4 0.8 0.2],'LineWidth',2);
% 
% p = cdfplot(UL_BG_Whatsapp2_IAT);
% set(p,'Color',[0.1 0.5 0.8],'LineWidth',2);

%IAT cdfplot
set(gca,'Xscale','Log');
axis([1e-5 1e4 0 1]);
title('Background (uplink): Inter-Arrival Time Distribution');
xlabel('Packet Inter-Arrival Time (seconds)');
ylabel('CDF');
legend('Mixed background');
hold off