#include "HelpMog_mhlp2html.h"

void p_HelpMog_BeginParagraph( const bool p_mayBeginParagraph, FILE *p_output, bool *p_paragraphBegun, HelpMog_StringStack *p_stringStack );

void p_HelpMog_mhlp2html( FILE *p_input, FILE *p_output, const char * const p_inputPath, const char * const p_outputPath )
{
  char character;
  int numberOf_at_charactersRead = 0;
  bool mayBeginParagraph = true, paragraphBegun = false;
  HelpMog_StringStack stringStack;
  while( fscanf( p_input, "%c", &character ) != EOF )
    if( numberOf_at_charactersRead == 3 )
    {
      if(( !paragraphBegun ) && (( character == 'B' ) || ( character == 'I' )))
        p_HelpMog_BeginParagraph( mayBeginParagraph, p_output, &paragraphBegun, &stringStack );
      switch( character )
      {
        case 'B':
          fprintf( p_output, "<b>" );
          stringStack.p_Push( "</b>" );
          break;
        case 'I':
          fprintf( p_output, "<i>" );
          stringStack.p_Push( "</i>" );
          break;
        case 'N':
          {
            HelpMog_CharacterQueue characterQueue;
            characterQueue.p_Read( p_input, NULL, "\n", NULL, false );
            char *string = characterQueue.f_String();
            fprintf( p_output, "<a name=\"%s\"></a>\n", string );
            free( string );
          }
          break;
        case 'L':
          {
            HelpMog_CharacterQueue characterQueue;
            characterQueue.p_Read( p_input, "|||" );
            char *label = characterQueue.f_String();
            label[ strlen( label ) - 3 ] = '\0';
            /* ^ Remove the character sequence "|||" from the end of the string. */
            characterQueue.p_Empty();
            characterQueue.p_Read( p_input, "\\\\\\" );
            /* ^ Remember that the character '\' begins an escape sequence, so the stop string must be "\\\\\\", not "\\\". */
            char *anchor = characterQueue.f_String();
            anchor[ strlen( anchor ) - 3 ] = '\0';
            /* ^ Remove the character sequence "\\\" from the end of the string. */
            fprintf( p_output, "<a href=\"#%s\">%s</a>", anchor, label );
            free( label );
            free( anchor );
          }
          break;
        case 'T':
          fprintf( p_output, "<h1 align=\"center\">" );
          stringStack.p_Push( "</h1>" );
          mayBeginParagraph = false;
          break;
        case 't':
          fprintf( p_output, "<h2 align=\"center\">" );
          stringStack.p_Push( "</h2>" );
          mayBeginParagraph = false;
          break;
        case 'E':
          fprintf( p_output, "<hr width=\"33%%\" align=\"center\">" );
          break;
        case 'C':
          fprintf( p_output, "<p align=\"center\">" );
          stringStack.p_Push( "</p>" );
          mayBeginParagraph = false;
          break;
        case 'n':
          if( !stringStack.f_IsEmpty())
            fprintf( p_output, "%s", stringStack.f_Pop());
          break;
        default:
          printf( "\n" );
          printf( "An unknown format specifier, '%c', was encountered in the %s file - the %s file may be formatted incorrectly.\n", character, p_inputPath, p_outputPath );
          break;
      }
      numberOf_at_charactersRead = 0;
    }
    else
      if( character == '@' )
        numberOf_at_charactersRead ++;
      else
        if( character == '\n' )
        {
          if( !stringStack.f_IsEmpty())
            stringStack.p_Print( p_output );
          stringStack.p_Empty();
          fprintf( p_output, "\n" );
          mayBeginParagraph = true;
          paragraphBegun = false;
        }
        else
        {
          if( !paragraphBegun )
            p_HelpMog_BeginParagraph( mayBeginParagraph, p_output, &paragraphBegun, &stringStack );
          fprintf( p_output, "%c", character );
        }
  if( !stringStack.f_IsEmpty())
    stringStack.p_Print( p_output );
}

void p_HelpMog_BeginParagraph( const bool p_mayBeginParagraph, FILE *p_output, bool *p_paragraphBegun, HelpMog_StringStack *p_stringStack )
{
  if( p_mayBeginParagraph )
  {
    fprintf( p_output, "<p>" );
    *p_paragraphBegun = true;
    p_stringStack->p_Push( "</p>" );
  }
}
