#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = demo
	
TEST_TARGET = \
	$(COMPONENT_NAME)_tests

#--- Inputs ----#
CPP_PLATFORM = Gcc

CPPUTEST_WARNINGFLAGS += -Wall 
CPPUTEST_WARNINGFLAGS += -Wswitch-default 
CPPUTEST_WARNINGFLAGS += -Wswitch-enum  
CPPUTEST_CFLAGS += -Wextra 

SRC_DIRS = ../../app/src

TEST_SRC_DIRS = \
	tests \
	
INCLUDE_DIRS = \
	$(CPPUTEST_HOME)/include/ \
	../../Drivers/STM32F1xx_HAL_Driver/Inc \
	../../Core/Inc \
	../../Drivers/CMSIS/Device/ST/STM32F1xx/Include \
	../../Drivers/CMSIS/Include/

CPPUTEST_ADDITIONAL_CFLAGS = \
	-DSTM32F103xB
  
ifeq ($(CPPUTEST_HOME),)
$(info CPPUTEST_HOME not set! See README.txt)
else  
include $(CPPUTEST_HOME)/build/MakefileWorker.mk
endif
