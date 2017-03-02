//#include <stdio.h>
//#include <stdlib.h>
#include "define.h"
//#include "parameter.h"

void AdPlot::resample (){
	int i,j;
    //int fs=2;
    //int cal_time=300;

	float time_d,rri_d,rfound_d;
	float target=0.5;
    int resamplepoint=cal_time*fs;

	float F[resamplepoint];


    //point= strlen(new_R_found);
    for(i=0;i<resamplepoint;i++){
	
		yi[i]=0;
		F[i]=0;
		   
    }
    F[0]  = R_found[0];
    //F[0]  = first_R_found;
	yi[0] = RRI[0];
   //printf("%f", R_found[1]);
    i=1;

    //printf("====================== resample =============================\n");
   // printf("%d %.4f %.4f \n",0,yi[0],F[0]);
    for (j=1;j<600;j++){
       if (i<resample_mo-1){
            F[j] = F[0]+j*target;
            time_d = F[j]- R_found[i-1];//(X-X1)
            rri_d  = RRI[i] - RRI[i-1] ; //(Y2-Y1)
            rfound_d = R_found[i] - R_found[i-1] ; //(X2-X1)
            yi[j] = RRI[i-1]+ ((time_d *rri_d*10000)/rfound_d)*0.0001 ;//Y=Y1+ {(X-X1)*(Y2-Y1)}/(X2-X1)

           //printf("%d %.4f %.4f \n",j,yi[j],F[j]);

            if((F[j]+target) > R_found[i]){
                i=i+1;
            }
       }
    }

}


