#ifndef CVRTEST_TRANSFERFUNCTIONHANDLER_H
#define CVRTEST_TRANSFERFUNCTIONHANDLER_H

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

#include <qdialog.h>
#include <qwidget.h>

class SoTransferFunction;
class Gradient;

namespace Ui {
  class SoTransferFunctionCtrl;
}
class TransferFunctionHandler : QDialog
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
  Ui::SoTransferFunctionCtrl * ctrl;

  int remap[2];

  class SoQtGradientDialog * gradientdialog;
  void gradientCallback(const Gradient & g);
  static void gradientCallbackP(const Gradient & g, void * userdata);
};

#endif // !CVRTEST_TRANSFERFUNCTIONHANDLER_H
