#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),//�����棬ʵ����Ϸ�㷨��
    beforepic(NULL),afterpic(NULL)//������ͼƬָ�븳ֵΪ�գ��������ã���
{
    ui->setupUi(this);
    //��ȡ��Ļ�ֱ���!
    QDesktopWidget *desktop = QApplication::desktop();
    QRect screen = desktop->screenGeometry();
    screenWidth = screen.width();
    screenHeight = screen.height();
    //qDebug()<<screenHeight<<"  "<<screenWidth<<"\n";
    //������Ļ�ֱ�������趨ͼƬ��С�ʹ��ڴ�С������height�����䣡
    int winheight=767/((double)1080/screenHeight)+103;
    int winwidth=802/((double)1920/screenWidth)+78;
    iconsize=36/((double)1080/screenHeight);
    qDebug()<<iconsize<<"      "<<screenWidth<<"         "<<screenHeight<<"\n";
    //���ó�ʼ���ڴ�С��
    this->resize(QSize(winwidth,winheight));
    //���ñ���ͼƬ��
    this->setAutoFillBackground(true); // ���Ҫ����, ���������ʾ��������ͼ.
    QPalette palette;
    // ���ű���ͼ
    palette.setBrush(QPalette::Window,QBrush(QPixmap(":/images/background3.jpg").scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));// ʹ��ƽ�������ŷ�ʽ
    // ��widget���ϱ���ͼ!!
    this->setPalette(palette);
    //����eventfilter��װ����ǰwindow
    //ui->centralWidget->installEventFilter(this);
    //��connect�ѶȲ˵���
    mp_bar=new QMenuBar(this);
    GameMenu=new QMenu("Game");
    actionEasy=new QAction(QString::fromLocal8Bit("Easy"),this);
    actionNormal=new QAction(QString::fromLocal8Bit("Normal"),this);
    actionHard=new QAction(QString::fromLocal8Bit("Hard"),this);
    mp_bar->addMenu(GameMenu);
    GameMenu->addAction(actionEasy);
    GameMenu->addAction(actionNormal);
    GameMenu->addAction(actionHard);
    connect(actionEasy,SIGNAL(triggered(bool)),this,SLOT(selectdifficulty()));//�����ź�ʱ�Զ�����bool������
    connect(actionNormal,SIGNAL(triggered(bool)),this,SLOT(selectdifficulty()));
    connect(actionHard,SIGNAL(triggered(bool)),this,SLOT(selectdifficulty()));

    //�����������ڵ����ӣ�
    connect(Sounddlg,SIGNAL(changevolume(int)),this,SLOT(setplayervolume(int)));

    //�������ֲ��ŵ����ӣ�
    connect(Sounddlg,SIGNAL(playmusic()),this,SLOT(openmusicplayer()));
    connect(Sounddlg,SIGNAL(stopmusic()),this,SLOT(closemusicplayer()));
    connect(Sounddlg,SIGNAL(setplaying()),this,SLOT(setplaying()));
    connect(this,SIGNAL(setsounddlg()),Sounddlg,SLOT(setpause()));

    //չʾ������
    connect(this,SIGNAL(pleaseshowscore()),this,SLOT(showscore()));
    //Ȼ���ʼ����Ϸ
    StartGame(Easy);//�Զ�ΪEasy�Ѷȣ�
}

Widget::~Widget()
{
    if(gamemodel)
        delete gamemodel;
    delete ui;
}
void Widget::paintEvent(QPaintEvent *event)//�¼���д,���л��߲�������QWidget������paintevent����
{//ÿ��update()����������������
        //���ý��䲢����ŵ������ϣ�
    QPainter painter(this);
    QLinearGradient gradient(0,0,880,870);
    //������һ��QLinearGradient����ʵ��������Ϊ�����յ����꣬����Ϊ��ɫ����ķ���!!
    gradient.setColorAt(0.3,Qt::red);//0-0.3Ϊ��ɫ
    gradient.setColorAt(0.5,Qt::white);//0.3-0.5��ɫ��
    gradient.setColorAt(0.8,Qt::yellow);//0.5-0.8 yellow
    gradient.setColorAt(1.0,QColor(0,191,255));//0.8-1.0 ������ɫ��
    painter.setRenderHint(QPainter::Antialiasing, true);
    QBrush brush(gradient);
    QPen pen(brush,5);//QBrush������䣬QPen���ڻ��������� ��ɫΪ���� ���Ϊ5��Ҳ������setcolor��setwidth��
    painter.setPen(pen);
    //qDebug()<<"Widgetuser:"<<this->Login->username<<"\n";
    //��ʼ���ߣ�ע�⣺vector��QT�У���ʹ��vector<T>::size(),�ǵ�ǿ��ת�������������
    //qDebug()<<gamemodel->painting.size()<<"\n";
    for(int i=0;i<(int)(gamemodel->painting.size())-1;i++)
    {
        QPoint paintp1,paintp2;
        Point p1=gamemodel->painting[i],p2=gamemodel->painting[i+1];
        qDebug()<<"c"<<p1.x<<" "<<p1.y<<" "<<p2.x<<" "<<p2.y<<"d"<<"\n";
        //�ȵõ�Ҫ���ĵ���mainwindow������꣡
        paintp1=QPoint(marginleft+(p1.y+0.5)*iconsize,marginheight+(p1.x+0.5)*iconsize);
        paintp2=QPoint(marginleft+(p2.y+0.5)*iconsize,marginheight+(p2.x+0.5)*iconsize);
        //�����QPainter���ߣ�
        painter.drawLine(paintp1,paintp2);
    }
}
void Widget::closeEvent(QCloseEvent *e)//ֱ���˳���
{
    int r=QMessageBox::warning(this,QString::fromLocal8Bit("Gaming"),QString::fromLocal8Bit("ȷ��Ҫֱ���˳���"),QMessageBox::Ok|QMessageBox::Cancel);
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
void Widget::setgametimer()//��Ϸ���˵�ʱ��ʱ��ֹͣ���У�
{
    if(qtimer->isActive())
        qtimer->stop();
    else
        qtimer->start(1000);
}
void Widget::StartGame(GameDiffculty gamedif)//��ʼ����Ϸ
{
    //��ʼ��Ϸ
    gamemodel=new GameModel;//�ȷ����ڴ棡
    gamemodel->startGame(gamedif);

    //�԰�ťͼƬ���з��䣡  ���ԣ�ÿһ�鶼�����ڴ������ķ��䣬�ٶ�Ӧ��Ϸ��ͼ������Ƭ��Ϊ0���Զ����ز���ʾ�������ڴ��ҵ�ʱ����ӷ��㣡
    for(int i=0;i<MAX_row*MAX_col;i++)
    {
        imagebutton[i]=new picbutton(this);
        //���������Լ���С��
        imagebutton[i]->setGeometry(marginleft+i%MAX_row*iconsize,marginheight+i/MAX_row*iconsize,iconsize,iconsize);
        imagebutton[i]->picx=i/MAX_row;imagebutton[i]->picy=i%MAX_row;//�����ʼ����
        //����������/չʾͼƬ����ť
        if(gamemodel->getMap()[i])//���õ�ͼ������Ϊ0,���ͼƬ����ŷ���ȥ��
        {
            QPixmap picmap;
            QString picpath;
            picpath.sprintf(":/Desktop/%d.png",gamemodel->getMap()[i]);//����sprintf��QStringʵ��ͼƬ������ȡ��
            picmap.load(picpath);//��ȡͼƬ��
            QIcon pic(picmap);//��pixmap���ؽ�QIcon!
            imagebutton[i]->setIcon(pic);
            imagebutton[i]->setIconSize(QSize(iconsize,iconsize));
            //ͼƬ������ɺ󣬿�ʼconnect��ť����Ӧ�ۺ�����

            imagebutton[i]->show();//���Ǹ��л��Ѷȵĺ������Ż���

            connect(imagebutton[i],SIGNAL(pressed()),this,SLOT(on_picbutton_clicked()));
        }
        else
        {
            imagebutton[i]->hide();//���Ϊ0��������Ӧ�ۺ��������������أ�
        }
    }

    //������+ʱ��
    qtimer=new QTimer;
    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(100);//���ý������ĳ�ʼֵ�Լ���Χ!


    //�����л�����!
    tim=300;

    //�Ѷȱ�ǩ�л���
    if(gamedif==Easy)
    ui->label_3->setText("Easy");
    else if(gamedif==Normal)
        ui->label_3->setText("Normal");
    else if(gamedif==Hard)
        ui->label_3->setText("Hard");

    ui->lcdNumber->setDigitCount(4);
    ui->lcdNumber->setDecMode();//����ʮ������ʾ�Լ���λ
    connect(qtimer,SIGNAL(timeout()),this,SLOT(time_withprogressbar()));
    qtimer->start(1000);//��ʼ��ʱ��ÿ��1s��ִ��һ�βۺ�������

    //����״̬��ʼ����
    islinking=false;

    //����bgm!
    musicplayer=new QMediaPlayer(this);

    //�����Ǹ�ͼ�����ϵͳ��ȡһ���İ취..�ҷ���QT����������·��...���Ƕ��ǲ��õľ���·����
    musicplayer->setMedia(QUrl::fromLocalFile("./sound/bgm.mp3"));
    musicplayer->setVolume(50);
}
void Widget::on_picbutton_clicked()//ͼƬ����¼�
{
     if(islinking)//�������Ӳ����ߣ���ʱ��ť��Ϊ����ѡ�У����ʱ��ЧΪ�����Ч����
    {
        QSound::play(":/sound/release.wav");//QSound::play����url��Դ�ļ�·�����ɣ��ǵü�˫���ţ���
        //���������󷵻أ�
        return;
    }

    //�ҳ���ǰѡ�еİ�ť�������õ���QObject::sender()���ط����źŵĶ��󣬼ǵ�ʹ��dynamic_cast����ת��Ϊpicbutton�࣡��
    afterpic=dynamic_cast<picbutton *>(sender());//�ҵ���Ӧ��imagebutton[i]��ͨ��afterpic������Ϣ��
    //�������ۣ�
    if(!beforepic)//��������һ����ť���������Ϊ�����һ��ͼƬ��
    {
        qDebug()<<"first"<<"\n";
        QSound::play(":/sound/select.wav");
        //����ѡ����ʽ���Ե�ǰ��ť������ʽ����
        afterpic->setStyleSheet(selectstyle);
        beforepic=afterpic;//�ѵ�ǰ��ť�ĵ�ַ�������ϸ���ť����ʹ�ã���
    }
    else//��һ����ť�Ѿ�����ֵ��
    {
        //ͬһ����ť
        if(beforepic==afterpic)
        {
            qDebug()<<"same"<<"\n";
            QSound::play(":/sound/release.wav");
            beforepic->setStyleSheet(releasestyle);
            beforepic=afterpic=NULL;
        }
        //��ͬ��ť�������Ƿ��ܹ�����
        else
        {
            qDebug()<<"judge"<<"\n";
            //������ʽ��
            afterpic->setStyleSheet(selectstyle);
            //�Ȼ�ȡ����-_-||
            Point bef,aft;
            bef.x=beforepic->picx;bef.y=beforepic->picy;
            aft.x=afterpic->picx;aft.y=afterpic->picy;
            gamemodel->painting.clear();//�����������!
            //�ж��Ƿ��ܹ����ӣ�
            if(gamemodel->canbelinked(bef,aft))//����ܹ����ӣ�
            {
                //������״̬����������״̬����
                islinking=true;
                //���֣�
                QSound::play(":/sound/linksuccessfully.wav");

                //�����0..
                gamemodel->setgamemap(0,beforepic->picx*MAX_row+beforepic->picy);
                gamemodel->setgamemap(0,afterpic->picx*MAX_row+afterpic->picy);
                qDebug()<<gamemodel->painting[0].x<<" "<<gamemodel->painting[1].x<<"\n";

                //����ȷ��������2�룡
                tim+=2;
                if(tim>300)
                    tim=300;
                //���ӷ�����
                emit pleaseshowscore();
                qDebug()<<gamemodel->grades<<"\n";
                //����!
                update();
                //ʱ���ӳ٣�
                QTimer::singleShot(delaydraw,this,SLOT(linkeffect()));//�ӳ�0.6s������ʾ��
                //�ж��Ƿ�������֣����ǣ����������У�
                if(gamemodel->isblocked())//bug��������֣���Ϊisblocked������canbelinked,�����vector�Ļ��ң���
                {
                    //��������!
                    qDebug()<<"block!"<<"\n";
                    gamemodel->block_rearrange();
                    block_repaint();
                }
                if(gamemodel->isWin())
                {
                    //ʤ����Ч��
                    QSound::play(":/sound/youwin.wav");

                    //ֹͣ��ʱ��
                    qtimer->stop();
                    //�Ի���
                    int r=QMessageBox::warning(this,QString::fromLocal8Bit("��Ϸ����"),QString::fromLocal8Bit("��Ӯ�ˣ�"),QMessageBox::Ok);

                    //�ȼ�¼�ɼ�����txt��
                    if(strcmp(Login->username,"Not login")!=0)//˵���Ѿ���½��
                    {
                        //
                        //gamemodel->grades=20;//���ԣ�
                        //
                        gamemodel->grades+=tim*5;//ʱ�佱������!
                        qDebug()<<"WIN mode:"<<Login->userscore<<"   "<<gamemodel->grades<<"\n";
                        if(Login->userscore<gamemodel->grades)//����������С���򸲸ǣ�
                        {
                            qDebug()<<gamemodel->grades<<"\n";
                            Login->userscore=gamemodel->grades;
                            Login->print();//��ӡ��txt!
                        }
                    }
                    //Ȼ�󷵻ز˵���
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
void Widget::block_repaint()//���»�ͼ��
{
    //��delete��ԭ����ͼ��button!
    for(int i=0;i<MAX_col*MAX_row;i++)
        if(imagebutton[i])
        delete imagebutton[i];
    gamemodel->painting.clear();
    //�ػ棡
    for(int i=0;i<MAX_row*MAX_col;i++)
    {
        imagebutton[i]=new picbutton(this);
        //���������Լ���С��
        imagebutton[i]->setGeometry(marginleft+i%MAX_row*iconsize,marginheight+i/MAX_row*iconsize,iconsize,iconsize);
        imagebutton[i]->picx=i/MAX_row;imagebutton[i]->picy=i%MAX_row;//�����ʼ����
        //����������/չʾͼƬ����ť
        if(gamemodel->getMap()[i])//���õ�ͼ������Ϊ0,���ͼƬ����ŷ���ȥ��
        {
            QPixmap picmap;
            QString picpath;
            picpath.sprintf(":/Desktop/%d.png",gamemodel->getMap()[i]);//����sprintf��QStringʵ��ͼƬ������ȡ��
            picmap.load(picpath);//��ȡͼƬ��
            QIcon pic(picmap);//��pixmap���ؽ�QIcon!
            imagebutton[i]->setIcon(pic);
            imagebutton[i]->setIconSize(QSize(iconsize,iconsize));
            //ͼƬ������ɺ󣬿�ʼconnect��ť����Ӧ�ۺ�����
            connect(imagebutton[i],SIGNAL(pressed()),this,SLOT(on_picbutton_clicked()));
        }
        else
        {
            imagebutton[i]->hide();//���Ϊ0��������Ӧ�ۺ��������������أ�
        }
    }
}
void Widget::time_withprogressbar()//��ʱ������
{
    tim--;
    int tim2=tim/3;
    if(tim==0)
    {
        qtimer->stop();
        //�ж�Ϊ�䣡
        QSound::play(":/sound/youlose.wav");
        int r=QMessageBox::warning(this,QString::fromLocal8Bit("��Ϸ����"),QString::fromLocal8Bit("�����ˣ�"),QMessageBox::Ok);
        gamemodel->setgamestatus(Lose);//�ж�Ϊ�䣡
        //���������棡
        if(r==QMessageBox::Ok)
        emit returntomenu();//���ͷ����źţ�
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
void Widget::linkeffect()//����Ч��
{
    gamemodel->painting.clear();//�����������!
    //ÿ����һ�ξ����һ��!
    //qDebug()<<beforepic->picx*MAX_row+beforepic->picy<<"\n";
    //qDebug()<<afterpic->picx*MAX_row+afterpic->picy<<"\n";

    //���ذ�ť��
    afterpic->hide();
    beforepic->hide();

    //������ʧ
    update();

    //ָ���ÿ�
    afterpic=beforepic=NULL;

    //�������
    islinking=false;
}
void Widget::selectdifficulty()//�趨�Ѷ�
{
    //�Ȱ�֮ǰ��ģ�ͺ�ͼƬ��ťȫ�������
    if(gamemodel)
    {
        delete gamemodel;
        for(int i=0;i<MAX_col*MAX_row;i++)
            if(imagebutton[i])
                delete imagebutton[i];
    }
    //���qtimer,ͬʱʱ��ع飡
    delete qtimer;
    tim=180;
    //ͣ�����֣�-----ͨ����sounddlg����������ͣ�źţ�ʹ��sounddlg�еİ�ť��ʽ���������״̬���Ӷ�����bug����

    emit setsounddlg();

    //�ػ�!
    update();

    //�Ʒ������㣡
    ui->lcdNumber_2->display(0);

    //���Ǳ�����֪���û������ĸ��Ѷȶ�Ӧaction��ť��ֻ���ҳ����ĸ���ť����triggered�źż��ɣ�
    //ʹ��sender()�ҳ��ź�Դ��
    QAction *chosen=(QAction *)dynamic_cast<QAction *>(sender());
    if(chosen==actionEasy)//�ź�Դ��Ӧeasy!
        StartGame(Easy);
    else if(chosen==actionNormal){
        qDebug()<<"normal"<<"\n";
        StartGame(Normal);
    }
    else if(chosen==actionHard)
        StartGame(Hard);
}

void Widget::on_pushButton_toggled(bool checked)//��ʼ/��ͣ��ť��
{
    if(checked)//ѡ�У�
    {
        ui->pushButton->setText("pause");
        //������Ϸ״̬Ϊ��ͣ
        qtimer->stop();
        gamemodel->setgamestatus(Pause);
        //���÷�������
        for(int i=0;i<MAX_row*MAX_col;i++)
            imagebutton[i]->hide();
    }
    else
    {
        ui->pushButton->setText("playing");
        //������ϷΪ��ʼ
        qtimer->start(1000);
        gamemodel->setgamestatus(Playing);
        //���÷������!
        for(int i=0;i<MAX_row*MAX_col;i++)
            if(gamemodel->getMap()[i])
                imagebutton[i]->show();
    }
}

void Widget::on_pushButton_3_clicked()//�������˵���
{
    int r=QMessageBox::warning(this,QString::fromLocal8Bit("Gaming"),QString::fromLocal8Bit("ȷ��Ҫ�˻����˵���?"),QMessageBox::Yes|QMessageBox::No);
    if(r==QMessageBox::Yes){
        emit returntomenu();
    }

}
void Widget::on_pushButton_2_clicked()//����������������һ���´��ں�slider���������ĸı䣡
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
