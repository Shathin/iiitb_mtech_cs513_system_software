#ifndef SERVER_LITERALS
#define SERVER_LITERALS
const char *initialPrompt = "Welcome to Spooks bank!\nWho are you?\n1. Admin\t2. Customer\t3.Exit\nEnter the number to choose!";

// Login Prompts ======================
// Admin Login Prompt (alp)

const char *alpWelcome = "Welcome admin! Enter your credentials to gain administrator access!";
const char *alpFailedDeactived = "Your access has been revoked ex-admin"; // This string is to be concatenated with the ex-admin's name
const char *alpSuccessful = "Hello there admin "; // This string is to be concatenated with the admin's name

// Customer Login Prompt (clp)
const char *clpWelcome = "Welcome dear customer! Enter your credentials to gain access to your account!";
const char *clpFailedDeactived = "Your access has been revoked dear customer! Please contact the bank to re-activate it!";
const char *clpSuccessful = "Hello there dear customer "; // This string is to be concatenated with the customer's name

// Common login prompt (lp)
const char *lpLogin = "Enter your login ID";
const char *lpPassword = "Enter your password";
const char *lpFailedCredentials = "It seems that you have entered the wrong credentials!";

// ====================================

// Admin Menu =========================

const char *adminMainMenu = "\n1. Add a new account \n2. Delete an account\n3. Modify customer information \n4. Modify account information \n5. Get customer details \n6. Get account details 7. Logout";

// Add account menu (acm)
const char *acmTitle = "Enter account details";
const char *acmCustomerExists = "Is the client already a part of the bank? Type in 'y' for yes and 'n' for no.";
const char *acmAccountType = "What's the account type? Enter 1 for regular account or 0 for joint account";
const char *acmAccountTypeInvalid = "It seems you've entered an invalid input! Please try again!";
const char *acmPromptCustomerInfo = "Does the customer already hold an account in the bank? Enter 1 for yes and 0 for no";
const char *acmCustomerID = "What is the customer's ID?/"; 
const char *acmAccountCreationError = "There was an error during account creation. Please try again!";
const char *acmAccountCreationSuccess = "The account for the customer was successfully created. The details are as follows:"; 

// 

// ====================================

#endif