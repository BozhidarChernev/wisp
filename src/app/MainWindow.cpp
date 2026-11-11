#include "MainWindow.h"

MainWindow::MainWindow()
{
    setWindowTitle("wisp - Nov 11 2026");
    resize(800, 600);

    QFont font = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    editor.setFont(font);

    QMenu *file_menu = menuBar()->addMenu("&File");

    QAction *new_file = file_menu->addAction("&New File");
    new_file->setShortcut(QKeySequence::New);
    connect(new_file, &QAction::triggered, this, &MainWindow::NewFile);

    QAction *open_file = file_menu->addAction("&Open File");
    open_file->setShortcut(QKeySequence::Open);
    connect(open_file, &QAction::triggered, this, &MainWindow::OpenFile);

    QAction *save_file = file_menu->addAction("&Save File");
    save_file->setShortcut(QKeySequence::Save);
    connect(save_file, &QAction::triggered, this, &MainWindow::SaveFile);

    QAction *save_file_as = file_menu->addAction("&Save File As");
    save_file_as->setShortcut(QKeySequence::SaveAs);
    connect(save_file_as, &QAction::triggered, this, &MainWindow::SaveFileAs);

    setCentralWidget(&editor);
}

void MainWindow::NewFile()
{
    editor.clear();
    current_file.clear();
    setWindowTitle("wisp - empty");
}

void MainWindow::OpenFile()
{
    QString path = QFileDialog::getOpenFileName(this, "Open File");

    if (path.isEmpty())
        return;

    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Error", "Could not open file.");
        return;
    }

    QTextStream input(&file);
    editor.setPlainText(input.readAll());

    current_file = path;
    setWindowTitle("wisp - " + path);
}

void MainWindow::SaveFile()
{
    if (current_file.isEmpty())
        SaveFileAs();
    else
        WriteToFile(current_file);
}

void MainWindow::SaveFileAs()
{
    QString path = QFileDialog::getSaveFileName(this, "Save File As");

    if (path.isEmpty())
        return;

    WriteToFile(path);
}

void MainWindow::WriteToFile(const QString &path)
{
    QFile file(path);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Error", "Could not save the file");
        return;
    }

    QTextStream output(&file);
    output << editor.toPlainText();

    current_file = path;
    setWindowTitle("wisp - " + path);
}