TARGET  := edugame
TARGET_FILES := main
FILES   := python_function
TEST_FILES := python_function_test

CC               := g++
LD               := g++
OBJSUFFIX	 := .o
LIBPREFIX	 := lib
STATIC_LIBSUFFIX := .a
CFLAGS 		 := -g -DBOOST_TEST_DYN_LINK
CFLAGS_PLATFORM  :=
LDFLAGS		 :=
FRAMEWORKS	 :=
LIBS		 := python2.7 boost_python dl 
TEST_LIBS	 := boost_unit_test_framework
EXESUFFIX        :=
DEPARGS          := -MD 



BOOST_VERSION=1_47_0
BOOST_LIBS=signals,thread,python,test
BOOST_ARGS= "-sBUILD="boost_unit_test_framework


# how we link to libraries depends on the platform
ARCH=$(shell uname | sed -e 's/-.*//g')

ifeq ($(ARCH), CYGWIN_NT)
# If building on Cygwin, use glut32, opengl32
EXESUFFIX := .exe
LIBS      += 
else

ifeq ($(ARCH), Darwin)
FRAMEWORKS += 
BOOST_ARGS += --with-python-root=/System/Library/Frameworks/Python.framework/Versions/2.7 "-sTOOLS=darwin" 
else
# Building on Linux
LIBS += 
BOOST
endif

endif # Not CYGWIN_END

TARGET := $(addsuffix $(EXESUFFIX), $(TARGET))
INCDIRS := . boost/include /usr/include/python2.7
LIBDIRS := boost/lib

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

.SUFFIXES: .cpp $(OBJSUFFIX)

.PHONY: clean release all

all: $(TARGET)

# Handle dependencies
-include $(patsubst %.o,%.d,$(OBJS))

$(TARGET): $(OBJS) $(TARGET_OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(TARGET_OBJS) $(LDFLAGS) $(LDLIBS) $(LDFRAMEWORKS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -o $@ -c $< $(DEPARGS)

test: $(OBJS) $(TEST_OBJS)
	$(LD) -o test $(OBJS) $(TEST_OBJS) $(LDFLAGS) $(LDLIBS) $(LDFRAMEWORKS) $(LDTESTLIBS)

boost:
	tar -xvf boost_${BOOST_VERSION}.tar.bz2
	cd boost_${BOOST_VERSION} && \
	./bootstrap.sh --prefix=../boost --libdir=../boost/lib --with-libraries=${BOOST_LIBS} && \
	./bjam variant=release link=shared install
	rm -rf boost_${BOOST_VERSION}

clean:
	rm -rf $(OBJS) $(TARGET) $(DEPS) $(TEST_OBJS) $(TEST_DEPS) $(TARGET_OBJS) $(TARGET_DEPS)
 
dist-clean:
	@make clean
	rm -rf boost

release:
	@make --no-print-directory RELEASE=1