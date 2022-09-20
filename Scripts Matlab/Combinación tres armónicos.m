clear all;
close all;
f1 = 50;
f2 = 100;
f3 = 150;
T = 1/f3;
nm = 40;
V_rms = 230;
Vp = sqrt(2)*V_rms;
Vpp = 2*Vp;

%% Potencia contratada 1: 
% P1 = 1150W, Irms = P1/Vrms = 5A, Vrms = 230V
Irms_1 = 5;
Ip_11 = (sqrt(2)*Irms_1)/2;
Ip_12 = Ip_11/2;
Ip_13 = Ip_11/8;

%% Potencia contratada 2: 
Irms_2 = 10;
Ip_21 = (sqrt(2)*Irms_2)/2;
Ip_22 = Ip_21/2;
Ip_23 = Ip_21/8;

%% Potencia contratada 3: 
Irms_3 = 15;
Ip_31 = (sqrt(2)*Irms_3)/2;
Ip_32 = Ip_31/2;
Ip_33 = Ip_31/8;

%% Potencia contratada 4: 
Irms_4 = 16;
Ip_41 = (sqrt(2)*Irms_4)/2;
Ip_42 = Ip_41/2;
Ip_43 = Ip_41/8;

t = [0 : 1/(nm*f1) : 0.1 ];

v = Vp*sin(2*pi*f1*t); %tension
vrms = rms(v)

%%P1 = 1150W, Irms = P1/Vrms = 5A, Vrms = 230V
i11 = Ip_11*sin(2*pi*f1*t); %%corriente
i12 = Ip_12*sin(2*pi*f2*t);
i13 = Ip_13*sin(2*pi*f3*t);
i1 = i11 + i12 + i13;
irms_1 = rms(i1)
irms_11 = rms(i11);
irms_12 = rms(i12);
irms_13 = rms(i13);
pt_1 = v.*i1;

P_1 = sum(pt_1)/length(v) %potencia real
S_1 = vrms*irms_1 %% potencia aparente
THD1 = (sqrt(irms_12^2+irms_13^2)/irms_11)*100
PF_1 = (P_1/S_1)*(1/sqrt(1+(THD1/100)^2)) %% factor de potencia

%%P2 = 2300W, Irms = P2/Vrms = 10A, Vrms = 230V
i21 = Ip_21*sin(2*pi*f1*t);
i22 = Ip_22*sin(2*pi*f2*t);
i23 = Ip_23*sin(2*pi*f3*t);
i2 = i21 + i22 + i23;
irms_2 = rms(i2)
irms_21 = rms(i21);
irms_22 = rms(i22);
irms_23 = rms(i23);

pt_2 = v.*i2;
P_2 = sum(pt_2)/length(v) %potencia real
S_2 = vrms*irms_2 %% potencia aparente
THD2 = (sqrt(irms_22^2+irms_23^2)/irms_21)*100
PF_2 = (P_2/S_2)*(1/sqrt(1+(THD2/100)^2))
%%P3 = 3450W, Irms = P3/Vrms = 15A, Vrms = 230V
i31 = Ip_31*sin(2*pi*f1*t);
i32 = Ip_32*sin(2*pi*f2*t);
i33 = Ip_33*sin(2*pi*f3*t);
i3 = i31 + i32 + i33;
irms_3 = rms(i3)
irms_31 = rms(i31);
irms_32 = rms(i32);
irms_33 = rms(i33);

pt_3 = v.*i3;
P_3 = sum(pt_3)/length(v) %potencia real
S_3 = vrms*irms_3 %% potencia aparente
THD3 = (sqrt(irms_32^2+irms_33^2)/irms_31)*100
PF_3 = (P_3/S_3)*(1/sqrt(1+(THD3/100)^2))

%%P4 = 4600W, Irms = P4/Vrms = 20A (máxima 16A), Vrms = 230V
i41 = Ip_41*sin(2*pi*f1*t);
i42 = Ip_42*sin(2*pi*f2*t);
i43 = Ip_43*sin(2*pi*f3*t);
i4 = i41 + i42 + i43;
irms_4 = rms(i4)
irms_41 = rms(i41);
irms_42 = rms(i42);
irms_43 = rms(i43);

pt_4 = v.*i4;

P_4 = sum(pt_4)/length(v) %potencia real
S_4 = vrms*irms_4 %% potencia aparente
THD4 = (sqrt(irms_42^2+irms_43^2)/irms_41)*100
PF_4 = (P_4/S_4)*(1/sqrt(1+(THD4/100)^2))
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

