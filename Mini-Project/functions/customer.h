#ifndef CUSTOMER_FUNCTIONS
#define CUSTOMER_FUNCTIONS

struct Customer loggedInCustomer;

// Function Prototypes =================================

bool customer_operation_handler(int connFD);
bool deposit(int connFD);
bool withdraw(int connFD);
bool get_balance(int connFD);
bool change_password(int connFD);

// =====================================================

// Function Definition =================================

// =====================================================

bool customer_operation_handler(int connFD)
{
    if (login_handler(false, connFD, &loggedInCustomer))
    {
        ssize_t writeBytes, readBytes;            // Number of bytes read from / written to the client
        char readBuffer[1000], writeBuffer[1000]; // A buffer used for reading & writing to the client
        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, CUSTOMER_LOGIN_SUCCESS);
        while (1)
        {
            strcat(writeBuffer, "\n");
            strcat(writeBuffer, CUSTOMER_MENU);
            writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
            if (writeBytes == -1)
            {
                perror("Error while writing CUSTOMER_MENU to client!");
                return false;
            }
            bzero(writeBuffer, sizeof(writeBuffer));

            readBytes = read(connFD, readBuffer, sizeof(readBuffer));
            if (readBytes == -1)
            {
                perror("Error while reading client's choice for CUSTOMER_MENU");
                return false;
            }

            int choice = atoi(readBuffer);
            switch (choice)
            {
            case 1:
                get_customer_details(connFD, loggedInCustomer.id);
                break;
            case 2:
                deposit(connFD);
                break;
            case 3:
                withdraw(connFD);
                break;
            case 4:
                get_balance(connFD);
                break;
            case 5:
                change_password(connFD);
                break;
            default:
                writeBytes = write(connFD, ADMIN_LOGOUT, strlen(ADMIN_LOGOUT));
                return false;
            }
        }
    }
    else
    {
        // CUSTOMER LOGIN FAILED
        return false;
    }
    return true;
}

bool deposit(int connFD)
{
    char readBuffer[1000], writeBuffer[1000];
    ssize_t readBytes, writeBytes;

    struct Account account;
    account.accountNumber = loggedInCustomer.account;

    long int depositAmount = 0;

    if (get_account_details(connFD, &account))
    {
        if (account.active)
        {

            writeBytes = write(connFD, DEPOSIT_AMOUNT, strlen(DEPOSIT_AMOUNT));
            // TODO : Add error checking

            bzero(readBuffer, sizeof(readBuffer));
            readBytes = read(connFD, readBuffer, sizeof(readBuffer));
            // TODO : Add error checking

            depositAmount = atol(readBuffer);
            if (depositAmount != 0)
            {
                account.balance += depositAmount;

                int accountFileDescriptor = open(ACCOUNT_FILE, O_WRONLY);
                off_t offset = lseek(accountFileDescriptor, account.accountNumber * sizeof(struct Account), SEEK_SET);

                struct flock lock = {F_WRLCK, SEEK_SET, offset, sizeof(struct Account), getpid()};
                int fcntlStatus = fcntl(accountFileDescriptor, F_SETLKW, &lock);
                // TODO : Add error checking

                writeBytes = write(accountFileDescriptor, &account, sizeof(struct Account));
                // TODO : Add error checking

                lock.l_type = F_UNLCK;

                write(connFD, DEPOSIT_AMOUNT_SUCCESS, strlen(DEPOSIT_AMOUNT_SUCCESS));
                read(connFD, readBuffer, sizeof(readBuffer)); // Dummy read

                get_balance(connFD);

                return true;
            }
            else
                writeBytes = write(connFD, DEPOSIT_AMOUNT_INVALID, strlen(DEPOSIT_AMOUNT_INVALID));
        }
        else
            write(connFD, ACCOUNT_DEACTIVATED, strlen(ACCOUNT_DEACTIVATED));
        read(connFD, readBuffer, sizeof(readBuffer)); // Dummy read
    }
    else
    {
        // FAIL
        return false;
    }
}
bool withdraw(int connFD)
{
    char readBuffer[1000], writeBuffer[1000];
    ssize_t readBytes, writeBytes;

    struct Account account;
    account.accountNumber = loggedInCustomer.account;

    long int withdrawAmount = 0;

    if (get_account_details(connFD, &account))
    {
        if (account.active)
        {

            writeBytes = write(connFD, WITHDRAW_AMOUNT, strlen(WITHDRAW_AMOUNT));
            // TODO : Add error checking

            bzero(readBuffer, sizeof(readBuffer));
            readBytes = read(connFD, readBuffer, sizeof(readBuffer));
            // TODO : Add error checking

            withdrawAmount = atol(readBuffer);
            if (withdrawAmount != 0 && account.balance - withdrawAmount >= 0)
            {
                account.balance -= withdrawAmount;

                int accountFileDescriptor = open(ACCOUNT_FILE, O_WRONLY);
                off_t offset = lseek(accountFileDescriptor, account.accountNumber * sizeof(struct Account), SEEK_SET);

                struct flock lock = {F_WRLCK, SEEK_SET, offset, sizeof(struct Account), getpid()};
                int fcntlStatus = fcntl(accountFileDescriptor, F_SETLKW, &lock);
                // TODO : Add error checking

                writeBytes = write(accountFileDescriptor, &account, sizeof(struct Account));
                // TODO : Add error checking

                lock.l_type = F_UNLCK;

                write(connFD, WITHDRAW_AMOUNT_SUCCESS, strlen(WITHDRAW_AMOUNT_SUCCESS));
                read(connFD, readBuffer, sizeof(readBuffer)); // Dummy read

                get_balance(connFD);

                return true;
            }
            else
                writeBytes = write(connFD, WITHDRAW_AMOUNT_INVALID, strlen(WITHDRAW_AMOUNT_INVALID));
        }
        else
            write(connFD, ACCOUNT_DEACTIVATED, strlen(ACCOUNT_DEACTIVATED));
        read(connFD, readBuffer, sizeof(readBuffer)); // Dummy read
    }
    else
    {
        // FAIL
        return false;
    }
}
bool get_balance(int connFD)
{
    char buffer[1000];
    struct Account account;
    account.accountNumber = loggedInCustomer.account;
    if (get_account_details(connFD, &account))
    {
        bzero(buffer, sizeof(buffer));
        if (account.active)
        {
            sprintf(buffer, "You have ₹ %ld imaginary money in our bank!^", account.balance);
            write(connFD, buffer, strlen(buffer));
        }
        else
            write(connFD, ACCOUNT_DEACTIVATED, strlen(ACCOUNT_DEACTIVATED));
        read(connFD, buffer, sizeof(buffer)); // Dummy read
    }
    else
    {
        // ERROR while getting balance
        return false;
    }
}
bool change_password(int connFD)
{
    ssize_t readBytes, writeBytes;
    char readBuffer[1000], writeBuffer[1000];

    char newPassword[1000];

    writeBytes = write(connFD, PASSWORD_CHANGE_OLD_PASS, strlen(PASSWORD_CHANGE_OLD_PASS));
    // TODO : Add error checking
    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    // TODO : Add error checking

    if (strcmp(readBuffer, loggedInCustomer.password) == 0)
    {
        // Password matches with old password
        writeBytes = write(connFD, PASSWORD_CHANGE_NEW_PASS, strlen(PASSWORD_CHANGE_NEW_PASS));
        // TODO : Add error checking
        bzero(readBuffer, sizeof(readBuffer));
        readBytes = read(connFD, readBuffer, sizeof(readBuffer));
        // TODO : Add error checking

        strcpy(newPassword, readBuffer);

        writeBytes = write(connFD, PASSWORD_CHANGE_NEW_PASS_RE, strlen(PASSWORD_CHANGE_NEW_PASS_RE));
        // TODO : Add error checking
        bzero(readBuffer, sizeof(readBuffer));
        readBytes = read(connFD, readBuffer, sizeof(readBuffer));
        // TODO : Add error checking

        if (strcmp(readBuffer, newPassword) == 0)
        {
            // New & reentered passwords match

            strcpy(loggedInCustomer.password, newPassword);

            int customerFileDescriptor = open(CUSTOMER_FILE, O_WRONLY);
            // TODO : Add error checking

            off_t offset = lseek(customerFileDescriptor, loggedInCustomer.id * sizeof(struct Customer), SEEK_SET);
            // TODO : Add error checking

            struct flock lock = {F_WRLCK, SEEK_SET, offset, sizeof(struct Customer), getpid()};
            int fcntlStatus = fcntl(customerFileDescriptor, F_SETLKW, &lock);
            // TODO : Add error checking

            writeBytes = write(customerFileDescriptor, &loggedInCustomer, sizeof(struct Customer));
            // TODO : Add error checking

            lock.l_type = F_UNLCK;
            fcntlStatus = fcntl(customerFileDescriptor, F_SETLK, &lock);
            // TODO : Add error checking

            close(customerFileDescriptor);

            writeBytes = write(connFD, PASSWORD_CHANGE_SUCCESS, strlen(PASSWORD_CHANGE_SUCCESS));
            // TODO : Add error checking
            readBytes = read(connFD, readBuffer, sizeof(readBuffer)); // Dummy read
        }
        else
        {
            // New & reentered passwords don't match
            writeBytes = write(connFD, PASSWORD_CHANGE_NEW_PASS_INVALID, strlen(PASSWORD_CHANGE_NEW_PASS_INVALID));
            // TODO : Add error checking
            readBytes = read(connFD, readBuffer, sizeof(readBuffer)); // Dummy read
        }
    }
    else
    {
        // Password doesn't match with old password
        writeBytes = write(connFD, PASSWORD_CHANGE_OLD_PASS_INVALID, strlen(PASSWORD_CHANGE_OLD_PASS_INVALID));
        // TODO : Add error checking
        readBytes = read(connFD, readBuffer, sizeof(readBuffer)); // Dummy read
    }
}

#endif