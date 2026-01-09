#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct{
  int  number;
  char name[50];
  char position[50];
}Player;

Player* creatingArray(int *size);
void addingPlayer(Player *team ,int size, int *numberPlayer);
void removingPlayer (Player *team ,int *numberPlayer);
void groupingPlayer(Player *team, int *numberPlayer) ;
void strToLower(char *s);
void printingText (Player *team, int *numberPlayer);
void saveToFile(Player *team, int *numberPlayer);

int main() {
  int numberPlayer = 0;
  int sizeSquad = 30;
  int userChoose;
  Player *team = creatingArray(&sizeSquad);
  while(userChoose != 6) {
    printf("Please choose which service do you wanna use ? (1 to 5):");
    scanf("%d",&userChoose);
    while(getchar() != '\n');
    switch(userChoose) {
      case 1:
        addingPlayer(team , sizeSquad, &numberPlayer);
      break;
      case 2:
        removingPlayer(team , &numberPlayer);
      break;
      case 3:
        groupingPlayer(team, &numberPlayer); 
      break;
      case 4 :
        printingText (team, &numberPlayer);
      break;
      case 5 :
        saveToFile(team, &numberPlayer);
      break;
      case 6 :
        printf("Thank you for choosing our services\n");
      break;
      default:
        printf("Please Enter a number just beween 1 to 5 \n");
    }
  }

  free(team);


  return 0;
}

Player* creatingArray(int *size) {
  Player *team = malloc((*size) * sizeof(Player));
  if(team == NULL) {
    printf("The allocation is failed\n");
    return NULL;
  }
  return team;
}

void addingPlayer(Player *team ,int size, int *numberPlayer) {
  int addPlayer;
  printf("How many player you wanna add : ");
  scanf("%d",&addPlayer);
  if(addPlayer + *numberPlayer <= size) {
    for(int i = *numberPlayer; i < addPlayer + *numberPlayer; i++) {
      printf("Please Enter the number of %dth player : " , i+1);
      scanf("%d",&team[i].number);
      while(getchar() != '\n');
      printf("Please enter the name of %dth player : ", i+1);
      fgets(team[i].name, sizeof(team[i].name),stdin);
      team[i].name[strcspn(team[i].name,"\n")] = '\0';
      printf("Please enter the position of %dth player : ", i+1);
      fgets(team[i].position, sizeof(team[i].position), stdin);
      team[i].position[strcspn(team[i].position,"\n")] = '\0';
    }
    *numberPlayer = (*numberPlayer) + addPlayer;
  }
  else {
    printf("the squad is full and you can't add any player\n");
  }

}

void removingPlayer (Player *team ,int *numberPlayer) {
  int found = 0;
  char playerName[50];
  printf("Enter the name of player that you want to transfer : ");
  fgets(playerName, sizeof(playerName), stdin);
  playerName[strcspn(playerName,"\n")]= '\0';
  for(int i =0; i < *numberPlayer; i++) {
    if( strcmp(playerName, team[i].name)== 0) {
      for(int j = i; j < *numberPlayer-1; j++) {
        team[j] = team[j+1];
      }
      (*numberPlayer)--;
      found = 1;
    }
  }
  if(found != 1) {
    printf("There is no player in squad that matches with that name\n");
  }
}

void groupingPlayer(Player *team, int *numberPlayer) {
  char position[50];
  int count = 0;
  int found = 0;
  int numberSpecific = *numberPlayer;
  Player *positionSpecific = malloc(*numberPlayer * sizeof(Player));
  if(positionSpecific == NULL) {
    printf("The allocation of position specific failed\n");
  }
  memcpy(positionSpecific, team, *numberPlayer * sizeof(Player));
  printf("which position do you want to show of its player : ");
  fgets(position, sizeof(position), stdin);
  position[strcspn(position,"\n")] = '\0';
  strToLower(position);
  for(int i = 0; i < numberSpecific; i++) {
    if(strcmp(positionSpecific[i].position, position)!= 0) {
        for(int j = i; j  < numberSpecific-1; j++) {
          positionSpecific[j] = positionSpecific[j+1];
        }
        numberSpecific--;
        i--;
        found = 1;
    }
  }
  if(found == 1) {

    for(int i = 0; i < numberSpecific; i++) {
      printf("%d- Number : %d  Name : %s Position : %s \n", i+1, positionSpecific[i].number, positionSpecific[i].name, positionSpecific[i].position);
    }
  } 
  else{
    printf("There is no player with that position in squad\n");
  }
  free(positionSpecific);
}

void strToLower(char *s) {
  for(char *p = s; *p; ++p) {
    *p = (char) tolower((unsigned char)*p);
  }
}

void printingText (Player *team, int *numberPlayer) {
  for(int i = 0; i < *numberPlayer; i++) {
    printf("%d- Number : %d Name : %s Position : %s\n", i+1, team[i].number, team[i].name, team[i].position);
  }
}

void saveToFile(Player *team, int *numberPlayer) {
  FILE *fp =  fopen("players.txt", "w");
  if(fp == NULL) {
    printf("The opening file is failed\n");
  }
  fprinff(fp, "%d\n", *numberPlayer);
  for(int i = 0; i < *numberPlayer; i++) {
    fprintf(fp, "%d Number : %d Name : %s position : %s\n",
    i+1,
    team[i].number,
    team[i].name,
    team[i].position);
  }
  fclose(fp);
  printf("Data saved succecfully\n");
}

