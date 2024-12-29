#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
        int day;
        int month;
        int year;
}date;

typedef struct{
    char reservationID[7];
    char roomNum[5];
    char reserveStatus[15];
    char custName[50];
    char nationalId[15];
    char nightNum[5];
    date checkindate;
    char stringdate[12];
    char email[50];
    char mobileNum[13];
}reservation;

void load(reservation r[]){
    const char del[2]=",";
    int i=0;
    FILE *fptr=fopen("Reservation.txt", "r");
    if(fptr==NULL){
        printf("\033[1;31mFile could not be found.\033[0m");
        exit(1);
    }
    char str[256];
    while(!feof(fptr)){
        fgets(str,256,fptr);
        char *token=strtok(str,del);
        if(token!=NULL)
            strcpy(r[i].reservationID,token);
        token=strtok(NULL,del);
        if(token!=NULL)
            strcpy(r[i].roomNum,token);
        token=strtok(NULL,del);
        if(token!=NULL)
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
        if(token!=NULL)
            strcpy(r[i].stringdate,token);
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

int countlines(FILE* file){
    if (file == NULL) {
        printf("\033[1;31mCould not open file\033[0m\n");
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



int compare_reservations(const void *a, const void *b) {
    reservation *r1 = (reservation *)a;
    reservation *r2 = (reservation *)b;

    if (r1->checkindate.year != r2->checkindate.year)

        return r1->checkindate.year - r2->checkindate.year;
    if (r1->checkindate.month != r2->checkindate.month)

        return r1->checkindate.month - r2->checkindate.month;
    return r1->checkindate.day - r2->checkindate.day;
}

void write_to_file(reservation r[], int numRecords) {
    FILE *fptr = fopen("Reservation.txt", "w");
    if (fptr == NULL) {
        printf("\033[1;31mCould not open file for writing.\033[0m\n");
        exit(1);
    }


    for (int i = 0; i < numRecords; i++) {
        fprintf(fptr, "%s,%s,%s,%s,%s,%s,%02d-%02d-%04d,%s,%s\n",
                r[i].reservationID,
                r[i].roomNum,
                r[i].reserveStatus,
                r[i].custName,
                r[i].nationalId,
                r[i].nightNum,
                r[i].checkindate.day,
                r[i].checkindate.month,
                r[i].checkindate.year,
                r[i].email,
                r[i].mobileNum);
    }

    fclose(fptr);
}



int main() {
    FILE *fptr = fopen("Reservation.txt", "r");
    if (fptr == NULL) {
        printf("\033[1;31mFile could not be found.\033[0m\n");
        return 1;
    }


    int numRecords = countlines(fptr);

    reservation r[numRecords];


    load(r);


    qsort(r, numRecords, sizeof(reservation), compare_reservations);




    fclose(fptr);
    return 0;
}

