Flappy Bird (C++ / graphics.h)
This is a simple Flappy Bird–style game made using C++ and the graphics.h (WinBGIm) library.
The bird flies upward when you press SPACE, and you must avoid hitting the pipes or the ground.

Features

Smooth bird movement (jump + gravity)

Random pipe generation

Score system

Game Over screen

Intro menu (Start / Leaderboard / Quit)

Saves name & score in data.txt

Simple 2D graphics using graphics.h

Controls

G → Start Game

L → Open Leaderboard

Q → Quit

SPACE → Jump

How to Run

Install WinBGIm graphics library.

Add graphics.h, winbgim.h, libbgi.a to your project.

Add linker flags:
-lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32

Compile and run main.cpp.

Files

main.cpp — Game code

data.txt — Stores names and scores

README.md — Project info

Description

This project is great for beginners learning basic game development in C++.
It covers movement, collision, graphics, keyboard input, score handling, and file reading/writing.

