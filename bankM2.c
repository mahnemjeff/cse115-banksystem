#include "funcs.h"

int main() {
    struct Customer customers[MAX_CUSTOMERS];
    int count = 0;
    int readStat;

    printf("\t=========================================\t\n");
    printf("\tWelcome to Bank of North South University\t\n");
    printf("\t=========================================\t\n");

    while (1)
    {
    int option;
    printf("\n\tPress 1 for User\t\n");
    printf("\tPress 2 for Admin\t\n");
    printf("\n\tPlease enter your choice: ");
    scanf("%d", &option);
    if (option == 2)
        {
        printf("\n");
        readStat = readData(customers, &count);  //password check
        if (readStat == 1)
        {
            int writeStat = writeData(customers, count);
        }
        printf("\n");
        printf("\n\t****************Bank Management System Menu:****************\t\n");
        printf("\t\t1. Add Customer\n");
        printf("\t\t2. Sort Data Alphabetically by Name\n");
        printf("\t\t3. Sort Data by Account Number\n");
        printf("\t\t4. Sort Data by Balance\n");
        printf("\t\t5. Search Customer by Account Number\n");
        printf("\t\t6. Delete Customer by Account Number\n");
        printf("\t\t7. Edit Customer Information\n");
        printf("\t\t8. Change Password\n");
        printf("\t\t9. Transfer Money\n");
        printf("\t\t10. Sort and Generate Text File\n");
        printf("\t\t11. Generate List of Customers by Service Region\n");
        printf("\t\t12. Show all accounts\n");
        printf("\t\t0. Exit\n\n");
        printf("\tEnter your choice: ");
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                if (count >= MAX_CUSTOMERS)
                    {
                        printf("\tMaximum number of customers reached.\t\n");
                    }
                else {
                        printf("\tEnter customer name: ");
                        scanf("%s", customers[count].name);
                        printf("\tEnter contact number: ");
                        scanf("%s", customers[count].contactNumber);
                        printf("\tEnter service region: ");
                        scanf("%s", customers[count].serviceRegion);
                        printf("\tEnter initial balance: ");
                        scanf("%f", &customers[count].balance);

                        //char pinInput[10];
                        printf("\tSet a PIN: ");
                        scanf("%s", customers[count].pin);
                        //customers[count].pin = atoi(pinInput);

                        customers[count].accountNumber = 1070000 + count + 1;
                        count++;

                        printf("\tCustomer added successfully.\t\n");
                    }
                break;
            case 2:
                sortDataAlphabetically(customers, count);
                break;
            case 3:
                sortDataByAccountNumber(customers, count);
                break;
            case 4:
                sortDataByDeposit(customers, count);
                break;
            case 5:
                printf("\tEnter account number: ");
                int accountNumber;
                scanf("%d", &accountNumber);
                searchData(customers, count, accountNumber);
                break;
            case 6:
                printf("\tEnter account number: ");
                scanf("%d", &accountNumber);
                deleteData(customers, &count, accountNumber);
                break;
            case 7:
                printf("\tEnter account number: ");
                scanf("%d", &accountNumber);
                editData(customers, count, accountNumber);
                break;
            case 8:
                changePassword();
                break;
            case 9:
                printf("\tEnter sender account number: ");
                int senderAccountNumber;
                scanf("%d", &senderAccountNumber);
                printf("\tEnter receiver account number: ");
                int receiverAccountNumber;
                scanf("%d", &receiverAccountNumber);
                transferMoney(customers, count, senderAccountNumber, receiverAccountNumber);
                break;
            case 10:
                printf("\tGenerate sorted text file by:\t\n");
                printf("\t1. Name\n");
                printf("\t2. Deposit\n");
                printf("\t3. Service Region\n");
                printf("\tEnter your choice: ");
                int sortChoice;
                scanf("%d", &sortChoice);

                switch (sortChoice) {
                    case 1:
                        sortDataAlphabetically(customers, count);
                        generateSortedTextFile(customers, count, "sortedByName.txt");
                        break;
                    case 2:
                        sortDataByDeposit(customers, count);
                        generateSortedTextFile(customers, count, "sortedByDeposit.txt");
                        break;
                    case 3:
                        printf("\tEnter service region: ");
                        char serviceRegion[100];
                        scanf("%s", serviceRegion);
                        generateListByServiceRegion(customers, count, serviceRegion);
                        break;
                    default:
                        printf("\tInvalid choice.\t\n");
                        break;
                }
                break;
            case 11:
                printf("Enter service region: ");
                char serviceRegion[100];
                scanf("%s", serviceRegion);
                generateListByServiceRegion(customers, count, serviceRegion);
                break;
            case 12:
                printAllAccounts(customers, count);
                break;
            case 0:
                printf("\n\t**************Exiting the program**************\t\n");
                printf("\n");
                writeData(customers, count);
                printf("\n\t===========================================\t\n");
                printf("\tThank you for your time and have a good day!\t\n");
                printf("\t=============================================\t\n");
                return 0;
                break;
        } // end of switch case
            } // end of if
       else if (option == 1)
           {
           printf("\n\t****************Banking Menu:****************\t\n");
           printf("\n\t\t1. Change Password\n");
           printf("\t\t2. Transfer Money\n");
           printf("\t\t3. Exit\n");
           printf("\n\tEnter your choice: ");
           int choice2;
           scanf("%d", &choice2);
           printf("\n");

            switch (choice2) {
                case 1:
                    changePassword();
                    break;
                case 2:
                    printf("Enter sender account number: ");
                    int senderAccountNumber;
                    scanf("%d", &senderAccountNumber);
                    printf("Enter receiver account number: ");
                    int receiverAccountNumber;
                    scanf("%d", &receiverAccountNumber);
                    transferMoney(customers, count, senderAccountNumber, receiverAccountNumber);
                    break;
                case 3:
                    printf("\t*************Exiting the program*************\t\n");
                    break;
                default:
                    printf("\n\tError!\t\n");
                    break;
        } // end of switch case
           } // end of else if
    } // end of while
    return 0;
}
