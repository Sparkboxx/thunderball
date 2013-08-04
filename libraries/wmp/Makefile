#
# This makefile is there to test if the WMP library compiles using
# some of the arduino standard libraries.
#
ARDUINO = $(INSTALL_DIR)/hardware/arduino/cores/arduino

C_MODULES =  \
$(ARDUINO)/wiring_pulse.c \
$(ARDUINO)/wiring_analog.c \
$(ARDUINO)/wiring.c \
$(ARDUINO)/wiring_digital.c \
$(ARDUINO)/WInterrupts.c \
$(ARDUINO)/wiring_shift.c \
# end of C_MODULES

CXX_MODULES = \
$(ARDUINO)/Tone.cpp \
$(ARDUINO)/main.cpp \
$(ARDUINO)/WMath.cpp \
$(ARDUINO)/WString.cpp \
$(ARDUINO)/Print.cpp \
$(ARDUINO)/HardwareSerial.cpp

ARDUINO_LIB = \
$(wildcard $(INSTALL_DIR)/libraries/*/*.cpp) \
$(wildcard $(INSTALL_DIR)/libraries/*/*/*.cpp) \
$(wildcard $(INSTALL_DIR)/libraries/*/*/*/*.cpp) \
$(wildcard $(INSTALL_DIR)/libraries/*/*.c) \
$(wildcard $(INSTALL_DIR)/libraries/*/*/*.c) \
$(wildcard $(INSTALL_DIR)/libraries/*/*/*/*.c) \
$(wildcard ~/Documents/Arduino/Libraries/*/*.cpp) \
$(wildcard ~/Documents/Arduino/Libraries/*/*.c)
