#include<stdio.h>
#include <string.h>
#include <ctype.h>
#include "reservation.h"
#include <time.h>
#include <stdlib.h>
#include "FUNCNAME.h"
//split date entered 
int splitDate(char checkinDate[],date*destination ){
       //date into day month and year
       char tokenization[12];
       strcpy(tokenization,checkinDate);
                char *tok = strtok(tokenization,"-");
                
                if(tok == NULL){
                    printf("Error in pointer1");
                   
                } 
                int day = atoi(tok);
            
                tok = strtok(NULL,"-");
                
                if(tok == NULL){
                    printf("Error in pointer2");
                   
                }
                int month = atoi(tok);
                tok = strtok(NULL,"-");
                
                if(tok == NULL){
                    printf("Error in pointer3");
                    
                }
                int year = atoi(tok); 
                destination->day = day;
                destination->month = month;
                destination->year = year;
}
//search for room
int findRoom(Room* rooms,char NUM[],int count){
    int i;
    int roomnumber = atoi(NUM);
    for(i=0;i<count;i++){
        if(rooms[i].number ==roomnumber){
            //return index
            return i;
        }
        }
        return -1;

}
// 1 = yes 0 = no 2 = main 
int choosemenu(){
    char choice;
    scanf(" %c",choice);
    if(isupper(choice)){
        choice = tolower(choice);
    }
    if(choice == 'y'){
        printf("GREAT!");
        return 1;
    }
    if(choice == 'n'){
        
        return 0;
    }
    if (choice == 'm'){
        printf(" back to menu.\n");
        return 2;
    }
    if(choice == 'e'){
        printf("Exiting...\n");
        exit(1);
    }
}
//clear screen
void clearScreen() {
    
    //check if windows
#ifdef _WIN32
//clear in windows
    system("cls"); 
#else 
//clear in other
    system("clear"); 
#endif
}
//validate id
int validateID(const char *id) {
    //check if id is 14 digita
    if (strlen(id) != 14) {
        return 0; 
    }
    for (int i = 0; i < 14; i++) {
        if (!isdigit(id[i])) {
            return 0; 
        }
    }

    return 1; 
}
//count number of words
int countwords(const char *c){
    int  i = 0, w = 0; 
    
    while(*c){
        if(isspace(*c)){
            w = 0;
        }
        else{
            if(w == 0){
                i++;
                w = 1;
            }
            }
         c++;
    }
    return i;
}
//check if name is valide
int validateName (const char *name){
    //only 2 words
    if (countwords(name) !=2){
        return 0;
    }
    int i = 0 ;
    while(name[i]!='\0'){
        // no numbers or characters
        if(!isalpha(name[i]) && name[i]!=' '){
            return 0;
        }
        i++;
    }
    return 1;
}
//chack if email is correct
int validateEmail(const char *email){
    //if email exists
    if(email == NULL){
        return 0;
    }
   
    //pointer to @
    char* at = strchr(email,'@');
    //pointer to . 
    char* dot = strchr(email,'.');
    
    // if an @ exists not in the start and end of email
    //and dot exists not directly before or after and not at the end of email or 
    // at the start of the email
    if(at == NULL || at == email || at == (email + strlen(email)-1)||dot == at-1 ||dot == at+1 || dot == (email +strlen(email)-1)||dot == email){
        return 0;
    }
    //no multiple @
    if(strchr(at+1,'@') != NULL){
        return 0;
    }
    //atleast 3 characters before @
    if (at - email < 3){
        return 0;
    }
    dot = strchr(at+1,'.');
    //dot exists after the @
    if(dot == NULL){
        return 0;
    }
    //stleast 3 characters after the @
    
    if (email +strlen(email) - dot-1 < 3){
    
        return 0 ;
    }
    char *space = strchr(email,' ');
    //no space in email
    if(space != NULL){
        return 0;
        }

    //copy all characters after the @
    //copy after pointer and allocate memory and give pointer to memory
    char* domain = strdup(at + 1);
    //printf("%s",domain);
    if (domain == NULL){
        printf("pointer failed");
    }
     for (int i = 0 ; i < strlen(domain)-1;i++){
        if(isupper(domain[i])){
            domain[i] = tolower(domain[i]);
            
        }
    }
    
    if(domain[strlen(domain)-1]=='\n'||domain[strlen(domain)-1]==' '){
        domain[strlen(domain) - 1] = '\0';
    }
    
   
    for(int i = 0 ; i < sizeof(domains) / sizeof(domains[0]) ; i++){
        
        if(strcmp(domain,domains[i]) == 0){
            free(domain);
            return 1;

        }
     
    }
    printf("%s is not a supported Domain \n",domain);
    free (domain);
    return 0;

    
}
//validate phone number
int validateMobile(const char* mobileNumber){
    // remove last whitespace character 
    /* if(mobileNumber[12]==' '||mobileNumber[12]=='\n'){
        mobileNumber[12] = '\0';
    } */
    //chack length of phone number
    if(strlen(mobileNumber)!=11){
        return 0;
    }
    //check if first digit is 0
    else if(mobileNumber[0] != '0'){
        return 0;
    }
    //no spaces in phone number
    char *space = strchr(mobileNumber,' ');
    if(space != NULL){
        return 0;
    }
    //only digits
    for (int i = 0 ; i < 11 ; i ++ ){
        if(!isdigit(mobileNumber[i])){
            return 0;
        }
    }
    char firstdigits [4];
    //copy first 3 digits of phone number into an array
    strncpy(firstdigits,mobileNumber,3);
    
    //end array 
    firstdigits[3] = '\0';
    for(int i = 0 ;i<3;i++){
       if(strcmp(firstdigits,phoneCompany[i]) == 0){
        return 1;
       }
    }
    return 0;
}
//validate date 
int validateDate (char reserveDate[], date* destination){
    //remove whitespace character
    //search for location of white space character and remove it
    reserveDate[strcspn(reserveDate, "\n")] = '\0';
    char forTokinazation [11];
    strcpy(forTokinazation,reserveDate);
    //check format
    if(strlen(forTokinazation)!=10 || forTokinazation[2]!='-'||forTokinazation[5]!='-'){
        printf("DATE WRONG FORMAT (dd-mm-yyyy)\n");
        return 0;
    }
   
    //devide date into partition (day,month,year)
    
    char *ptr = strtok(forTokinazation,"-");
     if(ptr == NULL){
        printf("Error in pointer");
        return 0;
    }
    int day = atoi(ptr);
    ptr = strtok(NULL,"-");
    if(ptr == NULL){
        printf("Error in pointer");
        return 0;
    }
    int month = atoi(ptr);
    ptr = strtok(NULL,"-");
    if(ptr == NULL){
        printf("Error in pointer");
        return 0;
    }
    int year = atoi(ptr);

    //check if date is valid
    int leap = 0;
    
    
    if(year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)){
        leap = 1;
    }
    if(month>12 || month<1){
         printf("wrong month %d\n",month);
        return 0;
        }
    if( day>31 || day<1 ||(day>28 && month == 2 && leap == 1)||(day == 29 && month == 2 && leap == 0)){
        printf("wrong day %d\n",day);
        return 0;
     }
    
    
    //get time now
    time_t t = time(NULL);

    struct tm *now = localtime(&t);
    int currentDay = now->tm_mday;
    int currentMonth = now->tm_mon + 1;
    int currentYear = now->tm_year + 1900; // counts years after 1900
    

    
    //check if date is in the future
    if(currentYear>year || (currentYear == year && currentMonth>month) || (currentYear == year && currentMonth == month && currentDay>day)){
        printf("date must be in the future \n");
        return 0 ;

    }
    if(year-currentYear>5){
        printf("date is too far in the future \n");
        return 0 ;
    }
    destination->day = day;
    destination->month = month;
    destination->year = year;

    
    
    
return 1;
    

}
//check if room category is correct
int validateRoomCategory(char category[]){
    category[strcspn(category, "\n")] = '\0';

    if(strchr(category,' ')!= NULL){
        printf("invalid category\n");
        return 0 ;
    }


for(int i = 0 ; i < 3;i++){
    if(strcmp(category,categories[i])==0){
        return 1;
    }
}
printf("%s\n",category);
printf("choose a correct category CASE SENSITIVE\n");
return 0 ;
}
//check if number of nights is correct
int validateNightNum(char num[]){
    num[strcspn(num, "\n")] = '\0';
    if(strchr(num,' ')!= NULL){
        printf("invalid number\n");
        return 0 ;
        }
        int i = 0;
        while(num[i]!='\0'){
            if(!isdigit(num[i])){
                printf("invalid number\n");
                return 0 ;
            }
            i++;
        }
        return 1 ;

}
//check if room number exists
int validateRoomnum(char NUM[]){
    //int roomnum = atoi(NUM);
    FILE* fptr = fopen("Room.txt","r");
    int lines = countlines(fptr);
    Room* rooms = malloc(lines*sizeof(Room));
    LoadRooms(fptr,rooms);
    fclose(fptr);
    if(findRoom(rooms,NUM,lines)==-1){
        printf("Room number is not available or incorrect\n");
        return 0;
    }
    else{
        return 1;
    }
} 
// enter data and validate into struct
void enterData(reservation* i){
     

   printf("To reserve a room please enter your first and last name:(maximum 100 characters) ");
    fgets(i->custName,sizeof(i->custName),stdin);
    i->custName[strcspn(i->custName, "\n")] = '\0';
    while(!validateName(i->custName)){
        printf("Wrong input please enter your first and last name:(maximum 100 characters) ");
        fgets(i->custName,sizeof(i->custName),stdin);
        i->custName[strcspn(i->custName, "\n")] = '\0';
} 

    printf("please Enter ur national ID: 14 digits");
    fgets(i->nationalId,sizeof(i->nationalId),stdin);
    i->nationalId[strcspn(i->nationalId, "\n")] = '\0';
    //wrong id
    while(!validateID(i->nationalId)){
       
        printf("Wrong ID Please try again: 14 digits");
        getchar();
        fgets(i->nationalId,sizeof(i->nationalId),stdin);
        i->nationalId[strcspn(i->nationalId, "\n")] = '\0';
        
    }
    i->nationalId[14]='\0';
    printf("please Enter your email: ");
    getchar();
    fgets(i->email,sizeof(i->email),stdin);
    i->email[strcspn(i->email, "\n")] = '\0';
    while(!validateEmail(i->email)){
        //getchar();
        printf("\nWrong email Please try again:");
        fgets(i->email,sizeof(i->email),stdin);
        i->email[strcspn(i->email, "\n")] = '\0';
    }
    //

   
    
     printf("please Enter your mobile number: ");
    fgets(i->mobileNum,sizeof(i->mobileNum),stdin);
     i->mobileNum[strcspn(i->mobileNum, "\n")] = '\0';
    while(!validateMobile(i->mobileNum)){
        //getchar();
        printf("Wrong mobile number Please try again:");
        fgets(i->mobileNum,sizeof(i->mobileNum),stdin);
         i->mobileNum[strcspn(i->mobileNum, "\n")] = '\0';
    }
    printf("Enter Date of Reservation: (dd-mm-yyyy) ");
    
    char reserveDate[11];
    
    fgets(i->stringdate,sizeof(i->stringdate),stdin);
    i->stringdate[strcspn(i->stringdate, "\n")] = '\0';
    //splitDate(i->stringDate,&i->checkIn);

    while(!validateDate(i->stringdate,i->checkinDate)){
        getchar();
        printf("Wrong date Please try again:");
        fgets(i->stringdate,sizeof(i->stringdate),stdin);
        i->stringdate[strcspn(i->stringdate, "\n")] = '\0';
        //splitDate(i->stringDate,&i->checkIn);
    } 
    printf("Enter Number of Nights: ");
    scanf(" %s",&i->nightNum);
    while(!validateNightNum(i->nightNum)){
        printf("Wrong number of nights Please try again:");
        //getchar();
        scanf(" %s",&i->nightNum);
        

    }
    getchar(); 
    printf("CASE SENSITIVE\n");
    printf("choose a Room category:(SeaView,LakeView,GardenView) ");
    fgets(i->RoomCategory,sizeof(i->RoomCategory),stdin);
      i->stringdate[strcspn(i->stringdate, "\n")] = '\0';
    while (!validateRoomCategory(i->RoomCategory)){
        printf("Wrong room category Please try again: (SeaView,LakeView,GardenView) \n");
        fgets(i->RoomCategory,sizeof(i->RoomCategory),stdin);
        printf("%s",i->RoomCategory);
       i->RoomCategory[strcspn(i->RoomCategory, "\n")] = '\0';
}
//getchar();
 
}
//  print data to confirm
void printReservation(reservation* customer){
    printf("\n");
    clearScreen();
    printf("\n");
    printf("Customer Name: %s\n",customer->custName);
    printf("National ID: %s\n",customer->nationalId);
    printf("Customer Email: %s\n",customer->email);
    printf("Customer Phone Number: %s\n",customer->mobileNum);
    printf("Number of Nights: %s\n",customer->nightNum);
    //printf("Room Category: %s\n",customer->roomNum);
    printf("Room Category: %s\n",customer->RoomCategory);
    printf("Reservation Date = %s\n",customer->stringdate);

}
//display rooms available in category
int showroom(Room* rooms , char* category,int count){
    printf("\n");
    clearScreen(); 
    int f = 0;
    printf("\t Available Rooms\n");
    for (int i = 0;i<count;i++){
    if(strcmp(rooms[i].roomCategory,category)==0){
        if(strcmp(rooms[i].status,"Available")==0){
            printf("Room number = %d\tPrice =  %d\n",rooms[i].number,rooms[i].price);
            f = 1;}
}  }
int flag = 0;
while (f == 0){
    printf("No rooms available in that category please choose another\n");
    printf("CASE SENSITIVE\n");
    printf("choose a Room category:(SeaView,LakeView,GardenView) ");
   
    fgets(category,11,stdin);
    while (!validateRoomCategory(category)){
        printf("Wrong room category Please try again: (SeaView,LakeView,GardenView) ");
        fgets(category,11,stdin);
}
   printf("\t    Available Rooms\n");
    for (int i = 0;i<count;i++){
    if(strcmp(rooms[i].roomCategory,category)==0){
         
        if(strcmp(rooms[i].status,"Available")==0){
            printf("Room number = %d\tPrice =  %d\n",rooms[i].number,rooms[i].price);
            f = 1;}
            else{
            flag+=1;}
            //if all choices go back to main
            if(flag == 3){
                printf("NO ROOMS AVAILABLE \n");
               return 0;
            }
}  }
}

}
// choose Room From the Available rooms
int chooseRoom (char roomNum[],Room* rooms,int count,reservation* customer){

    int flag = 0;
    char number[5];
    //sprintf(number,"%d",rooms[i].number);
    for (int i = 0;i<count;i++){
        sprintf(number,"%d",rooms[i].number);
        if(!strcmp(number,roomNum)){
            strcpy(rooms[i].status,"Reserved");
            strcpy(customer->roomNum , number );
            flag = 1;
            }
            }

            return flag;
            


}
//generate random id
void randomID(const char randomcharacter[],char*str , int num){
    int lengthRC = 10; //size of array of random array
    //intial value to start with in the pseudorandom generator
    //seed so that rand() doesn't give the same value each time
    //seed is the current time bcs time changes every second
    srand(time(NULL));
    for (int i = 0;i<num;i++){
        //rand gets a random number them by using mod the number produced is less than length of rc
        str[i] = randomcharacter[(rand()%lengthRC)];//gets a random character from the array
    }
}
//check if random id already exists
int validaterandomID(char * str,int line,reservation *all ){
    
    int flag = 0;
    for (int i = 0;i<line;i++){
        if (strcmp(str,all[i].reservationID)==0){
            flag = 1;
            break;
        }
    }
    return flag;

}
//find room by number or id
int findRoom_NumorID(reservation* all,int lines){
        char idNum[8];
    
   
    int i =0;
while(1){
    int flag = 0;
    printf("Enter your reservation ID or Room number: ");
    scanf("%s",idNum);
    
    // find the line where reservation exits
    for(i=0;i<lines;i++){
        // compare id
        if(strcmp(all[i].reservationID,idNum)==0){
            return i;
            break;}
            //compare room number
        else if(!strcmp(all[i].roomNum,idNum)){
            return i;
            break;}
            
 
    }

    //doesn't exist

    if(flag == 0){
        printf("No reservation found\nwould u like to try again(y/n/m/e)");
        char choice;
        scanf(" %c",&choice);
        if(choice == 'y'){
          continue;
            
        }
        else if(choice == 'n'){
            break;
        }
        else if (choice == 'm'){
            i = -1;
            return i;
        }
        else if(choice == 'e'){
            exit(1);
        }

      
    }}
}
//validate search by date
int validateSearchDate (char reserveDate[], date* destination){
    //remove whitespace character
    //search for location of white space character and remove it
    reserveDate[strcspn(reserveDate, "\n")] = '\0';
    //check format
    if(strlen(reserveDate)!=10 || reserveDate[2]!='-'||reserveDate[5]!='-'){
        printf("DATE WRONG FORMAT (dd/mm/yyyy)\n");
        return 0;
    }
   
    //devide date into partition (day,month,year)
    
    char *ptr = strtok(reserveDate,"-");
     if(ptr == NULL){
        printf("Error in pointer");
        return 0;
    }
    int day = atoi(ptr);
    ptr = strtok(NULL,"-");
    if(ptr == NULL){
        printf("Error in pointer");
        return 0;
    }
    int month = atoi(ptr);
     if(month>12 || month<1){
         printf("wrong month %d\n",month);
        return 0;
        }
    ptr = strtok(NULL,"-");
    if(ptr == NULL){
        printf("Error in pointer");
        return 0;
    }
    int year = atoi(ptr);

    //check if date is valid
    int leap = 0;
    
    
    if(year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)){
        leap = 1;
    }
   
    else if( day>31 || day<1 ||(day>28 && month == 2 && leap == 1)||(day == 29 && month == 2 && leap == 0)){
        printf("wrong day %d\n",day);
        return 0;
     }
    
    
        destination->day = day;
        destination->month = month;
        destination->year = year;


    
    
    
return 1;
    

}
// customer data, lines of reservation data,all rooms,number of rooms available
int enterchangereserve(reservation* all , int lines ,Room* rooms,int count){
            // change name
            char confirm;
            getchar();
        printf("1. Change Name\n");
        
        while(1){     
            printf("Current Name: %s\n",all->custName);
            printf("Do you want to change Reservation name: \nyes/no/return to menu/exit program(y/n/m/e)");  
            scanf(" %c",&confirm);
        if(confirm == 'y'){
            printf("Enter new name: ");
            getchar();
            fgets(all->custName,sizeof(all->custName),stdin);
            all->custName[strcspn(all->custName, "\n")] = '\0';
            while (!validateName(all->custName))
            {
                printf("Invalid name. Please enter a valid name.\n");
                printf("Enter new name: ");
                getchar();
                fgets(all->custName,sizeof(all->custName),stdin);
                all->custName[strcspn(all->custName, "\n")] = '\0';


                        }
            
           break;
        }
        else if (confirm !='y' && confirm!='n'&&confirm!='m'&&confirm!='e'){
            printf("Invalid choice\n");
            
                continue;
        }    
        else if(confirm == 'n'){
            break;

        }
        else if(confirm == 'm'){
            
            return -1;
        }
        else if(confirm == 'e'){
            exit(1);
        }}
        //change phone
        
        printf("2. Change Phone Number\n");   
        //phone number
        while (1)
        {
            all->mobileNum[strcspn(all->mobileNum,"\n")]='\0';
       
        printf("Current phone number: %s \n",all->mobileNum);
        printf("Do you want to change Reservation phone number: \nyes/no/return to menu/exit program(y/n/m/e)");
        scanf(" %c",&confirm);
        getchar();
        if(confirm == 'y'){
            printf("Enter new phone number: ");
            fgets(all->mobileNum,sizeof(all->mobileNum),stdin);
            all->mobileNum[strcspn(all->mobileNum, "\n")] ='\0';
            while (!validateMobile(all->mobileNum)){
                printf("Invalid phone number. Please enter a valid phone number.\n");
                printf("Enter new phone number: ");
                fgets(all->mobileNum,sizeof(all->mobileNum),stdin);
                all->mobileNum[strcspn(all->mobileNum, "\n")] ='\0';
                

            }
            break;
            }
            else if (confirm !='y' && confirm!='n'&&confirm!='m'&&confirm!='e'){
                printf("Invalid choice\n");
                continue;
                }
                else if(confirm == 'n'){
           break;

        }
        else if(confirm == 'm'){
            
            return -1;
        }
        else if(confirm == 'e'){
            exit(1);
        }
        }
       

        //change email
        printf("3. Change Email\n");
        while(1){
            printf("Current email: %s \n",all->email);
            printf("Do you want to change Reservation email: \nyes/no/return to menu/exit program(y/n/m/e) ");
            scanf(" %c",&confirm);
        if(confirm == 'y'){
            getchar();
            printf("Enter new email: ");
            fgets(all->email,sizeof(all->email),stdin);
            all->email[strcspn(all->email, "\n")] ='\0';
            while (!validateEmail(all->email)){

                printf("Invalid email. Please enter a valid email.\n");
                printf("Enter new email: ");
                fgets(all->email,sizeof(all->email),stdin);
                all->email[strcspn(all->email, "\n")] ='\0';
                
                }

           break;
            }
             else if (confirm !='y' && confirm!='n'&&confirm!='m'&&confirm!='e'){
                printf("Invalid choice\n");
                continue;
                } 
                else if(confirm == 'n'){
           break;

        }
        else if(confirm == 'm'){
            
            return -1;
        }
        else if(confirm == 'e'){
            exit(1);
        }
                }
            //room category
            
        printf("4. Change Room Category\n");
        //int roomnumber = atoi(all[i].roomNum);
        //using room number find category
        int roomlocation = findRoom(rooms,all->roomNum,count);
        if(roomlocation == -1){
            printf("room not found");
            exit(1);
            }
        while(1){
            printf("Current room category: %s \n",rooms[roomlocation].roomCategory);
        printf("Do you want to change Reservation room category: \nyes/no/return to menu/exit program(y/n/m/e)");
        scanf(" %c",&confirm);
        if(confirm == 'y'){
            printf("CASE SENSITIVE\n");
            printf("Enter new room category Please enter one of the following: SeaView,LakeView,GardenView ");
            //char room[20];
            getchar();
            fgets(all->RoomCategory,sizeof(all->RoomCategory),stdin);
            all->RoomCategory[strcspn(all->RoomCategory, "\n")] ='\0';
            while(!validateRoomCategory(all->RoomCategory)){
                printf("CASE SENSITIVE\n");
                printf("Invalid room category. Please enter one of the following: SeaView,LakeView,GardenView ");
    
                fgets(all->RoomCategory,sizeof(all->RoomCategory),stdin);
                all->RoomCategory[strcspn(all->RoomCategory, "\n")] ='\0';

            }
            //change room status to available
            strcpy(rooms[roomlocation].status , "Available");
            //show available rooms
            showroom(rooms,all->RoomCategory,count);
            char choice[5];
            printf("Enter number of the room of your choice: ");
            scanf(" %s",&choice);
            while(!chooseRoom(choice,rooms,count,all)){
                
                printf("Invalid choice, please choose a valid room number\n");
                printf("Enter number of the room of your choice: ");
                scanf(" %s",&choice);

            }
            
           break;
            }
             else if (confirm !='y' && confirm!='n'&&confirm!='m'&&confirm!='e'){
                printf("Invalid choice\n");
                continue;
                }
                else if (confirm == 'n'){
                   break;
                }
                else if(confirm == 'm'){
            
            return -1;
        }
        else if(confirm == 'e'){
            exit(1);
        }}
              
                // number of lines
        printf("5. Change Number of Nights\n");
        while (1){
            printf("Current number of nights :%s\n",all->nightNum);
             printf("Do you want to change Reservation number of nights: \nyes/no/return to menu/exit program(y/n/m/e)");
        scanf(" %c",&confirm);
        if(confirm == 'y'){
            
            printf("Enter new number of nights: ");
           
            scanf(" %s",&all->nightNum);
            while(!validateNightNum(all->nightNum)){
                printf("Invalid number of nights\n");
                printf("Enter new number of nights: ");
                scanf(" %s",&all->nightNum);
            }
            break;}
            else if (confirm !='y' && confirm!='n'&&confirm!='m'&&confirm!='e'){
                printf("Invalid choice\n");
                
                continue;
                }
                else if(confirm == 'n'){
           break;

        }
        else if(confirm == 'm'){
            
            return -1;
        }
        else if(confirm == 'e'){
            exit(1);
        }
        }
        
        //date
        printf("6. Change Date\n");
        
        while (1)
        {
            printf("Current Date = %s\n",all->stringdate);
        printf("Do you want to change Reservation date: \nyes/no/return to menu/exit program(y/n/m/e)");
            scanf(" %c",&confirm);
            if(confirm == 'y'){
                printf("Enter new date: (dd-mm-yyyy)");
                char resdate [11];
                getchar();
                fgets(resdate,sizeof(resdate),stdin);
                resdate[strcspn(resdate, "\n")] ='\0';
                printf(" %s",resdate);
                while(!validateDate(resdate,all->checkinDate)){
                    printf("Invalid date. Please enter a valid date (dd-mm-yyyy): ");
                    getchar();
                    fgets(resdate,sizeof(resdate),stdin);
                    resdate[strcspn(resdate, "\n")] ='\0';

                }
                break;
                }
                else if (confirm !='y' && confirm!='n'&&confirm!='m'&&confirm!='e'){
                    printf("Invalid choice\n");
                   
                continue;
                    }
                    else if(confirm == 'n'){
            break;
        }
        else if(confirm == 'm'){
            
            return -1;
        }
        else if(confirm == 'e'){
            exit(1);
        }

}}
// query search by room status
void searchRoomStatus(){

    char search[256];
    int flag=1, i;
    Room rooms[256];
    FILE *fptr=fopen("Room.txt", "r");
    int lines=countlines(fptr);
    LoadRooms(fptr,rooms);
    fclose(fptr);
    while(flag){
        printf("\033[1;34mEnter A to view available rooms, and R to view reserved rooms:\033[0m ");
        gets(search);
        while(!isalpha(search[0])||strlen(search)!=1){
                printf("\033[1;31mWrong entry, enter A or R:\033[0m ");
                gets(search);
            }
        switch(search[0]){
            case 'A':
                printf("Available rooms are: ");
                for(i=0;i<lines;i++){
                    if(!strcmp(rooms[i].status, "Available"))
                        printf("%d\n", rooms[i].number);
                }
            case 'a':
                printf("Available rooms are: ");
                for(i=0;i<lines;i++){
                    if(!strcmp(rooms[i].status, "Available"))
                        printf("%d\n", rooms[i].number);
                }
                flag=0;
                break;
            case 'R':
                printf("Reserved rooms are: ");
                for(i=0;i<lines;i++){
                    if(!strcmp(rooms[i].status, "Reserved"))
                        printf("%d\n", rooms[i].number);
                }
                flag=0;
                break;
            case 'r':
                printf("Reserved rooms are: ");
                for(i=0;i<lines;i++){
                    if(!strcmp(rooms[i].status, "Reserved"))
                        printf("%d\n", rooms[i].number);
                }
                flag=0;
                break;
            default:
                printf("\033[1;31mWrong entry, enter M or E:\033[0m ");
        }
    }
    menuOrExit();
}
//query search by room number
void searchRoomNum(){
    reservation r[256];
    Room rooms[256];
    FILE *fptr1=fopen("Room.txt", "r");
    int lines1=countlines(fptr1);
    LoadRooms(fptr1,rooms);
    fclose(fptr1);
    char roomNum[256];
    printf("\033[1;34mEnter room number:\033[0m ");
    gets(roomNum);
    int i=findRoom(rooms,roomNum,lines1);
    while(i==-1){
        printf("\033[1;31mRoom not found, enter room number:\033[0m ");
        gets(roomNum);
    }
    printf("This room is %s\n", rooms[i].status);
    if(!strcmp(rooms[i].status,"Reserved")){
        FILE *fptr2=fopen("Reservation.txt", "r");
        int lines2=countlines(fptr2);
        fclose(fptr2);
        load(r);
        int j=findReservation(r,roomNum,lines2);
        printf("Name of customer: %s\n", r[j].custName);
        printf("Customer national ID: %s\n", r[j].nationalId);
        printf("Email: %s\n", r[j].email);
        printf("Mobile number: %s", r[j].mobileNum);
    }
    menuOrExit();
}
//query search by custumer name
void searchName(){
    reservation r[256];
    int index=-1, j=0, i;
    char name[50], custName[50];
    printf("\033[1;34mEnter customer name:\033[0m ");
    fgets(name,sizeof(name),stdin);
    name[strcspn(name,"\n")]='\0';
    load(r);
    for(i=0;name[i]!='\0';i++){
            name[i]=tolower(name[i]);
    }
    while(j<256 &&r[j].custName[0]!='\0'){
        strcpy(custName,r[j].custName);
        for(i=0;custName[i]!='\0';i++){
            custName[i]=tolower(custName[i]);
        }
        if(!strcmp(name,custName)){
            index=j;
            break;
        }
        j++;
    }
    if(index==-1){
        printf("\033[1;31mCustomer name not found.\033[0m");
    }else{
        printf("Reservation ID: %s\n", r[index].reservationID);
        printf("Room number: %s\n", r[index].roomNum);
        printf("Room reservation status: %s\n", r[index].reserveStatus);
        printf("Name of customer: %s\n", r[index].custName);
        printf("Customer national ID: %s\n", r[index].nationalId);
        printf("Number of nights: %s\n", r[index].nightNum);
        printf("Check-in date: %s\n", r[index].stringdate);
        printf("Email: %s\n", r[index].email);
        printf("Mobile number: %s", r[index].mobileNum);
    }
    menuOrExit();
}
//parse date
void parseCheckinDate(const char *checkinDateStr, date *checkinDate) {
    char temp[11]; // Temporary buffer to avoid modifying the original string
    strcpy(temp, checkinDateStr);

    char *token = strtok(temp, "-");
    if (token != NULL) checkinDate->day= atoi(token);

    token = strtok(NULL, "-");
    if (token != NULL) checkinDate->month=atoi(token);

    token = strtok(NULL, "-");
    if (token != NULL) checkinDate->year=atoi(token);
}
// Returns the number of days in a given month of a given year
int days_in_month(int year, int month) {
    // Returns the number of days in a given month of a given year
    int days_in_months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
        return 29; // Leap year check for February
    }
    return days_in_months[month - 1]; // month is 1-based
}
//days from start of year
int days_from_start_of_year(int year, int month, int day) {
    int days = 0;
    for (int m = 1; m < month; m++) {
        days += days_in_month(year, m);
    }
    days += day;
    return days;
}
//
int findReservation(reservation *r,char NUM[],int count){
    int i;
    int roomnumber = atoi(NUM);
    for(i=0;i<count;i++){
        if(atoi(r[i].roomNum) ==roomnumber){
            //return index
            return i;
        }
        }
        return -1;

}
