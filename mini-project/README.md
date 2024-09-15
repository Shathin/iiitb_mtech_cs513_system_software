# Mini-Project - Design & Development of Online Banking Management System

## Title - Design and Development of online banking management system

### Description

The project aims to develop a banking system that is user-friendly and multifunctional. The project should have the following functionalities:

1. All account transactional details and customer information are stored in files.
2. Account holders have to pass through a login system to enter their accounts.
3. The application should possess password-protected administrative access; thus preventing the whole management system from unauthorized access.
4. Three types of login should be created: normal user, joint account user; administrator;
5. Once you login as administrator, you should be able to add, delete, modify, search for a specific account details.
6. Once the customer connect to the server, you should get login and password prompt.
7. After successful login, you should get menu for example:

    Do you want to:

    - Deposit
    - Withdraw
    - Balance Enquiry
    - Password Change
    - View details
    - Exit
8. If you login as a joint account holder, proper file locking should be implemented. If you want to view the account details then read lock is to be set else if you want to withdraw or deposit then write lock should be used to protect the critical data section.
9. Use socket programming – Server maintains the data base and service multiple clients concurrently. Client program can connect to the server and access their specific account details.
10. Use system calls instead of Library functions wherever it is possible in the project: Process Management, File Management, File Locking, Multithreading and Inter  Process Communication Mechanisms.

---

## How to execute?

Step 1: Get the server up and running   
- Compile the server program  
    ```
        gcc server.c -o server.out -lcrypt
    ```
- Run the server program
    ```
        ./server.out
    ```

Step 2: Run the client program
- Compile the client program
    ```bash
        gcc client.c -o client.out
    ```
- Run the client program for every user
    ```bash
        ./client.out
    ```
- Credentials to login as the admin  
    - Login ID : `Spooks`
    - Password : `420boo69`
- The credentials to login as the bank's customer will be displayed during each new customer's account creation.  

Step 3: ???  

Step 4: Profit
