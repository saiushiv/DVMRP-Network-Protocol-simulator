#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>


// ---------  PROGRAM STARTS HERE ------------//

  int main(int argc , char **argv)
  {

  //------- VARIABLES INITIALIZED ------------//

  int a,b,c,tos,period,i=1,k=0,trem=0,loop=0,count=10;
  char type[15];

  FILE *fd1 ;                           // File pointer
  FILE *fd2 ;
  FILE *fd  ; 

 // fd  = malloc(sizeof(FILE*) * 200);  
 // fd1 = malloc(sizeof(FILE*) * 200);
 // fd2 = malloc(sizeof(FILE*) * 200);
 
  char HOUT[20];
  char HIN[20];
  char LANX[10];
  char data[20];
  static const long max_len = 20 + 1;           // define the max length of the line to read
  char buff[max_len + 1];                       // define the buffer and allocate the length
  char *last_newline;
  char *last_line;
  char *word ; 
  char *pch ; 

 //------------------------------------------//   


 //-------------CHECKING FOR NUMBER OF ARGUMENTS PASSED TO THE PROGRAM-------------------//

  if(argc == 4)
  {
    switch(i)
       {
//----------------DEFINING THE MEANING OF EACH ARGUMENT---------------------------------//


  //--------------FIRST ARGUMENT IS THE HOST-ID------------------------------------------//
         case 1:
          a=atoi(argv[1]);  
          printf("Host-ID is %d\n",a);  
          i++;
  
  //--------------SECOND ARGUMENT IS THE LAN-ID------------------------------------------//
         case 2:
          b=atoi(argv[2]);
          printf("LAN-ID is %d\n",b); 
          
          sprintf(LANX,"LAN%d.txt",b);                  // LAN file to read

                 fd = fopen(LANX,"a+");

                    if(NULL == fd)
                      {
                     printf("fopen1() failed for LAN file!!!\n");
                     return 1;
                       }

                      else
                
                     {                                            
                       
                             
                       printf("LAN file opened successfully...");  // open file. 

                //         fputs("         ",fd);
                 //        fputs("\n",fd); 
                         fclose(fd);  
                      }
            i++;

 //--------------THIRD ARGUMENT IS THE "TYPE" OF HOST------------------------------------//
         case 3:
              strcpy(type,argv[3]);

                if ((strcmp(type,"receiver")) == 0)
                 { 

 //--------------IF THE HOST IS THE RECEIVER THEN PERFORM THESE FUNCTIONS--------------------//

               sprintf(HOUT,"HOUT%d.txt",a);
               sprintf(HIN,"HIN%d.txt",a); 

               printf("Host is a %s\n",type);

 //---------------OPENING THE HIN AND HOUT FILES OF RECEIVER--------------------------------------------//


        startrec:
             
               fd1 = fopen(HOUT,"a+");
               fd2 = fopen(HIN,"a+"); 
         
               if(NULL == fd1)
                {
                   printf("fopen1() Error!!!\n");
                   return 1;
                }

                else
                { 
                    printf("HOUT%d opened successfully through fopen()\n",a);
                  
                }
                if(NULL == fd2)
                {
                  printf("\n fopen2() Error!!!\n");
                  return 1;
                }

 //----------------WRITING DATA MESSAGE TO THE IN-FILE OF THE RECEIVER(i.e. INTO HIN)---------------

                 else
                 { 
                   printf("HIN%d opened successfully through fopen()\n",a);

       
                 sprintf(LANX,"LAN%d.txt",b);                  // LAN file to read

                 fd = fopen(LANX,"a+");

                    if(NULL == fd)
                      {
                     printf("fopen1() failed for LAN file!!!\n");
                     break;
                       }

                      else
                
                     {                                            
                       
                             
                       printf("LAN file opened successfully...");  // open file. 

                   //     buff[max_len + 1];

                        fseek(fd, -max_len, SEEK_END);   
 
// set pointer to the end of file minus the length you need Presumably there can be more than one new line caracter

                        fread(buff, max_len-1, 1, fd);

 // read the contents of the file starting from where fseek() positioned us from the end of the file.
                
                        buff[max_len-1] = '\0';                   // close the string

                        last_newline = strrchr(buff, '\n');      // find last occurrence of newline
    
                        last_line = last_newline+1;              // jump to it

                        word="data";

                        pch = strstr(buff,word);
                    
                     printf("\nin buffer : %s\n",buff);
                     printf("in last_line:%s\n",last_line);  
   
                       if(pch)
                         {
                             printf("captured: [%s]\n", buff);    // captured: DATA .....
                             fputs("\n",fd2);
                             fputs(last_line,fd2);
                             
                               
                          }
                
       
                       if (count == 10)
                         {
                         fputs("\n",fd1);
                         sprintf(data,"receiver %d",b);
                         fputs(data,fd1);
                         count = 0;
                         
                         }
                       
                       fclose(fd);                               // close the file
                       fclose(fd1);
                       fclose(fd2); 

                       count = count + 1; 
                   }
            
                           loop = 100;
                  
                           if (k < loop)
                            {
                  
                                k++;

                             }

                           for(; k < loop ; k++)
                           {
                              printf("Value of loop is:%d\n",loop);
                              printf("Value of timer in host %s is:%d\n",type,k); 
                              sleep(1);
                              goto startrec;
                
                           }
 
                      }
                            
              
             
              printf("Files Closed\n");     
              }
            i++;
           
   //     default  : printf( "Some problem in the input...Please check\n" );
   //                break;   

         }
   
   }

  else              ////////////From here starts the logic for sender////////////////
  {

     switch(i)
      {
  //----------------DEFINING THE MEANING OF EACH ARGUMENT---------------------------------//
          
  //--------------FIRST ARGUMENT IS THE HOST-ID------------------------------------------//
         case 1:
          a=atoi(argv[1]);  
          printf("Host-ID is %d\n",a);  
          i++;
  
  //--------------SECOND ARGUMENT IS THE LAN-ID------------------------------------------//
         case 2:
          b=atoi(argv[2]);
          printf("LAN-ID is %d\n",b); 
            i++;

 //--------------THIRD ARGUMENT IS THE "TYPE" OF HOST------------------------------------//
         case 3:
              strcpy(type,argv[3]);

               i++;
    
//--------------THIS ARGUMENT IS THE "TIME TO START"--------------------//
         case 4:
               tos = atoi(argv[4]);
                printf("Time to start is %d\n",tos);
                i++;

 //--------------THIS ARGUMENT IS THE "PERIOD"--------------------//
         case 5:
                 period = atoi(argv[5]);
                printf("period is %d\n",period);
                i++;
    
         }

        printf("ohh.....waiting till time to start as i am a sender\n"); 
        sleep(tos);


 //--------------IF THE HOST IS A "SENDER" THEN PERFORM THESE FUNCTIONS--------------------//

              printf("Host is a %s\n",type);

              sprintf(HOUT,"HOUT%d.txt",a);
   
   //--------------OPENING THE HOUT FILE OF THE SENDER - *****NO HIN FILE FOR SENDER****------//
   
     startover:
             
              fd1 = fopen(HOUT,"a+");

              if(NULL == fd1)
                {
                  printf("\n fopen1() Error!!!\n");
                  return 1;
                }
                else
                { 
               
                  printf("Hout%d opened successfully through fopen()\n",a);
                  sprintf(data,"data %d %d",b,b);
                  fputs("\n",fd1);
                  fputs(data,fd1);
                  fclose(fd1);
                  printf("Sender HOUT File Closed\n"); 

 //---------NOW COMES THE SENDER'S SLEEPING LOGIC---------------------------//

                    if (loop == 0)
                     {
                     trem = 100 - tos;
  
                     loop = trem / period;

                     }

               
                   if (k < loop)
                    {
                  
                      k++;

                     }

                   for(; k < loop ; k++)
                   {
                     printf("Value of loop is:%d\n",loop);
                     printf("Value of timer for host %s is:%d\n",type,k); 
                     sleep(period);
                     goto startover;
                
                   }


                }
                  
               
            }
 
            printf("in host type:%s\n",type);    
           printf("i..host and i..m shutting down...value of timer is : %d\n",k);
           return 0; 
   }




 
