#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(PSL1GHT)),)
$(error "Please set PSL1GHT in your environment. export PSL1GHT=<path>")
endif

include $(PSL1GHT)/ppu_rules

TC_ADD		:=	`date +%d%H%M`
ICON0		:=	ICON0.PNG
ICON1		:=	ICON1.PAM
PIC1		:=	PIC1.PNG
SFOXML		:=	sfo.xml


#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
#---------------------------------------------------------------------------------
TARGET		:=	$(notdir $(CURDIR))
BUILD		:=	build
SOURCES		:=	src src/Mapa src/Mapa/Nodo src/Mapa/Nodo/Minijuegos src/Mapa/Nodo/NPCs src/math src/physicsEngine src/renderEngine
DATA		:=	data
INCLUDES	:=	src

TITLE		:=	Meat Starto
APPID		:=	MEAT00001
CONTENTID	:=	UP0001-$(APPID)_00-0000000000000000

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------

CFLAGS		=	-O2 -Wall -mcpu=cell $(MACHDEP) $(INCLUDE)
CXXFLAGS	=	$(CFLAGS) 

LDFLAGS		=	$(MACHDEP) -Wl,-Map,$(notdir $@).map

#---------------------------------------------------------------------------------
# any extra libraries we wish to link with the project
#---------------------------------------------------------------------------------
LIBS	:=	 -lBox2D  -lSDLmain -lSDL_image -lSDL_ttf -lSDL  -laudio  -lgcm_sys  -ltiff  -ljpgdec -ljpeg -lpng   -lgcm_sys -lrsx -lio -lcairo -lm -lfreetype -lz -lpixman-1 -lrt -lnet -lsysmodule -lxml2    -lsysutil  -llv2  
#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:= $(PORTLIBS)

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(TARGET)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
					$(foreach dir,$(DATA),$(CURDIR)/$(dir))

export DEPSDIR	:=	$(CURDIR)/$(BUILD)

export BUILDDIR	:=	$(CURDIR)/$(BUILD)

#---------------------------------------------------------------------------------
# automatically build a list of object files for our project
#---------------------------------------------------------------------------------
CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
sFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.S)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
	export LD	:=	$(CC)
else
	export LD	:=	$(CXX)
endif

export OFILES	:=	$(addsuffix .o,$(BINFILES)) \
					$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) \
					$(sFILES:.s=.o) $(SFILES:.S=.o)

#---------------------------------------------------------------------------------
# build a list of include paths
#---------------------------------------------------------------------------------
export INCLUDE	:=	$(foreach dir,$(INCLUDES), -I$(CURDIR)/$(dir)) \
					$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
					$(LIBPSL1GHT_INC) \
					-I$(CURDIR)/$(BUILD)

#---------------------------------------------------------------------------------
# build a list of library paths
#---------------------------------------------------------------------------------
export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib) \
					$(LIBPSL1GHT_LIB)

export OUTPUT	:=	$(CURDIR)/$(TARGET)
.PHONY: $(BUILD) clean

#---------------------------------------------------------------------------------
$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(BUILD) $(OUTPUT).elf $(OUTPUT).self

#---------------------------------------------------------------------------------
run:
	ps3load $(OUTPUT).self


#---------------------------------------------------------------------------------
#---------------------------------------------------------------------------------
pkg: $(BUILD) #$(OUTPUT).pkg
	$(VERB) echo building pkg ... $(notdir $@)
	$(VERB) mkdir -p $(BUILDDIR)/pkg/USRDIR
	$(VERB) cp $(ICON0) $(BUILDDIR)/pkg/ICON0.PNG
	$(VERB) cp $(PIC1) $(BUILDDIR)/pkg/PIC1.PNG
	$(VERB) cp -f $(CURDIR)/loader/EBOOT.BIN $(BUILDDIR)/pkg/USRDIR/EBOOT.BIN
	$(VERB) $(SFO) --title "$(TITLE)" --appid "$(APPID)" -f $(SFOXML) $(BUILDDIR)/pkg/PARAM.SFO
	$(VERB) if [ -n "$(PKGFILES)" -a -d "$(PKGFILES)" ]; then cp -rf $(PKGFILES)/* $(BUILDDIR)/pkg/; fi
	$(VERB) $(PKG) --contentid $(CONTENTID) $(BUILDDIR)/pkg/ $(TARGET).pkg >> /dev/null

#---------------------------------------------------------------------------------
else

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
$(OUTPUT).self: $(OUTPUT).elf
$(OUTPUT).elf:	$(OFILES)

#---------------------------------------------------------------------------------
# This rule links in binary data with the .bin extension
#---------------------------------------------------------------------------------
%.bin.o	:	%.bin
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

-include $(DEPENDS)

#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------
