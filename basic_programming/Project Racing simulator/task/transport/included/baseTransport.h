#pragma once
#include <string>

enum class transport{
	eagle, //���
	carpet, //����
	broom, //�����
	camel, //�������
	camelFast, //������� ��������
	centaur, // �������
	boots // ������� ���������
};

class baseTransport {
	std::wstring n_name;
	bool n_isAir;
	transport type;
public:
	baseTransport(std::wstring n, bool air, transport tp);
	virtual ~baseTransport() {};
	std::wstring name() { return n_name; }
	transport transportType() { return type; }
	bool isAir() { return n_isAir; }

	virtual double rasing(int )=0;
};

