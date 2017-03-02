 //#include <math.h>
#include "define.h"

void* FFT(double* x,double* y,int n,int sign)
{
int i,j,k,l,m,n1,n2;
double c,c1,e,s,s1,t,tr,ti;
//Calculate i = log2N
for(j = 1,i = 1; i<16; i++)
{
     m = i;
     j = 2*j;
     if(j == n)
         break;
}
//�p�⽺�ιϪ���J 
n1 = n - 1;
for(j=0,i=0; i<n1; i++)
{
    if(i<j)           
    {
         tr = x[j];
         ti = y[j];
         x[j] = x[i];
         y[j] = y[i]; 
         x[i] = tr;
         y[i] = ti;                 
    }
    k = n/2;
    while(k<(j+1))
    {
        j = j - k;
        k = k/2;              
    }
    j = j + k;
}
//�p��C�@�Ū���X�Al���Y�@�šAi���P�@�Ū����P�s�A�ϥΦP�@���s(�Y��B��) 
n1 = 1;
for(l=1; l<=m; l++)
{
    n1 = 2*n1;
    n2 = n1/2;
    e = 3.1415926/n2;
    c = 1.0;
    s = 0.0;
    c1 = cos(e);
    s1 = sign*sin(e);
    for(j=0; j<n2; j++)
    {
        for(i=j; i<n; i+=n1)         
        {
            k = i + n2;
            tr = c*x[k] - s*y[k];
            ti = c*y[k] + s*x[k];
            x[k] = x[i] - tr;
            y[k] = y[i] - ti;
            x[i] = x[i] + tr;
            y[i] = y[i] + ti;        
        }
        t = c;
        c = c*c1 - s*s1;
        s = t*s1 + s*c1;
    }
}
}



void AdPlot:: PSD (){
    int i,k;
    float Fs;
	float space;
    float pt=300;
    int L;
//	int nfft=512;
    double x[nfft], y[nfft];//pow[nfft],f[nfft/2+1];

	for(i=0;i<nfft;i++)
	{
	x[i]=yi[i];
	y[i] = 0;
	}
	FFT(x,y,nfft,1);
    L=haN;
	for(i=0; i<nfft/2; i++)
	{
    pow[i] =(x[i]*x[i]+y[i]*y[i])/(L*L);
    //printf("%d %f %f %f\n",i,x[i],y[i],pow);
	}

    //printf("%d \n",haN);
    //L=haN;
    Fs=L/pt;
    //printf("%f %d %f\n",Fs,L,pt);
    space=100000/((nfft/2)+1);//linspace(0,1,NFFT/2+1)*10000

    for(k=1;k<(nfft/2)+1;k++)
	{
    f[k]=Fs*space*k*0.05;
    //printf("%d %f %f\n",k,f[k],space);
	}
	
	//======================== cal LF/HF =====================================     
	int f_VLF_get=0,f_LF_get=0,f_HF_get=0;
	int f_VLF=0,f_LF=0,f_HF=0;
	
    for (i=0;i<((nfft/2)+1);i++)
	{
    if (f[i]>=400 && f_VLF_get==0){
	    f_VLF=i;
	    f_VLF_get=1;
	   }
	
    if (f[i]>=1500 && f_LF_get==0){
	    f_LF=i;
	    f_LF_get=1;
	  }
	
    if (f[i]>=4000 && f_HF_get==0){
	    f_HF=i;
	    f_HF_get=1;
	}
	}
	
	float VLF=0,LF=0,HF=0,TP=0;
    for (i=1;i<f_VLF;i++){
	VLF=pow[i]+VLF;     
	}
    for (i=f_VLF;i<f_LF;i++){
	LF=pow[i]+LF;     
	}
    for (i=f_LF;i<f_HF;i++){
	HF=pow[i]+HF;
	}
	TP=VLF+LF+HF;

    //printf("f_VLF=%d f_LF=%d f_HF=%d\n",f_VLF,f_LF,f_HF);
    printf("LF=%f HF=%f\n",LF,HF);
    //printf("LF/HF=%f\n",LF/HF);
    ratio=LF/HF;
    ratio_reg[xxx]=ratio;
    printf("LF/HF=%f\n",ratio);
    LF_pre=4400*LF/(LF+HF);
}


