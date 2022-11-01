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
CPPUTEST_CFLAGS += -std=c89
CPPUTEST_CFLAGS += -Wextra 
CPPUTEST_CFLAGS += -pedantic 
CPPUTEST_CFLAGS += -Wstrict-prototypes

SRC_DIRS = ../../app/src

TEST_SRC_DIRS = \
	tests \
	tests/HomeAutomation
	
INCLUDE_DIRS =\
	$(CPPUTEST_HOME)/include/\
	include/*\
	SRC_DIRS = ../../app/src
  
ifeq ($(CPPUTEST_HOME),)
$(info CPPUTEST_HOME not set! See README.txt)
else  
include $(CPPUTEST_HOME)/build/MakefileWorker.mk
endif
