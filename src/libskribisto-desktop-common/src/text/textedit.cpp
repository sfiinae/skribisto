#include "textedit.h"

#include <QTextBlock>
#include <QTextCursor>
#include <QTextList>
#include <QUuid>

TextEdit::TextEdit(QWidget *parent)
{
    m_uuid = QUuid::createUuid().toString();

    connect(this, &QTextEdit::cursorPositionChanged, this, &TextEdit::updateFontActions);

    m_italicAction = new QAction(QIcon(":/icons/backup/format-text-italic.svg"), tr("Italic"), this);
    m_italicAction->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    m_italicAction->setShortcut(QKeySequence(tr("Ctrl+I")));
    m_italicAction->setCheckable(true);

    m_boldAction = new QAction(QIcon(":/icons/backup/format-text-bold.svg"), tr("Bold"), this);
    m_boldAction->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    m_boldAction->setShortcut(QKeySequence(tr("Ctrl+B")));
    m_boldAction->setCheckable(true);

    m_strikeAction = new QAction(QIcon(":/icons/backup/format-text-strikethrough.svg"), tr("Strikethrough"), this);
    m_strikeAction->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    m_strikeAction->setShortcut(QKeySequence(tr("Ctrl+T")));
    m_strikeAction->setCheckable(true);


    m_underlineAction = new QAction(QIcon(":/icons/backup/format-text-underline.svg"), tr("Underline"), this);
    m_underlineAction->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    m_underlineAction->setShortcut(QKeySequence(tr("Ctrl+U")));
    m_underlineAction->setCheckable(true);

    m_bulletListAction = new QAction(QIcon(":/icons/backup/format-text-underline.svg"), tr("List"), this);
    m_bulletListAction->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    m_bulletListAction->setShortcut(QKeySequence(tr("")));
    m_bulletListAction->setCheckable(true);

}

QString TextEdit::uuid()
{
return m_uuid;
}

//QSize TextEdit::sizeHint() const
//{
//return QSize(800, 500);
//}


void TextEdit::wheelEvent(QWheelEvent *event)
{

    // disable Ctrl+Wheel from QTextEdit which scrolls
    if(event->modifiers() == Qt::ControlModifier) {
        event->ignore();
        return;
    }


    QTextEdit::wheelEvent(event);
}

void TextEdit::connectActions()
{
    m_actionConnectionsList.clear();

    m_actionConnectionsList << QObject::connect(m_italicAction, &QAction::toggled, this, [this](bool checked){
            QTextCharFormat format;
            format.setFontItalic(checked);
            this->mergeCurrentCharFormat(format);
    });

    m_actionConnectionsList << QObject::connect(m_boldAction, &QAction::toggled, this, [this](bool checked){
            QTextCharFormat format;
            format.setFontWeight(checked ? 700 : 400);
            this->mergeCurrentCharFormat(format);
    });

    m_actionConnectionsList << QObject::connect(m_underlineAction, &QAction::toggled, this, [this](bool checked){
            QTextCharFormat format;
            format.setFontUnderline(checked);
            this->mergeCurrentCharFormat(format);
    });


    m_actionConnectionsList << QObject::connect(m_strikeAction, &QAction::toggled, this, [this](bool checked){
            QTextCharFormat format;
            format.setFontStrikeOut(checked);
            this->mergeCurrentCharFormat(format);
    });

    m_actionConnectionsList << QObject::connect(m_bulletListAction, &QAction::toggled, this, [this](bool checked){
            QTextCursor cursor(this->document());
            cursor.setPosition(this->textCursor().position());
            cursor.setPosition(this->textCursor().anchor(), QTextCursor::KeepAnchor);

            QTextBlock block = cursor.block();
            QTextList *currentList = cursor.currentList();
            const QTextBlock previousBlock = block.previous();

            QTextCursor previousBlockCursor(this->document());
            previousBlockCursor.setPosition(previousBlock.position());
            QTextList *previousList = previousBlockCursor.currentList();

            // add to previous list if there is one
            if(previousBlock.isValid() && previousList){

                previousList->add(block);

            }
            // remove list if there is one
            else if(currentList){
                QList<QTextBlock> blockList;

                int start = cursor.position();
                int end = cursor.anchor();

                for(int i = start; i <= end; i++){
                    QTextBlock thisBlock = this->document()->findBlock(i);
                    if(!blockList.contains(thisBlock)){
                        blockList.append(thisBlock);
                    }

                }

                for(const QTextBlock &blockInSet : blockList){
                    currentList->remove(blockInSet);
                    QTextBlockFormat format;
                    format.setIndent(0);
                    cursor.mergeBlockFormat(format);
                }



            }
            else { // create a new list
                QTextListFormat listFormat;
                listFormat.setStyle(QTextListFormat::ListDisc);
                cursor.createList(listFormat);
            }

    });
}


void TextEdit::disconnectActions()
{

    for (const QMetaObject::Connection& connection : qAsConst(m_actionConnectionsList)) {
        QObject::disconnect(connection);
    }

    m_actionConnectionsList.clear();
}


QAction *TextEdit::boldAction() const
{
    return m_boldAction;
}

void TextEdit::updateFontActions()
{
    this->disconnectActions();

    const QFont font = this->currentFont();
    QTextCursor cursor(this->document());
    cursor.setPosition(this->textCursor().position());

    m_italicAction->setChecked(font.italic());
    m_boldAction->setChecked(font.bold());
    m_underlineAction->setChecked(font.underline());
    m_strikeAction->setChecked(font.strikeOut());
    m_bulletListAction->setChecked(cursor.currentList() ? true : false);

    this->connectActions();
}

QAction *TextEdit::bulletListAction() const
{
    return m_bulletListAction;
}

QAction *TextEdit::underlineAction() const
{
    return m_underlineAction;
}

QAction *TextEdit::strikeAction() const
{
    return m_strikeAction;
}

QAction *TextEdit::italicAction() const
{
    return m_italicAction;
}
