all: prepare bin/client bin/server

CXX = clang++
CXXFLAGS = -Wall
CLIENT_OBJS = objs/client/main.o
SERVER_OBJS = objs/server/main.o
SHARED_OBJS = 

prepare:
	mkdir -p objs/{client,server} bin

bin/client: $(CLIENT_OBJS) $(SHARED_OBJS)
	$(CXX) $(CXXFLAGS) $(CLIENT_OBJS) $(SHARED_OBJS) -o bin/client

bin/server: $(SERVER_OBJS) $(SHARED_OBJS)
	$(CXX) $(CXXFLAGS) $(SERVER_OBJS) $(SHARED_OBJS) -o bin/server

objs/client/main.o:
	$(CXX) $(CXXFLAGS) -c src/client/main.cpp -o objs/client/main.o

objs/server/main.o:
	$(CXX) $(CXXFLAGS) -c src/server/main.cpp -o objs/server/main.o

clean:
	rm -r objs bin
