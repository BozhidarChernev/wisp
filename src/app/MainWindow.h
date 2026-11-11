#pragma once
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QAction>
#include <QFontDatabase>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

class MainWindow : public QMainWindow
{
public:
    MainWindow();

private:
    void NewFile();
    void OpenFile();
    void SaveFile();
    void SaveFileAs();

    void WriteToFile(const QString &path);

    QPlainTextEdit editor;
    QString current_file;
};