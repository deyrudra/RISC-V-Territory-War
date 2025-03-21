# Created by the FPGAcademy Monitor Program
# DO NOT MODIFY

############################################
# Path Environment Variable

# Cygwin path to the Nios V GNU Toolchain
export PATH := /home/compiler/bin/:$(PATH)
export PATH := /cygdrive/c/intelFPGA/23.1std/quartus/bin64/:$(PATH)
export PATH := /cygdrive/c/intelFPGA/23.1std/quartus/sopc_builder/bin/:$(PATH)

export PATH := C:/intelFPGA/23.1std/quartus/bin64/:$(PATH)
export PATH := C:/intelFPGA/23.1std/quartus/sopc_builder/bin/:$(PATH)
export PATH := C:/intelFPGA/23.1std/riscfree/debugger/gdbserver-riscv/:$(PATH)
export PATH := C:/intelFPGA/23.1std/riscfree/toolchain/riscv32-unknown-elf/bin/:$(PATH)

############################################
# Global Macros

DEFINE_COMMA			:= ,

############################################
# Compilation Macros

# Programs
AS		:= riscv32-unknown-elf-as
CC		:= riscv32-unknown-elf-gcc
LD		:= riscv32-unknown-elf-ld
OC		:= riscv32-unknown-elf-objcopy
OD		:= riscv32-unknown-elf-objdump
NM		:= riscv32-unknown-elf-nm
RM		:= rm -f

# Flags
USERCCFLAGS	:= -g -O1 -ffunction-sections -fverbose-asm -fno-inline -gdwarf-2
USERLDFLAGS	:= -Wl,--defsym=__stack_pointer$$=0x4000000 -Wl,--defsym  -Wl,JTAG_UART_BASE=0xff201000 -lm
ARCHASFLAGS	:= -march=rv32im_zicsr --gdwarf2
ARCHCCFLAGS	:= -march=rv32im_zicsr -mabi=ilp32
ARCHLDFLAGS	:= -march=rv32im_zicsr -mabi=ilp32
ARCHLDSCRIPT	:=
ASFLAGS		:= $(ARCHASFLAGS)
CCFLAGS		:= -Wall -c $(USERCCFLAGS) $(ARCHCCFLAGS)
LDFLAGS		:= $(USERLDFLAGS) $(ARCHLDFLAGS)
OCFLAGS		:= -O srec

# Files
ELF		:= main
ELFEXT		:= .elf
HDRS		:=
SRCS		:= ../game/main.c ../game/objecthandler.c ../game/loadassets.c
OBJS		:= $(patsubst %, %.o, $(SRCS))

############################################
# GDB Macros

# Programs
GDB_SERVER		:= ash-riscv-gdb-server.exe
GDB_CLIENT		:= riscv32-unknown-elf-gdb.exe

############################################
# System Macros

# Programs
SYS_PROG_QP_PROGRAMMER	:= quartus_pgm.exe
SYS_PROG_QP_HPS			:= quartus_hps.exe
SYS_PROG_SYSTEM_CONSOLE	:= system-console.exe
SYS_PROG_NII_GDB_SERVER	:= nios2-gdb-server.exe

# Flags
SYS_FLAG_CABLE			:= -c ""
SYS_FLAG_USB			:= ""
SYS_FLAG_JTAG_INST		:= --instance
SYS_FLAG_NII_HALT		:= --stop

# Default argument values
SYS_ARG_JTAG_INDEX		:= 1
SYS_ARG_GDB_PORT		:= 2399

# Files
SYS_FILE_SOF			:= "C:/intelFPGA/23.1std/fpgacademy/Computer_Systems/DE1-SoC/DE1-SoC_Computer/niosVg/DE1_SoC_Computer.sof"
SYS_SCRIPT_JTAG_ID		:= --script="C:/intelFPGA/23.1std/fpgacademy/AMP/bin/jtag_instance_check.tcl"
SYS_FILE_ARM_PL			:= --preloader "C:/intelFPGA/23.1std/fpgacademy/AMP/arm_tools/u-boot-spl.de1-soc.srec"
SYS_FLAG_ARM_PL_ADDR	:= --preloaderaddr 0xffff13a0

############################################
# Compilation Targets

COMPILE: $(ELF).srec

$(ELF).srec: $(ELF)$(ELFEXT)
	$(RM) $@
	$(OC) $(OCFLAGS) $< $@

SYMBOLS: $(ELF)$(ELFEXT)
	$(NM) -p $<

OBJDUMP: $(ELF)$(ELFEXT)
	$(OD) -d -S $<


$(ELF)$(ELFEXT): $(OBJS)
	$(RM) $@
	$(CC) $(LDFLAGS) $(OBJS) -o $@

%.c.o: %.c $(HDRS)
	$(RM) $@
	$(CC) $(CCFLAGS) $< -o $@

%.s.o: %.s $(HDRS)
	$(RM) $@
	$(AS) $(ASFLAGS) $< -o $@

CLEAN: 
	$(RM) $(ELF).srec $(ELF)$(ELFEXT) $(OBJS)

############################################
# System Targets

DETECT_DEVICES:
	$(SYS_PROG_QP_PROGRAMMER) $(SYS_FLAG_CABLE) --auto

ARM_RUN_PRELOADER:
	$(SYS_PROG_QP_HPS) $(SYS_FLAG_CABLE) -o GDBSERVER -gdbport0 $(SYS_ARG_GDB_PORT) $(SYS_FILE_ARM_PL) $(SYS_FLAG_ARM_PL_ADDR) 

DOWNLOAD_SYSTEM:
	$(SYS_PROG_QP_PROGRAMMER) $(SYS_FLAG_CABLE) -m jtag -o P;$(SYS_FILE_SOF)@$(SYS_ARG_JTAG_INDEX) 

CHECK_JTAG_ID:
	$(SYS_PROG_SYSTEM_CONSOLE) $(SYS_SCRIPT_JTAG_ID) $(SYS_FLAG_USB) $(SYS_FILE_SOF) 

HALT_NII:
	$(SYS_PROG_NII_GDB_SERVER) $(SYS_FLAG_CABLE) $(SYS_FLAG_JTAG_INST) $(SYS_ARG_JTAG_INDEX) $(SYS_FLAG_NII_HALT) 

TERMINAL:
	nios2-terminal.exe --instance 0

############################################
# GDB Targets

START_GDB_SERVER: 
	$(GDB_SERVER) --device 02D120DD --gdb-port 2454 --instance 1 --probe-type USB-Blaster-2 --transport-type jtag --auto-detect true

START_GDB_CLIENT: 
	$(GDB_CLIENT) "$(ELF)$(ELFEXT)"

############################################
# EXTRAS

.SILENT: SYMBOLS OBJDUMP