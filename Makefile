default:
	g++ -g main.cpp -o main -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all:
	cp LearnGaelic.scot-scraper/*.txt .
	./getAudio.sh
	