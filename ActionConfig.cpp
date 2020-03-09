#include "ActionConfig.h"
#include "MySensors_Butre.h"

void 
ActionConfig::perform_action()
{
  if ( action == NO_ACTION ) {
    return;
  }
  SimpleRelay & relay = relay_set.relays[relay_idx];
  if ( action == ACTION_ON ) {
    relay.set(true);
  } else if ( action == ACTION_OFF ) {
    relay.set(false);
  } else if ( action == ACTION_TOGGLE ) {
    relay.toggle();
  }

}
