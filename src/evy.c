#include "evy.h"

int main( int argc, char* argv[] ) {

  char buffer [4096];

  while( 1 ) {
    fputs( PROMPT, stdout );
    fputs( evaluate( fgets( buffer, sizeof(buffer), stdin ), &buffer[sizeof(buffer)/2] ), stdout );
  }

  return 0;

}

char* evaluate( char* in, char* buffer ) {

  buffer[0] = '\0';

  int offset = getIndentationLevel( in );

  struct Parameter* parameter = malloc( sizeof( struct Parameter ) );

  while( in[offset] != '\0' ) {
    offset += parseTokenAsKeyValuePair( &in[offset], parameter ) + 1;
    // sprintf( buffer, "{ key: %s, value: %s }\n", parameter->key, parameter->value );
    printf( "{ key: %s, value: %s }\n", parameter->key, parameter->value );
  }

  free( parameter );

  return buffer;

}

int getIndentationLevel( char* in ) {
  int level = 0;
  for( level = 0; in[level] == ' '; level++ );
  return level;
}

int parseTokenAsKeyValuePair( char* token, struct Parameter* parameter ) {

  int end = next( token );

  if( token[end] == '=' ) {

    token[end] = '\0';
    end++;

    parameter->key = token;
    parameter->value = &token[end];

    end += next(parameter->value);
    token[end] = '\0';

  } else {

    token[end] = '\0';

    parameter->key = NULL;
    parameter->value = token;

  }

  return end;

}

int next( char* in ) {

  int end;

  for( end = 0; in[end] != '\0' && in[end] != '\r' && in[end] != '\n' && in[end] != '=' && in[end] != ' '; end++ ) {
    if( in[end] == '\\' ) {
      end++;
    } else if( in[end] == '"' ) {
      end++;
      while( in[end] != '"' ) {
        if( in[end] == '\\' ) {
          end++;
        }
        end++;
      }
    }
  }

  return end;

}
