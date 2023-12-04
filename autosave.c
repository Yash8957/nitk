#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

// 1. Accident  2.Warning System 3.Accident-Details  4.Emergency Contacts 5.Insurance 6.Vehicle Details 7.Exit 8.Reset

//Emergency holds data of emergency contacts.
struct emergency
{
        int id;
        char name[30];
        long int ph;
        int n;
}e1,e2,e3; // 3 Struct variables hold details for 3 contacts.

//Vec-Details holds har coded details about the car.
struct vec_details
{

	char chassis[20],insurer[25],engine[10],plate_no[13],mfg[20],model[20];
	char fowner[20],lowner[20],addrs[100];
	float insured_price;
	int day,month,year;
}v;

//Pre-Accident/Warning Detail Structure
struct warning
{

	int speed,battery;
	char sb[1],oil[1],brake[1];
}w;

//Accident Structure
struct accident
{
	int accpin; //pincode of accident place
	int damage;
	int h,m,s;
	int day1,month1,year1;
}a;

// Hospital Structure
struct hospital
{
	int pin; //for 0-49 objects mangalore(575001-575025, 574101-574125)
	//for 50-74 udupi (576101-576125)
	//for 75-99 hassan (573201-573225)
	long int hph; //formula for randomizing phone number 8197197022 +(10000000*i) i belongs to [0,99]
	char hn[30];
	char district[30];
}h[100];

// Emergency Accident Structure (holds Accident Details for manipulation/display purpose )
struct accem
{
	int aeid;
        long int aeph;	
	char aename[30];
}ae1,ae2,ae3;


//f1-Activation File | f2-Vehicle Details | f3_1,f3_2,f3_3....-Emergency |                                      
//f5-Warning File | f6-Accident? | f7-Accident Details | f8-Hospital List | f9-Holds Master Password
FILE *f1,*f2,*f3_1,*f3_2,*f3_3,*f4,*f5,*f6,*f7,*f8,*f9;

//Declaration of activate() and logo func/n
int activate();
int logo();

void main()
{

	//Activation Function is Called.
	activate();

	//Selection of Appropriate Choice.
	int choice;
	char menu[1];
	//We use a do-while function, so that the body is executed atleast once
	do                    
	{
again:
	
	 printf("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^ MENU ^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
	printf("\n1. Accident Details \n2. Accident Safety System \n3. Warning Safety System \n4. Emergency Contact Details \n5. Insurance Details & Claim \n6. Vehicle Details (Non-Changeable) \n7. Exit System \n8. Reset System \nEnter Your Choice: ");
	scanf("%d",&choice);
	 printf("--------------------------------------------------------------\n");
	switch(choice)
	{
		//Enter Activation Details
		case 1:{
			       char ans[1],anst,anst1;
			       int i;
			       f6=fopen("Accident.txt","r");
			       if(f6==NULL || feof(f6))
			       {
				       //We are storing Y/N in Accident file, so that it can be used for future reference
				       printf("\nHas the accident take place? [Y/n]: ");
				       scanf("%s",ans);
				       anst=ans[0];
				       f6=fopen("Accident.txt","w");
				       fputc(toupper(anst),f6);
				       fclose(f6);
			       }
			       f6=fopen("Accident.txt","r");
			       anst1=fgetc(f6);
			      
			       //Enter Details of Accident
                               f7=fopen("Acc Details.txt","r");
			       
			       //We are basically checking of the Acc Detail file is empty and the accident has taken place
			       if((f7==NULL || feof(f7)) && anst1=='Y')  
			       {
				       f7=fopen("Acc Details.txt","w");
				       printf("\nEnter Accident Details!");
				       printf("\nEnter the date of accident [DD-MM-YYYY]: ");
				       scanf("%2d-%2d-%4d",&a.day1,&a.month1,&a.year1);
time:
				       printf("Enter the time of accident [HH:MM:SS]: ");
				       scanf("%2d:%2d:%2d",&a.h,&a.m,&a.s);
				       //we check for any invalid time
				       if(a.h<0 || a.h>23 || a.m<0 || a.m>59 || a.s<0 || a.s>59)
				       {
					       printf("\nEntered time is invalid, input it again.");
					       printf("\n");
					       goto time;
				       }
pinline:
				       printf("Enter the pincode of accident: ");
				       scanf("%d",&a.accpin);
				       //We check whether the pincode exists or not in hospital database (as of now we have 100 pincodes in our hospital database)
				       f8=fopen("Hospital.txt","r");
				       int pt=0;
				       {
				       for(i=0;i<100;i++)
				       {
					       fread(&h[i],sizeof(struct hospital),1,f8);
					       if(h[i].pin==a.accpin)
					       {
						      pt++;
						       break;				  
					       }					       
				       }
				       if(pt==0) //When pt=0, it basically means we were unable to find the pincode in our database
				       {
					       printf("\nEnter pincode is invalid, input it again.");
					       printf("\n");
					       goto pinline;
				       }
				       }
				       fclose(f8);
				       printf("Enter accident damage %%: ");
				       scanf("%d",&a.damage);
				       fwrite(&a,sizeof(struct accident),1,f7);
			       }
			       else  
			       {
				       char anst2;
				       f6=fopen("Accident.txt","r");
				       anst2=fgetc(f6);
				       printf("\n--------------------------------------------------------------");
				       if(anst2=='Y')
					       printf("\nAccident details have already been entered.");
				       else
					       printf("\nAccident details can't be entered since no accident has taken place.");
			       }
	       		       printf("\n--------------------------------------------------------------\n");
	       
			       break;
          	       }
		case 2:{
			       //Accident Safety System
			       //if f3_1,f3_2,,f3_3,f5,f6,f7,f8 is missing/corrupted it will exit, because it's necessary for executing Acc Safety System.
			       f3_1=fopen("Emergency1.txt","r");
			       f3_2=fopen("Emergency2.txt","r");
			       f3_3=fopen("Emergency3.txt","r");
			       if((f3_1==NULL || feof(f3_1)) && (f3_2==NULL || feof(f3_2)) && (f3_3==NULL || feof(f3_3))) //This is executed only if the file is empty or not yet created.
			       {
                                       printf("\nEmergency File is missing/corrupted; Before proceeding ahead encode it.\n");
                                       exit(0);

                               }       
			       f5=fopen("Warning.txt","r");
                               if(f5==NULL || feof(f5))
                               {
                                       printf("\nWarning File is missing/corrupted; Before proceeding ahead encode it.\n");
                                       exit(2);
                               }
			       f6=fopen("Accident.txt","r");
                               if(f6==NULL || feof(f6))
                               {
                                       printf("\nAccident File is missing/corrupted; Before proceeding ahead encode it.\n");
                                       exit(3);
                               }
			       f8=fopen("Hospital.txt","r");
                               if(f8==NULL || feof(f8))
                               {
                                       printf("\nHospital Database File is missing/corrupted; Before proceeding ahead encode it.\n");
                                       exit(4);
                               }
			       
			       int i;
			       char ansc; //Holds value 'Y' / 'N'
			       int accbat; //Stores Battery %
			       int d,m,y,h1,m1,s1; //Stores date and time
			       int aepin; //Stores Accident Pin
			       char aedis[20],aehn[30]; //Hospital District + Name
			       long int aeph; //Hospital Phone Number

			       //Opening of all the required Files
			       f3_1=fopen("Emergency1.txt","r");
                               f3_2=fopen("Emergency2.txt","r");
                               f3_3=fopen("Emergency3.txt","r");
			       f5=fopen("Warning.txt","r");
			       f6=fopen("Accident.txt","r");
			       f7=fopen("Acc Details.txt","r");
			       f8=fopen("Hospital.txt","r");
			       
			       ansc=fgetc(f6);

			       //First we check if the accident took place or not.			     
			       if(ansc=='Y')
			       {
				      //Accident Safety System has been activated
			       }
			       else
			       {
				       printf("\nAccident Safety System can't be activated, since no accident has taken place.\n");
				       exit(0);
			       }
			       
			       //Storing Emergency Data in 'struct accem'

			       //Checking if Emergency Contact-1 is Avaliable	       			      
			       fread(&e1,sizeof(struct emergency),1,f3_1);
			       ae1.aeid=e1.id;
			       ae1.aeph=e1.ph;
			       strcpy(ae1.aename,e1.name);

			       //Checking if Emergency Contact-2 is Avaliable
	                       fread(&e2,sizeof(struct emergency),1,f3_2);
			       ae2.aeid=e2.id;
			       ae2.aeph=e2.ph;
			       strcpy(ae2.aename,e2.name);
                               
			       //Checking if Emergency Contact-3 is Avaliable                               
                               fread(&e3,sizeof(struct emergency),1,f3_3);
			       ae3.aeid=e3.id;
			       ae3.aeph=e3.ph;
			       strcpy(ae3.aename,e3.name);                               

			       //We get battery %
			       fread(&w,sizeof(struct warning),1,f5);
			       accbat=w.battery;

			       //Get Accident Details
			       fread(&a,sizeof(struct accident),1,f7);
			       d=a.day1;
			       m=a.month1;
			       y=a.year1;
			       h1=a.h;
			       m1=a.m;
			       s1=a.s;
			       aepin=a.accpin;

			      //Getting Hospital Data
                               for(i=0;i<100;i++)
			       {
				       fread(&h[i],sizeof(struct hospital),1,f8);
				       if(aepin==h[i].pin)
				       {
					       strcpy(aedis,h[i].district);
					       strcpy(aehn,h[i].hn);
					       aeph=h[i].hph;
					       break;
				       }
			       }

			      //Output Required Data
			      printf("\n--------------------------------------------------------------");
			       printf("\n\t\t   ACCIDENT SAFETY SYSTEM\n");
			       printf("\nDate: %d-%d-%d  Time: %d:%d:%d",d,m,y,h1,m1,s1);
			       printf("\nAccident  Pincode: %d   District: %s",aepin,aedis);
			       printf("\n\nABS (!) has been deployed.");
			       printf("\nPolice & Fire Dept. Helplines have been sent with relevant location/timeline details.");
			       printf("\nImmediate Respone Message (IRM) has seen to the %s Hospital at %ld",aehn,aeph);
			       if(accbat>5)
			       {
				       printf("\n\nAccident Details have been sent to the listed Emergency Contacts.");
				       printf("\nEmergency Notification has been sent to %s at %ld.",ae1.aename,ae1.aeph);
				       printf("\nEmergency Notification has been sent to %s at %ld.",ae2.aename,ae2.aeph);
				       printf("\nEmergency Notification has been sent to %s at %ld.",ae3.aename,ae3.aeph);

			       }
			       printf("\n--------------------------------------------------------------\n");
			       fclose(f3_1);
			       fclose(f3_2);
			       fclose(f3_3);
			       fclose(f5);
			       fclose(f6);
			       fclose(f7);
			       fclose(f8);
			       break;

		       }
                case 3:{
			       //Warning Message
                          f5=fopen("Warning.txt","r");
			       if(f5==NULL || feof(f5))
			       {
				       //This is executed if Warning File is missing or corrupted.
				       printf("\nWarning File is missing/corrupted; Before proceeding ahead encode it.\n\n");
				       f5=fopen("Warning.txt","w");
                                       printf("Average speed of vehicle (in Kmph): ");
				       scanf("%d",&w.speed);
                                       printf("Is the seat belt tied? [Y/n]: ");
				       scanf("%s",w.sb);				       
				       printf("Enter system battery %%: ");
				       scanf("%d",&w.battery);
				       printf("Is there any oil leak? [Y/n]: ");
				       scanf("%s",w.oil);
                                       printf("Is the braking system functioning? [Y/n]: ");
				       scanf("%s",w.brake);
				       fwrite(&w,sizeof(struct warning),1,f5);
				       fclose(f5);
				       
			       }
			       else //Warning Message Board
			       {
				       char oilw,sbw,brw;
				       int spdw;
				       int l=0;
				       f5=fopen("Warning.txt","r");
				       fread(&w,sizeof(struct warning),1,f5);
				       oilw=toupper(w.oil[0]);
				       sbw=toupper(w.sb[0]);
				       brw=toupper(w.brake[0]);
				       spdw=w.speed;
				       fclose(f5);
				       printf("\n--------------------------------------------------------------");
				       printf("\n\t\t   WARNING MESSAGES \n");
				       if(spdw>80)
				       {
					       printf("\n%d. Over-Speeding. Slow Down (!).",++l);
				       }
				       if(sbw=='N')
				       {
					       printf("\n%d. Wear Your Seat Belt (//)",++l);

				       }
				       if(brw=='N')
                                       {
                                               printf("\n%d. Braking System has Malfunctioned (#).",++l);

                                       }
				       if(oilw=='Y')					     
                                       {
                                               printf("\n%d. System Oil Leak (O).",++l);
                                       }
				       if(l==0)
				       {
					       printf("\nNo Warning Messages.");
				       }
				       printf("\n--------------------------------------------------------------\n");
			       }
			       break; 
                       }

		case 4:{
			       //Emergency Contact Database
			        int option;
retry:
retry1:
retry2:
retry3:
retry4:
retry5:
				printf("\nPress  1.Create   2.Update  3.View   4.Exit - Emergency Contacts Database: ");
			       	scanf("%d",&option);
				switch(option)
			 	{
			 		//Create Case
				case 1:{
		 			      
					       f3_1=fopen("Emergency1.txt","r");
					       f3_2=fopen("Emergency2.txt","r");
					       f3_3=fopen("Emergency3.txt","r");		
                                		//This is executed only if the file is empty or not yet created. 			       
					       if((f3_1==NULL || feof(f3_1)) && (f3_2==NULL || feof(f3_2)) && (f3_3==NULL || feof(f3_3))) 
					       {	       
						       f3_1=fopen("Emergency1.txt","w");
       						       f3_2=fopen("Emergency2.txt","w");
       						       f3_3=fopen("Emergency3.txt","w");						       
	      					       printf("\nEnter complete details of 3 emergency contacts: ");             
		     				       
						       //Enter Details of All Contacts                                                
                                                       printf("\nDetails of Contact-1");	
						       printf("\nEnter Contact ID: ");
       						       scanf("%d",&e1.id);
       						       printf("Enter Contact's Name: ");
       						       scanf("%5s",e1.name);
       						       printf("Enter Phone Number (10-Digits): ");
       						       scanf("%10ld",&e1.ph);
       						       fwrite(&e1,sizeof(struct emergency),1,f3_1); 
       						       fclose(f3_1);

						       printf("\nDetails of Contact-2");	 					                                                                 
						       printf("\nEnter Contact ID: ");
       						       scanf("%d",&e2.id);
       						       printf("Enter Contact's Name: ");
       						       scanf("%5s",e2.name);     
						       printf("Enter Phone Number (10-Digits): ");
       						       scanf("%10ld",&e2.ph);
       						       fwrite(&e2,sizeof(struct emergency),1,f3_2); 
       						       fclose(f3_2);

       						       printf("\nDetails of Contact-3");	 					                                                                   
       						       printf("\nEnter Contact ID: ");
       						       scanf("%d",&e3.id);
						       printf("Enter Contact's Name: ");
       						       scanf("%5s",e3.name);
       						       printf("Enter Phone Number (10-Digits): ");
       						       scanf("%10ld",&e3.ph);
       						       fwrite(&e3,sizeof(struct emergency),1,f3_3); 
       						       fclose(f3_3);					
					       }
					       else 
					       {						       
						       printf("\nEmergency Contact Database has already been created.");
					       }
					       goto retry2;
				       }
	                  //Update Case			       
				case 2:{
                                              
					      int tid; //stores contact id to search; 
                                              int uid1,uid2,uid3; //uid stores id of every contact, to compare with 'tid'
					      f3_1=fopen("Emergency1.txt","r");
					      f3_2=fopen("Emergency2.txt","r");
					      f3_3=fopen("Emergency3.txt","r");
					      if((f3_1==NULL || feof(f3_1)) && (f3_2==NULL || feof(f3_2)) && (f3_3==NULL || feof(f3_3)))
					      {
						      printf("\nEmergency Contact Database is empty, Update it first.\n");
						      goto retry5;
					      }

					      printf("\nEnter Contact ID that's to be updated: ");
					      scanf("%d",&tid);
					      f3_1=fopen("Emergency1.txt","r");
					      fread(&e1,sizeof(struct emergency),1,f3_1);
					      uid1=e1.id;
					      f3_2=fopen("Emergency2.txt","r");	   
       					      fread(&e2,sizeof(struct emergency),1,f3_2);
					      uid2=e2.id;
					      f3_3=fopen("Emergency3.txt","r");
					      fread(&e3,sizeof(struct emergency),1,f3_3);
					      uid3=e3.id;       
                                      
					      //Compare tid with all the uids, if matched enter new details
					      if(tid==uid1)
					      { 
  						      f3_1=fopen("Emergency1.txt","w");
  						      printf("\nEnter Updated ID: ");
  						      scanf("%d",&e1.id);
  						      printf("Enter Updated Name: ");
  						      scanf("%s",e1.name);
						      printf("Enter Update Phone Number: ");
						      scanf("%ld",&e1.ph);
  						      fwrite(&e1,sizeof(struct emergency),1,f3_1);
  						      fclose(f3_1);
						      printf("\n--------------------------------------------------------------");
                          			      printf("\nEmergency Contact Database has been successfully update.");
						      printf("\n--------------------------------------------------------------");

					      }
					      else if(tid==uid2)
					      { 
  						      f3_2=fopen("Emergency2.txt","w");
  						      printf("\nEnter Updated ID: ");
  						      scanf("%d",&e2.id);
  						      printf("Enter Updated Name: ");
  						      scanf("%s",e2.name);
  						      printf("Enter Update Phone Number: ");
	  					      scanf("%ld",&e2.ph);	 
	  					      fwrite(&e2,sizeof(struct emergency),1,f3_2);
  						      fclose(f3_2);
						      printf("\n--------------------------------------------------------------");
						      printf("\nEmergency Contact Database has been successfully updated.");
						      printf("\n--------------------------------------------------------------\n");
					      }
					      else if(tid==uid3)
					      { 
  						      f3_3=fopen("Emergency3.txt","w");
  						      printf("\nEnter Updated ID: ");
  						      scanf("%d",&e3.id);
  						      printf("Enter Updated Name: ");
  						      scanf("%s",e3.name);
  						      printf("Enter Update Phone Number: ");
  						      scanf("%ld",&e3.ph);
  						      fwrite(&e3,sizeof(struct emergency),1,f3_3);
  						      fclose(f3_3);
						      printf("\n--------------------------------------------------------------");
						      printf("\nEmergency Contact Database has been successfully updated.");	
					      	      printf("\n--------------------------------------------------------------\n");
					      
					      }                               
  					      else
  					      {
  						      printf("\n--------------------------------------------------------------");
						      printf("\nNo such ID exists in the Contact Database.");
						      printf("\n--------------------------------------------------------------\n");
					      }
  					      goto retry2;
				       }
                                 //View Case
				 case 3:{
						f3_1=fopen("Emergency1.txt","r");
						f3_2=fopen("Emergency2.txt","r");
						f3_3=fopen("Emergency3.txt","r");
		 				if((f3_1==NULL || feof(f3_1)) && (f3_2==NULL || feof(f3_2)) && (f3_3==NULL || feof(f3_3)))
		 				{
		 					printf("\nEmergency Contact Database is empty, Update it first.\n");
		 					goto retry4;
		 				}
						printf("\n--------------------------------------------------------------");
		 				printf("\n\t\t  Emergency Contact Database\n");
						printf("\n    Sl\t   ID\t  Disp_Name\tPhone Number ");		 				
		 					
						fread(&e1,sizeof(struct emergency),1,f3_1);
						printf("\n");
						printf("    1.\t   %d\t  %s\t\t%ld",e1.id,e1.name,e1.ph);
						fclose(f3_1);
					
						fread(&e2,sizeof(struct emergency),1,f3_2);
						printf("\n");
						printf("    2.\t   %d\t  %s\t\t%ld",e2.id,e2.name,e2.ph);
						fclose(f3_2);

						fread(&e3,sizeof(struct emergency),1,f3_3);
						printf("\n");
						printf("    3.\t   %d\t  %s\t\t%ld",e3.id,e3.name,e3.ph);
						fclose(f3_3);
						printf("\n--------------------------------------------------------------\n");
						goto retry3;
		 			}
                                    //Exit Case
				    case 4:{
		    				   printf("\n--------------------------------------------------------------");
						   printf("\nYou have exited out of Emergency Contact Database.");
						   printf("\n--------------------------------------------------------------\n");
		    				   break;
		    			   }
		    		    default:{
		    				    printf("\nInvalid Choice. Try Again!!");
		    				    goto retry;
		    				    break;
		    			    }
				}
                          break;
		       }
                              //Insurance Claim
		case 5:{
		//Check whether required files exist or not.       
			       f2=fopen("Vehicle Details.txt","r");
		       	       if(f2==NULL || feof(f2))
		       	       { 
		       		       printf("\nVehicle Details file is missing/corrupted. Before proceeding ahead, encode it.\n");
		       		       exit(0);
		       	       }

		       	       f6=fopen("Accident.txt","r");
		       	       if(f6==NULL || feof(f6))
		       	       { 
		       		       printf("\nAccident file is missing/corrupted. Before proceeding ahead, encode it.\n");
		       		       exit(0);
		       	       }
		
			       char check; //Stores if accident has happened or not
			       check=getc(f6);
			       if(check=='N')
                               {
                                       printf("\n--------------------------------------------------------------");
                                       printf("\nInsurance can't be claimed since no accident has taken place.");
                                       printf("\n--------------------------------------------------------------\n");
                                       exit(0);
                               }

		      	       int td1,td2,d1,d2,m1,m2,y1,y2; // Stores date of purchase and accident
		       	       int depperc; //holds depriciation percentage
		       	       float insprice,net,gross,pricet; //insprice holds insured price (pricet - holds temporary value of original price)
		       	       float depval; //holds depreciated value of vehicle
		       	       int insdam; //stores damage %
		       	       float sgst,cgst; //holds gst tax 12% on net insurance
		       	       float depyear; //holds no of years between accident & purchase for managing depriciation.
		       	       char insname[30]; // holds name of insurer

		       	       f2=fopen("Vehicle Details.txt","r");
		       	       f7=fopen("Acc Details.txt","r");
		       	       fread(&a,sizeof(struct accident),1,f7);
		       	       fread(&v,sizeof(struct vec_details),1,f2);

		       	       strcpy(insname,v.insurer);
		       	       insdam=a.damage;
		       	       pricet=(float)v.insured_price;
		       	       insprice=pricet;
		       
			       d1=v.day;
		       	       td1=d1;
		       	       d2=a.day1;
		       	       td2=d2;
		       	       m1=v.month;
		       	       m2=a.month1;
		       	       y1=v.year;
		       	       y2=a.year1;

			       if(insdam==0)
			       {
      				       printf("\n--------------------------------------------------------------");
      				       printf("\nInsurance can't be claimed since no accidental damage has taken place.");
				       printf("\n--------------------------------------------------------------\n");
				       exit(0);
     			       }

		       	       fclose(f2);
			       fclose(f6);
		       	       fclose(f7);

                             //We Take 01/01/2000 as refernce to calc no of days between 'accident' & 'purchase' date. 
	                       d1=d1 + ((m1-1)*30) + ((y1-2000)*365);
		       	       d2=d2 + ((m2-1)*30) + ((y2-2000)*365);
		       	       d2=d2-d1;
		       	       depyear=(float)d2/365;
 
                          //We Calculate Depreciation % on the following data, 6months-5%, 0.5-1 year-15%, 1-2year-20%, 2-3year-30%, 
			  //3-4year-40%, 4-5year-50%, 5-7year-65%, 7-10-85%, >10 No insurance claim.
                               if(depyear<0.5)
		       	       {
		       		       insprice=insprice*0.95;
		       		       depperc=5;
		       	       }
		       	       else if(depyear>=0.5 && depyear<1.0)	
			       {
				       insprice=insprice*0.85;
				       depperc=15;
			       }
			       else if(depyear>=1.0 && depyear<2.0)
			       {
				       insprice=insprice*0.80;
				       depperc=20;
			       }
			       else if(depyear>=2.0 && depyear<3.0)
			       {
				       depperc=30;
				       insprice=insprice*0.70;
			       }
			       else if(depyear>=3.0 && depyear<4.0)
			       {
				       insprice=insprice*0.60;
				       depperc=40;
			       }
			       else if(depyear>4.0 && depyear<5.0)
			       {
				       depperc=50;
				       insprice=insprice*0.50;
			       }
		               else if(depyear>=5.0 && depyear<7.0)		   
			       {
				       depperc=65;
				       insprice=insprice*0.35;
			       }
			       else if(depyear>=7.0 && depyear<10.0)
			       {
				       depperc=85;
				       insprice=insprice*0.15;
			       }
			       else
			       {
				       printf("\nSince the car is more than 10 year(s) old, you can't claim insurance for it.");
				       exit(0);
			       }
                                      //insprice holds depricated value of car
				      //Damage % -Price|| (1-15)% damage=actual%  (15-35) damage%=(X-0.5)%  
				      //(35-50) damage%= (X-1.5)%   (50-65) damage%=(X-3)%   (65+)damage% =(X-4.5)%  X, is damage%
         
			       if(insdam>0 && insdam<15)
		      		       net=insprice*insdam;
		      	       else if(insdam>=15 && insdam<35)
				       net=insprice*(insdam-0.5);
			       else if(insdam>=35 && insdam<50)
				       net=insprice*(insdam-1.5);
			       else  if(insdam>=50 && insdam<65)
				       net=insprice*(insdam-3.0);
			       else
				       net=insprice*(insdam-4.5);

			       net=net/100.0;
		      	       cgst=net*0.06; //cgst is 6% of net
		      	       sgst=net*0.06; //sgst is 6% of net
		      	       gross=net-cgst-sgst;
			       
			       printf("\n--------------------------------------------------------------");
		      	       printf("\n\t\t    INSURANCE DETAILS");
			       printf("\n\nInsurer: %s Ltd.",insname);
		      	       printf("\nEx-Showroom Price: %0.2f Rs.",pricet);
		      	       printf("\nPurchase Date: %d-%d-%d  Insur. Claim Date: %d-%d-%d",td1,m1,y1,td2,m2,y2);
		      	       printf("\nDamage Perc: %d %%",insdam);
		      	       printf("\n\nDepriciation Perc: %d %%     Depriciated Price: %0.2f Rs.",depperc,insprice);
			       printf("\nNet Insurance Claim: %0.2f",net);
		      	       printf("\n\nDivision of Claim Amount:");
		      	       printf("\nGross: %0.2f Rs.   CGST[6%%]: %0.2f Rs.   SGST[6%%]: %0.2f Rs.",gross,cgst,sgst);
		      	       printf("\nInsurance data has been sent to the insurer, \npay will be processed after insurer's verification.");  
		      	       printf("\n--------------------------------------------------------------\n");
			       break;
		       }

		case 6:{
			       //Vehicle Details
			       f2=fopen("Vehicle Details.txt","r");
			       if(f2==NULL || feof(f2))
                       		       {
                                         //This is executed if Warning File is missing or corrupted.
				       printf("\nPlease enter vehicle details correctly. The information is hardcoded and can't be reset manually by the user.");
				       f2=fopen("Vehicle Details.txt","w");
				       printf("\n\nEnter Date of Purchase (DD-MM-YYYY): ");
                                       scanf("%2d-%2d-%4d",&v.day,&v.month,&v.year);
				       printf("Enter Owner's First Name: ");
				       scanf("%s",v.fowner);
				       printf("Enter Owner's Last Name: ");
                                       scanf("%s",v.lowner);
				       printf("Enter Registration Address:(Use '_' for SPACE): ");
				       scanf("%s",v.addrs);
				       printf("Enter Vehicle Brand-Model: ");
				       scanf("%s",v.model);
				       printf("Enter Chassis Number: ");
				       scanf("%s",v.chassis);
				       printf("Enter Engine Type: ");
				       scanf("%s",v.engine);
				       printf("Enter Registration Plate Number: ");
				       scanf("%13s",v.plate_no);
				       printf("Enter Insurer's Name: ");
				       scanf("%s",v.insurer);
				       printf("Enter Ex-Showroom Price: ");
				       scanf("%f",&v.insured_price);
				       fwrite(&v,sizeof(struct vec_details),1,f2);
				       fclose(f2);
			       }
			       else
			       {
				       //Display Vehicle Details
				       f2=fopen("Vehicle Details.txt","r");
				       fread(&v,sizeof(struct vec_details),1,f2);
  	                 	       printf("\n--------------------------------------------------------------");
                                       printf("\n\t\t      VEHICLE DETAILS");
				       printf("\n\nPurchase Date: %d-%d-%d",v.day,v.month,v.year);
				       printf("\n\nOwner's Name: %s %s",v.fowner,v.lowner);
				       printf("\nRegistration Address: %s",v.addrs);
				       printf("\n\nVehicle Brand-Model: %s",v.model);
				       printf("\n\nRegistered RTO Plate Number: %s",v.plate_no);
				       printf("\nChassis Number: %s \t  Engine Type: %s",v.chassis,v.engine);
				       printf("\n\nInsurer: %s Ltd. \t    Ex-Showroom Price: %.2f Rs.",v.insurer,v.insured_price);
                                       printf("\n--------------------------------------------------------------\n");
				       fclose(f2);
          		       }
			       fclose(f2);
			       break;
		       }

		case 7:{
			       //Display Exit Message
			       printf("\n--------------------------------------------------------------");
			       printf("\nYou have exited out of the system.");
			       printf("\n--------------------------------------------------------------\n");
			       exit(0);
			       break;
		       }
		       
		case 8:{
			       //Override All Files to NULL
		               char key[30],passcode[30];
			       char ans[2]; //Stores Y/N if we want to reset the system.
			       int len; //Stores length of master password to reduce abnormalities while comparing passwords
			       printf("\nAre you sure you want to reset the system [Y/n]: ");
			       scanf("%s",ans);
			       if(strcmp(ans,"y")==0 || strcmp(ans,"Y")==0)
			       {
				       f9=fopen("Password.txt","r");
				       while(fgets(key,30,f9)!=NULL)
					len=strlen(key);
				       key[len]='\0'; //There were some abnormalities while reading text from file, to avoid that this has been done.
				       printf("\nPlease Enter Master Passowrd (case-sensitive): "); 
      				       scanf("%s",passcode); 
				       if(strcmp(key,passcode)==0)
				       {
					       remove("Activation.txt");
					       remove("Password.txt");
					       remove("Emergency1.txt");
					       remove("Emergency2.txt");
					       remove("Emergency3.txt");
					       remove("Accident.txt");
					       remove("Acc Details.txt");
					       remove("Warning.txt");
					       printf("\n--------------------------------------------------------------");
					       printf("\nSystem has been successfully reset.");
					       printf("\n--------------------------------------------------------------\n");
			       		       exit(0);			       
				       }
				       else
				       {
 					       printf("\n--------------------------------------------------------------");
                                               printf("\nMaster Password is invalid, system reset has failed.");                                
                                               printf("\n--------------------------------------------------------------\n");
					       exit(0);
				       }
			       }

			       break;
		       }
		default:{
				printf("\nInvalid Choice. Try Again !!\n");
				goto again;
			}
	}
	printf("\nDo you want to visit the menu again? [Y/n]:");  // If we want to visit the menu again.
	scanf("%s",menu);
	}while(strcmp(menu,"Y")==0 || strcmp(menu,"y")==0); 



}
int activate()
{
	int i,ac,nc,sc;
	char ch='1';
	char actn_key,pwd[30];
	f1=fopen("Activation.txt","r");
	//It returns only if ch='\n'
       	if(f1==NULL)
	{
		logo();
		printf("\nIf you want to activate the safety system, press 'ENTER'. ");
                scanf("%1c",&actn_key);
                if(actn_key=='\n')
                {
                        f1=fopen("Activation.txt", "w");
                        fputc(ch,f1);
                        fclose(f1);
pass:
			ac=0; nc=0; sc=0; 
			// ac holds number of alpha char, nc holds  numerics, sc holds spl characters
			// We are entering the master password
			f9=fopen("Password.txt","w");
			printf("\nEnter a Master Password (Min: 8 Char, 1 Spl-Char, 1 Aplha-Num  Char): ");
			scanf("%s",pwd);
			if(strlen(pwd)<8) //Number of characters is less than 8
			{
				printf("\nPassword has less than 8 characters, Re-Enter: ");
				goto pass;
			}
			for(i=0;pwd[i]!='\0';i++)
			{				
				if((pwd[i]>='A' && pwd[i]<='Z') || (pwd[i]>='a' && pwd[i]<='z'))				
					ac++;
				else if(pwd[i]>='0' && pwd[i]<='9')
					nc++;
				else
					sc++;
			}
			
			if(ac==0)
			{
				printf("\nPassword has no Alpha characters, Re-Enter: ");
				goto pass;
			}
			if(nc==0)
                        {
                                printf("\nPassword has no Numeric characters, Re-Enter: ");
                                goto pass;
                        }
			if(sc==0)
                        {
                                printf("\nPassword has no Special characters, Re-Enter: ");
                                goto pass;
                        }
			fputs(pwd,f9);

			printf("\n--------------------------------------------------------------");
			printf("\nMaster Password has been successfully set.");
			printf("\n--------------------------------------------------------------\n");
			fclose(f9);
			return 0;
                }
		else 
			exit(0);
	}
}                 

// Logo of our safety system
int logo()
{
	printf("\t\t\t                                          @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	printf("\n\t\t\t                                          @                                                                               @");
	printf("\n\t\t\t                                          @                                                                               @");
	printf("\n\t\t\t                                          @                 **     **    ********    ********    **   ***                 @");
	printf("\n\t\t\t                                          @                 ***    **    ********    ********    **  **                   @");
	printf("\n\t\t\t                                          @                 ****   **       **          **       ** **                    @");
	printf("\n\t\t\t                                          @                 ** **  **       **          **       ****                     @");
	printf("\n\t\t\t                                          @                 **  ** **       **          **       ** **                    @");
	printf("\n\t\t\t                                          @                 **   ****       **          **       **  **                   @");
	printf("\n\t\t\t                                          @                 **    ***    ********       **       **   **                  @");
	printf("\n\t\t\t                                          @                 **     **    ********       **       **    **                 @");
	printf("\n\t\t\t                                          @                                                                               @");
	printf("\n\t\t\t                                          @                                                                               @");
	printf("\n\t\t\t                                          @           **      *   *  *****  *****    *****   **      *****  *****         @");
	printf("\n\t\t\t                                          @           * *     *   *    *    *   *    *       * *     *      *             @");
	printf("\n\t\t\t                                          @           ****    *   *    *    *   *    *****   ****    ****   *****         @");
	printf("\n\t\t\t                                          @           *   *   *   *    *    *   *        *   *   *   *      *             @");
	printf("\n\t\t\t                                          @           *    *  *****    *    *****    *****   *    *  *      *****         @");
	printf("\n\t\t\t                                          @           ===========================    =============================        @");
	printf("\n\t\t\t                                          @                                                                               @");
	printf("\n\t\t\t                                          @                                                                               @");
	printf("\n\t\t\t                                          @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");

printf("\n\n\n");
return 0;
}
