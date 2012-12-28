#include <stdio.h>
#include <stdlib.h>

typedef struct Parameter {
  char* key;
  char* value;
} Parameter;

typedef struct Parameters {
  int size;
  struct Parameter* items;
} Parameters;

typedef struct Event {
  char* name;
  int depth;
  struct Parameters* parameters;
  struct Event* parent;
} Event;

char* PROMPT = "Evy$ ";

char* evaluate( char* in, char* buffer );
int getIndentationLevel( char* in );
int parseTokenAsKeyValuePair( char* token, struct Parameter* parameter );
int next( char* in );
