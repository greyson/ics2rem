#ifndef __ICAL_COMPONENT_HPP__
#define __ICAL_COMPONENT_HPP__

#include "IcalDuration.hpp"
#include "IcalTime.hpp"
#include <string>
#include <boost/shared_ptr.hpp>

extern "C" {
#include <libical/icalcomponent.h>
}

namespace ical
{
   class Component
   {
   public:
      typedef boost::shared_ptr< icalcomponent > c_ptr;

      Component( icalcomponent * self )
         : self( self, & icalcomponent_free )
      {
      }

      Component( c_ptr self )
         : self( self )
      {
      }

      Component( Component const & self )
         : self( self.self )
      {
      }

      operator bool()
      {
         return self.get() != NULL;
      }

      std::string asIcalString()
      {
         char * temp = icalcomponent_as_ical_string_r( self.get() );
         std::string retval( temp );
         free( temp );

         return retval;
      }

      Component getInner() {
         return icalcomponent_get_inner( self.get() );
      }

      ical::Time getDTStart() {
         return icalcomponent_get_dtstart( self.get() );
      }

      ical::Time getDTEnd() {
         return icalcomponent_get_dtend( self.get() );
      }

      ical::Duration getDuration() {
         return icalcomponent_get_duration( self.get() );
      }

      std::string getSummary() {
         return icalcomponent_get_summary( self.get() );
      }

   private:

      c_ptr self;
   };
}

#endif // __ICAL_COMPONENT_HPP__
