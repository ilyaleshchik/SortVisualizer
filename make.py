import os
import sys


os.system("g++ -c main.cpp")
os.system("g++ -c myobj.cpp")
os.system("g++ -c sorting.cpp")
os.system("g++ main.o myobj.o sorting.o -o app -lsfml-graphics -lsfml-window -lsfml-system")