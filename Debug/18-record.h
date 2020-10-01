// Structure of a record - Example: "Record A - 1\n"
struct record
{
    char *recordName; //  Ex: "Record A - " -> 12 bytes
    int someNumber;   // Ex: 1 -> sizeof(int) -> 4bytes
};

char *filename = "./sample-files/18-file"; // Name of the file used for storing records