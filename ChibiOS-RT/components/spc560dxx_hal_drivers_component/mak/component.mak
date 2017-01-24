# List of library files exported by the component.
LIB_C_SRC       += ./components/spc560dxx_hal_drivers_component/lib/src/hal_lld.c \
                   ./components/spc560dxx_hal_drivers_component/lib/src/spc5_edma.c \
                   ./components/spc560dxx_hal_drivers_component/lib/src/spc5_emios.c \
                   ./components/spc560dxx_hal_drivers_component/lib/src/pal_lld.c \
                   ./components/spc560dxx_hal_drivers_component/lib/src/pwm_lld.c \
                   ./components/spc560dxx_hal_drivers_component/lib/src/serial_lld.c \

LIB_CPP_SRC     +=

LIB_ASM_SRC     +=

LIB_INCLUDES    += ./components/spc560dxx_hal_drivers_component/lib/include

APP_C_SRC       += \
                   ./components/spc560dxx_hal_drivers_component/cfg/pwm_lld_cfg.c \

APP_CPP_SRC     +=

APP_ASM_SRC     +=

APP_INCLUDES    += ./components/spc560dxx_hal_drivers_component/cfg
