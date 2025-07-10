#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int accountNumber;
    char name[50];
    float balance;
} Account;

//  Find and return account from file by account number
int findAccount(int accNum, Account *acc) {
    FILE *fp = fopen("accounts.dat", "rb");
    if (!fp) return 0;

    while (fread(acc, sizeof(Account), 1, fp)) {
        if (acc->accountNumber == accNum) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

//  Update account after deposit/withdraw/transfer
void updateAccount(Account updated) {
    FILE *fp = fopen("accounts.dat", "rb+");
    if (!fp) return;

    Account temp;
    while (fread(&temp, sizeof(Account), 1, fp)) {
        if (temp.accountNumber == updated.accountNumber) {
            fseek(fp, -sizeof(Account), SEEK_CUR);
            fwrite(&updated, sizeof(Account), 1, fp);
            break;
        }
    }
    fclose(fp);
}

//  Log transaction
void logTransaction(int accNum, const char *message) {
    char filename[100];
    sprintf(filename, "account_%d.txt", accNum);
    FILE *tf = fopen(filename, "a");
    fprintf(tf, "%s\n", message);
    fclose(tf);
}

//  Create new account
void createAccount() {
    FILE *fp = fopen("accounts.dat", "ab");
    Account acc;

    printf("\nEnter Account Number: ");
    scanf("%d", &acc.accountNumber);

    printf("Enter Account Holder Name: ");
    getchar(); // clear newline
    fgets(acc.name, sizeof(acc.name), stdin);
    acc.name[strcspn(acc.name, "\n")] = '\0'; // remove newline

    printf("Enter Initial Balance: ₹");
    scanf("%f", &acc.balance);

    fwrite(&acc, sizeof(Account), 1, fp);
    fclose(fp);

    char msg[100];
    sprintf(msg, "Account Created: ₹%.2f", acc.balance);
    logTransaction(acc.accountNumber, msg);

    printf(" Account Created Successfully!\n");
}

//  Deposit to account
void deposit() {
    int accNum;
    float amount;
    Account acc;

    printf("Enter Account Number: ");
    scanf("%d", &accNum);

    if (!findAccount(accNum, &acc)) {
        printf("❌ Account not found.\n");
        return;
    }

    printf("Enter amount to deposit: ₹");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("❌ Invalid amount.\n");
        return;
    }

    acc.balance += amount;
    updateAccount(acc);

    char msg[100];
    sprintf(msg, "Deposit: ₹%.2f | New Balance: ₹%.2f", amount, acc.balance);
    logTransaction(acc.accountNumber, msg);

    printf(" Deposit Successful!\n");
}

// Withdraw from account
void withdraw() {
    int accNum;
    float amount;
    Account acc;

    printf("Enter Account Number: ");
    scanf("%d", &accNum);

    if (!findAccount(accNum, &acc)) {
        printf("❌ Account not found.\n");
        return;
    }

    printf("Enter amount to withdraw: ₹");
    scanf("%f", &amount);

    if (amount <= 0 || amount > acc.balance) {
        printf("❌ Insufficient balance or invalid amount.\n");
        return;
    }

    acc.balance -= amount;
    updateAccount(acc);

    char msg[100];
    sprintf(msg, "Withdraw: ₹%.2f | Remaining Balance: ₹%.2f", amount, acc.balance);
    logTransaction(acc.accountNumber, msg);

    printf(" Withdrawal Successful!\n");
}

// Transfer money between accounts
void transfer() {
    int fromAccNum, toAccNum;
    float amount;
    Account fromAcc, toAcc;

    printf("Enter Your Account Number: ");
    scanf("%d", &fromAccNum);

    printf("Enter Recipient Account Number: ");
    scanf("%d", &toAccNum);

    if (fromAccNum == toAccNum) {
        printf(" Cannot transfer to same account.\n");
        return;
    }

    if (!findAccount(fromAccNum, &fromAcc) || !findAccount(toAccNum, &toAcc)) {
        printf(" One or both accounts not found.\n");
        return;
    }

    printf("Enter amount to transfer: ₹");
    scanf("%f", &amount);

    if (amount <= 0 || amount > fromAcc.balance) {
        printf(" Invalid or insufficient balance.\n");
        return;
    }

    fromAcc.balance -= amount;
    toAcc.balance += amount;

    updateAccount(fromAcc);
    updateAccount(toAcc);

    char msg1[100], msg2[100];
    sprintf(msg1, "Transferred ₹%.2f to Acc #%d | Balance: ₹%.2f", amount, toAccNum, fromAcc.balance);
    sprintf(msg2, "Received ₹%.2f from Acc #%d | Balance: ₹%.2f", amount, fromAccNum, toAcc.balance);

    logTransaction(fromAccNum, msg1);
    logTransaction(toAccNum, msg2);

    printf(" Transfer Successful!\n");
}

//  Show statement
void showStatement() {
    int accNum;
    char filename[100];

    printf("Enter Account Number: ");
    scanf("%d", &accNum);

    sprintf(filename, "account_%d.txt", accNum);
    FILE *fp = fopen(filename, "r");

    if (!fp) {
        printf("❌ No transactions found.\n");
        return;
    }

    printf("\n Transaction Statement for Account #%d:\n", accNum);
    char line[200];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
    fclose(fp);
}

int main() {
    int choice;

    while (1) {
        printf("\n====== BANK MENU ======\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Transfer\n");
        printf("5. Show Statement\n");
        printf("6. Exit\n");
        printf("=======================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: transfer(); break;
            case 5: showStatement(); break;
            case 6: printf(" Thank you! Exiting...\n"); exit(0);
            default: printf(" Invalid choice. Try again.\n");
        }
    }

    return 0;
}
