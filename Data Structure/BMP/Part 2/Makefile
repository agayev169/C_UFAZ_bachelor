CMP=g++
ARGS=-g -W -std=c++14
SRC=src/*
OUT=out/*
PSFSRC=src/psf.cpp
RESSRC=src/resize.cpp
GLUSRC=src/glue.cpp

$(OUT):$(SRC)
	echo $(OUT)
	if [ ! -d "out" ]; \
	then \
	mkdir out; \
	fi; \
	$(CMP) $(ARGS) $(PSFSRC) -o out/psf 
	$(CMP) $(ARGS) $(RESSRC) -o out/resize 
	$(CMP) $(ARGS) $(GLUSRC) -o out/glue
	cp src/resize_all.sh out/resize_all.sh

rm:
	rm -r out