#include <iostream>
#include "Container/Queue.h"
#include "Location2D.h"
#include <Windows.h>

// 작은 맵.
//const int mazeSize = 6;
//char map[mazeSize][mazeSize] =
//{
//	{'1','1','1','1','1','1'},
//	{'e','0','1','0','0','1'},
//	{'1','0','0','0','1','1'},
//	{'1','0','1','0','1','1'},
//	{'1','0','1','0','0','x'},
//	{'1','1','1','1','1','1'}
//};

// 큰 맵.
const int mazeSize = 20;
char map[mazeSize][mazeSize] =
{
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '1', '0', '1', '0', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1'},
	{'1', '0', '0', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
	{'1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1'},
	{'e', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
	{'1', '0', '1', '0', '1', '1', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '0', '1', '1', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', 'x'},
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
};

// 방문하려는 위치가 유효한지 확인
bool IsValidLocation(const Location2D& location)
{
	const int row = location.row;
	const int col = location.col;

	if (row < 0 || row >= mazeSize
		|| col < 0 || col >= mazeSize)
	{
		return false;
	}

	return map[row][col] == '0'
		|| map[row][col] == 'x';
}

void ClearScreen()
{
	system("cls");
}

void SetConsoleColor(WORD color)
{
	SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE),
		color
	);
}

void PrintMap(const Location2D& playerPosition,
	DWORD delay)
{
	Sleep(delay);

	//ClearScreen();
	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);

	for (int row = 0; row < mazeSize; row++)
	{
		for (int col = 0; col < mazeSize; col++)
		{
			if (row == playerPosition.row &&
				col == playerPosition.col)
			{
				SetConsoleColor(FOREGROUND_GREEN);
				std::cout << "P ";
				SetConsoleColor(
					FOREGROUND_BLUE |
					FOREGROUND_GREEN |
					FOREGROUND_RED);
				continue;
			}

			if (map[row][col] == 'x')
			{
				SetConsoleColor(FOREGROUND_RED);
				std::cout << "X ";
				SetConsoleColor(
					FOREGROUND_BLUE |
					FOREGROUND_GREEN |
					FOREGROUND_RED);
				continue;
			}

			std::cout << map[row][col] << " ";
		}

		std::cout << "\n";
	}
}
int main()
{
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 1;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&info
	);

	// 시작 위치 검색.
	Location2D start;

	bool found = false;
	for (int row = 0; row < mazeSize; row++)
	{
		if (found)  break;
		for (int col = 0; col < mazeSize; col++)
		{
			if (map[row][col] == 'e')
			{
				start.row = row;
				start.col = col;
				found = true;
				break;
			}
		}
	}

	// 초기 맵 출력.
	PrintMap(start, 0);

	// 스택 생성
	Queue<Location2D, mazeSize> queue;

	// 시작 위치 스택에 추가.
	queue.Enqueue(start);

	// 길찾기 (DFS).
	// 방문 및 길찾기 진행
	while (!queue.IsEmpty())
	{
		// 방문할 위치 꺼내기
		Location2D current;
		queue.Dequeue(current);

		PrintMap(current, 500);

		// 출구에 도착했는지 확인
		if (map[current.row][current.col] == 'x')
		{
			std::cout << "\n미로 탐색 성공!\n";
			return 0;
			break;
		}

		// 방문 및 방문한 위치 표시
		map[current.row][current.col] = '.';

		// 방문할 지점 스택에 추가.
		// 스택에 넣을 순서는 정할 수 있음.
		// 상/하/좌/우 순서로 스택에 삽입.
		if (IsValidLocation(
			Location2D(current.row - 1, current.col)))
		{
			queue.Enqueue(Location2D(current.row - 1, current.col));
		}
		if (IsValidLocation(
			Location2D(current.row + 1, current.col)))
		{
			queue.Enqueue(Location2D(current.row + 1, current.col));
		}
		if (IsValidLocation(
			Location2D(current.row, current.col - 1)))
		{
			queue.Enqueue(Location2D(current.row, current.col - 1));
		}
		if (IsValidLocation(
			Location2D(current.row, current.col + 1)))
		{
			queue.Enqueue(Location2D(current.row, current.col + 1));
		}
	}

	// 길찾기 실패.
	std::cout << "미로 탐색 실패\n";

	std::cin.get();
}