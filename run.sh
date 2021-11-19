#!/bin/bash
g++ zoom.cpp -std=c++17 -lsfml-window -lsfml-system -lsfml-graphics -pthread -o zoom
./zoom