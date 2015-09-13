#include <stdio.h>
#include <stdbool.h>
#include "tap.h"

int main( int argc, char** argv )
{
   plan( 3 );
   ok( 5 == 5, "5 equals 5" );
   ok( true == true, "true" );
   ok( true == true, "true" );

   return( 0 );
}
