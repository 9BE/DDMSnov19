################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/suhaimi/Arduino/hardware/espressif/esp32/cores/esp32/libb64/cdecode.c \
/home/suhaimi/Arduino/hardware/espressif/esp32/cores/esp32/libb64/cencode.c 

C_DEPS += \
./core/core/libb64/cdecode.c.d \
./core/core/libb64/cencode.c.d 

AR_OBJ += \
./core/core/libb64/cdecode.c.o \
./core/core/libb64/cencode.c.o 


# Each subdirectory must supply rules for building sources it contributes
core/core/libb64/cdecode.c.o: /home/suhaimi/Arduino/hardware/espressif/esp32/cores/esp32/libb64/cdecode.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"/home/suhaimi/Arduino/hardware/espressif/esp32/tools/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc" -DESP_PLATFORM -DMBEDTLS_CONFIG_FILE="mbedtls/esp_config.h" -DHAVE_CONFIG_H "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/config" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/app_trace" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/app_update" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/asio" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/bootloader_support" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/bt" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/coap" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/console" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/driver" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/efuse" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/esp-tls" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/esp32" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/esp_adc_cal" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/esp_event" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/esp_http_client" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/esp_http_server" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/esp_https_ota" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/esp_https_server" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/esp_ringbuf" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/espcoredump" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/ethernet" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/expat" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/fatfs" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/freemodbus" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/freertos" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/heap" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/idf_test" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/jsmn" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/json" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/libsodium" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/log" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/lwip" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/mbedtls" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/mdns" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/micro-ecc" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/mqtt" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/newlib" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/nghttp" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/nvs_flash" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/openssl" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/protobuf-c" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/protocomm" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/pthread" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/sdmmc" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/smartconfig_ack" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/soc" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/spi_flash" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/spiffs" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/tcp_transport" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/tcpip_adapter" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/ulp" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/unity" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/vfs" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/wear_levelling" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/wifi_provisioning" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/wpa_supplicant" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/xtensa-debug-module" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/esp32-camera" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/esp-face" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/fb_gfx" -std=gnu99 -Os -g3 -fstack-protector -ffunction-sections -fdata-sections -fstrict-volatile-bitfields -mlongcalls -nostdlib -Wpointer-arith -Wall -Werror=all -Wextra -Wno-error=unused-function -Wno-error=unused-but-set-variable -Wno-error=unused-variable -Wno-error=deprecated-declarations -Wno-unused-parameter -Wno-sign-compare -Wno-old-style-declaration -MMD -c -DF_CPU=240000000L -DARDUINO=10802 -DARDUINO_ESP32_DEV -DARDUINO_ARCH_ESP32 -DARDUINO_BOARD="ESP32_DEV" -DARDUINO_VARIANT="esp32"  -DESP32 -DCORE_DEBUG_LEVEL=0    -I"/home/suhaimi/Arduino/hardware/espressif/esp32/cores/esp32" -I"/home/suhaimi/Arduino/hardware/espressif/esp32/variants/esp32" -I"/home/suhaimi/Arduino/hardware/espressif/esp32/libraries/ArduinoOTA/src" -I"/home/suhaimi/Arduino/hardware/espressif/esp32/libraries/WiFi/src" -I"/home/suhaimi/Arduino/hardware/espressif/esp32/libraries/ESPmDNS/src" -I"/home/suhaimi/Arduino/hardware/espressif/esp32/libraries/Update/src" -I"/home/suhaimi/Arduino/hardware/espressif/esp32/libraries/SPIFFS/src" -I"/home/suhaimi/Arduino/hardware/espressif/esp32/libraries/WebServer/src" -I"/home/suhaimi/Arduino/hardware/espressif/esp32/libraries/FS/src" -I"/home/suhaimi/Arduino/libraries/ESP8266_and_ESP32_Oled_Driver_for_SSD1306_display/src" -I"/home/suhaimi/Arduino/hardware/espressif/esp32/libraries/SPI/src" -I"/home/suhaimi/Arduino/hardware/espressif/esp32/libraries/Wire/src" -I"/home/suhaimi/Arduino/libraries/ArduinoJson/src" -I"/media/suhaimi/HDD/eclipse/sloeber/arduinoPlugin/libraries/simplot/1.0.2" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

core/core/libb64/cencode.c.o: /home/suhaimi/Arduino/hardware/espressif/esp32/cores/esp32/libb64/cencode.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"/home/suhaimi/Arduino/hardware/espressif/esp32/tools/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc" -DESP_PLATFORM -DMBEDTLS_CONFIG_FILE="mbedtls/esp_config.h" -DHAVE_CONFIG_H "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/config" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/app_trace" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/app_update" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/asio" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/bootloader_support" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/bt" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/coap" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/console" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/driver" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/efuse" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/esp-tls" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/esp32" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/esp_adc_cal" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/esp_event" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/esp_http_client" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/esp_http_server" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/esp_https_ota" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/esp_https_server" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/esp_ringbuf" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/espcoredump" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/ethernet" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/expat" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/fatfs" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/freemodbus" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/freertos" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/heap" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/idf_test" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/jsmn" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/json" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/libsodium" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/log" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/lwip" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/mbedtls" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/mdns" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/micro-ecc" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/mqtt" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/newlib" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/nghttp" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/nvs_flash" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/openssl" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/protobuf-c" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/protocomm" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/pthread" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/sdmmc" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/smartconfig_ack" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/soc" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/spi_flash" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/spiffs" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/tcp_transport" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/tcpip_adapter" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/ulp" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/unity" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/vfs" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/wear_levelling" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/wifi_provisioning" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/wpa_supplicant" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/xtensa-debug-module" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/esp32-camera" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/esp-face" "-I/home/suhaimi/Arduino/hardware/espressif/esp32/tools/sdk/include/fb_gfx" -std=gnu99 -Os -g3 -fstack-protector -ffunction-sections -fdata-sections -fstrict-volatile-bitfields -mlongcalls -nostdlib -Wpointer-arith -Wall -Werror=all -Wextra -Wno-error=unused-function -Wno-error=unused-but-set-variable -Wno-error=unused-variable -Wno-error=deprecated-declarations -Wno-unused-parameter -Wno-sign-compare -Wno-old-style-declaration -MMD -c -DF_CPU=240000000L -DARDUINO=10802 -DARDUINO_ESP32_DEV -DARDUINO_ARCH_ESP32 -DARDUINO_BOARD="ESP32_DEV" -DARDUINO_VARIANT="esp32"  -DESP32 -DCORE_DEBUG_LEVEL=0    -I"/home/suhaimi/Arduino/hardware/espressif/esp32/cores/esp32" -I"/home/suhaimi/Arduino/hardware/espressif/esp32/variants/esp32" -I"/home/suhaimi/Arduino/hardware/espressif/esp32/libraries/ArduinoOTA/src" -I"/home/suhaimi/Arduino/hardware/espressif/esp32/libraries/WiFi/src" -I"/home/suhaimi/Arduino/hardware/espressif/esp32/libraries/ESPmDNS/src" -I"/home/suhaimi/Arduino/hardware/espressif/esp32/libraries/Update/src" -I"/home/suhaimi/Arduino/hardware/espressif/esp32/libraries/SPIFFS/src" -I"/home/suhaimi/Arduino/hardware/espressif/esp32/libraries/WebServer/src" -I"/home/suhaimi/Arduino/hardware/espressif/esp32/libraries/FS/src" -I"/home/suhaimi/Arduino/libraries/ESP8266_and_ESP32_Oled_Driver_for_SSD1306_display/src" -I"/home/suhaimi/Arduino/hardware/espressif/esp32/libraries/SPI/src" -I"/home/suhaimi/Arduino/hardware/espressif/esp32/libraries/Wire/src" -I"/home/suhaimi/Arduino/libraries/ArduinoJson/src" -I"/media/suhaimi/HDD/eclipse/sloeber/arduinoPlugin/libraries/simplot/1.0.2" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


