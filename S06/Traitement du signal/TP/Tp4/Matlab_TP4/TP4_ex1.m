
close all;
clear all;

N=100;
Te=1;Fe=1/Te;

t=(0:N-1)*Te; f=(0:N/2)*Fe/N;

a= input ('a=');

num=[1];

den=[1-a];

imp= zeros(1,N); imp(1)=1;
ind=ones(1,N);

yimp(1)=imp(1);
for k=2:N,
    yimp(k)=imp(k)+ a*yimp(k-1);
end

figure(1)
subplot(211)
plot(t,yimp);
xlabel('temps');
ylabel('reponse imp');

yind(1)=ind(1);
for k=2:N,
    yind(k)=ind(k)+ a*yind(k-1);
end

subplot(212)
plot(t,yind);
xlabel('temps');
ylabel('reponse ind');


z = exp(2*pi*i*f*Te);
H = 1./(1-a*z.^-1);

%trace du module et de l'argument
figure
module= abs(H);
argument = angle(H);

%Module
subplot(2,1,1);
plot(f,module)
title('le module H');
xlabel ('Frequence Hz');
ylabel ('module de H');

%Argument

subplot(2,1,2);
plot(f,argument)
title('largument H');
xlabel ('Frequence Hz');
ylabel ('argument  H');

%pole et zeros

figure(3)
zplane(num,den)


title('position de zero et pole dans le plan complexe');
xlabel ('Reel');
ylabel ('Imaginaire');




