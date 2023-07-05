Debug:
	g++ -c src/*.cpp src/algorithm/*.cpp src/graphics/*.cpp -std=c++14 -g -Wall -m64 -I include -I"D:\C++\libraries\SDL2-w64\include"
	g++ *.o -o bin/debug/main -L"D:\C++\libraries\SDL2-w64\lib" -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic
	rm -f *.o
	start bin/debug/main

Release:
	g++ -c src/*.cpp src/algorithm/*.cpp src/graphics/*.cpp -std=c++14 -O3 -Wall -m64 -I include -I"D:\C++\libraries\SDL2-w64\include"
	g++ *.o -o bin/release/main -s -L"D:\C++\libraries\SDL2-w64\lib" -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic -mwindows -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid -static-libgcc
	rm -f *.o
	start bin/release/main