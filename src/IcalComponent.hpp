#ifndef __ICAL_COMPONENT_HPP__
#define __ICAL_COMPONENT_HPP__

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

      std::string asIcalString_r()
      {
         char * temp = icalcomponent_as_ical_string_r( self.get() );
         std::string retval( temp );
         free( temp );

         return retval;
      }

   private:

      c_ptr self;
   };
}

#endif // __ICAL_COMPONENT_HPP__
