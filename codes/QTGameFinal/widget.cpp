#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),//主界面，实现游戏算法！
    beforepic(NULL),afterpic(NULL)//将两个图片指针赋值为空，后面有用！！
{
    ui->setupUi(this);
    //获取屏幕分辨率!
    QDesktopWidget *desktop = QApplication::desktop();
    QRect screen = desktop->screenGeometry();
    screenWidth = screen.width();
    screenHeight = screen.height();
    //qDebug()<<screenHeight<<"  "<<screenWidth<<"\n";
    //根据屏幕分辨率灵活设定图片大小和窗口大小！根据height来调配！
    int winheight=767/((double)1080/screenHeight)+103;
    int winwidth=802/((double)1920/screenWidth)+78;
    iconsize=36/((double)1080/screenHeight);
    qDebug()<<iconsize<<"      "<<screenWidth<<"         "<<screenHeight<<"\n";
    //设置初始窗口大小！
    this->resize(QSize(winwidth,winheight));
    //设置背景图片！
    this->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette;
    // 缩放背景图
    palette.setBrush(QPalette::Window,QBrush(QPixmap(":/images/background3.jpg").scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));// 使用平滑的缩放方式
    // 给widget加上背景图!!
    this->setPalette(palette);
    //重载eventfilter安装到当前window
    //ui->centralWidget->installEventFilter(this);
    //先connect难度菜单！
    mp_bar=new QMenuBar(this);
    GameMenu=new QMenu("Game");
    actionEasy=new QAction(QString::fromLocal8Bit("Easy"),this);
    actionNormal=new QAction(QString::fromLocal8Bit("Normal"),this);
    actionHard=new QAction(QString::fromLocal8Bit("Hard"),this);
    mp_bar->addMenu(GameMenu);
    GameMenu->addAction(actionEasy);
    GameMenu->addAction(actionNormal);
    GameMenu->addAction(actionHard);
    connect(actionEasy,SIGNAL(triggered(bool)),this,SLOT(selectdifficulty()));//传入信号时自动忽略bool参数！
    connect(actionNormal,SIGNAL(triggered(bool)),this,SLOT(selectdifficulty()));
    connect(actionHard,SIGNAL(triggered(bool)),this,SLOT(selectdifficulty()));

    //进行音量调节的链接！
    connect(Sounddlg,SIGNAL(changevolume(int)),this,SLOT(setplayervolume(int)));

    //进行音乐播放的链接！
    connect(Sounddlg,SIGNAL(playmusic()),this,SLOT(openmusicplayer()));
    connect(Sounddlg,SIGNAL(stopmusic()),this,SLOT(closemusicplayer()));
    connect(Sounddlg,SIGNAL(setplaying()),this,SLOT(setplaying()));
    connect(this,SIGNAL(setsounddlg()),Sounddlg,SLOT(setpause()));

    //展示分数！
    connect(this,SIGNAL(pleaseshowscore()),this,SLOT(showscore()));
    //然后初始化游戏
    StartGame(Easy);//自动为Easy难度！
}

Widget::~Widget()
{
    if(gamemodel)
        delete gamemodel;
    delete ui;
}
void Widget::paintEvent(QPaintEvent *event)//事件重写,进行画线操作！！QWidget才能用paintevent！！
{//每次update()都会调用这个函数！
        //设置渐变并将其放到画笔上！
    QPainter painter(this);
    QLinearGradient gradient(0,0,880,870);
    //创建了一个QLinearGradient对象实例，参数为起点和终点坐标，可作为颜色渐变的方向!!
    gradient.setColorAt(0.3,Qt::red);//0-0.3为红色
    gradient.setColorAt(0.5,Qt::white);//0.3-0.5白色！
    gradient.setColorAt(0.8,Qt::yellow);//0.5-0.8 yellow
    gradient.setColorAt(1.0,QColor(0,191,255));//0.8-1.0 深天蓝色！
    painter.setRenderHint(QPainter::Antialiasing, true);
    QBrush brush(gradient);
    QPen pen(brush,5);//QBrush用于填充，QPen用于绘制轮廓线 颜色为渐变 宽度为5！也可以用setcolor和setwidth！
    painter.setPen(pen);
    //qDebug()<<"Widgetuser:"<<this->Login->username<<"\n";
    //开始画线！注意：vector在QT中，若使用vector<T>::size(),记得强制转换，否则溢出！
    //qDebug()<<gamemodel->painting.size()<<"\n";
    for(int i=0;i<(int)(gamemodel->painting.size())-1;i++)
    {
        QPoint paintp1,paintp2;
        Point p1=gamemodel->painting[i],p2=gamemodel->painting[i+1];
        qDebug()<<"c"<<p1.x<<" "<<p1.y<<" "<<p2.x<<" "<<p2.y<<"d"<<"\n";
        //先得到要画的点在mainwindow里的坐标！
        paintp1=QPoint(marginleft+(p1.y+0.5)*iconsize,marginheight+(p1.x+0.5)*iconsize);
        paintp2=QPoint(marginleft+(p2.y+0.5)*iconsize,marginheight+(p2.x+0.5)*iconsize);
        //最后用QPainter画线！
        painter.drawLine(paintp1,paintp2);
    }
}
void Widget::closeEvent(QCloseEvent *e)//直接退出！
{
    int r=QMessageBox::warning(this,QString::fromLocal8Bit("Gaming"),QString::fromLocal8Bit("确定要直接退出吗？"),QMessageBox::Ok|QMessageBox::Cancel);
    if(r==QMessageBox::Ok){
        QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
        animation->setDuration(1000);
        animation->setStartValue(1);
        animation->setEndValue(0);
        animation->start();
       emit exitdirectly();
    }

    if(r==QMessageBox::Cancel)
        e->ignore();
}
void Widget::setgametimer()//游戏主菜单时计时器停止运行！
{
    if(qtimer->isActive())
        qtimer->stop();
    else
        qtimer->start(1000);
}
void Widget::StartGame(GameDiffculty gamedif)//初始化游戏
{
    //开始游戏
    gamemodel=new GameModel;//先分配内存！
    gamemodel->startGame(gamedif);

    //对按钮图片进行分配！  策略：每一块都进行内存和坐标的分配，再对应游戏地图分配照片，为0的自动隐藏不显示，这样在打乱的时候更加方便！
    for(int i=0;i<MAX_row*MAX_col;i++)
    {
        imagebutton[i]=new picbutton(this);
        //设置坐标以及大小！
        imagebutton[i]->setGeometry(marginleft+i%MAX_row*iconsize,marginheight+i/MAX_row*iconsize,iconsize,iconsize);
        imagebutton[i]->picx=i/MAX_row;imagebutton[i]->picy=i%MAX_row;//坐标初始化！
        //接下来隐藏/展示图片给按钮
        if(gamemodel->getMap()[i])//调用地图，若不为0,则把图片按序号放上去！
        {
            QPixmap picmap;
            QString picpath;
            picpath.sprintf(":/Desktop/%d.png",gamemodel->getMap()[i]);//利用sprintf和QString实现图片的灵活读取！
            picmap.load(picpath);//读取图片！
            QIcon pic(picmap);//把pixmap加载进QIcon!
            imagebutton[i]->setIcon(pic);
            imagebutton[i]->setIconSize(QSize(iconsize,iconsize));
            //图片设置完成后，开始connect按钮与响应槽函数！

            imagebutton[i]->show();//这是给切换难度的函数的优化！

            connect(imagebutton[i],SIGNAL(pressed()),this,SLOT(on_picbutton_clicked()));
        }
        else
        {
            imagebutton[i]->hide();//如果为0则不设置响应槽函数，并设置隐藏！
        }
    }

    //进度条+时间
    qtimer=new QTimer;
    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(100);//设置进度条的初始值以及范围!


    //窗口切换测试!
    tim=300;

    //难度标签切换！
    if(gamedif==Easy)
    ui->label_3->setText("Easy");
    else if(gamedif==Normal)
        ui->label_3->setText("Normal");
    else if(gamedif==Hard)
        ui->label_3->setText("Hard");

    ui->lcdNumber->setDigitCount(4);
    ui->lcdNumber->setDecMode();//设置十进制显示以及数位
    connect(qtimer,SIGNAL(timeout()),this,SLOT(time_withprogressbar()));
    qtimer->start(1000);//开始计时，每过1s就执行一次槽函数！！

    //链接状态初始化！
    islinking=false;

    //播放bgm!
    musicplayer=new QMediaPlayer(this);

    //跟我那个图书管理系统采取一样的办法..我发现QT里好难用相对路径...于是都是采用的绝对路径！
    musicplayer->setMedia(QUrl::fromLocalFile("./sound/bgm.mp3"));
    musicplayer->setVolume(50);
}
void Widget::on_picbutton_clicked()//图片点击事件
{
     if(islinking)//正在链接并画线，此时按钮变为不可选中，点击时音效为解除音效！！
    {
        QSound::play(":/sound/release.wav");//QSound::play采用url资源文件路径即可！记得加双引号！！
        //播放声音后返回！
        return;
    }

    //找出当前选中的按钮，这里用到了QObject::sender()返回发送信号的对象，记得使用dynamic_cast将其转换为picbutton类！！
    afterpic=dynamic_cast<picbutton *>(sender());//找到对应的imagebutton[i]并通过afterpic储存信息！
    //分类讨论！
    if(!beforepic)//不存在上一个按钮，可以理解为点击第一个图片！
    {
        qDebug()<<"first"<<"\n";
        QSound::play(":/sound/select.wav");
        //增加选中样式！对当前按钮设置样式！！
        afterpic->setStyleSheet(selectstyle);
        beforepic=afterpic;//把当前按钮的地址传给“上个按钮”来使用！！
    }
    else//上一个按钮已经被赋值！
    {
        //同一个按钮
        if(beforepic==afterpic)
        {
            qDebug()<<"same"<<"\n";
            QSound::play(":/sound/release.wav");
            beforepic->setStyleSheet(releasestyle);
            beforepic=afterpic=NULL;
        }
        //不同按钮！尝试是否能够消除
        else
        {
            qDebug()<<"judge"<<"\n";
            //设置样式！
            afterpic->setStyleSheet(selectstyle);
            //先获取坐标-_-||
            Point bef,aft;
            bef.x=beforepic->picx;bef.y=beforepic->picy;
            aft.x=afterpic->picx;aft.y=afterpic->picy;
            gamemodel->painting.clear();//画线数组清除!
            //判定是否能够链接！
            if(gamemodel->canbelinked(bef,aft))//如果能够链接！
            {
                //先锁定状态！处于连接状态！！
                islinking=true;
                //音乐！
                QSound::play(":/sound/linksuccessfully.wav");

                //数组归0..
                gamemodel->setgamemap(0,beforepic->picx*MAX_row+beforepic->picy);
                gamemodel->setgamemap(0,afterpic->picx*MAX_row+afterpic->picy);
                qDebug()<<gamemodel->painting[0].x<<" "<<gamemodel->painting[1].x<<"\n";

                //若正确消除则续2秒！
                tim+=2;
                if(tim>300)
                    tim=300;
                //增加分数！
                emit pleaseshowscore();
                qDebug()<<gamemodel->grades<<"\n";
                //画线!
                update();
                //时间延迟！
                QTimer::singleShot(delaydraw,this,SLOT(linkeffect()));//延迟0.6s让线显示！
                //判断是否进入死局，若是，则重新排列！
                if(gamemodel->isblocked())//bug在这里出现，因为isblocked调用了canbelinked,造成了vector的混乱！！
                {
                    //进行重排!
                    qDebug()<<"block!"<<"\n";
                    gamemodel->block_rearrange();
                    block_repaint();
                }
                if(gamemodel->isWin())
                {
                    //胜利音效！
                    QSound::play(":/sound/youwin.wav");

                    //停止计时！
                    qtimer->stop();
                    //对话框！
                    int r=QMessageBox::warning(this,QString::fromLocal8Bit("游戏提醒"),QString::fromLocal8Bit("你赢了！"),QMessageBox::Ok);

                    //先记录成绩进入txt！
                    if(strcmp(Login->username,"Not login")!=0)//说明已经登陆！
                    {
                        //
                        //gamemodel->grades=20;//测试！
                        //
                        gamemodel->grades+=tim*5;//时间奖励结算!
                        qDebug()<<"WIN mode:"<<Login->userscore<<"   "<<gamemodel->grades<<"\n";
                        if(Login->userscore<gamemodel->grades)//分数比现在小，则覆盖！
                        {
                            qDebug()<<gamemodel->grades<<"\n";
                            Login->userscore=gamemodel->grades;
                            Login->print();//打印进txt!
                        }
                    }
                    //然后返回菜单！
                    if(r==QMessageBox::Ok)
                        emit returntomenu();
                }
            }
            else{
                qDebug()<<"failed"<<"\n";
                QSound::play(":/sound/fail.wav");
                beforepic->setStyleSheet(releasestyle);
                afterpic->setStyleSheet(releasestyle);
                beforepic=afterpic=NULL;
            }
        }
    }
}
void Widget::block_repaint()//重新绘图！
{
    //先delete掉原来的图像button!
    for(int i=0;i<MAX_col*MAX_row;i++)
        if(imagebutton[i])
        delete imagebutton[i];
    gamemodel->painting.clear();
    //重绘！
    for(int i=0;i<MAX_row*MAX_col;i++)
    {
        imagebutton[i]=new picbutton(this);
        //设置坐标以及大小！
        imagebutton[i]->setGeometry(marginleft+i%MAX_row*iconsize,marginheight+i/MAX_row*iconsize,iconsize,iconsize);
        imagebutton[i]->picx=i/MAX_row;imagebutton[i]->picy=i%MAX_row;//坐标初始化！
        //接下来隐藏/展示图片给按钮
        if(gamemodel->getMap()[i])//调用地图，若不为0,则把图片按序号放上去！
        {
            QPixmap picmap;
            QString picpath;
            picpath.sprintf(":/Desktop/%d.png",gamemodel->getMap()[i]);//利用sprintf和QString实现图片的灵活读取！
            picmap.load(picpath);//读取图片！
            QIcon pic(picmap);//把pixmap加载进QIcon!
            imagebutton[i]->setIcon(pic);
            imagebutton[i]->setIconSize(QSize(iconsize,iconsize));
            //图片设置完成后，开始connect按钮与响应槽函数！
            connect(imagebutton[i],SIGNAL(pressed()),this,SLOT(on_picbutton_clicked()));
        }
        else
        {
            imagebutton[i]->hide();//如果为0则不设置响应槽函数，并设置隐藏！
        }
    }
}
void Widget::time_withprogressbar()//计时器联动
{
    tim--;
    int tim2=tim/3;
    if(tim==0)
    {
        qtimer->stop();
        //判定为输！
        QSound::play(":/sound/youlose.wav");
        int r=QMessageBox::warning(this,QString::fromLocal8Bit("游戏提醒"),QString::fromLocal8Bit("你输了！"),QMessageBox::Ok);
        gamemodel->setgamestatus(Lose);//判定为输！
        //返回主界面！
        if(r==QMessageBox::Ok)
        emit returntomenu();//发送返回信号！
    }
    if(tim2>=30&&tim2<=60)
        ui->progressBar->setStyleSheet("QProgressBar#progressBar:chunk\
        {\
        background-color:yellow;\
        }");
     if(tim2>=0&&tim2<30)
        ui->progressBar->setStyleSheet("QProgressBar#progressBar:chunk\
        {\
        background-color:purple;\
        }");
      ui->progressBar->setValue(tim2);
      ui->lcdNumber->display(tim);
}
void Widget::linkeffect()//链接效果
{
    gamemodel->painting.clear();//画线数组清除!
    //每链接一次就清除一次!
    //qDebug()<<beforepic->picx*MAX_row+beforepic->picy<<"\n";
    //qDebug()<<afterpic->picx*MAX_row+afterpic->picy<<"\n";

    //隐藏按钮！
    afterpic->hide();
    beforepic->hide();

    //让线消失
    update();

    //指针置空
    afterpic=beforepic=NULL;

    //解除锁定
    islinking=false;
}
void Widget::selectdifficulty()//设定难度
{
    //先把之前的模型和图片按钮全部清除！
    if(gamemodel)
    {
        delete gamemodel;
        for(int i=0;i<MAX_col*MAX_row;i++)
            if(imagebutton[i])
                delete imagebutton[i];
    }
    //清除qtimer,同时时间回归！
    delete qtimer;
    tim=180;
    //停掉音乐！-----通过向sounddlg发送设置暂停信号，使得sounddlg中的按钮样式变更并更改状态，从而消除bug！！

    emit setsounddlg();

    //重绘!
    update();

    //计分器归零！
    ui->lcdNumber_2->display(0);

    //我们必须先知道用户按了哪个难度对应action按钮！只需找出是哪个按钮发送triggered信号即可！
    //使用sender()找出信号源！
    QAction *chosen=(QAction *)dynamic_cast<QAction *>(sender());
    if(chosen==actionEasy)//信号源对应easy!
        StartGame(Easy);
    else if(chosen==actionNormal){
        qDebug()<<"normal"<<"\n";
        StartGame(Normal);
    }
    else if(chosen==actionHard)
        StartGame(Hard);
}

void Widget::on_pushButton_toggled(bool checked)//开始/暂停按钮！
{
    if(checked)//选中！
    {
        ui->pushButton->setText("pause");
        //设置游戏状态为暂停
        qtimer->stop();
        gamemodel->setgamestatus(Pause);
        //设置方块隐藏
        for(int i=0;i<MAX_row*MAX_col;i++)
            imagebutton[i]->hide();
    }
    else
    {
        ui->pushButton->setText("playing");
        //设置游戏为开始
        qtimer->start(1000);
        gamemodel->setgamestatus(Playing);
        //设置方块出现!
        for(int i=0;i<MAX_row*MAX_col;i++)
            if(gamemodel->getMap()[i])
                imagebutton[i]->show();
    }
}

void Widget::on_pushButton_3_clicked()//返回主菜单！
{
    int r=QMessageBox::warning(this,QString::fromLocal8Bit("Gaming"),QString::fromLocal8Bit("确定要退回主菜单吗?"),QMessageBox::Yes|QMessageBox::No);
    if(r==QMessageBox::Yes){
        emit returntomenu();
    }

}
void Widget::on_pushButton_2_clicked()//调节音量！！采用一个新窗口和slider进行音量的改变！
{
    ui->pushButton->setChecked(true);
    Sounddlg->exec();
}
void Widget::setplayervolume(int i)
{
    musicplayer->setVolume(i);
}
void Widget::openmusicplayer()
{
    musicplayer->play();
}
void Widget::closemusicplayer()
{
    musicplayer->pause();
}
void Widget::setplaying()
{
    ui->pushButton->setChecked(false);
}
void Widget::showscore()
{
    ui->lcdNumber_2->display(gamemodel->grades);
}
