#ifndef CVRTEST_TRANSFERFUNCTIONHANDLER_H
#define CVRTEST_TRANSFERFUNCTIONHANDLER_H

/**************************************************************************\
 *
 *  This file is part of a set of example programs for the Coin library.
 *  Copyright (C) 2000-2003 by Systems in Motion. All rights reserved.
 *
 *                   <URL:http://www.coin3d.org>
 *
 *  This sourcecode can be redistributed and/or modified under the
 *  terms of the GNU General Public License version 2 as published by
 *  the Free Software Foundation. See the file COPYING at the root
 *  directory of the distribution for more details.
 *
 *  As a special exception, all sourcecode of the demo examples can be
 *  used for any purpose for licensees of the Coin Professional
 *  Edition License, without the restrictions of the GNU GPL. See our
 *  web pages for information about how to acquire a Professional Edition
 *  License.
 *
 *  Systems in Motion, <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/

#include <qwidget.h>

class SoTransferFunction;
class SoTransferFunction_ctrl;
class Gradient;


class TransferFunctionHandler : QObject
{
  Q_OBJECT

public:
  TransferFunctionHandler(SoTransferFunction * node,
                          int remaplow, int remaphigh,
                          QWidget * parent = NULL);
  ~TransferFunctionHandler();

private slots:
  void lowEditUpdate(void);
  void highEditUpdate(void);
  void predefColorMapUpdate(int idx);
  void shiftEditUpdate(void);
  void offsetEditUpdate(void);

private:
  void initGUI(void);

  SoTransferFunction * node;
  SoTransferFunction_ctrl * ctrl;

  int remap[2];

  class SoQtGradientDialog * gradientdialog;
  void gradientCallback(const Gradient & g);
  static void gradientCallbackP(const Gradient & g, void * userdata);
};

#endif // !CVRTEST_TRANSFERFUNCTIONHANDLER_H
