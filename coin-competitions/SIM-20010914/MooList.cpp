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
// File: MooList.cpp

#ifndef MOO_LIST_CPP
#define MOO_LIST_CPP

#include "MooList.h"

template <class generic> MooList<generic>::MooList( void )
{
	
  this->first = new MooListItem<generic>;
  this->first->next = this->first;
  this->first->prev = this->first;

  this->current = this->first;
  this->count = 0;
  this->currentIndex = -1;
}

template <class generic> MooList<generic>::~MooList( void )
{
  this->empty( );
  delete this->first;
}

template <class generic> inline bool MooList<generic>::start( void )
{
  this->current = this->first->next;

  this->currentIndex = ( this->count > 0 ) ? 0 : -1;

  return ( this->current != this->first );
}

template <class generic> inline bool MooList<generic>::end( void )
{
	
  this->current = this->first->prev;
  this->currentIndex = this->count - 1;
  return ( this->current != this->first );

}

template <class generic> bool MooList<generic>::remove( void )
{
  if ( this->current == this->first )
    return false;

  MooListItem<generic> * del = this->current;

  del->next->prev = del->prev;
  del->prev->next = del->next;
  this->current = del->prev;

  delete del;

  this->count--;
  this->currentIndex--;

  return true;

}

template <class generic> bool MooList<generic>::remove( generic item )
{
	
  if ( this->search( item ) )
    return this->remove( );

  return false;

}

template <class generic> bool MooList<generic>::insert( generic item )
{
	
  MooListItem<generic> * ins = 0L;
  ins = new MooListItem<generic>;

  if ( ins ) {
	
    ins->item = item;

    ins->prev = this->current;
    ins->next = this->current->next;
    ins->next->prev = ins;
    ins->prev->next = ins;
    
    this->count++;
    this->current = ins;
    this->currentIndex++;

    return true;

  }

  return false;

}

template<class generic> bool MooList<generic>::append( generic item )
{

  this->end( );
  return this->insert( item );

}

template<class generic> inline bool MooList<generic>::next( void )
{
	
  if ( this->current->next == this->first )
    return false;

  this->current = this->current->next;
  this->currentIndex++;

  return true;

}

template<class generic> inline bool MooList<generic>::prev( void )
{
	
  if ( this->current->prev == this->first )
    return false;

  this->current = this->current->prev;
  this->currentIndex--;

  return true;

}

template<class generic> bool MooList<generic>::search( generic item )
{

  this->start( );

  do {

    if ( this->current->item == item )
      return true;
   
  } while( this->next( ) );
  
  return false;

}

template<class generic> bool MooList<generic>::search( find * function, void * data )
{
	
  this->start( );

  if ( this->current == this->first )
    return false;

  do {

    if ( function( this->current->item, data ) )
      return true;

  } while ( this->next( ) );

  return false;

}

template<class generic> void MooList<generic>::empty( void )
{
  this->end( );
  while ( this->remove( ) ) {}
}

template<class generic> inline unsigned int MooList<generic>::length( void )
{
  return this->count;
}

template<class generic> inline generic MooList<generic>::get( void )
{
  return this->current->item;
}

template<class generic> generic MooList<generic>::get( unsigned int index )
{

  if ( this->currentIndex > index ) {

    while( ( this->currentIndex > index ) && this->prev( ) ) {}

  } else if ( this->currentIndex < index ) {

    while( ( this->currentIndex < index ) && this->next( ) ) {}

  }

  return this->current->item;

}

template<class generic> unsigned int MooList<generic>::index( void )
{
  return this->currentIndex;
}

#endif // !MOO_LIST_CPP
