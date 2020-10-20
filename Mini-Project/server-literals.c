#define initialPrompt "Welcome to Spooks bank!\nWho are you?\n1. Admin\t2. Customer\t3.Exit\nEnter the number to choose!" 

// Login Prompts ======================
// Admin Login Prompt (alp)

#define alpWelcome "Welcome admin! Enter your credentials to gain administrator access!\n" 
#define alpFailedDeactived "Your access has been revoked ex-admin "  // This string is to be concatenated with the ex-admin's name
#define alpSuccessful "Hello there admin "  // This string is to be concatenated with the admin's name

// Customer Login Prompt (clp)
#define clpWelcome "Welcome dear customer! Enter your credentials to gain access to your account!\n" 
#define clpFailedDeactived "Your access has been revoked dear customer! Please contact the bank to re-activate it!\n" 
#define clpSuccessful "Hello there dear customer "  // This string is to be concatenated with the customer's name

// Common login prompt (lp)
#define lpLogin "Enter your login ID: " 
#define lpPassword "Enter your password: " 
#define lpFailedCredentials "It seems that you have entered the wrong credentials!" 

// ====================================

// Admin Menu =========================

#define adminMainMenu "\n1. Add a new account \n2. Delete an account\n3. Modify customer information \n4. Modify account information \n5. Get customer details \n6. Get account details 7. Logout\n" 

// Add account menu (acm)
#define acmTitle "Enter account details - " 
#define acmPromptAccountType "What's the account type? Enter 1 for regular account or 2 for joint account\n" 
#define acmPromptCustomerInfo "Does the customer already hold an account in the bank? Enter 1 for yes and 0 for no\n" 
#define acmPrompt 
// ====================================
