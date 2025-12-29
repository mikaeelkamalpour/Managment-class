#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char String[60];
typedef struct{
  int id;
  String name;
  float price;
  int quantity;

}Product;


Product *creatingPro(int size) {
  Product *store = calloc(size, sizeof(Product));
  if(store == NULL) {
    printf("Memory Erorr\n");
  }
  return store;
}

Product *add_new_product(Product *store, int *count) {
  int quantity_product = 0;
  printf("How much product you wanna add : ");
  scanf("%d",&quantity_product);
  Product *temp = realloc(store, (quantity_product + *count) * sizeof(Product));
  if(temp == NULL) {
    printf("Allocation of temp is failed\n");
    return store;
  }
  store = temp;
  for(int i = *count; i < quantity_product + *count; i++) {
    printf("Enter the id of %dth car : ",i+1);
    scanf("%d", &store[i].id);
    while(getchar() != '\n');
    printf("Enter the name of %dth car : ", i+1);
    fgets(store[i].name, sizeof(store[i].name), stdin);
    store[i].name[strcspn(store[i].name, "\n")] = 0;
    printf("Enter the price %dth car : ", i+1);
    scanf("%f", &store[i].price);
    printf("Enter the quantity of %dth car : ",i+1);
    scanf("%d", &store[i].quantity);
  }
  *count += quantity_product;
  return store;
}
void update_quantity(Product *store, int *count) {
  int idSearched = 0;
  int index  =  -1;
  printf("Enter the id of product which you are looking for : ");
  scanf("%d", &idSearched);
  for(int i = 0; i < *count; i++) {
    if(idSearched == store[i].id) {
      index = i;
      printf("Here is the car you looking for : \n ID : %d  Name : %s Price : %.2f$  Quantity : %d \n", store[i].id , store[i].name, store[i].price, store[i].quantity);
      printf("Enter the new quantity of this car : ");
      scanf("%d", &store[i].quantity);
      break;
    }
  }
  if(index == -1) {
    printf("There is no product in our store that matches with this ID \n");
  }
  
}
void display(Product *store, int *count) {
  for(int i = 0; i < *count; i++) {
    printf("%d-  ID : %d  Name : %s Price : %.2f$  Quantity : %d \n", i+1 ,store[i].id , store[i].name, store[i].price, store[i].quantity);
  }
}


int main() {
  int size = 1;
  int count = 0;
  int choiceUser = 0;
  Product *store = creatingPro(size);
  while (choiceUser != 4) {
    printf(" 1- Add a new product\n 2- Update product quantity\n 3 - Display all products \n 4-Save and Exit \n Which service do you want? (1,2,3,4) : ");
    scanf("%d", &choiceUser);
    switch (choiceUser) {
      case 1: 
      store = add_new_product(store, &count);
      break;
      case 2:
        update_quantity(store, &count);
      break;
      case 3:
        display(store, &count);
      break;
      case 4:
        printf("Thank you for choosing us!\n");
      break;
      default:
        printf("Invalid\n");
    }
  }
  free(store);

  return 0;
}
