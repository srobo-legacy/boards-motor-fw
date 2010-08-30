#ifndef __H_BRIDGE_H
#define __H_BRDIGE_H

typedef enum {
	M_OFF,
	M_FWD,
	M_REV,
	M_BRAKE
} h_bridge_state_t;

void h_bridge_init(void);

void h_bridge_set(h_bridge_state_t);
h_bridge_state_t h_bridge_get(void);

#endif /* __H_BRIDGE_H */
