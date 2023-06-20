#include <iostream>
#include <ctime>  //These are used to choose random places.
#include  <cstdlib>
#include <iomanip>
#include <bits/stdc++.h>
using namespace std;

int board[4][4];
int dirrow[]= {1, 0, -1, 0};
int dircol[]= {0, 1, 0, -1};


pair<int,int>genunoccupiedposition()
{
    int occupied=1;
    int row,col;
    while(occupied)
    {
        row=rand()%4;
        col=rand()%4;
        if(board[row][col]==0) occupied=0;
    }
    return make_pair(row,col);
}

void addingpiece()
{
    pair<int,int>position=genunoccupiedposition();
    board[position.first][position.second]=2;
}


void newgamestarts()
{
    for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
            board[i][j]=0;
            addingpiece();
}


void therules()
{
    system("cls");
    for(int i=0; i<4; ++i)
    {
        for(int j=0; j<4; ++j)
            if(board[i][j]==0)
                cout<<setw(4)<<".";
            else
                cout<<setw(4)<<board[i][j];
        cout<<endl;
    }
    cout<<"n:New game , w: Up , s:Down , d:Right , a:Left ,  q:Quit  "<<endl;
}


bool candomove(int i,int j,int nexti,int nextj)
{
    if(nexti<0 || nextj<0 || nexti>=4 || nextj>=4 ||
            (board[i][j]!=board[nexti][nextj] &&  board[nexti][nextj]!=0) )
        return false;
    return true;
}

void applymove(int currentmove)
{
    int startrow=0;
    int startcol=0;
    int steprow=1;
    int stepcol=1;
    if(currentmove==0)
    {
        startrow=3;
        steprow=-1;
    }
    if(currentmove==1)
    {
        startcol=3;
        stepcol=-1;
    }
    int possiblemove,canaddpiece=0;
    do{
        possiblemove=0;
    for(int i=startrow; i>=0&&i<4; i=i+steprow)
        for(int j=startcol; j>=0 && j<4; j=j+stepcol)
        {
            int nexti=i+dirrow[currentmove], nextj=j+dircol[currentmove];
            //cout<<i<<" "<<j<<nexti<<" "<<nextj<<endl;
            if( board[i][j]!=0 &&  candomove(i,j,nexti,nextj))
            {
                board[nexti][nextj]+=board[i][j];
                board[i][j]=0;
                possiblemove=canaddpiece=1;
            }
        }
    therules();
    }while(possiblemove);
        if(canaddpiece){
            addingpiece();
        }
}




int main()
{
    srand(time(0));
    char mapcommand[128]; //I took 128 because Ascii values of a to z lie in between 1-128 and I can use any other keys in future to process the game.
    mapcommand['s']=0;
    mapcommand['d']=1;
    mapcommand['w']=2;
    mapcommand['a']=3;
    newgamestarts();
    while(true)
    {
        therules();
        char command;
        cin>>command;
        //Processing
        if(command=='n')
            newgamestarts();
        else if(command=='q')
            break;
        else
        {
            int currentmove=mapcommand[command];
            //cout<<currentmove<<endl;
            applymove(currentmove);
        }
    }
    return 0;
}

