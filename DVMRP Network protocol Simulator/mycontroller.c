#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>

// ---------  PROGRAM STARTS HERE --------

int main(int argc , char *argv[])
{

  //sleep(20);

 //------- VARIABLES INITIALIZED ------------//

  int H[10],L[10],i=1,j=1,k=0,hout=1,rout=1,lout=1,M=0,loop=0,index = 0;
  int h,r=0; 
  char *R0[24];
  char typeH[5] = "host";
  char typeR[7] = "router";
  char typel[4] = "lan";

  long size;
  long R[10];
 
   char *token = NULL;

  char dtm[130];

  static const long max_len = 115 + 1;  // define the max length of the line to read for Router
  char buff[max_len + 1] ;              // define the buffer and allocate the length

   static const long max_lenH = 10 + 1;  // define the max length of the line to read for Host
  char buffH[max_lenH + 1] ;              // define the buffer and allocate the length
  
  FILE *fd;    // For writing in LAN Files...
  FILE *fd1;  // Check this logic for LAN file :use "**fd1" if u want to use separate file  descriptor for different files.
  FILE *fd2;  // This for HOST and router
 
  char LANX[20];
  char HOUTX[20];
  char ROUTX[20];
  

 //------------------------------------------//   

 //-------------CHECKING FOR NUMBER OF ARGUMENTS PASSED TO THE PROGRAM-------------------//

  if(argc > 33)
  {
   printf("Invalid Number of Arguments\n");
  }

  else
  {
     
     printf("Controller is starting with following arguments:\n");     

     k=argc;
     
     k=k-1; 
     
              
       if ((strcasecmp(typeH,argv[i])) == 0)          //strcasecmp to ignore the case of input
           
             {
             k=k-1;
              
             for (i=2; j == strlen(argv[i]);i++)
                       {
                          
                          H[hout]=atoi(argv[i]);
                          printf("Host-ID is %d\n",H[hout]);
                          hout = hout + 1; 
                          
                          k = k-1; 

                          if ( k==0 )
                            {
                              
                             break;

                             }                             
                       }
               }
             
                         
                       if((strcasecmp(typeR,argv[i])) == 0)
                         {
                          
                          k=k-1;

                          for (i= i+1 ; j == strlen(argv[i]);i++)
                             {
                               R[rout]=atoi(argv[i]);  
                               printf("Router-ID is %ld\n",R[rout]); 

                               rout = rout + 1 ;
                              
                               
                               k = k-1; 

                               
                               if ( k==0 )
                               {
                                  
                                 break;

                                }            
                             }
                          }
                    
                               if((strcasecmp(typel,argv[i])) == 0)
                                 {
                                     
                                     k=k-1;
                                      
                                     for (i= i+1 ; j == strlen(argv[i]) ; i++)
                                        {
                                          L[lout]=atoi(argv[i]); 
                                          printf("LAN-ID is %d\n",L[lout]); 
                                          
                                          sprintf(LANX,"LAN%d.txt",L[lout]);
                                          printf("%s\n",LANX);  
                                        
                                         if((fd = fopen(LANX,"a+")) == NULL)
                                            {
                                             printf("Error opening file %s",LANX);
                                             continue;
                                             }
                                            
                                  //          fputs("Welcome to LAN",fd);
                                   //         fputs("\n",fd); 
                                          
                                              fclose(fd);
               
                                        lout = lout + 1; 

                                        k = k-1; 

                                         if ( k==0 )
                                          {
                                            
                                            break;

                                          }            
                                         }
                                  }
            
           }



     //******************************************************************************************************       
     // From here starts the logic of reading HOUT and ROUT files...........
     //******************************************************************************************************
            
        for(h=1; h < hout ; h++) 
              {
                sprintf(HOUTX,"HOUT%d.txt",H[h]);
                printf("%s\n",HOUTX);  

            if((fd1 = fopen(HOUTX,"a+")) == NULL)    //One time write for Router and Host files. To prevent run time errors
                     {
                       printf("Error opening file %s",HOUTX);
                       break;
                     }

           //         fputs("\nWelcome to HOUT",fd1);
          //        fputs("\n",fd1); 
                    fclose(fd1);   
              }
 
 
         for(r=1; r < rout ; r++) 
              {
                
                sprintf(ROUTX,"ROUT%ld.txt",R[r]);
                printf("%s\n",ROUTX);  
                if((fd2 = fopen(ROUTX,"a+")) == NULL)
                    {
                      printf("Error opening file %s",ROUTX);
                      continue;
                    }
                     
           //       fputs("\nWelcome to ROUT",fd2);
          //      fputs("\n",fd2); 
                  fclose(fd2);
             }


        startcontrol:    /////READING FROM HOST FILES AND WRITING LAN FILES....................
          
          
           if(hout != 0)
            {
            for(h=1; h < hout ; h++) 
              {
                sprintf(HOUTX,"HOUT%d.txt",H[h]);
                printf("%s\n",HOUTX);  

               if((fd1 = fopen(HOUTX,"r")) == NULL)
                     {
                       printf("Error opening file %s",HOUTX);
                       break;
                     }

     //Reading particular Host File..............................

            
                 size = ftell(fd1);
        //         printf("the size of the file is :%ld",size);
                 
                 fseek(fd1, -max_lenH, SEEK_END);      

                 fread(buffH, max_lenH-1, 1, fd1);
           
               
                 fclose(fd1);                                    // close the file

                 buffH[max_lenH-1] = '\0';                         // close the string

                 char *last_newline = strrchr(buff, '\n');       // find last occurrence of newline 
    
                 char *last_line = last_newline + 1;               // jump to it
 


                           strcpy(dtm, buffH);

                  //         printf("current buff is:%s",buffH); 
                         
                          
                       //      printf("\nThe contents of the line in HOUT is \n");

                       //     if(strlen(dtm) != 0)
                      //       {
                             
                       //        token = strtok(dtm," "); 
 
                        //       while (token != NULL) 
                        //       {
                        //        R0[index] = token; 
                         //         index++;
                       //         token = strtok(NULL," ");
                            
                       //        }
                             
                                            
      //*************** Writing the Data from HOST into LAN files ..............*******************
                     
                //            if ((atoi(R0[1])) > 0)
                  //         {
                              
 
                              sprintf(LANX,"LAN%d.txt",L[h]);

                             if((fd  = fopen(LANX,"a+")) == NULL)
                              {
                                printf("Error opening file %s",LANX);
                                break;
                              }
                      
                        fputs("\n",fd);
                        fputs(buffH,fd);
                        fclose(fd);
                       }
                     }
           
      //     }

     //    }

//******************************** SECONDLY handling all the ROUTERS.....******************************************
     
            if(rout != 0)                      /////READING FROM ROUTER FILES AND WRITING LAN FILES....................
            {
   
           for(r=1; r < rout ; r++) 
              {
               
                sprintf(ROUTX,"ROUT%ld.txt",R[r]);
                printf("%s\n",ROUTX);  

                if((fd2 = fopen(ROUTX,"r")) == NULL)
                    {
                      printf("Error opening file %s",ROUTX);
                      break;
                    }
             
           
                fseek(fd2, -max_len, SEEK_END);      

                fread(buff, max_len-1, 1, fd2);

                fclose(fd2);                                    // close the file

                buff[max_len-1] = '\0';                         // close the string

                char *last_newline = strrchr(buff, '\n');       // find last occurrence of newline 
    
                char *last_line = last_newline + 1;               // jump to it

               
        //           printf("last line is :%s\n",last_line);
                   
        //        printf("last line in buff is :%s\n",buff);    

 //*************** Writing the Data from ROUTERS into LAN Files...........******************
                      
                  
                           
   //                         strcpy(dtm, buff);

                          
    //                       printf("\n The contents of the line %s \n",dtm);
 
     //                        if(strlen(dtm) != 0 ) 
      //                       {
      //                      token = strtok(dtm," "); 
 
       //                     while (token != NULL) 
       //                        {
        //                         R0[index] = token; 
        //                         printf("From last For Loop - %s\n", R0[index]);
        //                         index++; 
        //                         token = strtok(NULL," ");
                                 
        //                      }        
                
           
  //                if ( (atoi(R0[1])) > 0)
   //                   {
                          sprintf(LANX,"LAN%d.txt",L[r]);
                         if((fd  = fopen(LANX,"a+")) == NULL)
                         {
                           printf("Error opening file %s",LANX);
                           break;
                          }
            
                   
                           fputs("\n",fd);
                           fputs(buff,fd);
                           fclose(fd);
  
   //                     } 

               //      }
                  }
              }
          
   
                           loop = 100;
                  
                           if (M < loop)
                            {
                  
                                M++;

                             }

                           for(; M < loop ; M++)
                           {
                              printf("Value of loop is:%d\n",loop);
                              printf("Value of time counter in controller is:%d\n",M); 
                              sleep(1);
                              goto startcontrol;
                           }

            printf("in controller");   
           printf("i..m....shutting down...bye.....value of time counter in controller is : %d\n",M);
           return 0; 

 }



