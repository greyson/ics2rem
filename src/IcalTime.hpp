#ifndef __ICAL_TIME_HPP__
#define __ICAL_TIME_HPP__

extern "C" {
#include <libical/icaltime.h>
}

namespace ical
{
   class Time : public icaltimetype
   {
   public:
      Time( icaltimetype const & copyFrom )
         : icaltimetype( copyFrom ) { }

      time_t asTimet() { return icaltime_as_timet( *this ); }

      bool isDate() { return icaltime_is_date( *this ); };
      bool isUtc()  { return icaltime_is_utc( *this ); };
   };
}

#endif // __ICAL_TIME_HPP__
