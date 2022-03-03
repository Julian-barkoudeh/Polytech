%%%%Filtre 2eme ordre 

close all;
clear all;
 
N=200;
Te=1/10;Fe=1/Te;
 
t=(0:N-1)*Te; f=(0:N/2)*Fe/N;
 
r = input('r=');
f0 = input('f0=');
 
num=[1 0];
 
den=[1 -2*r*cos(2*pi*f0*Te) r^2];
 
imp= zeros(1,N); imp(1)=1;
ind=ones(1,N);
 
 
%reponse imp et ind avec le filtrage
rep_imp= filter(num,den,imp);
rep_ind= filter(num,den,ind);
 
figure(1)
subplot(4,1,1)
plot(t,rep_imp);
title('la reponse impul')
xlabel('temps');
ylabel('reponse imp');
 
 
 
 
subplot(412)
plot(t,rep_ind);
title('la reponse indic')
xlabel('temps');
ylabel('reponse ind');
 
 
z = exp(2*pi*1i*f*Te);
H = 1./(1-(2*r*cos(2*pi*f0*Te)*(z.^-1)) + (r^2)*(z.^-2));
 
%trace du module et de l'argument
module= abs(H);
argument = angle(H);
 
%Module
subplot(4,1,3);
plot(f,module);
title('le module H');
xlabel ('Frequence Hz');
ylabel ('module de H');
 
%Argument
 
subplot(4,1,4);
plot(f,argument);
title('phase de la fonction de transfert en degrés');
xlabel ('Frequence Hz');
ylabel ('argument H');
 
%pole et zeros
 
figure(2)
zplane(num,den)
 
 
title('position de zero et pole dans le plan complexe');
xlabel ('Reel');
ylabel ('Imaginaire');