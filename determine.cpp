
#include "define.h"
void AdPlot::determine(){
     int Avg,avg_co,D_grade_ratio,grade_ratio,level;
     double ratiosum,ratio_avg,diff;

     int con1_co,uptime_con1, count_1 ;
     double COMAVG,LF_HF_avg_1,tempAVG;



     if (xxx > 75){
         if (xxx == uptime_con1){
             count_1 = xxx-75;
             ratiosum = 0;
             for (con1_co=0;con1_co<75;con1_co++){
                 ratiosum = ratiosum+ratio_reg[count_1];
                 count_1 = count_1 +1;
             }

             LF_HF_avg_1 = ratiosum/75;

             if (uptime_con1 == 76)
                COMAVG = LF_HF_avg_1;
             else
                COMAVG = (tempAVG+LF_HF_avg_1)/2;

             tempAVG= LF_HF_avg_1;
             uptime_con1 =75+uptime_con1;

             if (COMAVG>5)          COMAVG=5;
             else if (COMAVG<2)     COMAVG=2;
         }
         else
             COMAVG=COMAVG;

         if(COMAVG<= ratio_reg[xxx])
             grade_ratio = 6;
         else if( COMAVG*0.8  <= ratio_reg[xxx])
             grade_ratio = 5;
         else if( COMAVG*0.65 <= ratio_reg[xxx])
             grade_ratio = 4;
         else if( COMAVG*0.5  <= ratio_reg[xxx])
             grade_ratio = 3;
         else if( COMAVG*0.35 <= ratio_reg[xxx])
             grade_ratio = 2;
         else
             grade_ratio = 1;
     }

     else
         grade_ratio = 6;


     //printf("Condition_1  = %d\n",grade_ratio);



     if (xxx>75){
         Avg = xxx-75;
         ratiosum = 0;
         for (avg_co=0;avg_co<30;avg_co++){
             Avg = Avg+1;
             ratiosum = ratiosum+ratio_reg[Avg];
         }
         //printf("ratiosum  = %f\n",ratiosum);
         ratio_avg = (ratiosum/30);
         diff = ratio_avg - ratio_reg[xxx];

         if(1<= diff)
             D_grade_ratio = 1;
         else if(0.5<= diff)
             D_grade_ratio = 2;
         else if(0<= diff)
             D_grade_ratio = 3;
         else if(-0.5<= diff)
             D_grade_ratio = 4;
         else
             D_grade_ratio = 5;
     }
     else
         D_grade_ratio = 3;

     //printf("Condition_2  = %d\n",D_grade_ratio);





     switch (grade_ratio){
     case 6:
         level=5;
         break;

     case 5:
         if      (D_grade_ratio==1)  level=4;
         else if (D_grade_ratio==2)  level=5;
         else if (D_grade_ratio==3)  level=5;
         else if (D_grade_ratio==4)  level=5;
         else                        level=5;
         break;

     case 4:
         if      (D_grade_ratio==1)  level=3;
         else if (D_grade_ratio==2)  level=3;
         else if (D_grade_ratio==3)  level=4;
         else if (D_grade_ratio==4)  level=4;
         else                        level=5;
         break;

     case 3:
         if      (D_grade_ratio==1)  level=2;
         else if (D_grade_ratio==2)  level=2;
         else if (D_grade_ratio==3)  level=3;
         else if (D_grade_ratio==4)  level=3;
         else                        level=4;
          break;

     case 2:
         if      (D_grade_ratio==1)  level=1;
         else if (D_grade_ratio==2)  level=1;
         else if (D_grade_ratio==3)  level=2;
         else if (D_grade_ratio==4)  level=2;
         else                        level=3;
         break;

     case 1:
         if      (D_grade_ratio==1)  level=1;
         else if (D_grade_ratio==2)  level=1;
         else if (D_grade_ratio==3)  level=1;
         else if (D_grade_ratio==4)  level=2;
         else                        level=2;
         break;
     }

     //level_reg[xxx]=level;
     if (z==25){
         if      (G>=17)   top=0;
         else if (R>=17)   top=2;
         else              top=1;

         G=0;
         B=0;
         R=0;
         z=1;

         if (level==5)               G=G+1;
         else if (level==4)          B=B+1;
         else if (level==3)          B=B+1;
         else                        R=R+1;
     }
     else{
         top=top ;
         z=z+1;

         if (level==5)              G=G+1;
         else if (level==4)         B=B+1;
         else if (level==3)         B=B+1;
         else                       R=R+1;
         //printf("G = %d\n",G);
         //printf("Y = %d\n",B);
         //printf("R = %d\n",R);

     }


}







