// https://www.hackerrank.com/contests/w36/challenges/ways-to-give-a-check

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;


bool checkKnight(vector<string>& board, int i, int j) {
	// check all the combinations
	if (i - 2 >= 0 && j + 1 < 8 && board[j + 1][i - 2] == 'k')  // -2, 1
		return true;

	if (i - 1 >= 0 && j + 2 < 8 && board[j + 2][i - 1] == 'k')  // -1, 2
		return true;

	if (i + 1 < 8 && j + 2 < 8 && board[j + 2][i + 1] == 'k')   // 1, 2
		return true;

	if (i + 2 < 8 && j + 1 < 8 && board[j + 1][i + 2] == 'k')   // 2, 1
		return true;

	if (i + 2 < 8 && j - 1 >= 0 && board[j - 1][i + 2] == 'k')  // 2, -1
		return true;

	if (i + 1 < 8 && j - 2 >= 0 && board[j - 2][i + 1] == 'k')  // 1, -2
		return true;

	if (i - 1 >= 0 && j - 2 >= 0 && board[j - 2][i - 1] == 'k') // -1, -2
		return true;

	if (i - 2 >= 0 && j - 1 >= 0 && board[j - 1][i - 2] == 'k') // -2, -1
		return true;

	return false;
}

bool checkRook(vector<string>& board, int _i, int _j, bool white = true) {
	char kingToDefeat = white ? 'k' : 'K';
	// left
	for (int i = _i - 1; i >= 0; i--) {
		if (board[_j][i] == '#')
			continue;
		else if (board[_j][i] == kingToDefeat)
			return true;
		else
			break;
	}

	// right
	for (int i = _i + 1; i < 8; i++) {
		if (board[_j][i] == '#')
			continue;
		else if (board[_j][i] == kingToDefeat)
			return true;
		else
			break;
	}

	// down
	for (int j = _j + 1; j < 8; j++) {
		if (board[j][_i] == '#')
			continue;
		else if (board[j][_i] == kingToDefeat)
			return true;
		else
			break;
	}

	// up
	for (int j = _j - 1; j >= 0; j--) {
		if (board[j][_i] == '#')
			continue;
		else if (board[j][_i] == kingToDefeat)
			return true;
		else
			break;
	}

	return false;
}

bool checkRooks(vector<string>& board, bool white = true) {
	char rook = white ? 'R' : 'r';
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			if (board[j][i] == rook && checkRook(board, i, j, white))
				return true;

	return false;
}

bool checkBishop(vector<string>& board, int _i, int _j, bool white = true) {
	char kingToDefeat = white ? 'k' : 'K';
	// down left
	int i = _i - 1;
	int j = _j + 1;
	while (i >= 0 && i < 8 && j >= 0 && j < 8) {
		if (board[j][i] != '#')
			if (board[j][i] == kingToDefeat)
				return true;
			else
				break;

		i--;
		j++;
	}

	// down right
	i = _i + 1;
	j = _j + 1;
	while (i >= 0 && i < 8 && j >= 0 && j < 8) {
		if (board[j][i] != '#')
			if (board[j][i] == kingToDefeat)
				return true;
			else
				break;

		i++;
		j++;
	}

	// up right
	i = _i + 1;
	j = _j - 1;
	while (i >= 0 && i < 8 && j >= 0 && j < 8) {
		if (board[j][i] != '#')
			if (board[j][i] == kingToDefeat)
				return true;
			else
				break;

		i++;
		j--;
	}

	// up left
	i = _i - 1;
	j = _j - 1;
	while (i >= 0 && i < 8 && j >= 0 && j < 8) {
		if (board[j][i] != '#')
			if (board[j][i] == kingToDefeat)
				return true;
			else
				break;

		i--;
		j--;
	}

	return false;
}

bool checkBishops(vector<string>& board, bool white = true) {
	char bsh = white ? 'B' : 'b';
	for (int j = 0; j < 8; ++j)
		for (int i = 0; i < 8; ++i)
			if (board[j][i] == bsh && checkBishop(board, i, j, white))
				return true;

	return false;
}

bool checkQueen(vector<string>& board, int i, int j, bool white = true) {
	return checkRook(board, i, j, white) || checkBishop(board, i, j, white);
}

bool checkQueens(vector<string>& board, bool white = true) {
	char queen = white ? 'Q' : 'q';
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			if (board[j][i] == queen && checkQueen(board, i, j, white))
				return true;

	return false;
}

vector<string> promoteBoardPawn(vector<string>& board) {
	vector<string> res;
	for (auto s : board)
		res.push_back(s);

	for (int i = 0; i < 8; ++i)
		if (board[1][i] == 'P' && board[0][i] == '#') { // promote
			res[0][i] = 'X';
			res[1][i] = '#';
			if (checkBishops(res, false) || checkQueens(res, false) || checkRooks(res, false))
			{
				res[0][i] = '#';
				res[1][i] = 'P';
			}
			else
				break;
		}

	return res;
}

int numberOfWays(vector<string>& board) {
	vector<string> res = promoteBoardPawn(board);

	int px, py;
	for (int j = 0; j < 8; ++j)
		for (int i = 0; i < 8; ++i)
			if (res[j][i] == 'X') {
				px = i;
				py = j;
				break;
			}

	int cnt = 0;
	if (checkBishops(res) || checkQueens(res) || checkRooks(res))
		cnt = 4;
	else {
		cnt += checkKnight(res, px, py);
		cnt += checkRook(res, px, py);
		cnt += checkBishop(res, px, py);
		cnt += checkQueen(res, px, py);
	}

	return cnt;
}

int main() {
	int n;
	cin >> n;

	while (n--) {
		vector<string> board;
		for (int i = 0; i < 8; ++i) {
			string s;
			cin >> s;

			board.push_back(s);
		}

		cout << numberOfWays(board) << endl;
	}
	return 0;
}
