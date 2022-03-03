%EX1 tp3_5a%%%%%%

close all;
clear all;
f1= 10.5;

N=256;
Fe=512;
Te=1/Fe;
Tmax =(N-1)*Te;
t=0:Te:Tmax;

a=2;
x1=a*cos(2*pi*f1*t);

figure(1)
plot(t,x1);

xlabel('temps / s');
ylabel('x1 / V');
legend('x1');

%La fonction de corrélation x1
corrx1=xcorr(x1);
corrx1b=xcorr(x1,'biased'); %division de xcorr par N-m
corrx1ub=xcorr(x1,'unbiased'); %division de xcorr par N

largcorr=N-1; % pour centrer l'etude de xcorr autour de tau = 0
tau=(-largcorr:largcorr)*Te;
figure(2)
subplot(3,1,1)
plot(tau,corrx1(N-largcorr:N+largcorr), 'r.')
xlabel('Temps tau /s');
ylabel('corr(x1) /V^2');
legend('cx','Location','North')

subplot(3,1,2)
plot(tau,corrx1b(N-largcorr:N+largcorr), 'r.')
xlabel('Temps tau /s');
ylabel('corr(x1) /V^2');
legend('Cx biased','Location','North')

subplot(3,1,3)
corrtheox1=0.5*a^2*cos(2*pi*f1*tau);
plot(tau,corrx1ub, 'r.', tau,corrtheox1,'k.')
xlabel('Temps tau /s');
ylabel('corr(x1) /V^2');
legend('Rouge Cx','noir corrx1 theor','Location','North')







