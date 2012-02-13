
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

void parseFile( fs::path const & path );

int main( int argc, char ** argv )
{
   argv++;
   for( ; --argc > 0; argv++ )
   {
      parseFile( * argv );
   }

   return 0;
}
