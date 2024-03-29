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

#include "VolumeRenderHandler.h"
#include "ui_SoVolumeRender.h"

#include <cassert>

#include <qvalidator.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qslider.h>
#include <qlabel.h>

#include <VolumeViz/nodes/SoVolumeRender.h>
#include <VolumeViz/nodes/SoVolumeData.h>

#include "utility.h"

// *************************************************************************

VolumeRenderHandler::VolumeRenderHandler(SoVolumeRender * rendernode,
                                         SoVolumeData * volumedatanode,
                                         QWidget * parent)
  : QDialog(parent)
{
  this->node = rendernode;
  // FIXME: should better place a sensor on it and detect when the
  // node is dying. 20021211 mortene.
  this->node->ref();

  this->vdnode = volumedatanode;
  this->vdnode->ref();

  this->ctrl = new Ui::SoVolumeRenderCtrl;
  this->ctrl->setupUi(this);
  this->show();

  this->initGUI();
}

VolumeRenderHandler::~VolumeRenderHandler()
{
  this->node->unref();
  this->vdnode->unref();
}

void
VolumeRenderHandler::initGUI(void)
{
  SbVec3s dimension;
  void * data;
  SoVolumeData::DataType type;
  SbBool ok = this->vdnode->getVolumeData(dimension, data, type);

  // "numSlices" slider & edit

  this->ctrl->numSlicesSlider->setMinimum(0);
  const unsigned short maxdim = SbGuiExMax(dimension[0], SbGuiExMax(dimension[1], dimension[2]));
  this->ctrl->numSlicesSlider->setMaximum(maxdim);
  this->ctrl->numSlicesSlider->setValue(this->node->numSlices.getValue());

  QObject::connect(this->ctrl->numSlicesSlider, SIGNAL(valueChanged(int)),
                   this, SLOT(numSlicesSliderUpdate(int)));


  QString s;
#if QT_VERSION >= 0x050E00
  s = QString("%1").arg(this->node->numSlices.getValue());
#else
  s.sprintf("%d", this->node->numSlices.getValue());
#endif
  this->ctrl->numSlicesEdit->setText(s);

  QObject::connect(this->ctrl->numSlicesEdit, SIGNAL(returnPressed()),
                   this, SLOT(numSlicesEditUpdate()));

  // numSlicesControl combobox

  this->ctrl->numSlicesControlCombo->setCurrentIndex(this->node->numSlicesControl.getValue());

  QObject::connect(this->ctrl->numSlicesControlCombo, SIGNAL(activated(int)),
                   this, SLOT(numSlicesControlUpdate(int)));

  if (this->node->numSlicesControl.getValue() == SoVolumeRender::ALL) {
    this->ctrl->numSlicesEdit->setEnabled(FALSE);
    this->ctrl->numSlicesSlider->setEnabled(FALSE);
  }

  // interpolation combobox

  this->ctrl->interpolationCombo->setCurrentIndex(this->node->interpolation.getValue());

  QObject::connect(this->ctrl->interpolationCombo, SIGNAL(activated(int)),
                   this, SLOT(interpolationUpdate(int)));

  // composition combobox

  this->ctrl->compositionCombo->setCurrentIndex(this->node->composition.getValue());

  QObject::connect(this->ctrl->compositionCombo, SIGNAL(activated(int)),
                   this, SLOT(compositionUpdate(int)));

  // viewAlignedSlices checkbox

  this->ctrl->viewAlignedSlicesCheckBox->setChecked(this->node->viewAlignedSlices.getValue());

  QObject::connect(this->ctrl->viewAlignedSlicesCheckBox, SIGNAL(stateChanged(int)),
                   this, SLOT(viewAlignedSlicesCheckBoxUpdate(int)));

  // Not in use yet -- 3D textures are not supported.
  this->ctrl->viewAlignedSlicesCheckBox->setEnabled(FALSE);
}


void
VolumeRenderHandler::numSlicesSliderUpdate(int val)
{
  this->node->numSlices = val;

  QString s;
#if QT_VERSION >= 0x050E00
  s = QString("%1").arg(val);
#else
  s.sprintf("%d", val);
#endif
  this->ctrl->numSlicesEdit->setText(s);
}

void
VolumeRenderHandler::numSlicesEditUpdate(void)
{
  this->node->numSlices = this->ctrl->numSlicesEdit->text().toInt();

  this->ctrl->numSlicesSlider->setValue(this->node->numSlices.getValue());
}

void
VolumeRenderHandler::numSlicesControlUpdate(int idx)
{
  this->node->numSlicesControl = idx;

  const SbBool is_all = this->node->numSlicesControl.getValue() == SoVolumeRender::ALL;
  this->ctrl->numSlicesEdit->setEnabled(!is_all);
  this->ctrl->numSlicesSlider->setEnabled(!is_all);
  this->ctrl->numSlicesLabel->setEnabled(!is_all);
}

void
VolumeRenderHandler::interpolationUpdate(int idx)
{
  this->node->interpolation = idx;
}

void
VolumeRenderHandler::compositionUpdate(int idx)
{
  this->node->composition = idx;
}

void
VolumeRenderHandler::viewAlignedSlicesCheckBoxUpdate(int idx)
{
  if (idx == Qt::PartiallyChecked) return;
  this->node->viewAlignedSlices = (idx == Qt::Checked) ? TRUE : FALSE;
}
