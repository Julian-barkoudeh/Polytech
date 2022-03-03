%EX1 tp3_5b%%%%%%

close all;
clear all;
f1= 10.5;
f2=60;

N=256;
Fe=512;
Te=1/Fe;
Tmax =(N-1)*Te;
t=0:Te:Tmax;

a=2;
x1=a*cos(2*pi*f1*t);
x2=cos(2*pi*f2*t+pi/4);

figure(1)
subplot(211)
plot(t,x1);

xlabel('temps / s');
ylabel('x1 / V');
legend('x1');

subplot(212)
plot(t,x2);

xlabel('temps / s');
ylabel('x2 / V');
legend('x2');

corrx1x2=xcorr(x1,x2,'unbiased'), %division de xcorr par N-m

figure(2)
largcorr=N-1;
tau=(-largcorr:largcorr)*Te;
plot(tau,corrx1x2(N-largcorr:N+largcorr), 'r.')
xlabel('Temps tau /s');
ylabel('corr(x1,x2) /V^2');
