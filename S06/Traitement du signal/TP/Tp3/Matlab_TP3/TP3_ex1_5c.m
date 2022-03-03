%EX1 tp3_5c%%%%%%

close ALL;
clear all;

N=256;
Fe=512;
Te=1/Fe;
Tmax=(N-1)*Te;
t=0:Te:Tmax;

x=randn(1,N);
xf = filtrage_reel(x,Te,N,50);%filtrage de x

figure(1)
subplot(2,1,1)
plot(t,x);
xlabel('Temps / s');
ylabel('x / v');
legend('Bruit Blanc');

subplot(2,1,2)
plot(t,xf);
axis([0 0.5 -1 1])
xlabel('Temps / s');
ylabel('x filtré / v');
legend('Bruit non Blanc');

corrx=xcorr(x,'unbiased');
corrxf=xcorr(xf,'unbiased');

figure(2)
largcorr=N-1; %permet de centrer l'étude de xcorr autour de tau=0
tau=(-largcorr:largcorr)*Te;
subplot(2,1,1)
plot(tau,corrx(N-largcorr:N+largcorr),'r.')
xlabel('Temps tau / s');
ylabel('xcorr(x) / v^2');
legend('rouge corr x','location','NorthEast');

subplot(2,1,2)
plot(tau,corrxf,'b.')
xlabel('Temps tau / s');
ylabel('xcorr(xf) / v^2');
legend('bleu corr x filtré','location','NorthEast');