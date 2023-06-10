#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CUSTOMERS 100

struct Customer {
    char name[100];
    int accountNumber;
    float balance;
    char contactNumber[20];
    char serviceRegion[10];
    char pin[3];
};


void encrypt(char *str, int key) {
    for (int i = 0; i < strlen(str); i++) {
        str[i] = str[i] + key;
    }
}

void decrypt(char *str, int key) {
    for (int i = 0; i < strlen(str); i++) {
        str[i] = str[i] - key;
    }
}

int writeData(struct Customer customers[], int count) {
    FILE *file = fopen("bankdata.txt", "w");
    if (file == NULL) {
        printf("\tError opening file.\t\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        encrypt(customers[i].name, 5);
        encrypt(customers[i].pin, 7);
        fprintf(file, "%s %d %.2f %s %s %s", customers[i].name, customers[i].accountNumber, customers[i].balance, customers[i].contactNumber,customers[i].serviceRegion, customers[i].pin);
        decrypt(customers[i].name, 5);
        decrypt(customers[i].pin, 7);
    }

    fclose(file);
    printf("\tData written to file successfully.\t\n");
    return 0;
}

int readData(struct Customer customers[], int *count) {
    FILE *file = fopen("bankdata.txt", "r");
    FILE *pass = fopen("pass.txt", "r");
    if (file == NULL || pass == NULL) {
        printf("\tError opening file.\t\n");
        return 1;
    }

    char password[100];
    fscanf(pass, "%s", password);
    decrypt(password, 5);

    char input[100];
    printf("\tEnter password: ");
    scanf("%s", input);

    if (strcmp(input, password) != 0) {
        printf("\n\tIncorrect password. Access denied.\t\n");
        fclose(file);
        fclose(pass);
        exit(0);
    }

    *count = 0;
    int fscworked = 6;
    while (fscworked == 6 && *count < MAX_CUSTOMERS) {
        fscworked = fscanf(file, "%s %d %f %s %s", customers[*count].name, &customers[*count].accountNumber, &customers[*count].balance, customers[*count].contactNumber, customers[*count].pin);
        if (fscworked != 6)
        {
            break;
        }
        decrypt(customers[*count].name, 5);
        decrypt(customers[*count].pin, 7);
        (*count)++;
    }

    fclose(file);
    fclose(pass);
    printf("\n\tData read from file successfully.\t\n");
    return 0;
}

void sortDataAlphabetically(struct Customer customers[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(customers[j].name, customers[j + 1].name) > 0) {
                struct Customer temp = customers[j];
                customers[j] = customers[j + 1];
                customers[j + 1] = temp;
            }
        }
    }
    printf("\n\tData sorted alphabetically successfully.\t\n");
}

void sortDataByDeposit(struct Customer customers[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (customers[j].balance < customers[j + 1].balance) {
                struct Customer temp = customers[j];
                customers[j] = customers[j + 1];
                customers[j + 1] = temp;
            }
        }
    }
    printf("\n\tData sorted by deposit amount successfully.\t\n");
}

void sortDataByAccountNumber(struct Customer customers[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (customers[j].accountNumber > customers[j + 1].accountNumber) {
                struct Customer temp = customers[j];
                customers[j] = customers[j + 1];
                customers[j + 1] = temp;
            }
        }
    }
    printf("\n\tData sorted by account number successfully.\t\n");
}

void searchData(struct Customer customers[], int count, int accountNumber) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (customers[i].accountNumber == accountNumber) {
            printf("\n\tCustomer found:\t\n");
            printf("\n\tName: %s\t\n", customers[i].name);
            printf("\n\tAccount Number: %d\t\n", customers[i].accountNumber);
            printf("\n\tBalance: %.2f\t\n", customers[i].balance);
            printf("\n\tContact Number: %s\t\n", customers[i].contactNumber);
            printf("\n\tService Region: %s\t\n", customers[i].serviceRegion);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("\n\tCustomer with account number %d not found.\t\n", accountNumber);
    }
}

void deleteData(struct Customer customers[], int *count, int accountNumber) {
    int found = 0;
    for (int i = 0; i < *count; i++) {
        if (customers[i].accountNumber == accountNumber) {
            found = 1; //???
            for (int j = i; j < *count - 1; j++) {
                customers[j] = customers[j + 1];
            }
            (*count)--;
            printf("\n\tCustomer with account number %d deleted.\t\n", accountNumber);
            break;
        }
    }
    if (!found) {
        printf("\n\tCustomer with account number %d not found.\t\n", accountNumber);
    }
}

void editData(struct Customer customers[], int count, int accountNumber) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (customers[i].accountNumber == accountNumber) {
            printf("\n\tEnter new name: ");
            scanf("%s", customers[i].name);
            printf("\n\tEnter new balance: ");
            scanf("%f", &customers[i].balance);
            printf("\n\tEnter new contact number: ");
            scanf("%s", customers[i].contactNumber);
            printf("\n\tEnter new service region number: ");
            scanf("%s", customers[i].serviceRegion);
            found = 1; //???
            printf("\tCustomer information updated successfully.\t\n");
            break;
        }
    }
    if (!found) {
        printf("\tCustomer with account number %d not found.\t\n", accountNumber);
    }
}

void changePassword() {
    FILE *pass = fopen("pass.txt", "r+");
    if (pass == NULL) {
        printf("\n\tError opening file.\t\n");
        return;
    }

    char password[100];
    fscanf(pass, "%s", password);
    decrypt(password, 5);

    char newPassword[100];
    printf("\n\tEnter current password: ");
    scanf("%s", newPassword);
    if (strcmp(newPassword, password) != 0) { //????
        printf("\n\tIncorrect password. Password change failed.\t\n");
        fclose(pass);
        return;
    }

    char newPasswordConfirm[100];
    printf("\n\tEnter new password: ");
    scanf("%s", newPassword);
    printf("\n\tConfirm new password: ");
    scanf("%s", newPasswordConfirm);

    if (strcmp(newPassword, newPasswordConfirm) == 0) {
        encrypt(newPassword, 5);
        fseek(pass, 0, SEEK_SET); //???
        fprintf(pass, "%s", newPassword);
        printf("\n\tPassword changed successfully.\t\n");
    } else {
        printf("\n\tPassword confirmation failed. Password change failed.\t\n");
    }

    fclose(pass);
}

void transferMoney(struct Customer customers[], int count, int senderAccountNumber, int receiverAccountNumber) {
    int senderIndex = -1;
    int receiverIndex = -1;

    for (int i = 0; i < count; i++) {
        if (customers[i].accountNumber == senderAccountNumber) {
            senderIndex = i;
        } else if (customers[i].accountNumber == receiverAccountNumber) {
            receiverIndex = i;
        }

        if (senderIndex != -1 && receiverIndex != -1) {
            break;
        }
    }

    if (senderIndex == -1) {
        printf("\n\tSender with account number %d not found.\t\n", senderAccountNumber);
        return;
    }

    if (receiverIndex == -1) {
        printf("\n\tReceiver with account number %d not found.\t\n", receiverAccountNumber);
        return;
    }

    char pin[3];
    printf("\n\tEnter your PIN: ");
    scanf("%s", pin);

    if (strcmp(customers[senderIndex].pin, pin) != 0) {
        printf("\n\tIncorrect PIN. Transfer failed.\t\n");
        return;
    }

    float amount;
    printf("\n\tEnter the amount to transfer: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("\n\tInvalid amount. Transfer failed.\t\n");
        return;
    }

    if (customers[senderIndex].balance < amount) {
        printf("\tInsufficient balance. Transfer failed.\t\n");
        return;
    }

    customers[senderIndex].balance -= amount;
    customers[receiverIndex].balance += amount;

    printf("\n\tTransfer successful.\t\n");

    FILE *file = fopen("transactions.txt", "a");
    if (file == NULL) {
        printf("\n\tError opening file.\t\n");
        return;
    }

    fprintf(file, "Sender Account Number: %d, Receiver Account Number: %d, Amount: %.2f\n", senderAccountNumber, receiverAccountNumber, amount);

    fclose(file);
}

void generateSortedTextFile(struct Customer customers[], int count, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("\n\tError opening file.\t\n");
        return;
    }

    fprintf(file, "Name              AccountNumber  Balance       ContactNumber   ServiceRegion \n\n"); //??

    for (int i = 0; i < count; i++) {
        fprintf(file, "%-19s %-14d %-12.2f %-15s %-14s\n", customers[i].name, customers[i].accountNumber, customers[i].balance, customers[i].contactNumber, customers[i].serviceRegion);
    }

    fclose(file);
    printf("\n\tText file generated successfully.\nPlease handle it carefully. It contains Sensitive data\t\n");
}

void generateListByServiceRegion(struct Customer customers[], int count, const char *serviceRegion) {
    FILE *file = fopen("listByServiceRegion.txt", "w");
    if (file == NULL) {
        printf("\n\tError opening file.\t\n");
        return;
    }

    fprintf(file, "\tName                AccountNumber  Balance      ContactNumber   ServiceRegion  \n\n");

    for (int i = 0; i < count; i++) {
        if (strcmp(customers[i].serviceRegion, serviceRegion) == 0) {
            fprintf(file, "%-19s %-14d %-12.2f %-15s %-14s\n", customers[i].name, customers[i].accountNumber, customers[i].balance, customers[i].contactNumber, customers[i].serviceRegion);
        }
    }

    fclose(file);
    printf("\n\tText file generated successfully.\nPlease handle it carefully. It contains Sensitive data\t\n");
}

void printAllAccounts(struct Customer customers[], int count) {
    printf("\n\tAll Customer Accounts:\t\n");
    printf("\tName                AccountNumber  Balance      ContactNumber   ServiceRegion  \n\n");
    for (int i = 0; i < count; i++) {
        printf("%-19s %-14d %-12.2f %-15s %-14s\n", customers[i].name, customers[i].accountNumber, customers[i].balance,
               customers[i].contactNumber, customers[i].serviceRegion);
    }
}


