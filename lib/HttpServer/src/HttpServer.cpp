#include <HttpServer.h>

HttpServer::HttpServer() : webServer(80)
{
  webServer.on("/", HTTP_GET, [this](AsyncWebServerRequest *request)
               { handleRoot(request); });

  webServer.on("/status", HTTP_GET, [this](AsyncWebServerRequest *request)
               { getStatus(request); });

  webServer.on("/cycle", HTTP_POST, [this](AsyncWebServerRequest *request)
               { cycleLed(request); });

  webServer.on("/toggle-1", HTTP_POST, [this](AsyncWebServerRequest *request)
               { toggleLed(request, true); });

  webServer.on("/toggle-2", HTTP_POST, [this](AsyncWebServerRequest *request)
               { toggleLed(request, false); });

  webServer.on("/turn-on-1", HTTP_POST, [this](AsyncWebServerRequest *request)
               { turnOnLed(request, true); });

  webServer.on("/turn-on-2", HTTP_POST, [this](AsyncWebServerRequest *request)
               { turnOnLed(request, false); });

  webServer.on("/turn-off-1", HTTP_POST, [this](AsyncWebServerRequest *request)
               { turnOffLed(request, true); });

  webServer.on("/turn-off-2", HTTP_POST, [this](AsyncWebServerRequest *request)
               { turnOffLed(request, false); });

  webServer.on("/turn-on-all", HTTP_POST, [this](AsyncWebServerRequest *request)
               { turnAllOnLed(request); });

  webServer.on("/turn-off-all", HTTP_POST, [this](AsyncWebServerRequest *request)
               { turnAllOffLed(request); });
}

void HttpServer::init(LedOnFn onFn,
                      LedOffFn offFn,
                      LedToggleFn toggleFn,
                      LedCycleFn cycleFn,
                      LedStateFn stateFn)
{
  ledOnFn = onFn;
  ledOffFn = offFn;
  ledToggleFn = toggleFn;
  ledCycleFn = cycleFn;
  ledStateFn = stateFn;

  webServer.begin();
}

void HttpServer::handleRoot(AsyncWebServerRequest *request)
{
  String indexHtml = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>ESP32-C3 Relay</title>
<style>
:root {
  --bg-color: #e4e8ec;
  --text-color: #343a40;
  --label-color: #444;
  --box-shadow: #ccc;
}

@media (prefers-color-scheme: dark) {
  :root {
    --bg-color: #202020;
    --text-color: #f0f0f0;
    --label-color: #999;
    --box-shadow: #141414;
  }
}

*, :after, :before {
    box-sizing: border-box;
}

body {
  font-family: Arial, sans-serif;
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  height: 80vh;
  margin: 0;
  background-color: var(--bg-color);
  color: var(--text-color);
}

h1 {
  margin-bottom: 2rem;
}

.container.single .form-group{
  margin: 3rem 0;
}

.container.single form,
.container.container.multiple {
  display: flex;
  flex-direction: column;
  align-items: center;
}

.container.multiple > .form-group {
  margin: 0 0;
  display: flex;
  flex-direction: row;
}

label {
  font-size: 1.3rem;
  margin-bottom: .4rem;
  font-weight: 500;
  color: var(--label-color);
}

.loader {
  display: none;
  width: 34px;
  height: 34px;
  border: 5px solid #FFF;
  border-bottom-color: transparent;
  border-radius: 50%;
  box-sizing: border-box;
  animation: rotation 1s linear infinite;
}

.btn[disabled] {
  cursor: not-allowed;
  opacity: 0.65;
  pointer-events: none;
}

.btn {
  display: flex;
  justify-content: center;
  align-items: center;
  font-weight: 500;
  padding: 12px 24px;
  font-size: 2rem;
  border-radius: 0.3rem;
  cursor: pointer;
  text-decoration: none;
  box-shadow: 3px 3px 3px var(--box-shadow);
  transition: background-color 0.15s;
}

.btn-single {
  min-width: 150px;
  height: 65px;
  text-transform: uppercase;
  color: #fff;
  background-color: #06ad22;
  border: 1px solid #069e20;
}

.btn-multiple {
  min-width: 110px;
  height: 65px;
  text-transform: uppercase;
  color: #06ad22;
  background-color: #444;
  border: 1px solid #333;
}

.btn-single:hover {
  background-color: #069e20;
}

.btn-single.state-off {
  color: #666;
  background-color: #bbb;
  border: 1px solid #bbb;
}

.btn-multiple.state-off {
  color: #bbb;
}

.btn-single.state-off:hover {
  background-color: #999999;
}

.container.multiple form:first-child>button {
  border-top-right-radius: 0;
  border-bottom-right-radius: 0;
}

.container.multiple form:last-child>button {
  border-top-left-radius: 0;
  border-bottom-left-radius: 0;
}

@keyframes rotation {
  0% {
    transform: rotate(0deg);
  }

  100% {
    transform: rotate(360deg);
  }
}
</style>
</head>
<body>
<h1>ESP32-C3 LED Relay</h1>

<div class="container single">
  <div class="form-group">
    <form action="/toggle-1" method="POST">
      <label>LED 1</label>
      <button class="btn %CLASS1% btn-single" type="submit">
        <span class="loader"></span>
        <span class="text">%STATE1%</span>
      </button>
    </form>
  </div>

  <div class="form-group">
    <form action="/toggle-2" method="POST">
      <label>LED 2</label>
      <button class="btn %CLASS2% btn-single" type="submit">
        <span class="loader"></span>
        <span class="text">%STATE2%</span>
      </button>
    </form>
  </div>
</div>

<div class="container multiple">
  <label>ALL</label>
  <div class="form-group">
    <form action="/turn-off-all" method="POST">
      <button class="btn btn-multiple state-off" type="submit">
        <span class="loader"></span>
        <span class="text">OFF</span>
      </button>
    </form>
    <form action="/turn-on-all" method="POST">
      <button class="btn btn-multiple" type="submit">
        <span class="loader"></span>
        <span class="text">ON</span>
      </button>
    </form>
  </div>
</div>

<script>
let isLoading = false;
const buttons = document.querySelectorAll('.btn');
const singleButtons = document.querySelectorAll('.btn-single');
const forms = document.querySelectorAll('form');
const poolDelay = 1000;
const formDelay = 500;

const resetButtons = () => {
  buttons.forEach((el, i) => {
    el.querySelector('.loader').style.display = 'block';
    el.querySelector('.text').innerText = '';
    el.disabled = true;
  });
}

const toggleButtons = (states) => {
  singleButtons.forEach((el, i) => {
    const isTurnedOn = states[i];
    el.classList.toggle('state-off', !isTurnedOn)
    el.querySelector('.text').innerText = isTurnedOn ? 'On' : 'Off';
  });
}

const setFormEventListener = () => {
  forms.forEach((el, i) => {
    el.addEventListener("submit", function (e) {
      isLoading = true;
      e.preventDefault();
      resetButtons();
      // prevent multiple POST requests
      window.setTimeout(() => e.target.submit(), formDelay);
    });
  });
}

const schedulePoolEvent = () => {
  window.setInterval(() => {
    if (isLoading) return;
    fetch('/status')
      .then(response => response.json())
      .then(data => toggleButtons(data.leds));
    // for debug only
    // toggleButtons([0,1])
  }, poolDelay);
}

setFormEventListener();

window.addEventListener('load', () => {
  schedulePoolEvent();
});
</script>
</body>

</html>
  )rawliteral";

  auto [state1, state2] = ledStateFn();

  indexHtml.replace("%CLASS1%", state1 ? "" : "state-off");
  indexHtml.replace("%STATE1%", state1 ? "ON" : "OFF");

  indexHtml.replace("%CLASS2%", state2 ? "" : "state-off");
  indexHtml.replace("%STATE2%", state2 ? "ON" : "OFF");

  request->send(200, "text/html", indexHtml);
}

void HttpServer::cycleLed(AsyncWebServerRequest *request)
{
  ledCycleFn();
  request->redirect("/");
}

void HttpServer::toggleLed(AsyncWebServerRequest *request, bool first)
{
  ledToggleFn(first);
  request->redirect("/");
}

void HttpServer::turnOnLed(AsyncWebServerRequest *request, bool first)
{
  ledOnFn(first);
  request->redirect("/");
}

void HttpServer::turnOffLed(AsyncWebServerRequest *request, bool first)
{
  ledOffFn(first);
  request->redirect("/");
}

void HttpServer::turnAllOnLed(AsyncWebServerRequest *request)
{
  ledOnFn(true);
  ledOnFn(false);
  request->redirect("/");
}

void HttpServer::turnAllOffLed(AsyncWebServerRequest *request)
{
  ledOffFn(true);
  ledOffFn(false);
  request->redirect("/");
}

void HttpServer::getStatus(AsyncWebServerRequest *request)
{
  auto [state1, state2] = ledStateFn();

  const String strState1 = state1 ? "true" : "false";
  const String strState2 = state2 ? "true" : "false";
  const String payload = "{\"leds\": [" + strState1 + ", " + strState2 + "]}";

  request->send(200, "application/json", payload);
}
