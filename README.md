    # Lab Exercises

## Hands-on List 1

### File Management

1. Create the following types of a files using (i) shell command (ii) system call 
    1. Soft link (`symlink` system call) 
    2. Hard link (`link` system call) 
    3. FIFO (`mkfifo` Library Function or `mknod` system call)
2. Write a simple program to execute in an infinite loop at the background. Go to `/proc` directory and identify all the process related information in the corresponding `proc` directory.
3. Write a program to create a file and print the file descriptor value. Use `creat()` system call
4. Write a program to open an existing file with read write mode. Try `O_EXCL` flag also.
5. Write a program to create five new files with an infinite loop. Execute the program in the background and check the file descriptor table at `/proc/pid/fd`.
6. Write a program to take input from `STDIN` and display on `STDOUT`. Use only `read`/`write` system calls
7. Write a program to copy `file1` into `file2` (`$cp file1 file2`).
8. Write a program to open a file in read only mode, read line by line and display each line as it is read. Close the file when end of file is reached.
9. Write a program to print the following information about a given file. 
    1. Inode 
    2. Number of hard links 
    3. UID 
    4. GID 
    5. Size 
    6. Block size 
    7. Number of blocks 
    8. Time of last access 
    9. Time of last modification 
    10. Time of last change
10. Write a program to open a file with read write mode, write 10 bytes, move the file pointer by 10 bytes (use `lseek`) and write again 10 bytes. 
    1. Check the return value of `lseek` 
    2. Open the file with `od` and check the empty spaces in between the data.
11. Write a program to open a file, duplicate the file descriptor and append the file with both the descriptors and check whether the file is updated properly or not. 
    1. Use `dup` 
    2. Use `dup2` 
    3. Use `fcntl`
12. Write a program to find out the opening mode of a file. Use `fcntl`.
13. Write a program to wait for a `STDIN` for 10 seconds using `select`. Write a proper print statement to verify whether the data is available within 10 seconds or not (check in `$man 2 select`).
14. Write a program to find the type of a file. 
    1. Input should be taken from command line. 
    2. Program should be able to identify any type of a file.
15. Write a program to display the environmental variable of the user (use `environ`).
16. Write a program to perform mandatory locking. 
    1. Implement write lock 
    2. Implement read lock
17. Write a program to simulate online ticket reservation. Implement write lock. 
Write a program to open a file, store a ticket number and exit. 
Write a separate program, to open the file, implement write lock, read the ticket number, increment the number and print the new ticket number then close the file.
18. Write a program to perform Record locking. 
    1. Implement write lock 
    2. Implement read lock

    Create three records in a file. Whenever you access a particular record, first lock it then modify/access to avoid race condition.

### Process Management

1. Write a program to find out time taken to execute `getpid` system call. Use time stamp counter.
2. Find out the priority of your running program. Modify the priority with `nice` command.
3. Write a program, call `fork` and print the parent and child process id.
4. Write a program, open a file, call `fork`, and then write to the file by both the child as well as the parent processes. Check output of the file.
5. Write a program to create a Zombie state of the running program.
6. Write a program to create an orphan process.
7. Write a program to create three child processes. The parent should wait for a particular child (use `waitpid` system call).
8. Write a program to execute an executable program. 
    1. Use some executable program 
    2. Pass some input to an executable program. (for example execute an executable of `$./a.out name`)
9. Write a program to execute `ls -Rl` by the following system calls 
    1. `execl` 
    2. `execlp` 
    3. `execle` 
    4. `execv` 
    5. `execvp`
10. Write a program to get maximum and minimum real time priority.
11. Write a program to get the scheduling policy and modify the scheduling policy (`SCHED_FIFO`, `SCHED_RR`).
12. Write a program to run a script at a specific time using a Daemon process.

---

## Hands-on List 2

1. Write a separate program (for each time domain) to set a interval timer in 10s and 10ms 
    1. `ITIMER_REAL`
    2. `ITIMER_VIRTUAL`
    3. `ITIMER_PROF`
2. Write a program to print the system resource limits. Use `getrlimit` system call.
3. Write a program to set (any one) system resource limit. Use `setrlimit` system call.
4. Write a program to measure how much time is taken to execute 100 `getppid()` system call. Use time stamp counter.
5. Write a program to print the system limitation of 
    1. Maximum length of the arguments to the exec family of functions. 
    2. Maximum number of simultaneous process per user id. 
    3. Number of clock ticks (jiffy) per second. 
    4. Maximum number of open files 
    5. Size of a page 
    6. Total number of pages in the physical memory 
    7. Number of  currently available pages in the physical memory.
6. Write a simple program to create three threads.
7. Write a simple program to print the created thread IDs.
8. Write a separate program using signal system call to catch the following signals. 
    1. `SIGSEGV`
    2. `SIGINT` 
    3. `SIGFPE` 
    4. `SIGALRM` (use `alarm` system call) 
    5. `SIGALRM` (use `setitimer` system call) 
    6. `SIGVTALRM` (use `setitimer` system call) 
    7. `SIGPROF` (use `setitimer` system call)
9. Write a program to ignore a `SIGINT` signal then reset the default action of the `SIGINT` signal - Use `signal` system call.
10. Write a separate program using sigaction system call to catch the following signals. 
    1. `SIGSEGV`
    2. `SIGINT`
    3. `SIGFPE`
11. Write a program to ignore a `SIGINT` signal then reset the default action of the `SIGINT` signal - use `sigaction` system call.
12. Write a program to create an orphan process. Use `kill` system call to send `SIGKILL` signal to the parent process from the child process.
13. Write two programs: first program is waiting to catch `SIGSTOP` signal, the second program will send the signal (using `kill` system call). Find out whether the first  program is able to catch the signal or not.
14. Write a simple program to create a pipe, write to the pipe, read from pipe and display on the monitor.
15. Write a simple program to send some data from parent to the child process.
16. Write a program to send and receive data from parent to child vice versa. Use two way communication.
17. Write a program to execute `ls -l | wc`
    1. Use `dup`
    2. Use `dup2`
    3. Use `fcntl`
18. Write a program to find out total number of directories on the `pwd`. Execute `ls -l | grep ^d | wc`. Use only `dup2`.
19. Create a FIFO file by 
    1. `mknod` command
    2. `mkfifo` command
    3. Use `strace` command to find out, which command (`mknod` or `mkfifo`) is better. 
    4. `mknod` system call 
    5. `mkfifo` library function
20. Write two programs so that both can communicate by FIFO - Use one way communication.
21. Write two programs so that both can communicate by FIFO - Use two way communications.
22. Write a program to wait for data to be written into FIFO within 10 seconds, use `select` system call with FIFO.
23. Write a program to print the maximum number of files can be opened within a process and size of a pipe (circular buffer). 
24. Write a program to create a message queue and print the key and message queue id.
25. Write a program to print a message queue's (use `msqid_ds` and `ipc_perm` structures)
    1. Access permission 
    2. `uid`, `gid` 
    3. Time of last message sent and received 
    4. Time of last change in the message queue
    5. Size of the queue 
    6. Number of messages in the queue
    7. Maximum number of bytes allowed
    8. PID of the `msgsnd` and `msgrcv`
26. Write a program to send messages to the message queue. Check `ipcs -q`
27. Write a program to receive messages from the message queue 
    1. With `0` as a flag 
    2. With `IPC_NOWAIT` as a flag
28. Write a program to change the exiting message queue permission. (Use `msqid_ds` structure)
29. Write a program to remove the message queue.
30. Write a program to create a shared memory. 
    1. Write some data to the shared memory
    2. Attach with `O_RDONLY` and check whether you are able to overwrite. 
    3. Detach the shared memory 
    4. Remove the shared memory
31. Write a program to create a semaphore and initialize value to the semaphore. 
    1. Create a binary semaphore 
    2. Create a counting semaphore
32. Write a program to implement semaphore to protect any critical section. 
    1. Rewrite the ticket number creation program using semaphore
    2. Protect shared memory from concurrent write access 
    3. Protect multiple pseudo resources (may be two) using counting semaphore 
    4. Remove the created semaphore
33. Write a program to communicate between two machines using socket.
34. Write a program to create a concurrent server. 
    1. Use `fork` 
    2. Use `pthread_create`
---------

# Mini-project

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
