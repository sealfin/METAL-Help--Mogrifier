#ifndef HelpMog_CharacterQueue_h

#define HelpMog_CharacterQueue_h

#include "seal_charQueue.h"

class HelpMog_CharacterQueue : public seal_CharQueue
{
  public:
    void p_Print( FILE *p )
    {
      if( f_IsEmpty())
        throw "HelpMog_CharacterQueue::p_Print - f_IsEmpty() == true.";
      if( p == NULL )
        throw "HelpMog_CharacterQueue::p_Print - p == NULL.";
      struct seal_QueueNode<char> *n = m_first;
      do
      {
        fprintf( p, "%c", n->m_content );
        n = n->m_n;
      }
      while( n != NULL );
    }
};

#endif
