#ifndef PUBLISHER_H
#define PUBLISHER_H

// initialise UDP socket
void publisher_init();

// serialise bno_data and lsm_data to JSON and send over UDP
void publisher_send();

#endif // PUBLISHER_H