#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>
#include"infomation.h"

//[시나리오]
//플레이어는 5층짜리 던전에 도착했다.
//각 층에는 각종 몬스터들이 기다리고 있다.
//
//[플레이 방식]
//플레이 방식은 플레이어와 몬스터가
//각각 주사위를 던져 큰 수가 나오는 쪽이
//승리하며 진 쪽은 HP가 감소한다.
//
//[게임 룰]
//- 게임을 시작하면 각 층에 몬스터 랜덤 배치
//- 플레이어 또는 몬스터는 HP가 0이 되면 사망
//- 각 층의 몬스터를 죽이면 다음 층으로 진행
//- 모든 적을 물리치면 엔딩 처리
//- 플레이 도중 사망하면 엔딩 처리
//
//[참고]
//플레이어 정보(이름, HP, 공격력, 방어력)
//몬스터 정보(이름, HP, 공격력, 방어력)
//맵(1차원 배열)
//플레이어와 몬스터 정보는 미리 설정

void InitInfomation(Info *_pInfo); //초기화 
void Update(); 
void PrintMainMenu(Info *_pInfo); //상단 현황판 출력
void ShowPlayerAttackDisplay(Info *_pInfo, E_INFO _eInfo); //플레이어가 공격일때 출력 
void ShowMonsterAttackDisplay(Info *_pInfo, E_INFO _eInfo); //몬스터가 공격일때 출력

void main()
{
	Update();
}
void Update()
{
	int arrFloor[5] = { 0, };	//층 배열
	int arrCheck[6] = { 0, };	// pInfo하고 1:1 매칭으로 몬스터 중복 체크
	int nFloorCnt = 0;			// 층 체크
	int nRandMonster = 0;		// 랜덤으로 뽑은 몬스터 받음
	int nMonsterCnt = MAX_INFO; // 몬스터 총수
	int nCheckMonster = 0;		//몬스터 중복 체크
	int nPlayerDice = 0;		//플레이어 주사위값
	int nMonsterDice = 0;		//몬스터 주사위 값
	int nFlag = 0;				//입력 분기 선택
	Info *pInfo = (Info*)malloc(sizeof(Info) *  MAX_INFO);
	InitInfomation(pInfo);
	
	PrintMainMenu(pInfo);
	printf("\t\t\t       던전에 들어가기\n\n\t\t\t (임의의 숫자를 입력 하세요.)\n\n");
	scanf_s("%d", &nFlag);

NextFloor:
	/*갱신을 위해 새로 그림*/
	system("cls");
	PrintMainMenu(pInfo);

	if (nFloorCnt >= 5)//현재 층을 체크 5층이되면 프로그램 종료
	{
		printf("\t\t\t\t\n던전 클리어!");
		printf("\t\t\t\t\n1. 종료하기\n");
		scanf_s("%d", &nFlag);
		if (nFlag == 1)
		{
			exit(1);
		}
	}

	printf("1.  %d 층 입장 하기\n", nFloorCnt + 1);
	scanf_s("%d", &nFlag);

	if (nFlag == 1)
	{
		nFloorCnt++;
		while (1)
		{		
			nFlag = 0;			
			srand(time(NULL));
			nRandMonster = (rand() % (MAX_INFO)) + 1;

			/*몬스터 리젠 중복 체크*/
			if (arrCheck[nRandMonster] == nCheckMonster)
			{
				arrCheck[nRandMonster] = 1;
			}
			else if (arrCheck[nRandMonster] != nCheckMonster)
			{
				continue;
			}
			printf("\t\t\t\t%d층에 도착 하였다. \n\n", nFloorCnt);
			printf("\t\t\t\t야생의 %s가(이) 나타났다.\n", pInfo[nRandMonster].cName);
			printf("\t\t\t\t도망따윈 없다. \n");
			printf("1.공격하기\n");
			scanf_s("%d", &nFlag);

			system("cls");

			PrintMainMenu(pInfo);
			while (nFlag == 1)
			{			
				printf("\t\t\t       몬스터의 스테이터스\t\t\t\n\n");
				printf("\t   이름 : %s  HP : %d  공격력 : %d  방어력 : %d \n\n", pInfo[nRandMonster].cName, pInfo[nRandMonster].nHp, pInfo[nRandMonster].nDamage, pInfo[nRandMonster].nDef);

				nPlayerDice = ((unsigned)rand() % DICE) + 1;
				srand(time(NULL));
				nMonsterDice = ((unsigned)rand() % DICE) + 1;
				srand(time(NULL));

				printf("\t\t\t주사위의 값\n");
				printf("\t\t\t%s : %d  vs %s : %d\n", pInfo[PLAYER].cName, nPlayerDice, pInfo[nRandMonster].cName, nMonsterDice);

				int tempD = 0;
				if (nPlayerDice > nMonsterDice) // 플레이어 주사위 수가 몬스터보다 크면
				{
					printf("\t\t\t%s의 값이 더 크게 나왔다!\n", pInfo[PLAYER].cName);
					switch (nRandMonster)
					{
					case ORC:
					{						
						ShowPlayerAttackDisplay(pInfo, ORC);
						if (pInfo[ORC].nHp <= 0)
						{
							printf("\t\t\t%s를(을) 물리쳤다! 다음 층으로 가자\n", pInfo[ORC].cName);
							printf("\t\t\t\n1.다음 층으로 가기\n");
							scanf_s("%d", &nFlag);
							system("cls");
							if (nFlag == 1)
							{
								goto NextFloor;
							}
						}
						break;
					}
					case TROLL:
					{
						ShowPlayerAttackDisplay(pInfo, TROLL);
						if (pInfo[TROLL].nHp <= 0)
						{
							printf("\t\t\t%s를(을) 물리쳤다! 다음 층으로 가자\n", pInfo[TROLL].cName);
							printf("\t\t\t\n1.다음 층으로 가기\n");
							scanf_s("%d", &nFlag);
							system("cls");
							if (nFlag == 1)
							{
								goto NextFloor;
							}
						}
						break;
					}
					case OGRE:
					{
						ShowPlayerAttackDisplay(pInfo, OGRE);
						if (pInfo[OGRE].nHp <= 0)
						{
							printf("\t\t\t%s를(을) 물리쳤다! 다음 층으로 가자\n", pInfo[OGRE].cName);
							printf("\t\t\t\n1.다음 층으로 가기\n");
							scanf_s("%d", &nFlag);
							system("cls");
							if (nFlag == 1)
							{
								goto NextFloor;
							}
						}
						break;
					}
					case IMP:
					{
						ShowPlayerAttackDisplay(pInfo, IMP);
						if (pInfo[IMP].nHp <= 0)
						{
							printf("\t\t\t%s를(을) 물리쳤다! 다음 층으로 가자\n", pInfo[IMP].cName);
							printf("\t\t\t\n1.다음 층으로 가기\n");
							scanf_s("%d", &nFlag);
							system("cls");
							if (nFlag == 1)
							{
								goto NextFloor;
							}
						}		
						break;
					}
					case DRAGON:
					{
						ShowPlayerAttackDisplay(pInfo, DRAGON);
						if (pInfo[DRAGON].nHp <= 0)
						{
							printf("\t\t\t%s를(을) 물리쳤다! 다음 층으로 가자\n", pInfo[DRAGON].cName);
							printf("\t\t\t\n1.다음 층으로 가기\n");
							scanf_s("%d", &nFlag);
							system("cls");
							if (nFlag == 1)
							{
								goto NextFloor;
							}
						}
						break;										
					}
					}
				}
				else if (nPlayerDice < nMonsterDice)// 플레이어 주사위 수가 몬스터보다 작으면
				{
					printf("\t\t\t%s의 값이 더 크게 나왔다!\n", pInfo[nRandMonster].cName);
					switch (nRandMonster)
					{
					case ORC:
					{
						ShowMonsterAttackDisplay(pInfo, ORC);
						break;
					}						
					case TROLL:
					{
						ShowMonsterAttackDisplay(pInfo, TROLL);
						break;
					}
					case OGRE:
					{
						ShowMonsterAttackDisplay(pInfo, OGRE);
						break;
					}
					case IMP:
					{
						ShowMonsterAttackDisplay(pInfo, IMP);
						break;
					}
					case DRAGON:
					{
						ShowMonsterAttackDisplay(pInfo, DRAGON);
						break;
					}
					}
				}
				else if (nPlayerDice == nMonsterDice)
				{
					printf("\t\t\t값이 똑같이 나왔다! 다시 공격 해보자\n");					
				}

				printf("\n1.공격하기\n");
				scanf_s("%d", &nFlag);
				system("cls");
				PrintMainMenu(pInfo);
				
				if (pInfo[PLAYER].nHp <= 0)
				{
					system("cls");

					printf("\t\t\t%s의 HP가 0 되어서 사망했다.\n", pInfo[PLAYER].cName);
					printf("\t\t\tGAME OVER\n");
					printf("\t\t\t\n1. 종료하기\n");
					scanf_s("%d", &nFlag);
					if (nFlag == 1)
					{
						exit(1);
					}
				}				
			}			
		}
	}	
	else
	{
		printf("제대로 입력 하세요. \n");
	}
}
void InitInfomation(Info *_pInfo)
{
	Info sInfo[MAX_INFO] = {
		{ 1500,1301,53,"한조대기중" },
		{ 340,65,30,"오크" },
		{ 600,80,40,"트롤" },
		{ 500,97,70,"오거" },
		{ 299,60,30,"임프" },
		{ 1200,190,66,"투명 드래곤" }
	};
	memcpy(_pInfo, &sInfo, sizeof(Info) * MAX_INFO);
}
void ShowPlayerAttackDisplay(Info *_pInfo, E_INFO _eMonster)
{
	int tempD = 0;
	tempD = _pInfo[PLAYER].nDamage - _pInfo[_eMonster].nDef;
	_pInfo[_eMonster].nHp -= tempD;
	printf("\t\t\t%s는(은) %s에게 %d만큼의 데미지를 주었다.\n\n", _pInfo[PLAYER].cName, _pInfo[_eMonster].cName, tempD);
	if (_pInfo[_eMonster].nHp <= 0 )
	{
		printf("\t\t\t%s의 남은 체력 : %d\n\n", _pInfo[_eMonster].cName, (_pInfo[_eMonster].nHp * -1)*0 );
	}
	else
	{
		printf("\t\t\t%s의 남은 체력 : %d\n\n", _pInfo[_eMonster].cName, _pInfo[_eMonster].nHp);
	}	
}
void ShowMonsterAttackDisplay(Info *_pInfo, E_INFO _eMonster)
{
	int tempD = 0;
	tempD = _pInfo[_eMonster].nDamage - _pInfo[PLAYER].nDef;
	_pInfo[PLAYER].nHp -= tempD;
	printf("\t\t\t%s는(은) %s에게 %d만큼의 데미지를 주었다.\n\n", _pInfo[_eMonster].cName, _pInfo[PLAYER].cName, tempD);
}
void PrintMainMenu(Info *_pInfo)
{
	char arrMoniter[YC][XC];
	int i, j;
	for (i = 0; i < YC; i++)
	{
		for (j = 0; j< XC; j++)
		{
			arrMoniter[i][j] = '\0';
		}
	}

	for (i = 0; i < YC; i++)
	{
		for (j = 0; j < XC; j++)
		{
			if (i == 0 || i == YC - 1)
			{
				arrMoniter[i][j] = '=';
			}
			else if (j == 0 || j == XC - 1)
			{
				arrMoniter[i][j] = '=';
			}
				
			if (i == 1 && ((j > 14 && j < 22) || (j == 23) || (j > 34 && j <42) || ( j == 43) || (j > 54 && j < 63 ) ))				
			{
				arrMoniter[i][j] = '0';
			}
			else if (i == 2 && (j == 15 || j == 23 || j == 38 || j == 43 || j == 55  ))
			{
				arrMoniter[i][j] = '0';
			}
			else if (i == 3 && (j == 15 || j == 19 || j == 20 || j == 21 || j == 22 || j == 23 ||
				 j == 37 || j == 39 || j == 41 || j == 42 || j == 43 || j == 55 ))
			{
				arrMoniter[i][j] = '0';
			}
			else if (i == 4 && (j == 15 || j == 23 || j == 36 || j == 40 || j == 43 || (j > 54 && j < 63)))
			{
				arrMoniter[i][j] = '0';
			}
			else if (i == 5 && ((j > 14 && j < 22) || j == 23 || j == 35 || j == 41 || j == 43 || j == 62 ))
			{
				arrMoniter[i][j] = '0';
			}
			else if (i == 6 && j == 23 || i == 6 && j == 43 || i == 6 && j == 62)
			{
				arrMoniter[i][j] = '0';
			}
			else if ( i == 7 && j == 15 || i == 7 && j == 35 || i == 7 && j == 62)
			{
				arrMoniter[i][j] = '0';
			}
			else if (i == 8 && (j > 14 && j < 24 || j == 17 || j == 18 || j == 19 || j == 20 || j == 21 || j == 22 || j == 23 || (j > 34 && j < 44 ) || (j > 54 && j < 63)))
			{
				arrMoniter[i][j] = '0';
			}
		}		
	}
	for (i = 0; i < YC; i++)
	{
		for (j = 0; j< XC; j++)
		{
			printf("%c", arrMoniter[i][j]);
		}
		printf("\n");
	}

	printf("\t\t\t    5층 던전에 어서 오시오\t\t\t\n\n");
	printf("\t\t\t       나의 스테이터스\t\t\t\n\n");
	printf("\t   이름 : %s  HP : %d  공격력 : %d  방어력 : %d \n\n", _pInfo[PLAYER].cName, _pInfo[PLAYER].nHp, _pInfo[PLAYER].nDamage, _pInfo[PLAYER].nDef);
}




