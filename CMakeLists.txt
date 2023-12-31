# CMake minimum required version
cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
if(NOT DEFINED PICO_SDK_PATH)
    set(PICO_SDK_PATH ${CMAKE_SOURCE_DIR}/libraries/pico-sdk)
    message(STATUS "PICO_SDK_PATH = ${PICO_SDK_PATH}")
endif()

include(wizfi360_evb_pico_azure_c-patch.cmake)
include(pico_sdk_import.cmake)
include(wizfi360_evb_pico_azure_c_sdk_version.cmake)

# Set project name
set(PROJECT_NAME WizFi360-EVB-Pico-AZURE-C)

# Set project informations
project(${PROJECT_NAME} C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

# Set the project root directory if it's not already defined, as may happen if
# the tests folder is included directly by a parent project, without including
# the top level CMakeLists.txt.
if(NOT DEFINED AZURE_SDK_DIR)
# Set azure-iot-sdk-c directory path
    set(AZURE_SDK_DIR ${CMAKE_SOURCE_DIR}/libraries/azure-iot-sdk-c)
    message(STATUS "AZURE_SDK_DIR = ${AZURE_SDK_DIR}")
endif()

if(NOT DEFINED CMSIS_5_DIR)
# Set CMSIS_5 directory path
    set(CMSIS_5_DIR ${CMAKE_SOURCE_DIR}/libraries/CMSIS_5)
    message(STATUS "CMSIS_5_DIR = ${CMSIS_5_DIR}")
endif()

if(NOT DEFINED WIZFI360_DRIVER_DIR)
# Set WizFi360 driver directory path
    set(WIZFI360_DRIVER_DIR ${CMAKE_SOURCE_DIR}/libraries/CMSIS-Driver/WiFi/WizFi360)
    message(STATUS "WIZFI360_DRIVER_DIR = ${WIZFI360_DRIVER_DIR}")
endif()

if(NOT DEFINED CMSIS_FREERTOS_DIR)
# Set CMSIS-FreeRTOS directory path
    set(CMSIS_FREERTOS_DIR ${CMAKE_SOURCE_DIR}/libraries/CMSIS-FreeRTOS/CMSIS/RTOS2/FreeRTOS)
    message(STATUS "CMSIS_FREERTOS_DIR = ${CMSIS_FREERTOS_DIR}")
endif()

if(NOT DEFINED FREERTOS_DIR)
# Set FreeRTOS directory path
    set(FREERTOS_DIR ${CMAKE_SOURCE_DIR}/libraries/CMSIS-FreeRTOS/Source)
    message(STATUS "FREERTOS_DIR = ${FREERTOS_DIR}")
endif()

if(NOT DEFINED IOT_SOCKET_DIR)
# Set IoT_Socket directory path
    set(IOT_SOCKET_DIR ${CMAKE_SOURCE_DIR}/libraries/IoT_Socket)
    message(STATUS "IOT_SOCKET_DIR = ${IOT_SOCKET_DIR}")
endif()

if(NOT DEFINED MBEDTLS_DIR)
# Set mbedtls directory path
    set(MBEDTLS_DIR ${CMAKE_SOURCE_DIR}/libraries/mbedtls)
    message(STATUS "MBEDTLS_DIR = ${MBEDTLS_DIR}")
endif()

if(NOT DEFINED PORT_DIR)
# port directory path
    set(PORT_DIR ${CMAKE_SOURCE_DIR}/port)
    message(STATUS "PORT_DIR = ${PORT_DIR}")
endif()

if(NOT DEFINED DHT_DIR)
# DHT directory path
    set(DHT_DIR ${CMAKE_SOURCE_DIR}/dht)
    message(STATUS "DHT_DIR = ${DHT_DIR}")
endif()


# Configure azure-iot-sdk-c
add_definitions(-DUSE_MQTT)
add_definitions(-DHSM_TYPE_SYMM_KEY)
add_definitions(-DHSM_TYPE_X509)
add_definitions(-DUSE_PROV_MODULE)
add_definitions(-DUSE_PROV_MODULE_FULL)

# Turn off mbedtls test mode 
set(ENABLE_PROGRAMS OFF CACHE BOOL "Build mbedtls programs")
set(ENABLE_TESTING OFF CACHE BOOL "Build mbedtls testing")

# Configure mbedtls
add_definitions(-DMBEDTLS_CONFIG_FILE="${PORT_DIR}/mbedtls/inc/ssl_config.h")
add_definitions(-DSET_TRUSTED_CERT_IN_SAMPLES)

# Configure Wi-Fi for WizFi360
add_definitions(-DDRIVER_WIFI_NUM=1)

# Hardware-specific examples in subdirectories:
add_subdirectory(examples)

# Add libraries in subdirectories:
add_subdirectory(${CMAKE_SOURCE_DIR}/libraries)
add_subdirectory(${MBEDTLS_DIR})
add_subdirectory(${PORT_DIR})
add_subdirectory(${DHT_DIR})

# Set compile options
add_compile_options(
        -Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        )
