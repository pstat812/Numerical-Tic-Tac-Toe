#include <stdio.h>

void getbestmove(int gameBoard[3][3],int bestmove[2]);
void printInfo(int gameBoard[3][3], int numbers[9]) {
    for (int i=2;i>=0;i--){
      for (int j=0;j<3;j++){
            printf("|");
            if (gameBoard[i][j] == 0){
              printf(" ");
            }else{
            printf("%d",gameBoard[i][j]);
          }
        }
     printf("|\n");
    }

  
  printf("Unused numbers:\n");
   for (int i=0;i<9;i++){
    if (numbers[i] == 0){
     printf("%d",i+1); 
     printf(" ");
    }
  }
   printf("\n");
}  
//return 1 if the position input is valid. If invalid,print a message and return 0
int checklegalposition(int gameBoard[3][3],char input){
  int legal = 1;
  
   if ((input < 49)||(input > 57)) {
      legal = 0;
      printf("you can only enter a number from 1-9\n");
     }

   else {
      int boardy = 0;
      int boardx = input-48;
      while (boardx > 3) {
       boardy += 1;
       boardx -= 3;
   }
      boardx --;
      if (gameBoard[boardy][boardx] != 0){
      legal = 0;
       printf("The position has been used\n");
      }
    }
  return legal;
}

//return 1 if the number input is valid. If invalid,print a message and return 0
int checklegalnumber(int numbers[9],char input){
  int legal = 1;
  
  if ((input < 49)||(input > 57)) {
     legal = 0;
     printf("you can only enter a number from 1-9\n");
    }
  
  else if ((input-48)%2 != 1){
     legal = 0;
     printf("you can only choose odd number\n");  
  }

  else if (numbers[(input-48)-1] != 0){
     legal = 0;
     printf("The number has been used\n");
    }
  return legal;
}



void placeNumber(int gameBoard[3][3], int numbers[9], int currentPlayer) {
  char first_input;
  char next_input;   
  int islegal = 0;
  int position,number;

  if (currentPlayer == 1){
      printf("### Player %d's turn ###",currentPlayer);
      printf("\n");
 //prompt user input if position is not valid
    while (islegal != 2){
       islegal = 0;
       printf("Input the position: ");
 //check is the input a single-digit character
       first_input = getchar();
       next_input = getchar();
      if (next_input == '\n'){
       islegal = 1;
      } 
  //clear input buffer
       while (next_input != '\n'){
        next_input = getchar();
      }
   //use function to valid input   
  if (islegal == 1){
   islegal += checklegalposition(gameBoard,first_input);
  } else {
    printf("You can only input 1 digit number from 1-9\n");
  }
}

   position = first_input-48;
   islegal  = 0;
  
  //prompt user input if number is not valid  
    while (islegal != 2){
        islegal  = 0;
        printf("Input the number: ");
  //check is the input a single-digit character
       first_input = getchar();
       next_input = getchar();
    if (next_input == '\n'){
         islegal  += 1;
     } 
   //clear input buffer
  while (next_input != '\n'){
     next_input = getchar();
 } 
    //use function to valid input 
   if (islegal == 1){
   islegal += checklegalnumber(numbers,first_input);   
     }else {
    printf("You can only input 1 digit number from 1-9\n");
   }
  }

   number = first_input-48;
}  

  //computer round, call the getbestmove function to get the best position and number in bestmove[] array
 if (currentPlayer == 2){
  printf("\nLoading......, please wait about a few seconds\n");
  int bestmove[2] = {0,0};
  getbestmove(gameBoard,bestmove);
  printf("### Player %d's turn ###",currentPlayer);
  printf("\n");
  position = bestmove[0];
  number = bestmove[1];
  printf("Input the position: %d\n",position);
  printf("Input the number: %d\n",number);
  }
  
  //update number used
  numbers[number-1] = 1;
  
  //update the gameboard content;
  int boardy = 0;
  int boardx = position;
  while (boardx > 3) {
    boardy += 1;
    boardx -= 3;
  }
  boardx --;
  gameBoard[boardy][boardx] = number;
}   

int hasWinner(int gameBoard[3][3]){
   int haswin = 0;
  int horizontalsum = 0;
  int verticalsum = 0;
  int leftdiagonalsum = 0;
  int rightdiagonalsum = 0;

   for (int i=0;i<3;i++){
      leftdiagonalsum += gameBoard[i][i];
      rightdiagonalsum += gameBoard[i][2-i];
     
      if (gameBoard[i][i] == 0){  
        leftdiagonalsum  = 100;   
       } 
      if (gameBoard[i][2-i] == 0){
        rightdiagonalsum  = 100;   
     } 
     
     horizontalsum = 0;
     verticalsum = 0;
     
    for (int j=0;j<3;j++){  
      horizontalsum += gameBoard[i][j];
      verticalsum += gameBoard[j][i];  
      
     if (gameBoard[i][j] == 0){
        horizontalsum = 100;
       }   
    if (gameBoard[j][i] == 0){
        verticalsum  = 100;   
       } 
   } 
     
   if ((horizontalsum == 15)||(verticalsum == 15)){
       haswin = 1;     
  }     
} 
  
   if ((leftdiagonalsum == 15)||(rightdiagonalsum == 15)){
       haswin = 1; 
     }
  
 return haswin;
} 

int isFull(int gameBoard[3][3]) {
    int placedCount = 0;
    for (int i=0;i<3;i++){
        for (int j=0;j<3;j++){
           if (gameBoard[i][j] != 0){
             placedCount += 1;
           }
        }  
    }
     if (placedCount == 9) {
          return 1;
      }else {
          return 0;
    }
} 

//function of find not used number from the board and output to a length 9 array
void notused_num(int gameBoard[3][3],int output[9],int isplayer){
      for (int i=0;i<9;i++){
        output[i] = 0;
      }
      int temp;
       for (int i=0;i<3;i++){
         for (int j=0;j<3;j++){
           if (gameBoard[i][j] > 0){
               temp = gameBoard[i][j]-1;
               output[temp] = 1;
                }
             }
         }
 if (isplayer == 1){
  output[1] = 1;
  output[3] = 1; 
  output[5] = 1;
  output[7] = 1;
 } else{
 output[0] = 1;
 output[2] = 1;
 output[4] = 1; 
 output[6] = 1;
 output[8] = 1;
 }
}

//function of find not used position from the board and output to a length 9 array
void notused_pos(int gameBoard[3][3],int output[9]){
  int index = 0;
    for (int i=0;i<3;i++){
         for (int j=0;j<3;j++){
             if(gameBoard[i][j]==0){ 
                 output[index] = 0;             
             }else
               output[index] = 1;
           index++;
    }
  } 
}

//return actual length of number or position for create another shorter array
int arraylength(int a[9]){
  int count = 0;
    for (int i=0;i<9;i++){
       if (a[i] == 0){
         count++;
       }  
    }  
  return count;
}

//function of create a shorter array 
void create_short_array(int input[9],int output[]){
    int index = 0;
   for (int i=0;i<9;i++){
        if (input[i] == 0){
          output[index] = i+1;
          index++;
        }
   }
}

//function of create a temp board and add a new move
void newboard(int position,int number,int gameBoard[3][3],int newBoard[3][3]){
      for (int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            newBoard[i][j] = gameBoard[i][j];     
        }
      }     
  int boardy = 0;
  int boardx = position;
  while (boardx > 3) {
    boardy += 1;
    boardx -= 3;
  }
  boardx --;
  newBoard[boardy][boardx] = number;
}

//function of find the highest score of new move in all variation by minimax algorthm
int movescore(int gameBoard[3][3],int maxscore,int depth_score){
  //return score if end game
  if ((hasWinner(gameBoard) == 1)&&(maxscore == 1)){
     return -depth_score ;     
}
 if ((hasWinner(gameBoard) == 1)&&(maxscore == 0)){
     return depth_score ;     
}
   if (isFull(gameBoard)==1){
 return 0;
}
int score,temp;
//creating a shortest array for recursion
int remain_pos[9];
int remain_num[9];  
if (maxscore == 1){ 
       score = -1000;
       notused_num(gameBoard,remain_num,0);
}      
else {
      score = 1000;
    notused_num(gameBoard,remain_num,1);
}
notused_pos(gameBoard,remain_pos);
int num_length = arraylength(remain_num);
int pos_length = arraylength(remain_pos);
int num_array[num_length];
int pos_array[pos_length]; 
create_short_array(remain_num, num_array);
create_short_array(remain_pos, pos_array);

//recursion to get max or min score from the new board 
for (int i = 0; i < pos_length; i++){
for (int j = 0; j < num_length; j++){
int newBoard[3][3];
newboard(pos_array[i],num_array[j],gameBoard,newBoard);
if (maxscore == 1){
      temp = movescore(newBoard,0,depth_score-1);
      if (temp > score)
       score = temp;
 } else 
      {  
      temp = movescore(newBoard,1,depth_score-1);
      if (temp < score)
          score = temp;
      }
    }    
  }
  
  return score;
} 

//function of return the best position and number chosen to bestmove[2]
void getbestmove(int gameBoard[3][3],int bestmove[2]){
  //create a a shorter array for looping 
    int highest_score = -1000;
    int remain_pos[9];
    int remain_num[9];
    notused_num(gameBoard,remain_num,0);
    notused_pos(gameBoard,remain_pos);
    int num_length = arraylength(remain_num);
    int pos_length = arraylength(remain_pos);
    int num_array[num_length];
    int pos_array[pos_length]; 
    create_short_array(remain_num, num_array);
    create_short_array(remain_pos, pos_array);
  //looping for finding the move of higest score
   for (int i=0;i<pos_length;i++){
      for (int j=0;j<num_length;j++){ 
        int newBoard[3][3];
        newboard(pos_array[i],num_array[j],gameBoard,newBoard);
        int temp = movescore(newBoard,0,8);
        if (temp > highest_score){
           highest_score = temp;
           bestmove[0] = pos_array[i];
           bestmove[1] = num_array[j];
        }
    }
  }
}


int main() {
     int gameBoard[3][3] = {0}; 
     int numbers[9] = {0};         
     int currentPlayer;           
     int gameContinue;                 
     currentPlayer = 1;
     gameContinue = 1;
 
while (gameContinue == 1) {
printInfo(gameBoard,  numbers);
placeNumber(gameBoard, numbers,currentPlayer);
  
 if (hasWinner(gameBoard) == 1){
      gameContinue = 0;
      printInfo(gameBoard,  numbers);
      printf("Congratulations! Player %d wins!",currentPlayer);
   
}else if (isFull(gameBoard)== 1){
      gameContinue = 0;
      printInfo(gameBoard,  numbers);
      printf("Draw game.");      
}

      if (currentPlayer == 1) {
            currentPlayer = 2;  
        } else {
            currentPlayer = 1; 
     }  
    
  } 
  return 0;
} 
