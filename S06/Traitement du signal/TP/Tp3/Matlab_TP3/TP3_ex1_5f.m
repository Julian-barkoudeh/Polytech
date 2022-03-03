%EX1 tp3_5d%%%%%%
close all;
clear all;

f1=10.5;
N=256;
Fe=512;
Te=1/Fe;
Tmax=(N-1)*Te;
t=0:Te:Tmax;

a=2;
x= a*cos(2*pi*f1*t);

figure (1)
freq=(0:N/2)/(N*Te);
cx=xcorr(x,'biased'); % divise par N
c=cx(N:2*N-1);  % on garde pr tau>0 de xcorr
C=fft(c,N)*Te;  % FFT de la partie droite de xcorr
T_Fourier_C=2*real(C)-Te*c(1);


semilogy(freq,T_Fourier_C(1:N/2+1),'ko')
xlabel('Fréquence / Hz');
ylabel('TF de corr(y) / V^2 Hz^-^1');
hold on ;
X=fft(x,N)*Te;
DSP=(abs(X).^2)/(N*Te);
semilogy(freq,DSP(1:N/2+1),'r.')

figure(2)
plot(freq,abs(T_Fourier_C(1:N/2+1)),'k')
hold on