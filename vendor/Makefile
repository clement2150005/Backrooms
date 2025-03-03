NAME = SDL2 SDL2_image SDL2_mixer
ARCH ?= $(shell uname -m) # Default to current architecture
PREFIX = ../libs
LIB_DIR = $(PREFIX)/lib
INCLUDE_DIR = $(PREFIX)/include

SDL2_DIR = SDL2-2.28.5
SDL2_IMAGE_DIR = SDL2_image-2.8.6
SDL2_MIXER_DIR = SDL2_mixer-2.8.1

SDL2_BUILD = $(SDL2_DIR)/build
SDL2_IMAGE_BUILD = $(SDL2_IMAGE_DIR)/build
SDL2_MIXER_BUILD = $(SDL2_MIXER_DIR)/build

CMAKE_FLAGS = -DCMAKE_INSTALL_PREFIX=$(PREFIX) \
              -DCMAKE_OSX_ARCHITECTURES=$(ARCH) \
              -DCMAKE_OSX_DEPLOYMENT_TARGET=10.15 \
              -DSDL_STATIC=ON \
              -DSDL2_DIR=$(CURDIR)/SDL2-2.28.5/build \
              -DSDL2_LIBRARY=$(CURDIR)/SDL2-2.28.5/build/libSDL2.a \
              -DSDL2_INCLUDE_DIR=$(CURDIR)/SDL2-2.28.5/include \
              -DSDL2MAIN_LIBRARY=$(CURDIR)/SDL2-2.28.5/build/libSDL2main.a \
              -DCMAKE_DISABLE_FIND_PACKAGE_SDL2=ON \
              -DCMAKE_C_FLAGS="-Wno-deprecated-declarations"

FRAMEWORKS = -DCMAKE_EXE_LINKER_FLAGS="-framework Cocoa -framework CoreVideo \
                                       -framework IOKit -framework AudioToolbox \
                                       -framework CoreAudio -framework AVFoundation \
                                       -framework ForceFeedback -framework GameController \
                                       -framework CoreServices -framework Carbon \
                                       -framework Metal -framework CoreHaptics \
									   -liconv"

all: $(LIB_DIR) $(INCLUDE_DIR) $(NAME) copy_libs copy_headers

$(LIB_DIR) $(INCLUDE_DIR):
	mkdir -p $@

$(SDL2_BUILD):
	mkdir -p $@

$(SDL2_IMAGE_BUILD):
	mkdir -p $@

$(SDL2_MIXER_BUILD):
	mkdir -p $@

SDL2: $(SDL2_BUILD)
	cd $(SDL2_BUILD) && cmake .. $(CMAKE_FLAGS) $(FRAMEWORKS) -DSDL_HAPTIC=ON && make && make install

SDL2_image: $(SDL2_IMAGE_BUILD)
	cd $(SDL2_IMAGE_BUILD) && cmake .. $(CMAKE_FLAGS) $(FRAMEWORKS) && make && make install

SDL2_mixer: $(SDL2_MIXER_BUILD)
	cd $(SDL2_MIXER_BUILD) && cmake .. $(CMAKE_FLAGS) $(FRAMEWORKS) && make && make install

copy_libs:
	cp -f $(SDL2_BUILD)/libSDL2.a $(LIB_DIR)/
	cp -f $(SDL2_IMAGE_BUILD)/libSDL2_image.a $(LIB_DIR)/
	cp -f $(SDL2_MIXER_BUILD)/libSDL2_mixer.a $(LIB_DIR)/

copy_headers:
	mkdir -p $(INCLUDE_DIR)/SDL2
	cp -rf $(SDL2_DIR)/include/* $(INCLUDE_DIR)/SDL2/
	cp -rf $(SDL2_IMAGE_DIR)/include/* $(INCLUDE_DIR)/SDL2/
	cp -rf $(SDL2_MIXER_DIR)/include/* $(INCLUDE_DIR)/SDL2/

clean:
	rm -rf $(SDL2_BUILD) $(SDL2_IMAGE_BUILD) $(SDL2_MIXER_BUILD)

fclean: clean
	rm -rf $(PREFIX)

re: fclean all

x86_64:
	$(MAKE) ARCH=x86_64

arm64:
	$(MAKE) ARCH=arm64
