clear all;
close all;
f1 = 50;
T = 1/f1;
nm = 40;
V_rms = 230;
Vp = sqrt(2)*V_rms;
Vpp = 2*Vp;

%% Potencia contratada 1: 
% P1 = 1150W, Irms = P1/Vrms = 5A, Vrms = 230V
Irms_1 = 5;
Ip_1 = sqrt(2)*Irms_1;
%% Potencia contratada 2: 
Irms_2 = 10;
Ip_2 = sqrt(2)*Irms_2;
%% Potencia contratada 3: 
Irms_3 = 15;
Ip_3 = sqrt(2)*Irms_3;
%% Potencia contratada 4: 
Irms_4 = 16; %% máxima corriente 
Ip_4 = sqrt(2)*Irms_4;

t = [0 : 1/(nm*f1) : 0.1 ];

v = Vp*sin(2*pi*f1*t); % señal de tension
vrms = rms(v)

%%P1 = 1150W, Irms = P1/Vrms = 5A, Vrms = 230V
i1 = Ip_1*sin(2*pi*f1*t); %%corriente
irms_1 = rms(i1)
pt_1 = v.*i1;
P_1 = sum(pt_1)/length(v) %potencia real
S_1 = vrms*irms_1 %% potencia aparente
PF_1 = P_1/S_1 %% factor de potencia

%%P2 = 2300W, Irms = P2/Vrms = 10A, Vrms = 230V
i2 = Ip_2*sin(2*pi*f1*t);
irms_2 = rms(i2)
pt_2 = v.*i2;
P_2 = sum(pt_2)/length(v) %potencia real
S_2 = vrms*irms_2 %% potencia aparente
PF_2 = P_2/S_2 %% factor de potencia

%%P3 = 3450W, Irms = P3/Vrms = 15A, Vrms = 230V
i3 = Ip_3*sin(2*pi*f1*t);
irms_3 = rms(i3)
pt_3 = v.*i3;
P_3 = sum(pt_3)/length(v) %potencia real
S_3 = vrms*irms_3 %% potencia aparente
PF_3 = P_3/S_3 %% factor de potencia

%%P4 = 4600W, Irms = P4/Vrms = 20A (máxima 16A), Vrms = 230V
i4 = Ip_4*sin(2*pi*f1*t);
irms_4 = rms(i4)
pt_4 = v.*i4;
P_4 = sum(pt_4)/length(v) %potencia real
S_4 = vrms*irms_4 %% potencia aparente
PF_4 = P_4/S_4 %% factor de potencia

figure(1);
plot(t,v);
axis([0 0.1 -Vp Vp]);
hold on;
figure(1);
plot(t,i1);
axis([0 0.1 -Vp Vp]);
hold on;
figure(1);
plot(t,i2);
axis([0 0.1 -Vp Vp]);
hold on;
figure(1);
plot(t,i3);
axis([0 0.1 -Vp Vp]);
hold on;
figure(1);
plot(t,i4);
axis([0 0.1 -Vp Vp]);




