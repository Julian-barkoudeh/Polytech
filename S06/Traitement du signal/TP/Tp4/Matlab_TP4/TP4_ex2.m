
%%%2) Filtre du premier ordre

close all;
clear all;

N=100;
Te=1/10;Fe=1/Te;

t=(0:N-1)*Te; f=(0:N/2)*Fe/N;

a= input ('a=');
b = input('b=');
num=[1 -b];

den=[1 -a];

imp= zeros(1,N); imp(1)=1;
ind=ones(1,N);


%reponse imp et ind avec le filtrage
rep_imp= filter(num,den,imp);
rep_ind= filter(num,den,ind);

figure(1)
subplot(2,1,1)
plot(t,rep_imp);
title('la reponse impul')
xlabel('temps');
ylabel('reponse imp');




subplot(212)
plot(t,rep_ind);
title('la reponse indic')
xlabel('temps');
ylabel('reponse ind');


z = exp(2*pi*1i*f*Te);
H = (1-b*z.^-1)./(1-a*z.^-1);

%trace du module et de l'argument
figure
module= abs(H);
argument = angle(H);

%Module
subplot(2,1,1);
plot(f,module);
title('le module H');
xlabel ('Frequence Hz');
ylabel ('module de H');

%Argument

subplot(2,1,2);
plot(f,argument);
title('largument H');
xlabel ('Frequence Hz');
ylabel ('argument  H');

%pole et zeros

figure(3)
zplane(num,den)


title('position de zero et pole dans le plan complexe');
xlabel ('Reel');
ylabel ('Imaginaire');




