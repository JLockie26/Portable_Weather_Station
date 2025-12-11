# Wiring
| Uno | SD Module |        Function        |
------|-----------|------------------------|
| 5V  |    5V     |  Power                 |
| D4  |    CS     |  Chip Select           |
| D11 |    MOSI   |  Data from Uno to Card |
| D13 |    SCK    |  Serial Clock          |
| D12 |    MISO   |  Data from Card to Uno |
| GND |    GND    |  Ground Connection     |

- Table from XC4386 SD Card Module doc

## I2C connections
- DHT11 sensor plugs into D2 on shield
- BMP280 and OLED plug into separate I2C ports on shield