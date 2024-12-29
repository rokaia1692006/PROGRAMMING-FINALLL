#include<stdio.h>
#include <string.h>
#include <ctype.h>
#include "reservation.h"
#include <time.h>
#include <stdlib.h>
#include "LOADANDSAVE.c"
#include "Functions.c"
#include "FUNCNAME.h"

//main menu (calling of functions)
void MainMenu() {
    char search[256];

        printf("\n\033[1;33mHotel Management System - Main Menu\033[0m\n");
        printf("-------------------------------------\n");
        printf("1. Reserve a Room\n");
        printf("2. Check-In\n");
        printf("3. Cancel Reservation\n");
        printf("4. Check-Out\n");
        printf("5. Check Room Availability\n");
        printf("6. View Customer Details\n");
        printf("7. Edit Reservation Details\n");
        printf("8. Query/Search\n");
        printf("9. Reservation Report\n");
        printf("10. Exit\n");
       printf("\033[1;34mEnter your choice (1-10): \033[0m");

        scanf("%s",search);
        getchar();

   int choice = atoi (search);
   if (choice>10)
   {printf("Error, try again.\n");
   MainMenu();}

        switch (choice) {
           case 1:
                reserve();
                break;
            case 2:
                checkInGuest();
                break;
            case 3:
                CancelReservation();
                break;
            case 4:
                Checkout();
                break;
           case 5:
                RoomAvailability();
                break;
            case 6:
                details();
                break;
            case 7:
                changeReservation();
                break;
            case 8:
                query();
                break;
            case 9:
                printbydate();
                break;
            case 10:
                printf("Exiting to system...\n");
                exit(1);
            default:
                {printf("\033[1;31mInvalid choice. Please try again.\033[0m\n");
                MainMenu();}
        }}

//user identification
int login(user *users, int user_count) {

    char username[50], password[50];


        printf("\033[1;34mEnter Username: \033[0m");
        scanf("%s", username);
        printf("\033[1;34mEnter Password: \033[0m");
        scanf("%s", password);


    for (int i = 0; i < user_count; i++) {

        if (strcmp(username, users[i].fileusername) == 0 && strcmp(password, users[i].filepassword) == 0) {
            MainMenu();
            return 1;
        }
    }
    printf("\033[1;31mInvalid username or password. Please try again.\033[0m\n");

    return 0;

}

//main calling
int firstmenuLogin(){


    user *users = NULL;
    int user_count = 0;
    char search[256];


    if (!loadUsers(&users, &user_count)) {
       printf("\033[1;31mError: Could not load user credentials.\033[0m\n");
        return 0;
    }


    printf("\033[1;33mWelcome to the Hotel Management System\033[0m\n");
    printf("---------------------------------------\n");
    printf("1. Login\n");
    printf("2. Exit\n");
    printf("Select an option 1 or 2: ");
    scanf("%s",search);
    getchar();
    while(!isdigit(search[0])||strlen(search)!=1){
                printf("\033[1;31mWrong entry, enter 1 or 2: \033[0m ");
                gets(search);
            }

   int choice = atoi (search);
    switch(choice) {
        case 1:
            if (login(users, user_count)) {
                printf("\033[1;32mLogin successful!\033[0m\n");
                    MainMenu();
    }
            else {

                free(users);
                firstmenuLogin();
    }

            break;
        case 2:
            printf("\033[1;31mExiting the system.\033[0m\n");
            return 0;
        default:
            printf("\033[1;31mInvalid choice. Please try again.\033[0m\n"); firstmenuLogin();
        }


    free(users);

    return 0;


}

//return to menu or exit
void menuOrExit(){
    char search[256];
    int flag=1;
    while(flag){
        printf("\033[1;34mEnter 1 to go back to main menu, and 2 to \033[1;34m\033[1;31mEXIT:\033[0m ");
        scanf("%s", search);
        getchar();
        while(!isdigit(search[0])||strlen(search)!=1){
                printf("\033[1;31mWrong entry, enter 1 or 2:\033[0m ");
                scanf("%s", search);
            }
        switch(search[0]){
            case '1':
                MainMenu();
                flag=0;
                break;
            case '2':
                exit(1);
                flag=0;
                break;
            default:
                printf("\033[1;31mWrong entry.\033[0m");
        }
    }
}

//******reserve room */
void reserve(){
//enter custumer data
reservation* customer  = malloc(sizeof(reservation)-1);
while(1){
enterData(customer);
//print the reservation data
printReservation(customer);
//check if data is correct
printf("is the data correct if no u will be prompted to enter the data again \n");
printf("yes/no/exit (y/n/e)");
char choice;
scanf(" %c",&choice);
// try again
if(choice == 'n'){
    printf("Enter the data again:\n");
    continue;
}
//exit while
else if (choice == 'y'){
    printf("GREAT!\n");
    break;
}
else if(choice == 'e'){
    exit(1);

}
else{
    printf("please choose y/n/e");
}
}
//open room
FILE *file = fopen("Room.txt", "r");

if(file == NULL){
    printf("file not found");
    exit(1);
    }
//count the lines in room
int count  = countlines(file);
//allocate memory
Room* rooms = malloc(count*sizeof(Room));
//memory allocation failed
if(rooms == NULL){
    printf("Memory not allocated\n");
    fclose(file);
   return;
    }
    //load into struct
LoadRooms(file,rooms);
fclose(file); 
//open reservation
file = fopen("Reservation.txt", "r"); 
if(file == NULL){
    printf("file not found");
    exit(1);
    }


//show rooms

showroom(rooms,customer->RoomCategory,count);

char roomNumber[5];
printf("Enter number of the room of your choice: ");
scanf(" %s",&roomNumber);
//check if choice is valid
while(!chooseRoom(roomNumber,rooms,count,customer)){

    printf("Invalid choice, please choose a valid room number \n");
    printf("Enter number of the room of your choice: ");
    scanf(" %s",&roomNumber);
}
//write in file
file = fopen("Room.txt", "w");
//check if file is open
if(file == NULL){
    printf("file not found");
    exit(1);
    }
    // save rooms
    saveRooms(file,rooms,count);
    fclose(file); 
    //open reservation
file = fopen("Reservation.txt","r");

if(file == NULL){
    printf("file not found");
    return;
}
//count lines
int line = countlines(file);

fclose(file);
//allocate memory
reservation *all = malloc(line*sizeof(reservation));
load(all);

//generate random id

randomID(randomcharacter,customer->reservationID,7);
customer->reservationID[sizeof(customer->reservationID)-1]='\0';
//validate random id
while(validaterandomID(customer->reservationID,line,all)){
    printf("ID already exist\n");
    randomID(randomcharacter,customer->reservationID,7);
customer->reservationID[sizeof(customer->reservationID)-1]='\0';
}
free(all);
printf("Your Reservation ID is %s please remeber it for later use\n",customer->reservationID);
//status is unconfirmed
strncpy(customer->reserveStatus,"unconfirmed",sizeof(customer->reserveStatus));
//end the string
customer->reserveStatus[sizeof(customer->reserveStatus)-1] = '\0';
//append data
    file = fopen("Reservation.txt","a+");
    fseek(file,0,SEEK_END); // making sure
    if(file == NULL){
        printf("Could not open file\n");
        return;
        }
        if (ftell(file) != 0) { // Check if the file is not empty
        fprintf(file, "\n");
    } 
    //write new costumer in file
writeCustomer(file,customer);

free(rooms);
menuOrExit();
}

//******check in */
 void checkInGuest() {
     char c;
    FILE *res = fopen("Reservation.txt","r"); //reservation
    if (res == NULL) {
        printf("Could not open file\n");
        return;
        }
    int lines = countlines(res); //lines in reservation
    fclose(res);
    
    reservation *all = malloc(lines*sizeof(reservation)); //all people
    load(all);
  
    int f = findRoom_NumorID(all,lines);
    if(f == -1){
        menuOrExit;
        }
        res = fopen("Room.txt","r");
        if (res == NULL) {
            printf("Could not open file\n");
            menuOrExit();}
            int lines2 = countlines(res); //lines in room
            
            Room *rooms = malloc(lines2*sizeof(Room)); //all rooms
            LoadRooms(res,rooms);
            fclose(res);
            for(int i = 0 ; i < lines2;i++){
                if(rooms[i].number == atoi(all[f].roomNum)){
                    strcpy(all[f].RoomCategory,rooms[i].roomCategory);
            }}

    printReservation(&all[f]);
   printf("Do you want to check in? (y/n): \n");
  
   while (1){
   scanf(" %c",&c);
    if (c!='y'&&c!='n'){
        printf("Invalid input. Please enter y or n.\n");
        continue;
    }
   if(c == 'y'){
     date today;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    today.day = tm.tm_mday;
    today.month = tm.tm_mon + 1;
    today.year = tm.tm_year + 1900;

   splitDate(all[f].stringdate,all[f].checkinDate);
    if (today.year < all[f].checkinDate->year ||
                (today.year == all[f].checkinDate->year && today.month < all[f].checkinDate->month) ||
                (today.year == all[f].checkinDate->year && today.month == all[f].checkinDate->month && today.day < all[f].checkinDate->day)) {
                printf("Check-in not allowed before the check-in date.\n");
                return;
            }
    //update status to checked in
    strncpy(all[f].reserveStatus, "confirmed", sizeof(all[f].reserveStatus));
    all[f].reserveStatus[sizeof(all[f].reserveStatus)-1] = '\0';
    res = fopen("Reservation.txt","w"); //reservation
    if (res == NULL) {
        printf("Could not open file\n");
        return;
        }
     //lines in reservation
    
    for(int i = 0 ;i<lines;i++){
        writeCustomer(res,&all[i]);
        if(i!=(lines-1)){
            fprintf(res,"\n");
        }

    }
    fclose(res);
    printf("You have been checked in\n");
    free(all);
    menuOrExit();
    }
    if(c =='n'){
        printf("You have not been checked in\n");
        free(all);
        menuOrExit();

    }}
 menuOrExit();
 }

//******cancel */
void CancelReservation () {

    char s[100];


   printf("\033[1;34mFor cancellation, if you'll provide the room number enter 'Room', if you'll provide the reservation ID enter 'ID'\033[0m\n");
   gets(s);
   if (strcasecmp(s,"ROOM") == 0 || strcasecmp(s,"room")==0 || strcasecmp(s,"Room") == 0 ){
      int index=-1,ROOMNI=0,j=0,count=0,c1=0;
      char ROOMN[5],c[2];

      reservation r[256];

      reservation *fptr = &r[index];
  if (fptr == NULL) {printf("\033[1;31mError in opening reservation file.\033[0m");}
  else {
    printf("\033[1;34mPlease enter the room number: \033[0m");
    scanf("%s", &ROOMN);
    getchar();
            //the enter after writing the room number get in the way if the room is already available
load(r);
       while(strcmp(r[j].roomNum,"")){

        if(!(strcmp(ROOMN,r[j].roomNum))){
            index=j;

            break;
        }
        j++;
    }
    if(index==-1){
        printf("\033[1;31mRoom number not found.\033[0m\n");
        printf("If you want to re-do the process, enter '1', if you want to return to the main menu, enter '2', and if you want to exit enter '3'\n");
        scanf("%d",&c1);
        getchar();
            if (c1 == 1) CancelReservation();
            else if (c1 == 2) MainMenu();
            else if (c1 == 3) exit(1);
            else {printf("\033[1;31mInvalid input, returning to main menu.\033[0m\n"); MainMenu();}}

        if (!(strcmp(ROOMN,r[index].roomNum))){
            if (strcmp(r[index].reserveStatus,"unconfirmed")==0){
                    ROOMNI=atoi(r[index].roomNum);
                FILE *fptr=fopen("Room.txt","r");
                if (fptr == NULL ){printf("\033[1;31mError in opening room text file.\033[0m\n");}
                    else {
                    count = countlines(fptr);
                    Room *room = malloc(count*sizeof(Room));
                    if (room==NULL){
                        printf("\033[1;31mError in dyanmic allocation.\033[0m\n");
                    }
                    else{
                    LoadRooms(fptr,room);
                   fclose(fptr);
                   char roomnum[5];
                   sprintf(roomnum, "%d", ROOMNI);

                   int indexx = findRoom(room,roomnum,count);
                   if(strcmp(room[indexx].status,"Available")==0){printf("\033[1;31mRoom is already available, unable to cancel.\033[0m\n");
                   CancelReservation();}
                  else{strcpy(room[indexx].status,"Available");



                  printf("\033[1;33mAre you sure you want to delete room %d record? Enter 'Y' for yes and 'N' for no.\033[0m\n",ROOMNI);
                  scanf("%s",c);
                  getchar();
                  if (strcmp(c,"n")==0 || strcmp(c,"N")==0){MainMenu();}

                  else if(strcmp(c,"y")==0 || strcmp(c,"Y")==0){


                    fptr=fopen("Room.txt","w");
                   if (fptr == NULL ){printf("\033[1;31mError in opening room text file.\033[0m");}
                   else{

                    saveRooms(fptr,room,count); //to write the rooms again into the file but with "Available"
                   fclose(fptr);

                  fptr=fopen("Reservation.txt","r");
                  if (fptr==NULL){printf("\033[1;31mError in opening reservation file.\033[0m\n");}
                    else {
                            count = countlines(fptr);
                            reservation *res = malloc(count*sizeof(reservation)); ////check for dynamic allocation
                            load(res);

                 fclose(fptr);

                       ////deleting records

                 fptr=fopen("Reservation.txt","w");
                  if (fptr == NULL) {printf("\033[1;31mError in writing into the reservation file again.\033[0m\n");}

                else{ for (int i = 0; i < count; i++) {

      if (i != index && i!=(count-1)) {                                  // Skip the reservation at the specified index
            saveRes(fptr,&res[i]);
            fprintf(fptr,"\n",res);// Save this line only, it will loop through each line
       }
     if (i == count-1 && i!=index){saveRes(fptr,&res[i]);} }
            printf("\033[1;32mThe record for the Room %d is deleted.\033[0m\n",ROOMNI);
            fclose(fptr);
            menuOrExit();}}}


       }else {printf("\033[1;31mInvalid input, please try again.\033[0m\n");menuOrExit();}}}}


       }
       else {printf("\033[1;31mReservation is confirmed, cannot cancel.\033[0m\n"); menuOrExit();}}
        }


  }
   else if (strcasecmp(s,"ID")==0 || strcasecmp(s,"id") == 0 || strcasecmp(s,"Id") == 0) {
       int RESIDI=0,index=-1,j=0,ROOMNI=0,count=0,c1=0;
       char RESID[8],c[2];
     reservation r[256];

  reservation *fptr = &r[index];
  if (fptr == NULL) {printf("\033[1;31mError in opening reservation file.\033[0m\n");}
  else {
 printf("\033[1;34mPlease enter your reservation ID to cancel: \033[0m");
    scanf("%s", &RESID);
    RESIDI=atoi(RESID);
    getchar(); //otherwise, it will repeat the cancel reservation function if it returned to it

    load(r);
       while(strcmp(r[j].reservationID,"")){

        if(!(strcmp(RESID,r[j].reservationID))){
            index=j;

            break;
        }
        j++;
    }
    if(index==-1){
        printf("\033[1;31mReservation ID not found\033[0m\n");
        printf("If you want to re-do the process, enter '1', if you want to return to the main menu, enter '2', and if you want to exit enter '3'\n");
        scanf("%d",&c1);
        getchar();
            if (c1 == 1) CancelReservation();
            else if (c1 == 2) MainMenu();
            else if (c1 == 3) exit(1);
            else {printf("\033[1;31mInvalid input, returning to main menu.\033[0m\n"); MainMenu();}}

        if (!(strcmp(RESID,r[index].reservationID))){
             if (strcmp(r[index].reserveStatus,"unconfirmed")==0){
                    ROOMNI=atoi(r[index].roomNum);
                FILE *fptr=fopen("Room.txt","r");
                if (fptr == NULL ){printf("\033[1;31mError in opening room text file.\033[0m\n");}
                    else {
                    count = countlines(fptr);
                    Room *room = malloc(count*sizeof(Room));
                    LoadRooms(fptr,room);

                   fclose(fptr);
                   char roomnum[5];
                   sprintf(roomnum, "%d", ROOMNI);
                   int indexx = findRoom(room,roomnum,count);
                   if(strcmp(room[indexx].status,"Available")==0){printf("\033[1;31mRoom is already available, unable to cancel.\033[0m\n");menuOrExit();}
                  else{strcpy(room[indexx].status,"Available");

                  printf("\033[1;31mAre you sure you want to delete room %d record? Enter 'Y' for yes and 'N' for no.\033[0m\n",ROOMNI);
                  scanf("%s",c);
                  getchar();
                  if (strcmp(c,"n")==0 || strcmp(c,"N")==0){MainMenu();}

                  else if(strcmp(c,"y")==0 || strcmp(c,"Y")==0){

                    fptr=fopen("Room.txt","w");
                   if (fptr == NULL ){printf("\033[1;31mError in opening room text file.\033[0m");}
                   else{

                    saveRooms(fptr,room,count); //to write the rooms again into the file but with "Available"
                   fclose(fptr);

                  fptr=fopen("Reservation.txt","r");
                  if (fptr==NULL){printf("\033[1;31mError in opening reservation file.\033[0m\n");}
                    else {
                            count = countlines(fptr);

                            reservation *res = malloc(count*sizeof(reservation));
                            load(res);

                 fclose(fptr);

                       ////deleting records

                 fptr=fopen("Reservation.txt","w");
                  if (fptr == NULL) {printf("\033[1;31mError in writing into the reservation file again.\033[0m\n");}
               else{
                  for (int i = 0; i < count; i++) {
        if (i != index && i!=count-1) {                                  // Skip the reservation at the specified index

            saveRes(fptr,&res[i]);
            fprintf(fptr,"\n",res);// Save this line only, it will loop through each line
            } if (i == count-1 && i!=index){saveRes(fptr,&res[i]);}}
            printf("\033[1;32mThe record for the ID %d, room %d is deleted.\033[0m\n",RESIDI,ROOMNI);

                       menuOrExit();
                }}}}
                else {printf("\033[1;31mInvalid input, returning to main menu.\033[0m\n");menuOrExit();}

       }}}}
       else {printf("\033[1;31mReservation is confirmed, cannot cancel.\033[0m\n"); menuOrExit();}}}

   else {printf("\033[1;31mAn error occured, try again please.\033[0m\n"); menuOrExit();}}

//******check out */
void Checkout(){
reservation r[256];
int bills=1,j=0,count=0,index=-1,ROOMNI=0,total_bills=0,price=0,indexx=0,c1=0,c2=0;
char ROOMN[5],c[2];

reservation *fptr = &r[index];
  if (fptr == NULL) {printf("\033[1;31mError in opening reservation file.\033[0m");}
  else {
    printf("\033[1;34mPlease enter the room number: \033[0m");
    scanf("%s", &ROOMN);
    getchar();
    ROOMNI=atoi(ROOMN);
            //the enter after writing the room number get in the way if the room is already available
load(r);
       while(strcmp(r[j].roomNum,"")){

        if(!(strcmp(ROOMN,r[j].roomNum))){
            index=j;

            break;
        }
        j++;
    }
    if(index==-1){
        printf("\033[1;31mRoom number not found.\033[0m\n");
        printf("If you want to re-do the process, enter '1', if you want to return to the main menu, enter '2', and if you want to exit enter '3'\n");
        scanf("%d",&c1);
        getchar();
            if (c1 == 1) Checkout();
            else if (c1 == 2) MainMenu();
            else if (c1 == 3) exit(1);
            else {printf("\033[1;31mInvalid input, returning to main menu.\033[0m\n"); MainMenu();}
        }

if (!(strcmp(ROOMN,r[index].roomNum))){
             if (strcmp(r[index].reserveStatus,"confirmed")==0){
                    FILE *fptr=fopen("Reservation.txt","r");
                    if (fptr==NULL){printf("\033[1;31mError in opening reservation file.\033[0m\n");}
                    else {

                            count = countlines(fptr);

                            reservation *res = malloc(count*sizeof(reservation));
                            load(res);

         int CheckInYear=0,CheckInMonth=0,CheckInDay=0,daysforbills=0;
            char date[50];
            strcpy(date,r[index].stringdate);

            parseCheckinDate(date, r[index].checkinDate);

                CheckInYear = r[index].checkinDate->year;
                CheckInMonth = r[index].checkinDate->month;
              CheckInDay = r[index].checkinDate->day;

            time_t t = time(NULL);

               struct tm *now = localtime(&t);
               int CurrentDay = now->tm_mday;
               int CurrentMonth = now->tm_mon + 1;
               int CurrentYear = now->tm_year + 1900;



    if (CheckInYear > CurrentYear || (CurrentYear == CheckInYear && CurrentMonth < CheckInMonth) || (CurrentYear == CheckInYear && CurrentMonth == CheckInMonth && CurrentDay < CheckInDay)){
                printf("\033[1;31mCheck-in date did not come yet.\033[0m\n"); Checkout();
               }


   if (CurrentYear == CheckInYear && CurrentMonth==CheckInMonth){
        daysforbills = CurrentDay - CheckInDay;
    }
  else if (CheckInYear == CurrentYear) {
        for (int month = CheckInMonth; month < CurrentMonth; month++) {
            daysforbills += days_in_month(CurrentYear, month); // Add full months between
        }
        daysforbills += CurrentDay - CheckInDay; // Add days in the current month
    }
    // Case 3: Different years
    else {
        // Calculate days from CheckInYear to the end of CheckInYear
        int days_in_check_in_year = days_from_start_of_year(CheckInYear, 12, 31) -
                                    days_from_start_of_year(CheckInYear, CheckInMonth, CheckInDay);

        // Calculate full days for years between CheckInYear and CurrentYear
        int days_in_full_years = 0;
        for (int year = CheckInYear + 1; year < CurrentYear; year++) {
            days_in_full_years += 365 + ( (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) ); }

        // Calculate days in CurrentYear
        int days_in_current_year = days_from_start_of_year(CurrentYear, CurrentMonth, CurrentDay);

        // Add all days together
        daysforbills = days_in_check_in_year + days_in_full_years + days_in_current_year;
    }
               fclose(fptr);

            fptr=fopen("Room.txt","r");
                if (fptr == NULL ){printf("Error in opening room text file.");}
                    else {
                    count = countlines(fptr);

                    Room *room = malloc(count*sizeof(Room));
                    LoadRooms(fptr,room);
                   fclose(fptr);
                   char roomnum[5];
                   sprintf(roomnum, "%d", ROOMNI);
                   int indexx = findRoom(room,roomnum,count);

                   strcpy(room[indexx].status,"Available");
                   bills=room[indexx].price;

                   total_bills=bills*daysforbills;
                   printf("The total bill is equal to: %d$\n",total_bills);
                   fclose(fptr);

              printf("\033[1;31mAre you sure you want to delete room %d record? Enter 'Y' for yes and 'N' for no.\033[0m\n",ROOMNI);
                  scanf("%c",c);

                  if ( (strcmp(c,"N")==0) || (strcmp(c,"n")==0)){MainMenu();}

                  else if((strcmp(c,"Y")==0) || (strcmp(c,"y")==0)){


                   fptr=fopen("Room.txt","w");
                   if (fptr == NULL ){printf("Error in opening room text file.\n");}
                   else{

                    saveRooms(fptr,room,count);
                    //to write the rooms again into the file but with "Available"
                   fclose(fptr);

                      fptr=fopen("Reservation.txt","r");
                    if (fptr==NULL){printf("Error in opening reservation file.\n");}
                    else {

                            count = countlines(fptr);
                            fclose(fptr);
                           
                       ////deleting records

               FILE *fptr1=fopen("Reservation.txt","w");
                  if (fptr == NULL) {printf("Error in writing into the reservation file again.\n");}

                 else{
                        for (int i = 0; i < count; i++) {

      if (i != index && i!=(count-1)) {                         // Skip the reservation at the specified index
            saveRes(fptr1,&res[i]);

            fprintf(fptr1,"\n",res);// Save this line only, it will loop through each line
       }
     if (i == count-1 && i!=index){saveRes(fptr1,&res[i]);} }
            printf("\033[1;32mThe record for the room %d is deleted.\033[0m\n",ROOMNI);
            fclose(fptr1);

            menuOrExit();

        }}}}
        else{MainMenu;}}}}

                else {printf("\033[1;31mThis room is unconfirmed, cannot check out\033[0m\n");
                Checkout();}}
                else {printf("\033[1;31mRoom number is not found.\033[0m\n"); Checkout();}}}
//******room availability */
void RoomAvailability(){
    char search[256];
    int flag=1, i;
    Room rooms[256];
    FILE *fptr=fopen("Room.txt", "r");
    int lines=countlines(fptr);
    LoadRooms(fptr,rooms);
    fclose(fptr);

                printf("\033[1;33mAvailable rooms are: \033[0m\n");
                for(i=0;i<lines;i++){
                    if(!strcmp(rooms[i].status, "Available"))
                        printf("%d %s %s %d\n",rooms[i].number,rooms[i].status,rooms[i].roomCategory,rooms[i].price);}

                printf("\033[1;33mReserved rooms are: \033[0m\n");
                for(i=0;i<lines;i++){
                    if(!strcmp(rooms[i].status, "Reserved"))
                        printf("%d %s %s %d\n",rooms[i].number,rooms[i].status,rooms[i].roomCategory,rooms[i].price);}

    menuOrExit();
}

//******details */
void details(){
    int flag=1, index=-1, j=0;
    char search[10];
    char reserveId[7], roomNum[5];
    reservation r[256];
    while(flag){
        printf("Enter 1 for reservation ID search and 2 for room number search: ");
        gets(search);
        while(!isdigit(search[0])||strlen(search)!=1){
                printf("Wrong entry, enter 1 or 2: ");
                gets(search);
            }
        search[0]=atoi(search);
        switch(search[0]){
            case 1:
                printf("Enter reservation ID: ");
                scanf("%s", reserveId);
                flag=0;
                break;
            case 2:
                printf("Enter room number: ");
                scanf("%s", roomNum);
                flag=0;
                break;
        }
    }
    load(r);
    while(strcmp(r[j].reservationID,"")||strcmp(r[j].roomNum,"")){
        if(!strcmp(reserveId,r[j].reservationID)){
            index=j;
            break;
        }
        if(!strcmp(roomNum,r[j].roomNum)){
            index=j;
            break;
        }
        j++;
    }
    if(index==-1)
        printf("Reservation ID/room number not found.");
    else{
        printf("Name of customer: %s\n", r[index].custName);
        printf("Email: %s\n", r[index].email);
        printf("Mobile number: %s", r[index].mobileNum);
    }
    menuOrExit();
}

//****change reservation details*/
void changeReservation(){
   
    FILE *res = fopen("Reservation.txt","r"); //reservation
    int lines = countlines(res); //lines in reservation
    fclose(res);
    
    reservation *all = malloc(lines*sizeof(reservation)); //all people
    load(all);
  
    int f = findRoom_NumorID(all,lines);
    printReservation(&all[f]);
    printf("%d\n",f);
    if(f == -1){
        return;
        }

    //found
    //load Rooms file
         FILE* Rooms = fopen("Room.txt","r");
        int count = countlines(Rooms);//lines in Rooms
        Room* rooms = malloc(count*sizeof(Room)); // all rooms
        LoadRooms(Rooms,rooms);
        fclose(Rooms); 
        

//print reservation
while(1){
int x = enterchangereserve(&all[f],lines,rooms,count);
if(x == -1){
    return;
}
printReservation(&all[f]);
        printf("New Details");
        
printf("is the data correct if no u will be prompted to enter the data again \n");
printf("y/n/e: ");
char finalconfirm;
scanf(" %c",&finalconfirm);
while(finalconfirm !='n'&&finalconfirm !='y'&&finalconfirm !='e'){
    printf("Invalid choice\n");
    printf("y/n/e: ");
    scanf(" %c",&finalconfirm);
}
if(finalconfirm == 'n'){
    printf("Enter the data again:\n");
    getchar();
    
}

if(finalconfirm == 'e'){
    exit(1);
}
else if (finalconfirm == 'y'){
    printf("GREAT!\n");
    break;
    }
     
        }

        //save rooms 
        Rooms = fopen("Room.txt","w");
         saveRooms(Rooms,rooms,count);
         fclose(Rooms);
         res = fopen("Reservation.txt","w");
         for(int z = 0;z<lines;z++){
            //save customers
         writeCustomer(res,&all[z]);
         if(z!=(lines-1)){
            fprintf(res,"\n");
         }}

         fclose(res);
         menuOrExit();
    }

 //****Query */
 void query(){
    char search[256];
    int flag=1;
    while(flag){
        printf("\033[1;34mWhich would you like to search about?\033[0m\n");
        printf("1. Reservation details and customer information, using customer name.\n");
        printf("2. Current status of room, using room number\n");
        printf("3. Available or occupied rooms, using room status.\n");
        gets(search);
        while(!isdigit(search[0])||strlen(search)!=1){
                printf("\033[1;31mWrong entry, enter 1, 2 or 3:\033[0m ");
                gets(search);
            }
        switch(search[0]){
            case '1':
                searchName();
                flag=0;
                break;
            case '2':
                searchRoomNum();
                flag=0;
                break;
            case '3':
                searchRoomStatus();
                flag=0;
                break;
            default:
                printf("\033[1;31mWrong entry, enter 1. 2 or 3:\033[0m ");
        }
    }
    menuOrExit();
}

//*****report by date*/
void printbydate(){
    int x = 1;
    char searchDate[11];
    date search;
    while(x){
    printf("\n");
    clearScreen();
    getchar();
    printf("Please enter the date:(dd-mm-yyyy) ");
    fgets(searchDate,sizeof(searchDate),stdin);
     searchDate[strcspn(searchDate, "\n")] = '\0';
    while(!validateSearchDate(searchDate,&search)){
        
        printf("Wrong date Please try again:");
        fgets(searchDate,sizeof(searchDate),stdin);
        searchDate[strcspn(searchDate, "\n")] = '\0';
        
        //printf("%s\n",searchDate);
        
    }
    clearScreen();
    printf("\n");
    while (1)
        {
            char confirm;
            printf("Date you entered= %d/%d/%d\n",search.day,search.month,search.year);
        printf("is it correct (yes =y,n = no enter date agin , e = close code): (y/n/e)");
            scanf(" %c",&confirm);
            //getchar();
            if(confirm == 'y'){
             printf("GREAT!");
             x= 0;
             break;}
                //x =1;
                
                else if (confirm !='y' && confirm!='n'&& confirm!='e'){
                    printf("Invalid choice\n");
                    x =1;
                continue;
                    }
                    else if(confirm == 'n'){
            x = 1;
            break;

        }
        
        else if(confirm == 'e'){
            exit(1);
        }
        
} }
    //printf("\n");
    //clearScreen();
    int flag  = 0;
    FILE *fptr = fopen("Reservation.txt","r");
    if(fptr == NULL){
        printf("Could not open file\n");
        return ;
    }
    int lines = countlines(fptr);
    //printf("lines = %d",lines);
    fclose(fptr);
    reservation* reservations = malloc(lines * sizeof(reservation));
    load(reservations);
    fptr = fopen("Room.txt","r");
    if(fptr == NULL){
        printf("Could not open file\n");
        getchar();
        return ;
        }
    int roomlines = countlines(fptr);
    Room *rooms = malloc(roomlines*(sizeof(Room)));
    LoadRooms(fptr,rooms);
    fclose(fptr);
   
    clearScreen();
    printf("\n");
    for(int i = 0; i < lines; i++){
        splitDate(reservations[i].stringdate,reservations[i].checkinDate);

        if((search.day == reservations[i].checkinDate->day)&&(search.month == reservations[i].checkinDate->month)&&(search.year == reservations[i].checkinDate->year)){
        int room = findRoom(rooms,reservations[i].roomNum,roomlines);
        strcpy(reservations[i].RoomCategory,rooms[room].roomCategory);
        printReservation(&reservations[i]);
        printf("\n\t***************************************************\t\n");
        flag = 1;
       
        }
   
}
      if(flag == 0){
            printf("No reservations found for the given date\n");
         }
   //getchar(); 
menuOrExit();
}
 