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

CPPUTEST_ADDITIONAL_CFLAGS = \
	-DSTM32F103xB

CPPUTEST_CXXFLAGS += \
	-DSTM32F103xB

INCLUDE_DIRS = \
	$(CPPUTEST_HOME)/include/ \
	../../Drivers/STM32F1xx_HAL_Driver/Inc \
	../../Core/Inc \
	../../Drivers/CMSIS/Device/ST/STM32F1xx/Include \
	../../Drivers/CMSIS/Include

SRC_DIRS = \
	../../app/src

TEST_SRC_DIRS = \
	tests

MOCKS_SRC_DIRS = \
	mocks

CPPUTEST_USE_EXTENSIONS = Y

ifeq "$(CPPUTEST_HOME)" ""
    $(error The CPPUTEST_HOME env variable is not set.)
endif

include $(CPPUTEST_HOME)/build/MakefileWorker.mk
