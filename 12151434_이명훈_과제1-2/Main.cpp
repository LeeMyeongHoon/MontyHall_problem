/******************************************************************************************************

[	파일명	]	Main.cpp
[	작성자	]	12151434_컴퓨터공학과_이명훈
[	목  적	]	몬티홀 문제상황을 컴퓨터 시뮬레이션으로 구현하여 확률을 계산한다.
[	특이점	]

*******************************************************************************************************/

#include <iostream>
#include <cstdlib>
#include <iomanip>


#define GOAT	0			// 염소 = 0
#define CAR		1			// 자동차 = 1

#define DOOR_TOTAL 3		// 문이 총 3개 있다.
#define ITEM_TOTAL 2		// 자동차, 염소 두 종류


using namespace std;

int main(void)
{
	unsigned int trialTotal;					// 입력되는 전체 수행 횟수
	bool switchOption;							// 입력되는 선택 옵션

	bool randItem;								// 상품배치를 랜덤하게 하는데 필요한 변수 
	short locateItemCount[ITEM_TOTAL] = { 0 };	// 각 상품별 배치될 (자동차,염소)의 갯수 목록
	bool itemBehindDoor[DOOR_TOTAL] = { 0 };	// 각 문에 배치된 상품 목록

	short firstChoice;							// 참가자의 첫 선택
	short openGoatDoor;							// 참가자의 첫 선택 후, 사회자가 열어주어 염소가 있는 문  
	short randDoor;								// 사회자가 문을 열기 위해 필요한 변수
	short finalChoice;							// 참가자의 최종 선택
	bool IsSuccess;								// 수행할 때마다 당첨 여부가 저장되는 변수(true=당첨,false=꽝)
	unsigned int successCount = 0;				// 당첨 횟수를 누적

	// 출력에 사용되는 문자열
	const char* itemName[ITEM_TOTAL] = { "염소" , "자동차" };
	const char* optionString[2] = { "선택 유지","선택 변경" };
	const char* resultString[2] = { "꽝입니다!","당첨입니다!" };

	cout << "수행 횟수를 입력하세요 : ";
	cin >> trialTotal;
	cout << "\n\n-------------------------------------------------------------------------------------\n\n\n";
	cout << "[0] 선택 유지.\t[1] 선택 변경." << endl;
	cout << "\n\n-------------------------------------------------------------------------------------\n\n";

	cout << "옵션을 선택하세요 : ";
	cin >> switchOption;
	cout << '\n';
	for (size_t trialCount = 1; trialCount <= trialTotal; trialCount++)
	{
		// 자동차 1대와 염소 2마리를 랜덤으로 배치합니다.
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


		// 참가자가 문을 선택합니다.
		firstChoice = rand() % DOOR_TOTAL;

		// 사회자가 염소가 있는 다른 문을 열어줍니다.
		while (1)
		{
			randDoor = rand() % DOOR_TOTAL;
			if ((randDoor != firstChoice) && (itemBehindDoor[randDoor] == GOAT))
			{
				openGoatDoor = randDoor;
				break;
			}
		}

		// Option[1] : 선택을 변경합니다.
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

		// Option[0] : 선택을 유지합니다.
		else
		{
			finalChoice = firstChoice;
		}

		// 최종 선택한 문에 자동차가 있는지 확인한다
		if (itemBehindDoor[finalChoice] == CAR)
		{
			IsSuccess = true;
			successCount++;
		}
		else
		{
			IsSuccess = false;
		}

		// 위에 나온 과정을 출력합니다.
		for (int i = 0; i < DOOR_TOTAL; i++)
			cout << '[' << i << ']' << setw(6) << itemName[itemBehindDoor[i]] << ' ';

		cout << "---참가자 선택[" << firstChoice << "]";
		cout << "---사회자가 열어준 문" << '[' << openGoatDoor << "]---";
		cout << optionString[switchOption] << "---최종선택" << '[' << finalChoice << ']' << "---" << resultString[IsSuccess] << "\n\n";

	}

	// 결과로 당첨 확률을 출력합니다.
	cout << "\n\n-------------------------------------------------------------------------------------\n\n";
	cout << "당첨 확률 : " << successCount << '/' << trialTotal << " = " << static_cast<double>(successCount) / trialTotal * 100 << '%' << endl;

	return 0;
}