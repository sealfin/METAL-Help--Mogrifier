#ifndef HelpMog_StringStack_h

#define HelpMog_StringStack_h

#include "seal_stack.h"
#include <stdio.h>

class HelpMog_StringStack : public seal_Stack<char*>
{
  public:
    void p_Print( FILE *p )
    {
      if( f_IsEmpty())
        throw "HelpMog_StringStack::p_Print - f_IsEmpty() == true.";
      if( p == NULL )
        throw "HelpMog_StringStack::p_Print - p == NULL.";
      struct seal_StackNode<char*> *n = m_top;
      do
      {
        fprintf( p, "%s", n->m_content );
        n = n->m_d;
      }
      while( n != NULL );
    }

  private:
    char *f_Assign( char *p )
    {
      if( p == NULL )
        throw "HelpMog_StringStack::p_Push - p == NULL.";
      return p;
    }
};

#endif
