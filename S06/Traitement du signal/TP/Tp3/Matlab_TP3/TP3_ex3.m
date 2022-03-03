%TP3 Exo3 %%%%%%%%%%%%%%%%%%%%%%%%%

close all;
clear all;

N=2048;
Fe=512;
Te=1/Fe;

t=(0:N-1)*Te;
x=randn(1,N)+cos(2*pi*60*t);

figure(1)
subplot(121)
plot(t,x);
axis([0 N*Te -5 5]);
xlabel('temps');
ylabel('signal x');
title('signal x de depart');

freq=(0:N/2)/(N*Te);

subplot(122)
X=fft(x,N)*Te;
DSPX=(abs(X).^2)/(N*Te);
semilogy(freq(2:N/2+1),DSPX(2:N/2+1),'r-')
xlabel('Fréquence');
ylabel('DSP x');

N_prime=N/8;
Te_prime=8*Te;
Fe_prime=1/Te_prime;
t_prime= (0:N_prime-1)*Te_prime;

%y = signal x sous-échantillonné
y=x(8*[1:N/8]-7); %on prend 1 point sur 8 en partant du premier

figure(2)
subplot(121)
plot(t_prime,y);
axis([0 N_prime*Te_prime -5 5]);
xlabel('temps');
ylabel('signal x sous-échant.');
title('signal x sous-échantillonné');

freq=(0:N_prime/2)/(N_prime*Te_prime);

subplot(122)
Y=fft(y,N_prime)*Te_prime;
DSPY=(abs(Y).^2)/(N_prime*Te_prime);
semilogy(freq(2:N_prime/2+1),DSPY(2:N_prime/2+1),'r-')
xlabel('Frequence');
ylabel('DSP x sous-echant.');

xf = filtrage_reel(x,Te,N,0.8*Fe_prime/2); %signal x filtré
z = xf(8*(1:N/8)-7); %on prend un 1 point sur 8
%z c'est le signal x filtré et échantillonné

figure(3)
subplot(121);
plot(t_prime,z);
axis([0 N_prime*Te_prime -5 5]);
xlabel('temps');
ylabel('signal x filtré sous-echant.');
title('signal x filtré sous-echantillonné');


subplot(122)
Z=fft(z,N_prime)*Te_prime;
DSPZ=(abs(Z).^2)/(N_prime*Te_prime);
semilogy(freq(2:N_prime/2+1),DSPZ(2:N_prime/2+1),'r-o')
xlabel('Frequence');
ylabel('DSP x sous-echant.');
hold on;
semilogy(freq(2:N_prime/2+1),DSPX(2:N_prime/2+1),'b-')

figure(4)
imp=zeros(1,N); imp(1)=1;
repimp = filtrage_reel(imp, Te, N, 0.8*Fe_prime/2);
H=fft(repimp,N);
modH=abs(H);
freq=(0:N/2)/(N*Te);
subplot(211)
plot(freq(1:N/2),modH(1:N/2),'r-')
xlabel('Fréquence');
ylabel('module de la fn de transfert du filtre réel');
subplot(212)
phaseH=angle(H)*180/pi;
plot(freq(1:N/2+1),phaseH(1:N/2+1),'r-')
xlabel('Fréquence');
ylabel('Phase de la fn de transfert du filtre');

























