#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "types.h"

class HttpServer
{
public:
    HttpServer();
    void init(LedOnFn onFn,
              LedOffFn offFn,
              LedToggleFn toggleFn,
              LedCycleFn cycleFn,
              LedStateFn stateFn);

private:
    AsyncWebServer webServer;
    LedOnFn ledOnFn;
    LedOffFn ledOffFn;
    LedToggleFn ledToggleFn;
    LedCycleFn ledCycleFn;
    LedStateFn ledStateFn;
    void handleRoot(AsyncWebServerRequest *request);
    void getStatus(AsyncWebServerRequest *request);
    void cycleLed(AsyncWebServerRequest *request);
    void toggleLed(AsyncWebServerRequest *request, bool first);
    void turnOnLed(AsyncWebServerRequest *request, bool first);
    void turnOffLed(AsyncWebServerRequest *request, bool first);
    void turnAllOnLed(AsyncWebServerRequest *request);
    void turnAllOffLed(AsyncWebServerRequest *request);
};

#endif