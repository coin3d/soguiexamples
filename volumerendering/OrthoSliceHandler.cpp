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

#include "OrthoSliceHandler.h"
#include <SoOrthoSlice_ctrl.h>
#include "utility.h"

#include <assert.h>

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
{
  this->node = orthonode;
  // FIXME: should better place a sensor on it and detect when the
  // node is dying. 20021211 mortene.
  this->node->ref();

  this->vdnode = volumedatanode;
  this->vdnode->ref();

  this->ctrl = new SoOrthoSlice_ctrl(parent);
  this->ctrl->show();

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

  this->ctrl->sliceNumberSlider->setMinValue(0);
  const int maxsliceidx = dimension[this->node->axis.getValue()] - 1;
  this->ctrl->sliceNumberSlider->setMaxValue(maxsliceidx);
  this->ctrl->sliceNumberSlider->setValue(this->node->sliceNumber.getValue());

  QObject::connect(this->ctrl->sliceNumberSlider, SIGNAL(valueChanged(int)),
                   this, SLOT(sliceNumberSliderUpdate(int)));


  QString s;
  s.sprintf("%d", this->node->sliceNumber.getValue());
  this->ctrl->sliceNumberEdit->setText(s);

  QObject::connect(this->ctrl->sliceNumberEdit, SIGNAL(returnPressed()),
                   this, SLOT(sliceNumberEditUpdate()));

  // axis combobox

  this->ctrl->axisCombo->setCurrentItem(this->node->axis.getValue());

  QObject::connect(this->ctrl->axisCombo, SIGNAL(activated(int)),
                   this, SLOT(axisUpdate(int)));

  // interpolation combobox

  this->ctrl->interpolationCombo->setCurrentItem(this->node->interpolation.getValue());

  QObject::connect(this->ctrl->interpolationCombo, SIGNAL(activated(int)),
                   this, SLOT(interpolationUpdate(int)));

  // alphaUse combobox

  this->ctrl->alphaUseCombo->setCurrentItem(this->node->alphaUse.getValue());

  QObject::connect(this->ctrl->alphaUseCombo, SIGNAL(activated(int)),
                   this, SLOT(alphaUseUpdate(int)));

  // clipping checkbox

  this->ctrl->clippingCheckBox->setChecked(this->node->clipping.getValue());

  QObject::connect(this->ctrl->clippingCheckBox, SIGNAL(stateChanged(int)),
                   this, SLOT(clippingCheckBoxUpdate(int)));

  // clippingSide combobox

  this->ctrl->clippingSideCombo->setCurrentItem(this->node->clippingSide.getValue());

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

  this->ctrl->sliceNumberSlider->setMaxValue(maxsliceidx);
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
  if (idx == QButton::NoChange) return;
  this->node->clipping = (idx == QButton::On) ? TRUE : FALSE;
}

void
OrthoSliceHandler::clippingSideUpdate(int idx)
{
  this->node->clippingSide = idx;
}
