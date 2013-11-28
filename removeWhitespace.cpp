#include "HelpMog_RemoveWhitespace.h"

void p_HelpMog_RemoveExtraneousWhitespaceCharacters( FILE *p_input, FILE *p_output )
{
  char character;
  bool whitespaceCharacterInput = false, printingCharacterInput = false;
  while( fscanf( p_input, "%c", &character ) != EOF )
    if(( character != ' ' ) && ( character != '\t' ) && ( character != '\n' ))
    {
      if( whitespaceCharacterInput )
      {
        fprintf( p_output, " " );
        whitespaceCharacterInput = false;
      }
      else
        printingCharacterInput = true;
      fprintf( p_output, "%c", character );
    }
    else
      if( character == '\n' )
      {
        fprintf( p_output, "\n" );
        whitespaceCharacterInput = false;
        printingCharacterInput = false;
      }
      else
        if( printingCharacterInput )
          whitespaceCharacterInput = true;
}
