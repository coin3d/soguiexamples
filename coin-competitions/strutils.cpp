
#include <strutils.h>
#include <string.h>

char *
strconcat(const char * array[], unsigned int &total)
{
  int i;
  for (i = total = 0; array[i]; i++ )
    total += strlen(array[i]) + 1;
  char * buf = new char [total + 1];
  for (i = total = 0; array[i]; i++ ) {
    strcpy(buf+total, array[i]);
    total += strlen(array[i]);
    buf[total] = '\n';
    total++;
  }
  return buf;
}

