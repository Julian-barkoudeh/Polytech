%*************************** MOHAMET CHERIF FAYE ************************
%EI2I3_HF
%TP4 - Traitement du signal

clear all
close all
clc

%a=0.5;
r=input('r= ');
%%équation de récurrece
Fe=1;
fo=0.2;
Te=1/Fe;
N=50;
m=1:1:N;
%fm=0:(N-1)*Fe/N
f=0:Fe/N:(N-1)*Fe/N;

x_ind=ones(1,N);
x_imp=zeros(1,N); x_imp(1)=1;
y=zeros(1, N);

%réponse indicielle et impulsionnelle avec utilisation de la fonxtion
%filter
rep_ind=filter([1], [1, -2*r*cos(2*pi*fo*Te) r^2], x_ind);
rep_imp=filter([1], [1, -2*r*cos(2*pi*fo*Te) r^2], x_imp);
%MODULE 
Yf= fft(rep_imp)
module = abs(Yf);
%PHASE 
H= (1./(sqrt(1-2*r*cos(2*pi*(f-fo)*Te)+ r*r)).*(1./(sqrt(1-2*r*cos(2*pi*(f+fo)*Te)+ r*r))));
%ph=-1*atan2((a*sin(2*pi*fm*Te)),(1-a*cos(2*pi*fm*Te)));

%AFFICHAGE DES COURBES
%affichage réponse indicielle
subplot(3,1,1)
plot(m, rep_ind);
title('représentation de la réponse indicielle');
xlabel('temps[s]');
ylabel('Amplitude[V]');
%affichage réponse impulsionnelle
subplot(3,1,2);
plot(m, rep_imp);
title('représentation de la réponse impulsionnelle');
xlabel('temps[s]');
ylabel('Amplitude[V]');
%affichage module
subplot(3,1,3);
plot(f,module);
title('représentation module');
xlabel('temps[s]');
ylabel('Amplitude[V]');

%affichage phase
% subplot(4,1,4);
% plot(f,ph);
% title('représentation de la phase');
% xlabel('temps[s]');
% ylabel('Amplitude[V]');

