# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 1.5.1)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

cmake_minimum_required(VERSION 3.12)

# Inclui o script de importação do Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Define o nome do projeto
project(neopixel_buzzer_example)

# Inicializa o Pico SDK
pico_sdk_init()

add_executable(neopixel_pio.c 
    neopixel_pio.c
    
)

# Vincula as bibliotecas necessárias
target_link_libraries(neopixel_buzzer_example
    pico_stdlib
    hardware_pio
    hardware_gpio
)

# Habilita a saída padrão via USB (para depuração)
pico_enable_stdio_usb(neopixel_buzzer_example 1)

# Desabilita a saída padrão via UART (opcional)
pico_enable_stdio_uart(neopixel_buzzer_example 0)

# Gera arquivos adicionais (como .uf2 e .hex)
pico_add_extra_outputs(neopixel_buzzer_example)