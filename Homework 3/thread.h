#ifndef THREAD_H
#define THREAD_H

//For multithreading
#include <windows.h>


//Function for creating threads
//Use case: thatFunctionHandle = (HANDLE)_beginthreadex(0, 0, &aFunction;, 0, 0, 0);
//          WaitForSingleObject(thatFunctionHandle, INFINITE);
uintptr_t _beginthreadex( 
   void *security,
   unsigned stack_size,
   unsigned ( *start_address )( void * ),
   void *arglist,
   unsigned initflag,
   unsigned *thrdaddr 
);

// //A simpler function for creating thread that is sufficient for this program
// // type(DWORD WINAPI)  function is the method that we want to have run parallely
// // type(LPDWORD)  threadID is the thread ID;
// HANDLE WINAPI simpleCreateThread(LPTHREAD_START_ROUTINE function, LPDWORD threadId){
//     return CreateThread(0, 0, function, 0, 0, threadId);
// }



// HANDLE WINAPI CreateThread(
// __in_opt LPSECURITY_ATTRIBUTES lpThreadAttributes,
// __in SIZE_T dwStackSize,
// __in LPTHREAD_START_ROUTINE lpStartAddress, 
// __in_opt LPVOID lpParameter, 
// __in DWORD dwCreationFlags,
// __out_opt LPDWORD lpThreadId 
// ); 

#endif