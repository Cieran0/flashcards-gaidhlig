all:
	cp LearnGaelic.scot-scraper/*.txt .
	g++ -g main.cpp -o main -lraylib -lGL -lm -lpthread -ldl -lrt -lX11