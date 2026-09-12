# MCXN236 Image Processing - ARM GNU Toolchain Makefile
#
# Host: Windows
# Target: MCXN236 (Cortex-M33)
#
# Generates:
#   output/mcxn236_image_processing.elf
#   output/mcxn236_image_processing.bin
#   output/mcxn236_image_processing.dump
#   output/mcxn236_image_processing.map
#
# VMEM is intentionally kept as a separate conversion step until the
# required VMEM format (word width/endianness/addressing) is confirmed.

PROJECT     := mcxn236_image_processing
BUILD_DIR   := build
OUTPUT_DIR  := output

TOOLCHAIN   := toolchain/bin
CC          := $(TOOLCHAIN)/arm-none-eabi-gcc.exe
AS          := $(TOOLCHAIN)/arm-none-eabi-gcc.exe
OBJCOPY     := $(TOOLCHAIN)/arm-none-eabi-objcopy.exe
OBJDUMP     := $(TOOLCHAIN)/arm-none-eabi-objdump.exe
SIZE        := $(TOOLCHAIN)/arm-none-eabi-size.exe

LINKER      := linker/MCXN236_flash_ns.ld

CPU_FLAGS   := -mcpu=cortex-m33 -mthumb

CFLAGS      := $(CPU_FLAGS) \
               -ffunction-sections \
               -fdata-sections \
               -fno-common \
               -Wall \
               -Wextra \
               -Og \
               -g3

ASFLAGS     := $(CPU_FLAGS) \
               -x assembler-with-cpp \
               -g3

CPPFLAGS    := -Iinclude \
               -Idrivers/include \
               -Idevice \
               -Istartup \
               -Itoolchain/arm-none-eabi/include

LDFLAGS     := $(CPU_FLAGS) \
               -T$(LINKER) \
               -Wl,-Map=$(OUTPUT_DIR)/$(PROJECT).map \
               -Wl,--gc-sections \
               -Wl,--print-memory-usage \
               --specs=nosys.specs

C_SOURCES := $(wildcard src/*.c) \
             $(wildcard drivers/src/*.c) \
             $(wildcard startup/*.c)

ASM_SOURCES := $(wildcard startup/*.S)

C_OBJECTS   := $(patsubst %.c,$(BUILD_DIR)/%.o,$(C_SOURCES))
ASM_OBJECTS := $(patsubst %.S,$(BUILD_DIR)/%.o,$(ASM_SOURCES))
OBJECTS     := $(C_OBJECTS) $(ASM_OBJECTS)

ELF         := $(OUTPUT_DIR)/$(PROJECT).elf
BIN         := $(OUTPUT_DIR)/$(PROJECT).bin
DUMP        := $(OUTPUT_DIR)/$(PROJECT).dump
MAP         := $(OUTPUT_DIR)/$(PROJECT).map

.PHONY: all clean info

all: $(ELF) $(BIN) $(DUMP)
	@echo.
	@echo Build complete.
	@$(SIZE) $(ELF)

$(ELF): $(OBJECTS) $(LINKER) | $(OUTPUT_DIR)
	@echo [LD] $@
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(BIN): $(ELF) | $(OUTPUT_DIR)
	@echo [BIN] $@
	$(OBJCOPY) -O binary $< $@

$(DUMP): $(ELF) | $(OUTPUT_DIR)
	@echo [DUMP] $@
	$(OBJDUMP) -d -S -x $< > $@

$(BUILD_DIR)/%.o: %.c
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	@echo [CC] $<
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.S
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	@echo [AS] $<
	$(AS) $(CPPFLAGS) $(ASFLAGS) -c $< -o $@

$(OUTPUT_DIR):
	@if not exist "$(OUTPUT_DIR)" mkdir "$(OUTPUT_DIR)"

info:
	@echo Compiler: $(CC)
	@echo Linker:   $(LINKER)
	@echo CPU:      cortex-m33
	@echo Outputs:  $(OUTPUT_DIR)

clean:
	@if exist "$(BUILD_DIR)" rmdir /S /Q "$(BUILD_DIR)"
	@if exist "$(OUTPUT_DIR)" rmdir /S /Q "$(OUTPUT_DIR)"
	@echo Clean complete.
