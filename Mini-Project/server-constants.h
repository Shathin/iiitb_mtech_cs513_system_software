#ifndef SERVER_CONSTANTS
#define SERVER_CONSTANTS


#define INITAL_PROMPT "Welcome to Spooks bank!\nWho are you?\n1. Admin\t2. Customer\t3.Exit\nEnter the number corresponding to the choice!"

// ========== COMMON TEXT =============================

// LOGIN
#define LOGIN_ID "Enter your login ID"
#define PASSWORD "Enter your password"
#define INVALID_LOGIN "The login ID specified doesn't exist!$"
#define INVALID_PASSWORD "The password specified doesn't match!$"

// GET ACCOUNT DETAILS
#define GET_ACCOUNT_NUMBER "Enter the account number of the account you're searching for"
#define GET_CUSTOMER_ID "Enter the customer ID of the customer you're searching for"



// ====================================================

// ========== ADMIN SPECIFIC TEXT======================

// LOGIN WELCOME
#define ADMIN_LOGIN_WELCOME "Welcome dear admin! With great power comes great responsibility!\nEnter your credentials to unlock this power!"
#define ADMIN_LOGIN_SUCCESS "Welcome superman!"

// ADMIN MENU
#define ADMIN_MENU "1. Get Customer Details\n2. Get Account Details\n3. Add Account\n4. Delete Account\n5. Modify Customer Information\nPress any other key to logout"

// ADD CUSTOMER
#define ADMIN_ADD_CUSTOMER_PRIMARY "Enter the details for the primary customer\n"
#define ADMIN_ADD_CUSTOMER_SECONDARY "Enter the details for the secondary customer\n"
#define ADMIN_ADD_CUSTOMER_NAME "What is the customer's name?"
#define ADMIN_ADD_CUSTOMER_GENDER "What is the customer's gender?\nEnter M for male, F for female and O for others"
#define ADMIN_ADD_CUSTOMER_AGE "What is the customer's age?"
#define ADMIN_ADD_CUSTOMER_AUTOGEN_LOGIN "The autogenerated login ID for the customer is : "
#define AUTOGEN_PASSWORD "spookytime" // append to end of next string macro
#define ADMIN_ADD_CUSTOMER_AUTOGEN_PASSWORD "The autogenerated password for the customer is : "

// ADD ACCOUNT
#define ADMIN_ADD_ACCOUNT_TYPE "What type of account is to be created? Enter 1 for regular account and 2 for joint account"
#define ADMIN_ADD_ACCOUNT_NUMBER "The newly created account's number is :"

// DELETE ACCOUNT
#define ADMIN_DEL_ACCOUNT_NO "What is the account number of the account you want to delete?"
#define ADMIN_DEL_ACCOUNT_SUCCESS "This account has been successfully deleted"
#define ADMIN_DEL_ACCOUNT_FAILURE "This account cannot be deleted since it still has some money"

// MODIFY CUSTOMER INFO
#define ADMIN_MOD_CUSTOMER_ID "Enter the ID of the customer who's information you want to edit"
#define ADMIN_MOD_CUSTOMER_MENU "Which information would you like to modify?\n1. Name 2. Age 3. Gender \nPress any other key to cancel"
#define ADMIN_MOD_CUSTOMER_NEW_NAME "What's the updated value for name?"
#define ADMIN_MOD_CUSTOMER_NEW_GENDER "What's the updated value for gender?"
#define ADMIN_MOD_CUSTOMER_NEW_AGE "What's the updated value for age?"

// ====================================================

// ========== CUSTOMER SPECIFIC TEXT===================

// LOGIN WELCOME
#define CUSTOMER_LOGIN_WELCOME "Welcome dear customer! Enter your credentials to gain access to your account!"
#define CUSTOMER_LOGIN_SUCCESS "Welcome beloved customer!"

// ====================================================

#endif