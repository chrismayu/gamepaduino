#ifndef _PITCH_WHEEL_H
#define _PITCH_WHEEL_H

#include "midi_controller.h"
//#include "midi_interface.h"

namespace meta { namespace midi { namespace luthier {

template<class midi_controller_Type>
struct pitch_wheel: public midi_controller_Type
{
  typedef          midi_controller_Type             midi_controller_type;
  typedef typename midi_controller_type::gamepad_t  gamepad_t;
  
  typedef  int8_t pitch_bend_t; // todo: generalize pitch_bend_t in midi interface
  
  
  pitch_wheel(midi_instrument_base& base)
  : midi_instrument_base(base)
  {}
  
  virtual void action_any_state_changed() {
    midi_instrument_base::action_any_state_changed();
    
    //Serial.print(gamepad_t::get_x_cal()); Serial.print("\t\t");
    //Serial.print(gamepad_t::get_x()); Serial.print("\t\t");
    
    using ::meta::midi::pitch_bend_t;
    using ::meta::midi::pitch_bend_coded_t;
    
    pitch_bend_t pb(gamepad_t::get_x()*100 + pitch_bend_t::CENTER_PITCH);
    //pitch_bend_t pb(gamepad_t::get_x() + pitch_bend_t::CENTER_PITCH);
    /*pitch_bend_t pb(map(gamepad_t::get_x(), 
                        gamepad_t::analog_range.xmin,
                        gamepad_t::analog_range.xmax,
                        pitch_bend_t::MIN_BEND,
                        pitch_bend_t::MAX_BEND));*/
    
    midi_instance().pitch_bend(get_channel(), pb);
    
    midi_instance().control_change(get_channel(),0x10,abs(get_y()));
    
    //pitch_bend_coded_t pbc(pb.value);
    //Serial.print(pbc._lllllll, HEX); Serial.print("\t\t");
    //Serial.println(pbc._mmmmmmm, HEX);
  }
};

}}}
#endif // _PITCH_WHEEL_H


