#include "gamemodel.h"
GameModel::GameModel():gamestatus(Playing),gamedifficulty(Easy)//���Ƚ�����Ϸ״̬����Ϸ�Ѷȶ���ĸ�ֵ����
{}
GameModel::~GameModel()
{
    //��Ҫ���ٶ�̬�����һ��..
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
void GameModel::startGame(GameDiffculty gamedif)//�����ť�������Ϸ����Ϸ״̬Ϊ������...
{
       //���ȸ���ͼ����ռ�..
    gameMap=new int[sizeof(int)*(MAX_col+3)*(MAX_row+3)+1];//��������������ڱ߽续�ߣ���
    gamedifficulty=gamedif;//��ʼ����Ϸ�Ѷ�.. ע����������Ϸ���Ѷȣ���
    gamestatus=Playing;//��Ϸ��...
    for(int i=0;i<(MAX_row+3)*(MAX_col+3);i++)
        gameMap[i]=0;//һ�������г�ʼ��..��ע�⣬��gameMap[mr*x+y]=0ʱ������õ�(x,y)û��ͼƬ��Ϊ1ʱ��Ϊpic1,2ʱΪpic2....
    //MAX_ROW*x+y��ʾ����(x,y)
    int Gamedifnum;
    //��ʼ��������
    grades=0;

    switch(gamedifficulty)//��ʼ����Ϸ����������
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
    painting.clear();//����滭���飡
    //�ȷ���ͼƬ��
    int picID=0;
    //ÿ���������λ�õ���������Gamedifnum�Ѿ������˲�ͬ�Ѷ��µķ�������������ֻ��ѭ��һ����picID
    for(int i=0;i<Gamedifnum;i+=2)
    {//����ᳬ��..ֻ��ȡ����ѭ��
        gameMap[i]=picID%MAX_icon+1;
        gameMap[i+1]=picID%MAX_icon+1;//��֤ͼƬ�ɶԳ��֣�Ȼ����ң������䣡!
        picID++;
    }
   //���������Ϸ��ͼ
    srand((unsigned)time(NULL));//����������ӣ�
    for(int i=0;i<MAX_col*MAX_row;i++)
    {
        int randomnum=rand()%(MAX_col*MAX_row);
        std::swap(gameMap[i],gameMap[randomnum]);
    }
}
GameStatus GameModel::getgamestatus()//�����Ϸ״̬��
{
    return gamestatus;
}
void GameModel::setgamestatus(GameStatus gamesta)
{
    gamestatus=gamesta;
}
int GameModel::canbelinked(Point p1, Point p2)//�������������㷨����������һ�Լ�20�֣�
{
    //����һ��Ϊ�գ�
    if(gameMap[MAX_row*p1.x+p1.y]==0||gameMap[MAX_row*p2.x+p2.y]==0) return false;
    //����ͼ��Բ��ϣ�
    else if(gameMap[MAX_row*p1.x+p1.y]!=gameMap[MAX_row*p2.x+p2.y]) return false;
    else if(canlinkdirectly(p1,p2))//ֱ��������
    {
        painting.clear();
        painting.push_back(p1);
        painting.push_back(p2);
        qDebug()<<"a"<<p1.x<<" "<<p1.y<<" "<<p2.x<<" "<<p2.y<<"b"<<"\n";
        grades+=40;
        return 1;
    }
    else if(canlinkonecorner(p1,p2))//����
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
    else if(canlinktwocorner(p1,p2))//����
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
    else //����������
    {
        painting.clear();
        return 0;
    }
}

//���ж�����һ��û��vector���ж����Ӻ�����
int GameModel::canbelinked2(Point p1, Point p2)//�������������㷨����������һ�Լ�20�֣�
{
    //����һ��Ϊ�գ�
    if(gameMap[MAX_row*p1.x+p1.y]==0||gameMap[MAX_row*p2.x+p2.y]==0) return false;
    //����ͼ��Բ��ϣ�
    else if(gameMap[MAX_row*p1.x+p1.y]!=gameMap[MAX_row*p2.x+p2.y]) return false;
    else if(canlinkdirectly(p1,p2))//ֱ��������
        return 1;
    else if(canlinkonecorner(p1,p2))//����
        return 2;
    else if(canlinktwocorner(p1,p2))//����
        return 3;
    else //����������
        return 0;
}
//�����������㷨���֣��ж�һ��/����/���������Լ��ж��Ƿ�������֣�������Կ���dfs+��֦����������������ÿ��ͼƬ���ж�n��������n=1,2,3!��(n-1)^2��..dfs����ͼƬ������������ͬ��ͼƬ�ڱ�ţ���no1-no.nһ������(n-1)*n/2,���ټ������...

//һ��������Ҳ����򵥵��ж��㷨...
bool GameModel::canlinkdirectly(Point p1, Point p2)
{
    if(p1==p2) return false;
    if(p1.x!=p2.x&&p1.y!=p2.y) return false;
    //����
    if(p1.y==p2.y)
    {
        if(p1.x<p2.x)//ͳһ������֤p1x>p2x
            std::swap(p1.x,p2.x);
        for(int i=p2.x+1;i<p1.x;i++)
        if(gameMap[MAX_row*i+p1.y])//��ͼƬʱ
            //MAX_ROW*x+y��ʾ����(x,y)

        {
            //qDebug()<<"column pic"<<"\n";
            return false;
        }
    }
    //����
    if(p1.x==p2.x)
    {
        if(p1.y<p2.y)//ͳһ������֤p1y>p2y
            std::swap(p1.y,p2.y);
        for(int i=p2.y+1;i<p1.y;i++)
        if(gameMap[MAX_row*p1.x+i])//��ͼƬʱ
            //MAX_ROW*x+y��ʾ����(x,y)
        {
            //qDebug()<<"row pic"<<"\n";
            return false;
        }
    }
    return true;
}
bool GameModel::canlinkonecorner(Point p1, Point p2)//��������
{
    Point tpone1(p1.x,p2.y);//���ֿ��ܹյ㣡
    Point tpone2(p2.x,p1.y);
    //ʹ��bfs,���õ���������������������⣡
    //��һ������������ɣ���ֱ������������������������Ҫ������x y ����ͬ������
    if(p1.x==p2.x||p1.y==p2.y) return false;
    if(canlinkdirectly(p1,tpone1)&&canlinkdirectly(tpone1,p2)&&!gameMap[tpone1.x*MAX_row+tpone1.y]) //����·��ͨ�� ע�������пӣ��������жϹս�λ�Ƿ���ͼƬ����
    {
        qDebug()<<"tpcorner1"<<"\n";
        tpone=tpone1;
        return true;
    }
    if(canlinkdirectly(p1,tpone2)&&canlinkdirectly(tpone2,p2)&&!gameMap[tpone2.x*MAX_row+tpone2.y])//������ͨ��
    {
        qDebug()<<"tpcorner2"<<"\n";
        tpone=tpone2;
        return true;
    }
    return false;
}
//�������������׳����⣡���Ͻ��޸���
//����Ҫ��������޸ģ�
bool GameModel::canlinktwocorner(Point p1, Point p2)//����������
{
    Point tp2corner1;
    Point tmp1,tmp2;//���ڴ���߽������
    //tp2corner1����һ�������p1һ�£�����һ��������Ҫ���䶯������ѭ�������� tp2corner2һ��������tp2corner1һ�£�����һ��������p2һ�£�
    //���ﲻ��������·������ʾ��һ����·������!

    //tp2corner1(���¼��tp1)x��p1x��ͬ����Ϊ���������
    tp2corner1.x=p1.x;
    //p1y++ һ�������
    for(int i=p1.y+1;i<MAX_col&&!gameMap[MAX_row*p1.x+i];i++)//����+�ж�
        //�Ժ�߽��п��ܱ䶯��ע���ˣ���
    {
        tp2corner1.y=i;
        if(canlinkonecorner(tp2corner1,p2))//�������ӣ�
        {
            qDebug()<<"p1y++"<<"\n";
            tp1=tp2corner1;
            tp2=tpone;
            tpone.x=-3;tpone.y=-3;
            return true;
        }
    }
    //�߽������ p1y++ max_col!
    tmp1.x=p1.x;tmp1.y=MAX_col;
    tmp2.x=p2.x;tmp2.y=MAX_col;
    if((canlinkdirectly(p1,tmp1)||p1.y==MAX_col-1)&&(canlinkdirectly(tmp2,p2)||p2.y==MAX_col-1)){
        qDebug()<<"p1y++ �߽�"<<"\n";
        tp1=tmp1;tp2=tmp2;
        return true;
    }
    //p1y--  һ�������
    for(int i=p1.y-1;i>=0&&!gameMap[MAX_row*p1.x+i];i--)//ע��δ�����ܳ��ֵı߽�䶯��
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
    //�߽磡
    tmp1.x=p1.x;tmp1.y=-1;
    tmp2.x=p2.x;tmp2.y=-1;
    qDebug()<<"p1y--  �߽�"<<"\n"<<tmp1.x<<" "<<tmp1.y<<" "<<p1.x<<" "<<p1.y<<"\n";
    if((canlinkdirectly(p1,tmp1)||p1.y==0)&&(canlinkdirectly(tmp2,p2)||p2.y==0)){
        qDebug()<<"p1y-- �߽�"<<"\n";
        tp1=tmp1;tp2=tmp2;
        return true;
    }
    //����tp2corn1!
    tp2corner1.x=-3;tp2corner1.y=-3;

    //tp1 y��p1y��ͬ��Ҳ��Ϊ���������
    tp2corner1.y=p1.y;
    //p1x++   һ�������
    for(int i=p1.x+1;i<MAX_row&&!gameMap[MAX_row*i+p1.y];i++)//����+�ж�
        //�Ժ�߽��п��ܱ䶯��ע���ˣ���
    {
        tp2corner1.x=i;
        if(canlinkonecorner(tp2corner1,p2))//�������ӣ�
        {
            qDebug()<<"p1x++"<<"\n";
            tp1=tp2corner1;
            tp2=tpone;
            tpone.x=-3;tpone.y=-3;
            return true;
        }
    }
    //�߽����
    tmp1.y=p1.y;tmp1.x=MAX_row;
    tmp2.y=p2.y;tmp2.x=MAX_row;
    qDebug()<<"p1x++  �߽�"<<"\n"<<tmp1.x<<" "<<tmp1.y<<" "<<p1.x<<" "<<p1.y<<"\n";
    if((canlinkdirectly(p1,tmp1)||p1.x==MAX_row-1)&&(canlinkdirectly(tmp2,p2)||p2.x==MAX_row-1)){
        qDebug()<<"p1x++  �߽�"<<"\n";
        tp1=tmp1;tp2=tmp2;
        return true;
    }
    //p1x--   һ�������
    for(int i=p1.x-1;i>=0&&!gameMap[MAX_row*i+p1.y];i--)//����+�ж�
        //�Ժ�߽��п��ܱ䶯��ע���ˣ���
    {
        tp2corner1.x=i;
        if(canlinkonecorner(tp2corner1,p2))//�������ӣ�
        {
            qDebug()<<"p1x--"<<"\n";
            tp1=tp2corner1;
            tp2=tpone;
            tpone.x=-3;tpone.y=-3;
            return true;
        }
    }
    //�߽��жϣ�
    tmp1.y=p1.y;tmp1.x=-1;
    tmp2.y=p2.y;tmp2.x=-1;
    if((canlinkdirectly(p1,tmp1)||p1.x==0)&&(canlinkdirectly(tmp2,p2)||p2.x==0)){
        qDebug()<<"p1x-- �߽�"<<"\n";
        tp1=tmp1;tp2=tmp2;
        return true;
    }
    //���������������øõ㣡
    qDebug()<<"failed!pp"<<"\n";
    tp2corner1.x=-3;tp2corner1.y=-3;
    tp1.x=tp1.y=tp2.x=tp2.y=-3;
    return false;
}
int* GameModel::getMap()//��ȡ��ͼ
{
    return gameMap;
}
bool GameModel::isblocked()//�ж��Ƿ��������
{//����һ�����������
    //�����ж�(i1,j1) (i2,j2)
    //���ж��Ƿ�Ϊͬһ��ͼƬ��Ȼ�󵱳�����һ��ͼƬ���Խ���������ʱ�򣬼���������ʱ������ֱ���˳�����
    //�������������֣���ô�����ڳ�ͼƬ��Ҫ�����жϣ��Ҳ���ֱ���˳�����
    Point p1,p2;
    if(isWin())//ʤ����������block���棡��
        return false;
    for(int i=0;i<MAX_col*MAX_row-1;i++)
        for(int j=i+1;j<MAX_col*MAX_row;j++)
        {
            p1.y=i%MAX_row;
            p1.x=i/MAX_row;
            p2.y=j%MAX_row;
            p2.x=j/MAX_row;
            //���жϸõ���û��ͼƬ��û����������
            if(!gameMap[p1.x*MAX_row+p1.y]||!gameMap[p2.x*MAX_row+p2.y])
                continue;
            //���ж��Ƿ�Ϊͬһ��ͼƬ ������������
            if(gameMap[p1.x*MAX_row+p1.y]!=gameMap[p2.x*MAX_row+p2.y])
                continue;
            //Ȼ������жϣ�
            if(canbelinked2(p1,p2))//����������ӣ�
                return false;
        }
    //ȫ���������������֣�
    return true;
}
bool GameModel::isWin()
{
    for(int i=0;i<MAX_row*MAX_col;i++)
    {
        if(gameMap[i])//��ͼһ��������ͼƬ����˵��û�����������
        {
            qDebug()<<"false"<<"\n";
            return false;
        }
    }
    //û��ͼƬ����ɣ�
    gamestatus=Win;
    return true;
}
void GameModel::block_rearrange()
{
    //����Ҫdelete��ԭ����map����Ϊ������Ὣgamemap��Ϊ0��
    do
    {
        //�Ƚ����������ţ�
        srand((unsigned)time(NULL));
        for(int i=0;i<MAX_col*MAX_row;i++)
        {
            int randomnum=rand()%(MAX_col*MAX_row);//�����������
            //��������i������randomnum���ߵ�gamemap(��ͼƬ��)����
            std::swap(gameMap[i],gameMap[randomnum]);
        }
    }while(isblocked());
}
void GameModel::setgamemap(int cur,int i)
{
    gameMap[i]=cur;
}
