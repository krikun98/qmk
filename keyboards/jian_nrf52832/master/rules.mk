
RGBLIGHT_ENABLE = no

# it should exist either in <this_dir>/ld/
MCU_LDSCRIPT = nrf52832_master
MCU_SERIES = NRF52832
NRFSDK_ROOT := $(NRFSDK12_ROOT) #Path to nRF SDK v15.0.0

# project specific files
#SRC =	matrix.c

NRF_SEPARATE = master
#CFLAGS += -DNRF_XTAL_32MHZ