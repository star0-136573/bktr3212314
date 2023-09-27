#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPushButton>
#include <QEvent>
#include <QFont>
#include <QGroupBox>
#include "gamecontrol.h"
#include <QMainWindow>
#include <stack>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

  enum gamemode{heuri,algo,jigsaw};
   gamecontrol game;
   int qsize = 9;
   int gamemode = heuri;

   /*
    *draw grid and basic game control
    */
   void GridLine(int bsize,int i, int j, QPushButton *a);
   void StartGrid(int qsize);
   void NumberGrid(int qsize);
   void toggleFont(QPushButton *pb, QFont f,bool b);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

      static int const EXIT_CODE_REBOOT =  -123456789;
private slots:

    /*
     *draw grid and basic game control
     */
    void gridClicked();
    void numberGridClicked();
    void on_startButton_clicked();
    void on_startButton_2_clicked();
    void on_yesNew_clicked();
    void on_noNew_clicked();
    void on_CancelNum_clicked();


    void on_constraint_clicked();
    /*
     *Show patten button clicked
     */
    void on_patterns_clicked();
    void ShowPattern();
    void toggleFontPatternMode(QPushButton *pb,QFont f,QString type);
    /*
     * Nishio mode button
     */
    void on_nishio_clicked();
    void nishio_trace(QString cell, QString value, QString originalvalue,bool trackAux);
    void nishioflow();

    /*
     * select game size and game mode
     */

    void on_selectionOk_clicked();
    void on_nine_clicked();
    void on_sixteen_clicked();
    void on_heurimode_clicked();
    void on_algomode_clicked();
    void on_jigsawmode_clicked();
    void on_solve_clicked();

private:
    Ui::MainWindow *ui;
    /*
     * ui control for selections
     */
    QString selectedCell;
    QString selectedText;
    bool constraintMode = false;
    bool patternMode = false;
    bool nishioMode = false;

};
#endif // MAINWINDOW_H
