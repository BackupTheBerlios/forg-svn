// dbfs.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

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

