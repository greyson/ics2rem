#ifndef __ICAL_PARSER_HPP__
#define __ICAL_PARSER_HPP__

#include "IcalComponent.hpp"

extern "C" {
#include <libical/icalparser.h>
}

#include <boost/function.hpp>

namespace ical
{
   class Parser
   {
   public:
      typedef boost::shared_ptr< icalparser > c_ptr;

      Parser()
         : myParser( icalparser_new(), icalparser_free )
      {
      }

      void setGenData( void * data )
      {
         userGenData = data;
         icalparser_set_gen_data( myParser.get(), this );
      }

      /**
       * Callback to retrive a line of text for the 'getLine'
       * function.
       *
       *    This is designed to be a bit easier to use in a C++
       *    setting, using boost::function allows the function passed
       *    in to be a class member, and even to have many bindings
       *    that are automatically passed with it.
       */
      typedef boost::function< char * (
         char * s, std::size_t size, void * d ) > LineGenFunction;

      char * getLine( LineGenFunction line_gen_func )
      {
         // Temporarily contain the user's line generating function
         // and substitute our more C-friendly version.
         userLineGenFunction = line_gen_func;
         return icalparser_get_line( myParser.get(), myLineGenFunc );
      }

      icalcomponent * addLine( char * str )
      {
         return icalparser_add_line( myParser.get(), str );
      }

   private:
      c_ptr myParser;

      static char * myLineGenFunc( char * s, size_t size, void * vself )
      {
         Parser * self = (Parser *)vself;
         return self->userLineGenFunction( s, size, self->userGenData );
      }

      void * userGenData;
      LineGenFunction userLineGenFunction;
   };
}

#endif // __ICAL_PARSER_HPP__
