
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

void parseFile( fs::path const & path );

int main( int argc, char ** argv )
{
   parseFile( argv[1] );
   return 0;
}
