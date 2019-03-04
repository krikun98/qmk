
RGBLIGHT_ENABLE = no

# it should exist either in <this_dir>/ld/
MCU_LDSCRIPT = nrf51822
MCU_SERIES = NRF51822
NRFSDK_ROOT := $(NRFSDK12_ROOT) #Path to nRF SDK v12.0.0

LDSCRIPT = nrf51822

# project specific files
#SRC =	matrix.c

NRF_SEPARATE = master
#CFLAGS += -DNRF_XTAL_32MHZ