clear all;
close all;
f1 = 50;
f2 = 100;
T = 1/f2;
nm = 40;
V_rms = 230;
Vp = sqrt(2)*V_rms;
Vpp = 2*Vp;

%% Potencia contratada 1: 
% P1 = 1150W, Irms = P1/Vrms = 5A, Vrms = 230V
Irms_1 = 5;
Ip_11 = (sqrt(2)*Irms_1)/2;
Ip_12 = Ip_11/2;

%% Potencia contratada 2: 
Irms_2 = 10;
Ip_21 = (sqrt(2)*Irms_2)/2;
Ip_22 = Ip_21/2;
i2 = Ip_21 + Ip_22;

%% Potencia contratada 3: 
Irms_3 = 15;
Ip_31 = (sqrt(2)*Irms_3)/2;
Ip_32 = Ip_31/2;
i3 = Ip_31 + Ip_32;

%% Potencia contratada 4: 
Irms_4 = 16;
Ip_41 = (sqrt(2)*Irms_4)/2;
Ip_42 = Ip_41/2;
i4 = Ip_41 + Ip_42;

t = [0 : 1/(nm*f1) : 0.1 ];

v = Vp*sin(2*pi*f1*t); %tension
vrms = rms(v)

%%P1 = 1150W, Irms = P1/Vrms = 5A, Vrms = 230V
i11 = Ip_11*sin(2*pi*f1*t); %%corriente
i12 = Ip_12*sin(2*pi*f2*t);
i1 = i11 + i12;
irms_1 = rms(i1)
irmsTHD1 = rms(i12);
irms1_0 = rms(i11);

%% Distorsión armónica
THDI_1 = (irmsTHD1/irms1_0)*100;

pt_1 = v.*i1;
P_1 = sum(pt_1)/length(v) %potencia real
S_1 = vrms*irms_1 %% potencia aparente
%%PF_sin = (P_1/S_1);
PF_1 = (P_1/S_1)*(1/sqrt(1+(THDI_1/100)^2)) %% factor de potencia

%%P2 = 2300W, Irms = P2/Vrms = 10A, Vrms = 230V
i21 = Ip_21*sin(2*pi*f1*t);
i22 = Ip_22*sin(2*pi*f2*t);
i2 = i21 + i22;
irms_2 = rms(i2)
irmsTHD2 = rms(i22);
irms2_0 = rms(i21);

pt_2 = v.*i2;
P_2 = sum(pt_2)/length(v) % potencia real
S_2 = vrms*irms_2 % potencia aparente
THDI_2 = (irmsTHD2/irms2_0)*100; %% distorsión armónica
PF_2 = (P_2/S_2)*(1/sqrt(1+(THDI_2/100)^2)) %% factor de potencia

%%P3 = 3450W, Irms = P3/Vrms = 15A, Vrms = 230V
i31 = Ip_31*sin(2*pi*f1*t);
i32 = Ip_32*sin(2*pi*f2*t);
i3 = i31 + i32;
irms_3 = rms(i3)
irmsTHD3 = rms(i32);
irms3_0 = rms(i31);

pt_3 = v.*i3;
P_3 = sum(pt_3)/length(v) %potencia real
S_3 = vrms*irms_3 %% potencia aparente
THDI_3 = (irmsTHD3/irms3_0)*100; %% distorsión armónica
PF_3 = (P_3/S_3)*(1/sqrt(1+(THDI_3/100)^2)) %% factor de potencia

%%P4 = 4600W, Irms = P4/Vrms = 20A (máxima 16A), Vrms = 230V
i41 = Ip_41*sin(2*pi*f1*t);
i42 = Ip_42*sin(2*pi*f2*t);
i4 = i41 + i42;
irms_4 = rms(i4)
irmsTHD4 = rms(i42);
irms4_0 = rms(i41);

pt_4 = v.*i4;
P_4 = sum(pt_4)/length(v) %potencia real
S_4 = vrms*irms_4 %% potencia aparente
THDI_4 = (irmsTHD4/irms4_0)*100; %% distorsión armónica
PF_4 = (P_4/S_4)*(1/sqrt(1+(THDI_4/100)^2)) %% factor de potencia


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

