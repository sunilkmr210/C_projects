#include <stdio.h>

#define X -1
#define O -2
#define MAX_SIZE 50 //This is the Max size of the Input Buffer

int turn = O; 

int board[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

int variations = 0; //To keep track of no. of variations the ai has seen

void copyBoard(int from[], int to[]){
    for(int i = 0; i < 9; i++){
        to[i] = from[i];
    }
}

//gets line WITHOUT \n 
int getl(char s[], int lim){
    int c, i;

    for(i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    
    s[i] = '\0';
    return i;
}

//Converts char[] to int
int bufferToNum(char buffer[]){
    int n = 0;
    for(int i = 0; buffer[i] != '\0'; i++){
        n = 10 * n + buffer[i] - '0';
    }
    return n;
}

//converts the board numbers to char to display
char boardToChar(int i){
    int a = board[i];
    if (a == X){        
        return 'X';
    } else if (a == O){
        return 'O';
    } else {    
       return a + '0';
    }    
}

//prints board
void printBoard(){
    printf("=============\n| %c | %c | %c |\n-------------\n| %c | %c | %c |\n-------------\n| %c | %c | %c |\n=============\n", boardToChar(0), boardToChar(1), boardToChar(2), boardToChar(3), boardToChar(4), boardToChar(5), boardToChar(6), boardToChar(7), boardToChar(8));    
}

//alternates turn
void alternateTurn(){
    if (turn == O){
        turn = X;    
    } else if (turn == X){
        turn = O;
    }
}

//returns 1 if draw, return 0 if not a draw
int drawCheck(int l_board[]){
    for(int i = 0; i < 9; i++){
        if (l_board[i] == i+1){
            return 0;
        }
    }
    return 1;
}

//returns X if X won and O if O one and 0 if nobody winning
int winCheck(int l_board[]){
    //Rows
    for (int i = 0; i < 3; i++){
        if (l_board[3*i] == l_board[3*i + 1] && l_board[3*i + 1] == l_board[3*i + 2]){
            return l_board[3*i];
        }
    }

    //Columns
    for (int j = 0; j < 3; j++){
        if (l_board[j] == l_board[3 + j] && l_board[3 + j] == l_board[6 + j]){
            return l_board[j];
        }
    }

    //Diagonal Top Left to Bottom Right
    if (l_board[0] == l_board[4] && l_board[0] == l_board[8]){
        return l_board[0];
    }

    //Diagonal Top Right to bottom Left
    if (l_board[2] == l_board[4] && l_board[2] == l_board[6]){
        return l_board[2];
    }

    return 0;
}

//1 if nothing is ther and 0 if something was already ther
int putInBoard(int l_board[], int pos, int newVal){
    if (l_board[pos] == pos+1){
        l_board[pos] = newVal;
        return 1;
    } else
    {
        return 0;
    }    
}

//X if X win, O if O win, 0 if draw, 1 if nothing
int gameState(int l_board[]){
    int wc = winCheck(l_board);
    if (wc == X){
        return X;
    } else if(wc == O){
        return O;
    } else {
        if (drawCheck(l_board)){
            return 0;
        }
    }
    return 1;
}

void legalMoves(int l_board[], int output[]){    
    for(int i = 0; i < 9; i++){
        if (l_board[i] == i+1){
            output[i] = 1;
        } else {
            output[i] = 0;
        }
    }
}

int max(int a, int b){
    return a>b ? a : b;
}

int min(int a, int b){
    return a<b ? a : b;
}

//X is ai
int minimax(int l_board[], int depth, int maximising){
    int gs = gameState(l_board);
    variations++;
    if (gs == X){
        return 10;
    } else if (gs == O){
        return -10;
    } else if (gs == 0){
        return 0;
    }
    if (depth == 0){
        return 0;
    }
    if (maximising){
        //Its AI's Turn so it has to maximise
        int val = -100;
        int legalMovesArr[9];
        legalMoves(l_board, legalMovesArr);
        for (int i = 0; i < 9; i++){
            if (legalMovesArr[i]){
                int tempBoard[9];
                copyBoard(l_board, tempBoard);
                putInBoard(tempBoard, i, X);
                val = max(minimax(tempBoard, depth-1, 0), val);
            }
        }
        return val;
    } else {        
        int val = 100;
        int legalMovesArr[9];
        legalMoves(l_board, legalMovesArr);
        for (int i = 0; i < 9; i++){
            if (legalMovesArr[i]){
                int tempBoard[9];
                copyBoard(l_board, tempBoard);
                putInBoard(tempBoard, i, O);
                val = min(minimax(tempBoard, depth-1, 1), val);
            }
        }
        return val;
    }
}

int ai(int l_board[], int depth){
    int legalMovesArr[9];
    legalMoves(board, legalMovesArr);
    int val = -100;    
    int best_move = 0;
    for (int i = 0; i < 9; i++){
        if (legalMovesArr[i]){
            int tempBoard[9];
            copyBoard(l_board, tempBoard);
            putInBoard(tempBoard, i, X);
            int temp = minimax(tempBoard, depth-1, 0);
            if (val <= temp){
                val = temp;
                best_move = i;
            }            
        }
    }
    return best_move;
}

int main(){
    printBoard();
    int gameOn = 0;
    char buffer[MAX_SIZE];
    while(!gameOn){
        if (turn == O){
            printf("%c's turn: ", turn == X ? 'X' : 'O');
            getl(buffer, MAX_SIZE);
            int num = bufferToNum(buffer);        
            while (num <= 0 || num > 9){
                printf("Please enter an integer between 1 and 9: ");
                getl(buffer, MAX_SIZE);
                num = bufferToNum(buffer);            
            }
            if (putInBoard(board, num-1, turn)){
                ;
            } else {            
                while(!putInBoard(board, num-1, turn)){
                    printf("Something already exists, Please enter a new number: ");
                    getl(buffer, MAX_SIZE);
                    num = bufferToNum(buffer);
                }
            }
        } else {
            putInBoard(board, ai(board, 8), X);
            printf("Calculated %d variations\n", variations);
            variations = 0;
        }
        
        printBoard();                
        alternateTurn();
        int gs = gameState(board);
        if (gs == X){
            printf("X won!");
            return 0;
        } else if (gs == O){
            printf("O won!");
            return 0;
        } else if (gs == 0){
            printf("Draw!");
            return 0;
        }           
    }
    
    return 0;
}