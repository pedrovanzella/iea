all: prepare client server managequestions

client: bin/client
server: bin/server
managequestions: bin/managequestions

CXX = clang++
CXXFLAGS = -Wall

LIBS = -lboost_system-mt

CLIENT_OBJS = objs/client/main.o
SERVER_OBJS = objs/server/main.o objs/server/question.o objs/server/player.o objs/server/team.o
MANAGEQUESTIONS_OBJS = objs/server/question.o objs/server/managequestions.o
SHARED_OBJS = objs/shared/message.o

prepare:
	mkdir -p objs/{client,server,shared} bin
	cp examples/questionsdb bin/questionsdb

bin/managequestions: $(MANAGEQUESTIONS_OBJS) $(SHARED_OBJS)
	$(CXX) $(CXXFLAGS) $(LIBS) $(MANAGEQUESTIONS_OBJS) $(SHARED_OBJS) -o bin/managequestions

bin/client: $(CLIENT_OBJS) $(SHARED_OBJS)
	$(CXX) $(CXXFLAGS) $(LIBS) $(CLIENT_OBJS) $(SHARED_OBJS) -o bin/client

bin/server: $(SERVER_OBJS) $(SHARED_OBJS)
	$(CXX) $(CXXFLAGS) $(LIBS) $(SERVER_OBJS) $(SHARED_OBJS) -o bin/server

objs/client/main.o: src/client/main.cpp
	$(CXX) $(CXXFLAGS) -c src/client/main.cpp -o objs/client/main.o

objs/server/main.o: src/server/main.cpp
	$(CXX) $(CXXFLAGS) -c src/server/main.cpp -o objs/server/main.o

objs/server/question.o: src/server/question.cpp src/server/question.hpp
	$(CXX) $(CXXFLAGS) -c src/server/question.cpp -o objs/server/question.o

objs/server/managequestions.o: src/server/managequestions.cpp
	$(CXX) $(CXXFLAGS) -c src/server/managequestions.cpp -o objs/server/managequestions.o

objs/server/player.o: src/server/player.cpp src/server/player.hpp
	$(CXX) $(CXXFLAGS) -c src/server/player.cpp -o objs/server/player.o

objs/server/team.o: src/server/team.cpp src/server/team.hpp
	$(CXX) $(CXXFLAGS) -c src/server/team.cpp -o objs/server/team.o

objs/shared/message.o: src/shared/message.cpp src/shared/message.hpp
	$(CXX) $(CXXFLAGS) -c src/shared/message.cpp -o objs/shared/message.o

clean:
	rm -r objs bin
