/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>

#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::blue);
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    keywordFormat.setForeground(Qt::darkYellow);
    QStringList keywordPatterns_def;
    keywordPatterns_def << "\\bOUT_A\\b" ;
    foreach (const QString &pattern_def, keywordPatterns_def)
    {
        rule.pattern = QRegExp(pattern_def);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    keywordFormat.setForeground(Qt::darkGreen);
    //keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns_nxc;
    keywordPatterns_nxc << "\\bPrecedes\\b"
                        << "\\bButtonPressed\\b"
                        << "\\bButtonCount\\b"
                        << "\\bReadButtonEx\\b"
                        << "\\bButtonPressCount\\b"
                        << "\\bButtonLongPressCount\\b"
                        << "\\bButtonShortReleaseCount\\b"
                        << "\\bButtonLongReleaseCount\\b"
                        << "\\bButtonReleaseCount\\b"
                        << "\\bButtonState\\b"
                        << "\\bSetButtonLongPressCount\\b"
                        << "\\bSetButtonLongReleaseCount\\b"
                        << "\\bSetButtonPressCount\\b"
                        << "\\bSetButtonReleaseCount\\b"
                        << "\\bSetButtonShortReleaseCount \\b"
                        << "\\bSetButtonState\\b"
                        << "\\bSysReadButton\\b"
                        << "\\bRemoteKeepAlive\\b"
                        << "\\bRemoteMessageRead\\b"
                        << "\\bRemoteMessageWrite\\b"
                        << "\\bRemotePlaySoundFile\\b"
                        << "\\bRemotePlayTone\\b"
                        << "\\bRemoteResetMotorPosition\\b"
                        << "\\bRemoteResetScaledValue\\b"
                        << "\\bRemoteSetInputMode\\b"
                        << "\\bRemoteSetOutputState\\b"
                        << "\\bRemoteStartProgram\\b"
                        << "\\bRemoteStopProgram\\b"
                        << "\\bRemoteStopSound\\b"
                        << "\\bRemoteGetOutputState\\b"
                        << "\\bRemoteGetInputValues\\b"
                        << "\\bRemoteGetBatteryLevel\\b"
                        << "\\bRemoteLowspeedGetStatus\\b"
                        << "\\bRemoteLowspeedRead\\b"
                        << "\\bRemoteGetCurrentProgramName\\b"
                        << "\\bRemoteDatalogRead\\b"
                        << "\\bRemoteGetContactCount\b"
                        << "\\bRemoteGetContactName\\b"
                        << "\\bRemoteGetConnectionCount\\b"
                        << "\\bRemoteGetConnectionName\\b"
                        << "\\bRemoteGetProperty\\b"
                        << "\\bRemoteResetTachoCount\\b"
                        << "\\bRemoteDatalogSetTimes\\b"
                        << "\\bRemoteSetProperty\\b"
                        << "\\bRemoteLowspeedWrite\\b"
                        << "\\bRemoteOpenRead\\b"
                        << "\\bRemoteOpenAppendData\\b"
                        << "\\bRemoteDeleteFile\\b"
                        << "\\bRemoteFindFirstFile\\b"
                        << "\\bRemoteGetFirmwareVersion\\b"
                        << "\\bRemoteGetBluetoothAddress\\b"
                        << "\\bRemoteGetDeviceInfo\\b"
                        << "\\bRemoteDeleteUserFlash\\b"
                        << "\\bRemoteOpenWrite\\b"
                        << "\\bRemoteOpenWriteLinear\\b"
                        << "\\bRemoteOpenWriteData\\b"
                        << "\\bRemoteCloseFile\\b"
                        << "\\bRemoteFindNextFile\\b"
                        << "\\bRemotePollCommandLength\\b"
                        << "\\bRemoteWrite\\b"
                        << "\\bRemoteRead\\b"
                        << "\\bRemoteIOMapRead\\b"
                        << "\\bRemotePollCommand\\b"
                        << "\\bRemoteRenameFile\\b"
                        << "\\bRemoteBluetoothFactoryReset\\b"
                        << "\\bRemoteIOMapWriteValue\\b"
                        << "\\bRemoteIOMapWriteBytes\\b"
                        << "\\bRemoteSetBrickName\\b";
                      /*  << "\\b \\b"
                        << "\\b \\b"
                        << "\\b \\b"
                        << "\\b \\b"
                        << "\\b \\b"
                        << "\\b \\b"
                        << "\\b \\b"
                        << "\\b \\b"
                        << "\\b \\b"
                        << "\\b \\b"
                        << "\\b \\b"
                        << "\\b \\b"
                        << "\\b \\b"
                        << "\\b \\b"
                        << "\\b \\b"
                        << "\\b \\b"
                        << "\\b \\b"
                        << "\\b \\b"
                        << "\\b \\b"*/


    foreach (const QString &pattern_nxc, keywordPatterns_nxc)
    {
        rule.pattern = QRegExp(pattern_nxc);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }



    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                    << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
                    << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b" << "\\bbyte\\b"
                    << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                    << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                    << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                    << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                    << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                    << "\\bvoid\\b" <<"\\btask\\b"<< "\\bvolatile\\b"
                    << "\\btrue\\b"<< "\\bfalse\\b" << "\\bbool\\b"
                    << "\\bdefine\\b" << "\\bcase\\b";
    foreach (const QString &pattern, keywordPatterns)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    keywordFormat.setForeground(Qt::darkMagenta);
    //keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns_if;
    keywordPatterns_if << "\\bif\\b" << "\\bwhile\\b" << "\\bfor\\b"
                       << "\\brepeat\\b" << "\\belse\\b" << "\\buntil\\b"
                       << "\\bgoto\\b";
    foreach (const QString &pattern_if, keywordPatterns_if)
    {
        rule.pattern = QRegExp(pattern_if);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(Qt::gray);
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::gray);

    quotationFormat.setForeground(Qt::darkGreen);
    quotationFormat.setFontItalic(true);
    rule.pattern = QRegExp("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");
}

void Highlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = commentStartExpression.indexIn(text);

    while (startIndex >= 0) {
        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
    }
}
