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

#include <qimage.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qgroupbox.h>
#include <qcheckbox.h>
#include <qpainter.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qvalidator.h>

#include "CurveView.h"
#include "SoQtColorTableEditor.h"
#include "SoQtColorTableEditorP.h"
//#include "moc_SoQtColorTableEditorP.icc"

// *************************************************************************

#define PRIVATE(p) p->pimpl
#define PUBLIC(p) p->publ

// *************************************************************************

SoQtColorTableEditorP::SoQtColorTableEditorP(class SoQtColorTableEditor * publ)
{
  this->publ = publ;
}

SoQtColorTableEditorP::~SoQtColorTableEditorP()
{
  delete this->curveview;
}

void
SoQtColorTableEditorP::toggleUpdate()
{
  this->contupdate = this->instantupdate->isChecked();
  if (this->callBack) {
    this->callBack(PUBLIC(this), this->callbackData);
  }
}

void
SoQtColorTableEditorP::apply()
{
  if (this->callBack) {
    this->callBack(PUBLIC(this), this->callbackData);
  }
}

void
SoQtColorTableEditorP::done()
{
  if (!this->contupdate) {
    if (this->callBack) { this->callBack(PUBLIC(this), this->callbackData); }
  }
  PUBLIC(this)->close();
}

void
SoQtColorTableEditorP::reset()
{
  this->curvetypelist->setCurrentIndex(CurveView::SMOOTH);
  this->curveview->resetActive();
  if (this->callBack) {
    this->callBack(PUBLIC(this), this->callbackData);
  }
}

void
SoQtColorTableEditorP::changeCurveMode(int i)
{
  this->curveview->changeCurveMode(i);
  if (this->callBack) {
    this->callBack(PUBLIC(this), this->callbackData);
  }
}

void
SoQtColorTableEditorP::curveCallBack(void * userData)
{
  SoQtColorTableEditorP * thisp = (SoQtColorTableEditorP*) userData;
  if (thisp->contupdate && thisp->callBack) {
    thisp->callBack(PUBLIC(thisp), thisp->callbackData);
  }
}

void
SoQtColorTableEditorP::updateColorLabels()
{
  int width = this->horgrad->width();
  int height = this->horgrad->height();

  QPixmap pm = this->curveview->getPixmap(width-1, height-1);
  
  // flicker free drawing
  QPainter painter(&pm);
  painter.end();
  painter.begin(this->horgrad);
  painter.drawPixmap(1,1,pm);
}

void
SoQtColorTableEditorP::setConstantValue()
{
  this->curveview->changeCurveMode(CurveView::FREE);
  this->curvetypelist->setCurrentIndex(CurveView::FREE);
  int value = this->constantvalue->text().toInt();
  this->curveview->setConstantValue(value);
}

SoQtColorTableEditor::SoQtColorTableEditor(int numcolors, QWidget * parent, const char * name)
: QWidget(parent)
{
  this->setObjectName(name);
  this->pimpl = new SoQtColorTableEditorP(this);
  PRIVATE(this)->callBack = NULL;
  PRIVATE(this)->mode = SoQtColorTableEditor::RGB;
  
  QSizePolicy sizepolicy;
  sizepolicy.setVerticalPolicy(QSizePolicy::MinimumExpanding);
  this->setSizePolicy(sizepolicy);

  QGridLayout * toplayout = new QGridLayout(this);
#if QT_VERSION >= 0x050000
  toplayout->setContentsMargins(10, 10, 10, 10);
#else
  toplayout->setMargin(10);
#endif
  QVBoxLayout * buttonlayout = new QVBoxLayout();

  QGroupBox * controlgroup = new QGroupBox(this);
  controlgroup->setAlignment(Qt::Horizontal);
  QHBoxLayout * hboxlayout = new QHBoxLayout();

  QVBoxLayout * col1layout = new QVBoxLayout();
  PRIVATE(this)->modetext = new QLabel(controlgroup);
  PRIVATE(this)->modetext->setText("Modify channel: ");
  col1layout->addWidget(PRIVATE(this)->modetext);

  PRIVATE(this)->colormodelist = new QComboBox(controlgroup);
  PRIVATE(this)->colormodelist->show();
  col1layout->addWidget(PRIVATE(this)->colormodelist);
  col1layout->addStretch(1);
  
  QVBoxLayout * col2layout = new QVBoxLayout();
  PRIVATE(this)->curvetypetext = new QLabel(controlgroup);
  PRIVATE(this)->curvetypetext->setText("Curve Type: ");
  col2layout->addWidget(PRIVATE(this)->curvetypetext);
 
  PRIVATE(this)->curvetypelist = new QComboBox(controlgroup);
  PRIVATE(this)->curvetypelist->show();
  PRIVATE(this)->curvetypelist->addItem("Smooth");
  PRIVATE(this)->curvetypelist->addItem("Free");
  col2layout->addWidget(PRIVATE(this)->curvetypelist);
  col2layout->addStretch(1);

  QVBoxLayout * col3layout = new QVBoxLayout();
  PRIVATE(this)->constanttext = new QLabel(controlgroup);
  PRIVATE(this)->constanttext->setText(" Set constant value: ");
  col3layout->addWidget(PRIVATE(this)->constanttext);

  PRIVATE(this)->constantvalue = new QLineEdit(controlgroup);
  PRIVATE(this)->constantvalue->setMaxLength(3);
  PRIVATE(this)->constantvalue->setValidator(new QIntValidator(0, numcolors-1, this));
  col3layout->addWidget(PRIVATE(this)->constantvalue);
  col3layout->addStretch(1);

  hboxlayout->addLayout(col1layout);
  hboxlayout->addLayout(col2layout);
  hboxlayout->addLayout(col3layout);
  controlgroup->setLayout(hboxlayout);

  PRIVATE(this)->contupdate = FALSE;
  PRIVATE(this)->instantupdate = new QCheckBox(controlgroup);
  PRIVATE(this)->instantupdate->setChecked(FALSE);
  
  buttonlayout->setAlignment(Qt::AlignBottom);

  QWidget * curvewidget = new QWidget(this);
  curvewidget->setFixedSize(QSize(numcolors+40,numcolors+40));
  QGridLayout * curvelayout = new QGridLayout(curvewidget);

  PRIVATE(this)->vertgrad = new QLabel(curvewidget);
  PRIVATE(this)->horgrad = new QLabel(curvewidget);
  PRIVATE(this)->vertgrad->setFixedSize(20, numcolors);
  PRIVATE(this)->horgrad->setFixedSize(numcolors, 20); 
  PRIVATE(this)->vertgrad->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  PRIVATE(this)->horgrad->setFrameStyle(QFrame::Panel | QFrame::Sunken);

  curvelayout->addWidget(PRIVATE(this)->vertgrad, 0, 0);
  curvelayout->addWidget(PRIVATE(this)->horgrad, 1, 1);

  PRIVATE(this)->curveview = 
    new CurveView(numcolors, PRIVATE(this)->mode, new QGraphicsScene, curvewidget);
  PRIVATE(this)->curveview->show();

  curvelayout->addWidget(PRIVATE(this)->curveview, 0, 1);

  PRIVATE(this)->vertgrad->setPixmap(PRIVATE(this)->curveview->getGradient(20, numcolors));
  PRIVATE(this)->horgrad->setPixmap(PRIVATE(this)->curveview->getPixmap(numcolors, 20));

  toplayout->addWidget(controlgroup, 0, 0);
  toplayout->addLayout(buttonlayout, 1, 1);
  toplayout->addWidget(curvewidget, 1, 0);

  PRIVATE(this)->applybutton = new QPushButton(this);
  PRIVATE(this)->donebutton = new QPushButton(this);
  PRIVATE(this)->resetbutton = new QPushButton(this);

  PRIVATE(this)->applybutton->setAutoDefault(FALSE);
  PRIVATE(this)->resetbutton->setAutoDefault(FALSE);
  PRIVATE(this)->donebutton->setAutoDefault(FALSE);

  buttonlayout->addWidget(PRIVATE(this)->applybutton);
  buttonlayout->addWidget(PRIVATE(this)->resetbutton);
  buttonlayout->addWidget(PRIVATE(this)->donebutton);

  PRIVATE(this)->instantupdate->setText("Continuous update");
  PRIVATE(this)->applybutton->setText("Apply");
  PRIVATE(this)->donebutton->setText("Done");
  PRIVATE(this)->resetbutton->setText("Reset");

  this->setMode(PRIVATE(this)->mode);


  connect(PRIVATE(this)->colormodelist, SIGNAL(activated(int)), 
          PRIVATE(this)->curveview, SLOT(changeColorMode(int)));
  connect(PRIVATE(this)->curvetypelist, SIGNAL(activated(int)),
          PRIVATE(this), SLOT(changeCurveMode(int)));
  connect(PRIVATE(this)->constantvalue, SIGNAL(returnPressed(void)),
          PRIVATE(this), SLOT(setConstantValue(void)));

  connect(PRIVATE(this)->instantupdate, SIGNAL(clicked()), 
          PRIVATE(this), SLOT(toggleUpdate()));
  connect(PRIVATE(this)->applybutton, SIGNAL(clicked(void)), 
          PRIVATE(this), SLOT(apply(void)));
  connect(PRIVATE(this)->donebutton, SIGNAL(clicked(void)), 
          PRIVATE(this), SLOT(done(void)));
  connect(PRIVATE(this)->curveview, SIGNAL(curveChanged(void)),
          PRIVATE(this), SLOT(updateColorLabels(void)));
  connect(PRIVATE(this)->resetbutton, SIGNAL(clicked()), 
          PRIVATE(this), SLOT(reset(void)));
}

SoQtColorTableEditor::~SoQtColorTableEditor()
{
  delete PRIVATE(this);
}

void 
SoQtColorTableEditor::getColors(uint8_t * color, int num) const
{
  PRIVATE(this)->curveview->getColors(color, num);
}

void 
SoQtColorTableEditor::setColors(uint8_t * color, int num)
{
  PRIVATE(this)->curvetypelist->setCurrentIndex(CurveView::FREE);
  PRIVATE(this)->curveview->setColors(color, num);
  if (PRIVATE(this)->callBack) {
    PRIVATE(this)->callBack(this, PRIVATE(this)->callbackData);
  }
}

void
SoQtColorTableEditor::setChangeCallback(SoQtColorTableEditor::ChangeCB * cb,
                                        void * userData)
{
  PRIVATE(this)->callBack = cb;
  PRIVATE(this)->callbackData = userData;
  PRIVATE(this)->curveview->setCallBack(PRIVATE(this)->curveCallBack, PRIVATE(this));
  if (cb) { cb(this, userData); }
}

SoQtColorTableEditor::Mode
SoQtColorTableEditor::getMode() const
{
  return PRIVATE(this)->mode;
}

void
SoQtColorTableEditor::setMode(Mode mode) 
{
  QPixmap pm(16,16);
  PRIVATE(this)->mode = mode;
  PRIVATE(this)->curveview->setMode(mode);

  PRIVATE(this)->colormodelist->clear();

  switch(mode) {
  case SoQtColorTableEditor::LUMINANCE:
  case SoQtColorTableEditor::LUMINANCE_ALPHA:
    pm.fill(Qt::gray);
    PRIVATE(this)->colormodelist->addItem(pm, "Gray");
    break;

  case SoQtColorTableEditor::RGB:
  case SoQtColorTableEditor::RGBA:
    pm.fill(Qt::red);
    PRIVATE(this)->colormodelist->addItem(pm, "Red");
    pm.fill(Qt::green);
    PRIVATE(this)->colormodelist->addItem(pm, "Green");
    pm.fill(Qt::blue);
    PRIVATE(this)->colormodelist->addItem(pm, "Blue");
    break;
  }

  if ((mode == SoQtColorTableEditor::LUMINANCE_ALPHA) ||
      (mode == SoQtColorTableEditor::RGBA)) {
    pm.fill(Qt::white);
    PRIVATE(this)->colormodelist->addItem(pm, "Alpha");
  }
}

#undef PRIVATE
#undef PUBLIC


