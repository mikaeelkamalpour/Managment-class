#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
  int id;
  char title[100];
  // char author[100];
  int is_borrowed;
  char student_name[50];
}Book;

Book* creatingArr(int *count);
Book* add_book(Book* library, int *count);
void borrow_book(Book *library, int *count);
void return_book(Book *library, int *count);
void display(Book* library, int *count);


int main() {
  int count = 0;
  Book *library = creatingArr(&count);
  int userChoose = 0;
  while (userChoose !=5) {
    printf("Which service do you like to use : (1,2,3,4) ");
    scanf("%d",&userChoose);
    switch(userChoose) {
      case 1:
      library = add_book(library, &count);
      break;
      case 2:
        borrow_book(library, &count);
      break;
      case 3:
        return_book(library, &count);
      break;
      case 4:
        display(library, &count);
      break;
      case 5:
        printf("Thank you for usuing our services\n");
      break;
      default:
        printf("Enter a number\n");
    }
  }

  free(library);
  return 0;
}

Book* creatingArr(int *count){

  Book *library = malloc((*count) * (sizeof(Book)));
  if(library == NULL) {
    printf("The allocation of library failed\n");
  }

  return library;

}

Book* add_book(Book* library, int *count) {

  int add_quantity = 0;
  printf("How many book do you wanna add :  ");
  scanf("%d", &add_quantity);
  Book* temp = realloc(library , (*count + add_quantity)* sizeof(Book));
  if(temp == NULL) {
    printf("the allocation of temp failed\n");
    return library;
  }
  library = temp;
  for(int i = *count; i < (*count + add_quantity) ; i++ ) {
    printf("Enter the ID of the %dth book : ", i+1);
    scanf("%d", &library[i].id);
    while(getchar() != '\n');
    printf("Enter the name of the the %dth book : ", i+1);
    fgets(library[i].title, sizeof(library[i].title), stdin);
    library[i].title[strcspn(library[i].title, "\n")] = 0;
    library[i].is_borrowed = 0;
    strcpy(library[i].student_name, "none");
  }
  *count += add_quantity;
  return library;
}
void borrow_book(Book *library, int *count) {
  int index = -1;
  char nameBook[100] = "";
  while(getchar()!= '\n');
  printf("please Enter the name of the book that you want to search : ");
  fgets(nameBook, sizeof(nameBook), stdin);
  nameBook[strcspn(nameBook, "\n")] = 0;
  for(int i = 0; i < *count; i++) {
    if(strcmp(library[i].title, nameBook) == 0) {
      index = i;
      break;
    }
  }
  if(index == -1) {
    printf("there is no book in our library which is match with title\n");
  } 
  else if(library[index].is_borrowed == 1){
    printf("The book is already borrowed by %s \n",library[index].student_name);
  }
  else {
    printf("Please enter your name : ");
    fgets(library[index].student_name, sizeof(library[index].student_name), stdin);
    library[index].is_borrowed = 1;
  }
}
void return_book(Book *library, int *count) {
  int id_return = 0;
  int index = -1;
  printf("Enter the ID of the book that you wanna return : ");
  scanf("%d", &id_return);
  for(int i = 0; i < *count; i++) {
    if(id_return == library[i].id) {
      index = i;
      break;
    }
  }
  if(index == -1) {
    printf("Your id that enter doesn match with any book in our lubrary\n");
  }
  else {
    strcpy(library[index].student_name , "none");
    library[index].is_borrowed = 0;
  }
}
void display(Book* library, int *count) {
  char borrow[10] = ""; 
  for(int i = 0; i< *count; i++) {
    if(library[i].is_borrowed == 0 ) {
      strcpy(borrow, "No");
    }
    else {
      strcpy(borrow, "Yes");
    }
    printf("%d- ID: %d  Title : %s Borrowed : %s  Student's name : %s\n", i+1, library[i].id, library[i].title, borrow, library[i].student_name );
  }
}
