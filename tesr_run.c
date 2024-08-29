#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BOARD_SIZE 52
#define PIECE_FOR_PLAYER 4
#define PLAYERS 4
#define NUM_OF_BLOCKS 2
#define TOTAL_FAR_TO_END 52

struct Piece
{
    int position;
    int isHome;
    int isBoard;
    int isXplace;
    int isInblock;
    int direction; /// clockwise - heads[1](1) counterclockwise - tail[2](-1)
    int forToend;
    int cutCount;
};
struct Blocks
{
    int block_1Position;
    int block_1Active;
    int block_1count;
    int block_1direction;
    int block_2Position;
    int block_2Active;
    int block_2count;
    int block_2direction;
};
struct Player
{
    struct Piece pieces[PIECE_FOR_PLAYER];
    struct Blocks blocks;
    char color[8];
    int playerId;
    int isXPlace;
};
typedef struct {
    int id;
    int group;
    int byCapIndex;
    int farToEnd;
} piece1;

typedef struct {
    piece1 pieces[PIECE_FOR_PLAYER];
} cutItem;

cutItem tempArray2[PIECE_FOR_PLAYER];
int livePlayer = 0;
int red_movePiece;
static int tempBlock = -1;
struct Player players[PLAYERS];
// initialize Players
void definePlayers(struct Player *players)
{
    for (int index = 0; index < PLAYERS; index++)
    {
        players[index].playerId = index + 1;
        players[index].isXPlace = 0;
        strcpy(players[index].color, (index == 0) ? "RED" : (index == 1) ? "GREEN"
                                                        : (index == 2)   ? "YELLOW"
                                                                         : "BLUE");
        players[index].blocks.block_1Active = 0;
        players[index].blocks.block_1count = 1;
        players[index].blocks.block_1Position = 0;
        players[index].blocks.block_1direction = 1;//
        players[index].blocks.block_2Active = 0;
        players[index].blocks.block_2count = 1;
        players[index].blocks.block_2Position = 0;
        players[index].blocks.block_2direction = -1;//

        for (int index2 = 0; index2 < PIECE_FOR_PLAYER; index2++)
        {
            players[index].pieces[index2].isHome = 0;
            players[index].pieces[index2].position = 0;
            players[index].pieces[index2].isBoard = 0;
            players[index].pieces[index2].isXplace = 0;
            players[index].pieces[index2].isInblock = 1; // 1  mean piece not in block
            players[index].pieces[index2].direction = 0;
            players[index].pieces[index2].forToend = (BOARD_SIZE -1);
            players[index].pieces[index2].cutCount = 0;
        }
    }
    printf("\t\t>> \033[1m\033[4m\033[45mGAME PLAYERS ARE READY\033[0m\033[0m\033[0m <<\n");
}
//reset function
void resetTempArray2(){
    printf("reset temp2 array\n");
    for (int index = 0; index < PLAYERS; index++){
        for (int index2 = 0; index2 < PIECE_FOR_PLAYER; index2++){
            tempArray2[index].pieces[index2].byCapIndex = 0;
            tempArray2[index].pieces[index2].farToEnd = 0; 
            tempArray2[index].pieces[index2].group = 0;
            tempArray2[index].pieces[index2].id = 0;   
        }
    }
printf("temp 2 updated\n");
}
// update pieces(this use at moving )
void updateEndFar(int index1, int index2,int diceValue){
    if(players[index1].pieces[index2].isBoard){
        players[index1].pieces[index2].forToend -= diceValue;
    }}
    // rolling dice function
int rollingDice(int diceCounter)
{
    int diceValue = (rand() % 6) + 1;
    printf(">> \033[1mThis is %d chance\033[0m \n", diceCounter);
    if (diceCounter == 3)
    {
        if (diceValue == 6)
        {
            return 0;
        }
    }
    printf("Dice value = %d\n", diceValue);
    return diceValue;
}
// coin toss function
int coinToss()
{
    printf(" >> Coin tossing\n");
    int tossValue = (rand() % 2) + 1;
    if (tossValue == 1)
    {
        printf(">> Got HEAD \n>> This piece go clockwise direction\n");
        return 1;
    }
    else
    {
        printf(">> Got TAIL \n>> This piece go Counterclockwise direction\n");
        return -1;
    }
}
void isWinPlace(int index){
    if (players[livePlayer].pieces[index].position == (livePlayer == 0) ? 51 : (livePlayer == 1) ? 12 :(livePlayer == 0) ? 25 : 38 ){
        players[livePlayer].pieces[index].isHome = 1;
        players[livePlayer].pieces[index].isBoard = 0;
         printf(">> Welcome to home piece %d\n",index);
    }
}
void isBlock(int index)
{
    if (tempBlock > 0)//??????????????????????????
    {
        tempBlock = -1; // this argument is imposible
    }
    //  printf("*****************************************************************************************************************test3\n");
    for (int index2 = 0; index2 < PIECE_FOR_PLAYER; index2++)
    {
        if (index2 == index)
        {
        }
        else
        {
            // printf("*****************************************************************************************************************test4\n");
            if ((players[livePlayer].pieces[index].position == players[livePlayer].pieces[index2].position) )
            {
                // printf("*****************************************************************************************************************test5\n");
                players[livePlayer].pieces[index].isInblock = 0;  // 0 means this piece in a block
                players[livePlayer].pieces[index2].isInblock = 0; // same
                printf(" \t\t\t>> \033[45mCreat a Block for (%s) at position %d and pieces : %d,\033[0m ", players[livePlayer].color, index, players[livePlayer].pieces[index].position);
                printf("%d,", index2);
                if (tempBlock == -1)
                {
                    players[livePlayer].blocks.block_1Position = players[livePlayer].pieces[index].position;
                    players[livePlayer].blocks.block_1Active = 1;
                    printf(">> Location of block : %d\n", players[livePlayer].blocks.block_1Position);
                    //if make a data type in struct like - count data in block in hear we can count them;
                    players[livePlayer].blocks.block_1count++; // can not understand
                }
                else
                {
                    players[livePlayer].blocks.block_2Position = players[livePlayer].pieces[index].position;
                    players[livePlayer].blocks.block_2Active = 1;
                    printf(">> Location of block : %d\n", players[livePlayer].blocks.block_2Position);
                    players[livePlayer].blocks.block_2count++;// can not understand
                }
            }

            // printf("\n");
        }
    }
    printf("\n");
    tempBlock++;
}

//
int directionWiseMove(int index, int diceValue, int notPrint)
{   if(players[livePlayer].pieces[index].isBoard && !players[livePlayer].pieces[index].isHome){
    if (players[livePlayer].pieces[index].direction == 1)
    {
        if( notPrint){
        int check = directionWiseMove(index,diceValue,0);
            for(int i = 0; i < PLAYERS; i++){
            if(i == livePlayer){}
            else{
                if ((players[livePlayer].pieces[index].position < players[i].blocks.block_1Position) && (players[i].blocks.block_1Position <= check) ){
                    // thawa blpn
                    diceValue = (players[i].blocks.block_1Position - players[livePlayer].pieces[index].position) - 1;// normsl only but it not work for when is on 1 and 52

                }
                else if( ((players[livePlayer].pieces[index].position < players[i].blocks.block_2Position) && (players[i].blocks.block_2Position <= check))){
                    diceValue = (players[i].blocks.block_1Position - players[livePlayer].pieces[index].position) - 1;
                }
                }
            }
        printf("....................test1\n");
        players[livePlayer].pieces[index].position = ((players[livePlayer].pieces[index].position + diceValue) == 52) ? 52 : ((players[livePlayer].pieces[index].position + diceValue) % BOARD_SIZE);
        players[livePlayer].pieces[index].forToend -= diceValue;
        printf(">> %s player piece(%d) moves to position %d\n", players[livePlayer].color, index, players[livePlayer].pieces[index].position);
        if( players[livePlayer].pieces[index].position == ((livePlayer) == 0 ? 51 : (livePlayer) == 1 ? 12 : (livePlayer) == 2 ? 25 : 38)){
            players[livePlayer].pieces[index].isHome = 1;
            players[livePlayer].pieces[index].isBoard = 0;
            printf(">> Welcome to home piece %d\n",index);
        }
        return 1;
    }
    else{
         int tempPosition = ((players[livePlayer].pieces[index].position + diceValue) == 52) ? 52 : ((players[livePlayer].pieces[index].position + diceValue) % BOARD_SIZE);
         return tempPosition;
    }}
    else
    {
       
        if ((players[livePlayer].pieces[index].position <= 6) && (players[livePlayer].pieces[index].position >= 1) && (players[livePlayer].pieces[index].position == diceValue))
        {
            if (notPrint){
            printf("....................test-1\n");
            players[livePlayer].pieces[index].position = 52;
            players[livePlayer].pieces[index].forToend -= diceValue;
            printf("........................anuthu move from tail\n");
             
            printf(">> %s player piece(%d) moves to position %d\n", players[livePlayer].color, index, players[livePlayer].pieces[index].position);
            return 1;
        }
        else{
            int tempPosition = 52;
            return tempPosition;
        }}
        else
        {
             if(notPrint){
            int check = directionWiseMove(index,diceValue,0);
            
            for(int i = 0; i < PLAYERS; i++){
            if(i == livePlayer){}
            else{
                if ((players[livePlayer].pieces[index].position >= players[i].blocks.block_1Position) && (players[i].blocks.block_1Position >= check) ){
                    // thawa blpn
                    diceValue = (players[livePlayer].pieces[index].position - players[i].blocks.block_1Position) - 1 ;// normsl only but it not work for when is on 1 and 52

                }
                else if( ((players[livePlayer].pieces[index].position >= players[i].blocks.block_2Position) && (players[i].blocks.block_2Position >= check))){
                    diceValue = (players[livePlayer].pieces[index].position - players[i].blocks.block_2Position) -1 ;
                }
                }
            }
            
            players[livePlayer].pieces[index].position = ((BOARD_SIZE + (players[livePlayer].pieces[index].position - diceValue)) % BOARD_SIZE);
            players[livePlayer].pieces[index].forToend -= diceValue;
            printf("....................test-1(b)\n");
            
                        
            printf(">> %s player piece(%d) moves to position %d\n", players[livePlayer].color, index, players[livePlayer].pieces[index].position);
            if( players[livePlayer].pieces[index].position == ((livePlayer) == 0 ? 51 : (livePlayer) == 1 ? 12 : (livePlayer) == 2 ? 25 : 38)){
            players[livePlayer].pieces[index].isHome = 1;
            printf(">> Welcome to home piece %d\n",index);
        }
            return 1;
        }
            else{
                int tempPosition = ((BOARD_SIZE + (players[livePlayer].pieces[index].position - diceValue)) % BOARD_SIZE);
                return tempPosition;
    }
        }
    } /// X wala blocks hadenn puluwand?yes it can be happen
    if( notPrint){
    isBlock(index);
    return 0;
    }
}}
//
int canMove(int livePlayer, int dicevalue, int index)
{

    if (players[livePlayer].pieces[index].position == 0 && dicevalue != 6)
    {
        return 0;
    }

    if (players[livePlayer].pieces[index].isHome)
    { // Win box == is home
        return 0;
    }
    if (players[livePlayer].pieces[index].isInblock == 0)
    {
        return 2;
    }
    return 1;
}
// which piece can move
int who_is_move(int livePlayer, int diceValue)
{
    for (int index = 0; index < PIECE_FOR_PLAYER; index++)
    {
        int tempIndex = canMove(livePlayer, diceValue, index);
        if (tempIndex)
        {

            if (tempIndex == 2)
            {
                printf("in block'''''''''''''''''''\n");
                if(players[livePlayer].blocks.block_2Active){
                     printf("in 2block'''''''''''''''''''\n");
                return 5;// block 2 active means 1 also active
            }
            }
            else{
            return index;
             }
    }
}
return -1;
}
// check whether is the block or not
// real cutting
int cutting(int index,int min_possition,int dicevalue,int index3,int index4){
    printf("cutting fuction\n");
    if(players[index].pieces[index3].isBoard){
            printf("true if\n");
            players[index].pieces[index3].position = 0;
            players[index].pieces[index3].isBoard = 0;
            players[index].pieces[index3].forToend = BOARD_SIZE;
           // players[livePlayer].pieces[index].forToend = (BOARD_SIZE -10);// why 10
            directionWiseMove(index4,dicevalue,1);
            players[livePlayer].pieces[index4].cutCount++;
            printf(" >> ***************************************************test(captured piece) %d\n",tempArray2[livePlayer].pieces->byCapIndex);
            // move funtion
            printf(" >> %s(%d) piece capture %s(%d) piece\n",players[livePlayer].color,index4,players[index].color,index3);
            return 0;
        }
            return 0;
    }


/// check which piece nearest to each home
int whoIsCut(int dicevalue){
    int minPositionIndex;
    for ( int index = 0; index < PIECE_FOR_PLAYER; index++){
        int min_position = tempArray2[index].pieces->farToEnd;
                if (tempArray2[index].pieces->farToEnd < min_position) {
                min_position = tempArray2[index].pieces->farToEnd;
          }
        
        minPositionIndex = min_position;
      
    }
    int index2,index3,index4;
    for (index2 = 0; index2 < PIECE_FOR_PLAYER; index2++){
        if (tempArray2[index2].pieces->farToEnd == minPositionIndex){
            index3 = tempArray2[index2].pieces->id;
            index4 = tempArray2[index2].pieces->byCapIndex;
            index2 = tempArray2[index2].pieces->group;
            break;
        }
    }// now index2 is farEnd min index

    /// check who cut
    
    cutting(index2,minPositionIndex,dicevalue,index3,index4);
      }
//cut function Commen
int cutFunction(int dicevalue){
    int tempArray[4]={0,1,2,3};
    int cutOn = 0;
    resetTempArray2();
    for(int index1 = 0; index1 < PLAYERS; index1++){
        if(tempArray[index1] == livePlayer){
            continue; //// is there a leak?.............................................................block
        }
        else{
          //  printf("cut fuction else part\n");
            for(int index2 = 0; index2 < PIECE_FOR_PLAYER; index2++){
                //
               // printf("group %d piece %d\n",index1,index2);
                    for(int index3 = 0; index3 < PIECE_FOR_PLAYER; index3++){
                      //  printf("group %d piece %d -----our group piece%d\n",index1,index2,index3);
                        if(players[livePlayer].pieces[index3].isBoard ){
                        //    printf("test case 1\n");
                            if(players[livePlayer].pieces[index3].direction == 1){
//printf("test case 2 (head)\n");
                            if((((players[livePlayer].pieces[index3].position)+dicevalue) % BOARD_SIZE) == (players[index1].pieces[index2].position*players[index1].pieces[index2].isBoard )){
                                       //     printf("test case 3\n");
                                    tempArray2[index1].pieces->group = players[index1].playerId;
                                    tempArray2[index1].pieces->id = index2;
                                    tempArray2[index1].pieces->farToEnd = players[index1].pieces[index2].forToend;
                                    tempArray2[index1].pieces->byCapIndex = index3;
                                    cutOn = 1;
                                    
                        }}
                        else{
                          //  printf("test case 4(tail)\n");
                            if((( (BOARD_SIZE + (players[livePlayer].pieces[index3].position - dicevalue)) % BOARD_SIZE) == (players[index1].pieces[index2].position*players[index1].pieces[index2].isBoard)|| (players[livePlayer].pieces[index3].position <= 6 && players[livePlayer].pieces[index3].position >= 1 && (players[livePlayer].pieces[index3].position == dicevalue) && players[index1].pieces[index2].position ==52) )){
                                     //   printf("test case 5\n");
                                    tempArray2[index1].pieces->group = players[index1].playerId;
                                    tempArray2[index1].pieces->id = index2;
                                    tempArray2[index1].pieces->farToEnd = players[index1].pieces[index2].forToend;
                                    tempArray2[index1].pieces->byCapIndex = index3;
                                    cutOn = 1;

                            }
                        }
                    }
                }
            }
        }
}
if(cutOn == 1){
    printf("going to cut\n");
whoIsCut(dicevalue);
return 1;
}
printf("not on cut fuction return 0\n");
return 0;
}

int numofPieceInBlock()
{
    int count = 0;
    for (int index2 = 0; index2 < PIECE_FOR_PLAYER; index2++)
    {
        if (players[livePlayer].pieces[index2].position == players[livePlayer].blocks.block_1Position)
        {
            count++;
        }
        if (players[livePlayer].pieces[index2].position == players[livePlayer].blocks.block_2Position)
        {
            count++;
        }
    }
    return count;
}
//
// void movingBlock(int diceNewValue)
// {
// }
// // move when have block
// void moveBlock(int index, int diceValue)
// {
//     if ((players[livePlayer].blocks.block_1Position == 1 | 14 | 27 | 40) || (players[livePlayer].blocks.block_2Position == 1 | 14 | 27 | 40))
//     {
//         printf("This block can be broken\n");
//         // broken function
//     }
//     else
//     {
//         int numofpieceInBlock = numofPieceInBlock();

//         // divede dice
//         // funtion of moving
//     }
// }
// movin_get new pieces

int movePiece(int index, int diceValue)
{
    if (players[livePlayer].pieces[index].position == 0)
    { // get new pieces
        if (diceValue == 6)
        {
            players[livePlayer].pieces[index].position = (livePlayer + 1) == 1 ? 1 : (livePlayer + 1) == 2 ? 14
                                                                                 : (livePlayer + 1) == 3   ? 27
                                                                                                           : 40;
                                                                                                             printf("position this piece %d\n",players[livePlayer].pieces[index].position);
                                                                            
            players[livePlayer].pieces[index].isBoard = 1;
            players[livePlayer].pieces[index].isXplace = 1;
            players[livePlayer].pieces[index].forToend = TOTAL_FAR_TO_END -1;
            printf(" >> %s player gets piece(%d) to board!\n", players[livePlayer].color, index);
            players[livePlayer].pieces[index].direction = coinToss();
            printf("direction this piece %d\n",players[livePlayer].pieces[index].direction);
            /// check it direction 1 or -1
            return 5;
        }
        else
        { // can not get pieces
            printf("\t\t>> %s player needs a 6 to move out of home to base\n", players[livePlayer].color);
            return -1;
        }
    }
    else{
    return index;
    }
    // else
    // { // this if for piece which can moving hear and there
    //     directionWiseMove(index, diceValue);
    //     isBlock(index);
    // }
}
//---------------------RED
// int whoGetRedPiece(int diceValue){
//     for( int index = 0; index < PIECE_FOR_PLAYER; index++){
//         movePiece(index,diceValue);
//     }
// }
//---------------------RED(check who can cut)

int gameHandle(int diceValue){
    //  int diceValue = rollingDice(diceCounter);
    printf("gameHandle\n"); 
    int movingPiece = who_is_move(livePlayer, diceValue);
    printf("gameHandle 1\n"); 
    if (movingPiece == -1)
    {
        printf(" >> %s player cannot move any piece yet!\n", players[livePlayer].color);
        return 0;
    }
    else if (movingPiece == 5)
    {
        printf(" >> Now moving block wise\n");
        return 0;
        // function call
    }

    else
    {
        red_movePiece = movePiece(movingPiece, diceValue);
        if(red_movePiece == -1 || red_movePiece == 5){
            printf("_______________________________________________test caase when get peice from base\n");
            red_movePiece = 0;
            return 0;
        }
        else if( red_movePiece == 0 || red_movePiece == 1 || red_movePiece == 2 || red_movePiece == 3){
        printf("_______________________________________________test caase when have piece to move \n");
        return 1;
        }
    }
}
///GREEN Beharvios
void blockDirection(int blockPosition){
    int max= 52;
    int maxIndex;
    for( int index = 0; index < PIECE_FOR_PLAYER; index ++){
        if(blockPosition == players[livePlayer].pieces[index].position){
              if( max < players[livePlayer].pieces[index].forToend){
                max = players[livePlayer].pieces[index].forToend;
                maxIndex = index;
              } 
        } 
    }
    players[livePlayer].blocks.block_1direction = players[livePlayer].pieces[maxIndex].direction;
}
int createBlock(int index ,int index2){

}
static int  tempBlock2 = -1;
int canMakeBlock(int index,int diceValue){
    printf("dice %d and current position %d\n",diceValue,players[livePlayer].pieces[index].position);
    int tempLocation = directionWiseMove(index,diceValue,0);
    printf("\t\t\ttempposition : %d\n",tempLocation);
    if (tempBlock2 > 0)//??????????????????????????
    {
        tempBlock2 = -1; // this argument is imposible
    }
    
    for (int index2 = 0; index2 < PIECE_FOR_PLAYER; index2++){
        if( index2 == index){
            continue;
        }
        else if ( tempLocation == players[livePlayer].pieces[index2].position){
            printf("\t\t\t####################################test\n");
                players[livePlayer].pieces[index].isInblock = 0;  // 0 means this piece in a block
                players[livePlayer].pieces[index2].isInblock = 0; // same
                players[livePlayer].pieces[index].position = tempLocation;
                players[livePlayer].pieces[index].forToend -= diceValue;
                printf("\t\t\t new location of piece : %d\n",players[livePlayer].pieces[index].position);
                printf(" >> \033[45mCreat a Block for (%s) at position %d and pieces : %d,\033[0m \n", players[livePlayer].color, index, players[livePlayer].pieces[index].position);
                isWinPlace(index);
                printf("%d,", index2);
                if (tempBlock2 == -1 && (players[livePlayer].pieces[index].position == players[livePlayer].pieces[index2].position) )
                {
                    printf("\t\t\t####################################test1\n");
                    players[livePlayer].blocks.block_1Position = players[livePlayer].pieces[index].position;
                    players[livePlayer].blocks.block_1Active = 1;
                    printf(">\t\t\t> Location of block1 : %d\n", players[livePlayer].blocks.block_1Position);
                    //if make a data type in struct like - count data in block in hear we can count them;
                    players[livePlayer].blocks.block_1count ++; // can not understand
                    tempBlock2++;
                    return 1;
                }
                else if (tempBlock2 == 0 && (players[livePlayer].pieces[index].position ==players[livePlayer].pieces[index2].position))
                {
                    printf("\t\t\t####################################test2\n");
                    players[livePlayer].blocks.block_2Position = players[livePlayer].pieces[index].position;
                    players[livePlayer].blocks.block_2Active = 1;
                    printf(">> Location of block : %d\n", players[livePlayer].blocks.block_2Position);
                    players[livePlayer].blocks.block_2count++;// can not understand  i think it oky now
                    tempBlock2++;
                    return 1;
                }
            }
            // printf("\n");
        }

    
   // printf("\n");
 
         return 0;   //can not creat block
        }
    
int whoMakeBlock(int diceValue){
    printf("whoMakeBlock...............................\n");
    for (int index = 0; index < PIECE_FOR_PLAYER; index++){
        if( (players[livePlayer].pieces[index].isBoard) && (players[livePlayer].pieces[index].isInblock == 1) && !(players[livePlayer].pieces[index].isHome) ){ // 1 mean it is not in block
        printf("checking .....................\n");
          if( canMakeBlock(index,diceValue) ){
            printf("created a block\n");
            return 1;
          }
         }      
    }
    return 0;
}
int blockMoving(int index, int diceValue){


    if (players[livePlayer].blocks.block_1direction == 1)
    {
        
        printf("....................test1\n");
        players[livePlayer].pieces[index].position = ((players[livePlayer].pieces[index].position + diceValue) == 52) ? 52 : ((players[livePlayer].pieces[index].position + diceValue) % BOARD_SIZE);
        players[livePlayer].pieces[index].forToend -= diceValue;
        printf(">> %s player piece(%d) moves to position %d----------------block wise\n", players[livePlayer].color, index, players[livePlayer].pieces[index].position);
    }
    else
    {
       
        if (players[livePlayer].pieces[index].position <= 6 && players[livePlayer].pieces[index].position >= 1 && (players[livePlayer].pieces[index].position == diceValue))
        {
            printf("....................test-1\n");
            players[livePlayer].pieces[index].position = 52;
            players[livePlayer].pieces[index].forToend -= diceValue;
            printf(">> %s player piece(%d) moves to position %d----------------block wise\n", players[livePlayer].color, index, players[livePlayer].pieces[index].position);
            }
        else
        {
            players[livePlayer].pieces[index].position = (BOARD_SIZE + (players[livePlayer].pieces[index].position - diceValue)) % BOARD_SIZE;
            players[livePlayer].pieces[index].forToend -= diceValue;
            printf(">> %s player piece(%d) moves to position %d----------------block wise\n", players[livePlayer].color, index, players[livePlayer].pieces[index].position);
            printf("....................test-1(b)\n");
          
        }
    } /// X wala blocks hadenn puluwand?yes it can be happen
    
    
    return 0;
}

int whichPiecesMoveBlock(int block_position, int diceValue,int count){
        int templocation;
        for ( int index = 0; index < PIECE_FOR_PLAYER; index++){
            if (players[livePlayer].pieces[index].isBoard && (block_position == players[livePlayer].pieces[index].position)){
            blockMoving(index, diceValue);
            printf("i\t\t\t\tndex location %d\n",players[livePlayer].pieces[index].position);
            templocation = players[livePlayer].pieces[index].position;
            printf("moving Block wise.......\n");
            }
        }
        printf("%d created a block\n",templocation);
        return 0;
}

int moveBlocks(int diceValue){
    int position_block1 = players[livePlayer].blocks.block_1Position,
        position_block2 = players[livePlayer].blocks.block_2Position;
    printf("\t\t\t\tmove blocks\n");
    if ( players[livePlayer].blocks.block_1Active == 1 || players[livePlayer].blocks.block_2Active == 1){
        if(position_block1 == 51 || position_block1 == 12 || position_block1 == 25 || position_block1 == 38 || position_block2 == 51 || position_block2 == 12 || position_block2 == 25 || position_block2 == 38 ){
            return 0;
        }
        printf("test case at moveBlock...................\n");
        int x = (players[livePlayer].blocks.block_1Position + 52);
        int y = (players[livePlayer].blocks.block_2Position + 52);
        if ( x > y){
            int count_piece_inBlock = players[livePlayer].blocks.block_1count;
            int new_dice = (diceValue/count_piece_inBlock);
            whichPiecesMoveBlock(players[livePlayer].blocks.block_1Position,new_dice,count_piece_inBlock);
            return 1;
            // move block 1 each player
        }
        if ( x < y) {
            int count_piece_inBlock = players[livePlayer].blocks.block_2count;
            int new_dice = (diceValue/count_piece_inBlock);
            whichPiecesMoveBlock(players[livePlayer].blocks.block_1Position,new_dice,count_piece_inBlock);
            return 1;
            // move block 2 each player
        }
    }
    printf("--------------------------------------------------------------\n");
    return 0;
}
//yellow
int getNewpiece(int dicevalue){
    for (int index = 0; index < PIECE_FOR_PLAYER; index++){
            if( ((livePlayer == 1) || (livePlayer == 2) || (livePlayer == 3)) && (players[livePlayer].pieces[index].position == 0) && (dicevalue == 6)){
     players[livePlayer].pieces[index].position =(livePlayer) == 1 ? 14
      : (livePlayer) == 2 ? 27 : 40;
                                                                                                             printf("position this piece %d\n",players[livePlayer].pieces[index].position);
                                                                            
            players[livePlayer].pieces[index].isBoard = 1;
            players[livePlayer].pieces[index].isXplace = 1;
            players[livePlayer].pieces[index].forToend = TOTAL_FAR_TO_END -1;
            printf(" >> %s player gets piece(%d) to board!\n", players[livePlayer].color, index);
            players[livePlayer].pieces[index].direction = coinToss();
            printf("direction this piece %d\n",players[livePlayer].pieces[index].direction); 
            return 1;  
    }
    }
    return 0;
}
int gameHandlefor_yellow(int diceValue){
    //  int diceValue = rollingDice(diceCounter);
    printf("gameHandle yellow\n"); 
    int movingPiece = who_is_move(livePlayer, diceValue);
    if (movingPiece == -1)
    {
        printf(" >> %s player cannot move any piece yet!\n", players[livePlayer].color);
        return 0;
    }
    else if (movingPiece == 5)
    {
        printf(" >> Now moving block wise\n");
        return 0;
        // function call
    }

    else
    {
        red_movePiece = movePiece(movingPiece, diceValue);
        if(red_movePiece == -1 ){ // 5 mean piece ekak isbord krl
            red_movePiece = 0; 
        }
        else if(red_movePiece == 5){
            printf("return 5\n");
            return 5;
        }
        else if( red_movePiece == 0 || red_movePiece == 1 || red_movePiece == 2 || red_movePiece == 3){
        return 0;
        }
    }
}
int check_win(int livePlayer)
{
    for (int index = 0; index < PIECE_FOR_PLAYER; index++)
    {
        if (!players[livePlayer].pieces[index].isHome)
        {
            return 0;
        }
    }
    return 1;
}
// control unit
int controler(int diceCounter)
{   
    int diceValue,temdicevale;
    start:
     diceValue = rollingDice(diceCounter); 
     temdicevale = diceValue;
    printf("rolling 1 time\n");
   // int movingPiece = gameHandle(diceCounter,diceValue);
    switch (livePlayer)
    {
    case 0 :// red player
        
        printf("case 0\n");
        if(cutFunction(diceValue)||gameHandle(diceValue)){// check who can cut/ is can cut near to home/dice roll 6 if can cut cut/ can not cut does not work
        int index = red_movePiece;//if roll 6 get new peice from base to path
        red_movePiece = 0;
        directionWiseMove(index,diceValue,1);
        }
        printf("\n");
        if (temdicevale == 6){
            goto start;
        }
       // in hear should be check dice == 6 and make a goto
         break; 

    case 1 :
          printf("case 1\n");
        if( whoMakeBlock(diceValue) || moveBlocks(diceValue) || getNewpiece(diceValue) || (gameHandlefor_yellow(diceValue)) ||directionWiseMove(red_movePiece,diceValue,1) || cutFunction(diceValue) ){}
                  red_movePiece = 0;
                               
        printf("\n");
        if (temdicevale == 6){
            goto start;
        }
        break;

    case 2 :
    //    printf("case 2\n");
    //    if( ((gameHandlefor_yellow(diceValue) == 5 ) || (gameHandlefor_yellow(diceValue) == 0 )) || directionWiseMove(red_movePiece,diceValue,1) || cutFunction(diceValue) || whoMakeBlock(diceValue) || moveBlocks(diceValue) ){}
    //    red_movePiece = 0;
    //    printf("\n");
    //    if (temdicevale == 6){
    //         goto start;
    //     }
         break;
    case 3 :
        //function
        // printf("case 3\n");
        // if( ((gameHandlefor_yellow(diceValue) == 5 ) || (gameHandlefor_yellow(diceValue) == 0 )) || directionWiseMove(red_movePiece,diceValue,1) || cutFunction(diceValue) || whoMakeBlock    (diceValue) || moveBlocks(diceValue) ){}
        // red_movePiece = 0;
        // printf("\n");
        // if (temdicevale == 6){
        //     goto start;
        // }
        break;
    }
}
// main
int main()
{
    srand(time(NULL));
    definePlayers(players);
    resetTempArray2();
   int i = 0;
    while (1)
    {
        int diceCounter = 1;
        controler(diceCounter);
         if (check_win(livePlayer))
        {
            printf("\n\t\t\t>> \033[35m\033[1mPlayer %s wins!\033[0m\033[0m\n", players[livePlayer].color);
            break;
        }
        livePlayer = (livePlayer + 1) % PLAYERS;
     i++;
    }
    return 0;
}