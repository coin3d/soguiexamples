#ifndef SIMVOLEON_TESTCODE_UTILITY_H
#define SIMVOLEON_TESTCODE_UTILITY_H

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

#include <Inventor/SbBasic.h>

// *************************************************************************

template <class Type>
inline Type SbGuiExMax( const Type A, const Type B ) {
  return (A < B) ? B : A;
}

template <class Type>
inline Type SbGuiExMin( const Type A, const Type B ) {
  return (A < B) ? A : B;
}

// *************************************************************************

class SbVec3s;
extern uint8_t * generate8bitVoxelSet(SbVec3s & dim);

// *************************************************************************

#endif // SIMVOLEON_TESTCODE_UTILITY_H
