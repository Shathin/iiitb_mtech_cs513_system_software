#ifndef ADMIN
#define ADMIN

struct admin
{
    short int adminID;   // Auto-generated admin ID : 0, 1, 2, ....
    char adminName[20]; // Name of the admin
    char loginID[25];    // Format : adminName-adminID
    char password[100];  // Password of the admin [Experimental - Store hash of the password plain-text]
};

#endif