#!/bin/bash

g++ suaviza.cpp -o suaviza `pkg-config --cflags --libs opencv`
g++ edges.cpp -o edges `pkg-config --cflags --libs opencv`
g++ canny.cpp -o canny `pkg-config --cflags --libs opencv`
g++ histograma.cpp -o histograma `pkg-config --cflags --libs opencv`

echo "Informe a imagem: "
read f;

./edges $f
./suaviza $f
./canny $f
./histograma $f

exit 0
