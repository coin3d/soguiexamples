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
