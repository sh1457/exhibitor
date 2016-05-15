#!/bin/bash

git rm ../_posts/*

g++ Exhibitor.cpp

./a.out

python script.py

git add ../*

git commit -m "Projects Updated"

git push origin HEAD:gh-pages
