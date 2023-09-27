#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QPalette>
#include <QFrame>
#include "math.h"
#include <QDebug>
#include <QEvent>
#include <QObject>
#include <QPalette>
#include <QFont>
#include <QMessageBox>
#include <QProcess>
#include <QGroupBox>
#include "gamecontrol.h"
//using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
  //  this->setFixedSize(this->width(),this->height());
    ui->newGameBox->setVisible(false);
  //  ui->Info->setVisible(false);
    ui->nishiobox->setVisible(false);
    ui->choice->setVisible(false);
   /*
    *  set true for testing
    */
     ui->solve->setVisible(false);

}

//#########################################################
/*
 *
 *    #### part 1, basic setup of game functioning ###
 */

//###############  construct grids/number keys/value update handling ###########


/*
 *   construct sudoku grid
 */
void MainWindow::StartGrid(int qsize)
{

     game.startpuzzle(qsize);




    int bsize = sqrt(qsize);
    int cell_size = 28;
    if(qsize==16 && gamemode != heuri){

        cell_size = 26;
        ui->menubox->setGeometry(30,10,570,78);
        ui->Board->setGeometry(30,95,521,420);
        ui->Info->setGeometry(600,100,110,481);
        ui->controlpanel->setGeometry(715,10,205,590);
        ui->Info->raise();
     }

    if(qsize == 9){
        cell_size = 45;
       //  ui->menubox->setGeometry(70,70,161,171);
        if(gamemode!=heuri){
            ui->Board->setGeometry(50,130,171,181);

        }
        else ui->Board->setGeometry(90,137,171,181);


    }
    if(gamemode!=heuri){
      cell_size-=8;
      if(qsize == 9) cell_size-=8;
    }


    QGridLayout *layout = new QGridLayout;
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setSpacing(0);

    for(int i=0; i<qsize ; i++){
          int upper = 0;

          if(qsize == 9) upper = 10;
          else upper = 16;
          int indent = game.randnum(0,upper);

        for(int j=0; j<qsize; j++){
            QPushButton *pb;
            pb = new QPushButton;
           //0 refers to the space
           if(*(game.puzzle+i*qsize+j) !=0){
             pb->setText(QString::number(*(game.puzzle+i*qsize+j)));
             pb->setAccessibleName("clues");
           }
           else{
             pb->setText(" ");
             connect(pb,SIGNAL(clicked()),this,SLOT(gridClicked()));
            }

            pb->setFixedSize(cell_size,cell_size);
            pb->setObjectName(QString::number(i*qsize+j+1));


         if(gamemode == heuri){
             GridLine(bsize,i,j,pb);
               layout->addWidget(pb,i,j);
         }
          else{
             QLabel *ql = new QLabel(QString::number(i*qsize+j+1));
             ql->setAlignment(Qt::AlignCenter);
             ql->setStyleSheet("color:#ffd480;\n font-size:9px\n");

             if(gamemode == jigsaw) indent = game.randnum(0,upper-1);
             layout->addWidget(ql,i*2,j+indent);
             layout->addWidget(pb,i*2+1,j+indent);

         }

        }
      //  QLabel *ql2 = new QLabel("   ");

    }

    ui->Board->setStyleSheet("QPushButton{border: 1px solid #ffb380;\n} QPushButton:hover{background:#cccccc;\n} QPushButton:pressed{background:#4dc3ff};\n");
    ui->Board->setLayout(layout);
}

/*
 *   add grid lines
 */
void MainWindow::GridLine(int bsize,int i, int j, QPushButton *a)
{
    QString top = "border-top: 3px solid #1ac6ff;\n";
    QString left = "border-left: 3px solid #1ac6ff;\n";
    QString bottom1 = "border-bottom: 1px solid #ffb380;\n";
    QString bottom2 = "border-bottom: 3px solid #1ac6ff;\n";
    QString right1 = "border-right:1px solid #ffb380\n";
    QString right2= "border-right: 3px solid #1ac6ff;\n";


//    qDebug() <<  "name: " << a->objectName();

    if(i ==0) {
         if(j==0)  a->setStyleSheet(top + left +bottom1+right1);
         else if((j+1)%bsize==0) a->setStyleSheet(top+right2+bottom1);
         else
             a->setStyleSheet(top+bottom1+right1);
     }

    else if((i+1)%bsize == 0  ){

          if(j == 0) a->setStyleSheet(bottom2+left+right1);
          else if((j+1)%bsize ==0)
             a->setStyleSheet(right2+bottom2);
          else
             a->setStyleSheet(bottom2+right1);
     }else{


          if(j == 0) a->setStyleSheet(bottom1+left+right1);
          else if((j+1)%bsize ==0)
              a->setStyleSheet(bottom1+right2);
          else
              a->setStyleSheet(bottom1+right1);

     }

}

void MainWindow::gridClicked()
{
    QObject *b = QObject::sender();
  //  qDebug() << b->objectName();
    QString q = b->objectName();
    selectedCell = q;


   QPushButton *pb = ui->Board->findChild<QPushButton*>(selectedCell);
    QFont f("Courier",13,QFont::Bold,true);
    toggleFont(pb,f,true);

    selectedText = pb->text();



}


/*
 *  construct number grid
 */

void MainWindow::NumberGrid(int qsize)
{

    QGridLayout *layout = new QGridLayout;
    layout->setSizeConstraint(QLayout::SetFixedSize);
    int cell_size = 30;
    layout->setSpacing(6);

    if(qsize == 9){
     layout->setSpacing(12);
     cell_size = 36;
    }

    int nsize = sqrt(qsize);
   QPalette pl;
    for(int i = 0; i< nsize; i++){
        for(int j=0; j<nsize; j++){
               QPushButton *b;
               b = new QPushButton;
               b->setText(QString::number(i*nsize+j+1));

               pl.setColor(b->foregroundRole(),Qt::green);
               b->setPalette(pl);

               b->setObjectName(QString::number(i*nsize+j+1));
               connect(b,SIGNAL(clicked()),this,SLOT(numberGridClicked()));
              // qDebug() <<  "name: " << b->objectName();
               b->setFixedSize(cell_size,cell_size);
               layout->addWidget(b,i,j);
        }
    }

    ui->numberbox->setLayout(layout);

    ui->numberbox->setStyleSheet("QPushButton{background:#e0ebeb;border:1px solid #ff8000; border-radius:10px;color:#3399ff;\n}"
                                 " QPushButton:hover{background:#ffb366;\n} QPushButton:pressed{background:#ff751a;\n}");

}


/*
 *  handling of update value
 */
void MainWindow::numberGridClicked()
{
    QObject *b = QObject::sender();
    qDebug() << b->objectName();
    QString num = b->objectName();
     QPushButton *pb = ui->Board->findChild<QPushButton*>(selectedCell);



   bool gridupdated =  game.updategrid(selectedCell.toInt(),num.toInt());

   if(gridupdated)    pb->setText(num);
   else  pb->setText(selectedText);

   QFont f("MS Shell Dlg 2",9,QFont::Normal,true);
   toggleFont(pb,f,false);

   if(gridupdated && nishioMode){

       nishio_trace(selectedCell,num,selectedText,true);
   }

}
/*
 *  cancel number change and handling of update value of the grids
 */
void MainWindow::on_CancelNum_clicked()
{
    QPushButton *pb = ui->Board->findChild<QPushButton*>(selectedCell);
    QFont f("MS Shell Dlg 2",9,QFont::Normal,true);
    toggleFont(pb,f,false);

}

/*
 *  helper function for font color change
 */
void MainWindow::toggleFont(QPushButton *pb,QFont f,bool gridclick)
{
    if(pb->text()==" ")   pb->setText("?");
     else if(pb->text()=="?")   pb->setText(" ");

    pb->setFont(f);
    QPalette p;
    if(gridclick)
      p.setColor(pb->foregroundRole(),Qt::red);
    else
      p.setColor(pb->foregroundRole(),Qt::green);
    pb->setPalette(p);

  // constraint
   if(constraintMode){
      if(gridclick){
      //find constraint and store in arr
      int arr[qsize];
      game.constraints(selectedCell.toInt(),arr);
      ui->numberbox->setEnabled(gridclick);
      ui->CancelNum->setEnabled(gridclick);
     for(int i=0; i<qsize; i++)
         //set invisible the invalid candidates
        if(*(arr+i)!=3) ui->numberbox->findChild<QPushButton*>(QString::number(i+1))->setVisible(false);
      }else{

          for(int i=0; i<qsize; i++){
          ui->numberbox->findChild<QPushButton*>(QString::number(i+1))->setVisible(true);
          }
          ui->numberbox->setEnabled(gridclick);
          ui->CancelNum->setEnabled(gridclick);
      };
   }
   else{
   ui->numberbox->setEnabled(gridclick);
   ui->CancelNum->setEnabled(gridclick);
   }
   ui->Board->setDisabled(gridclick);
   ui->numberbox->setAutoFillBackground(!gridclick);
}

//##################### start game button triggered #############
void MainWindow::on_startButton_clicked()
{


       ui->startButton->setVisible(false);
        ui->choice->setVisible(true);




}

void MainWindow::on_selectionOk_clicked()
{

    //handling of possible bug of qsize update delaying
    if(qsize == 9 || qsize == 16){
    NumberGrid(qsize);
    StartGrid(qsize);
    }
        ui->choice->setVisible(false);
}

void MainWindow::on_nine_clicked()
{
    qsize = 9;
    ui->selectedsize->setText("9 X 9");
}

void MainWindow::on_sixteen_clicked()
{
    qsize = 16;
    ui->selectedsize->setText("16 X 16");
}


void MainWindow::on_heurimode_clicked()
{
    gamemode = heuri;
    ui->selectedmode->setText("Heuristics");
   ui->Hello->setText("Heuri");
}


void MainWindow::on_algomode_clicked()
{
   gamemode = algo;
   ui->selectedmode->setText("Algorithmic");
   ui->Hello->setText("Algo");

}

void MainWindow::on_jigsawmode_clicked()
{
    gamemode = jigsaw;
    ui->selectedmode->setText("Jigsaw");
    ui->Hello->setText("Jigsaw");
}


//#################### restart ################################
void MainWindow::on_startButton_2_clicked()
{

    ui->newGameBox->setVisible(true);

}

//yes to confirm restart
void MainWindow::on_yesNew_clicked()
{

      QProcess pc;
     // pc.startDetached("Backtracking",QStringList());
        //qApp->quit();

       qApp->exit( MainWindow::EXIT_CODE_REBOOT );

      pc.start("Backtracking",QStringList());


}

//no to cancel
void MainWindow::on_noNew_clicked()
{
    ui->newGameBox->setVisible(false);
}

//########################## end of part 1 ###################################


/*
 *          ####  Part 2 , functions help to solve puzzle ###
 */

//################ show constraints/show patterns/nishio #####################



//############################ show constraint ##########################
/*
 *   show constraints button clicked
 *
 *   when constraint mode activated, number grid will response correspondingly
 */
void MainWindow::on_constraint_clicked()


{
    // show to hide , hide to show
    constraintMode = !constraintMode;
   if(constraintMode) ui->constraint->setText("hide constraints");
   else ui->constraint->setText("show constraints");


}
//######################### end of show constraints #######################


//############################ show patterns mode ##########################

/*
 * font handling for show patterns
 */
void MainWindow::toggleFontPatternMode(QPushButton *pb,QFont f, QString type)
{
    if(pb->text()==" ")
    {
        pb->setText(type);
        pb->setFont(f);
        QPalette p;
        p.setColor(pb->foregroundRole(),Qt::red);
           pb->setPalette(p);
    }
    else  pb->setText(" ");

}


//for storing three patterns X-wings Y-wings and Rect as stack in map
std::map<std::string,std::stack<std::vector<int>>> xyrStack;
std::vector<int> previousPattern;
/*
 * show patterns functions handling
 */
void MainWindow::ShowPattern()
{

    QObject *b = QObject::sender();
    QString type = b->objectName();

    QFont f("Courier",13,QFont::Bold,true);
      if(!previousPattern.empty()){
          for(auto i : previousPattern ){
              QPushButton *pb = ui->Board->findChild<QPushButton*>(QString::number(i+1));
               toggleFontPatternMode(pb,f," ");

          }
      }
      //stack ptr point to a stack in map
     std::stack<std::vector<int>> *stackPtr;
     stackPtr = &xyrStack[type.toStdString()];

      //if no pattern left or found
      if(!stackPtr->empty()){
      previousPattern = stackPtr->top();
      stackPtr->pop();
      int count = 1;
      ui->Info->setVisible(true);
      //delete label
      delete ui->Info->findChild<QVBoxLayout*>();
      while ( QLabel* w = ui->Info->findChild<QLabel*>() )
          delete w;
      QVBoxLayout *qh   = new QVBoxLayout;

      for(auto i : previousPattern ){
          QString text = type+QString::number(count++);
          QPushButton *pb = ui->Board->findChild<QPushButton*>(QString::number(i+1));
          toggleFontPatternMode(pb,f,text);

          //show constraints of each cells in such patterns

          QLabel *lb;
          lb=new QLabel();
          lb->setAlignment(Qt::AlignLeft);
          QString tmpText = text.append(":");
          int arr[qsize];
          game.constraints(i+1,arr);
       // qDebug() << "i: " << i << "\n";
          for(int j=0; j<qsize; j++){
             if(*(arr+j)==3){
                tmpText.append(" ").append(QString::number(j+1));
                if(tmpText.size()==13 || tmpText.size()==31) tmpText.append("\n      ");
              }
           }
        //  qDebug() << "text: " << tmpText << "\n";
          //set constraints on label
          lb->setText(tmpText);
          lb->setStyleSheet("color:#cc6600;\n");

          qh->addWidget(lb);
          qh->setAlignment(Qt::AlignVCenter);


        }
        ui->Info->setLayout(qh);
        ui->patternbox->findChild<QPushButton*>(type)->setText(QString::number(stackPtr->size()));
      }else{
          ui->patternbox->findChild<QPushButton*>(type)->setText(QString::number(0));
      }

//    std::cout << "frontEnd: \n";
//     for(auto &x: Xwing){
//         for(auto y:x){
//             std::cout << y << " ";
//         }
//         std::cout << "\n";
//     }

}

/*
 *  show pattern button clicked
 */
void MainWindow::on_patterns_clicked()
{
  patternMode = !patternMode;
  if(patternMode){

   ui->Board->setDisabled(true);
   ui->constraint->setDisabled(true);
   ui->nishio->setDisabled(true);

      std::map<std::string,std::set<std::vector<int>>> pMap;
      pMap = game.pattern();
      //store to map
      std::string tmp[3] = {"X","Y","R"};
         for(std::string i : tmp){
          for(auto &x: pMap[i]){
              xyrStack[i].push(x);
           }

         }


   ui->patterns->setText(QString("Hide Patterns"));
    if(!xyrStack["X"].empty() || !xyrStack["Y"].empty() || !xyrStack["R"].empty() ){
         ui->patternbox->show();
        QPushButton *xw;
        xw = new QPushButton("Xwing");
        xw->setObjectName("X");
        connect(xw,SIGNAL(clicked()),this,SLOT(ShowPattern()));
        QPushButton *yw;
        yw = new QPushButton("Ywing");
        yw->setObjectName("Y");
        connect(yw,SIGNAL(clicked()),this,SLOT(ShowPattern()));
        QPushButton *rect;
        rect = new QPushButton("Rect");
        rect->setObjectName("R");
        connect(rect,SIGNAL(clicked()),this,SLOT(ShowPattern()));


        ui->patternLayout->addWidget(xw);
        ui->patternLayout->addWidget(yw);
        ui->patternLayout->addWidget(rect);
        ui->patternbox->setStyleSheet("QPushButton{background:#4080bf;\n}");


    }else{
      QLabel *lb;
      lb = new QLabel("No Patterns Found.");
      lb->setAlignment(Qt::AlignCenter);
      ui->patternLayout->addWidget(lb,Qt::AlignCenter);

    }
  }else{
      //hide pattern mode handling
      ui->patterns->setText("Patterns");
      while ( QPushButton* w = ui->patternbox->findChild<QPushButton*>() )
          delete w;
     while ( QLabel* w = ui->Info->findChild<QLabel*>() )
         delete w;
      while ( QVBoxLayout* w = ui->Info->findChild<QVBoxLayout*>() )
              delete w;
      xyrStack.clear();
      //clear marks of previous pattern
      QFont f("Courier",13,QFont::Bold,true);
        if(!previousPattern.empty()){
            for(auto i : previousPattern ){
                QPushButton *pb = ui->Board->findChild<QPushButton*>(QString::number(i+1));
                 toggleFontPatternMode(pb,f," ");
            }
        }
        ui->Board->setEnabled(true);
        ui->constraint->setEnabled(true);
        ui->nishio->setEnabled(true);
      ui->patternbox->hide();
     // ui->Info->setVisible(false);


  }
}
//###########################  end of show patterns #########################

//########################### nishio mode ######################################

QVBoxLayout *qh ;;
//two stack for nishio
std::stack<std::vector<QString>> track;
std::stack<std::vector<QString>> trackAux;
/*
 *  if nishio mode activated, nishio_trace will be activated when cells' clicked
 */
void MainWindow::nishio_trace(QString cell, QString value, QString originalvalue,bool aux)
{

    // qDebug() << "nishio: " << cell << " " << value << " \n";
    /*
     *  adding cells to track, trackAux if for re-track
     */
     QPushButton *pb = ui->Board->findChild<QPushButton*>(cell);
     if(aux){
         trackAux = std::stack<std::vector<QString>>();
     }else{
          pb->setText(value);
     }
     /*
      * label out track on screen handling
      */
     pb->setDisabled(true);
     QPalette p;
     p.setColor(pb->foregroundRole(),Qt::red);
     pb->setPalette(p);
     std::vector<QString> tmp= {cell,value,originalvalue};
     track.push(tmp);
     QString lbl = "cell";
     lbl.append(cell).append(" -> ").append(value);
     QLabel *ql;
     ql = new QLabel(lbl);
     ql->setObjectName(cell);
     ql->setStyleSheet("color: #0099cc;\n background:#a6a6a6;\n");
     qh->addWidget(ql);
     qh->setAlignment(Qt::AlignTop);

}

/*
 * handling the flow of Backtrack, Next and reset
 */
void MainWindow::nishioflow()
{


    QObject *b = QObject::sender();
    QString sn= b->objectName();

    if(sn=="Backtrack")
    {
        /*
         *  pull cells from track and push to trackAux
         */
       if(!track.empty()){
       QPushButton *pb = ui->Board->findChild<QPushButton*>(track.top().at(0));
       delete ui->Info->findChild<QLabel*>(track.top().at(0));
       game.nishioupdategrid(track.top().at(0).toInt(),track.top().at(1).toInt());

       QString tmp = track.top().at(2);
       if(tmp == "?") tmp = " ";
       pb->setEnabled(true);
       pb->setText(tmp);
       trackAux.push(track.top());
       track.pop();
       }

    }
    else if(sn=="Next")
    {
        if(!trackAux.empty())
        {
            QPushButton *pb = ui->Board->findChild<QPushButton*>(trackAux.top().at(0));
           game.nishioupdategrid(trackAux.top().at(0).toInt(),trackAux.top().at(1).toInt());
           pb->setText(trackAux.top().at(1));
           //trace again
           nishio_trace(trackAux.top().at(0),trackAux.top().at(1),
                        trackAux.top().at(2),false);

           trackAux.pop();
        }
    }
    //reset
    else
    {
        //reset when there're some trial moves
        while(!track.empty()){
        QPushButton *pb = ui->Board->findChild<QPushButton*>(track.top().at(0));
        delete ui->Info->findChild<QLabel*>(track.top().at(0));
        game.nishioupdategrid(track.top().at(0).toInt(),track.top().at(1).toInt());

        QString tmp = track.top().at(2);
        if(tmp == "?") tmp = " ";
        pb->setEnabled(true);
        pb->setText(tmp);
        QPalette p;
        p.setColor(pb->foregroundRole(),Qt::green);
        pb->setPalette(p);

        track.pop();
        }
    }

}
/*
 * nishio button clicked, call nishioflow
 */

void MainWindow::on_nishio_clicked()
{
    //start to end, end to start
    nishioMode = !nishioMode;
    if(nishioMode)
    {
          ui->constraint->clicked(true);
          ui->constraint->setDisabled(true);
          ui->patterns->setDisabled(true);
          ui->nishio->setText("End nishio");
         // ui->Info->setVisible(true);
          ui->nishiobox->setVisible(true);
          ui->nishiobtnGrid->setSpacing(1);
           qh  = new QVBoxLayout;
           //create buttons
          QString ts[3] = {"Backtrack","Next","Reset"};
          for(QString s : ts){
              QPushButton *pb;
              pb = new QPushButton;
              pb->setText(s);
              pb->setObjectName(s);
              if(!(s=="Backtrack")) pb->setFixedWidth(50);
              ui->nishiobtnGrid->addWidget(pb);
              connect(pb,SIGNAL(clicked()),this,SLOT(nishioflow()));
          }

          ui->Info->setLayout(qh);

    }
    else
    {
       //no move to backtrack
       while(!track.empty()){
           QPushButton *pb = ui->Board->findChild<QPushButton*>(track.top().at(0));
           pb->setEnabled(true);
           QPalette p;
           p.setColor(pb->foregroundRole(),Qt::green);
           pb->setPalette(p);
             track.pop();

       }
        ui->patterns->setEnabled(true);
        ui->nishio->setText("nishio");

        while ( QPushButton* w = ui->nishiobox->findChild<QPushButton*>() )
            delete w;
        while ( QLabel* w = ui->Info->findChild<QLabel*>() )
            delete w;
      //  ui->Info->setVisible(false);
        ui->nishiobox->setVisible(false);
        ui->constraint->clicked(true);
        ui->constraint->setEnabled(true);
        track = std::stack<std::vector<QString>>();
        trackAux = std::stack<std::vector<QString>>();

    }
}

//######################### end of nishio #####################################

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * solving puzzle handling
 */

void MainWindow::on_solve_clicked()
{
    game.solve();
    QPalette p;
    for(int i = 0; i<qsize; i++){
        for(int j = 0 ; j<qsize; j++){
            //assign number to cells except the originally genearated
           QPushButton *pb = ui->Board->findChild<QPushButton*>(QString::number(i*qsize+j+1));

                       if(pb->accessibleName() != "clues"){

               pb->setText(QString::number(*(game.puzzle+i*qsize+j)));
               p.setColor(pb->foregroundRole(),Qt::red);
               pb->setPalette(p);

            }

        }
    }
}

