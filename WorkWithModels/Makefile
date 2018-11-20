CPP=g++
LDFLAGS= -I. -lGL -lGLEW -lglfw -lassimp
# DEPS= Mesh.hpp Shader.hpp
OBJ=Mesh.o main.o Shader.o Window.o Camera.o Texture.o Light.o Model.o

#%.o: %.cpp $(DEPS)
#	$(CPP) -c -o $@ $
exe: $(OBJ) 
	$(CPP) -o $@ $^ $(LDFLAGS)
.PHONY: exe
clean:
	rm -f $(OBJ) exe
.PHONY: clean

exec:
	./exe
.PHONY: exec