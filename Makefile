LIBS=-lGL -lglfw -lGLEW
HEADERS=stb_image.h allmodels.h  constants.h model.h podloga.h dachy.h sciany.h smiglo.h helikopter.h
FILES=stb_image.cpp main_file.cpp  model.cpp  podloga.cpp dachy.cpp sciany.cpp smiglo.cpp helikopter.cpp

main_file: $(FILES) $(HEADERS)
	g++ -o main_file $(FILES)  $(LIBS) -I.
