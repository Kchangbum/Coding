#include<iostream>
#include<string>
using namespace std;

/*보글 게임판*/
/*
- 알고리즘
        - 기저 사례
                1) 시작 위치가 범위 밖이면 무조건 실패
                2) 첫 글자가 일치하지 ㅏㄶ으면 실패
                3) 단어 길이가 1이면 성공
        - 인접한 여덟 칸 검사
        - 다음 칸 범위안에 있는지, 첫 글자는 일치하는지 확인할 필요 없음

*/

/* 보글 게임판*/
char board[5][5] = {
        {'U', 'R', 'L', 'P', 'M'}, 
        {'X', 'P', 'R', 'E', 'T'},
        {'G', 'I', 'A', 'E', 'T'},
        {'X', 'T', 'N', 'Z', 'Y'},
        {'X', 'O', 'Q', 'R', 'S'},
};

// 8방향 이동 (좌상, 상, 우상, 좌, 우 좌하, 하 우하)
const int dx[8] = {-1, -1, -1, 1, 1, 1, 0, 0};
const int dy[8] = {-1, 0, 1, -1, 0, 1, -1, 1};

// 좌표 (y, x)가 보드 안에 있는지 확인
bool inRange(int y, int x) {
        return (y >= 0 && x >= 0 && y < 5 && x < 5);

}

//word를 읽기 전용(const)로 메모리 관리 및 안정성 개선
bool hasWord(int y, int x, const string& word) {
        //기저 사례 1)
        if (!inRange(y, x)) return false;
        //기저 사례 2)
        if (board[y][x] != word[0]) return false;
        //기저 사례 3)
        if (word.size() == 1) return true;

        //인접한 여덟 칸 탐색
        for (int direction = 0; direction < 8; direction ++) {
                int nextX = x + dx[direction];
                int nextY = y + dy[direction];

                //다음 위치에서 나머지 단어 탐색
                if (hasWord(nextY, nextX, word.substr(1))) return true;
        }
        return false;
}

int main() {
        string word = "PRETTY";

        cout << (hasWord(1, 1, word) ? "Found" : "Not Found") << endl;
}