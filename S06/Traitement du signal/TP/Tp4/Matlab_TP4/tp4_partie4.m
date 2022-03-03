

clear all
close all
clc
load signal2
r=input('r= ');
fo =20000
Fe=100000;
f1=40000;
f2=20000;
Te=1/Fe;
N=length(signal);
m=1:1:N;
f=0:Fe/N:(N-1)*Fe/N;
rep=filter([1], [1, -2*r*cos(2*pi*fo*Te) r^2], signal);
plot(m, rep);
title('représentation de la réponse du signal');
xlabel('temps');
ylabel('Amp');
