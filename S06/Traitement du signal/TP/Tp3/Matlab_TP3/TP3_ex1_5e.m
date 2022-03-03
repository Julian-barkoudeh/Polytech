%EX1 tp3_5e%%%%%%

close ALL;
clear all;
load x;
load y;
N=length(x);
Fe=512;
Te=1/Fe;
Tmax=(N-1)*Te;
t=0:Te:Tmax;


figure(1)
subplot(2,1,1)
plot(t,x);
xlabel('Temps');
ylabel('x');
legend('x');

subplot(2,1,2)
plot(t,y);
xlabel('Temps');
ylabel('y');
legend('y');

corrxyub=xcorr(x,y,'unbiased');

figure(2)

largcorr=N-1;
largtau=[-largcorr:largcorr];
tau=largtau*Te;
plot(tau,corrxyub(N+largtau),'r')
xlabel('Temps tau')
ylabel('corr(x y)');
legend('rouge corrxy unbiased','location','NorthWest');



