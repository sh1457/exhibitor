#!/bin/bash

git rm ../_posts/*

g++ Exhibitor.cpp

./a.out

mkdir ../_posts

python script.py

git add ../*

git commit -m "Projects Updated"

git push origin HEAD:gh-pages
