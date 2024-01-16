#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<math.h>
int hbj;


char board[32][32];     //global board

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
void setTextColor(int textColor,int backColor){
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
void stuckError(){
    setTextColor(4,0);
    printf("your opponent will stuck with this wall!\n");
    setTextColor(7,0);
}
void BoardExitError(int swOfPlayerType)
{
    if (swOfPlayerType)
    {
    setTextColor(4,0);
    printf("You cannot move in this direction because you are out of board!\n");
    sleep(1000);
    printf("please try anothe direction\n");
    setTextColor(7,0);
    }
}
void WallPassingError(int swOfPlayerType)
{
    if (swOfPlayerType)
    {
        setTextColor(4,0);
        printf("You cannot jupm through the wall!!\n");
        sleep(1000);
        printf("please try anothe direction\n");
        setTextColor(7,0);
    } 
}
void ZeroWallError(int swOfPlayerType)
{
    if (swOfPlayerType)
    {
        setTextColor(4,0);
        printf("you dont have wall anymore\nyou can just move\n");
        setTextColor(7,0);
    } 
}
void RemainingWalls(int howMany,int swOfPlayerType)
{
    if (swOfPlayerType)
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
int paint(int n,int xOfPlayer,int yOfPlayer,int turn,int x1Saver,int x2Saver){
    char arrey[2*n-1][2*n-1];
    // int power=pow(2*(n-1),2);
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


        // if (arrey[saver[k][0]-1][saver[k][1]+1]!=H && arrey[saver[k][0]-1][saver[k][1]+1]!=V && saver[k][0]-1>-1 && saver[k][1]+1<2*n-1)//top right
        // {
        //     if (arrey[saver[k][0]-1][saver[k][1]+1]!=sign)
        //     {
        //         saver[counter][0]=saver[k][0]-1;
        //         saver[counter][1]=saver[k][1]+1;
        //         counter++;
        //         arrey[saver[k][0]-1][saver[k][1]+1]=sign;
        //     }
 
        // }
        
        // if (arrey[saver[k][0]-1][saver[k][1]-1]!=H && arrey[saver[k][0]-1][saver[k][1]-1]!=V && saver[k][0]-1>-1 && saver[k][1]-1>-1)//left top
        // {
        //     if (arrey[saver[k][0]-1][saver[k][1]-1]!=sign)
        //     {
        //         saver[counter][0]=saver[k][0]-1;
        //         saver[counter][1]=saver[k][1]-1;
        //         counter++;
        //         arrey[saver[k][0]-1][saver[k][1]-1]=sign;
        //     }

        // }
        
        // if (arrey[saver[k][0]+1][saver[k][1]-1]!=H && arrey[saver[k][0]+1][saver[k][1]-1]!=V && saver[k][0]+1<2*n-1 && saver[k][1]-1>-1)//left down
        // {
        //     if (arrey[saver[k][0]+1][saver[k][1]-1]!=sign)
        //     {
        //         saver[counter][0]=saver[k][0]+1;
        //         saver[counter][1]=saver[k][1]-1;
        //         counter++;
        //         arrey[saver[k][0]+1][saver[k][1]-1]=sign;
        //     }
  
        // }
        
        // if (arrey[saver[k][0]+1][saver[k][1]+1]!=H && arrey[saver[k][0]+1][saver[k][1]+1]!=V && saver[k][0]+1<2*n-1 && saver[k][1]+1<2*n-1)//right down
        // {
        //     if (arrey[saver[k][0]+1][saver[k][1]+1]!=sign)
        //     {
        //         saver[counter][0]=saver[k][0]+1;
        //         saver[counter][1]=saver[k][1]+1;
        //         counter++;
        //         arrey[saver[k][0]+1][saver[k][1]+1]=sign;
        //     }
   
        // }
   
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



int counter=0;      //my code with this variable can recognize this time which player is playing
  








int main(){
    srand(time(NULL));
    int n;
    scanf("%d",&n);
    for (int i = 0; i < 2*n-1; i++)
    {
        for (int j = 0; j < 2*n-1; j++)
        {
            if (i%2==0 && j%2==0)
            {
                board[i][j]=254;
            }
            else board[i][j]=32;
            
        }
        
    }       //create the board whith squares
    int x1,y1,x2,y2;
    scanf("%d %d\n%d %d",&x1,&y1,&x2,&y2);
    board[2*x1][2*y1]='1';      //simbol of player1
    board[2*x2][2*y2]='2';      //simbol of player2




    // int wa1x,wa1y,wacount1;
    // char wadir1;
    // int wa2x,wa2y,wacount2;
    // char wadir2;
    // scanf("%d",&wacount1);
    // for (int i = 0; i < wacount1; i++)
    // {
    //     scanf("%d %d %c", &wa1x, &wa1y, &wadir1);

    //     wa1x *= 2;
    //     wa1y *= 2;
    //     if(wadir1 == 'H' && wa1x-1>-1 && wa1y>-1 && wa1y+2<2*n-1 && board[wa1x-1][wa1y] != 196 && board[wa1x-1][wa1y] != 179 && board[wa1x-1][wa1y+1] != 196 &&board[wa1x-1][wa1y+1] != 179 && board[wa1x-1][wa1y+2] != 196 &&board[wa1x-1][wa1y+2] != 179){
    //     board[wa1x-1][wa1y] = 196;
    //     board[wa1x-1][wa1y + 1] = 196;
    //     board[wa1x-1][wa1y + 2] = 196;
    //     }
    //     else if (wadir1=='V' && wa1y-1>-1 && wa1x>-1 && wa1x+2<2*n-1 && board[wa1x][wa1y-1] != 196 && board[wa1x][wa1y-1] != 179 && board[wa1x+1][wa1y-1] != 196 &&board[wa1x+1][wa1y-1] != 179 && board[wa1x+2][wa1y-1] != 196 &&board[wa1x+2][wa1y-1] != 179){
    //         board[wa1x][wa1y-1] = 179;
    //         board[wa1x+1][wa1y-1] = 179;
    //         board[wa1x+2][wa1y-1] = 179;
    //     }
    // }       //end of defult walls of player1


    
    // scanf("%d",&wacount2);
    // for(int i = 0; i < wacount2; i++){

    //     scanf("%d %d %c", &wa2x, &wa2y, &wadir2);
    //     wa2x *= 2;
    //     wa2y *= 2;
    //     if(wadir2 == 'H' && wa2x-1>-1 && wa2y>-1 && wa2y+2<2*n-1 && board[wa2x-1][wa2y] != 196 && board[wa2x-1][wa2y] != 179 && board[wa2x-1][wa2y+1] != 196 &&board[wa2x-1][wa2y+1] != 179 && board[wa2x-1][wa2y+2] != 196 &&board[wa2x-1][wa2y+2] != 179){
    //         board[wa2x-1][wa2y] = 196;
    //         board[wa2x-1][wa2y + 1] = 196;
    //         board[wa2x-1][wa2y + 2] = 196;
    //     }
    //     else if (wadir2=='V' && wa2y-1>-1 && wa2x>-1 && wa2x+2<2*n-1 && board[wa2x][wa2y-1] != 196 && board[wa2x][wa2y-1] != 179 && board[wa2x+1][wa2y-1] != 196 &&board[wa2x+1][wa2y-1] != 179 && board[wa2x+2][wa2y-1] != 196 &&board[wa2x+2][wa2y-1] != 179){
    //         board[wa2x][wa2y-1] = 179;
    //         board[wa2x-1][wa2y-1] = 179;
    //         board[wa2x-2][wa2y-1] = 179;
    //     }
    // }       //end of defult walls of player1







    //end of board defult setting

    for (int i = 0; i < 2*n-1; i++)     //print the default board
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






    //move and place walls will start from bellow





    int p1Walls;
    int p2Walls;
    setTextColor(9,0);
    printf("pleas Determine how many walls the player1 has\n");
    setTextColor(7,0);
    scanf("%d",&p1Walls);
    setTextColor(9,0);
    printf("pleas Determine how many walls the player2 has\n");
    setTextColor(7,0);
    scanf("%d",&p2Walls);
    int x1Saver;        //finish line for player1
    int x2Saver;        //finish line for player2
    if (x1>=n/2)
    {
        x1Saver=n-1;
        x2Saver=0;
    }
    else 
    {
        x1Saver=0;
        x2Saver=n-1;
    }

    getchar();
    char player;
    int swOfPlayerType=1;
    while (1)
    {
        setTextColor(5,0);
        printf("do you have any friend to play with?Y=(yes) / N=(no,play with Bot)\n");
        setTextColor(7,0);
        scanf("%c",&player);
        if (player=='N')
        {
            swOfPlayerType=0;
            break;
        }
        else if (player=='Y')
        {
            break;
        }
          
    }




    while (x1!=x2Saver && x2!=x1Saver)
    {
        if (swOfPlayerType)
        {
            setTextColor(9,0);
            printf("if do you want to move press (m)\nand if you want to place a wall press (w)\n");
            setTextColor(7,0);
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
        }       //end of select between m & w
        

        if (decision=='m')      
        {
            
            lable:
            while (1)
            {
                if (!(swOfPlayerType==0 && counter%2!=0))
                {
                    setTextColor(9,0);
                    printf("In which direction do you want to move?\ntop(w),down(s),right(d),left(a)\n");
                    setTextColor(14,0);
                    printf("and if that is emergency you have q(top L),e(top R),z(down L),c(down R) options too\n");
                    setTextColor(7,0);
                }
                // if (counter%2==0)
                // {
                //     switch (bentType(x1,y1,x2,y2,counter))
                //     {
                //     case 1:
                //         pMoreOptions('q','e',"top left","top right");
                //         break;
                //     case 2:
                //         pMoreOptions('z','c',"down left","down right");
                //         break;
                //     case 3:
                //         pMoreOptions('q','z',"top left","down left");
                //         break;
                //     case 4:
                //         pMoreOptions('e','c',"top right","down right");
                //         break;
                    
                //     default:
                //         break;
                //     }
                // }
                // else if (counter%2!=0)
                //     switch (bentType(x1,y1,x2,y2,counter))
                //     {
                //     case 1:
                //         pMoreOptions('z','c',"down left","down right");
                //         break;
                //     case 2:
                //         pMoreOptions('q','e',"top left","top right");
                //         break;
                //     case 3:
                //         pMoreOptions('e','c',"top right","down right");
                //         break;
                //     case 4:
                //         pMoreOptions('q','z',"top left","down left");
                //         break;
                    
                //     default:
                //         break;
                //     }
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
                }       //end of select move type
                

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
                            WallPassingError(swOfPlayerType);
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
                            WallPassingError(swOfPlayerType);        
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
                            WallPassingError(swOfPlayerType);     
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
                            WallPassingError(swOfPlayerType);        
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
                            WallPassingError(swOfPlayerType);    
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
                            WallPassingError(swOfPlayerType);      
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
                            WallPassingError(swOfPlayerType);     
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
                            WallPassingError(swOfPlayerType);       
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
                        else BoardExitError(swOfPlayerType);  
                    }
                          
                    
                    else
                    {
                        BoardExitError(swOfPlayerType);     
                    }       
                }




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
                            WallPassingError(swOfPlayerType);   
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
                            WallPassingError(swOfPlayerType);
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
                            WallPassingError(swOfPlayerType);        
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
                            WallPassingError(swOfPlayerType);                    
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
                            WallPassingError(swOfPlayerType);                   
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
                            WallPassingError(swOfPlayerType);              
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
                            WallPassingError(swOfPlayerType);  
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
                            WallPassingError(swOfPlayerType);                                   
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
                        else BoardExitError(swOfPlayerType);  
                    }   

                    else
                    {
                        BoardExitError(swOfPlayerType);                            
                    }                    
                }                    
            }     //end of move  
            board[2*x1][2*y1]='1';      //player 1 moved
            board[2*x2][2*y2]='2';      //player 2 moved

        }
        
            
            

        else if (decision=='w')
        {
            if (counter%2==0)
            {
                if (p1Walls>0)
                {
                    p1Walls--;
                }
                else
                {
                    ZeroWallError(swOfPlayerType);
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
                    ZeroWallError(swOfPlayerType);
                    goto lable;
                }

            }

            
            
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
                }        //end of wall selectiont
                

                
                xOfWall *= 2;
                yOfWall *= 2;
                if(wallDirect == 'H' && xOfWall-1>-1  && xOfWall<2*n-1 && yOfWall>-1 && yOfWall+2<2*n-1 && board[xOfWall-1][yOfWall] == 32 && board[xOfWall-1][yOfWall + 1] == 32 && board[xOfWall-1][yOfWall + 2]  == 32)
                {
                    board[xOfWall-1][yOfWall] = 196;

                    board[xOfWall-1][yOfWall + 1] = 196;

                    board[xOfWall-1][yOfWall + 2] = 196;

                    if (counter%2==0 && p1Walls<4)
                    {
                        RemainingWalls(p1Walls,swOfPlayerType);
                    }
                    else if (counter%2!=0 && p2Walls<4)
                    {
                        RemainingWalls(p2Walls,swOfPlayerType);
                    }
                    // break;
                }
                else if (wallDirect=='V' && yOfWall-1>-1 && yOfWall<2*n-1 && xOfWall-2>-1 && xOfWall<2*n-1 && board[xOfWall][yOfWall-1] == 32 && board[xOfWall-1][yOfWall-1]  == 32 && board[xOfWall-2][yOfWall-1] == 32)
                {
                    board[xOfWall][yOfWall-1] = 179;

                    board[xOfWall-1][yOfWall-1] = 179;

                    board[xOfWall-2][yOfWall-1] = 179;

                    if (counter%2==0 && p1Walls<4)
                    {
                        RemainingWalls(p1Walls,swOfPlayerType);
                    }
                    else if (counter%2!=0 && p2Walls<4)
                    {
                        RemainingWalls(p2Walls,swOfPlayerType);
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



                if (counter%2==0)
                {
                    if (paint(n,2*x2,2*y2,counter,x1Saver,x2Saver))
                    {
                        break;
                    }
                    else
                    {
                        stuckError();
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
                        stuckError();
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
                
                

            }

        }


        // clearscreen();      //clear terminal

        for (int i = 0; i < 2*n-1; i++)     //print the updated board
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

        counter++;      //this can tell the computer that the turn of current player finished    
    }
    //end of geme
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
    
    
    
    
    return 0;
}
