TARGET  := edugame
TARGET_FILES := main
FILES   := #python_function
TEST_FILES := #python_function_test

CC               := g++
LD               := g++
OBJSUFFIX	 := .o
LIBPREFIX	 := lib
STATIC_LIBSUFFIX := .a
CFLAGS 		 := -g -DBOOST_TEST_DYN_LINK
CFLAGS_PLATFORM  :=
LDFLAGS		 :=
FRAMEWORKS	 :=
LIBS		 := #python2.5 boost_python dl
TEST_LIBS	 := boost_unit_test_framework
EXESUFFIX        :=
DEPARGS          := -MD



BOOST_VERSION=1_47_0
BOOST_LIBS=signals,thread,python,test
OOST_ARGS= -sBUILD=boost_unit_test_framework variant=release link=shared

TARGET := $(addsuffix $(EXESUFFIX), $(TARGET))
INCDIRS := . #boost/include /usr/include/python2.5
LIBDIRS := #boost/lib

# how we link to libraries depends on the platform
ARCH=$(shell uname | sed -e 's/-.*//g')

ifeq ($(ARCH), CYGWIN_NT)
# If building on Cygwin, use glut32, opengl32
EXESUFFIX := .exe
LIBS      +=
else

ifeq ($(ARCH), Darwin)
# Building on Os X
FRAMEWORKS +=
BOOST_ARGS += toolset=darwin architecture=x86 address-model=32
INCDIRS += irrlicht-1.7.2/include
LIBDIRS +=
LIBS +=
CFLAGS += -arch i386
LDFLAGS += -arch i386

else
# Building on Linux
endif

endif # Not CYGWIN_END

CFLAGS += $(addprefix -I, $(INCDIRS)) $(CFLAGS_PLATFORM)
LDFLAGS += $(addprefix -L, $(LIBDIRS))

LDLIBS  := $(addprefix -l, $(LIBS))
LDFRAMEWORKS := $(addprefix -framework , $(FRAMEWORKS))

OBJS := $(addsuffix $(OBJSUFFIX), $(FILES))
DEPS := $(addsuffix .d, $(FILES))

TARGET_OBJS := $(addsuffix $(OBJSUFFIX), $(TARGET_FILES))
TARGET_DEPS := $(addsuffix .d, $(TARGET_FILES))

TEST_OBJS := $(addsuffix $(OBJSUFFIX), $(TEST_FILES))
TEST_DEPS := $(addsuffix .d, $(TEST_FILES))
LDTESTLIBS += $(addprefix -l, $(TEST_LIBS))

LDLIBS += -framework OpenGL -framework Cocoa -framework Carbon -framework IOKit

.SUFFIXES: .cpp $(OBJSUFFIX)

.PHONY: clean release all

all: $(TARGET)

# Handle dependencies
-include $(patsubst %.o,%.d,$(OBJS))

ifeq ($(ARCH), Darwin)
$(TARGET): $(OBJS) $(TARGET_OBJS)
	$(LD) -o $(TARGET) irrlicht-1.7.2/source/Irrlicht/MacOSX/build/Release/libIrrlicht.a $(OBJS) $(TARGET_OBJS) $(LDFLAGS) $(LDLIBS) $(LDFRAMEWORKS)
		lipo -create edugame -output edugame.app/Contents/MacOS/edugame
else
$(TARGET): $(OBJS) $(TARGET_OBJS)
	$(LD) -o $(TARGET) irrlicht-1.7.2/source/Irrlicht/MacOSX/build/Release/libIrrlicht.a $(OBJS) $(TARGET_OBJS) $(LDFLAGS) $(LDLIBS) $(LDFRAMEWORKS)
endif

%.o: %.cpp
	$(CXX) $(CFLAGS) -o $@ -c $< $(DEPARGS)

test: $(OBJS) $(TEST_OBJS)
	$(LD) -o test $(OBJS) $(TEST_OBJS) $(LDFLAGS) $(LDLIBS) $(LDFRAMEWORKS) $(LDTESTLIBS)

boost:
	tar -xvf boost_${BOOST_VERSION}.tar.bz2
	cd boost_${BOOST_VERSION} && \
	./bootstrap.sh --prefix=../boost --libdir=../boost/lib --with-libraries=${BOOST_LIBS} && \
	./bjam ${BOOST_ARGS} install
	rm -rf boost_${BOOST_VERSION}

blah:

clean:
	rm -rf $(OBJS) $(TARGET) $(DEPS) $(TEST_OBJS) $(TEST_DEPS) $(TARGET_OBJS) $(TARGET_DEPS) test

dist-clean:
	@make clean
	rm -rf boost

release:
	@make --no-print-directory RELEASE=1