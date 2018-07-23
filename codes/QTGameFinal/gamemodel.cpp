#include "gamemodel.h"
GameModel::GameModel():gamestatus(Playing),gamedifficulty(Easy)//首先进行游戏状态和游戏难度对象的赋值！！
{}
GameModel::~GameModel()
{
    //需要销毁动态分配的一切..
    if(gameMap!=NULL)
    {
        delete gameMap;
        gameMap=NULL;
    }
}
void GameModel::startGame()
{
    startGame(gamedifficulty);
}
void GameModel::startGame(GameDiffculty gamedif)//点击按钮后进入游戏，游戏状态为进行中...
{
       //首先给地图分配空间..
    gameMap=new int[sizeof(int)*(MAX_col+3)*(MAX_row+3)+1];//起码多留两行用于边界画线！！
    gamedifficulty=gamedif;//初始化游戏难度.. 注意是整场游戏的难度！！
    gamestatus=Playing;//游戏中...
    for(int i=0;i<(MAX_row+3)*(MAX_col+3);i++)
        gameMap[i]=0;//一个个进行初始化..请注意，当gameMap[mr*x+y]=0时，代表该点(x,y)没有图片，为1时，为pic1,2时为pic2....
    //MAX_ROW*x+y表示坐标(x,y)
    int Gamedifnum;
    //初始化分数！
    grades=0;

    switch(gamedifficulty)//初始化游戏方块数量！
    {
    case Easy:
        Gamedifnum=easynum;
        break;
    case Normal:
        Gamedifnum=normalnum;
        break;
    case Hard:
        Gamedifnum=hardnum;
        break;
    }
    painting.clear();//清理绘画数组！
    //先分配图片！
    int picID=0;
    //每次填充相邻位置的两个！！Gamedifnum已经表明了不同难度下的方块数量！现在只需循环一遍填picID
    for(int i=0;i<Gamedifnum;i+=2)
    {//后面会超过..只需取余便可循环
        gameMap[i]=picID%MAX_icon+1;
        gameMap[i+1]=picID%MAX_icon+1;//保证图片成对出现，然后打乱，最后填充！!
        picID++;
    }
   //随机打乱游戏地图
    srand((unsigned)time(NULL));//播随机数种子！
    for(int i=0;i<MAX_col*MAX_row;i++)
    {
        int randomnum=rand()%(MAX_col*MAX_row);
        std::swap(gameMap[i],gameMap[randomnum]);
    }
}
GameStatus GameModel::getgamestatus()//获得游戏状态！
{
    return gamestatus;
}
void GameModel::setgamestatus(GameStatus gamesta)
{
    gamestatus=gamesta;
}
int GameModel::canbelinked(Point p1, Point p2)//调用三个消除算法函数！消除一对加20分！
{
    //其中一个为空！
    if(gameMap[MAX_row*p1.x+p1.y]==0||gameMap[MAX_row*p2.x+p2.y]==0) return false;
    //两个图标对不上！
    else if(gameMap[MAX_row*p1.x+p1.y]!=gameMap[MAX_row*p2.x+p2.y]) return false;
    else if(canlinkdirectly(p1,p2))//直接消除！
    {
        painting.clear();
        painting.push_back(p1);
        painting.push_back(p2);
        qDebug()<<"a"<<p1.x<<" "<<p1.y<<" "<<p2.x<<" "<<p2.y<<"b"<<"\n";
        grades+=40;
        return 1;
    }
    else if(canlinkonecorner(p1,p2))//二线
    {
        painting.clear();
        painting.push_back(p1);
        painting.push_back(tpone);
        painting.push_back(p2);
        //qDebug()<<p1.x<<" "<<p1.y<<" "<<p2.x<<" "<<p2.y<<tpone.x<<" "<<tpone.y<<"\n";
        grades+=40;
        tpone.x=tpone.y=-3;
        return 2;
    }
    else if(canlinktwocorner(p1,p2))//三线
    {
        qDebug()<<"rubbish qt fuck you!"<<"\n";
        painting.clear();
        painting.push_back(p1);
        painting.push_back(tp1);
        painting.push_back(tp2);
        painting.push_back(p2);
        qDebug()<<"e"<<painting[0].x<<painting[0].y<<"f"<<"\n";
        tp1.x=tp1.y=tp2.x=tp2.y=-3;
        grades+=40;
        return 3;
    }
    else //不能消除！
    {
        painting.clear();
        return 0;
    }
}

//给判定死局一个没有vector的判定连接函数！
int GameModel::canbelinked2(Point p1, Point p2)//调用三个消除算法函数！消除一对加20分！
{
    //其中一个为空！
    if(gameMap[MAX_row*p1.x+p1.y]==0||gameMap[MAX_row*p2.x+p2.y]==0) return false;
    //两个图标对不上！
    else if(gameMap[MAX_row*p1.x+p1.y]!=gameMap[MAX_row*p2.x+p2.y]) return false;
    else if(canlinkdirectly(p1,p2))//直接消除！
        return 1;
    else if(canlinkonecorner(p1,p2))//二线
        return 2;
    else if(canlinktwocorner(p1,p2))//三线
        return 3;
    else //不能消除！
        return 0;
}
//下面进入核心算法部分，判定一线/二线/三线消除以及判断是否进入死局（或许可以考虑dfs+剪枝法？？）暴力法，每个图片都判定n线消除，n=1,2,3!共(n-1)^2次..dfs：对图片采用索引法，同种图片内标号，从no1-no.n一共检验(n-1)*n/2,减少检验次数...

//一线消除，也是最简单的判定算法...
bool GameModel::canlinkdirectly(Point p1, Point p2)
{
    if(p1==p2) return false;
    if(p1.x!=p2.x&&p1.y!=p2.y) return false;
    //横向！
    if(p1.y==p2.y)
    {
        if(p1.x<p2.x)//统一化，保证p1x>p2x
            std::swap(p1.x,p2.x);
        for(int i=p2.x+1;i<p1.x;i++)
        if(gameMap[MAX_row*i+p1.y])//有图片时
            //MAX_ROW*x+y表示坐标(x,y)

        {
            //qDebug()<<"column pic"<<"\n";
            return false;
        }
    }
    //纵向
    if(p1.x==p2.x)
    {
        if(p1.y<p2.y)//统一化，保证p1y>p2y
            std::swap(p1.y,p2.y);
        for(int i=p2.y+1;i<p1.y;i++)
        if(gameMap[MAX_row*p1.x+i])//有图片时
            //MAX_ROW*x+y表示坐标(x,y)
        {
            //qDebug()<<"row pic"<<"\n";
            return false;
        }
    }
    return true;
}
bool GameModel::canlinkonecorner(Point p1, Point p2)//二线消除
{
    Point tpone1(p1.x,p2.y);//两种可能拐点！
    Point tpone2(p2.x,p1.y);
    //使用bfs,利用单线消除解决二线消除问题！
    //若一线消除不能完成，则直接跳过二线消除，二线消除要求两点x y 均不同！！！
    if(p1.x==p2.x||p1.y==p2.y) return false;
    if(canlinkdirectly(p1,tpone1)&&canlinkdirectly(tpone1,p2)&&!gameMap[tpone1.x*MAX_row+tpone1.y]) //两条路都通！ 注意这里有坑！！必须判断拐角位是否有图片！！
    {
        qDebug()<<"tpcorner1"<<"\n";
        tpone=tpone1;
        return true;
    }
    if(canlinkdirectly(p1,tpone2)&&canlinkdirectly(tpone2,p2)&&!gameMap[tpone2.x*MAX_row+tpone2.y])//两条皆通！
    {
        qDebug()<<"tpcorner2"<<"\n";
        tpone=tpone2;
        return true;
    }
    return false;
}
//三线消除最容易出问题！！赶紧修复！
//可能要经历多次修改！
bool GameModel::canlinktwocorner(Point p1, Point p2)//三线消除！
{
    Point tp2corner1;
    Point tmp1,tmp2;//用于储存边界情况！
    //tp2corner1其中一个坐标跟p1一致，另外一个坐标需要灵活变动（采用循环！！） tp2corner2一个坐标与tp2corner1一致，另外一个坐标与p2一致！
    //这里不会采用最佳路径！显示任一可行路径即可!

    //tp2corner1(以下简称tp1)x与p1x相同，分为两种情况！
    tp2corner1.x=p1.x;
    //p1y++ 一般情况！
    for(int i=p1.y+1;i<MAX_col&&!gameMap[MAX_row*p1.x+i];i++)//搜索+判定
        //以后边界有可能变动！注意了！！
    {
        tp2corner1.y=i;
        if(canlinkonecorner(tp2corner1,p2))//可以连接！
        {
            qDebug()<<"p1y++"<<"\n";
            tp1=tp2corner1;
            tp2=tpone;
            tpone.x=-3;tpone.y=-3;
            return true;
        }
    }
    //边界情况！ p1y++ max_col!
    tmp1.x=p1.x;tmp1.y=MAX_col;
    tmp2.x=p2.x;tmp2.y=MAX_col;
    if((canlinkdirectly(p1,tmp1)||p1.y==MAX_col-1)&&(canlinkdirectly(tmp2,p2)||p2.y==MAX_col-1)){
        qDebug()<<"p1y++ 边界"<<"\n";
        tp1=tmp1;tp2=tmp2;
        return true;
    }
    //p1y--  一般情况！
    for(int i=p1.y-1;i>=0&&!gameMap[MAX_row*p1.x+i];i--)//注意未来可能出现的边界变动！
    {
        tp2corner1.y=i;
        if(canlinkonecorner(tp2corner1,p2))
        {
            qDebug()<<"p1y--"<<"\n";
            tp1=tp2corner1;
            tp2=tpone;
            tpone.x=-3;tpone.y=-3;
            return true;
        }
    }
    //边界！
    tmp1.x=p1.x;tmp1.y=-1;
    tmp2.x=p2.x;tmp2.y=-1;
    qDebug()<<"p1y--  边界"<<"\n"<<tmp1.x<<" "<<tmp1.y<<" "<<p1.x<<" "<<p1.y<<"\n";
    if((canlinkdirectly(p1,tmp1)||p1.y==0)&&(canlinkdirectly(tmp2,p2)||p2.y==0)){
        qDebug()<<"p1y-- 边界"<<"\n";
        tp1=tmp1;tp2=tmp2;
        return true;
    }
    //重置tp2corn1!
    tp2corner1.x=-3;tp2corner1.y=-3;

    //tp1 y与p1y相同，也分为两种情况！
    tp2corner1.y=p1.y;
    //p1x++   一般情况！
    for(int i=p1.x+1;i<MAX_row&&!gameMap[MAX_row*i+p1.y];i++)//搜索+判定
        //以后边界有可能变动！注意了！！
    {
        tp2corner1.x=i;
        if(canlinkonecorner(tp2corner1,p2))//可以连接！
        {
            qDebug()<<"p1x++"<<"\n";
            tp1=tp2corner1;
            tp2=tpone;
            tpone.x=-3;tpone.y=-3;
            return true;
        }
    }
    //边界情况
    tmp1.y=p1.y;tmp1.x=MAX_row;
    tmp2.y=p2.y;tmp2.x=MAX_row;
    qDebug()<<"p1x++  边界"<<"\n"<<tmp1.x<<" "<<tmp1.y<<" "<<p1.x<<" "<<p1.y<<"\n";
    if((canlinkdirectly(p1,tmp1)||p1.x==MAX_row-1)&&(canlinkdirectly(tmp2,p2)||p2.x==MAX_row-1)){
        qDebug()<<"p1x++  边界"<<"\n";
        tp1=tmp1;tp2=tmp2;
        return true;
    }
    //p1x--   一般情况！
    for(int i=p1.x-1;i>=0&&!gameMap[MAX_row*i+p1.y];i--)//搜索+判定
        //以后边界有可能变动！注意了！！
    {
        tp2corner1.x=i;
        if(canlinkonecorner(tp2corner1,p2))//可以连接！
        {
            qDebug()<<"p1x--"<<"\n";
            tp1=tp2corner1;
            tp2=tpone;
            tpone.x=-3;tpone.y=-3;
            return true;
        }
    }
    //边界判断！
    tmp1.y=p1.y;tmp1.x=-1;
    tmp2.y=p2.y;tmp2.x=-1;
    if((canlinkdirectly(p1,tmp1)||p1.x==0)&&(canlinkdirectly(tmp2,p2)||p2.x==0)){
        qDebug()<<"p1x-- 边界"<<"\n";
        tp1=tmp1;tp2=tmp2;
        return true;
    }
    //不符合条件则重置该点！
    qDebug()<<"failed!pp"<<"\n";
    tp2corner1.x=-3;tp2corner1.y=-3;
    tp1.x=tp1.y=tp2.x=tp2.y=-3;
    return false;
}
int* GameModel::getMap()//获取地图
{
    return gameMap;
}
bool GameModel::isblocked()//判断是否进入死局
{//方法一，暴力解决！
    //两两判断(i1,j1) (i2,j2)
    //先判断是否为同一对图片，然后当出现有一对图片可以进行消除的时候，即不是死局时，可以直接退出！！
    //最坏情况：出现死局，那么所有在场图片都要进行判断，且不能直接退出！！
    Point p1,p2;
    if(isWin())//胜利不包括在block里面！！
        return false;
    for(int i=0;i<MAX_col*MAX_row-1;i++)
        for(int j=i+1;j<MAX_col*MAX_row;j++)
        {
            p1.y=i%MAX_row;
            p1.x=i/MAX_row;
            p2.y=j%MAX_row;
            p2.x=j/MAX_row;
            //先判断该点有没有图片，没有则跳过！
            if(!gameMap[p1.x*MAX_row+p1.y]||!gameMap[p2.x*MAX_row+p2.y])
                continue;
            //先判断是否为同一个图片 不是则跳过！
            if(gameMap[p1.x*MAX_row+p1.y]!=gameMap[p2.x*MAX_row+p2.y])
                continue;
            //然后进行判断！
            if(canbelinked2(p1,p2))//如果可以连接！
                return false;
        }
    //全部不能连接则死局！
    return true;
}
bool GameModel::isWin()
{
    for(int i=0;i<MAX_row*MAX_col;i++)
    {
        if(gameMap[i])//地图一旦出现有图片，则说明没有完成消除！
        {
            qDebug()<<"false"<<"\n";
            return false;
        }
    }
    //没有图片则完成！
    gamestatus=Win;
    return true;
}
void GameModel::block_rearrange()
{
    //不需要delete掉原来的map，因为消除后会将gamemap置为0！
    do
    {
        //先进行坐标重排！
        srand((unsigned)time(NULL));
        for(int i=0;i<MAX_col*MAX_row;i++)
        {
            int randomnum=rand()%(MAX_col*MAX_row);//制造随机数！
            //交换坐标i与坐标randomnum两者的gamemap(即图片！)！！
            std::swap(gameMap[i],gameMap[randomnum]);
        }
    }while(isblocked());
}
void GameModel::setgamemap(int cur,int i)
{
    gameMap[i]=cur;
}
