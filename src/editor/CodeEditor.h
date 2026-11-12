#include <QPlainTextEdit>
#include <QTextBlock>

class CodeEditor : public QPlainTextEdit
{
public:
    CodeEditor();

protected:
    void keyPressEvent(QKeyEvent *event) override;
};