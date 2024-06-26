#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
//Fibonacci secara dynamic programming
class Fibonacci{
    public:
    std::vector<long long> memo;
    long long setMemo(int n){
        memo = std::vector<long long>(n+1);
    }

    long long dynaFibo(int n){
        memo[0] = 0;
        memo[1] = 1;
        for (long long i = 2; i <= n; i++) {
            memo[i] = memo[i - 1] + memo[i - 2];
        }
        return memo[n];
    }

    long long fibo(int n){
        if (n<=1) return n;
        return fibo(n-1)+fibo(n-2);
    }

};

//Fibonacci secara rekursif

int main(){
    int njumlah[] = {10, 25, 30, 40, 50};
    Fibonacci dp;
    int loops[] = {1000,150,20,7,4};
    long long (Fibonacci::*arrayOfFunction[])(int) = {&dp.fibo, &dp.dynaFibo};

    std::ofstream file("KompleksitasWaktu.csv");
    if (!file.is_open()){
        std::cerr << "Error opening output file!" << std::endl;
        return 1;
    }
    file << "n,Rekursif,DynamicFibonacci" << std::endl;
    for (int i = 0; i < 5; i++){
        int loop = loops[i];
        file << njumlah[i];
        for(int j = 0; j < 2; j++){
            int n = njumlah[i];
            if (j == 1)dp.setMemo(n);
            double total = 0;
            for (int k = 0; k < loop; k++){    
            auto start = std::chrono::high_resolution_clock::now();
            (dp.*arrayOfFunction[j])(n);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            total += duration.count();
            }
            std::cout << total/loop << std::endl;
            file << "," << total/loop;
        }
        file << std::endl;
    }
    return 0;
}