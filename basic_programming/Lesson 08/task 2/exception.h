#pragma once
#include <iostream>

class excFigure {
public:
	virtual const char* what()=0 { }
};

class summCornTriangle: public excFigure {
public:
	const char* what() override { return "сумма углов не равна 180"; }
};

class summCornQuad : public excFigure {
public:
	const char* what() override { return "сумма углов не равна 360"; }
};

class reghtTriangle : public excFigure {
public:
	const char* what() override { return "угол С не равен 90"; }
};

class sideAC : public excFigure {
public:
	const char* what() override { return "стороны a и c не равны"; }
};

class cornAC : public excFigure {
public:
	const char* what() override { return "углы A и C не равны"; }
};

class sideAC_and_BD : public excFigure {
public:
	const char* what() override { return "стороны a, c и b, d попарно не равны "; }
};

class sideEqual : public excFigure {
public:
	const char* what() override { return "не все стороны равны"; }
};

class cornEqual90 : public excFigure {
public:
	const char* what() override { return "не все углы равны 90"; }
};

class cornEqual60 : public excFigure {
public:
	const char* what() override { return "не все углы равны 60"; }
};

class cornAC_and_BD : public excFigure {
public:
	const char* what() override { return "углы A, C и B, D попарно не равны "; }
};


