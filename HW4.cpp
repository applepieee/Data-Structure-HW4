#include<iostream>
#include <iomanip>
#include<queue>

using namespace std;
bool val[20][20],val_bfs[20][20];//whether visited or no
int map1[20][20],map2[20][20],map3[20][20],map4[20][20];
int r,c,mini;//dir;//1:rieht 2:down 3:left 4:up
bool last_bfs=false;//while veritfy can they escape from fire need
class point//def a point class
{
public:
    int col;
    int row;
};
queue<point> q;//bfs need
void print_map(int (*map)[20],int setw_num)//print map
{

    for(int i=0;i<r;i++)
    {
         for(int j=0;j<c;j++)
            if(map1[i][j]==-1 && map != map2)
                cout <<  setw(setw_num) << "-1";
            else
                cout <<  setw(setw_num) << map[i][j];
        cout << endl;
    }

}



void DFS(int row,int col,int num,int dir)
{
    val[row][col]=true;//whether visited or no

    if(map1[row][col+1]!=1 && (col+1) < c && dir !=3 && !val[row][col+1])//right
    {
        map2[row][col+1]=num;
        DFS(row,col+1,num,1);
    }
    if(map1[row+1][col]!=1 &&(row+1)<r && dir !=4 && !val[row+1][col])//down
    {
        map2[row+1][col]=num;
        DFS(row+1,col,num,2);
    }
    if((col-1) > -1 && map1[row][col-1]!=1 && dir !=1 && !val[row][col-1])//left
    {
        map2[row][col-1]=num;
        DFS(row,col-1,num,3);
    }

    if((row-1)> -1 && dir !=2 && map1[row-1][col]!=1 && !val[row-1][col])//up
    {
        map2[row-1][col]=num;
        DFS(row-1,col,num,4);
    }
}
bool IsVal(int row,int col)
{
    if(row>-1 && row<r && col > -1 && col<c )//check if out of map
        return true;
    return false;
}
bool IsBound(int row,int col)//check bound
{
    if(row== r-1 || col== c-1 || row==0 || col==0)
         return true;
    return false;
}

void BFS(int (*map)[20])
{
    mini=r*c;
    point p;
    while(q.size() !=0)
    {
        p=q.front();
        q.pop();
        int row[4]={p.row-1,p.row,p.row+1,p.row};//0:up 1:right 2:dowm 3:left
        int col[4]={p.col,p.col+1,p.col,p.col-1};
        int cross_row[4]={p.row-1,p.row+1,p.row+1,p.row-1};
        int cross_col[4]={p.col+1,p.col+1,p.col-1,p.col-1};
        for(int i=0;i<4;i++)
        {
            if(map1[row[i]][col[i]]!=1 && IsVal(row[i],col[i]) && !val_bfs[row[i]][col[i]] )//can walk
            {
                if(last_bfs)
                    if( ((map[p.row][p.col]+1) > map4[row[i]][col[i]] ) || ((map[p.row][p.col]+1) == map4[row[i]][col[i]] )  )//run slower than fire
                        continue;

                map[row[i]][col[i]]=map[p.row][p.col]+1;
                val_bfs[row[i]][col[i]]=true;
                point tmp;
                tmp.col=col[i];
                tmp.row=row[i];
                q.push(tmp);
                if(IsBound(row[i],col[i]))
                {
                    if(map[row[i]][col[i]] < mini)
                        mini=map[row[i]][col[i]];
                }
            }
            if(map==map4 && map1[cross_row[i]][cross_col[i]] !=1 && IsVal(cross_row[i],cross_col[i]) && !val_bfs[cross_row[i]][cross_col[i]])
            {
                point tmp;
                val_bfs[cross_row[i]][cross_col[i]]=true;
                map[cross_row[i]][cross_col[i]]=map[p.row][p.col]+1;
                tmp.col=cross_col[i];
                tmp.row=cross_row[i];
                q.push(tmp);
            }
        }

    }
}

int main()
{
    int y,x;
    char input;

    cin >> r >> c >>y >> x;
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
        {
            cin >> input;
            switch(input)
            {
            case '%':
                map1[i][j]=-1;
                break;
            case '+':
                map1[i][j]=1;
                break;
            case '$':
                map1[i][j]=0;
                break;
            default:
                break;
            }
        }
    cout << "[1]show the map" << endl;
    print_map(map1,2);
    int col,row,start_num=0;
    for(row=0;row<r;row++)//search start point
        for(col=0;col<c;col++)
            if(map1[row][col]!=1 && val[row][col]==false )
            {
                map2[row][col]=start_num+1;
                DFS(row,col,start_num+1,1);
                start_num++;
            }
    cout<<"=================================="<<endl;
    cout << "[2]show the map" << endl;
    print_map(map2,3);
    cout <<"The number of regions is? ";
    cout <<start_num << endl;
    cout<<"=================================="<<endl;
    cout << "[3]show the map" << endl;
    point p1;//-1 point
    for(int row=0;row<r;row++)//search -1 point
        for(int col=0;col<c;col++)
            if(map1[row][col]==-1)
            {
                p1.col=col;
                p1.row=row;
                q.push(p1);
                break;
            }


    BFS(map3);
    print_map(map3,3);
    cout <<"Is there a miimum path? " ;
    if(mini==r*c)
        cout <<"-1";
    else
        cout << mini;
    cout<<endl;
    cout<<"=================================="<<endl;
    cout << "[4]show the map" << endl;
    while(!q.empty()) q.pop();//clear queue
    for(int i=0;i<20;i++)//inital array val_bfs
        for(int j=0;j<20;j++)
            val_bfs[i][j]=false;
    point p2;//fire point
    p2.col=x;
    p2.row=y;
    q.push(p2);
    BFS(map4);
    for(int i=0;i<r;i++)//print map4
    {
        for(int j=0;j<c;j++)
            if(i==y && j==x )
                cout <<  setw(3) << "-1";
            else
                cout <<  setw(3) << map4[i][j];
         cout <<endl;
    }

    cout <<" Can they escape from the fire? ";
    for(int i=0;i<20;i++)//inital array val_bfs,map3
    {
         for(int j=0;j<20;j++)
        {
            val_bfs[i][j]=false;
            map3[i][j]=0;
        }
    }
    q.push(p1);
    last_bfs=true;
    BFS(map3);
    if(mini==r*c)
        cout <<"-1";
    else
        cout << mini;
}
