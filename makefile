CC = g++ -g
CCFLAGS = -I./inc -Iglm -o glsl
LDFLAGS = `pkg-config --static --libs glfw3 glew`

glsl: src/main.cpp src/engine.cpp src/shader.cpp
	$(CC) $(CCFLAGS) src/main.cpp src/engine.cpp src/shader.cpp $(LDFLAGS)
	./glsl

clean:
	rm glsl

.PHONY: all glsl clean
