idf_component_register(SRCS "main.c" "control_logic.c"
                       INCLUDE_DIRS "." "../include"
                       REQUIRES esp_adc esp_driver_ledc esp_timer freertos log)
