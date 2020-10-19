struct customer
{
    int customerID;        // An auto-generated customer ID : 0, 1, 2, ....
    char loginID[40];      // Format : customerName-customerID
    char password[100];    // Password of the customer [Experimental - Store hash of the password plaintext]
    bool isActive;         // Is the customer active
    char customerName[30]; // The customer's name
    char customerGender;   // M -> male, F -> female, O -> other
    char customer_age;     // Age of the customer
    int accounts[];        // List of account numbers that the customer owns
};