#include "ActionConfig.h"
#include "MySensors_Butre.h"

void 
ActionConfig::perform_action()
{
  if ( action == NO_ACTION ) {
    return;
  }
  Output & output = butre.relay_set.relays[relay_idx];
  if ( action == ACTION_ON ) {
    output.set(true);
  } else if ( action == ACTION_OFF ) {
    output.set(false);
  } else if ( action == ACTION_TOGGLE ) {
    output.toggle();
  }

}
