# Makefile for uboonecode v06_26_01_08 (and possibly later)

CPPFLAGS=-I $(BOOST_INC) \
				 -I $(CANVAS_INC) \
				 -I $(CETLIB_INC) \
				 -I $(FHICLCPP_INC) \
				 -I $(GALLERY_INC) \
				 -I $(LARCOREOBJ_INC) \
				 -I $(LARDATAOBJ_INC) \
				 -I $(NUSIMDATA_INC) \
				 -I $(UBOONECODE_INC) \
				 -I $(ROOT_INC)

CXXFLAGS=-std=c++14 #-Wall #-pedantic #-Werror
CXX=g++
LDFLAGS=$$(root-config --libs) \
				-L $(CANVAS_LIB) -l canvas_Utilities -l canvas_Persistency_Common -l canvas_Persistency_Provenance \
				-L $(CETLIB_LIB) -l cetlib \
				-L $(GALLERY_LIB) -l gallery \
				-L $(NUSIMDATA_LIB) -l nusimdata_SimulationBase \
				-L $(LARCOREOBJ_LIB) -l larcoreobj_SummaryData \
				-L $(LARDATAOBJ_LIB) -l lardataobj_Simulation -l lardataobj_RecoBase -l lardataobj_MCBase -l lardataobj_RawData -l lardataobj_OpticalDetectorData -l lardataobj_AnalysisBase \
				-L $(UBOONECODE_LIB) -l EventWeight

SBNFitConstructor: SBNFitConstructor.cxx
		@$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

all: SBNFitConstructor

clean:
	rm *.o SBNFitConstructor

