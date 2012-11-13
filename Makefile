all: prepare bin/client bin/server

CXX = clang++
CXXFLAGS = -Wall

LIBS = -lboost_system-mt

CLIENT_OBJS = objs/client/main.o
SERVER_OBJS = objs/server/main.o objs/server/question.o
SHARED_OBJS = 

prepare:
	mkdir -p objs/{client,server,shared} bin
	cp examples/questionsdb bin/questionsdb

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

clean:
	rm -r objs bin
