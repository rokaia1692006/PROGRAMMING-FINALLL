#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "reservation.h" // Ensure this header file defines the user, Room, and reservation types
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function declarations
void MainMenu();
int firstmenuLogin();
void menuOrExit();
void reserve();
void CancelReservation();
void Checkout();
void RoomAvailability();
void details();
void changeReservation();
void query();
void printbydate();

int login(user *users, int user_count);
int findRoom(Room* rooms, char NUM[], int count);
void parseCheckinDate(const char *checkinDateStr, date *checkinDate);
int splitDate(char checkinDate[], date* destination);
void load(reservation* r);
void saveRooms(FILE *file, Room *rooms, int count);
void writeCustomer(FILE *file, reservation *customer);
void loadRooms(FILE *file, Room *rooms);
int countlines(FILE *file);
void clearScreen(); 
int findReservation(reservation *r, char NUM[], int count); // Corrected function declaration

#endif // FUNCTIONS_H