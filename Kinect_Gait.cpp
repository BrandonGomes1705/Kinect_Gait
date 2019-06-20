#include "stdafx.h" 
#include <iostream> 
#include <iomanip> 
#include <Windows.h> 
#include <NuiApi.h> 
#include "gait.h" 
#include <fstream> 
 
void shift(float arr[20][3], int a) //shift values in buffer
{  
 for (int i = 0; i < a; i++)  
 {   
  arr[i + 1][0] = arr[i][0];   
  arr[i + 1][1] = arr[i][1];   
  arr[i + 1][2] = arr[i][2];  
 } 
} 
 
 
int stat(float ar[20][3],float x, float y,float z) //check if foot is stationary
{  
 if ((x >= ar[19][0] - 0.05 && x <= ar[19][0] + 0.05) && (y >= ar[19][1] - 0.05 && y <= ar[19][1] + 0.05) && (z >= ar[19][2] - 0.05 && z <= ar[19][2] + 0.05))  
 {     return 1;  }  
 else   return 2; 
} 

int main() 
{    
 if (NuiGetSensorCount(&numSensors) < 0 || numSensors < 1)  
 {  
  std::cout << "Error 1: No sensor found" << std::endl;   return 0;  
 }  
 
 if (NuiCreateSensorByIndex(0, &sensor) < 0)  
 {   
  std::cout << "Error 2:Failed to connect to sensor" << std::endl;   return 0;  
 }  
 
 sensor->NuiInitialize(NUI_INITIALIZE_FLAG_USES_SKELETON);  //initialise sensor
 sensor->NuiSkeletonTrackingEnable(   NULL,   0  );  
 NUI_SKELETON_FRAME ourframe = { 0 };  int test[2] = { 0 };  
 std::ofstream myfile;  myfile.open("data.txt"); 
 
 
 while (1)  { 
 
  if (sensor->NuiSkeletonGetNextFrame(0.1, &ourframe) == S_OK)   
  {    
   sensor->NuiTransformSmooth(&ourframe, NULL); 
       for (int i = 0; i < 7; i++)   
       {     
        if (ourframe.SkeletonData[i].eTrackingState == NUI_SKELETON_TRACKED)     
        { 
         xr = ourframe.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_FOOT_RIGHT].x;  //get coordinates of feet      
         yr = ourframe.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_FOOT_RIGHT].y;        
         zr = ourframe.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_FOOT_RIGHT].z; 
 
         xr = (float)((int)(xr * 100)) / 100;        
         yr = (float)((int)(yr * 100)) / 100;        
         zr = (float)((int)(zr * 100)) / 100; 
 
         xl = ourframe.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_FOOT_LEFT].x;        
         yl = ourframe.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_FOOT_LEFT].y;       
         zl = ourframe.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_FOOT_LEFT].z; 
 
         xl = (float)((int)(xl * 100)) / 100;        
         yl = (float)((int)(yl * 100)) / 100;        
         zl = (float)((int)(zl * 100)) / 100; 
        }
         
         if (foot == 1)        
         { 
          if (stat(rightf, xr, yr, zr) == 1)   //check if right foot stationary      
          {         
           if (!((xr >= rightfp[1][0] - 0.1 && xr <= rightfp[1][0] + 0.1) && (yr >= rightfp[1][1] - 0.1 && yr <= rightfp[1][1] + 0.1) && (zr >= rightfp[1][2] - 0.1 && zr <= rightfp[1][2] + 0.1)) && count > 10)          
           {           
            long int beforer;           
            rightfp[0][0] = xr;           
            rightfp[0][1] = yr;           
            rightfp[0][2] = zr;           
            if (countr == 1) 
            {            
             long int afterr =  GetTickCount();            
             x = rightfp[0][0] - rightfp[1][0]; 
             y = rightfp[0][1] - rightfp[1][1];            
             z = rightfp[0][2] - rightfp[1][2];            
             dist = x*x + y*y + z*z;    //calculate distance travelled by foot       
             dist = sqrt(dist);            
             std::cout << "Right stride: " << dist << std::endl;            
             myfile << dist << ",";           
             x = leftfp[0][0] - rightfp[0][0];           
             y = leftfp[0][1] - rightfp[0][1];            
             z = leftfp[0][2] - rightfp[0][2];            
             dist = x*x + y*y + z*z;  //calculate distance between left and right feet          
             dist = sqrt(dist);            
             std::cout << "Right step: " << dist << std::endl;           
             myfile << dist << ",";            
             foot = 2;            
             myfile << afterr - beforer << ",";           
            }          
            rightfp[1][0] = rightfp[0][0];           
            rightfp[1][1] = rightfp[0][1];           
            rightfp[1][2] = rightfp[0][2];           
            countr = 1;           
            count = 0;             
            beforer = GetTickCount();          
           } 
 
        }         
          else 
          {          
           count++;         
          }       
         }        
        if (foot == 2)        
        {         
         if (stat(leftf, xl, yl, zl) == 1)  //check if left foot stationary       
         {         
          if (!((xl >= leftfp[1][0] - 0.1 && xl <= leftfp[1][0] + 0.1) && (yl >= leftfp[1][1] - 0.1 && yl <= leftfp[1][1] + 0.1) && (zl >= leftfp[1][2] - 0.1 && zl <= leftfp[1][2] + 0.1)) && counts > 10)          
          {           
           long int beforel; 
           leftfp[0][0] = xl;           
           leftfp[0][1] = yl;           
           leftfp[0][2] = zl;           
           if (countl == 1) 
           {            
            long int afterl = GetTickCount();            
            x = leftfp[0][0] - leftfp[1][0];            
            y = leftfp[0][1] - leftfp[1][1];            
            z = leftfp[0][2] - leftfp[1][2];            
            dist = x*x + y*y + z*z;            
            dist = sqrt(dist);            
            std::cout << "Left stride: " << dist << std::endl;            
            myfile << dist << ",";            
            x = leftfp[0][0] - rightfp[0][0];            
            y = leftfp[0][1] - rightfp[0][1];            
            z = leftfp[0][2] - rightfp[0][2];            
            dist = x*x + y*y + z*z;            
            dist = sqrt(dist);            
            std::cout << "Left step: " << dist << std::endl;            
            myfile << dist << ",";            
            myfile << afterl - beforel << '\n';            
            foot = 1;                       
           }           
           leftfp[1][0] = leftfp[0][0];           
           leftfp[1][1] = leftfp[0][1];           
           leftfp[1][2] = leftfp[0][2];           
           countl = 1;          
           counts = 0;           
           beforel = GetTickCount();          
          } 
 
        }         
         else 
         {          
          counts++;         
         }        
        }                

        for (int j = 0; j < 20; j++)        
        {        
         leftf[j + 1][0] = leftf[j][0];         
         leftf[j + 1][1] = leftf[j][1];         
         leftf[j + 1][2] = leftf[j][2];        
        } 
 
        shift(rightf,20);         
 
        rightf[0][0] = xr;        
        rightf[0][1] = yr;        
        rightf[0][2] = zr;       
        leftf[0][0] = xl;        
        leftf[0][1] = yl;        
        leftf[0][2] = zl;                  
       }         
  }   
 }   
 
}  
NuiShutdown();  //Shutdown sensor
myfile.close();  
return 0; 
 
}
