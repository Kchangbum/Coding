#include<iostream>
#include<vector>
using namespace std;

/* 작업 정의
        - 원소들의 총 개수
        - 더 골라야 할 원소들의 개수
        - 지금까지 고른 원소들의 번호
*/
/*
        - n: 원소의 개수
        - picked: 지금까지 고른 원소들의 번호
        - toPick:  더 고를 원소의 수
        일때, 앞으로 toPick개의 원소를 고르는 모든 방법 출력
*/
void printPicked(vector<int>& picked) {
        //print
        cout <<"(  ";
        for(int i = 0; i < picked.size(); i++) {
                cout << picked[i] << "  ";
        }
        cout <<")"<<endl;
}

void pick(int n, vector<int>& picked, int toPick) {
        //더 고를 원소가 없을때 고른 원소들을 출력
        if(toPick == 0) {
                printPicked(picked); 
                return;
        }
        //고를 수 있는 가장작은 번호를 계산
        int smallest = picked.empty() ? 0 : picked.back() + 1;  //back() 함수: vector의 마지막 요소를 반환
        for(int next = smallest; next < n; next++) {
                picked.push_back(next);
                pick(n, picked, toPick-1);
                picked.pop_back();
        }
}


int main() {
        int n = 7;
        vector<int> picked;
        int toPick = 4;
        pick(n, picked, toPick);
}