cmake_minimum_required(VERSION 3.16)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

project(FreqsyTNC_Blink C ASM)

set(CMAKE_C_STANDARD 11)

set(CPU_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")

set(CMAKE_C_FLAGS "${CPU_FLAGS} -Wall -g -O0 -ffunction-sections -fdata-sections")
set(CMAKE_EXE_LINKER_FLAGS "${CPU_FLAGS} -T${CMAKE_SOURCE_DIR}/linker.ld -Wl,-Map=${PROJECT_NAME}.map -Wl,--gc-sections --specs=nosys.specs -nostartfiles")

add_executable(${PROJECT_NAME}
    Core/Src/startup.c
    Core/Src/main.c
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND arm-none-eabi-objcopy -O binary ${PROJECT_NAME} ${PROJECT_NAME}.bin
    COMMAND arm-none-eabi-size ${PROJECT_NAME}
)