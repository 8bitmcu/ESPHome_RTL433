# ESPHome_RTL433

I wanted to have the flexibility of the [rtl_433_ESP](https://github.com/NorthernMan54/rtl_433_ESP) library, with all the benefits of ESPHome, so I set out to import that library as a custom component.
This isn't the cleanest or best implementation, but it's simple enough to be understood and built up from.



## configuration

The device I have it configured for is a [Heltec WiFi LoRa 32 v2](https://heltec.org/project/wifi-lora-32/), but this should work on any [supported modules](https://github.com/NorthernMan54/rtl_433_ESP#user-content-transceiver-modules-supported) by rtl_433_ESP.


## performance

I only have basic push button style devices, and some door sensors (as shown in the yaml). Overall, I find the response time on the push buttons to be faster than RC_Switch.
