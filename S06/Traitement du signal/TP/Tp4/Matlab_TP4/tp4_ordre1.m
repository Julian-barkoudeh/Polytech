%*************************** MOHAMET CHERIF FAYE ************************
%EI2I3_HF
%TP4 - Traitement du signal

clear all
close all
clc

a= input('a= ')
%%�quation de r�currece
Fe=1;
Te=1/Fe;
N=50;
m=1:1:N;
%fm=0:(N-1)*Fe/N
fm=0:Fe/N:(N-1)*Fe/N;

%r�ponse indicielle et impulsionnelle
x_ind=ones(1,N);
x_imp=zeros(1,N); x_imp(1)=1;
y=zeros(1, N);
y(1)=x_ind(1);
y2(1)= x_imp(1);

%BOUCLE FOR
for n=2:N
    y(n)=x_ind(n)+a*y(n-1) %% reponse indicielle
    y2(n)=x_imp(n)+a*y2(n-1) %% reponse impulsionnelle
end

%MODULE 
Yf= fft(y2)
module = abs(Yf);
%PHASE 
H= 1./(sqrt(1-2*a*cos(2*pi*fm*Te)+ a*a));
ph=-1*atan2((a*sin(2*pi*fm*Te)),(1-a*cos(2*pi*fm*Te)));

%AFFICHAGE DES COURBES
%affichage r�ponse indicielle
subplot(4,1,1)
plot(m, y);
title('repr�sentation de la r�ponse indicielle');
xlabel('temps[s]');
ylabel('Amplitude[V]');
%affichage r�ponse impulsionnelle
subplot(4,1,2);
plot(m, y2);
title('repr�sentation de la r�ponse impulsionnelle');
xlabel('temps[s]');
ylabel('Amplitude[V]');
%affichage module
subplot(4,1,3);
plot(module);
title('repr�sentation module');
xlabel('temps[s]');
ylabel('Amplitude[V]');

%affichage phase
subplot(4,1,4);
plot(fm,ph);
title('repr�sentation de la phase');
xlabel('temps[s]');
ylabel('Amplitude[V]');


