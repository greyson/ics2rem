#include <boost/filesystem.hpp>

#include "IcalComponent.hpp"
#include "IcalParser.hpp"

namespace fs = boost::filesystem;

char * read_stream( char * s, std::size_t size, void * d )
{
   char * c = fgets( s, size, (FILE *) d );
   return c;
}

void parseFile( fs::path const & path )
{
   // Create a new parser object
   ical::Parser parser;

   FILE * stream = fopen( path.c_str(), "r" );
   assert( stream != NULL );

   // Tell the parser what input routine it should use.
   parser.setGenData( stream );

   char * line = NULL;
   do
   {
      // Get a single content line by making one or more calls to
      // read_stream()
      line = parser.getLine( read_stream );

      // Now, add that line into the parser object. If that line
      // completes a component, c will be non-zero
      ical::Component c = parser.addLine( line );

      if( c )
      {
         std::string temp = c.asIcalString_r();
         std::cout << temp << std::endl
                   << "---------------" << std::endl;
      }
   } while( line != NULL );
}
