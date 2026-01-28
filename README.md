# ESP32-C3 Dual LED Controller
A simple ESP32-C3 project to control 02 LED strips via a web interface and a physical push button.

<img width="270" src="https://github.com/user-attachments/assets/72859d9e-99ca-4c3f-a4ff-6d512422b335" />
<img width="270" src="https://github.com/user-attachments/assets/60f6a48b-7dbd-4109-960f-b92f9d7d98be" />
<img width="270" src="https://github.com/user-attachments/assets/036d4241-7682-4798-a40a-43510beda6df" />

### The Web interface
<img width="500" src="https://github.com/user-attachments/assets/3b3a0bce-a33f-4288-aa44-b7863287e0ec" />

### The PCB
<img width="500" src="https://github.com/user-attachments/assets/9c82cf47-de94-4f1c-9925-8533e8d0968f" />

### Sample of push button
<img width="500" src="https://github.com/user-attachments/assets/efb497c9-0103-4b13-a689-5130bdc15a99" />


## Simple API
Additionally, the LED can be controlled via a simple API, making it easy to integrate with home automation (e.g.: set up a cron job to turn it on and off automatically):
* `GET` `http://192.168.1.190/status`
* `POST` `http://192.168.1.190/cycle`
* `POST` `http://192.168.1.190/toggle-1`
* `POST` `http://192.168.1.190/toggle-2`
* `POST` `http://192.168.1.190/turn-on-1`
* `POST` `http://192.168.1.190/turn-on-2`
* `POST` `http://192.168.1.190/turn-off-1`
* `POST` `http://192.168.1.190/turn-off-2`
* `POST` `http://192.168.1.190/turn-on-all`
* `POST` `http://192.168.1.190/turn-off-all`

NOTE: Change `http://192.168.1.190` to your actual device IP. Assign a Static IP to your device in your home router.


## Protoboard & PCB
### The prototype in Protoboard
<img width="420" src="https://github.com/user-attachments/assets/23b26750-aaef-4c15-932e-7ff1c0f91ca3" />


### PCB designed in EasyEDA
<img width="420" src="https://github.com/user-attachments/assets/be04c019-ec37-4e58-8ffa-bbf7e948564f" />
<img width="395" src="https://github.com/user-attachments/assets/056e105b-4b44-4575-abbe-85ed983f31e1" />


## Schematics
<img src="https://github.com/user-attachments/assets/e72373e9-14d8-43fe-99bf-a5f8384c7944" />

### Notes:
1) Gate resistor (220Ω) is optional but recommended to prevent spikes.
2) Pull-down resistor (10kΩ) between Gate and GND is optional but prevents accidental turn-on during boot.
3) IRF9540N is optional but protects against reverse-polarity

## Components
* 01 ESP32-C3 Mini board
* 01 Push Button
* 02 Green LED
* 03 220Ω Resistors
* 02 10KΩ Resistor
* 02 N-channel MOSFET able to work with 3.3v logic (e.g.: IRFZ44N)
* 01 P-channel power MOSFET IRF9540N
* 02 LED Strip (12v)
* 01 Power Supply (12v)
* 01 Mini 360 DC-DC Bulk Converter

## About PlatformIO IDE
Platform IO is a plugin for Microsoft Virtual Studio Code. It is a more robust IDE compared to official Arduino IDE. It also allows us to easily create our own private libraries and use a more object oriented code.

## About the code
The PINs can be customized in the `Config/src/Config.h`

```c++
#define RELAY_PIN_1 1
#define RELAY_PIN_2 0
#define LED_PIN_1 3
#define LED_PIN_2 4
#define BUTTON_PIN 10
#define WIFI_SSID "MY_SSID"
#define WIFI_PWD "MY_PASSWORD"
```

## Fritzing file
* [esp32-c3-led-relay-v2-12v.zip](https://github.com/user-attachments/files/23429899/esp32-c3-led-relay-v2-12v.zip)
