# List of library files exported by the component.
LIB_C_SRC       += ./components/portable_spc5_hal_component/lib/src/hal.c \
                   ./components/portable_spc5_hal_component/lib/src/hal_queues.c \
                   ./components/portable_spc5_hal_component/lib/src/pal.c \
                   ./components/portable_spc5_hal_component/lib/src/pwm.c \
                   ./components/portable_spc5_hal_component/lib/src/serial.c \

LIB_CPP_SRC     +=

LIB_ASM_SRC     +=

LIB_INCLUDES    += ./components/portable_spc5_hal_component/lib/include

APP_C_SRC       +=

APP_CPP_SRC     +=

APP_ASM_SRC     +=

APP_INCLUDES    += ./components/portable_spc5_hal_component/cfg

DDEFS           += -D__SPC5_HAL__
