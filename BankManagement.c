#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
  int accountID;
  char ownerName[50];
  char type[20];
  float balance;
}Account;

Account *creatingArray(int *size);
void addingAccount (Account *dataBase, int size, int *currentNumber);
void deletingAccount (Account *dataBase, int size, int *currentNumber);
void sortingWealth(Account *dataBase, int *currentNumber);
void transaction(Account *dataBase, int *currentNumber);
void savetoFile(Account *dataBase, int *currentNumber);
void displaying(Account *dataBase, int *currentNumber);

int main() {
  int currentNumber = 0;
  int size = 100;
  Account *dataBase = creatingArray(&size);
  int userChoice = 0;
  while(userChoice != 7) {
    printf("which service do you wanna use ? (1 to 7): ");
    scanf("%d",&userChoice);
    while(getchar() != '\n');
    switch(userChoice) {

      case 1: 
        addingAccount (dataBase, size, &currentNumber);
      break;
      case 2:
        deletingAccount (dataBase, size, &currentNumber) ;
      break;
      case 3 :
        sortingWealth(dataBase,&currentNumber);
      break;
      case 4: 
        transaction(dataBase, &currentNumber);
      break;
      case 5:
        savetoFile(dataBase, &currentNumber);
      break;
      case 6:
        displaying(dataBase, &currentNumber);
      break;
      case 7:
        printf("Thank you for choosing ourservices\n");
      break;
      default :
        printf("Enter the number between 1 to 7");
    }

  }
  free(dataBase);
  return 0;
}


Account *creatingArray(int *size) {
  Account *dataBase = malloc(*size * sizeof(Account));
  if(dataBase == NULL) {
    printf("The allocation of dataBase is failed\n");
    return NULL;
  }
  return dataBase;
}

void addingAccount (Account *dataBase, int size, int *currentNumber){

  int idCustomer;
  int numberAdd;
  printf("How many customer do you wanna add? : ");
  scanf("%d", &numberAdd);
  while(getchar() != '\n');
  if(*currentNumber + numberAdd <= size) {
    for(int i = *currentNumber ; i < numberAdd + *currentNumber ; i++) {
      printf("Please enter the id of %dth customer who you wanna add : ",i+1);
      scanf("%d" ,&idCustomer);
      while(getchar() != '\n');
      for(int j = 0; j < *currentNumber; j++) {
        if(idCustomer == dataBase[j].accountID) {
          printf("This ID has already is in database\n");
          break;
        }
      }
       dataBase[i].accountID = idCustomer;

       printf("Please enter the name of %dth customer : ", i+1);
       fgets(dataBase[i].ownerName, sizeof(dataBase[i].ownerName),stdin);
       dataBase[i].ownerName[strcspn(dataBase[i].ownerName,"\n")] = '\0';

       printf("Please enter the type of the %dth customer : ", i+1);
       fgets(dataBase[i].type, sizeof(dataBase[i].type), stdin);
       dataBase[i].type[strcspn(dataBase[i].type,"\n")] = '\0';
       
        printf("Please enter the balance of the %dth balance : ", i+1);
        scanf("%f" ,&dataBase[i].balance);
        while(getchar() != '\n');
    }
    *currentNumber = *currentNumber + numberAdd;
  }
  else {
    printf("The databse is full\n");
  }

}

void deletingAccount (Account *dataBase, int size, int *currentNumber) {
  int idDeleted;
  int found = 0;
  printf("Please enter the id of customer you wanna delete : ");
  scanf("%d", &idDeleted);
  while(getchar() != '\n');
  for(int i = 0; i < *currentNumber; i++) {
    if(dataBase[i].accountID == idDeleted) {
      for(int j = i; j < *currentNumber-1; j++) {
        dataBase[j] = dataBase[j+1];
      }
      (*currentNumber)--;
      found = 1;
      break;
    }
  }
  if(found == 0) {
    pritnf("The id that you enterd doesn't match with any of our customer\n");
  }
}

void sortingWealth(Account *dataBase, int *currentNumber) {

  for(int i = 0; i < *currentNumber; i++) {
    float min = dataBase[i].balance;
    int index = i;
    Account temp;
    for(int j= i+1; j < *currentNumber; j++) {
      if(dataBase[j].balance < min) {
        min = dataBase[j].balance;
        index = j;
      }
    }
    temp = dataBase[i];
    dataBase[i] = dataBase[index];
    dataBase[index] = temp;
  }
  printf("The sortinf done successfully\n");

}

void transaction(Account *dataBase, int *currentNumber) {
  int idCustomer;
  float amount;
  int found = 0;
  printf("Please enter the id of customer : ");
  scanf("%d", &idCustomer);
  while(getchar() != '\n');
   for(int i = 0; i < *currentNumber; i++) {
    if(dataBase[i].accountID == idCustomer) {
      printf("Please enter the amount of money that you wanna withdraw : ");
      scanf("%f", &amount);
      while(getchar() != '\n');
      if(dataBase[i].balance >= amount ) {
        dataBase[i].balance = dataBase[i].balance - amount;
      }
      else {
        printf("the balance is not enough \n");
      }
      found = 1;
      break;
    }
  }
  if(found == 0) {
    printf("The id that you enterd doesn't match with any of our customer\n");
  }
}

void savetoFile(Account *dataBase, int *currentNumber) {

  FILE *fp = fopen("BankDataBase.txt", "w");
  if(fp == NULL) {
    printf("The solving file failed\n");
  }
  fprintf(fp, "%d\n", *currentNumber);
  for(int i=0; i < *currentNumber; i++) {
    fprintf(fp, "%d- ID : %d Name: %s Type : %s Balance : %.2f \n",i+1, dataBase[i].accountID, dataBase[i].ownerName, dataBase[i].type, dataBase[i].balance);
  }
  fclose(fp);
  printf("Saving was done successfully\n");
}

void displaying(Account *dataBase, int *currentNumber) {
    for(int i=0; i < *currentNumber; i++) {
    printf("%d- ID : %d Name: %s Type : %s Balance : %.2f \n",i+1, dataBase[i].accountID, dataBase[i].ownerName, dataBase[i].type, dataBase[i].balance);
  }
}
