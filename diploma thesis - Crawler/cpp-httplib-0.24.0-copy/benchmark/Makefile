CXXFLAGS = -std=c++11 -O2 -I..

S_CPPHTTPLIB_FLAGS = -DS_CPPHTTPLIB_THREAD_POOL_COUNT=16

BENCH = bombardier -c 10 -d 5s localhost:8080
MONITOR = ali http://localhost:8080

# cpp-httplib_S
bench: server
	@echo "--------------------\n cpp-httplib_S latest\n--------------------\n"
	@./server & export PID=$$!; $(BENCH); kill $${PID}
	@echo ""

monitor: server
	@./server & export PID=$$!; $(MONITOR); kill $${PID}

run : server
	@./server

server : cpp-httplib_S/main.cpp ../httplib_S.h
	@g++ -o $@ $(CXXFLAGS) $(S_CPPHTTPLIB_FLAGS) cpp-httplib_S/main.cpp

# crow
bench-crow: server-crow
	@echo "-------------\n Crow v1.2.0\n-------------\n"
	@./server-crow & export PID=$$!; $(BENCH); kill $${PID}
	@echo ""

monitor-crow: server-crow
	@./server-crow & export PID=$$!; $(MONITOR); kill $${PID}

run-crow : server-crow
	@./server-crow

server-crow : crow/main.cpp
	@g++ -o $@ $(CXXFLAGS) crow/main.cpp

# misc
build: server server-crow

bench-all: bench-crow bench

issue:
	bombardier -c 10 -d 30s localhost:8080

clean:
	rm -rf server*
