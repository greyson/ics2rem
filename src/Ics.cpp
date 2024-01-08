#include <boost/filesystem.hpp>

#include "IcalComponent.hpp"
#include "IcalParser.hpp"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <memory>

namespace fs = boost::filesystem;

namespace {
   char const * const MONTHS[] = {
      "Jan", "Feb", "Mar",
      "Apr", "May", "Jun",
      "Jul", "Aug", "Sep",
      "Oct", "Nov", "Dec",
   };
}

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
         /*
         std::string temp = c.getInner().asIcalString();
         std::cout << temp << std::endl
                   << "---------------" << std::endl;
         */

         ical::Time dtstart = c.getDTStart();
         std::cout << "REM " << dtstart.day
                   << " " << MONTHS[ dtstart.month - 1 ]
                   << " " << dtstart.year;

         ical::Duration duration = c.getDuration();
         if( dtstart.isDate() )
         {
            if( ! duration.isNullDuration() )
            {
               std::cout << " *1";
            }
         }

         // Include the time if it's a date-time (aka, not date)
         if( ! dtstart.isDate() )
         {
            std::cout << " AT " << dtstart.hour << ':';
            if( dtstart.minute < 10 )
               std::cout << '0';
            std::cout << dtstart.minute;
         }

         if( ! duration.isNullDuration() )
         {
            int all = duration.asInt();
            if( dtstart.isDate() )
            {
               ical::Time dtend = c.getDTEnd();
               std::cout << " UNTIL "
                         << dtend.day << ' '
                         << MONTHS[ dtend.month - 1 ] << ' '
                         << dtend.year;
            }
            else
            {
               int seconds = all % 60;
               int minutes = all / 60 % 60;
               int hours = all / 60 / 60;
               std::cout << " DURATION " << hours << ':';
               if( minutes < 10 )
                  std::cout << '0';
               std::cout << minutes;
            }
         }

         // Add the summary field as the message
         std::cout << " MSG %\"" << c.getSummary() << "%\"";

         if( ! dtstart.isDate() )
         {
            std::cout << " %3";
         }

         std::cout << std::endl;
      }
   } while( line != NULL );
}
