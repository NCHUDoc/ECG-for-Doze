
#include "define.h"
// #include <math.h>
 //#include "parameter.h"
 
 void AdPlot::RRI_mean (){
 //	int fs=2;
//	int cal_time=300;
	int resamplepoint=cal_time*fs;
    float ang,hann;
    int i=0;
    float RRIsum=0;
    float RRImean;
    int k;
    for(k=0;k<resamplepoint;k++)
    {
      if(yi[k]>0){

      RRIsum = yi[k]+RRIsum;
      i=i+1;
       //printf("%d %.4f  %.4f\n",i,yi[k],RRIsum);

      }
    }


    haN=i;

   RRImean=(RRIsum*10000/i)*0.0001;
   HR=60/RRImean;
   //printf("%f \n ", RRImean);
   //printf("%d \n ", HR);
   for(k=0;k<i;k++)
   {
   yi[k] = (yi[k]- RRImean)*1000;
   //printf("%d  %f \n",k,yi[k]);

   }
   
//==================== hannig window ================================

   for(k=0;k<i;k++)
   {  // double yyi=yi[k];
       ang = cos(((6.28*k)*1000/haN)*0.001);
       hann=0.5-0.5*ang;//0.5*(1-cos(2*))
       yi[k] = yi[k]*hann; 
       //printf("%f\n",yi[k]);
      // printf("%d %.4f %.4f %.4f %.4f \n",k,ang,yyi,hann,yi[k]);
       }  

   if(i<512){
       for(k=i;k<513;k++){
           yi[k]=0;
       }
   }






}
