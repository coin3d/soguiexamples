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
