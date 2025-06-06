FROM ubuntu:16.04
COPY . /usr/src/dockerTestTask2/
WORKDIR /usr/src/dockerTestTask2
RUN apt update
RUN apt install -y g++
RUN g++ -o "task2" "task2.cpp"
CMD ["./task2"]