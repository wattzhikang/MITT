src = src
bin = bin
gen = bin/generated_files

objs = $(gen)/main.o\
	$(gen)/Planet.o\
	$(gen)/FileReader.o\
	$(gen)/ConfigFile.o\
	$(gen)/GravitationalSystem.o\

$(bin)/mitt : $(objs)
	@ echo "Linking MITT"
	@ g++ -g -Wall $^ -o $@

$(gen)/%.o : $(src)/%.cpp
	@ echo Compiling $<
	@ g++ -g -Wall -c $< -o $@

clean : 
	rm $(objs)
