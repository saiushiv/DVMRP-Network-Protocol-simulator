#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>

// ---------  PROGRAM STARTS HERE --------

int main(int argc , char **argv)
{

  //sleep(20);

 //------- VARIABLES INITIALIZED ------------//

  int L[10],myRID=0,i,j,a,c,k=0,loop = 0,B=0,r=0,l=0;

  //int LID ,RID,d0,d1,d2,d3,d4,d5,d6,d7,d8,d9; 

  char *R0[24];

// R1[8],R2[8],R3[8],R4[8],R5[8],R6[8],R7[8],R8[8],R9[8];

  //char RTD[10][3];
  char RT[10][3];
  int M[10][3]; 

  static const long max_len = 126 + 1;  // define the max length of the line to read
  char buff[max_len + 1];               // define the buffer and allocate the length


  //LANID=0,dist=10,NxID=0;

  FILE *fd1 = NULL;
  FILE *fd2 = NULL;
  char dtm[150];
  FILE *fd3 = NULL;
 
  FILE *fd;  
  
  char *token = NULL;

  char dv[130],temp[20];
    
  char ROUTX[20];
  char LANX[20];

 //------------------------------------------//   

 //-------------CHECKING FOR NUMBER OF ARGUMENTS PASSED TO THE PROGRAM-------------------//

  if(argc > 10)
  {
   printf("Invalid Number of Arguments\n");
  }

     else
     {
                       myRID = atoi(argv[1]);
                       printf ("My Router-ID is : %d",myRID);

                     

      }
        
                      printf("Router is starting with following arguments:\n");

                        for(i=0 ; i<10 ; i++)
                            {
                                RT[i][0]=i;
                                RT[i][1]=10;
                                RT[i][2]=myRID; 
  
                             }

  //---------------OPENING THE ROUT FILES OF ROUTER--------------------------------------------//       
       
               sprintf(ROUTX,"ROUT%d.txt",myRID);

               if((fd1 = fopen(ROUTX,"a+")) == NULL)
                      {
                     printf("Error opening file %s\n",ROUTX);
                    exit(1);
                      }
               
              

 //----------------------------WRITING DV MESSAGES IN ROUT FILES-------------------//
                        
                       
            //             fputs("\t",fd1);  

               
                         for (c=2; c < argc; c++)
                         {
                           
                           L[l]=atoi(argv[c]);
                          
                           RT[L[l]][1] = 0 ;
                           RT[L[l]][2] = myRID;
                           
                           printf("LAN-ID is %d\n",L[l]);

                           sprintf(LANX,"LAN%d.txt",L[l]);
                           printf("%s\n",LANX);  
                                        
                           if((fd = fopen(LANX,"a+")) == NULL)
                                 {
                                     printf("Error opening file %s",LANX);
                                      continue;
                                  }
                                            
                    //            fputs("\n",fd); 
                    //            fputs("Welcome to LAN",fd);
                                fclose(fd);
                           


                           sprintf(dv,"DV %d %d",L[l],myRID); 
                           l++;

                            for(i=0 ; i<10 ; i++)
                            {
                                M[i][0]=i;
                                M[i][1]=10;
                                M[i][2]=i; 
                                
                                if(l==i)  
                                 {
                                 M[i][1]=0;
                                 M[i][2]=myRID;
                                 } 

                              sprintf(temp," %d router%d",M[i][1],M[i][2]); 
                              strcat(dv,temp);    
                            
                       
                            }       
   
                                   fputs("\n",fd1); 
                                   fputs(dv,fd1);
                              
                                                                    
                        }
                         
             //           fputs("\t",fd1); 

             //           printf("\nclosing ROUT\n");

                        fclose(fd1);

   //------------READING LAN FILES--------------------------------------------------//

     startcontrol:
                    printf(" in router %d\n",myRID);
                    if(l != 0)
                       {
                          for(r=0; r < l ; r++) 
                           {
            //                 printf("value of r:%d\n",r);
                             sprintf(LANX,"LAN%d.txt",L[r]);
            //                 printf("listening to LANFILE : %s\n",LANX);  

                             if((fd = fopen(LANX,"r")) == NULL)
                              {
                                printf("Error opening file %s",LANX);
                                  break;
                               }
                        
                
       //..................... Reading particular LAN File..............................

              
                  fseek(fd, -max_len, SEEK_END);      

                  fread(buff, max_len-1, 1, fd);

                  fclose(fd);                                    // close the file
  
                 buff[max_len-1] = '\0';                         // close the string

                char *last_newline = strrchr(buff, '\n');       // find last occurrence of newline 
    
                char *last_line = last_newline - 1;               // jump to it


                char *word="DV";

                char *pch = strstr(buff,word);
   
     //           printf("in buff:%s\n",buff);
     //           printf("in last line:%s",last_line);   

                      if(pch)
                         {
                            
                            printf("Found %s\n", buff);    // captured: DV .....
        

                            strcpy(dtm, buff);

                          }


                            if (strlen(dtm) != 0)
                             {
                               printf("\n The contents of the line as tokens is \n");
 
                               token = strtok(dtm," "); 

                            
                               while (token != NULL) 
                               {
                                 R0[k] = token; 
                                   k++;
                                 token = strtok(NULL," ");
                               
                               }
                               
                           
     //                    for (k=0;k<23; ++k) 
     //                    printf("From last For Loop - %s\n", R0[k]);
   
                          }
//-----------FROM THE TOKENS TAKING THE VALUES AND UPDATING THE ROUTING TABLE-----------------//

          if (pch)
          {
          k=3;

          printf("%d",atoi(R0[2]));

         if (myRID != atoi(R0[2])) 
           {
                      
             for(i=0; i<10; i++) 
             {  
             
               if(RT[i][1] > (atoi(R0[k])))
                {
                
                 RT[i][1]=((atoi(R0[k])) + 1);
                 printf("%d",(R0[k+1][6] - '0'));
                 RT[i][2] = (R0[k+1][6] - '0');
                }
               
                k= k+2;
              
            }
           }


        
           printf("\n");
           printf("\n");
           printf("The new routing table is:\n");

              for(i=0; i<10; i++) 
             {  
               for(j=0; j<3; j++) 
                {
               printf("%d\t",RT[i][j]); 
                }
                printf("\n"); 
             }
            }               
         }                
      }

                           loop = 100;
                  
                           if (B < loop)
                            {
                  
                                B++;

                             }

                           for(; B < loop ; B++)
                           {
                              printf("Value of loop is:%d\n",loop);
                              printf("Value of time counter in router is:%d\n",B); 
                              sleep(1);
                              goto startcontrol;
                           }

           printf("i..m..router..shutting down...bye.....value of time counter in Router is : %d\n",B);
           return 0; 
  }



       
                
      


   
