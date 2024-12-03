#pragma once
#include <iostream>

class excFigure {
public:
	virtual const char* what()=0 { }
};

class summCornTriangle: public excFigure {
public:
	const char* what() override { return "����� ����� �� ����� 180"; }
};

class summCornQuad : public excFigure {
public:
	const char* what() override { return "����� ����� �� ����� 360"; }
};

class reghtTriangle : public excFigure {
public:
	const char* what() override { return "���� � �� ����� 90"; }
};

class sideAC : public excFigure {
public:
	const char* what() override { return "������� a � c �� �����"; }
};

class cornAC : public excFigure {
public:
	const char* what() override { return "���� A � C �� �����"; }
};

class sideAC_and_BD : public excFigure {
public:
	const char* what() override { return "������� a, c � b, d ������� �� ����� "; }
};

class sideEqual : public excFigure {
public:
	const char* what() override { return "�� ��� ������� �����"; }
};

class cornEqual90 : public excFigure {
public:
	const char* what() override { return "�� ��� ���� ����� 90"; }
};

class cornEqual60 : public excFigure {
public:
	const char* what() override { return "�� ��� ���� ����� 60"; }
};

class cornAC_and_BD : public excFigure {
public:
	const char* what() override { return "���� A, C � B, D ������� �� ����� "; }
};


