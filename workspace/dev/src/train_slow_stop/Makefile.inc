mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS += util.o timer.o horn.o drive_unit.o signal_reader.o operation_switch.o train_slow_stop.o

SRCLANG := c

# APPL_DIR += $(mkfile_path)app $(mkfile_path)../utils

# INCLUDES += \
# 	-I$(mkfile_path)app \
# 	-I$(mkfile_path)../utils
