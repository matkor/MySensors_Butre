#include "InputList.h"
#include "MySensors_Butre.h"


void 
InputList::update(Butre & butre) {
	for (int inputIdx = 0 ; inputIdx < INPUTS_NUM; inputIdx ++ ) {
		inputs[inputIdx].update(butre);
	}
}    

