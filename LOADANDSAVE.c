#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "reservation.h"
#include "FUNCNAME.h"
//load users.txt
int loadUsers( user **users, int *user_count ){

    FILE *ptr;
    ptr= fopen("users.txt", "r");

    if(!ptr) {
        printf("\033[1;31mCould not open users.txt file.\033[0m\n");
        return 0;
    }

    *users = (user *)malloc(50 * sizeof(user)); // 50 refers to the maximum amount of users
    if(*users == NULL) {
        printf("\033[1;31mMemory allocation failed.\033[0m\n");
        fclose(ptr);
        return 0;
    }

    char line[100];
    *user_count = 0;

    while (fgets(line, sizeof(line), ptr) && *user_count < 50) {
        sscanf(line, "%s %s", (*users)[*user_count].fileusername, (*users)[*user_count].filepassword);
        (*user_count)++;
    }

    fclose(ptr);
    return 1;

}
//load reservation.txt
void load(reservation* r){
   
    const char del[2]=",";
    
    int i=0;
    FILE *fptr=fopen("Reservation.txt", "r");
    if(fptr==NULL){
        printf("File could not be found.");
        exit(1);
    }
    //malloc pls?
    char str[256];
    while(!feof(fptr)){
        
        fgets(str,256,fptr);
        //no \n in line
        str[strcspn(str, "\n")] = '\0';
        
        char *token=strtok(str,del);
       
        if(token!=NULL)
            strcpy(r[i].reservationID,token);
        token=strtok(NULL,del);
        
        if(token==NULL){
            printf("Error in pointer1\n");
        }
      
            strncpy(r[i].roomNum,token,sizeof(r[i].roomNum)-1) ;
                r[i].roomNum[sizeof( r[i].roomNum) - 1] = '\0'; 
            
        token=strtok(NULL,del);
        
        if(token==NULL){
            printf("Error in pointer2\n");
            return;
        }

            strcpy(r[i].reserveStatus,token);
            
            

           
        token=strtok(NULL,del);
        
        if(token!=NULL)
            strcpy(r[i].custName,token);
           
        token=strtok(NULL,del);
        
        if(token!=NULL)
            strcpy(r[i].nationalId,token);
         
        token=strtok(NULL,del);
       
        if(token!=NULL)
            strcpy(r[i].nightNum,token);
          
        token=strtok(NULL,del);
        
        if(token!=NULL){
             //check in date
            strcpy(r[i].stringdate,token);
           
             
            }
        
        token=strtok(NULL,del);
        
        if(token!=NULL)
            strcpy(r[i].email,token);
           
        token=strtok(NULL,del);
        
        if(token!=NULL)
            strcpy(r[i].mobileNum,token);
           
       
               
            i++;
    }
    fclose(fptr);
}
//count lines in files
int countlines(FILE* file){
    if (file == NULL) {
        printf("Could not open file\n");
        return 0;
        }
        char line[100];
        //get number of lines in file
        int count = 0;
        while (!feof(file)){
            char c = fgetc(file);
            if (c == '\n'){
            count++;}
        }
        rewind(file); //reset pointer to start of file
        return count+1;
        

}
//load Rooms.txt
void LoadRooms(FILE *file,Room *rooms){
        int i = 0 ;
        char line[100];
        
        while (fgets(line, sizeof(line), file) != NULL) {
            //room number
            line[strcspn(line, "\n")] = '\0';
              if(line == NULL){
                continue;
            }
            char *ptr = strtok(line, " ");
            if(ptr == NULL){
                printf("error in pointer-12");
                return ;
            } 
            rooms[i].number = atoi(ptr);
            //room status
            ptr = strtok(NULL, " ");
            if(ptr == NULL){
                printf("error in pointer-11");
                return ;
                }
                strncpy(rooms[i].status,ptr,sizeof(rooms[i].status)-1) ;
                rooms[i].status[sizeof( rooms[i].status) - 1] = '\0';
            
            //categery
            ptr = strtok(NULL, " ");
            if(ptr == NULL){
                printf("error in pointer-10");
                return ;
                }
                strncpy(rooms[i].roomCategory,ptr,sizeof(rooms[i].roomCategory)-1) ;
                rooms[i].roomCategory[sizeof( rooms[i].roomCategory) - 1] = '\0';
           
            //room price
            ptr = strtok(NULL, " ");
            if(ptr == NULL){
                printf("error in pointer-9");
                return ;
                }
                rooms[i].price = atoi(ptr);
            i++;
            }
            
}
//save customer
void writeCustomer(FILE* file,reservation*all){
 
    fprintf(file,"%s,",all->reservationID);
    fprintf(file,"%s,",all->roomNum);
    fprintf(file,"%s,",all->reserveStatus);
    fprintf(file,"%s,",all->custName);
    //printf("%s",all->nationalId);
    fprintf(file,"%s,",all->nationalId);
    fprintf(file,"%s,",all->nightNum);
    fprintf(file,"%s,",all->stringdate);
    fprintf(file,"%s,",all->email);
    fprintf(file,"%s",all->mobileNum);
    

   
}
//save rooms
void saveRooms(FILE* file,Room * rooms,int count){
    for (int i = 0;i<count;i++){
        fprintf(file,"%d %s %s %d",rooms[i].number,
        rooms[i].status,rooms[i].roomCategory,rooms[i].price);
        
        if(i!=count-1){
            fprintf(file,"\n");
        }}
}
//save resrvation
void saveRes(FILE *file, reservation *res) { //this function prints in the file the line I gave it to it, the res[i]
    fprintf(file,"%s,%s,%s,%s,%s,%s,%s,%s,%s",res->reservationID,res->roomNum,res->reserveStatus,res->custName,res->nationalId,res->nightNum,res->stringdate,res->email,res->mobileNum);
}