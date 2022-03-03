%EX1 tp3_5d%%%%%%

close ALL;
clear all;

N=256;
Fe=512;
Te=1/Fe;
Tmax=(N-1)*Te;
t=0:Te:Tmax;

a1=1;
a2=0.1;
a3=1;
f1=10;
phi=pi/6;
x1=a1*cos(2*pi*f1*t);
x2=a2*cos(2*pi*f1*t+phi)+a3*randn(1,N);

figure(1)
subplot(211)
plot(t,x1);

xlabel('Temps');
ylabel('x1');
legend('x1');

subplot(212)
plot(t,x1);

xlabel('Temps');
ylabel('x2');
legend('x2');

%etude de la fonction d'intercorrelation x et y

corrub12=xcorr(x1,x2,'unbiased'); %division de xcor par N-m

figure(2)
largcorr=80;
largtau= [-largcorr:largcorr];

tau=largtau*Te;
plot(tau,corrub12(N+largtau),'k-')
xlabel('temps tau');
ylabel('corr(x1 x2)');
title('intercorrelation entre x1 et x2 (unbiased)');










