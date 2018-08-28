#!/bin/bash

echo "Informe a imagem: "
read f;

./edges $f
./suaviza $f
./canny $f
./histograma $f

exit 0
