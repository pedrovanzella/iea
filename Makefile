all: prepare client server managequestions

client: bin/client
server: bin/server
managequestions: bin/managequestions

CXX = clang++
CXXFLAGS = -Wall

LIBS = -lboost_system-mt -lboost_thread-mt

CLIENT_OBJS = objs/client/main.o objs/client/client.o
SERVER_OBJS = objs/server/main.o objs/server/question.o objs/server/player.o objs/server/team.o objs/server/session.o objs/server/server.o objs/server/bot.o
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

objs/client/client.o: src/client/client.cpp src/client/client.hpp
	$(CXX) $(CXXFLAGS) -c src/client/client.cpp -o objs/client/client.o

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

objs/server/session.o: src/server/session.cpp src/server/session.hpp
	$(CXX) $(CXXFLAGS) -c src/server/session.cpp -o objs/server/session.o

objs/server/bot.o: src/server/bot.cpp src/server/bot.hpp
	$(CXX) $(CXXFLAGS) -c src/server/bot.cpp -o objs/server/bot.o

objs/server/server.o: src/server/server.cpp src/server/server.hpp
	$(CXX) $(CXXFLAGS) -c src/server/server.cpp -o objs/server/server.o

objs/shared/message.o: src/shared/message.cpp src/shared/message.hpp
	$(CXX) $(CXXFLAGS) -c src/shared/message.cpp -o objs/shared/message.o

clean:
	rm -r objs bin
