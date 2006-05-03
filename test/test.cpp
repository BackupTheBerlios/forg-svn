// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

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

int _tmain(int argc, _TCHAR* argv[])
{
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

