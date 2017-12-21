/******************************************************************************************************

[	���ϸ�	]	Main.cpp
[	�ۼ���	]	12151434_��ǻ�Ͱ��а�_�̸���
[	��  ��	]	��ƼȦ ������Ȳ�� ��ǻ�� �ùķ��̼����� �����Ͽ� Ȯ���� ����Ѵ�.
[	Ư����	]

*******************************************************************************************************/

#include <iostream>
#include <cstdlib>
#include <iomanip>


#define GOAT	0			// ���� = 0
#define CAR		1			// �ڵ��� = 1

#define DOOR_TOTAL 3		// ���� �� 3�� �ִ�.
#define ITEM_TOTAL 2		// �ڵ���, ���� �� ����


using namespace std;

int main(void)
{
	unsigned int trialTotal;					// �ԷµǴ� ��ü ���� Ƚ��
	bool switchOption;							// �ԷµǴ� ���� �ɼ�

	bool randItem;								// ��ǰ��ġ�� �����ϰ� �ϴµ� �ʿ��� ���� 
	short locateItemCount[ITEM_TOTAL] = { 0 };	// �� ��ǰ�� ��ġ�� (�ڵ���,����)�� ���� ���
	bool itemBehindDoor[DOOR_TOTAL] = { 0 };	// �� ���� ��ġ�� ��ǰ ���

	short firstChoice;							// �������� ù ����
	short openGoatDoor;							// �������� ù ���� ��, ��ȸ�ڰ� �����־� ���Ұ� �ִ� ��  
	short randDoor;								// ��ȸ�ڰ� ���� ���� ���� �ʿ��� ����
	short finalChoice;							// �������� ���� ����
	bool IsSuccess;								// ������ ������ ��÷ ���ΰ� ����Ǵ� ����(true=��÷,false=��)
	unsigned int successCount = 0;				// ��÷ Ƚ���� ����

	// ��¿� ���Ǵ� ���ڿ�
	const char* itemName[ITEM_TOTAL] = { "����" , "�ڵ���" };
	const char* optionString[2] = { "���� ����","���� ����" };
	const char* resultString[2] = { "���Դϴ�!","��÷�Դϴ�!" };

	cout << "���� Ƚ���� �Է��ϼ��� : ";
	cin >> trialTotal;
	cout << "\n\n-------------------------------------------------------------------------------------\n\n\n";
	cout << "[0] ���� ����.\t[1] ���� ����." << endl;
	cout << "\n\n-------------------------------------------------------------------------------------\n\n";

	cout << "�ɼ��� �����ϼ��� : ";
	cin >> switchOption;
	cout << '\n';
	for (size_t trialCount = 1; trialCount <= trialTotal; trialCount++)
	{
		// �ڵ��� 1��� ���� 2������ �������� ��ġ�մϴ�.
		locateItemCount[GOAT] = 2;
		locateItemCount[CAR] = 1;

		for (size_t doorIndex = 0; doorIndex < DOOR_TOTAL; doorIndex++)
		{
			for (;;)
			{
				randItem = rand() % ITEM_TOTAL;				// CAR(1) or GOAT(0)
				if (locateItemCount[randItem] > 0)
				{
					itemBehindDoor[doorIndex] = randItem;
					locateItemCount[randItem]--;
					break;
				}
			}
		}


		// �����ڰ� ���� �����մϴ�.
		firstChoice = rand() % DOOR_TOTAL;

		// ��ȸ�ڰ� ���Ұ� �ִ� �ٸ� ���� �����ݴϴ�.
		while (1)
		{
			randDoor = rand() % DOOR_TOTAL;
			if ((randDoor != firstChoice) && (itemBehindDoor[randDoor] == GOAT))
			{
				openGoatDoor = randDoor;
				break;
			}
		}

		// Option[1] : ������ �����մϴ�.
		if (switchOption)
		{
			for (size_t doorIndex = 0; doorIndex < DOOR_TOTAL; doorIndex++)
			{
				if ((doorIndex != firstChoice) && (doorIndex != openGoatDoor))
				{
					finalChoice = doorIndex;
					break;
				}
			}
		}

		// Option[0] : ������ �����մϴ�.
		else
		{
			finalChoice = firstChoice;
		}

		// ���� ������ ���� �ڵ����� �ִ��� Ȯ���Ѵ�
		if (itemBehindDoor[finalChoice] == CAR)
		{
			IsSuccess = true;
			successCount++;
		}
		else
		{
			IsSuccess = false;
		}

		// ���� ���� ������ ����մϴ�.
		for (int i = 0; i < DOOR_TOTAL; i++)
			cout << '[' << i << ']' << setw(6) << itemName[itemBehindDoor[i]] << ' ';

		cout << "---������ ����[" << firstChoice << "]";
		cout << "---��ȸ�ڰ� ������ ��" << '[' << openGoatDoor << "]---";
		cout << optionString[switchOption] << "---��������" << '[' << finalChoice << ']' << "---" << resultString[IsSuccess] << "\n\n";

	}

	// ����� ��÷ Ȯ���� ����մϴ�.
	cout << "\n\n-------------------------------------------------------------------------------------\n\n";
	cout << "��÷ Ȯ�� : " << successCount << '/' << trialTotal << " = " << static_cast<double>(successCount) / trialTotal * 100 << '%' << endl;

	return 0;
}