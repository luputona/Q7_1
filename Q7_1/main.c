#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>
#include"infomation.h"

//[�ó�����]
//�÷��̾�� 5��¥�� ������ �����ߴ�.
//�� ������ ���� ���͵��� ��ٸ��� �ִ�.
//
//[�÷��� ���]
//�÷��� ����� �÷��̾�� ���Ͱ�
//���� �ֻ����� ���� ū ���� ������ ����
//�¸��ϸ� �� ���� HP�� �����Ѵ�.
//
//[���� ��]
//- ������ �����ϸ� �� ���� ���� ���� ��ġ
//- �÷��̾� �Ǵ� ���ʹ� HP�� 0�� �Ǹ� ���
//- �� ���� ���͸� ���̸� ���� ������ ����
//- ��� ���� ����ġ�� ���� ó��
//- �÷��� ���� ����ϸ� ���� ó��
//
//[����]
//�÷��̾� ����(�̸�, HP, ���ݷ�, ����)
//���� ����(�̸�, HP, ���ݷ�, ����)
//��(1���� �迭)
//�÷��̾�� ���� ������ �̸� ����

void InitInfomation(Info *_pInfo); //�ʱ�ȭ 
void Update(); 
void PrintMainMenu(Info *_pInfo); //��� ��Ȳ�� ���
void ShowPlayerAttackDisplay(Info *_pInfo, E_INFO _eInfo); //�÷��̾ �����϶� ��� 
void ShowMonsterAttackDisplay(Info *_pInfo, E_INFO _eInfo); //���Ͱ� �����϶� ���

void main()
{
	Update();
}
void Update()
{
	int arrFloor[5] = { 0, };	//�� �迭
	int arrCheck[6] = { 0, };	// pInfo�ϰ� 1:1 ��Ī���� ���� �ߺ� üũ
	int nFloorCnt = 0;			// �� üũ
	int nRandMonster = 0;		// �������� ���� ���� ����
	int nMonsterCnt = MAX_INFO; // ���� �Ѽ�
	int nCheckMonster = 0;		//���� �ߺ� üũ
	int nPlayerDice = 0;		//�÷��̾� �ֻ�����
	int nMonsterDice = 0;		//���� �ֻ��� ��
	int nFlag = 0;				//�Է� �б� ����
	Info *pInfo = (Info*)malloc(sizeof(Info) *  MAX_INFO);
	InitInfomation(pInfo);
	
	PrintMainMenu(pInfo);
	printf("\t\t\t       ������ ����\n\n\t\t\t (������ ���ڸ� �Է� �ϼ���.)\n\n");
	scanf_s("%d", &nFlag);

NextFloor:
	/*������ ���� ���� �׸�*/
	system("cls");
	PrintMainMenu(pInfo);

	if (nFloorCnt >= 5)//���� ���� üũ 5���̵Ǹ� ���α׷� ����
	{
		printf("\t\t\t\t\n���� Ŭ����!");
		printf("\t\t\t\t\n1. �����ϱ�\n");
		scanf_s("%d", &nFlag);
		if (nFlag == 1)
		{
			exit(1);
		}
	}

	printf("1.  %d �� ���� �ϱ�\n", nFloorCnt + 1);
	scanf_s("%d", &nFlag);

	if (nFlag == 1)
	{
		nFloorCnt++;
		while (1)
		{		
			nFlag = 0;			
			srand(time(NULL));
			nRandMonster = (rand() % (MAX_INFO)) + 1;

			/*���� ���� �ߺ� üũ*/
			if (arrCheck[nRandMonster] == nCheckMonster)
			{
				arrCheck[nRandMonster] = 1;
			}
			else if (arrCheck[nRandMonster] != nCheckMonster)
			{
				continue;
			}
			printf("\t\t\t\t%d���� ���� �Ͽ���. \n\n", nFloorCnt);
			printf("\t\t\t\t�߻��� %s��(��) ��Ÿ����.\n", pInfo[nRandMonster].cName);
			printf("\t\t\t\t�������� ����. \n");
			printf("1.�����ϱ�\n");
			scanf_s("%d", &nFlag);

			system("cls");

			PrintMainMenu(pInfo);
			while (nFlag == 1)
			{			
				printf("\t\t\t       ������ �������ͽ�\t\t\t\n\n");
				printf("\t   �̸� : %s  HP : %d  ���ݷ� : %d  ���� : %d \n\n", pInfo[nRandMonster].cName, pInfo[nRandMonster].nHp, pInfo[nRandMonster].nDamage, pInfo[nRandMonster].nDef);

				nPlayerDice = ((unsigned)rand() % DICE) + 1;
				srand(time(NULL));
				nMonsterDice = ((unsigned)rand() % DICE) + 1;
				srand(time(NULL));

				printf("\t\t\t�ֻ����� ��\n");
				printf("\t\t\t%s : %d  vs %s : %d\n", pInfo[PLAYER].cName, nPlayerDice, pInfo[nRandMonster].cName, nMonsterDice);

				int tempD = 0;
				if (nPlayerDice > nMonsterDice) // �÷��̾� �ֻ��� ���� ���ͺ��� ũ��
				{
					printf("\t\t\t%s�� ���� �� ũ�� ���Դ�!\n", pInfo[PLAYER].cName);
					switch (nRandMonster)
					{
					case ORC:
					{						
						ShowPlayerAttackDisplay(pInfo, ORC);
						if (pInfo[ORC].nHp <= 0)
						{
							printf("\t\t\t%s��(��) �����ƴ�! ���� ������ ����\n", pInfo[ORC].cName);
							printf("\t\t\t\n1.���� ������ ����\n");
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
							printf("\t\t\t%s��(��) �����ƴ�! ���� ������ ����\n", pInfo[TROLL].cName);
							printf("\t\t\t\n1.���� ������ ����\n");
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
							printf("\t\t\t%s��(��) �����ƴ�! ���� ������ ����\n", pInfo[OGRE].cName);
							printf("\t\t\t\n1.���� ������ ����\n");
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
							printf("\t\t\t%s��(��) �����ƴ�! ���� ������ ����\n", pInfo[IMP].cName);
							printf("\t\t\t\n1.���� ������ ����\n");
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
							printf("\t\t\t%s��(��) �����ƴ�! ���� ������ ����\n", pInfo[DRAGON].cName);
							printf("\t\t\t\n1.���� ������ ����\n");
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
				else if (nPlayerDice < nMonsterDice)// �÷��̾� �ֻ��� ���� ���ͺ��� ������
				{
					printf("\t\t\t%s�� ���� �� ũ�� ���Դ�!\n", pInfo[nRandMonster].cName);
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
					printf("\t\t\t���� �Ȱ��� ���Դ�! �ٽ� ���� �غ���\n");					
				}

				printf("\n1.�����ϱ�\n");
				scanf_s("%d", &nFlag);
				system("cls");
				PrintMainMenu(pInfo);
				
				if (pInfo[PLAYER].nHp <= 0)
				{
					system("cls");

					printf("\t\t\t%s�� HP�� 0 �Ǿ ����ߴ�.\n", pInfo[PLAYER].cName);
					printf("\t\t\tGAME OVER\n");
					printf("\t\t\t\n1. �����ϱ�\n");
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
		printf("����� �Է� �ϼ���. \n");
	}
}
void InitInfomation(Info *_pInfo)
{
	Info sInfo[MAX_INFO] = {
		{ 1500,1301,53,"���������" },
		{ 340,65,30,"��ũ" },
		{ 600,80,40,"Ʈ��" },
		{ 500,97,70,"����" },
		{ 299,60,30,"����" },
		{ 1200,190,66,"���� �巡��" }
	};
	memcpy(_pInfo, &sInfo, sizeof(Info) * MAX_INFO);
}
void ShowPlayerAttackDisplay(Info *_pInfo, E_INFO _eMonster)
{
	int tempD = 0;
	tempD = _pInfo[PLAYER].nDamage - _pInfo[_eMonster].nDef;
	_pInfo[_eMonster].nHp -= tempD;
	printf("\t\t\t%s��(��) %s���� %d��ŭ�� �������� �־���.\n\n", _pInfo[PLAYER].cName, _pInfo[_eMonster].cName, tempD);
	if (_pInfo[_eMonster].nHp <= 0 )
	{
		printf("\t\t\t%s�� ���� ü�� : %d\n\n", _pInfo[_eMonster].cName, (_pInfo[_eMonster].nHp * -1)*0 );
	}
	else
	{
		printf("\t\t\t%s�� ���� ü�� : %d\n\n", _pInfo[_eMonster].cName, _pInfo[_eMonster].nHp);
	}	
}
void ShowMonsterAttackDisplay(Info *_pInfo, E_INFO _eMonster)
{
	int tempD = 0;
	tempD = _pInfo[_eMonster].nDamage - _pInfo[PLAYER].nDef;
	_pInfo[PLAYER].nHp -= tempD;
	printf("\t\t\t%s��(��) %s���� %d��ŭ�� �������� �־���.\n\n", _pInfo[_eMonster].cName, _pInfo[PLAYER].cName, tempD);
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

	printf("\t\t\t    5�� ������ � ���ÿ�\t\t\t\n\n");
	printf("\t\t\t       ���� �������ͽ�\t\t\t\n\n");
	printf("\t   �̸� : %s  HP : %d  ���ݷ� : %d  ���� : %d \n\n", _pInfo[PLAYER].cName, _pInfo[PLAYER].nHp, _pInfo[PLAYER].nDamage, _pInfo[PLAYER].nDef);
}




