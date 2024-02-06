#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<math.h>




typedef struct File File;
//global variables
//-------------------------------------------------------------------------------------------------------------------------------------------------------
char board[32][32];     //global board
int counter=0;      //my code with this variable can recognize this time which player is playing
int sign=0;     //this variable is to recognize this turn one of the players is block or not
int wallSaverOfP1[2][48];
int wallSaverOfP2[2][48];  
int wallOfP1Counter=0; 
int wallOfP2Counter=0;
//-------------------------------------------------------------------------------------------------------------------------------------------------------


//functions of Bot
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void Botdecision(char *decision){
    if ((rand() % 10)>6)
    {
        *decision='w';
    }
    else *decision='m';
}

void BotType(char *type){
    int random=(rand() % 10);
    if (random>8)
    {
        *type='w';
    }
    else if (random>7)
    {
        *type='d';
    }
    else if (random>6)
    {
        *type='a';
    }
    else
    {
        *type='s';
    }
}

void WallOfBot(int *x,int *y,char *dir,int n){
    if ((rand() % 2)%2==0)
    {
        *dir='H';
    }
    else *dir='V';

    int xSaver;
    int ySaver;
    xSaver=rand() % 15;
    ySaver=rand() % 15;

    while (xSaver>=n)
    {
        xSaver-=n;
    }
    while (ySaver>=n)
    {
        ySaver-=n;
    }

    *x=xSaver;
    *y=ySaver;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------


//functions of attachmant
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void setTextColor(int textColor,int backColor)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorAttribute = backColor << 4 | textColor;
    SetConsoleTextAttribute(consoleHandle, colorAttribute);
}

void sleep(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal>clock());
}

void clearscreen()
{
    system("cls");
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------


//function of bent moves
//-------------------------------------------------------------------------------------------------------------------------------------------------------
int bentType(int x1,int y1,int x2,int y2,int turn)
{
    if (x1-1==x2 && y1==y2)
    {
        if (turn%2==0)
        return 1;
        else
        return 2;
    }
    else if (x1+1==x2 && y1==y2)
    {
        if (turn%2==0)
        return 2;
        else
        return 1;
    }
    else if (x1==x2 && y1-1==y2)
    {
        if (turn%2==0)
        return 3;
        else
        return 4;
    }
    else if (x1==x2 && y1+1==y2)
    {
        if (turn%2==0)
        return 4;
        else
        return 3;
    }
    else return -1;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------


//functions of printf and massages
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void printBoard(int n)
{
    for (int i = 0; i < 2*n-1; i++)  
    {
        for (int j = 0; j < 2*n-1; j++)
        {
            if (board[i][j]=='1')
            {
                if (j!=2*n-2)
                {
                    setTextColor(10,0);
                    printf("%c",board[i][j]);
                    setTextColor(7,0);
                }
                else
                {
                    setTextColor(10,0);
                    printf("%c\n",board[i][j]);
                    setTextColor(7,0);
                }
            }
            else if (board[i][j]=='2')
            {
                if (j!=2*n-2)
                {
                    setTextColor(12,0);
                    printf("%c",board[i][j]);
                    setTextColor(7,0);
                }
                else
                {
                    setTextColor(12,0);
                    printf("%c\n",board[i][j]);
                    setTextColor(7,0);
                }
            }
            else if (j!=2*n-2)
            {
                setTextColor(11,0);
                printf("%c",board[i][j]);
                setTextColor(7,0);
            }
            else
            {
                setTextColor(11,0);
                printf("%c\n",board[i][j]);
                setTextColor(7,0);
            }
        }
    }
}

void stuckError(int swOfPlayerType,int counter)
{
    if (! ( !swOfPlayerType && counter%2==1))
    {
    setTextColor(4,0);
    printf("your opponent will stuck with this wall!\n");
    setTextColor(7,0);
    }
}

void BoardExitError(int swOfPlayerType,int counter)
{
    if (! ( !swOfPlayerType && counter%2==1))
    {
    setTextColor(4,0);
    printf("You cannot move in this direction because you are out of board!\n");
    sleep(1000);
    printf("please try anothe direction\n");
    setTextColor(7,0);
    }
}

void WallPassingError(int swOfPlayerType,int counter)
{
    if (! ( !swOfPlayerType && counter%2==1))
    {
        setTextColor(4,0);
        printf("You cannot jupm through the wall!!\n");
        sleep(1000);
        printf("please try anothe direction\n");
        setTextColor(7,0);
    }
}

void ZeroWallError(int swOfPlayerType,int counter)
{
    if (! ( !swOfPlayerType && counter%2==1))
    {
        setTextColor(4,0);
        printf("you dont have wall anymore\nyou can just move\n");
        setTextColor(7,0);
    }
}

void RemainingWalls(int howMany,int swOfPlayerType,int counter)
{
    if (! ( !swOfPlayerType && counter%2==1))
    {
    setTextColor(6,0);
    printf("!!!!!!you have just %d more walls!!!!!!\n",howMany);
    setTextColor(7,0);
    }
}

void PrizeOfWinner()
{
    setTextColor(10,0);
    printf(" () ()\n\\_____/");
    setTextColor(7,0);
}

void mORwPrint()
{
    setTextColor(9,0);
    printf("if do you want to move press (m)\nand if you want to place a wall press (w)\n");
    setTextColor(7,0);
}

void directionPrint()
{
    setTextColor(9,0);
    printf("In which direction do you want to move?\ntop(w),down(s),right(d),left(a)\n");
    setTextColor(14,0);
    printf("and if that is emergency you have q(top L),e(top R),z(down L),c(down R) options too\n");
    setTextColor(7,0);
}

void orderError()
{
    setTextColor(4,0);
    printf("please select between S and L\n");
    setTextColor(7,0);
}

void newsOfIncreasingWalls(int swOfPlayerType,int counter)
{
    if (! ( !swOfPlayerType && counter%2==1))
    {
        if (counter%2==0)
        {
            setTextColor(10,0);
            printf("Hey playe1\ntow walls have been added to your walls\n");
            setTextColor(7,0);
        }
        else
        {
            setTextColor(10,0);
            printf("Hey playe2\ntow walls have been added to your wall\n");
            setTextColor(7,0);
        }
    }
}

void newsOfIncreasingAndDecreasingWalls(int swOfPlayerType,int counter)
{
    if (! ( !swOfPlayerType && counter%2==1))
    {
        if (counter%2==0)
        {
            setTextColor(10,0);
            printf("one of player 2 walls have stoled and added to yours\n");
            setTextColor(7,0);
        }
        else
        {
            setTextColor(10,0);
            printf("one of player 1 walls have stoled and added to yours\n");
            setTextColor(7,0);
        }
    }
}

void newsOfDecreasingWall(int swOfPlayerType,int counter){
    if (! ( !swOfPlayerType && counter%2==1))
    {
        if (counter%2==0)
        {
            setTextColor(12,0);
            printf("Hey player1 We have removed two walls from you\n");
            setTextColor(7,0);
        }
        else
        {
            setTextColor(12,0);
            printf("Hey player2 We have removed two walls from you\n");
            setTextColor(7,0);
        }
    }
}

void newsOfBlocking(int swOfPlayerType,int counter){
    if (! ( !swOfPlayerType && counter%2==1))
    {
        if (counter%2==0)
        {
            setTextColor(12,0);
            printf("player1 have been blocked playing two round\n");
            setTextColor(7,0);
        }
        else
        {
            setTextColor(12,0);
            printf("player2 have been blocked playing two round\n");
            setTextColor(7,0);
        }
    }
}

void wallInfo(int w1,int w2)
{
    setTextColor(14,0);
    printf("walls of player1 = %d\nwalls of player2 = %d",w1,w2);
    setTextColor(7,0);
    printf("\n");
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------


//function of prisone check
//-------------------------------------------------------------------------------------------------------------------------------------------------------
int paint(int n,int xOfPlayer,int yOfPlayer,int turn,int x1Saver,int x2Saver)
{
    char arrey[2*n-1][2*n-1];
    int saver[1000][2];
    int counter=1;

    for (int i = 0; i < 2*n-1; i++)
    {
        for (int j = 0; j < 2*n-1; j++)
        {
            arrey[i][j]=board[i][j];
        }
    }

    saver[0][0]=xOfPlayer;
    saver[0][1]=yOfPlayer;

    //local variables initialize
    char H=196;
    char V=179;
    char sign='0';

    for (int k = 0; k < counter; k++)
    {
        if (arrey[saver[k][0]][saver[k][1]+1]!=H && arrey[saver[k][0]][saver[k][1]+1]!=V && saver[k][1]+1<2*n-1)//left
        {
            if (arrey[saver[k][0]][saver[k][1]+2]!=sign)
            {
                saver[counter][0]=saver[k][0];
                saver[counter][1]=saver[k][1]+2;
                counter++;
                arrey[saver[k][0]][saver[k][1]+2]=sign;
            }
        }

        if (arrey[saver[k][0]][saver[k][1]-1]!=H && arrey[saver[k][0]][saver[k][1]-1]!=V && saver[k][1]-1>-1)//right
        {
            if (arrey[saver[k][0]][saver[k][1]-2]!=sign)
            {
                saver[counter][0]=saver[k][0];
                saver[counter][1]=saver[k][1]-2;
                counter++;
                arrey[saver[k][0]][saver[k][1]-2]=sign;
            }
        }

        if (arrey[saver[k][0]-1][saver[k][1]]!=H && arrey[saver[k][0]-1][saver[k][1]]!=V && saver[k][0]-1>-1)//top
        {
            if (arrey[saver[k][0]-2][saver[k][1]]!=sign && arrey[saver[k][0]][saver[k][1]]!=32)
            {
                saver[counter][0]=saver[k][0]-2;
                saver[counter][1]=saver[k][1];
                counter++;
                arrey[saver[k][0]-2][saver[k][1]]=sign;
            }
        }

        if (arrey[saver[k][0]+1][saver[k][1]]!=H && arrey[saver[k][0]+1][saver[k][1]]!=V && saver[k][0]+1<2*n-1)//down
        {
            if (arrey[saver[k][0]+2][saver[k][1]]!=sign && arrey[saver[k][0]][saver[k][1]]!=32)
            {
                saver[counter][0]=saver[k][0]+2;
                saver[counter][1]=saver[k][1];
                counter++;
                arrey[saver[k][0]+2][saver[k][1]]=sign;
            }
        }
    }

    if (turn%2==0)      //the turn of player 2
    {
        for (int j = 0; j < 2*n-1; j++)
        {
            if (arrey[2*x1Saver][j]=='0')
            {
                return 1;       //it means your opponent is safe
            }
        }
    }
    else
    {
        for (int j = 0; j < 2*n-1; j++)
        {
            if (arrey[2*x2Saver][j]=='0')
            {
                return 1;       //it means your opponent is safe
            }
        }
    }

    return 0;
}

//initialize the files
//-----------------------------------------------------------------------------------------------------------------------------------------------------
FILE *prjFile;
FILE *prjFile2;
FILE *prjFile3;
FILE *prjFile4;
FILE *prjFile5;
//------------------------------------------------------------------------------------------------------------------------------------------------------


//functions of game saving
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void open_file_board(int n)
{
    prjFile = fopen("D:\\TermOne\\Term1_TermProject\\board_saver.txt", "wt");

    if(!prjFile)
    {
        printf("can't open file1");
        exit(0);
    }
    for (int i = 0; i < 2*n-1; i++)     //print the updated board
    {
        for (int j = 0; j < 2*n-1; j++)
        {
            if (board[i][j]=='1')
            {
                if (j!=2*n-2)
                {
                    setTextColor(10,0);
                    fprintf(prjFile, "%c",board[i][j]);
                    setTextColor(7,0);
                }
                else
                {
                    setTextColor(10,0);
                    fprintf(prjFile, "%c\n",board[i][j]);
                    setTextColor(7,0);
                }
            }
            else if (board[i][j]=='2')
            {
                if (j!=2*n-2)
                {
                    setTextColor(12,0);
                    fprintf(prjFile, "%c",board[i][j]);
                    setTextColor(7,0);
                }
                else
                {
                    setTextColor(12,0);
                    fprintf(prjFile, "%c\n",board[i][j]);
                    setTextColor(7,0);
                }
            }
            else if (j!=2*n-2)
            {
                setTextColor(11,0);
                fprintf(prjFile, "%c",board[i][j]);
                setTextColor(7,0);
            }
            else
            {
                setTextColor(11,0);
                fprintf(prjFile, "%c\n",board[i][j]);
                setTextColor(7,0);
            }
        }
    }
    fclose(prjFile);
}

void open_file_board2()
{
    int t=0, z=0, n;
    char boardTxt;

    prjFile2 = fopen("D:\\TermOne\\Term1_TermProject\\board_saver.txt", "rt");
    prjFile5 = fopen("D:\\TermOne\\Term1_TermProject\\board_saver2.txt", "rt");

    if(!prjFile2)
    {

        printf("can't open file");
        exit(0);
    }
    if(!prjFile5)
    {

        printf("can't open file");
        exit(0);
    }

    fscanf(prjFile2, "%c", &boardTxt);
    fscanf(prjFile5, "%d", &n);
    while(!feof(prjFile2))
    {
        printf("%c", boardTxt);
        board[t][z] = boardTxt;
        z++;
        if(z > 2 * n - 1)
        {
            t++;
            z=0;
        }
        fscanf(prjFile2, "%c", &boardTxt);
    }
    fclose(prjFile2);
}

void open_file_info(int n, int x1, int y1, int x2, int y2, int x1Saver, int x2Saver, int p1Walls, int p2Walls, char player, int swOfPlayerType, int counter)
{
    prjFile3 = fopen("D:\\TermOne\\Term1_TermProject\\board_saver2.txt", "wt");

    if(!prjFile3)
    {
        printf("can't open file2");
        exit(0);
    }

    fprintf(prjFile3, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%c\n%d\n%d", n, x1, y1, x2, y2, x1Saver, x2Saver, p1Walls, p2Walls, player, swOfPlayerType, counter);
    fclose(prjFile3);
}

void open_file_info2(int *n, int *x1, int *y1, int *x2, int *y2, int *x1Saver, int *x2Saver, int *p1Walls, int *p2Walls, char *player, int *swOfPlayerType, int *counter)
{
    int infoTxt;
    char infoTxt2;
    prjFile4 = fopen("D:\\TermOne\\Term1_TermProject\\board_saver2.txt", "rt");

    if(!prjFile4)
    {
        printf("can't open file");
        exit(0);
    }

    fscanf(prjFile4, "%d\n", &infoTxt); *n = infoTxt;
    fscanf(prjFile4, "%d\n", &infoTxt); *x1 = infoTxt;
    fscanf(prjFile4, "%d\n", &infoTxt); *y1 = infoTxt;
    fscanf(prjFile4, "%d\n", &infoTxt); *x2 = infoTxt;
    fscanf(prjFile4, "%d\n", &infoTxt); *y2 = infoTxt;
    fscanf(prjFile4, "%d\n", &infoTxt); *x1Saver = infoTxt;
    fscanf(prjFile4, "%d\n", &infoTxt); *x2Saver = infoTxt;
    fscanf(prjFile4, "%d\n", &infoTxt); *p1Walls = infoTxt;
    fscanf(prjFile4, "%d\n", &infoTxt); *p2Walls = infoTxt;
    fscanf(prjFile4, "%c\n", &infoTxt2); *player = infoTxt2;
    fscanf(prjFile4, "%d\n", &infoTxt); *swOfPlayerType = infoTxt;
    fscanf(prjFile4, "%d\n", &infoTxt); *counter = infoTxt;

    fclose(prjFile4);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------


//Spells and rewards finctions
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void reward(int counter,int *w1,int *w2,int swOfPlayerType)
{
    if (rand()%2==0)        //add some walls
    {
        if (counter%2==0)
        {
            *w1+=2;
            
        }
        else
        {
            *w2+=2;
            
        }
        newsOfIncreasingWalls(swOfPlayerType,counter);
        wallInfo(*w1 , *w2);
    }
    else        //remove frome opponent and add to yours
    {
        if (counter%2==0 && *w2>0)
        {
            *w1++;
            *w2--;
        }
        else if (counter%2==1 && *w1>0)
        {
            *w2++;
            *w1--;     
        }
        newsOfIncreasingAndDecreasingWalls(swOfPlayerType,counter);
    }
}

int spell(int counter,int *w1,int *w2,int n,int swOfPlayerType)
{
    int randNum=rand();

    if (randNum%3==0)       //delete players walls of a player
    {
        if (counter%2==0)
        {
            for (int i = 0; i < wallOfP1Counter; i++)
            {
                board[wallSaverOfP1[0][i]][wallSaverOfP1[1][i]]=32;
            }
            clearscreen();
            printBoard(n);

            if (! ( !swOfPlayerType && counter%2==1))
            {
            setTextColor(12,0);
            printf("surprize!\nAll of your walls in the board has been deleted\n");
            setTextColor(7,0);

            return 0;
            }
            
        }
        else
        {
            for (int i = 0; i < wallOfP2Counter; i++)
            {
                board[wallSaverOfP2[0][i]][wallSaverOfP2[1][i]]=32;
            }
            clearscreen();
            printBoard(n);

            if (! ( !swOfPlayerType && counter%2==1))
            {
            setTextColor(12,0);
            printf("surprize!\nAll of your walls in the board has been deleted\n");
            setTextColor(7,0);

            return 0;
            }
        }
    }

    else if (randNum%3==1)      //decrease wall
    {
        if (counter%2==0 && *w1>=2)
        {
            *w1-=2;
        }
        else if (counter%2==0 && *w1<2 && *w1>0)
        {
            *w1--;
        }
        if (counter%2==1 && *w2>=2)
        {
            *w2-=2;
        }
        else if (counter%2==1 && *w2<2 && *w2>0)
        {
            *w2--;
        }
        newsOfDecreasingWall(swOfPlayerType,counter);
        wallInfo(*w1,*w2);

        return 0;     
    }

    else        //block user
    {
        newsOfBlocking(swOfPlayerType,counter);
        sleep(2500);
        if (counter%2==0)
        {
            return +3;
        }
        else
        {
            return -3;
        }
    }    
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------


//MAIN
//-------------------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
    //SRAND problem solver
    srand(time(NULL));
    //---------------------------------------------------------------------------------------------------------------------------------------------------


    //load or play
    //---------------------------------------------------------------------------------------------------------------------------------------------------
    char order;
    while (1)
    {
        setTextColor(9, 0);
        printf("shall we start over(press S) or load the last game(press L)?\n");
        setTextColor(7, 0);
        scanf(" %c", &order);
        if (order=='S'|| order=='L') break;
        else orderError;
    }

    int n;
    int p1Walls, x1, y1;
    int p2Walls, x2, y2;
    int x1Saver;        //finish line for player1
    int x2Saver;
    char player;
    int swOfPlayerType = 1;

    if(order == 'L')
    {
        setTextColor(2, 0);
        printf("previous board:\n\n");
        setTextColor(6, 0);
        open_file_board2();
        open_file_info2(&n, &x1, &y1, &x2, &y2, &x1Saver, &x2Saver, &p1Walls, &p2Walls, &player, &swOfPlayerType, &counter);
    }
    //---------------------------------------------------------------------------------------------------------------------------------------------------


    //initialize the defaulte information of Game
    //---------------------------------------------------------------------------------------------------------------------------------------------------
    else 
    {
        setTextColor(9, 0);
        printf("give the default information of game to computer\n");
        setTextColor(7, 0);
        scanf("%d", &n);

        //create the board whith squares
        for (int i = 0; i < 2 * n - 1; i++) 
        {
            for (int j = 0; j < 2 * n - 1; j++) 
            {
                if (i % 2 == 0 && j % 2 == 0) 
                {
                    board[i][j] = 254;
                } else board[i][j] = 32;
            }
        }       

        scanf("%d %d\n%d %d", &x1, &y1, &x2, &y2);
        board[2 * x1][2 * y1] = '1';      //simbol of player1
        board[2 * x2][2 * y2] = '2';      //simbol of player2


        //print the default board
        printBoard(n);      


        setTextColor(9, 0);
        printf("pleas Determine how many walls the player1 has\n");
        setTextColor(7, 0);
        scanf("%d", &p1Walls);
        setTextColor(9, 0);
        printf("pleas Determine how many walls the player2 has\n");
        setTextColor(7, 0);
        scanf("%d", &p2Walls);

        //initialize finish line for each player
        if (x1 >= n / 2) 
        {
            x1Saver = n - 1;
            x2Saver = 0;
        } 
        else 
        {
            x1Saver = 0;
            x2Saver = n - 1;
        }


        getchar();


        //play with bot or player
        while (1) 
        {
            setTextColor(5, 0);
            printf("do you have any friend to play with?Y=(yes) / N=(no,play with Bot)\n");
            setTextColor(7, 0);
            scanf("%c", &player);
            if (player == 'N') 
            {
                swOfPlayerType = 0;
                break;
            } 
            else if (player == 'Y') 
            {
                break;
            }
        }
    }
    //---------------------------------------------------------------------------------------------------------------------------------------------------

    //Play
    //---------------------------------------------------------------------------------------------------------------------------------------------------
    while (x1!=x2Saver && x2!=x1Saver)
    {
        //reward or spell
        //-----------------------------------------------------------------------------------------------------------------------------------------------
        if (rand()%2==0)        
        {
            reward(counter,&p1Walls,&p2Walls,swOfPlayerType);
        }
        else
        {
            int num=spell(counter,&p1Walls,&p2Walls,n,swOfPlayerType);
            if (abs(num)==3)
            {
                sign=num;
            }   
        }
        //-----------------------------------------------------------------------------------------------------------------------------------------------



        //if players are block
        //-----------------------------------------------------------------------------------------------------------------------------------------------
        if (sign>0)    //player one is blocked
        {
            if (sign==(+3))
            {
                counter++;
                sign--;
            }
            else
            {
                counter+=2;
                sign--;
            }
        }
        else if (sign<0)        //player tow is blocked
        {
            if (sign==(-3))
            {
                counter++;
                sign++;
            }
            else
            {
                counter+=2;
                sign++;
            }
        }
        //-----------------------------------------------------------------------------------------------------------------------------------------------
        
        
        //select between m or w
        //-----------------------------------------------------------------------------------------------------------------------------------------------
        if (! ( !swOfPlayerType && counter%2==1))
        {
            mORwPrint();
        }
        else if (!swOfPlayerType && counter%2!=0)
        {
            setTextColor(9,0);
            printf("wait for Bot\n");
            setTextColor(7,0);
        }

        char decision;

        while (1 && !(swOfPlayerType==0 && counter%2!=0))
        {

            scanf(" %c",&decision);
            if (decision=='m' ||decision=='w')
            {
                break;
            }
            else
            {
                setTextColor(6,0);
                printf("you should choose between w(place a wall) & m(move your piece)\n");
                setTextColor(7,0);
            }
        }

        if (!swOfPlayerType && counter%2!=0)
        {
            Botdecision(&decision);
        }
        //-----------------------------------------------------------------------------------------------------------------------------------------------



        //code block of move 
        //-----------------------------------------------------------------------------------------------------------------------------------------------
        if (decision=='m')
        {
            lable:
            while (1)
            {
                //select direction
                //----------------------------------------------------------------------------------------------------------------------------------------
                if (!(swOfPlayerType==0 && counter%2!=0))
                {
                   directionPrint();
                }
                char type;
                while (1 && !(swOfPlayerType==0 && counter%2!=0))
                {
                    scanf(" %c",&type);
                    if (type=='w' ||type=='d' ||type=='s' ||type=='a') break;
                    else if (bentType(x1,y1,x2,y2,counter)==1 && (type=='e'||type=='q')) break;
                    else if (bentType(x1,y1,x2,y2,counter)==2 && (type=='z'||type=='c')) break;
                    else if (bentType(x1,y1,x2,y2,counter)==3 && (type=='q'||type=='z')) break;
                    else if (bentType(x1,y1,x2,y2,counter)==4 && (type=='e'||type=='z')) break;
                    else
                    {
                        setTextColor(4,0);
                        printf("You have to choose between the four main diractions and secondary directions that you are allowed to use\n");
                        setTextColor(7,0);
                    }

                }
                if (!swOfPlayerType && counter%2!=0)
                {
                    BotType(&type);
                }       
                //end of select move type
                //----------------------------------------------------------------------------------------------------------------------------------------



                //move of player one
                //----------------------------------------------------------------------------------------------------------------------------------------
                int retu=bentType(x1,y1,x2,y2,counter);
                if (counter%2==0)
                {
                    board[2*x1][2*y1]=254;

                    //if the direction is main

                    if (type == 'w' && x1-2>-1 && x1-1==x2 && y1==y2)
                    {
                        if (board[2*x1-3][2*y1]==32)
                        {
                            x1-=2;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType,counter);
                        }
                    }
                    else if (type == 'w' && x1-1>-1)
                    {
                        if (board[2*x1-1][2*y1]==32)
                        {
                            x1--;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType,counter);
                        }
                    }
                    else if (type == 's' && x1+2<n && x1+1==x2 && y1==y2)
                    {
                        if (board[2*x1+3][2*y1]==32)
                        {
                            x1+=2;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType,counter);
                        }
                    }
                    else if (type == 's' && x1+1<n)
                    {
                        if (board[2*x1+1][2*y1]==32)
                        {
                            x1++;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType,counter);
                        }
                    }
                    else if (type == 'd' && y1+2<n && x1==x2 && y1+1==y2)
                    {
                        if (board[2*x1][2*y1+3]==32)
                        {
                            y1+=2;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType,counter);
                        }
                    }
                    else if (type == 'd' && y1+1<n)
                    {
                        if (board[2*x1][2*y1+1]==32)
                        {
                            y1++;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType,counter);
                        }
                    }
                    else if (type == 'a' && y1-2>-1 && x1==x2 && y1-1==y2)
                    {
                        if (board[2*x1][2*y1-3]==32)
                        {
                            y1-=2;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType,counter);
                        }
                    }
                    else if(type == 'a' && y1-1>-1)
                    {
                        if (board[2*x1][2*y1-1]==32)
                        {
                            y1--;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType,counter);
                        }
                    }

                    //if the direction is not main

                    else if (retu!=-1 && board[x1+x2][y1+y2]==32)   //x1+x2 & y1+y2 is the average coordinate of they blocks
                    {
                        if (type == 'q' && x1-1>-1 && y1-1>-1 && ((board[2*x1-3][2*y1]!=32 && retu==1) || (board[2*x1][2*y1-3]!=32 && retu==3)))
                        {
                            x1--;
                            y1--;
                            break;
                        }

                        else if (type == 'e' && x1-1>-1 && y1+1<n && ((board[2*x1-3][2*y1]!=32 && retu==1) || (board[2*x1][2*y1+3]!=32 && retu==4)))
                        {
                            x1--;
                            y1++;
                            break;
                        }

                        else if (type == 'z' && x1+1<n && y1-1>-1 && ((board[2*x1+3][2*y1]!=32 && retu==2) || (board[2*x1][2*y1-3]!=32 && retu==3)))
                        {
                            x1++;
                            y1--;
                            break;
                        }

                        else if(type == 'c' && x1+1<n && y1+1<n && ((board[2*x1+3][2*y1]!=32 && retu==2) || (board[2*x1][2*y1+3]!=32 && retu==4)))
                        {
                            x1++;
                            y1++;
                            break;
                        }

                        else BoardExitError(swOfPlayerType,counter);
                    }

                    else
                    {
                        BoardExitError(swOfPlayerType,counter);
                    }
                }
                //end of move of player one
                //-----------------------------------------------------------------------------------------------------------------------------------------




                //move of player tow
                //-----------------------------------------------------------------------------------------------------------------------------------------
                else
                {
                    board[2*x2][2*y2]=254;
                    if (type == 'w' && x2-2>-1  && x2-1==x1 && y2==y1)
                    {
                        if (board[2*x2-3][2*y2]==32)
                        {
                            x2-=2;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType,counter);
                        }
                    }
                    else if (type == 'w' && x2-1>-1)
                    {
                        if (board[2*x2-1][2*y2]==32)
                        {
                            x2--;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType,counter);
                        }
                    }
                    else if (type == 's' && x2+2<n && x2+1==x1 && y2==y1)
                    {
                        if (board[2*x2+3][2*y2]==32)
                        {
                            x2+=2;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType,counter);
                        }
                    }
                    else if (type == 's' && x2+1<n)
                    {
                        if (board[2*x2+1][2*y2]==32)
                        {
                            x2++;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType,counter);
                        }
                    }
                    else if (type == 'd' && y2+2<n && x2==x1 && y2+1==y1)
                    {
                        if (board[2*x2][2*y2+3]==32)
                        {
                            y2+=2;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType,counter);
                        }
                    }
                    else if (type == 'd' && y2+1<n)
                    {
                        if (board[2*x2][2*y2+1]==32)
                        {
                            y2++;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType,counter);
                        }
                    }
                    else if (type == 'a' && y2-2>-1 && x2==x1 && y2-1==y1)
                    {
                        if (board[2*x2][2*y2-3]==32)
                        {
                            y2-=2;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType,counter);
                        }
                    }
                    else if(type == 'a' && y2-1>-1)
                    {
                        if (board[2*x2][2*y2-1]==32)
                        {
                            y2--;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType,counter);
                        }
                    }


                    //if the direction is not main


                    else if (retu!=-1 && board[x1+x2][y1+y2]==32)   //x1+x2 & y1+y2 is the average coordinate of they blocks
                    {
                        if (type == 'q' && x2-1>-1 && y2-1>-1 && ((board[2*x2-3][2*y2]!=32 && retu==1) || (board[2*x2][2*y2-3]!=32 && retu==3)))
                        {
                            x2--;
                            y2--;
                            break;
                        }

                        else if (type == 'e' && x2-1>-1 && y2+1<n && ((board[2*x2-3][2*y2]!=32 && retu==1) || (board[2*x2][2*y2+3]!=32 && retu==4)))
                        {
                            x2--;
                            y2++;
                            break;
                        }

                        else if (type == 'z' && x2+1<n && y2-1>-1 && ((board[2*x2+3][2*y2]!=32 && retu==2) || (board[2*x2][2*y2-3]!=32 && retu==3)))
                        {
                            x2++;
                            y2--;
                            break;
                        }

                        else if(type == 'c' && x2+1<n && y2+1<n && ((board[2*x2+3][2*y2]!=32 && retu==2) || (board[2*x2][2*y2+3]!=32 && retu==4)))
                        {
                            x2++;
                            y2++;
                            break;
                        }

                        else BoardExitError(swOfPlayerType,counter);
                    }

                    else
                    {
                        BoardExitError(swOfPlayerType,counter);
                    }
                }
                //end of move of player tow
                //--------------------------------------------------------------------------------------------------------------------------------------
            }

            //edit the players place
            board[2*x1][2*y1]='1';
            board[2*x2][2*y2]='2';

        }
        //end of move
        //-----------------------------------------------------------------------------------------------------------------------------------------------




        //place wall
        //-----------------------------------------------------------------------------------------------------------------------------------------------
        else if (decision=='w')
        {
            //decreas wall
            //-------------------------------------------------------------------------------------------------------------------------------------------
            if (counter%2==0)
            {
                if (p1Walls>0)
                {
                    p1Walls--;
                }
                else
                {
                    ZeroWallError(swOfPlayerType,counter);
                    goto lable;
                }
            }
            else
            {
                if (p2Walls>0)
                {
                    p2Walls--;
                }
                else
                {
                    ZeroWallError(swOfPlayerType,counter);
                    goto lable;
                }
            }
            //-------------------------------------------------------------------------------------------------------------------------------------------



            while (1)
            {
                int xOfWall;
                int yOfWall;

                if (!(swOfPlayerType==0 && counter%2!=0))
                {
                setTextColor(9,0);
                printf("Please enter three items bellow\n");
                sleep(500);
                setTextColor(9,0);
                printf("Row\n");
                sleep(500);
                printf("Column\n");
                sleep(500);
                printf("type : V(vertical) or H(horisontal)\n");
                setTextColor(7,0);
                scanf("%d",&xOfWall);
                scanf("%d",&yOfWall);
                }

                //select the wall direction
                //----------------------------------------------------------------------------------------------------------------------------------------
                char wallDirect;

                while (1 && !(swOfPlayerType==0 && counter%2!=0))
                {
                    scanf(" %c",&wallDirect);
                    if (wallDirect=='H' || wallDirect=='V')
                    {
                        break;
                    }
                    else
                    {
                        setTextColor(4,0);
                        printf("pay attention to your wall type.you can just insert one of these options:V(vertical),H(horisontal)\n");
                        sleep(1000);
                        setTextColor(6,0);
                        printf("Your mistake can be entering lowercase letters\n");
                        setTextColor(7,0);
                    }
                }

                if (swOfPlayerType==0 && counter%2!=0)
                {
                    WallOfBot(&xOfWall,&yOfWall,&wallDirect,n);
                }        
                //end of wall selectiont
                //----------------------------------------------------------------------------------------------------------------------------------------


                //aplly wall
                //----------------------------------------------------------------------------------------------------------------------------------------
                xOfWall *= 2;
                yOfWall *= 2;
                if(wallDirect == 'H' && xOfWall-1>-1  && xOfWall<2*n-1 && yOfWall>-1 && yOfWall+2<2*n-1 && board[xOfWall-1][yOfWall] == 32 && board[xOfWall-1][yOfWall + 1] == 32 && board[xOfWall-1][yOfWall + 2]  == 32)
                {
                    if (counter%2==0)       //add walls in wall saver
                    {
                        wallSaverOfP1[0][wallOfP1Counter] = wallSaverOfP1[0][wallOfP1Counter+1] = wallSaverOfP1[0][wallOfP1Counter+2] = xOfWall-1;
                        wallSaverOfP1[1][wallOfP1Counter]=yOfWall;
                        wallSaverOfP1[1][wallOfP1Counter+1]=yOfWall+1;
                        wallSaverOfP1[1][wallOfP1Counter+2]=yOfWall+2;
                        wallOfP1Counter+=3;
                    }

                    else
                    {
                        wallSaverOfP1[0][wallOfP2Counter] = wallSaverOfP1[0][wallOfP2Counter+1] = wallSaverOfP1[0][wallOfP2Counter+2] = xOfWall-1;
                        wallSaverOfP1[1][wallOfP2Counter]=yOfWall;
                        wallSaverOfP1[1][wallOfP2Counter+1]=yOfWall+1;
                        wallSaverOfP1[1][wallOfP2Counter+2]=yOfWall+2;
                        wallOfP2Counter+=3;
                    }
                    
                    board[xOfWall-1][yOfWall] = 196;
                    
                    board[xOfWall-1][yOfWall + 1] = 196;

                    board[xOfWall-1][yOfWall + 2] = 196;

                    if (counter%2==0 && p1Walls<4)
                    {
                        RemainingWalls(p1Walls,swOfPlayerType,counter);
                    }
                    else if (counter%2!=0 && p2Walls<4)
                    {
                        RemainingWalls(p2Walls,swOfPlayerType,counter);
                    }
                    // break;
                }
                else if (wallDirect=='V' && yOfWall-1>-1 && yOfWall<2*n-1 && xOfWall-2>-1 && xOfWall<2*n-1 && board[xOfWall][yOfWall-1] == 32 && board[xOfWall-1][yOfWall-1]  == 32 && board[xOfWall-2][yOfWall-1] == 32)
                {
                    if (counter%2==0)           //add walls in wall saver
                    {
                        wallSaverOfP1[0][wallOfP1Counter] = wallSaverOfP1[0][wallOfP1Counter+1] = wallSaverOfP1[0][wallOfP1Counter+2] = yOfWall-1;
                        wallSaverOfP1[1][wallOfP1Counter]=xOfWall;
                        wallSaverOfP1[1][wallOfP1Counter+1]=xOfWall-1;
                        wallSaverOfP1[1][wallOfP1Counter+2]=xOfWall-2;
                        wallOfP1Counter+=3;
                    }

                    else
                    {
                        wallSaverOfP1[0][wallOfP2Counter] = wallSaverOfP1[0][wallOfP2Counter+1] = wallSaverOfP1[0][wallOfP2Counter+2] = yOfWall-1;
                        wallSaverOfP1[1][wallOfP2Counter]=xOfWall;
                        wallSaverOfP1[1][wallOfP2Counter+1]=xOfWall-1;
                        wallSaverOfP1[1][wallOfP2Counter+2]=xOfWall-2;
                        wallOfP2Counter+=3;
                    }

                    board[xOfWall][yOfWall-1] = 179;

                    board[xOfWall-1][yOfWall-1] = 179;

                    board[xOfWall-2][yOfWall-1] = 179;

                    if (counter%2==0 && p1Walls<4)
                    {
                        RemainingWalls(p1Walls,swOfPlayerType,counter);
                    }
                    else if (counter%2!=0 && p2Walls<4)
                    {
                        RemainingWalls(p2Walls,swOfPlayerType,counter);
                    }
                    // break;
                }       //end of putting walls in the board
                else
                {
                    if (swOfPlayerType)
                    {
                        setTextColor(4,0);
                        printf("you can't place your wall here\n");
                        setTextColor(7,0);
                    }
                }
                //----------------------------------------------------------------------------------------------------------------------------------------


                //prisone check
                //----------------------------------------------------------------------------------------------------------------------------------------
                if (counter%2==0)
                {
                    if (paint(n,2*x2,2*y2,counter,x1Saver,x2Saver))
                    {
                        break;
                    }
                    else
                    {
                        stuckError(swOfPlayerType,counter);
                        p1Walls++;
                        if (wallDirect=='H')
                        {
                            board[xOfWall-1][yOfWall] = 32;

                            board[xOfWall-1][yOfWall + 1] = 32;

                            board[xOfWall-1][yOfWall + 2] = 32;
                        }
                        else
                        {
                            board[xOfWall][yOfWall-1] = 32;

                            board[xOfWall-1][yOfWall-1] = 32;

                            board[xOfWall-2][yOfWall-1] = 32;
                        }
                    }
                }

                else
                {
                    if (paint(n,2*x1,2*y1,counter,x1Saver,x2Saver))
                    {
                        break;
                    }
                    else
                    {
                        stuckError(swOfPlayerType,counter);
                        p2Walls++;
                        if (wallDirect=='H')
                        {
                            board[xOfWall-1][yOfWall] = 32;

                            board[xOfWall-1][yOfWall + 1] = 32;

                            board[xOfWall-1][yOfWall + 2] = 32;
                        }
                        else
                        {
                            board[xOfWall][yOfWall-1] = 32;

                            board[xOfWall-1][yOfWall-1] = 32;

                            board[xOfWall-2][yOfWall-1] = 32;
                        }
                    }
                }
                //---------------------------------------------------------------------------------------------------------------------------------------
            }
        }



        //update everything
        //-----------------------------------------------------------------------------------------------------------------------------------------------
        clearscreen();      //clear terminal

        wallInfo(p1Walls,p2Walls);      //remmember how many walls player one and tow have

        printBoard(n);      //print the updated board

        if (sign==0)        
        {
            counter++;
        }

        if(!swOfPlayerType && counter%2!=0){
            mORwPrint();
        }
    

        open_file_board(n);
        open_file_info(n, x1, y1, x2, y2, x1Saver, x2Saver, p1Walls, p2Walls, player, swOfPlayerType, counter);
        //-----------------------------------------------------------------------------------------------------------------------------------------------
    }
    //end of geme
    //---------------------------------------------------------------------------------------------------------------------------------------------------


    //declare winner
    //-----------------------------------------------------------------------------------------------------------------------------------------------
    if (x2==x1Saver)
    {
        if (swOfPlayerType)
        {
        setTextColor(10,0);
        printf("Hey player 2\nYou won\n");
        setTextColor(7,0);
        }
        else
        {
            setTextColor(10,0);
            printf("Game over\n");
            setTextColor(7,0);
        }
    }

    else
    {
        setTextColor(10,0);
        printf("Hey player 1\nYou won\n");
        setTextColor(7,0);
    }

    if (!(x2==x1Saver && swOfPlayerType==0))
    {
        PrizeOfWinner();
    }
    
    else printf("nooobe-h sag");
    //-----------------------------------------------------------------------------------------------------------------------------------------------



    return 0;
}