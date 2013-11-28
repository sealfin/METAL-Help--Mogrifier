#include "HelpMog_RemoveWhitespace.h"
#include "HelpMog_mhlp2html.h"

static const char * const k_HelpMog_INPUT_FILE_PATH = "metal_help.mhlp";

bool f_HelpMog_InputFileIsInSameFolderAsProgram( void );

void main( void )
{
  const char * const k_HelpMog_OUTPUT_FILE_PATH = "metal_help.html";
  const char * const k_HelpMog_TEMPORARY_OUTPUT_FILE_PATH = "help_mog.temp";

  printf( "---\n" );
  printf( "- METAL Help 'Mogrifier\n" );
  printf( "- by Mark Bishop/sealfin\n" );
  printf( "- METAL-Help-Mogrifier@sealfin.com\n" );
  printf( "---\n" );
  printf( "\n" );
  printf( "METAL Help 'Mogrifier is a program for translating the %s file which comes with METAL BASIC (and which is viewable only in the built-in help browser of METAL BASIC) into a .html file viewable - and searchable and printable - in any web browser.\n", k_HelpMog_INPUT_FILE_PATH );
  printf( "\n" );
  printf( "After translation, a file named %s will be created - the %s file will not be changed.\n", k_HelpMog_OUTPUT_FILE_PATH, k_HelpMog_INPUT_FILE_PATH );
  bool errorOccurred = false;
  if( f_HelpMog_InputFileIsInSameFolderAsProgram())
  {
    printf( "\n" );
    printf( "Please press the Return key to begin translating." );
    HelpMog_CharacterQueue characterQueue;
    characterQueue.p_Read( stdin, NULL, "\n", NULL, false );
    errorOccurred = !f_HelpMog_InputFileIsInSameFolderAsProgram();
  }
  else
    errorOccurred = true;
  while( errorOccurred )
  {
    printf( "\n" );
    printf( "Sorry, an error occurred: the %s file is not in the same folder as this program.\n", k_HelpMog_INPUT_FILE_PATH );
    printf( "\n" );
    printf( "To translate the %s file, that file must be in the same folder as this program; please move that file into the same folder as this program and press the Return key to begin translating.", k_HelpMog_INPUT_FILE_PATH );
    HelpMog_CharacterQueue characterQueue;
    characterQueue.p_Read( stdin, NULL, "\n", NULL, false );
    errorOccurred = !f_HelpMog_InputFileIsInSameFolderAsProgram();
  }
  FILE *input = fopen( k_HelpMog_INPUT_FILE_PATH, "r" );
  FILE *output = fopen( k_HelpMog_TEMPORARY_OUTPUT_FILE_PATH, "w" );
  p_HelpMog_RemoveExtraneousWhitespaceCharacters( input, output );
  fclose( input );
  fclose( output );
  input = fopen( k_HelpMog_TEMPORARY_OUTPUT_FILE_PATH, "r" );
  output = fopen( k_HelpMog_OUTPUT_FILE_PATH, "w" );
  p_HelpMog_mhlp2html( input, output, k_HelpMog_INPUT_FILE_PATH, k_HelpMog_OUTPUT_FILE_PATH );
  fclose( input );
  remove( k_HelpMog_TEMPORARY_OUTPUT_FILE_PATH );
  fclose( output );
  printf( "\n" );
  printf( "The %s file has been translated and the %s file has been created.\n", k_HelpMog_INPUT_FILE_PATH, k_HelpMog_OUTPUT_FILE_PATH );
  printf( "\n" );
  printf( "This program will now quit.\n" );
}

bool f_HelpMog_InputFileIsInSameFolderAsProgram( void )
{
  FILE *file = fopen( k_HelpMog_INPUT_FILE_PATH, "r" );
  if( file != NULL )
  {
    fclose( file );
    return true;
  }
  return false;
}
