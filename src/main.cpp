/*
   src/app/MainWindow.h
    src/app/MainWindow.cpp

    src/editor/Editor.h
    src/editor/Editor.cpp
*/

#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow window;
    window.setWindowTitle("wisp - Nov 11 2026 @ 12:17 AM");
    window.resize(900, 600);
    window.showMaximized();

    return app.exec();
}