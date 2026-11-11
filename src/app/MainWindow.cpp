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

    QAction *open_folder = file_menu->addAction("&Open Folder");
    open_folder->setShortcut(QKeySequence("Ctrl+Shift+O"));
    connect(open_folder, &QAction::triggered, this, &MainWindow::OpenFolder);

    QAction *save_file = file_menu->addAction("&Save File");
    save_file->setShortcut(QKeySequence::Save);
    connect(save_file, &QAction::triggered, this, &MainWindow::SaveFile);

    QAction *save_file_as = file_menu->addAction("&Save File As");
    save_file_as->setShortcut(QKeySequence::SaveAs);
    connect(save_file_as, &QAction::triggered, this, &MainWindow::SaveFileAs);

    file_tree.setModel(&filesys_model);
    file_tree.setHeaderHidden(true);

    file_tree.hideColumn(1);
    file_tree.hideColumn(2);
    file_tree.hideColumn(3);

    folder_dock.setWidget(&file_tree);
    folder_dock.setFeatures(QDockWidget::NoDockWidgetFeatures);

    addDockWidget(Qt::LeftDockWidgetArea, &folder_dock);
    folder_dock.hide();

    connect(&file_tree, &QTreeView::doubleClicked, this, &MainWindow::OpenFromTree);

    setCentralWidget(&editor);
}

void MainWindow::LoadFile(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Error", "Could not open file.");
        return;
    }

    QByteArray data = file.readAll();

    if (data.contains('\0'))
    {
        QMessageBox::warning(this, "Error", "Could not read file. Make sure it is a text file");
        return;
    }

    editor.setPlainText(QString::fromUtf8(data));

    bool file_readonly = !QFileInfo(path).isWritable();
    editor.setReadOnly(file_readonly);

    current_file = path;
    setWindowTitle("wisp - " + path);
}

void MainWindow::OpenFromTree(const QModelIndex &index)
{
    if (filesys_model.isDir(index))
        return;

    LoadFile(filesys_model.filePath(index));
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

    LoadFile(path);
}

void MainWindow::OpenFolder()
{
    QString folder_directory = QFileDialog::getExistingDirectory(this, "Open Folder");

    // didn't select a folder
    if (folder_directory.isEmpty())
        return;

    filesys_model.setRootPath(folder_directory);
    file_tree.setRootIndex(filesys_model.index(folder_directory));

    folder_dock.setWindowTitle(QFileInfo(folder_directory).fileName());
    folder_dock.show();
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