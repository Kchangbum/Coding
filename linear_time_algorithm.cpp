#include<iostream>
#include<vector>
using namespace std;

// 길이가 N인 실수 배열 A가 주어질 때, 각 위치에서의 M-이동 평균 값을 구한다.
vector<double> movingAverage2(const vector<double>& A, int M) {
        vector<double> ret;
        int N = A.size();       // 입력할 데이터
        double partialSum = 0;  // 각 부분을 합칠 변수

        for(int i = 0; i < M-1; ++i)    //시간 복잡도: M-1+(N-M+1) = N => O(N)
        partialSum += A[i];
        for(int i = M-1; i < N; ++i) {
                partialSum += A[i];
                ret.push_back(partialSum/M);
                partialSum -=A[i-M+1];
        }
        return ret;
}

int main() {
        vector<double> A = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
        int M = 3;
        vector<double> result = movingAverage2(A, M);

        for(int i = 0; i < result.size(); i++)
        cout << result[i] << "    ";
}