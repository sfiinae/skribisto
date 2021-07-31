﻿#include "skrhighlighter.h"
#include <QDebug>
#include <QTextDocument>
#include <QTextBoundaryFinder>
#include <QColor>
#include "skrdata.h"

SKRHighlighter::SKRHighlighter(QTextDocument *parentDoc)
    : QSyntaxHighlighter(parentDoc), m_spellCheckerSet(false), m_projectId(-2), m_isForMinimap(false)
{
    SKRSpellChecker *spellChecker = new SKRSpellChecker(this);

    this->setSpellChecker(spellChecker);

    connect(skrdata->projectDictHub(),
            &SKRProjectDictHub::projectDictFullyChanged,
            this,
            [this](int projectId, const QStringList& newProjectDict) {
        if (projectId == this->getProjectId()) {
            this->getSpellChecker()->setUserDict(newProjectDict);
            this->rehighlight();
        }
    }
            );

    connect(skrdata->projectDictHub(), &SKRProjectDictHub::projectDictWordAdded, this,
            [this](int projectId, const QString& newWord) {
        if (projectId == this->getProjectId()) {
            this->getSpellChecker()->addWordToUserDict(newWord);
            this->rehighlight();
        }
    }
            );

    connect(skrdata->projectDictHub(), &SKRProjectDictHub::projectDictWordRemoved, this,
            [this](int projectId, const QString& wordToBeRemoved) {
        if (projectId == this->getProjectId()) {
            this->getSpellChecker()->removeWordFromUserDict(wordToBeRemoved);
            this->rehighlight();
        }
    }
            );

    connect(spellChecker, &SKRSpellChecker::activated, this, [this](bool activated) {
        if (activated) {
            this->getSpellChecker()->setUserDict(m_userDictList);
            this->rehighlight();
        }
    }
            );
}

// -------------------------------------------------------------------


// -------------------------------------------------------------------

void SKRHighlighter::highlightBlock(const QString& text)
{
    //    if (text.length() > 7000) { // cancel the highlighting to prevent
    // slowing.
    //        qWarning() << "a paragraph is too long for highlighting !";
    //        return;
    //    }

    setCurrentBlockState(0);

    // -----------------------------------------------------------------
    // find  :

    QList<int> findList;

    QTextCharFormat findFormat;

    if (m_isForMinimap) {
        findFormat.setBackground(QBrush(QColor(m_findHighlightColor)));
    }
    else {
        findFormat.setBackground(QColor(m_findHighlightColor));
    }

    if (!textToHighLight.isEmpty()) {
        int position = 0;

        while (position >= 0) {
            int start = text.indexOf(textToHighLight, position, sensitivity);

            if (start == -1) break;

            //            setFormat(start , textToHighLight.size(), findFormat);

            // list for later merging :
            for (int i = start; i < start + textToHighLight.size();
                 ++i) findList.append(i);

            position = text.indexOf(textToHighLight,
                                    position + textToHighLight.size(),
                                    sensitivity);
        }
    }

    // -----------------------------------------------------------------
    //  dialogs:


    QList<int> dialogList;
    QTextCharFormat dialogFormat;

    if (m_isForMinimap) {
        dialogFormat.setBackground(QBrush(QColor(m_otherHighlightColor_1)));

        QRegularExpression startExpression("\\«");
        QRegularExpression endExpression("\\»");

        int startIndex = 0;

        if (previousBlockState() != 1) startIndex = text.indexOf(startExpression);

        while (startIndex >= 0) {
            QRegularExpressionMatch endMatch;
            int endIndex = text.indexOf(endExpression, startIndex, &endMatch);
            int dialogLength;

            if (endIndex == -1) {
                setCurrentBlockState(1);
                dialogLength = text.length() - startIndex;
            } else {
                dialogLength = endIndex - startIndex
                               + endMatch.capturedLength();
            }
            setFormat(startIndex, dialogLength, dialogFormat);


            for (int i = startIndex; i < startIndex + dialogLength; i++) {
                dialogList << i;
            }

            startIndex = text.indexOf(startExpression,
                                      startIndex + dialogLength);
        }
    }

    if (m_isForMinimap) {
        dialogFormat.setBackground(QBrush(QColor(m_otherHighlightColor_1)));

        QRegularExpression startExpression("^-|^–|^—");
        QRegularExpression endExpression("\\»|.$");

        int startIndex = 0;

        if (previousBlockState() != 1) startIndex = text.indexOf(startExpression);

        while (startIndex >= 0) {
            QRegularExpressionMatch endMatch;
            int endIndex = text.indexOf(endExpression, startIndex, &endMatch);
            int dialogLength;

            if (endIndex == -1) {
                setCurrentBlockState(1);
                dialogLength = text.length() - startIndex;
            } else {
                dialogLength = endIndex - startIndex
                               + endMatch.capturedLength();
            }
            setFormat(startIndex, dialogLength, dialogFormat);


            for (int i = startIndex; i < startIndex + dialogLength; i++) {
                dialogList << i;
            }

            startIndex = text.indexOf(startExpression,
                                      startIndex + dialogLength);
        }
    }

    // -----------------------------------------------------------------
    //    spell check :

    QList<int> spellcheckerList;

    QTextCharFormat spellcheckFormat;

    // BUG to be uncommented when bug
    // https://bugreports.qt.io/browse/QTBUG-87260 is fixed
    spellcheckFormat.setUnderlineColor(QColor(m_spellCheckHighlightColor));

    //
    spellcheckFormat.setUnderlineStyle(QTextCharFormat::SpellCheckUnderline);

    if (m_isForMinimap) {
        spellcheckFormat.setBackground(QBrush(QColor(m_spellCheckHighlightColor)));
    }
    else {
        spellcheckFormat.setForeground(QBrush(QColor(m_spellCheckHighlightColor)));
    }

    if (m_spellCheckerSet)
        if (m_spellChecker->isActive()) {
            QTextBoundaryFinder wordFinder(QTextBoundaryFinder::Word, text);
            int wordStart     = 0;
            int wordLength    = 0;
            QString wordValue = "";

            while (wordFinder.position() < text.length())
            {
                if (wordFinder.position() == -1) break;

                if (wordFinder.position() == 0)
                {
                    wordStart = 0;
                }
                else
                {
                    wordStart = wordFinder.position();
                }


                wordLength = wordFinder.toNextBoundary() - wordStart;

                wordValue = text.mid(wordStart, wordLength);


                if (!m_spellChecker->spell(text.mid(wordStart, wordLength))) {
                    //                setFormat(wordStart, wordLength,
                    // spellcheckFormat);


                    if (text.mid(wordStart + wordLength, 1) == "-") { // cerf-volant,
                        // orateur-né
                        wordFinder.toNextBoundary();
                        int nextWordLength = wordFinder.toNextBoundary() -
                                             (wordStart + wordLength + 1);
                        wordFinder.toPreviousBoundary();
                        wordFinder.toPreviousBoundary();

                        QString hyphenWord = text.mid(wordStart,
                                                      wordLength + nextWordLength + 1);

                        //                    qDebug() <<
                        // "hyphenWord_Highlighter : " + hyphenWord;
                        if (!m_spellChecker->spell(text.mid(wordStart,
                                                            hyphenWord.size()))) {
                            wordLength = hyphenWord.size();
                            wordFinder.toNextBoundary();
                            wordFinder.toNextBoundary();

                            for (int i = wordStart; i < wordStart + wordLength;
                                 ++i) spellcheckerList.append(i);
                            continue;
                        }
                        else {
                            wordFinder.toNextBoundary();
                            wordFinder.toNextBoundary();
                            continue;
                        }
                    }


                    // list for later merging :
                    for (int i = wordStart; i < wordStart + wordLength;
                         ++i) spellcheckerList.append(i);
                }
            }
        }


    // QList<int> spellcheckPositionList;

    for (int k = 0; k < text.length(); ++k) {
        QTextCharFormat finalFormat;

        if (dialogList.contains(k)) {
            finalFormat.merge(dialogFormat);
        }

        if (findList.contains(k)) {
            finalFormat.merge(findFormat);
        }


        if (spellcheckerList.contains(k)) {
            finalFormat.merge(spellcheckFormat);

            // bug fix:
            // spellcheckPositionList.append(currentBlock().position() + k);
        }

        setFormat(k, 1, finalFormat);
    }

    // emit paintUnderlineForSpellcheckCalled(spellcheckPositionList,
    // currentBlock());

    emit shakeTextSoHighlightsTakeEffectCalled();
}

// -------------------------------------------------------------------


void SKRHighlighter::setTextToHighlight(QString string)
{
    textToHighLight = string;
    this->rehighlight();
}

// -------------------------------------------------------------------

void SKRHighlighter::setCaseSensitivity(bool isCaseSensitive)
{
    if (isCaseSensitive) {
        sensitivity = Qt::CaseSensitive;
    }
    else {
        sensitivity = Qt::CaseInsensitive;
    }
}

// -------------------------------------------------------------------

SKRSpellChecker * SKRHighlighter::getSpellChecker()
{
    if (!m_spellChecker) {
        qDebug() << "no check speller set";
    }
    return m_spellChecker;
}

// -------------------------------------------------------------------

void SKRHighlighter::setSpellChecker(SKRSpellChecker *spellChecker)
{
    if (spellChecker) {
        m_spellChecker    = spellChecker;
        m_spellCheckerSet = true;
    }
    else {
        //        qWarning() << "TextHighlighter : no spellchecker set";
        m_spellCheckerSet = false;
    }
}

QString SKRHighlighter::getOtherHighlightColor_3() const
{
    return m_otherHighlightColor_3;
}

void SKRHighlighter::setOtherHighlightColor_3(const QString& newOtherHighlightColor_3)
{
    if (m_otherHighlightColor_3 == newOtherHighlightColor_3) return;

    m_otherHighlightColor_3 = newOtherHighlightColor_3;
    this->rehighlight();
    emit otherHighlightColor_3Changed();
}

QString SKRHighlighter::getOtherHighlightColor_2() const
{
    return m_otherHighlightColor_2;
}

void SKRHighlighter::setOtherHighlightColor_2(const QString& newOtherHighlightColor_2)
{
    if (m_otherHighlightColor_2 == newOtherHighlightColor_2) return;

    m_otherHighlightColor_2 = newOtherHighlightColor_2;
    this->rehighlight();
    emit otherHighlightColor_2Changed();
}

QString SKRHighlighter::getOtherHighlightColor_1() const
{
    return m_otherHighlightColor_1;
}

void SKRHighlighter::setOtherHighlightColor_1(const QString& newOtherHighlightColor_1)
{
    if (m_otherHighlightColor_1 == newOtherHighlightColor_1) return;

    m_otherHighlightColor_1 = newOtherHighlightColor_1;
    this->rehighlight();
    emit otherHighlightColor_1Changed();
}

QString SKRHighlighter::getFindHighlightColor() const
{
    return m_findHighlightColor;
}

void SKRHighlighter::setFindHighlightColor(const QString& newFindHighlightColor)
{
    if (m_findHighlightColor == newFindHighlightColor) return;

    m_findHighlightColor = newFindHighlightColor;
    this->rehighlight();
    emit findHighlightColorChanged();
}

QString SKRHighlighter::spellCheckHighlightColor() const
{
    return m_spellCheckHighlightColor;
}

void SKRHighlighter::setSpellCheckHighlightColor(const QString& newSpellCheckHighlightColor)
{
    if (m_spellCheckHighlightColor == newSpellCheckHighlightColor) return;

    m_spellCheckHighlightColor = newSpellCheckHighlightColor;

    this->rehighlight();
    emit spellCheckHighlightColorChanged();
}

// -------------------------------------------------------------------

bool SKRHighlighter::getIsForMinimap() const
{
    return m_isForMinimap;
}

void SKRHighlighter::setIsForMinimap(bool newIsForMinimap)
{
    m_isForMinimap = newIsForMinimap;

    this->rehighlight();
    emit isForMinimapChanged(newIsForMinimap);
}

// -------------------------------------------------------------------

int SKRHighlighter::getProjectId() const
{
    return m_projectId;
}

// -------------------------------------------------------------------

void SKRHighlighter::setProjectId(int projectId)
{
    m_projectId = projectId;

    // get userdict
    if (projectId != -2) {
        m_userDictList.clear();
        m_userDictList = skrdata->projectDictHub()->getProjectDictList(projectId);

        //
        //
        //
        // m_userDictList.append(skrdata->projectDictHub()->getProjectDynamicDictList(projectId));
    }

    // set user dict
    if (m_spellChecker && m_spellChecker->isHunspellLaunched() && (projectId != -2)) {
        m_spellChecker->setUserDict(m_userDictList);
    }


    emit projectIdChanged(projectId);
}

// --------------------------------------------------------------
