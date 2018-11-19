CPP=g++
LDFLAGS= -I. -lGL -lGLEW -lglfw
# DEPS= Mesh.hpp Shader.hpp
OBJ=Mesh.o firstTrigProjections.o Shader.o Window.o Camera.o

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