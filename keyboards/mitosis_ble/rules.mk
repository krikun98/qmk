
DEFAULT_FOLDER = mitosis_ble/master

NRF_DEBUG = no

# default state, RAM overflow 304 bytes
# with all options disabled, RAM overflow 280 bytes
# with disabled log in nrf.mk, RAM overflow is 252 bytes
#  NRFCFLAGS += -DNRF_LOG_ENABLED=0
#  NRFCFLAGS += -DNRF_LOG_BACKEND_SERIAL_USES_UART=0
# disabled stack, still 252 bytes
# ASFLAGS += -D__HEAP_SIZE=0 -D__STACK_SIZE=0
# twis disabled, 212 bytes


MOUSEKEY_ENABLE = no	# Mouse keys
EXTRAKEY_ENABLE = no	# Audio control and System control
CONSOLE_ENABLE = no    # Console for debug
COMMAND_ENABLE = no    # Commands for debug and configuration
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE = no	    # USB Nkey Rollover
CUSTOM_MATRIX = yes # This flag should be on for nrf52

BOOTMAGIC_ENABLE = no  # Virtual DIP switch configuration
UNICODE_ENABLE   = no
SLEEP_LED_ENABLE = no
API_SYSEX_ENABLE = no
RGBLIGHT_ENABLE = no
RGBLIGHT_ANIMATION = no

## chip/board settings
MCU_FAMILY = NRF51
# linker script to use
# Cortex version
# Teensy LC is cortex-m0; Teensy 3.x are cortex-m4
MCU  = cortex-m0
# ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
ARMV = 6
# If you want to be able to jump to bootloader from firmware on STM32 MCUs,
# set the correct BOOTLOADER_ADDRESS. Either set it here, or define it in
# ./bootloader_defs.h or in ./boards/<FOO>/bootloader_defs.h (if you have
# a custom board definition that you plan to reuse).
# If you're not setting it here, leave it commented out.
# It is chip dependent, the correct number can be looked up here (page 175):
# http://www.st.com/web/en/resource/technical/document/application_note/CD00167594.pdf
# This also requires a patch to chibios:
#   <tmk_dir>/tmk_core/tool/chibios/ch-bootloader-jump.patch
#STM32_BOOTLOADER_ADDRESS = 0x1FFFC800

# Build Options
#   comment out to disable the options.
#