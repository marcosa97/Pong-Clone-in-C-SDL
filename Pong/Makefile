INCLUDES = -I /usr/include/SDL2/

LIBS = -lSDL2 -lGL -lSDL2_image -lSDL2_ttf

Pong.out: main.o game.o gameOver.o graphics.o intro.o play.o texture.o timer.o title.o 
	g++ -Wall -g $(INCLUDES) -o Pong.out main.o game.o gameOver.o graphics.o intro.o play.o texture.o timer.o title.o $(LIBS)

main.o: main.cpp game.h gameState.h
	g++ -Wall -g $(INCLUDES) $(LIBS) -c main.cpp

game.o: game.cpp game.h
	g++ -Wall -g $(INCLUDES) $(LIBS) -c game.cpp

gameOver.o: gameOver.cpp gameOver.h
	g++ -Wall -g $(INCLUDES) $(LIBS) -c gameOver.cpp

graphics.o: graphics.cpp graphics.h texture.h
	g++ -Wall -g $(INCLUDES) $(LIBS) -c graphics.cpp

intro.o: intro.cpp intro.h
	g++ -Wall -g $(INCLUDES) $(LIBS) -c intro.cpp

play.o: play.cpp play.h
	g++ -Wall -g $(INCLUDES) $(LIBS) -c play.cpp

texture.o: texture.cpp texture.h graphics.h
	g++ -Wall -g $(INCLUDES) $(LIBS) -c texture.cpp

timer.o: timer.cpp timer.h
	g++ -Wall -g $(INCLUDES) $(LIBS) -c timer.cpp

title.o: title.cpp title.h
	g++ -Wall -g $(INCLUDES) $(LIBS) -c title.cpp

clean:
	rm -f main.o game.o gameOver.o graphics.o intro.o play.o texture.o timer.o title.o
