#ifndef RESERVATION_H 
#define RESERVATION_H
typedef struct{
    int day;
    int month;
    int year;
}date;
typedef struct{
    char fileusername[50];
    char filepassword[50];

}user;
typedef struct{    
char reservationID[7];
    char roomNum[5];
    char reserveStatus[15];
    char custName[50];
    char nationalId[15];
    char nightNum[5];
    date checkinDate[12];
    char email[256];
    char mobileNum[13];
    char stringdate[12];
    char RoomCategory[12];
}reservation;

typedef struct 
{
    int number;
    char status[100];
    char roomCategory[100];
    int price;


}Room;
const char* domains []= {
    "alexu.edu.eg",
    "gmail.com",
    "yahoo.com",
    "hotmail.com",
    "outlook.com",
    "aol.com",
    "icloud.com",
    "protonmail.com",
    "protonmail.ch",
    "yandex.com",
    "mail.ru",
    "yahoo.co.uk",
    "yahoo.com.au",
    "yahoo.com.br",
    "yahoo.com.cn",
    "yahoo.com.hk",
    "yahoo.com.in",
    "yahoo.com.mx",
    "yahoo.com.sg",
    "yahoo.com.tr",
    "yahoo.com.tw",
    "yahoo.com.ua",
    "yahoo.com.vn",
    "yahoo.co.jp",
    "yahoo.co.kr",
    "yahoo.co.nz",
    "yahoo.co.th",
    "yahoo.co.uk",
    "yahoo.com.ar"
};
const char* phoneCompany[]={
    "011",
    "012",
    "015",
    "010"
};
const char* categories[]={
    "SeaView",
    "LakeView",
    "GardenView"
};

const char randomcharacter[] = {
    '1','2','3','4','5','6','7',
    '8','9','0'


};
#endif