#include <QCoreApplication>
#include <iostream>
#include "gamecontrol.h"
#include "grid.h"
#include "generatepuzzle.h"
#include "unittest.h"
#include "showconstraint.h"
#include <QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[])
{


   // gamecontrol g;
   // g.test(9,999);

   int currentExitCode = 0;
   do {
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    currentExitCode = a.exec();
   } while( currentExitCode == MainWindow::EXIT_CODE_REBOOT );
 return currentExitCode;



}
