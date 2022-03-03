%EXO2 TP3%%%

close all;
clear all;
f1= 10.5;
fp=70;

N=256;
Fe=512;
Te=1/Fe;
Tmax =(N-1)*Te;
t=0:Te:Tmax;

a=2;
x1=a*cos(2*pi*f1*t);
xm_ap= (1+x1).*cos(2*pi*fp*t);
xm_sp= x1.*cos(2*pi*fp*t);

figure(1)
subplot(211)
plot(t,xm_ap);
xlabel('Temps');
ylabel('signal modulé avec porteuse');
title('Modulations avec et sans porteuse');

subplot(212)
plot(t,xm_sp);
xlabel('Temps');
ylabel('signal modulé sans porteuse');

%spectre

delta_f=Fe/N;
freq=delta_f*(0:N/2-1);

figure(2)
Xm_ap=Te*abs(fft(xm_ap));
Xm_sp=Te*abs(fft(xm_sp));
subplot(211)
plot(freq,Xm_ap(1:N/2));
xlabel('Fréquence');
ylabel('spectre du signal modulé avec porteuse');
title('Modulations avec et sans porteuse');
subplot(212)
plot(freq,Xm_sp(1:N/2));
xlabel('Fréquence');
ylabel('spectre du signal modulé sans porteuse');

%demodulation 
xm_ap_demod = xm_ap.*cos(2*pi*fp*t);
xm_sp_demod = xm_sp.*cos(2*pi*fp*t);



figure (3)
subplot (211)
plot(t, xm_ap_demod);
xlabel('temps');
ylabel('signal demodulé avecporteuse');

%spectre 
figure(4)
Xm_ap_demod=Te*abs(fft(xm_ap_demod));
Xm_sp_demod=Te*abs(fft(xm_sp_demod));
subplot(2,1,1)
plot(freq,Xm_ap_demod(1:N/2));
xlabel('Fréquence');
ylabel('spectre du signal démodulé avec porteuse');
title('Démodulations avec et sans  porteuse');

subplot(2,1,2)
plot(freq,Xm_sp_demod(1:N/2));
xlabel('Fréquence');
ylabel('spectre du signal démodulé avec porteuse');
%filtrage  passe bas des signaux
xm_ap_demod_filtre=filtrage_reel(xm_ap_demod,Te,N,70);
xm_sp_demod_filtre=filtrage_reel(xm_sp_demod,Te,N,70);

figure(5)
subplot(2,1,1)
plot(t,xm_ap_demod_filtre-mean(xm_ap_demod_filtre)); %On enleve la composante continue
xlabel('Temps');
ylabel('signal démodulé avec porteuse');

title('Démodulation(incluant le filtrage passe-bas) des signaux modulés avec et sans porteuse');

subplot(2,1,2);
plot(t,xm_ap_demod_filtre);
xlabel('Temps');
ylabel('signal démodulé sans porteuse');


