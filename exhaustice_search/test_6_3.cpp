#include <iostream>
#include<cstring>
using namespace std;

int n;
bool areFriends[10][10];

// 짝을 찾을 수 있는 경우의 수를 계산하는 함수
int countPairings(bool taken[10]) {
        int firstFree = -1; // 남는 학생들 중 가장 번호가 빠른 학생

        // 기저 사례) 모든 학생이 짝을 찾았으면 한 가지 방법을 찾았으므로 종료
        for(int i = 0; i < n; i++) {
                if(!taken[i]) {
                        firstFree = i; // taken[i]가 0인 학생의 인덱스 확인
                        break;
                }
        }
        
        if(firstFree == -1) return 1;  // 모든 학생이 짝을 찾았다면 1을 반환
        int ret = 0;

        // 짝을 찾기 위한 탐색
        for(int pathWith = firstFree+1; pathWith < n; pathWith++) {
                        if(!taken[pathWith] && areFriends[firstFree][pathWith]) {  // 남은 학생 중 가장 번호가 빠른 학생이 있고 그 학생과 친한 짝이 있을 경우
                                taken[firstFree] = taken[pathWith] = true;  // firstFree와 pathWith를 짝으로 지정
                                ret += countPairings(taken);  // 나머지 학생들에 대해 재귀적으로 짝을 찾음
                                taken[firstFree] = taken[pathWith] = false;  // firstFree와 pathWith를 다시 없앰 (백트래킹)
                        }
        }
                        
        return ret;  // 계산된 짝의 수 반환
}

int main() {
        int cases;
        cin >> cases;  // 테스트 케이스 수 입력

        for (int i = 0; i < cases; i++) {
                int m;
                cin >> n >> m;  // 학생 수 n과 친구 관계의 개수 m 입력
                
                bool taken[10]; // 학생들이 짝을 찾았는지 여부를 나타내는 배열
		memset(taken, 0, sizeof(taken));
		memset(areFriends, 0, sizeof(areFriends));

                // 친구 관계 설정
                for (int j = 0; j < m; j++) {
                        int x, y;
                        cin >> x >> y;  // 친구 관계 입력
                        areFriends[x][y] = areFriends[y][x] = true;
                }

                cout << countPairings(taken) << endl;  // 가능한 짝짓기 방법의 수 출력
        }

        return 0;
}


/* 
1. 문제 이해
        - 각 학생들의 쌍에 대해 이들이 서로 친구인지 여부가 주어질 때, 학생들을 짝지을 수 있는 방법의 수 계산
        - 문제 분석
                - 입력: 
                        - 학생 수 C
                        - 친구 관계를 나타내는 이차원 배열 friend[i][j]
                - 출력:
                        - 모든 학생이 짝지어진 상태로 만들 수 있는 경우의 수
                - 조건:
                        - 모든 학생이 짝지어야 함
                        - 짝이 되는 학생들이 일부만 다르더라도 다른 방법으로 간주
2. 문제를 익숙한 용어로 재정의와 추상화
        - 문제 정의 (재귀적 사고)
                - 기저 사례) 
                        - 남은 학생이 없으면(모두 짝지어졌으면) 1가지 방법으로 간주
                - 재귀적 사례)
                        - 첫 번째 짝지어지지 않은 학생을 선택
                        - 그 학생과 친구인 나머지 학생들과 짝을 지어보며 가능한 모든 방법을 재귀적으로 계산
                => 짝지어지지 않은 첫 번째 학생을 찾음 -> 해당 학생과 짝이 될 수 있는 모든 친구를 찾아서 짝을 짓고 나머지 학생들에 대해 재귀호출 -> 짝을 지을 때마다 경우의 수 누적
        - 문제 추상화
                - 함수 정의
                        - int countParings(bool taken[])
                - 변수
                        - taken[]: 각 학생이 짝지어졌는지 여부를 저장하는 배열
                        - arefriends[][]: 친구 관계를 나타내는 이차원 배열
                        - n: 전체 학생 수
                - 함수 동작
                        - 모든 학생이 짝지어졌는지 확인 (taken배열이 모두 true면 1반환)
                        - 아직 짝지어지지 않은 첫 번째 학생을 찾음
                        - 해당 학생과 짝지을 수 있는 찾구를 찾아 짝을 짓고, 재귀적으로 나머지 학생들을 처리
                        - 짝을 지은 후에는 짝짓기를 원상복구하여 다름 경우를 탐색 (백트래킹)
3. 어떻게 진행할지 계획 수립
        1. 입력 받기
                - 학생 수 n을 입력 받고, 친구 관계를 나타내는 friend[][]배열을 설정
        2. 짝짓기 함수 호출
                - taken[]배열을 false로 초기화하여 아무도 짝지어지지 않은 상태에서 시작
        3. 재귀적으로 가능한 모든 짝짓기 경우의 수 계산
                - 첫 번째로 짝지어지지 않은 학생을 찾고, 친구들과 짝을 지으며 경우의 수 탐색
                - 백트래킹을 사용하여 모든 가능한 조합을 시도
        4. 결과 출력
                - 가능한 모든 짝짓기 방법의 수를 출력
4. 계획 검증 및 수행
        - 기본적인 테스트 케이스 수행
                - 작은 입력값부터 실행하여 예상한 결과가 나오는지 확인
5. 프로그램 구현
6. 어떻게 풀었는지 돌아보고, 개선할 방법이 있는지 탐색
*/