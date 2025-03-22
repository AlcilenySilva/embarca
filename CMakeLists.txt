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

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Importa o Raspberry Pi Pico SDK
include(pico_sdk_import.cmake)

set(PICO_BOARD pico CACHE STRING "Board type")

# Define o nome do projeto
project(trabalhofinalplaca C CXX ASM)

# Inicializa o Raspberry Pi Pico SDK
pico_sdk_init()

# Adiciona os arquivos do projeto ao executável
add_executable(trabalhofinalplaca 
    main.c
    buzzer.c
    neopixel_pio.c
)

# Define nome e versão do programa
pico_set_program_name(trabalhofinalplaca "trabalhofinalplaca")
pico_set_program_version(trabalhofinalplaca "0.1")

# Gera automaticamente o cabeçalho do programa PIO
pico_generate_pio_header(trabalhofinalplaca ${CMAKE_CURRENT_LIST_DIR}/ws2818b.pio)

# Ativa saída via USB e desativa via UART
pico_enable_stdio_uart(trabalhofinalplaca 0)
pico_enable_stdio_usb(trabalhofinalplaca 1)

# Adiciona bibliotecas necessárias
target_link_libraries(trabalhofinalplaca
    pico_stdlib
    hardware_pio
    hardware_clocks
    hardware_pwm

   

)

# Adiciona diretórios de inclusão para os headers
target_include_directories(trabalhofinalplaca PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

# Gera arquivos extras para UF2 e outras saídas
pico_add_extra_outputs(trabalhofinalplaca)
