//#include <iostream>

#include "define.h"


void  AdPlot::remove(){
	int i,tr;
	int kk=1;
    int min_range;
    int max_range;
    float temp ;

    if (org_RRImean >= 170){
        max_range=256;
        min_range=153;
    }
    else if (153 <= org_RRImean && org_RRImean < 170){
        max_range=219;
        min_range=140;
    }
    else if (140 <= org_RRImean && org_RRImean < 153){
        max_range=192;
        min_range=128;
    }
    else if (128 <= org_RRImean && org_RRImean < 140){
        max_range=170;
        min_range=118;
    }
    else{
        max_range=256;
        min_range=153;
    }


    for(tr=0;tr<600;tr++){
        if(min_range < RRI[tr] && RRI[tr] < max_range){
            temp=(RRI[tr]*1000/255)*0.001;
            RRI[kk-1]= temp;
            kk=kk+1;
        }
    }
    printf("Remove Ectopic R-peak number%d\n",kk);

    for(i=kk+1;i<600;i++){
    RRI[i]=0;

    }

    /*for(tr=2;tr<500;tr++){
		
         if(0.2<RRI[tr] && RRI[tr]<1){
		 	
			   if(min_range<RRI[tr] && RRI[tr]<max_range){
			     RRI[kk]= RRI[tr];
                 yi[kk-1]=RRI[kk];
                 range =RRI[tr]*0.3;
			     min_range= RRI[tr]-range;
			     max_range= RRI[tr]+range;
			     kk=kk+1;
			 }
		}
    }*/
    resample_mo=kk;

/*
    for(i=0;i<500;i++){
        printf("i=%d RRI=%f\n",i,RRI[i]);
	}

*/
    R_found[0]=first_R_found;
    // printf("i=%d R_found=%f\n",i,R_found[0]);
    for(i=1;i<kk;i++){
        R_found[i]= R_found[i-1]+RRI[i-1];
        //printf("i=%d R_found=%f\n",i,R_found[i]);
    }
}

