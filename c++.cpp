#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QTextEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QFontDialog>
#include <QVBoxLayout>
#include <QScrollBar>

class NotepadPro : public QMainWindow {
    Q_OBJECT

public:
    NotepadPro(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("Notepad Pro");
        resize(800, 600);

        // Text Area
        textEdit = new QTextEdit(this);
        textEdit->setStyleSheet("background-color: #1e1e1e; color: #dcdcdc;");
        setCentralWidget(textEdit);

        // Menu Bar
        QMenuBar *menuBar = new QMenuBar(this);
        menuBar->setStyleSheet("background-color: #2b2b2b; color: white;");
        setMenuBar(menuBar);

        // File Menu
        QMenu *fileMenu = menuBar->addMenu("File");
        fileMenu->addAction("New", this, &NotepadPro::newFile);
        fileMenu->addAction("Open", this, &NotepadPro::openFile);
        fileMenu->addAction("Save", this, &NotepadPro::saveFile);
        fileMenu->addAction("Exit", this, &QWidget::close);

        // Edit Menu
        QMenu *editMenu = menuBar->addMenu("Edit");
        editMenu->addAction("Undo", textEdit, &QTextEdit::undo);
        editMenu->addAction("Redo", textEdit, &QTextEdit::redo);
        editMenu->addAction("Cut", textEdit, &QTextEdit::cut);
        editMenu->addAction("Copy", textEdit, &QTextEdit::copy);
        editMenu->addAction("Paste", textEdit, &QTextEdit::paste);
        editMenu->addAction("Select All", textEdit, &QTextEdit::selectAll);

        // Format Menu
        QMenu *formatMenu = menuBar->addMenu("Format");
        formatMenu->addAction("Word Wrap", this, &NotepadPro::toggleWordWrap);
        formatMenu->addAction("Font", this, &AllPhoebe::chooseFont);
    }

private slots:
    void newFile() {
        textEdit->clear();
    }

    void openFile() {
        QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Text Files (*.txt);;All Files (*)");
        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                textEdit->setPlainText(file.readAll());
                file.close();
            } else {
                QMessageBox::warning(this, "Error", "Cannot open file");
            }
        }
    }

    void saveFile() {
        QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", "Text Files (*.txt);;All Files (*)");
        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                file.write(textEdit->toPlainText().toUtf8());
                file.close();
            } else {
                QMessageBox::warning(this, "Error", "Cannot save file");
            }
        }
    }

    void toggleWordWrap() {
        if (textEdit->wordWrapMode() == QTextOption::NoWrap) {
            textEdit->setWordWrapMode(QTextOption::WordWrap);
        } else {
            textEdit->setWordWrapMode(QTextOption::NoWrap);
        }
    }

    void chooseFont() {
        bool ok;
        QFont font = QFontDialog::getFont(&ok, textEdit->font(), this);
        if (ok) {
            textEdit->setFont(font);
        }
    }

private:
    QTextEdit *textEdit;
};

#include "main.moc"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    NotepadPro;
    editor.show();
    return app.exec();
}
