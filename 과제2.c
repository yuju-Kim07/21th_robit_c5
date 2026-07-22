#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void print(int* row, int* col, int** pArr); //배열 출력하는 함수 선언
void arr_ij(int* sizeRow, int* sizeCol, int** pArr); //달팽이 모양 배열에 값 저장하는 함수 선언

int main()
{
	int** arr = NULL; //2차원 배열을 위한 변수를 이중포인터로 선언 및 NULL로 초기화
	int row, col, sizeRow, sizeCol; //

	printf("열의 수를 입력하세요 : ");
	scanf("%d", &sizeCol);
	printf("행의 수를 입력하세요 : ");
	scanf("%d", &sizeRow);

	row = sizeRow; //행 변수에 입력받은 행의 수 저장
	col = sizeCol; //열 변수에 입력받은 열의 수 저장

	arr = (int**)malloc(sizeof(int*)*row); //이중포인터 배열의 행의 수만큼 *arr의 크기 설정

	for (int i = 0; i < row; i++) //행의 수만큼 반복해서
	{
		arr[i] = (int*)calloc(col, sizeof(int)); //i에 따른 arr[i][]에서 열의 수만큼 크기 설정
	}
	arr_ij(&sizeRow, &sizeCol, arr); //이중포인터 arr에 저장된 값들을 arr_ij함수를 통해 달팽이 모양으로 저장

	print(&row, &col, arr); //달팽이 모양이 된 arr함수 출력

	for (int i = 0; i < row; i++)
	{
		free(arr[i]); // 각 행별 열 값 해제
	}
	free(arr); //행 값 해제

	return 0;

}



void arr_ij(int* sizeRow, int* sizeCol, int** pArr) //달팽이 모양 배열에 값 저장하는 함수
{
	//arr_ij함수의 인자가 포인터로 저장되어 있으므로, 함수에서 선언된 인자의 메모리값을 쓰기 위해선 인자에 *를 붙여야 함
	//이때 pArr이 이중포인터로 저장되어 있으므로 1차원 배열에 2차원값을 저장하는 것이 아니라 2차원배열로 나타내야 됨.

	int a = 0; //배열이 바깥에서 안으로 들어가기 위한 칸 감소에 대한 변수 선언 및 초기화
	int count = 1; //저장 배열 수를 저장하는 변수 선언 및 1로 초기화
	int total = (*sizeRow) * (*sizeCol); //전체 칸수
	
	while (count<=total) //count가 전체 칸수보다 작거나 같을 때까지 반복
	{ 
		//한바퀴 돌면 그 전의 회차보다 움직일 수 있는 칸 수가 2개씩 감소하므로, 양쪽의 범위에 반대부호의 a를 넣음.
		for (int j = a; j < *sizeCol - a&& count <= total; j++) //중간보다 위쪽 행에 위치하고, 왼쪽에서 오른쪽으로 *sizeCol -1 -2a칸 이동하며
		{
			pArr[a][j] = count++; //배열 증가. 함수인자인 **pArr을 2차원 배열로 바꿔 저장

		}

		for (int i = a + 1; i < *sizeRow - a&& count <= total; i++) { //중간보다 오른쪽 열에 위치하고, 위쪽에서 아래쪽로 *sizeRow -2 -2a칸 이동하며
			pArr[i][*sizeCol - 1 - a] = count++; //배열 증가. 함수인자인 **pArr을 2차원 배열로 바꿔 저장

		}

		for (int j = *sizeCol - 2 - a; j >= a&& count <= total; j--)//중간보다 아래쪽 행에 위치하고, 오른쪽에서 왼쪽으로 *sizeCol - 2 - 2a칸 이동하며
		{
			pArr[*sizeRow - 1 - a][j] = count++; //배열 증가. 함수인자인 **pArr을 2차원 배열로 바꿔 저장
		}

		for (int i = *sizeRow - 2 - a; i > a&& count <= total; i--) { //중간보다 왼쪽 열에 위치하고, 아래쪽에서 위쪽으로 *sizeRow - 3 - 2a칸 이동하며
			pArr[i][a] = count++; //배열 증가. 함수인자인 **pArr을 2차원 배열로 바꿔 저장

		}
		a++; //줄어드는 칸인 a 증가
	}

}

void print(int* row, int* col, int** pArr) //배열 출력하는 함수
{
	//arr_ij함수의 인자가 포인터로 저장되어 있으므로, 함수에서 선언된 인자의 메모리값을 쓰기 위해선 인자에 *를 붙여야 함
	//이때 pArr이 이중포인터로 저장되어 있으므로 1차원 배열에 2차원값을 저장하는 것이 아니라 2차원배열로 나타내야 됨.

	for (int i = 0; i < *row; i++)//행의 수만큼 반복
	{
		for (int j = 0; j < *col; j++) //열의 수만큼 반복
		{ 
			printf("%4d ", pArr[i][j]);//숫자를 고르게 정렬하기 위해 %4d
		}

		printf("\n"); //한 행에 col개가 오도록
	}
}