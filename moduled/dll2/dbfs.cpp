/* Copyright (C) 2006 Artjom V. Loenenko aka tikkeri */
// dbfs.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

/* begin tikkeri's code */
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


int mif( void* a)
{
	puts( "*** mif call ***" );
	printf( "mif arg is: %#lx\n", a );
	putchar( '\n' );

	return 0;
}

int mtf( char* s )
{
	puts( "*** mtf call ***" );

	if( s )
	{
		printf( "mtf arg is: '''%s'''\n", s );
	}

	putchar( '\n' );

	return 0;
}


struct module_desc md = { "Descr", "dll2.dll", "jartur,tikkeri", mif, mtf };
/* end tikkeri's code */



struct 
{
    void* hello;
} dll_interface ;

void hello();

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch( ul_reason_for_call )
    {
        case DLL_PROCESS_ATTACH:
                printf( "DLL loaded sucesfully!\n" );
                dll_interface.hello = &hello;
                break;
            
        case DLL_PROCESS_DETACH:
                printf( "DLL Is Being Unloaded!\n" );
                getchar();
                break;
    }

    return TRUE;
}

void hello()
{
    printf( "Hello, World! From DLL2!! IT WORKS! HELL YEAH! ;)\n" );
    getchar();
}

/*void* get_interface()
{
    return &dll_interface;
}*/

