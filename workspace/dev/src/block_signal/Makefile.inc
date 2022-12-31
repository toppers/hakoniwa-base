mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS += util.o timer.o horn.o signal_display.o train_detector.o manual_switch.o rotator.o block_signal.o

SRCLANG := c

# APPL_DIR += $(mkfile_path)app $(mkfile_path)../utils

# INCLUDES += \
# 	-I$(mkfile_path)app \
# 	-I$(mkfile_path)../utils
