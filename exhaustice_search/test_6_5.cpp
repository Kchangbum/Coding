/*========================================================*/
/*
****게임판 덮기****
1. 문제 이해
        - H x W 크기의 게임판
        - 검은 칸과 흰 칸으로 구성
        - 서로 겹치거나, 검은 칸을 덮거나, 게임판 밖으로 나가서는 안됨
        - 흰칸을 세 칸짜리 L자 모양의 블록으로 덮기
        - 2초 안에 실행
        - 64MB 이하의 메모리를 사용
        입력:
                - 첫 줄: 테스트 케이스의 수 C
                - 두 번째 줄: 두개의 정수 H,W(1<=H, W <= 20)
                - 세 번째 줄: H줄에 각 W글자로 게임판의 모양이 주어짐 ('#': 검은칸, '.': 흰칸)
        입력이 주어지는 흰 칸의 수는 50을 넘지 않음
        출력:
                - 한 줄에 하나씩 흰 칸을 모두 덮는 방법의 수 출력
2. 문제를 익숙한 용어로 재정의
        - 사용 함수와 변수
                - 함수
                        - 블럭 배치 여부
                                - bool set(vector<vector<int>>& board, int x, int y, int type, int delta);
                        - 게임판을 완전히 덮은 케이스 수
                                - int cover(vector<vector<int>>& board);
                        - 메인 함수
                                - int main()
                - 변수 
                        - boardType[][][]       = 만들 수 있는 블럭
                        - x                     = x좌표
                        - y                     = y좌표
                        
                        - board[][]             = 게임판을 입력할 2차원 배열
                        - cases                 = 테스트 케이스 수
                        - str                   = 게임 판을 만들 문자(#: 검은색 .: 흰색)

                        - type                  = 놓고자 하는 블럭 타입
                        - delta                 = 블럭 배치 여부 (1:배치 / -1: 제거)
                        - ret                   = 모두 덮어진 게임 판 수 

3. 어떻게 진행할지 계획 수립
        기저 사례)
                1. 서로 겹치는 상황 (한번쓴 곳은 다시 쓸 수 없음)
                2. 검은 칸을 덮는 상황
                3. 게임판 밖으로 나가는 상황

        성공)
                흰칸을 세 칸짜리 L자 모양의 블록으로 덮기
4. 계획 검증
5. 프로그램 구현
*/

#include<iostream>
#include<vector>
#include<string>

using namespace std;

int H, W; // 게임판 크기
int cases; // 테스트 케이스 수
int coverType[4][3][2] = { //블럭 타입
        { {0,0}, {1,0},  {0,1} },
        { {0,0}, {0,1},  {1,1} },
        { {0,0}, {1,0},  {1,1} },
        { {0,0}, {1,0}, {1,-1} }
};

/*블록 배치 여부*/
bool set(vector<vector<int>>& board, int x, int y, int type, int delta) {
        bool ok = true;
        for(int i = 0; i < 3; i++) { 
                int nx = x + coverType[type][i][0];
                int ny = y + coverType[type][i][1];

                //도형이 게임판 밖으로 나가거나 다른 도형과 겹치는지 확인 / delta가 -1인 경우
                //board[][] += delta >1 => 1보다 크면 블록이 있다는 것을 의미하므로 false
                        // += 연산으로 delta가 -1이 되면 블록을 제거
                if(nx < 0 || nx >= board.size() || ny < 0 || ny >+ board[i].size() || (board[nx][ny] += delta) > 1) ok = false;

        }
        return ok;
}

/*게임판을 완전히 덮은 케이스 수*/
int cover(vector<vector<int>>& board) {
        int x = -1;
        int y = -1;
        for(int i = 0; i < board.size(); i++) {
                for(int j = 0; j < board[i].size(); j++) {
                        if(board[i][j] == 0) { //가장 왼쪽 위가 빈칸인 위치 지정
                                x = i;
                                y = j;
                                break;
                        }
                }
                if(y != -1) break; // 칸을 찾았을 때
        }

        if(y == -1) return 1; // 모든 칸을 찾았을 때 

        int ret = 0;
        for(int type = 0; type < 4; type++) {
                if(set(board, x, y, type, 1)) ret += cover(board); // 블럭 배치
                set(board, x, y, type, -1); //블럭 제거
        }
        return ret;
}

int main() {
        cin >> cases;
        while(cases--) {
                cin >> H >> W;
                string str;
                vector<vector<int>> board(H, vector<int>(W,0)); // 게임판

                for(int i = 0; i < H; i++) { // 게임판 입력
                        cin >> str;
                        for(int j = 0; j < str.size(); j++) {
                                if(str[j] == '#') board[i][j] = 1;
                        }
                }

                cout << cover(board) << endl << endl;
        }
}

/*
6. 어떻게 풀었는지 돌아보고, 개선할 방법이 있는지 탐색
*/
/*========================================================*/