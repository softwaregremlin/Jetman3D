TARGET		:= JetMan-3D
SOURCES		:= .
			
INCLUDES	:= include

LIBS = -lvitaGL -lc -lSceCommonDialog_stub -lm -lSceGxm_stub -lSceDisplay_stub -lSceAppMgr_stub -lSceCtrl_stub -lmathneon -lSceAudio_stub -lvorbisenc -lvorbisfile -lvorbis -logg -lm


#CFILES   := $(foreach dir,$(SOURCES), $(wildcard $(dir)/*.c))
CFILES   := $(foreach dir,$(SOURCES), $(wildcard $(dir)/main.c))
CPPFILES   := $(foreach dir,$(SOURCES), $(wildcard $(dir)/*.cpp))
BINFILES := $(foreach dir,$(DATA), $(wildcard $(dir)/*.bin))
OBJS     := $(addsuffix .o,$(BINFILES)) $(CFILES:.c=.o) $(CPPFILES:.cpp=.o) 

PREFIX  = arm-vita-eabi
CC      = $(PREFIX)-gcc
CXX      = $(PREFIX)-g++
CFLAGS  = -g -Wl,-q -O2 -ftree-vectorize
CXXFLAGS  = $(CFLAGS) -fno-exceptions -std=gnu++11 -fpermissive
ASFLAGS = $(CFLAGS)

all: $(TARGET).vpk

$(TARGET).vpk: eboot.bin
	vita-mksfoex -s TITLE_ID=VGLJETMAN "$(TARGET)" param.sfo
	vita-pack-vpk -s param.sfo -b eboot.bin \
	--add data/textures/aliens.png=data/textures/aliens.png \
	--add data/textures/astro.png=data/textures/astro.png \
	--add data/textures/explosion.png=data/textures/explosion.png \
	--add data/textures/GroundTexture.png=data/textures/GroundTexture.png \
	--add data/textures/intro.png=data/textures/intro.png \
	--add data/textures/laser.png=data/textures/laser.png \
	--add data/textures/particle.png=data/textures/particle.png \
	--add data/textures/rockets.png=data/textures/rockets.png \
	--add data/textures/spectrumChars.png=data/textures/spectrumChars.png \
	--add data/sounds/Explosion.ogg=data/sounds/Explosion.ogg \
	--add data/sounds/Intro.ogg=data/sounds/Intro.ogg \
	--add data/sounds/Laser.ogg=data/sounds/Laser.ogg \
	--add data/sounds/LevelStart.ogg=data/sounds/LevelStart.ogg \
	--add data/sounds/Rocket.ogg=data/sounds/Rocket.ogg \
	--add data/sounds/RocketAssemble.ogg=data/sounds/RocketAssemble.ogg \
	--add data/sounds/RocketDesc.ogg=data/sounds/RocketDesc.ogg \
	--add data/sounds/RocketPickup.ogg=data/sounds/RocketPickup.ogg \
	--add data/sounds/TrinketPickup.ogg=data/sounds/TrinketPickup.ogg \
	--add data/models/aliens/1.bin=data/models/aliens/1.bin \
	--add data/models/aliens/2.bin=data/models/aliens/2.bin \
	--add data/models/aliens/3.bin=data/models/aliens/3.bin \
	--add data/models/aliens/4.bin=data/models/aliens/4.bin \
	--add data/models/aliens/5.bin=data/models/aliens/5.bin \
	--add data/models/aliens/6.bin=data/models/aliens/6.bin \
	--add data/models/aliens/7.bin=data/models/aliens/7.bin \
	--add data/models/aliens/8.bin=data/models/aliens/8.bin \
	--add data/models/background/1.bin=data/models/background/1.bin \
	--add data/models/gas/1.bin=data/models/gas/1.bin \
	--add data/models/ground/1.bin=data/models/ground/1.bin \
	--add data/models/intro/1.bin=data/models/intro/1.bin \
	--add data/models/jetman/1.bin=data/models/jetman/1.bin \
	--add data/models/jetman/legs/1.bin=data/models/jetman/legs/1.bin \
	--add data/models/jetman/legs/2.bin=data/models/jetman/legs/2.bin \
	--add data/models/jetman/legs/3.bin=data/models/jetman/legs/3.bin \
	--add data/models/jetman/legs/4.bin=data/models/jetman/legs/4.bin \
	--add data/models/jetman/legs/5.bin=data/models/jetman/legs/5.bin \
	--add data/models/jetman/legs/6.bin=data/models/jetman/legs/6.bin \
	--add data/models/platforms/1.bin=data/models/platforms/1.bin \
	--add data/models/rockets/1.bin=data/models/rockets/1.bin \
	--add data/models/rockets/2.bin=data/models/rockets/2.bin \
	--add data/models/rockets/3.bin=data/models/rockets/3.bin \
	--add data/models/rockets/4.bin=data/models/rockets/4.bin \
	--add data/models/trinkets/1.bin=data/models/trinkets/1.bin \
	--add data/models/trinkets/2.bin=data/models/trinkets/2.bin \
	--add data/models/trinkets/3.bin=data/models/trinkets/3.bin \
	--add data/models/trinkets/4.bin=data/models/trinkets/4.bin \
	--add data/models/trinkets/5.bin=data/models/trinkets/5.bin \
	--add sce_sys/icon0.png=sce_sys/icon0.png \
	--add sce_sys/livearea/contents/bg.png=sce_sys/livearea/contents/bg.png \
	--add sce_sys/livearea/contents/startup.png=sce_sys/livearea/contents/startup.png \
	--add sce_sys/livearea/contents/template.xml=sce_sys/livearea/contents/template.xml	\
	$@

eboot.bin: $(TARGET).velf
	vita-make-fself -s $< eboot.bin	
	
%.velf: %.elf
	vita-elf-create $< $@
	
$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@
	
clean:
	@rm -rf *.velf *.elf *.vpk $(OBJS) param.sfo eboot.bin

# curl -T eboot.bin ftp://192.168.1.20:1337/ux0:/app/VITAGL005/
