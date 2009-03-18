#ifndef SOQTCOLORTABLEEDITORP_H
#define SOQTCOLORTABLEEDITORP_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2003 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org> for more information.
 *
 *  Systems in Motion, Teknobyen, Abels Gate 5, 7030 Trondheim, NORWAY.
 *  <URL:http://www.sim.no>.
 *
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
