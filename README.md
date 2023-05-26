![image](https://github.com/Balcarj/RoboCop/assets/68673534/5e001415-0ed7-40f0-9e30-05038005c254)

# MiniSumo - "SUMEC"
Tento projekt se zaměřuje na design a konstrukci robota pro soutěž v kategorii MiniSumo (10X10 cm, 500g).

Start projektu: 2022

## Součástky
- Akumulátor: - LiPo 450mAH, 11.1V nominalního napětí, 3S
- H-můstek: - TB6612FNG
- Motory: - 150 RPM, 12V x2
- Senzor čáry: - QRE1113 x4
- Laserove senzory: - VL53L0X x3
# TB6612FNG Pinout:

![image](https://github.com/Balcarj/RoboCop/assets/120202417/d428edce-0110-4f3d-872b-86517cfe1f39)

# VL53L0X Pinout:
![image](https://github.com/Balcarj/RoboCop/assets/120202417/961efc51-b523-499f-9c7b-6f78cc3e25a9)

### Vývojová deska
- ESP32
- aktuální vývojová deska: ESP32 DevKit V1
- Dual-core procesor s konektivitou WIFI a Bluetooth.
### Důležite informace o ADC a WiFi:
- ESP32 integruje dva 12bitové ADC SAR (Successive Approximation Register), které podporují celkem 18 měřicích kanálů (analogové piny). API ovladače ADC podporuje ADC1 (8 kanálů, připojených ke GPIO 32 - 39) a ADC2 (10 kanálů, připojených ke GPIO 0, 2, 4, 12 - 15 a 25 - 27). Použití ADC2 má však pro aplikaci určitá omezení:

1. ADC2 je používán ovladačem Wi-Fi. Proto může aplikace používat ADC2 pouze tehdy, když není spuštěn ovladač Wi-Fi.

2. Některé z pinů ADC2 se používají jako páskovací piny (GPIO 0, 2, 15), a proto je nelze volně používat. Tak je tomu v následujících oficiálních vývojových sadách (ESP32 DevKitC a ESP-WROVER-KIT).

Více informací: https://docs.espressif.com/projects/esp-idf/en/v4.2/esp32/api-reference/peripherals/adc.html
# PINOUT:
<img width="583" alt="image" src="https://github.com/Balcarj/RoboCop/assets/120202417/0a48480b-2006-40af-a8f0-d4dc24d26c9d">

![image](https://github.com/Balcarj/RoboCop/assets/120202417/4ce2e7c0-2c51-49bb-a4e9-0d59cccc6bc7)


