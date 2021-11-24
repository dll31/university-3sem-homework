#include "Sunday.h"
#include <cstring>
using namespace std;

outputData Sunday(string& needle, string haystack) {

	outputData out;

	int hayLen = haystack.length();
	int nLen = needle.length();

	int i = 0; // ������ ������� ������ ����� ����
	int j = 0; // ������ ������� �������� ������

	// ���������� ���������, ����� ���������� ������� ����� ���� ������, ��� ������ ����
	while (i <= hayLen - nLen) {
		// ��������� ������ ���� � ����������, ����������� � ��������� � ������ ����� ���� �����������
		while (j < nLen && haystack[i + j] == needle[j]) {
			j++;
		}

		// ���� j ����� ����� �������� ������, ���������� ������� � ��� �����, � �� ������ �������� ������� ������ ������� �������� ������ � ��� �����
		if (j == nLen) {
			out.id.push_back(i);
			return out;
		}

		// ������������ ���������� ��������, ������� ����� ����������, ���� ���������� ���, � ���������� ������ �������� ������ i
		if (i < hayLen - nLen) {
			// ������ ��������� ���������� � �������� ������, � ���������� ��������, ������� ���������� ����������, ����� ���������� ��������, ���������� �� ��������� ������� ������� ��������� � �������� ������
			// ���� �� �� ����������, ���������� ����������� �������� ����� ����� �������� ������ + 1, ��� � ������ ���� nLen - (- 1)
			i += (nLen - needle.find_last_of(haystack[i + nLen]));
		}
		else {
			out.errors.push_back(-1);
			return out;
		}
		// ������������� ������ ������� �� 0 ����� ������� ���������
		j = 0;
	}

	out.errors.push_back(-1);
	return out;
}