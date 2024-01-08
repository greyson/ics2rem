#ifndef __ICAL_DURATION_HPP__
#define __ICAL_DURATION_HPP__

#include <string>

extern "C" {
#include <libical/icalduration.h>
}

namespace ical
{
   class Duration : public icaldurationtype
   {
   public:
      Duration()
         : icaldurationtype( icaldurationtype_null_duration() ) { }

      Duration( icaldurationtype const & copyFrom )
         : icaldurationtype( copyFrom ) { }

      Duration( int fromInt )
         : icaldurationtype( icaldurationtype_from_int( seconds ) ) { }

      Duration( std::string const & fromString )
         : icaldurationtype( icaldurationtype_from_string( fromString.c_str() ) ) { }

      std::string asIcalString() {
         char * temp = icaldurationtype_as_ical_string_r( *this );
         std::string retval( temp );
         free( temp );
         return retval;
      }

      bool isNullDuration() {
         return icaldurationtype_is_null_duration( *this );
      }

      bool isBadDuration() {
         return icaldurationtype_is_bad_duration( *this );
      }

      int asInt() {
         return icaldurationtype_as_int( *this );
      }
   };
}

#endif // __ICAL_DURATION_HPP__
