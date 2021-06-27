#include<iostream>

using namespace std;

//This is the Tic-Tac-Toe board on which we are gonna play!

char tictac[3][3] = {
    {'-','-','-',},
    {'-','-','-',},
    {'-','-','-',}
};

//This function returns the number in 3x3 board taking rownumber 
//and column number as input
/*
1|2|3
4|5|6   This is the corresponding positions matched with the board
7|8|9
*/

int positionnumber(int i,int j){
    if(i==0){
        if(j==0) return 1;
        else if(j==1) return 2;
        else return 3;
    }
    else if(i==1){
        if(j==0) return 4;
        else if(j==1) return 5;
        else return 6;
    }
    else{
        if(j==0) return 7;
        else if(j==1) return 8;
        else return 9;
    }
}   

//This functions fills the character in appropriate postion

void fill(int position,char player){
    switch (position)
    {
    case 1:
        tictac[0][0] = player;
        break;
    
    case 2:
        tictac[0][1] = player;
        break;
    
    case 3:
        tictac[0][2] = player;
        break;

    case 4:
        tictac[1][0] = player;
        break;

    case 5:
        tictac[1][1] = player;
        break;

    case 6:
        tictac[1][2] = player;
        break;

    case 7:
        tictac[2][0] = player;
        break;

    case 8:
        tictac[2][1] = player;
        break;

    case 9:
        tictac[2][2] = player;
        break;
    
    default:
        break;
    }
    return;
}

//Function to check wether there are any moves left

bool gamecomplete(char board[3][3]){
    for(int r = 0;r<3;r++){
        for(int c=0;c<3;c++){
            if(board[r][c] == '-') return false;
        }
    }
    return true;
}

//Funtion to check wether any player has won or not

bool victory(char board[3][3],char player){
    for(int r=0;r<3;r++){
        if((board[r][0] ==player) && (board[r][1] ==player) && (board[r][2]==player)){
            return true;
        }
    }
    for(int c=0;c<3;c++){
        if((board[0][c] == player) && (board[1][c] == player) && (board[2][c] == player)){
            return true;
        }
    }
    if ((board[0][0]== player) && (board[1][1] == player) && (board[2][2] == player)){
        return true; 
    } 

    if ((board[0][2]== player) && (board[1][1] == player) && (board[2][0] == player)){
        return true; 
    } 
    
    return false;

}

//Function to display the Tic-tac-toe board

void display(){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout<<tictac[i][j];
            if(j<2) cout<<"|";
        }
        cout<<"\n";
    }
    cout<<"\n";
}


/*
This function is invoked when it's the Human's turn
Takes input position in which the player would like to place his character
*/

void player_turn(char player){
    int position;
    cout<<"Enter position: ";
    cin>>position;
    fill(position,player);
}

/*
Function to check wether a move could make a player win
Returns the position in which the player should make the move
If no move makes the player win, it returns -1
*/

int winning_position(char who){
    
    //There are 4 blocks in this function to check winning along 
    //rows,columns,left diagonal and right diagonal

    //Block 1: Loops to check each row for winning chance

    int row=-1,col=-1;
    for(int i=0;i<3;i++){
        int count = 0;
        col = -1;
        for(int j=0;j<3;j++){
            if(tictac[i][j] == who) count++;
            else if(tictac[i][j] == '-') col = j;
        }
        if(count == 2 && col!=-1){
            int pos = positionnumber(i,col);
            return pos;
        }
    }

    //Block 2: Loops to check each column for winning chance

    row =-1;col =-1;
    for(int j=0;j<3;j++){
        int count = 0;
        row = -1;
        for(int i=0;i<3;i++){
            if(tictac[i][j] == who) count++;
            else if(tictac[i][j] == '-') row = i;
        }
        if(count == 2 && row!=-1){
            int pos = positionnumber(row,j);
            return pos;
        }
    }

    //Block 3: Checking left diagonal for winning chance
    int count=0;
    int diagr=-1,diagcol=-1;

    for(int i=0;i<3;i++){
        if(tictac[i][i] == who) count++;
        else if(tictac[i][i] == '-') diagr = diagcol = i; 
    }

    if(count==2 && diagr!=-1 && diagcol!=-1){
        int pos = positionnumber(diagr,diagcol);
        return pos;
    }

    //Bloack 4: Checking right diagonal for winning chance
    count=0,diagr=-1,diagcol =-1;

    for(int i=0;i<3;i++){
        if(tictac[i][2-i] == who) count++;
        else if(tictac[i][2-i] == '-'){
            diagr = i;
            diagcol = 2-i;
        }
    }

    if(count == 2 && diagr!=-1 && diagcol!=-1){
        int pos = positionnumber(diagr,diagcol);
        return pos;
    }

    //returning -1 if no winning move

    return -1;
}

/*
This function is invoked when it's the computer's turn to play
Fills the optimal position for the computer
*/

void computer_turn(char computer){
    int winningpos;
    char player;

    if(computer == 'x') player = 'o';
    else player = 'x';
    
    winningpos = -1;

    /* WHAT DOES THE FUNCTION DO? :

    First we check if there is a chance to win for the computer, if there it makes that move
    Otherwise we check if there is winning move for the human, if there we block that position
    Otherwise we fill the center first, because it blocks 4 paths to win
    If center is already filled then we check for corners and finally edge positions to fill
    
    */
    
    winningpos = winning_position(computer);         
    if(winningpos!=-1){
        fill(winningpos,computer);
        return;
    }

    winningpos = winning_position(player);
    if(winningpos!=-1){
        fill(winningpos,computer);
        return;
    }

    //checking for center
    if(tictac[1][1] == '-'){
        tictac[1][1] = computer;
        return;
    }
    
    //Go for corners 

    if(tictac[0][0]=='-'){
        tictac[0][0] = computer;
        return;
    }

    else if(tictac[0][2] =='-'){
        tictac[0][2] = computer;
        return;
    }

    else if(tictac[2][0] == '-'){
        tictac[2][0] = computer;
        return;
    }

    else if(tictac[2][2] == '-'){
        tictac[2][2] = computer;
        return;
    }

    //Go for Edge positions
    
    if(tictac[0][1]=='-'){
        tictac[0][1] = computer;
        return;
    }

    else if(tictac[1][2] =='-'){
        tictac[1][2] = computer;
        return;
    }

    else if(tictac[1][0] == '-'){
        tictac[1][0] = computer;
        return;
    }

    else if(tictac[2][1] == '-'){
        tictac[2][1] = computer;
        return;
    }
}

/*
Suppose the board is like this:
- - x            x - -
- o -     OR     - o -
x - -            - - x

If a corner is empty the computer move function will greedily choose a corner,
but it makes the opponent win.
So we must choose an edge postion(i.e 2,4,6,8) to stop the human from winning 

diagoanl_trapcheck() function return true if formation is like mentioned above
*/

bool diagonal_trapcheck(char player){
    char opp;
    if(player == 'x') opp='o';
    else opp = 'x';

    if(tictac[0][0]==player && tictac[2][2]==player && tictac[1][1]==opp){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if((i==0 && j==0) || (i==2&& j==2) || (i==1 && j==1)) continue;
                if(tictac[i][j]!='-') {
                    return false;
                }
            }
        }
        return true;
    }

    else if(tictac[2][0]==player && tictac[0][2]==player && tictac[1][1]==opp){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if((i==2 && j==0) || (i==0 && j==2) || (i==1 && j==1)) continue;
                if(tictac[i][j]!='-') {
                    return false;
                }
            }
        }
        return true;
    }

    return false;
}   

//The main function, Everything starts here :))

main(){
    
    //Infinite loop, breaks out when player chooses not to play
    while(1){
        
        //making the board empty again for next game

        for(int i=0;i<3;i++){
            for(int j =0;j<3;j++) tictac[i][j] = '-'; 
        }

        cout<<"Do you wish to play first or second?(x:first player o:second player): ";
        char player,computer;

        cin>>player;
        if(player == 'x') computer = 'o';
        else computer = 'x';

        display();
        cout<<"Start: \n\n";

        //There are two while(1) loops similar to each other, the only difference is the order of play
        //In first loop human plays first and in second loop computer plays first

        if(player == 'x'){
            
            //Loop breaks when either a player wins,or it's a draw.

            while(1){

                //First check wether any player has won or no moves left 

                if(victory(tictac,player)){
                    cout<<"You won against Computer :)\n";
                    break;
                }                                                      

                else if(victory(tictac,computer)){
                    cout<<"Computer won :(\n";
                    break;
                }
                                                                        
                else if(gamecomplete(tictac)){                   
                    cout<<"Match Drawn! :)\n";
                    break;
                }

                
                player_turn(player);
                display();

                //once the player plays we check is human is trying to trap the computer diagonally,
                //If yes we fill any edge position and continue

                if(diagonal_trapcheck(player)){
                    int edges[4][2] = {{0,1},{1,2},{2,1},{1,0}};
                    int flag = 0;
                    for(int i=0;i<4;i++){
                        int row = edges[i][0];
                        int col = edges[i][1];
                        if(tictac[row][col] == '-'){
                            tictac[row][col] = computer;
                            flag=1;
                            cout<<"Computer Played:\n";
                            display();
                            break;
                        }
                    }
                    if(flag) continue;
                }

                //Checking for victories and draw again

                if(victory(tictac,player)){
                    cout<<"You won against Computer :)\n";
                    break;
                }

                else if(victory(tictac,computer)){
                    cout<<"Computer won :(\n";
                    break;
                }

                else if(gamecomplete(tictac)){
                    cout<<"Match Drawn! :)\n";
                    break;
                }

                computer_turn(computer);
                cout<<"Computer Played: \n";
                display();
                
            }
        }

        else{

            //Loop breaks when either a player wins,or it's a draw.
            //The second while loop where computer plays first
            //rest all similar to previous while loop

            while(1){
                    if(victory(tictac,player)){
                    cout<<"You won against Computer :)\n";
                    break;
                }

                else if(victory(tictac,computer)){
                    cout<<"Computer won :(\n";
                    break;
                }

                else if(gamecomplete(tictac)){
                    cout<<"Match Drawn! :)\n";
                    break;
                }

                computer_turn(computer);
                cout<<"Computer Played: \n";
                display();

                if(victory(tictac,player)){
                    cout<<"You won against Computer :)\n";
                    break;
                }

                else if(victory(tictac,computer)){
                    cout<<"Computer won :(\n";
                    break;
                }

                else if(gamecomplete(tictac)){
                    cout<<"Match Drawn! :)\n";
                    break;
                }

                player_turn(player);
                display();
            }
        }

        cout<<"Do you wish to play another game?(Enter 'y' is Yes)\n";
        char response;
        cin>>response;
        if(response == 'y') continue;
        else break;
    }
}

/*
MEANING FOR VARIABLES USED IN MAIN FUNCTION:
Variable                     |           Meaning
1.player,computer(char)      | denotes which player is x and which is o.Also not x should play first always
2.flag(int)                  | if diagonal_tap() function is true, helps to continue the loop without running below
3.edges(2D 4x2 int array)    | stores all edge positions(i.e 2,4,6,8)
4.response(char)             | y or n according to player's wish to play another game   
*/
