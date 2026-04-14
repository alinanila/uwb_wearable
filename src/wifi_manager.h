#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

// connect to wifi on startup — blocks until connected
void wifi_connect();

// check wifi is still connected, attempt reconnect if not
// returns true if connected, false if not
bool wifi_check();

#endif // WIFI_MANAGER_H