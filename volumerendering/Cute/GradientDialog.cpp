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
#define PRIVATE(p) (p->pimpl)
#define PUBLIC(p) (p->pub)

#include <qlayout.h>
#include <qimage.h>
#include <QGraphicsView>
#include <QList>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qlabel.h>
#include <qfiledialog.h>
#include <qpushbutton.h>
#include <qsizepolicy.h>

#include "gradientp/GradientView.h"
#include "gradientp/SoQtGradientDialogP.h"
#include "SoQtGradientDialog.h"

//#include "moc_SoQtGradientDialogP.icc"

QString * SoQtGradientDialogP::defaultdir = NULL;

SoQtGradientDialogP::SoQtGradientDialogP(SoQtGradientDialog * publ)
{
  PUBLIC(this) = publ;
  this->updatecontinuously = FALSE;
  this->lastreportedgradient = NULL;
}

SoQtGradientDialogP::~SoQtGradientDialogP()
{
  delete this->lastreportedgradient;
}

void
SoQtGradientDialogP::contupdateClicked()
{
  this->updatecontinuously = this->contupdate->isChecked();
  this->invokeChangeCallback();
}

void
SoQtGradientDialogP::invokeChangeCallback()
{  
  if (this->changeCallBack) {
    const Gradient & g = this->gradview->getGradient();

    if (!this->lastreportedgradient) {
      this->lastreportedgradient = new Gradient(g);
    }
    else {
      if (*this->lastreportedgradient == g) { return; }
    }

    *this->lastreportedgradient = g;
    this->changeCallBack(g, this->changeCallBackData);
  }
}

void
SoQtGradientDialogP::gradientCallBack(const Gradient & g, void * userData)
{
  SoQtGradientDialogP * thisp = (SoQtGradientDialogP *)userData;
  if (thisp->updatecontinuously) { thisp->invokeChangeCallback(); }
}

void
SoQtGradientDialogP::done()
{
  if (!this->updatecontinuously) { this->invokeChangeCallback(); }
}

void
SoQtGradientDialogP::resetGradient()
{
  this->gradview->setGradient(this->gradientcopy);
  this->saveCurrent();
  this->invokeChangeCallback();
}

void 
SoQtGradientDialogP::loadGradient()
{
  this->filedialog->setFileMode(QFileDialog::ExistingFile);

  if (this->filedialog->exec()) {
    QStringList filenames = this->filedialog->selectedFiles();
    if (!filenames.isEmpty()) {
      QString filename = filenames[0];
      this->saveCurrent();
      Gradient grad(filename);
      QString dir = this->filedialog->directory().path();

      QString description = filename.remove(0, dir.length() + 1);
      PUBLIC(this)->addGradient(grad, description);

      if (SoQtGradientDialogP::defaultdir == NULL) { // set the static defaultdir to the first dir chosen
        SoQtGradientDialogP::defaultdir = new QString(dir);
      }
    }
  }
}

void 
SoQtGradientDialogP::saveGradient()
{
  this->filedialog->setFileMode(QFileDialog::AnyFile);

  if (this->filedialog->exec()) {
    QStringList filenames = this->filedialog->selectedFiles();
    if (!filenames.isEmpty()) {
        QString filename = filenames[0];
      if (!filename.contains(this->filetype)) {
        filename.append(this->filetype);
      }
      Gradient grad = this->gradview->getGradient();
      grad.save(filename);
    
      QString dir = this->filedialog->directory().path();
      QString description = filename.remove(0, dir.length() + 1);
      this->gradientlist->setItemText(this->old_index, description);
      this->gradientlist->setItemData(this->old_index, grad.getImage(60, 16, QImage::Format_ARGB32_Premultiplied), Qt::DecorationRole);
      if (SoQtGradientDialogP::defaultdir == NULL) { // set the static defaultdir to the first dir chosen
        SoQtGradientDialogP::defaultdir = new QString(dir);
      }
    }
  }
}

void 
SoQtGradientDialogP::chooseGradient(int i)
{
  this->saveCurrent();
  this->gradview->setGradient(this->gradients[i]);
  this->gradientcopy = this->gradients[i];
  this->old_index = i;
  this->invokeChangeCallback();
}

void SoQtGradientDialogP::saveCurrent()
{
  const Gradient & grad = this->gradview->getGradient();
  QString description = this->gradientlist->itemText(this->old_index);
  this->gradientlist->setItemText(this->old_index, description);
  this->gradientlist->setItemData(this->old_index, grad.getImage(60, 16, QImage::Format_ARGB32_Premultiplied), Qt::DecorationRole);
  this->gradients[old_index] = grad;
}

SoQtGradientDialog::SoQtGradientDialog(const Gradient & grad,
                                       QWidget * parent, 
                                       bool modal,
                                       const char* name)
: QDialog(parent)
{
  setWindowTitle(name);
  setModal(modal);
  PRIVATE(this) = new SoQtGradientDialogP(this);
  PRIVATE(this)->changeCallBack = NULL;
  PRIVATE(this)->changeCallBackData = NULL;

  QSizePolicy sizepolicy;
  sizepolicy.setVerticalPolicy(QSizePolicy::MinimumExpanding);
  this->setSizePolicy(sizepolicy);

  PRIVATE(this)->filetype = ".grad";
  PRIVATE(this)->filedialog = new QFileDialog(this);
  if (SoQtGradientDialogP::defaultdir) {
    PRIVATE(this)->filedialog->setDirectory(*SoQtGradientDialogP::defaultdir);
  }
  auto scene = new QGraphicsScene;
  PRIVATE(this)->gradview = new GradientView(scene, grad, this, "GradientView");
  scene->setParent(PRIVATE(this)->gradview);
  PRIVATE(this)->gradview->setFrameStyle(QFrame::Sunken);

  PRIVATE(this)->gradientlist = new QComboBox(this);
  PRIVATE(this)->gradientlist->setObjectName("gradientlist");
  PRIVATE(this)->old_index = 0;
  this->addGradient(grad, "no filename specified");
  PRIVATE(this)->gradientlist->hide();

  QGridLayout * toplayout = new QGridLayout(this);
  //toplayout->setSpacing(5);
  //toplayout->setMargin(10);
  toplayout->addWidget(PRIVATE(this)->gradview, 0, 0, 1, 3);

  QHBoxLayout * buttonlayout = new QHBoxLayout();
  toplayout->addLayout(buttonlayout, 2, 0);

  QVBoxLayout * loadsaveLayout = new QVBoxLayout();
  buttonlayout->addLayout(loadsaveLayout);

  QHBoxLayout * contupdatelayout = new QHBoxLayout();
  contupdatelayout->setAlignment(Qt::AlignRight | Qt::AlignBottom);
  toplayout->addLayout(contupdatelayout, 1, 2);

  QHBoxLayout * applyresetLayout = new QHBoxLayout();
  applyresetLayout->setAlignment(Qt::AlignBottom | Qt::AlignRight);
  toplayout->addLayout(applyresetLayout, 2, 2);

  loadsaveLayout->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
  loadsaveLayout->addWidget(PRIVATE(this)->gradientlist, 0, Qt::AlignLeft);

  QPushButton * loadbutton = new QPushButton(this);
  loadbutton->setObjectName("loadbutton");
  loadbutton->setText("Load");
  loadsaveLayout->addWidget(loadbutton, 0, Qt::AlignLeft);

  QPushButton * savebutton = new QPushButton(this);
  savebutton->setObjectName("savebutton");
  savebutton->setText("Save");
  loadsaveLayout->addWidget(savebutton, 0, Qt::AlignLeft);

  PRIVATE(this)->contupdate = new QCheckBox(this);
  PRIVATE(this)->contupdate->setText("Continuous update ");
  PRIVATE(this)->contupdate->setChecked(FALSE);

  contupdatelayout->addWidget(PRIVATE(this)->contupdate);

  PRIVATE(this)->applybutton = new QPushButton(this);
  PRIVATE(this)->applybutton->setText("Apply");
  applyresetLayout->addWidget(PRIVATE(this)->applybutton);

  QPushButton * resetbutton = new QPushButton(this);
  resetbutton->setText("Reset");
  applyresetLayout->addWidget(resetbutton);

  QPushButton * donebutton = new QPushButton(this);
  donebutton->setText("Done");
  applyresetLayout->addWidget(donebutton);

  connect(loadbutton, SIGNAL(clicked()), PRIVATE(this), SLOT(loadGradient()));
  connect(savebutton, SIGNAL(clicked()), PRIVATE(this), SLOT(saveGradient()));
  connect(PRIVATE(this)->applybutton, SIGNAL(clicked()), PRIVATE(this), SLOT(invokeChangeCallback()));
  connect(resetbutton, SIGNAL(clicked()), PRIVATE(this), SLOT(resetGradient()));
  connect(donebutton, SIGNAL(clicked()), PRIVATE(this), SLOT(done()));
  connect(donebutton, SIGNAL(clicked()), this, SLOT(accept()));
  connect(PRIVATE(this)->gradientlist, SIGNAL(activated(int)), PRIVATE(this), SLOT(chooseGradient(int)));
  connect(PRIVATE(this)->contupdate, SIGNAL(clicked()), PRIVATE(this), SLOT(contupdateClicked()));
}

SoQtGradientDialog::~SoQtGradientDialog()
{
  delete this->pimpl;
}

void SoQtGradientDialog::addGradient(const Gradient & grad, QString description)
{
  PRIVATE(this)->gradientcopy = grad;

  if (PRIVATE(this)->changeCallBack) {
    PRIVATE(this)->gradientcopy.setChangeCallback(PRIVATE(this)->gradientCallBack,
                                                  PRIVATE(this));
  }

  PRIVATE(this)->gradients.append(PRIVATE(this)->gradientcopy);
  PRIVATE(this)->gradientlist->addItem(description);
  PRIVATE(this)->old_index = PRIVATE(this)->gradientlist->count() - 1;
  PRIVATE(this)->gradientlist->setItemData(PRIVATE(this)->old_index, PRIVATE(this)->gradientcopy.getImage(60, 16, QImage::Format_ARGB32_Premultiplied), Qt::DecorationRole);
  
  PRIVATE(this)->gradientlist->setCurrentIndex(PRIVATE(this)->old_index);
  PRIVATE(this)->gradview->setGradient(PRIVATE(this)->gradientcopy);
  PRIVATE(this)->gradientlist->show();

  PRIVATE(this)->invokeChangeCallback();
}

const Gradient & SoQtGradientDialog::getGradient() const
{
  return PRIVATE(this)->gradview->getGradient();
}

void SoQtGradientDialog::setDataLimits(float min, float max)
{
  PRIVATE(this)->gradview->setDataLimits(min, max);
}

void SoQtGradientDialog::setChangeCallback(Gradient::ChangeCB * cb, void * userdata)
{
  PRIVATE(this)->changeCallBack = cb;
  PRIVATE(this)->changeCallBackData = userdata;
  PRIVATE(this)->gradientcopy.setChangeCallback(PRIVATE(this)->gradientCallBack, PRIVATE(this));
  PRIVATE(this)->gradview->setChangeCallback(PRIVATE(this)->gradientCallBack, PRIVATE(this));
}

void 
SoQtGradientDialog::setContinuousNotification(SbBool yes)
{
  PRIVATE(this)->contupdate->setChecked(yes);
  PRIVATE(this)->updatecontinuously = yes;
}

SbBool 
SoQtGradientDialog::getContinuousNotification(void) const
{
  return PRIVATE(this)->updatecontinuously;
}

void 
SoQtGradientDialog::alwaysContinuousUpdates(SbBool yes)
{
  PRIVATE(this)->updatecontinuously = yes;
  PRIVATE(this)->contupdate->setChecked(yes);

  if (yes) {
    PRIVATE(this)->contupdate->hide();
    PRIVATE(this)->applybutton->hide();
  }
  else {
    PRIVATE(this)->contupdate->show();
    PRIVATE(this)->applybutton->show();
  }
}

#undef PRIVATE
#undef PUBLIC
