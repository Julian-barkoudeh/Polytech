% function prin()
clear all;close all
% ATTENTION, lors de l'execution, il faut d'abord charger le signal,
% Puis faire tourner un des filtres
% Vous pouvez charger le fichier "annonce_TP_TS.wav" ou "coucou.wav"
% Pour avoir des effets sonores importants choisir des delay de plusieurs dizaines
% de millisecondes (D=1000, 2000, ...)
% NB : si vous ecoutez le signal filtre et que vous n'avez pas filtre, pas bien...
te1=1;
while te1==1,
 choix = menu(' Choisissez',...
 ' Charger le signal ',...
 ' Filtre passe bas FIR',...
 ' Peigne FIR',...
 ' Passe Tout',...
 ' Reverb',...
 ' Synthese',...
 ' Butterworth',...
 ' Ecoute signal original',...
 ' Ecoute signal filtre',...
 ' Quitter');
 if choix==1,
 close all
 [nom chemin]=uigetfile('*.wav','Fichier à charger');
% if nom==0,
% prin;
% end
 [Signal,Fe]=audioread(nom);
 Signal=Signal';
 N=length(Signal);
 Te=1/Fe;
 f=(0:N-1)/(N*Te);
 t=(0:N-1)*Te;
 imp=zeros(1,N); imp(1)=1;
 figure; plot(t,Signal);title('Signal');

 elseif choix==2,%Filtre passe bas FIR
 close all
 D = 32;

 num=ones(1,D+1);
 den = 1;
 z=exp(2*pi*1i*f*Te);
 h=(1-z.^-(D+1))./(1-z.^-1);
 impf = filter(num, den, Signal); %numérateur + dénominateur fonction de transfert
 cf=fft(impf,N)*Te; % fft réponse impulsionnelle
 c = abs(h); % Pour avoir un vecteur réel
 PC = angle(h)*(180/pi);
 % tracee du module et de l'argument du filtre
 figure(2)
 subplot(2, 1, 1);
 plot(f(2:N/2+1),c(2:N/2+1))
 title('Module fonction de transfert')
 xlabel('Fréquence / Hz');
 subplot(2, 1, 2);
 plot(f(2:N/2+1), PC(2:N/2+1)) % en degree
 xlabel('Fréquence / Hz');
 title('Phase fonction de transfert');

 % filtrage du signal fft
 Filtfft=fft(impf,N)*Te;
 signalfft=fft(Signal,N)*Te;
 % tracée du signal filtré
 figure(3)
 subplot(2, 1, 1);
 plot(t,Signal);
 xlabel('temps / s');
 title('Signal');
 subplot(2, 1, 2);
 plot(t, impf);
 xlabel('temps / s');
 title('Signal filtré ');
 % module et phase en fft
 figure(4)
 subplot(4, 1, 1);
 semilogy(f(2:N/2+1), abs(signalfft(2:N/2+1)))
 xlabel('Fréquence / Hz');
 title('Module de la tf du signal ');
 subplot(4, 1, 2);
 plot(f(2:N/2+1), angle(signalfft(2:N/2+1))*(180/pi))
 xlabel('Fréquence / Hz');
 title('Phase de la tf du signal ');
 subplot(4, 1, 3);
 semilogy(f(2:N/2+1), abs(Filtfft(2:N/2+1)))
 xlabel('Fréquence / Hz');
 title('Module de la tf du signal filtré ');
 subplot(4, 1, 4);
 plot(f(2:N/2+1), angle(Filtfft(2:N/2+1))*(180/pi))
 xlabel('Fréquence / Hz');
 title('Phase de la tf du signal filtré ');

 imp=zeros(1,N);
 imp(1)=1;
 impf = filter(num, den, imp);
 figure(5)
 plot(t,impf);
 xlabel('Temps (s)');
 title('Réponse impulsionelle');
 audiowrite('passe_bas.wav',impf/max(impf),Fe)

elseif choix==3,%Peigne FIR
 close all
 D = 16;

 num=zeros(1,D+1);
 num(1) = 1;
 num(1, D+1) = -1;
 den = (1);
 z=exp(2*pi*1i*f*Te);
 h=(1+z.^-(D));
 impf = filter(num, den, Signal); %numérateur + dénominateur fonction de transfert
 cf=fft(impf,N)*Te; % fft réponse impulsionnelle
 c = abs(h); % Pour avoir un vecteur réel
 PC = angle(h)*(180/pi);

 % tracee du module et de l'argument du filtre
 figure(2)
 subplot(2, 1, 1);
 plot(f(2:N/2+1),c(2:N/2+1))
 title('Module fonction de transfert')
 xlabel('Fréquence / Hz');
 subplot(2, 1, 2);
 plot(f(2:N/2+1), PC(2:N/2+1)) % en degree
 xlabel('Fréquence / Hz');
 title('Phase fonction de transfert');

 % filtrage du signal fft
 Filtfft=fft(impf,N)*Te;
 signalfft=fft(Signal,N)*Te;
 % tracée du signal filtré
 figure(3)
 subplot(2, 1, 1);
 plot(t,Signal);
 xlabel('temps / s');
 title('Signal');
 subplot(2, 1, 2);
 plot(t, impf);
 xlabel('temps / s');
 title('Signal filtré ');
 % module et phase en fft
 figure(4)
 subplot(4, 1, 1);
 semilogy(f(2:N/2+1), abs(signalfft(2:N/2+1)))
 xlabel('Fréquence / Hz');
 title('Module de la tf du signal ');
 subplot(4, 1, 2);
 plot(f(2:N/2+1), angle(signalfft(2:N/2+1))*(180/pi))
 xlabel('Fréquence / Hz');
 title('Phase de la tf du signal ');
 subplot(4, 1, 3);
 semilogy(f(2:N/2+1), abs(Filtfft(2:N/2+1)))
 xlabel('Fréquence / Hz');
 title('Module de la tf du signal filtré ');
 subplot(4, 1, 4);
 plot(f(2:N/2+1), angle(Filtfft(2:N/2+1))*(180/pi))
 xlabel('Fréquence / Hz');
 title('Phase de la tf du signal filtré ');

 imp=zeros(1,N);
 imp(1)=1;
 impf = filter(num, den, imp);
 figure(5)
 plot(t,impf);
 xlabel('Temps (s)');
 title('Réponse impulsionelle');
 audiowrite('Peigne.wav',impf/max(impf),Fe)

 elseif choix==4,%Passe tout
 close all
 D = 20;
 g=0.5;
 num=zeros(1,D+1); 
 num(1) = -g;
 num(1, D+1) = 1;
 den=zeros(1,D+1);
 den(1, 1) = 1;
 den(1,D+1)=-g;

 z=exp(2*pi*1i*f*Te);
 h=(-g+(z.^-D))./(1-g*(z.^-D));
 impf = filter(num, den, Signal); %numérateur + dénominateur fonction de transfert
 cf=fft(impf,N)*Te; % fft réponse impulsionnelle
 c = abs(h); % Pour avoir un vecteur réel
 PC = angle(h)*(180/pi);

 % tracee du module et de l'argument du filtre
 figure(2)
 subplot(2, 1, 1);
 plot(f(2:N/2+1),c(2:N/2+1))
 title('Module fonction de transfert')
 xlabel('Fréquence / Hz');
 subplot(2, 1, 2);
 plot(f(2:N/2+1), PC(2:N/2+1)) % en degree
 xlabel('Fréquence / Hz');
 title('Phase fonction de transfert');

 % filtrage du signal fft
 Filtfft=fft(impf,N)*Te;
 signalfft=fft(Signal,N)*Te;
 % tracée du signal filtré
 figure(3)
 subplot(2, 1, 1);
 plot(t,Signal);
 xlabel('temps / s');
 title('Signal');
 subplot(2, 1, 2);
 plot(t, impf);
 xlabel('temps / s');
 title('Signal filtré ');
 % module et phase en fft
 figure(4)
 subplot(4, 1, 1);
 semilogy(f(2:N/2+1), abs(signalfft(2:N/2+1)))
 xlabel('Fréquence / Hz');
 title('Module de la tf du signal ');
 subplot(4, 1, 2);
 plot(f(2:N/2+1), angle(signalfft(2:N/2+1))*(180/pi))
 xlabel('Fréquence / Hz');
 title('Phase de la tf du signal ');
 subplot(4, 1, 3);
 semilogy(f(2:N/2+1), abs(Filtfft(2:N/2+1)))
 xlabel('Fréquence / Hz');
 title('Module de la tf du signal filtré ');
 subplot(4, 1, 4);
 plot(f(2:N/2+1), angle(Filtfft(2:N/2+1))*(180/pi))
 xlabel('Fréquence / Hz');
 title('Phase de la tf du signal filtré ');

 imp=zeros(1,N);
 imp(1)=1;
 impf = filter(num, den, imp);
 figure(5)
 plot(t,impf);
 xlabel('Temps (s)');
 title('Réponse impulsionelle');
 audiowrite('passe tout.wav',impf/max(impf),Fe)

 elseif choix==5,%reverberation
 close all

 D = 500;
 num=zeros(1,D+1);
 num(1) = 1;
 num(1, D+1) = -1;
 den = (1);

 sig1 = filter(num, den, Signal);

 D = 500;
 num=zeros(1,D+1);
 num(1) = 1;
 num(1, D+1) = -1;
 den = (1);
 sig2 = filter(num, den, Signal);

 D = 500;
 num=zeros(1,D+1);
 num(1) = 1;
 num(1, D+1) = -1;
 den = (1);
 sig3 = filter(num, den, Signal);

 D = 500;
 num=zeros(1,D+1);
 num(1) = 1;
 num(1, D+1) = -1;
 den = (1);
 sig4 = filter(num, den, Signal);

 D = 500;
 num=zeros(1,D+1);
 num(1) = 1;
 num(1, D+1) = -1;
 den = (1);
 sig5 = filter(num, den, Signal);

 D = 500;
 num=zeros(1,D+1);
 num(1) = 1;
 num(1, D+1) = -1;
 den = (1);
 sig6 = filter(num, den, Signal);

 somme_peigne= sig1+sig2+sig3+sig4+sig5+sig6;


 D = 500;
 g=0.5;
 num=zeros(1,D+1);
 num(1) = -g;
 num(1, D+1) = 1;
 den=zeros(1,D+1);
 den(1, 1) = 1;
 den(1,D+1)=-g;

 pass1 = filter(num, den, somme_peigne);

 D = 750;
 g=0.5;
 num=zeros(1,D+1);
 num(1) = -g;
 num(1, D+1) = 1;
 den=zeros(1,D+1);
 den(1, 1) = 1;
 den(1,D+1)=-g;

 pass2 = filter(num, den, pass1);




 D = 1000;
 g=0.5;
 num=zeros(1,D+1);
 num(1) = -g;
 num(1, D+1) = 1;
 den=zeros(1,D+1);
 den(1, 1) = 1;
 den(1,D+1)=-g;

 Sig = filter(num, den, pass2);
 fonc_fft=fft(Sig,N)*Te;

 figure(2)
 subplot(2, 1, 1);
 plot(f, abs(fonc_fft))
 title('Module fonction de transfert')
 xlabel('Fréquence / Hz');
 subplot(2, 1, 2);
 plot(f, angle(fonc_fft)*(180/pi)) % en degree
 xlabel('Fréquence / Hz');
 title('Phase fonction de transfert');
 % filtrage du signal fft

 Filtfft=fft(Sig,N)*Te;
 signalfft=fft(Signal,N)*Te;
 xlabel('Fréquence / Hz');
 title('Phase fonction de transfert');
 % tracée du signal filtré
 figure(3)
 subplot(2, 1, 1);
 plot(t,Signal);
 xlabel('temps / s');
 title('Signal');
 subplot(2, 1, 2);
 plot(t, Sig);
 xlabel('temps / s');
 title('Signal filtré ');
 % module et phase en fft
 figure(4)
 subplot(4, 1, 1);
 plot(f, abs(signalfft))
 xlabel('Fréquence / Hz');
 title('Module de la tf du signal ');
 subplot(4, 1, 2);
 plot(f, angle(signalfft)*(180/pi))
 xlabel('Fréquence / Hz');
 title('Phase de la tf du signal ');
 subplot(4, 1, 3);
 plot(f, abs(Filtfft))
 xlabel('Fréquence / Hz');
 title('Module de la tf du signal filtré ');
 subplot(4, 1, 4);
 plot(f, angle(Filtfft)*(180/pi))
 xlabel('Fréquence / Hz');
 title('Phase de la tf du signal filtré ');
 audiowrite('reverberation.wav',Sig/max(Sig),Fe)

 elseif choix==6, %synthese dans le domanie fréquentiel
 close all
 audiowrite('synthese.wav',Sig/max(Sig),Fe)
 elseif choix==7,%Butterworth
 close all
 %D = 32;
 % num=zeros(1,D+1);
 num(1, -2 + 1)*Fe ;
 %num(1, D+1) = -1;
 den = [1 -1];
 a = filter(num, den, imp);
 fonc_fft=fft(a,N)*Te;
 % tracee du module et de l'argument du filtre
 figure(2)
 subplot(2, 1, 1);
 plot(f, abs(fonc_fft))
 title('Module fonction de transfert')
 xlabel('Fréquence / Hz');
 subplot(2, 1, 2);
 plot(f, angle(fonc_fft)*(180/pi)) % en degree
 xlabel('Fréquence / Hz');
 title('Phase fonction de transfert');
 % filtrage du signal fft
 Sig = filter(num, den, Signal);
 Filtfft=fft(Sig,N)*Te;
 signalfft=fft(Signal,N)*Te;
 xlabel('Fréquence / Hz');
 title('Phase fonction de transfert');
 % tracée du signal filtré
 figure(3)
 subplot(2, 1, 1);
 plot(t,Signal);
 xlabel('temps / s');
 title('Signal');
 subplot(2, 1, 2);
 plot(t, Sig);
 xlabel('temps / s');
 title('Signal filtré ');
 % module et phase en fft
 figure(4)
 subplot(4, 1, 1);
 plot(f, abs(signalfft))
 xlabel('Fréquence / Hz');
 title('Module de la tf du signal ');
 subplot(4, 1, 2);
 plot(f, angle(signalfft)*(180/pi))
 xlabel('Fréquence / Hz');
 title('Phase de la tf du signal ');
 subplot(4, 1, 3);
 plot(f, abs(Filtfft))
 xlabel('Fréquence / Hz');
 title('Module de la tf du signal filtré ');
 subplot(4, 1, 4);
 plot(f, angle(Filtfft)*(180/pi))
 xlabel('Fréquence / Hz');
 title('Phase de la tf du signal filtré ');

 audiowrite('Butterworth.wav',Sig/max(Sig),Fe)
 elseif choix==8,
 sound(Signal/max(Signal),Fe);
 elseif choix==9,
 sound(Sig/max(Sig),Fe);
 else,%Quitter
 close all;
 break;
 end
end