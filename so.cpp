
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

//#include "parameter.h"
#include "define.h"
void AdPlot::so()
{


    int   i,j,Rget,satisfy,counter,R_negative,Max;
    int   postive,Q_point,R_point;
    double slope_threshold,slope_maxi,slope_initial_maxi,first_maxi,slope;
    int   R_found_a[700];

    double RRI_total;

    //void *ecg_data= malloc( sizeof(float) * 108000);
/*
    int sample_rate = 255;
    int cal_time=300;
    int cal_point=sample_rate*cal_time;
*/

    //THRESHOLD_PARAM = 8;
    //FILTER_PARAMETER = 16;

    i=0;
    Rget=0;
    satisfy=0;
    j=0;
    Rget=0;
    counter = 0;
    R_negative=0;
    Max=0;
    postive=0;


    for(i=0;i<700;i++){
        R_found_a[i]=0;
        RRI[i]=0;
    }





   //slope_initial_maxi=-2*ecg_data[1]-ecg_data[2]+ecg_data[4]+2*ecg_data[5];
    slope_initial_maxi=-2*ecg_data[0]-ecg_data[1]+ecg_data[3]+2*ecg_data[4];
   // printf("ecg_data[0] = %f   %f\n" ,ecg_data[0],ecg_data[1]);
   //  printf("ecg_data[112] = %f   ecg_data[113] = %f\n" ,ecg_data[112],ecg_data[113]);
    //算出前360筆資料的slope_initial_maxi
    for (i=0;i<sample_rate;i++){
        if (i>=2){
            slope=-2*ecg_data[i-2]-ecg_data[i-1]+ecg_data[i+1]+2*ecg_data[i+2];

            if (slope > slope_initial_maxi){
                slope_initial_maxi = slope;
            }
        }
    }

    slope_maxi=slope_initial_maxi;
    //printf("slope_maxi = %f\n",slope_maxi);

    for(i=2;i<cal_point-2;i++){
        if (Rget==0){
            if (satisfy<2){
                //slope=-2*ecg_data[i-2]-ecg_data[i-1]+ecg_data[i+1]+2*ecg_data[i+2];
                slope=(ecg_data[i+1]-ecg_data[i-1])+2*(ecg_data[i+2]-ecg_data[i-2]);

                //slope_threshold=(THRESHOLD_PARAM/16)*slope_maxi;
                slope_threshold=0.5*slope_maxi;

                if (slope>slope_threshold){
                    postive=1;
                    satisfy=satisfy+1;
                }
                else
                    satisfy=0;


                if (satisfy==2){
                    //printf("slope %d %f %f\n",i,slope,slope_threshold);
                    Q_point=i-1;
                     // printf("Total Q_point= %d\n",Q_point);
                    Max=1;
                }

                if (postive==0){
                   if (slope*slope>slope_threshold*slope_threshold)
                       satisfy=satisfy+1;
                   else
                        satisfy=0;

                   if (satisfy==2){
                       Q_point=i-1;
                       //printf("Total Q_point= %d\n",Q_point);
                       Max=0;
                   }
                }
            }
            else{
                if (Max==1) {
                    if ((ecg_data[i+1])<(ecg_data[i])){
                        R_point=i;

                        R_found_a[j]=R_point;
                        j=j+1;
                        //printf("i=%d Total R_found number %d\n",j,R_point);


                        satisfy=0;

                        Rget=1;
                        postive=1;

                        first_maxi=ecg_data[R_point]-ecg_data[Q_point];

                        slope_maxi=((first_maxi-slope_maxi)*0.0625)+slope_maxi;

                        //slope_maxi=(first_maxi*0.0625)+(slope_maxi*0.9375);
                        //printf(" %d slope_maxi= %f\n",i,slope_maxi);
                    }
                }
                else{
                    if (ecg_data[i+1]>ecg_data[i]){
                        R_point=i;

                        R_found_a[j]=R_point;
                        j=j+1;

                        R_negative=R_negative+1;

                        satisfy=0;

                        Rget=1;
                        postive=1;
                    }
                }
            }
        }
        else{
            if (counter ==100){
                Rget = 0;
                counter = 0;
            }
            else
                counter = counter + 1;

        }
    }
    j=j-1;

    RRI_total=j;
    printf("Total R-Peak number %f\n",RRI_total);

/*   for(i=0;i<j;i++){
   int temprr=R_found_a[i];
      printf("i=%d Total R_found number %d\n",i,temprr);
  }*/

/*
    for(i=1;i<j;i++){

        RRI[i-1]=(R_found_a[i]-R_found_a[i-1]);
        RRI[i-1]=RRI[i-1]*0.004;
        //RRI[i-1]=RRI[i-1]/sample_rate;

       //printf("RRI %f\n",RRI[i-1]);
    }
*/

    int org_RRI_sum=0;
    int org_count=0;


    first_R_found=(R_found_a[0]*1000/255)*0.001;
    //printf("R_found_a[0]= %f\n",R_found_a[0]);
    for(i=1;i<j;i++){
        RRI[i-1]=(R_found_a[i]-R_found_a[i-1]);
       // printf("i=%d RRI= %f\n",i-1,RRI[i-1]);
        if (RRI[i-1]<500){
            org_RRI_sum=org_RRI_sum+RRI[i-1];
            org_count=org_count+1;
        }
    }
    org_RRImean = (org_RRI_sum*100/org_count)*0.01;

  //printf("org_RRImean %f\n",org_RRImean);



}

