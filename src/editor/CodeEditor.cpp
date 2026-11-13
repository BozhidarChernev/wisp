#include "CodeEditor.h"

CodeEditor::CodeEditor()
{
}

void CodeEditor::keyPressEvent(QKeyEvent *event)
{
    // auto indent
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) // Qt::Key_Return = numpad enter
    {
        QPlainTextEdit::keyPressEvent(event);

        QString prev_line_text = textCursor().block().previous().text();
        QString empty_spaces = "";

        for (int i = 0; i < prev_line_text.size(); i++)
        {
            if (!prev_line_text[i].isSpace())
                break;

            empty_spaces += prev_line_text[i];
        }

        textCursor().insertText(empty_spaces);
        return;
    }

    // tab fix
    if (event->key() == Qt::Key_Tab)
    {
        textCursor().insertText("    ");
        return;
    }

    {
        QString openers = "[{(\"'`";
        QString closers = "]})\"'`";
        QString typed_char = event->text();

        if (!typed_char.isEmpty())
        {
            int idx = openers.indexOf(typed_char);

            if (idx != -1)
            {
                QString completed = "";
                completed += openers[idx];
                completed += closers[idx];

                textCursor().insertText(completed);
                moveCursor(QTextCursor::Left);
                return;
            }
        }
    }

    // zoom in / zoom out
    {
        if (event->modifiers() == Qt::ControlModifier)
        {
            if (event->key() == Qt::Key_Plus || event->key() == Qt::Key_Equal)
            {
                zoomIn(5);
                return;
            }

            if (event->key() == Qt::Key_Minus)
            {
                zoomOut(5);
                return;
            }
        }
    }

    QPlainTextEdit::keyPressEvent(event);
}
