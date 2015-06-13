# export all variables to sub-make processes
.EXPORT_ALL_VARIABLES: #export

ARCH = intel64

ROOTDIR = $(abspath $(dir $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))))
INCDIR = $(ROOTDIR)/include
SRCDIR = $(ROOTDIR)/src
BLDDIR = build/$(ARCH)
OUTDIR = lib/$(ARCH)

OUTNAME = $(shell basename $(ROOTDIR))
HEADERS = $(shell ls -1 $(INCDIR)/*.h   2> /dev/null | tr "\n" " ") \
          $(shell ls -1 $(SRCDIR)/*.hpp 2> /dev/null | tr "\n" " ") \
          $(shell ls -1 $(SRCDIR)/*.hxx 2> /dev/null | tr "\n" " ") \
          $(shell ls -1 $(SRCDIR)/*.hh 2>  /dev/null | tr "\n" " ")
CPPSRCS = $(shell ls -1 $(SRCDIR)/*.cpp 2> /dev/null | tr "\n" " ")
CXXSRCS = $(shell ls -1 $(SRCDIR)/*.cxx 2> /dev/null | tr "\n" " ")
CCXSRCS = $(shell ls -1 $(SRCDIR)/*.cc  2> /dev/null | tr "\n" " ")
CSOURCS = $(shell ls -1 $(SRCDIR)/*.c   2> /dev/null | tr "\n" " ")
SOURCES = $(CPPSRCS) $(CXXSRCS) $(CCXSRCS) $(CSOURCS)
CPPOBJS = $(patsubst %,$(BLDDIR)/%,$(notdir $(CPPSRCS:.cpp=-cpp.o)))
CXXOBJS = $(patsubst %,$(BLDDIR)/%,$(notdir $(CXXSRCS:.cxx=-cxx.o)))
CCXOBJS = $(patsubst %,$(BLDDIR)/%,$(notdir $(CCXSRCS:.cc=-cc.o)))
COBJCTS = $(patsubst %,$(BLDDIR)/%,$(notdir $(CSOURCS:.c=-c.o)))
OBJECTS = $(CPPOBJS) $(CXXOBJS) $(CCXOBJS) $(COBJCTS)

CXXFLAGS = $(NULL)
CFLAGS = $(NULL)
DFLAGS = -DLIBXSTREAM_EXPORTED
IFLAGS = -I$(INCDIR)

STATIC ?= 1
DBG ?= 0

parent = $(subst ?, ,$(firstword $(subst /, ,$(subst $(NULL) ,?,$(patsubst ./%,%,$1)))))

ICPC = $(notdir $(shell which icpc 2> /dev/null))
ICC = $(notdir $(shell which icc 2> /dev/null))
GPP = $(notdir $(shell which g++ 2> /dev/null))
GCC = $(notdir $(shell which gcc 2> /dev/null))

ifneq (,$(ICPC))
	CXX = $(ICPC)
	ifeq (,$(ICC))
		CC = $(CXX)
	endif
	AR = xiar
else
	CXX = $(GPP)
endif
ifneq (,$(ICC))
	CC = $(ICC)
	ifeq (,$(ICPC))
		CXX = $(CC)
	endif
	AR = xiar
else
	CC = $(GCC)
endif
ifneq ($(CXX),)
	LD = $(CXX)
endif
ifeq ($(LD),)
	LD = $(CC)
endif

ifneq (,$(filter icpc icc,$(CXX) $(CC)))
	CXXFLAGS += -fPIC -Wall -std=c++0x
	CFLAGS += -fPIC -Wall -std=c99
	DFLAGS += -DUSE_MKL
	ifeq (0,$(DBG))
		CXXFLAGS += -fno-alias -ansi-alias -O3 -ipo -openmp
		CFLAGS += -fno-alias -ansi-alias -O3 -ipo -openmp
		LDFLAGS += -openmp
		DFLAGS += -DNDEBUG
		ifeq ($(AVX),1)
			CXXFLAGS += -xAVX
			CFLAGS += -xAVX
		else ifeq ($(AVX),2)
			CXXFLAGS += -xCORE-AVX2
			CFLAGS += -xCORE-AVX2
		else ifeq ($(AVX),3)
			CXXFLAGS += -xCOMMON-AVX512
			CFLAGS += -xCOMMON-AVX512
		else
			CXXFLAGS += -xHost
			CFLAGS += -xHost
		endif
	else ifneq (1,$(DBG))
		CXXFLAGS += -O0 -g3 -gdwarf-2 -debug inline-debug-info
		CFLAGS += -O0 -g3 -gdwarf-2 -debug inline-debug-info
	else
		CXXFLAGS += -O0 -g -openmp
		CFLAGS += -O0 -g -openmp
		LDFLAGS += -openmp
	endif
	ifeq (0,$(OFFLOAD))
		CXXFLAGS += -no-offload
		CFLAGS += -no-offload
	else
		#CXXFLAGS += -offload-option,mic,compiler,"-O2 -opt-assume-safe-padding"
		#CFLAGS += -offload-option,mic,compiler,"-O2 -opt-assume-safe-padding"
	endif
	LDFLAGS += -fPIC
	ifneq ($(STATIC),0)
		ifneq ($(STATIC),)
			LDFLAGS += -no-intel-extensions -static-intel
		endif
	endif
else # GCC assumed
	CXXFLAGS += -Wall
	CFLAGS += -Wall
	ifeq (0,$(DBG))
		CXXFLAGS += -O3 -fopenmp
		CFLAGS += -O3 -fopenmp
		LDFLAGS += -fopenmp
		DFLAGS += -DNDEBUG
		ifeq ($(AVX),1)
			CXXFLAGS += -mavx
			CFLAGS += -mavx
		else ifeq ($(AVX),2)
			CXXFLAGS += -mavx2
			CFLAGS += -mavx2
		else ifeq ($(AVX),3)
			CXXFLAGS += -mavx512f
			CFLAGS += -mavx512f
		else
			CXXFLAGS += -march=native
			CFLAGS += -march=native
		endif
	else ifneq (1,$(DBG))
		CXXFLAGS += -O0 -g3 -gdwarf-2
		CFLAGS += -O0 -g3 -gdwarf-2
	else
		CXXFLAGS += -O0 -g -fopenmp
		CFLAGS += -O0 -g -fopenmp
		LDFLAGS += -fopenmp
	endif
	ifneq ($(OS),Windows_NT)
		CXXFLAGS += -fPIC
		CFLAGS += -fPIC
		LDFLAGS += -fPIC
	endif
	ifneq ($(STATIC),0)
		ifneq ($(STATIC),)
			LDFLAGS += -static
		endif
	endif
endif

ifeq (,$(CXXFLAGS))
	CXXFLAGS = $(CFLAGS)
endif
ifeq (,$(CFLAGS))
	CFLAGS = $(CXXFLAGS)
endif

ifneq ($(STATIC),0)
	LIBEXT := a
else
	LIBEXT := so
endif

.PHONY: all
all: $(OUTDIR)/$(OUTNAME).$(LIBEXT)

$(OUTDIR)/$(OUTNAME).$(LIBEXT): $(OBJECTS)
	@mkdir -p $(OUTDIR)
ifeq ($(STATIC),0)
	$(LD) -shared -o $@ $(LDFLAGS) $^
else
	$(AR) -rs $@ $^
endif

$(BLDDIR)/%-c.o: $(SRCDIR)/%.c $(HEADERS) $(ROOTDIR)/Makefile
	@mkdir -p $(BLDDIR)
	$(CC) $(CFLAGS) $(DFLAGS) $(IFLAGS) -c $< -o $@

$(BLDDIR)/%-cpp.o: $(SRCDIR)/%.cpp $(HEADERS) $(ROOTDIR)/Makefile
	@mkdir -p $(BLDDIR)
	$(CXX) $(CXXFLAGS) $(DFLAGS) $(IFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@rm -f $(OBJECTS)

.PHONY: realclean
realclean:
	@rm -rf $(call parent,$(BLDDIR))
	@rm -rf $(call parent,$(OUTDIR))

install: all
	@cp -r $(INCDIR) . 2> /dev/null || true
	@rm -rf $(call parent,$(BLDDIR))

