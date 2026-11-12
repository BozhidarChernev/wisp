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
#include <QDockWidget>
#include <QFileSystemModel>
#include <QTreeView>

#include "../editor/CodeEditor.h"

class MainWindow : public QMainWindow
{
public:
    MainWindow();

private:
    void NewFile();
    void OpenFile();
    void OpenFolder();
    void SaveFile();
    void SaveFileAs();

    void WriteToFile(const QString &path);
    void LoadFile(const QString &path);
    void OpenFromTree(const QModelIndex &index);

    // QPlainTextEdit editor;
    CodeEditor editor;
    QString current_file;

    QFileSystemModel filesys_model;
    QDockWidget folder_dock;
    QTreeView file_tree;
};