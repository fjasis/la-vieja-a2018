#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
//#include"viejav2.c"

typedef struct {//Move
    int fil, col;
}Movida;
int oponente;
 
char caracterus ;

char caracteroponente(char caracterus){
    if(caracterus=='X'){
        oponente='O';
    }
    else if(caracterus=='O'){
        oponente='X';
    }
}

// This function returns true if there are moves
// remaining on the board. It returns false if
// there are no moves left to play.
bool Siquedanmovimientos(char matriz[3][3]){//ismovesleft
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++)
            if (matriz[i][j]==' ')
                return true;
    return false;
}
 
// This is the evaluation function as discussed
// in the previous article ( http://goo.gl/sJgv68 )
int evaluacion(char b[3][3]){//evaluate
    int fil,col;
    // Checking for Rows for X or O victory.
    for (fil = 0; fil<3; fil++)
    {
        if (b[fil][0]==b[fil][1] &&b[fil][1]==b[fil][2]){
            if (b[fil][0]==caracterus){
                return +10;
            }
            else if (b[fil][0]==oponente){
                return -10;
            }
        }
    }
 
    // Checking for Columns for X or O victory.
    for (col = 0; col<3; col++)
    {
        if (b[0][col]==b[1][col] &&b[1][col]==b[2][col])
        {
            if (b[0][col]==caracterus){
                return +10;
            }
            else if (b[0][col]==oponente){
                return -10;
            }
        }
    }
 
    // Checking for Diagonals for X or O victory.
    if (b[0][0]==b[1][1] && b[1][1]==b[2][2])
    {
        if (b[0][0]==caracterus){
            return +10;
        }
        else if (b[0][0]==oponente){
            return -10;
        }
    }
 
    if (b[0][2]==b[1][1] && b[1][1]==b[2][0])
    {
        if (b[0][2]==caracterus){
            return +10;
        }
        else if (b[0][2]==oponente){
            return -10;
        }
    }
 
    // Else if none of them have won then return 0
    return 0;
}
 
// This is the minimax function. It considers all
// the possible ways the game can go and returns
// the value of the board
int minimax(char matriz[3][3], int depth, bool isMax)
{
    int puntaje = evaluacion(matriz);
    int i,j;
 
    // If Maximizer has won the game return his/her
    // evaluated score
    if (puntaje == 10){
        return puntaje;
    }
 
    // If Minimizer has won the game return his/her
    // evaluated score
    if (puntaje == -10){
        return puntaje;
    }
 
    // If there are no more moves and no winner then
    // it is a tie
    if (Siquedanmovimientos(matriz)==false){
        return 0;
    }
 
    // If this maximizer's move
    if (isMax){
        int mejor = -1000; //best
 
        // Traverse all cells
        for (i=0;i<3;i++){
            for (j=0;j<3;j++){
                // Check if cell is empty
                if (matriz[i][j]==' '){
                    // Make the move
                    matriz[i][j] = caracterus;
 
                    // Call minimax recursively and choose
                    // the maximum value
                    mejor = fmax( mejor,
                        minimax(matriz, depth+1, !isMax) );
 
                    // Undo the move
                    matriz[i][j] = ' ';
                }
            }
        }
        return mejor;
    }
 
    // If this minimizer's move
    else
    {
        int mejor = 1000;
 
        // Traverse all cells
        for (i = 0; i<3; i++)
        {
            for (j = 0; j<3; j++)
            {
                // Check if cell is empty
                if (matriz[i][j]==' ')
                {
                    // Make the move
                    matriz[i][j] = oponente;
 
                    // Call minimax recursively and choose
                    // the minimum value
                    mejor = fmin(mejor,
                           minimax(matriz, depth+1, !isMax));
 
                    // Undo the move
                    matriz[i][j] = ' ';
                }
            }
        }
        return mejor-depth;
    }
}
 
// This will return the best possible move for the player
Movida buscamejormovida(char matriz[3][3]){//findBestove
    int mejorVal = -1000; int i,j;
    Movida mejormovida;
    mejormovida.fil = -1;
    mejormovida.col = -1;
 
    // Traverse all cells, evalutae minimax function for
    // all empty cells. And return the cell with optimal
    // value.
    for (i = 0; i<3; i++){
        for (int j = 0; j<3; j++){
            // Check if celll is empty
            if (matriz[i][j]==' '){
                // Make the move
                matriz[i][j] = caracterus;
 
                // compute evaluation function for this
                // move.
                int movidaVal = minimax(matriz, 0, false);
 
                // Undo the move
                matriz[i][j] = ' ';
 
                // If the value of the current move is
                // more than the best value, then update
                // best/
                if (movidaVal > mejorVal)
                {
                    mejormovida.fil = i;
                    mejormovida.col = j;
                    mejorVal = movidaVal;
                }
            }
        }
    }
 
    printf("The value of the best Move is : %d\n\n",mejorVal);
    
    return mejormovida;
}
 
// Driver code
