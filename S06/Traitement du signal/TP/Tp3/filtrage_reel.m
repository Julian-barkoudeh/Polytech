%routine de filtrage utilisée dans la fin de l'exo 2 du TP3
%xdm, envoyé en argument est le signal démodulé 
function xdmf = filtrage_reel(xdm,Te,N,Fc);

% Te = input('Temps d''échantillonnage des signaux (Te)= ');
% N = input('Nombre de points de la fen^etre temporelle (N)= ');
% Fc = input('Fréquence de coupure du filtre souhaitée= ');

K=2/Te;
% K2=K^2; Fc2=Fc^2;dpFc=2*pi*Fc; dpFc2=dpFc^2;  % Butterworth PB ordre 2
% num=dpFc2*[1 2 1];  
% den=[K2+dpFc*sqrt(2)*K+dpFc2,-2*K2+2*dpFc2,K2-dpFc*sqrt(2)*K+dpFc2];
K2=K^2; Fc2=Fc^2;dpFc=2*pi*Fc; dpFc2=dpFc^2;K3=K^3;dpFc3=dpFc^3;
num=dpFc3*[1 3 3 1];  % Butterworth PB ordre 3
den(1)=K3+2*dpFc*K2+2*dpFc2*K+dpFc3;
den(2)=-3*K3-2*dpFc*K2+2*dpFc2*K+3*dpFc3;
den(3)=3*K3-2*dpFc*K2-2*dpFc2*K+3*dpFc3;
den(4)=-K3+2*dpFc*K2-2*dpFc2*K+dpFc3;
xdmf = filter(num,den,xdm) ;             %où x1dm est le signal x1 démodulé)
