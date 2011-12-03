#ifndef SOQTCOLORTABLEEDITORP_H
#define SOQTCOLORTABLEEDITORP_H

/**************************************************************************\
 * Copyright (c) Kongsberg Oil & Gas Technologies AS
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
\**************************************************************************/

#include <qobject.h>
#include <Inventor/SbBasic.h>
#include "SoQtColorTableEditor.h" // for Mode
#include "ColorCurve.h" // for ColorCurve::ChangeCB

class QComboBox;
class CurveEditor;
class CurveView;
class QPushButton;
class QCheckBox; 
class QLabel;
class QLineEdit;

class SoQtColorTableEditorP : public QObject {

  Q_OBJECT

public:
  SoQtColorTableEditorP(SoQtColorTableEditor * publ);
  ~SoQtColorTableEditorP();
  static void curveCallBack(void * userData);
  SoQtColorTableEditor * publ;
  QLabel * modetext;
  QLabel * curvetypetext;
  QLabel * constanttext;
  QLabel * vertgrad;
  QLabel * horgrad;
  CurveView * curveview;
  QComboBox * colormodelist;
  QComboBox * curvetypelist;
  QLineEdit * constantvalue;
  QPushButton * applybutton;
  QPushButton * donebutton;
  QPushButton * resetbutton;
  QCheckBox * instantupdate;
  SoQtColorTableEditor::ChangeCB * callBack;
  void * callbackData;
  SbBool contupdate;
  SoQtColorTableEditor::Mode mode;

public slots:
  void done(void);
  void apply(void);
  void reset(void);
  void toggleUpdate(void);
  void changeCurveMode(int);
  void setConstantValue(void);
  void updateColorLabels(void);
};

#endif // ! SOQTCOLORTABLEEDITORP_H
