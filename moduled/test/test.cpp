/* Copyright (C) 2006 Artjom V. Loenenko aka tikkeri */
// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"






/* next to be moved to the header */
typedef int (*module_init_func)(void*);
typedef int (*module_test_func)(char*);
typedef struct module_desc
{
	const char* descr;
	const char* name;
	const char* author;
	module_init_func mif;
	module_test_func mtf;
} module_desc_t;








class dll_object
{
public:
    dll_object( LPCTSTR dll );

    typedef void (*_hello)(void);
    _hello hello;

private:
    HMODULE dll_hmodule;
};

dll_object::dll_object( LPCTSTR dll )
{
    this->dll_hmodule = LoadLibrary( dll );
    if( this->dll_hmodule == NULL )
    {
        LPVOID lpMsgBuf;
        FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                       FORMAT_MESSAGE_FROM_SYSTEM | 
                       FORMAT_MESSAGE_IGNORE_INSERTS,
                       NULL,
                       GetLastError(),
                       MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                       (LPTSTR) &lpMsgBuf,
                       0,
                       NULL );

        MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error loading dll.", MB_ICONEXCLAMATION | MB_OK );
        throw 1;
    }
    else
    {
        this->hello = (_hello)GetProcAddress( dll_hmodule, "hello" );
    }
}


/* begins tikkeri's code */
/* testing... dont kick me =) */
int check_dll( char* str )
{
	void* dll;
	module_desc_t* md;

	fprintf( stderr, "Checking dll %s\n", str );
	dll = LoadLibraryA( str );

	if( ! dll )
	{
		fprintf( stderr, "Cant load file! [%s]\n", strerror( errno ));
		return -1;
	}

	md = (module_desc_t*)GetProcAddress( (HMODULE)dll, "md" );

	if( ! md )
	{
		fprintf( stderr, "Cant get md addr\n" );
	}
	else
	{
		md->author && printf( "md->author is\t%s\n", md->author );
		md->descr && printf( "md->descr is\t%s\n", md->descr );
		md->name && printf( "md->name is\t%s\n", md->name );
		md->mif &&	md->mif( (void*)0x6613 );
		md->mtf && 	md->mtf( "\n*** Pray to my god, sucker! ***" );
	}

	return 0;
}
/* end tikkeri's code */

int _tmain(int argc, _TCHAR* argv[])
{
	check_dll( "dll2.dll" );
	check_dll( "dll.dll" );

    dll_object* a = new dll_object( "dbfs" );
    a->hello();
    dll_object* b;
    try
    {
        b = new dll_object( "dll3" );
    }
    catch( int a )
    {
        b = new dll_object( "dll2" );
    }

    b->hello();
    a->hello();
}

