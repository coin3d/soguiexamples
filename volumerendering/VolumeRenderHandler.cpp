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

#include "VolumeRenderHandler.h"
#include "ui_SoVolumeRender_ctrl.h"

#include <assert.h>

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
SoVolumeRender_ctrl::SoVolumeRender_ctrl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SoVolumeRender_ctrl)
{
    ui->setupUi(this);
}


SoVolumeRender_ctrl::~SoVolumeRender_ctrl()
{
    delete ui;
}

VolumeRenderHandler::VolumeRenderHandler(SoVolumeRender * rendernode,
                                         SoVolumeData * volumedatanode,
                                         QWidget * parent)
{
  this->node = rendernode;
  // FIXME: should better place a sensor on it and detect when the
  // node is dying. 20021211 mortene.
  this->node->ref();

  this->vdnode = volumedatanode;
  this->vdnode->ref();

  this->ctrl = new SoVolumeRender_ctrl(parent);
  this->ctrl->show();

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

  this->ctrl->ui->numSlicesSlider->setMinValue(0);
  const unsigned short maxdim = SbGuiExMax(dimension[0], SbGuiExMax(dimension[1], dimension[2]));
  this->ctrl->ui->numSlicesSlider->setMaxValue(maxdim);
  this->ctrl->ui->numSlicesSlider->setValue(this->node->numSlices.getValue());

  QObject::connect(this->ctrl->ui->numSlicesSlider, SIGNAL(valueChanged(int)),
                   this, SLOT(numSlicesSliderUpdate(int)));


  QString s;
  s.sprintf("%d", this->node->numSlices.getValue());
  this->ctrl->ui->numSlicesEdit->setText(s);

  QObject::connect(this->ctrl->ui->numSlicesEdit, SIGNAL(returnPressed()),
                   this, SLOT(numSlicesEditUpdate()));

  // numSlicesControl combobox

  this->ctrl->ui->numSlicesControlCombo->setCurrentItem(this->node->numSlicesControl.getValue());

  QObject::connect(this->ctrl->ui->numSlicesControlCombo, SIGNAL(activated(int)),
                   this, SLOT(numSlicesControlUpdate(int)));

  if (this->node->numSlicesControl.getValue() == SoVolumeRender::ALL) {
    this->ctrl->ui->numSlicesEdit->setEnabled(FALSE);
    this->ctrl->ui->numSlicesSlider->setEnabled(FALSE);
  }

  // interpolation combobox

  this->ctrl->ui->interpolationCombo->setCurrentItem(this->node->interpolation.getValue());

  QObject::connect(this->ctrl->ui->interpolationCombo, SIGNAL(activated(int)),
                   this, SLOT(interpolationUpdate(int)));

  // composition combobox

  this->ctrl->ui->compositionCombo->setCurrentItem(this->node->composition.getValue());

  QObject::connect(this->ctrl->ui->compositionCombo, SIGNAL(activated(int)),
                   this, SLOT(compositionUpdate(int)));

  // viewAlignedSlices checkbox

  this->ctrl->ui->viewAlignedSlicesCheckBox->setChecked(this->node->viewAlignedSlices.getValue());

  QObject::connect(this->ctrl->ui->viewAlignedSlicesCheckBox, SIGNAL(stateChanged(int)),
                   this, SLOT(viewAlignedSlicesCheckBoxUpdate(int)));

  // Not in use yet -- 3D textures are not supported.
  this->ctrl->ui->viewAlignedSlicesCheckBox->setEnabled(FALSE);
}


void
VolumeRenderHandler::numSlicesSliderUpdate(int val)
{
  this->node->numSlices = val;

  QString s;
  s.sprintf("%d", val);
  this->ctrl->ui->numSlicesEdit->setText(s);
}

void
VolumeRenderHandler::numSlicesEditUpdate(void)
{
  this->node->numSlices = this->ctrl->ui->numSlicesEdit->text().toInt();

  this->ctrl->ui->numSlicesSlider->setValue(this->node->numSlices.getValue());
}

void
VolumeRenderHandler::numSlicesControlUpdate(int idx)
{
  this->node->numSlicesControl = idx;

  const SbBool is_all = this->node->numSlicesControl.getValue() == SoVolumeRender::ALL;
  this->ctrl->ui->numSlicesEdit->setEnabled(!is_all);
  this->ctrl->ui->numSlicesSlider->setEnabled(!is_all);
  this->ctrl->ui->numSlicesLabel->setEnabled(!is_all);
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
  if (idx == QCheckBox::NoChange) return;
  this->node->viewAlignedSlices = (idx == QCheckBox::On) ? TRUE : FALSE;
}
