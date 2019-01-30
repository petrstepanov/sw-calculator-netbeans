# Select compiler command depending on environment
OS:=$(shell uname)
ifeq ($(OS),Darwin)
  CXX=clang++
else
  CXX=g++
endif

# Define variables for directories
SRC_DIR=src
OBJ_DIR=build
BIN_DIR=dist

# Replace with your application name
APP_NAME=sw-calculator

DICT_NAME=$(APP_NAME)-dictionary
DICT_FILENAME=$(DICT_NAME).cxx             # app-dictionary.cxx
DICT_PCM_FILENAME=$(DICT_NAME)_rdict.pcm   # app-dictionary_rdict.pcm
# DSYM_DIR=sw-calculator.so.dSYM

# Compiler flags, library search paths and ROOT shared libraries names
CXXFLAGS=-O3 `root-config --cflags` -fPIC
LDFLAGS=`root-config --ldflags`
GLIBS=`root-config --glibs` -lRooFit -lRooFitCore -lHtml -lMinuit -lFumili

# Build lists of header, source and object files
H_EXT = h
HEADERS = $(shell find $(SRC_DIR) -type f -name *.$(H_EXT))
HEADERS := $(filter-out $(SRC_DIR)/LinkDef.h,$(HEADERS))

SRC_EXT = cpp
SOURCES = $(shell find $(SRC_DIR) -type f -name *.$(SRC_EXT))

OBJECTS_TEMP = $(SOURCES:.cpp=.o)
OBJECTS = $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(OBJECTS_TEMP))

# Executable and shared library files path and name
EXECUTABLE=$(BIN_DIR)/$(APP_NAME)       # src/app
SHARED_LIBRARY=$(APP_NAME)-library.so   # app-library.so

# convenience variable for making directories
dir_guard=@mkdir -p $(@D)

# Empty target ensures that list of all 'end products' are called
all: executable

debug: CXXFLAGS += -g #-ggdb -DDEBUG -g
debug: executable

executable: directories $(DICT_FILENAME) $(SHARED_LIBRARY) $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(SHARED_LIBRARY)
	@echo "Linking "$@
	$(CXX) -o $@ $(OBJECTS) $(SHARED_LIBRARY) $(GLIBS)
	# move .so library to bin folder
	mv $(SHARED_LIBRARY) $(BIN_DIR)/$(SHARED_LIBRARY)
	# change search location of the .so library to the executable directory of the app (macOS only)
ifeq ($(OS),Darwin)
	install_name_tool -change $(APP_NAME).so @executable_path/$(APP_NAME).so $(EXECUTABLE)
endif
	# move dictionary .pcm next to the app executable, remove dictionary .cxx
	mv $(DICT_PCM_FILENAME) $(BIN_DIR)/$(DICT_PCM_FILENAME)
	rm $(DICT_FILENAME)

$(DICT_FILENAME): $(HEADERS) $(SRC_DIR)/LinkDef.h
	rootcling -f $@ -c $(CXXFLAGS) -p $^

# https://root.cern.ch/interacting-shared-libraries-rootcling (they forgot $(GLIBS) damn)
$(SHARED_LIBRARY): $(DICT_FILENAME) $(SOURCES)
	$(CXX) -shared -o $@ $(LDFLAGS) $(CXXFLAGS) $(GLIBS) $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(dir_guard)
	@echo "Compiling "$@
# compile with dependency files - why?
#	$(CXX) $(CXXFLAGS) -c -g -MMD -MP -MF "$@.d" -o $@ $<
# compile with debug symbols
#	$(CXX) $(CXXFLAGS) -c -g $< -o $@
# just compile
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f -r $(OBJ_DIR)
	rm -f -r $(BIN_DIR)
	rm -f $(DICT_FILENAME)
	rm -f $(SHARED_LIBRARY)

directories:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)

echo:
	$(info SOURCES: $(SOURCES))
	$(info HEADERS: $(HEADERS))

# List of special targets that do not generate files
.PHONY: directories echo
