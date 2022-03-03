close all;
clear all;

load s1;
load s2;
N=size(s1,2);
Fe=512;
Te=1/Fe;
Tmax=(N-1)*Te;
time=0:Te:Tmax;

s=s1.*cos(2*pi*35*time)+s2.*cos(2*pi*95*time);


figure (1)
subplot(3,1,1)
plot(time,s1,'r');
axis([0 N*Te -1 1]);
xlabel('Temps ');
ylabel('signal s1');
title('Signaux s1, s2 et modulé');

subplot(3,1,2)
plot(time,s2,'r');
axis([0 N*Te -2 2]);
xlabel('Temps');
ylabel('signal s2');

subplot(3,1,3)
plot(time,s,'r');
axis([0 N*Te -2 2]);
xlabel('Temps');
ylabel('signal modulé');

figure (2)
freq=(0:N/2)/(N*Te);
subplot(3,1,1)
S1=fft(s1,N)*Te;
DSPS1=(abs(S1).^2)/(N*Te);
semilogy(freq(2:N/2+1),DSPS1(2:N/2+1),'r.')
xlabel('Fréquence');
ylabel('DSP s1');

subplot(3,1,2)
S2=fft(s2,N)*Te;
DSPS2=(abs(S2).^2)/(N*Te);
semilogy(freq(2:N/2+1),DSPS2(2:N/2+1),'r.')
xlabel('Fréquence');
ylabel('DSP s2');

subplot(3,1,3)
s2=fft(s,N)*Te;
DSPS2=(abs(S2).^2)/(N*Te);
semilogy(freq(2:N/2+1),DSPS2(2:N/2+1),'r.')
xlabel('Fréquence');
ylabel('DSP signal modulé');

s1df = 2.*filtrage_reel(s.*cos(2*pi*35*time),Te,N,10);% signal s1 démodulé
s2df = 2.*filtrage_reel(s.*cos(2*pi*95*time),Te,N,10);% signal s2 démodulé

figure(3)
subplot(2,1,1)
plot(time,s1df,'r');
axis([0 N*Te -1 1]);
xlabel('Temps');
ylabel('Signaux s1, s2 démodulés');

subplot(2,1,2)
plot(time,s2df,'r');
axis([0 N*Te -2 2]);
xlabel('Temps');
ylabel('signal s2 démodulé');

figure(4)
subplot(2,1,1)
plot(time,s1,'k',time,s1df,'r');
xlabel('Temps');
ylabel('Signal s1 démodulé');
title('signaux s1, s2 démodulé');

subplot(2,1,2)
plot(time,s2,'k',time,s2df,'r');
axis([0 N*Te -2 2]);
xlabel('Temps');
ylabel('signal s2 démodulé');