/**************************************************************************\
 *
 *  This file is part of a set of demo programs for the Coin library.
 *  Copyright (C) 2000-2001 by Systems in Motion. All rights reserved.
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
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  http://www.sim.no support@sim.no Voice: +47 22114160 Fax: +47 22207097
 *
\**************************************************************************/
// File: MooList.h

#ifndef MOO_LIST_H
#define MOO_LIST_H

template <class generic> class MooList
{

public:

	template <class T> struct MooListItem
	{
		T item;
		MooListItem * next;
		MooListItem * prev;
	};

	typedef bool find( generic item, void * data );

	MooList( void );
    ~MooList( void );

	bool start( void );
	bool end( void );

	bool insert( generic item );
	bool append( generic item );

	bool remove( void );
	bool remove( generic item );

	bool search( generic item );
	bool search( find * function, void * data );

	void empty( void );

	unsigned int length( void );

	bool next( void );
	bool prev( void );

	generic get( void );
	generic get( unsigned int index );
    //generic operator[]( unsigned int index );
	unsigned int index( void );

private:

	MooListItem<generic> * first;
	MooListItem<generic> * current;
	unsigned int count;
	unsigned int currentIndex;
};

#endif // !MOO_LIST_H
