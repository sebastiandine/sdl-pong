build:
	g++ src/objects/Ball.cpp src/objects/Player.cpp src/objects/Score.cpp src/scenes/Scene.cpp src/scenes/Menu.cpp src/scenes/GameOver.cpp src/scenes/PlayerVsCpu.cpp main.cpp -lSDL2 -lSDL2_ttf -lSDL2_mixer -o sdl2pong
run:
	./sdl2pong
clean:
	rm sdl2pong
build-sanitize:
	g++ -fsanitize=address src/objects/Ball.cpp src/objects/Player.cpp src/objects/Score.cpp src/scenes/Scene.cpp src/scenes/Menu.cpp src/scenes/GameOver.cpp src/scenes/PlayerVsCpu.cpp main.cpp -lSDL2 -lSDL2_ttf -lSDL2_mixer -o sdl2pong-sanitize

pack:
	mkdir -p target && tar -czvf target/sdl2-pong.tar.gz assets sdl2pong
