#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char string[50];

typedef struct {
  int Id;
  string name;
  float gpa;

}Student;

int gettingNumberOfStudent(); 
Student *creatingStu(int *size);
Student* addingStudnets(Student *arrstudents, int *size);
Student* removingStudents(Student *arrstudents, int*size);
Student* topStudentList(Student *arrStudents, int *size, int *numberTop);
void display(Student *arrStudent, int*size, Student *topStudentList , int *numberTop);

int main() {

  int choseNum = 0;
  int numberTop = 0;
  int size = gettingNumberOfStudent();
  Student *topStudentLis = NULL;
  Student *studentGroup = creatingStu(&size); 
  while (choseNum != 5) {
   printf("Hi , I hope you doing well\n which service do you want have : \n 1- Adding student : \n 2- Removing students from the list \n 3- sort Student for Top list \n 4- Displays the list \n 5- Exit\n"); 
   scanf("%d", &choseNum); 
   switch (choseNum) {
     case 1 : 
      studentGroup = addingStudnets(studentGroup , &size);
      break;
     case 2 : 
      studentGroup = removingStudents(studentGroup, &size);     
      break;  
     case 3:
      topStudentLis = topStudentList(studentGroup , &size, &numberTop);
      break;
     case 4:
      display(studentGroup , &size , topStudentLis , &numberTop);
      break;
     case 5:
      printf("I hope you enjoyed our services\n");
      break;
    default:
      printf("You need to enter a number between 1 to 5");
      break;
    }
  }
  free(studentGroup);
  free(topStudentLis);
  return 0;
}

int gettingNumberOfStudent() {
  int size = 0;
  printf("How many students do you have ? ");
  scanf("%d", &size);
  return size;
}

Student* creatingStu(int *size) {

  Student *studentGroup = malloc(*size * sizeof(Student));
  if(studentGroup == NULL) {
    return NULL;
  }
  for(int i = 0; i < *size ; i++) {
    printf ("Enter the id of %dth student : ", i+1);
    scanf("%d", &(studentGroup[i].Id));
    getchar();
    printf("Enter the name of %dth student : ", i+1);
    fgets(studentGroup[i].name, sizeof(studentGroup[i].name), stdin);
    studentGroup[i].name[strcspn(studentGroup[i].name, "\n")] = '\0';
    printf("Enter the GPA of %dth student : ", i + 1);
    scanf("%f", &studentGroup[i].gpa);
    getchar();

  }
  return studentGroup;
}

Student* addingStudnets(Student *arrstudents, int *size) {

  int newSize = 0;
  printf("How many students d oyou wanna add : ");
  scanf("%d", &newSize);
  newSize += *size;
  getchar();
  Student* newStudentGroup = realloc(arrstudents , newSize *sizeof(Student));
  if(newStudentGroup == NULL) {
    return NULL;
  }
  for(int i = *size; i < newSize; i++ ) {
    printf("Enter the ID of %dth student : ", i+1);
    scanf("%d", &newStudentGroup[i].Id);
    getchar();
    printf("Enter the name of %dth student : ", i+1);
    fgets(newStudentGroup[i].name , sizeof(newStudentGroup[i].name), stdin);
    newStudentGroup[i].name[strcspn(newStudentGroup[i].name, "\n")] = '\0';
    printf("Enter the GPA of %dth student : ", i+1);
    scanf("%f", &newStudentGroup[i].gpa);
    getchar();
  }
  *size = newSize;
  return newStudentGroup;

}

Student* removingStudents(Student *arrstudents, int*size) {
  int idDel = 0;
  printf("Enter the ID of student which you wanna delete : ");
  scanf("%d", &idDel);
  for(int i = 0 ; i < *size; i++ ) {
    if(arrstudents[i].Id == idDel) {
      for(int j = i; j < *size -1 ; j++) {
        arrstudents[j] = arrstudents[j+1];
      }
      *size = *size - 1;
      break;
    }
  }
  Student* newStudentGroup = realloc(arrstudents, *size * sizeof(Student));
  if(newStudentGroup == NULL) {
    return NULL;
  }
  return newStudentGroup;

}

Student* topStudentList(Student *arrStudents, int *size, int *numberTop) {
  float Gpatop = 26.25;
  int counterTop = 0;
  Student *topStudent = malloc(*size * sizeof(Student));
  if(topStudent == NULL) {
    return NULL;
  }
  for(int i = 0; i < *size ; i++) {
    if(arrStudents[i].gpa >= Gpatop) {
      topStudent[counterTop] = arrStudents[i]; 
      (counterTop++);
    }
  }
  topStudent = realloc(topStudent , counterTop * sizeof(Student) );
  if(topStudent == NULL) {
    return NULL;
  }
  *numberTop = counterTop;
  return topStudent;
}

void display(Student *arrStudent, int*size, Student *topStudentList , int *numberTop) {

  if(*size == 0 ) {
    printf("there is no student to show");
  }else {
    int numChose = 0;
    printf("Which group do you wanna displayed? \n 1.All students \n 2. Top student\n Enter the number : ");
    scanf("%d", &numChose);
    if(numChose == 1) {
      for(int i = 0; i < *size ; i++) {
        printf("%d- ID : %d   Name : %s  GPA : %.2f \n", i+1 , arrStudent[i].Id , arrStudent[i].name, arrStudent[i].gpa);
      }
    } else if(numChose == 2) {
      if(*numberTop == 0) {
        printf("There is no student in Top list");
      }
      for(int i = 0 ; i < *numberTop ; i++) {
        printf("%d- ID : %d   Name : %s  GPA : %.2f \n", i+1 , topStudentList[i].Id , topStudentList[i].name, topStudentList[i].gpa);
      }
    } else {
      printf("choose the right number between 1 or 2");
    }
  }


}
