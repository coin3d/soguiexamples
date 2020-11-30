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

#include "OrthoSliceHandler.h"
#include "ui_SoOrthoSlice.h"
#include "utility.h"

#include <cassert>

#include <qvalidator.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qslider.h>

#include <VolumeViz/nodes/SoOrthoSlice.h>
#include <VolumeViz/nodes/SoVolumeData.h>

// *************************************************************************

OrthoSliceHandler::OrthoSliceHandler(SoOrthoSlice * orthonode,
                                     SoVolumeData * volumedatanode,
                                     QWidget * parent)
  : QDialog(parent)
{
  this->node = orthonode;
  // FIXME: should better place a sensor on it and detect when the
  // node is dying. 20021211 mortene.
  this->node->ref();

  this->vdnode = volumedatanode;
  this->vdnode->ref();

  this->ctrl = new Ui::SoOrthoSliceCtrl;
  this->ctrl->setupUi(this);
  this->show();

  this->initGUI();
}

OrthoSliceHandler::~OrthoSliceHandler()
{
  this->node->unref();
  this->vdnode->unref();
}

void
OrthoSliceHandler::initGUI(void)
{
  SbVec3s dimension;
  void * data;
  SoVolumeData::DataType type;
  SbBool ok = this->vdnode->getVolumeData(dimension, data, type);

  // "sliceNumber" slider & edit

  this->ctrl->sliceNumberSlider->setMinimum(0);
  const int maxsliceidx = dimension[this->node->axis.getValue()] - 1;
  this->ctrl->sliceNumberSlider->setMaximum(maxsliceidx);
  this->ctrl->sliceNumberSlider->setValue(this->node->sliceNumber.getValue());

  QObject::connect(this->ctrl->sliceNumberSlider, SIGNAL(valueChanged(int)),
                   this, SLOT(sliceNumberSliderUpdate(int)));


  QString s;
  s.sprintf("%d", this->node->sliceNumber.getValue());
  this->ctrl->sliceNumberEdit->setText(s);

  QObject::connect(this->ctrl->sliceNumberEdit, SIGNAL(returnPressed()),
                   this, SLOT(sliceNumberEditUpdate()));

  // axis combobox

  this->ctrl->axisCombo->setCurrentIndex(this->node->axis.getValue());

  QObject::connect(this->ctrl->axisCombo, SIGNAL(activated(int)),
                   this, SLOT(axisUpdate(int)));

  // interpolation combobox

  this->ctrl->interpolationCombo->setCurrentIndex(this->node->interpolation.getValue());

  QObject::connect(this->ctrl->interpolationCombo, SIGNAL(activated(int)),
                   this, SLOT(interpolationUpdate(int)));

  // alphaUse combobox

  this->ctrl->alphaUseCombo->setCurrentIndex(this->node->alphaUse.getValue());

  QObject::connect(this->ctrl->alphaUseCombo, SIGNAL(activated(int)),
                   this, SLOT(alphaUseUpdate(int)));

  // clipping checkbox

  this->ctrl->clippingCheckBox->setChecked(this->node->clipping.getValue());

  QObject::connect(this->ctrl->clippingCheckBox, SIGNAL(stateChanged(int)),
                   this, SLOT(clippingCheckBoxUpdate(int)));

  // clippingSide combobox

  this->ctrl->clippingSideCombo->setCurrentIndex(this->node->clippingSide.getValue());

  QObject::connect(this->ctrl->clippingSideCombo, SIGNAL(activated(int)),
                   this, SLOT(clippingSideUpdate(int)));
}


void
OrthoSliceHandler::sliceNumberSliderUpdate(int val)
{
  this->node->sliceNumber = val;

  QString s;
  s.sprintf("%d", val);
  this->ctrl->sliceNumberEdit->setText(s);
}

void
OrthoSliceHandler::sliceNumberEditUpdate(void)
{
  this->node->sliceNumber = this->ctrl->sliceNumberEdit->text().toInt();

  this->ctrl->sliceNumberSlider->setValue(this->node->sliceNumber.getValue());
}

void
OrthoSliceHandler::axisUpdate(int idx)
{
  this->node->axis = idx;

  SbVec3s dimension;
  void * data;
  SoVolumeData::DataType type;
  SbBool ok = this->vdnode->getVolumeData(dimension, data, type);
  assert(ok);

  const uint32_t maxsliceidx = dimension[idx] - 1;

  this->node->sliceNumber =
    SbGuiExMin(this->node->sliceNumber.getValue(), maxsliceidx);

  this->ctrl->sliceNumberSlider->setMaximum(maxsliceidx);
  this->ctrl->sliceNumberSlider->setValue(this->node->sliceNumber.getValue());
}

void
OrthoSliceHandler::interpolationUpdate(int idx)
{
  this->node->interpolation = idx;
}

void
OrthoSliceHandler::alphaUseUpdate(int idx)
{
  this->node->alphaUse = idx;
}

void
OrthoSliceHandler::clippingCheckBoxUpdate(int idx)
{
  if (idx == Qt::PartiallyChecked) return;
  this->node->clipping = (idx == Qt::Checked) ? TRUE : FALSE;
}

void
OrthoSliceHandler::clippingSideUpdate(int idx)
{
  this->node->clippingSide = idx;
}
