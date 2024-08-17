//AD:SELENAY 
//SOYAD:HUR 
//ÖĞRENCİ NUMARASI: 23080103374 
//ÖĞRETİM GÖREVLİSİ:Dr. Öğr. Üyesi SELMAN HIZAL
#include <iostream>
#include <chrono>
#include <stack>
#include <vector>
#include <string>
#include <cmath>
#include <tuple>
#include <thread>
using namespace std;

vector<vector<int>> kuleler;

void kuleleriGoster(int diskSayisi) {
    int maxYukseklik = diskSayisi;
    
    for (int y = maxYukseklik - 1; y >= 0; y--) {
        for (int x = 0; x < 3; x++) {
            if (y < kuleler[x].size()) {
                int diskBoyutu = kuleler[x][y];
                string disk = string(diskBoyutu, '*');
                cout << string(maxYukseklik - diskBoyutu, ' ') << disk << string(maxYukseklik - diskBoyutu, ' ') << "  ";
            } else {
                cout << string(maxYukseklik * 2 + 1, ' ') << "  ";
            }
        }
        cout << endl;
    }
    cout << string(3, '-') << string((maxYukseklik * 2 + 2) * 3 - 3, ' ') << endl;
    cout << " A " << string(maxYukseklik * 2 - 1, ' ') << " B " << string(maxYukseklik * 2 - 1, ' ') << " C " << endl;
    cout << endl;
}


void diskTasi(int disk, char kaynak, char hedef) {
    int kaynakIndex = kaynak - 'A';
    int hedefIndex = hedef - 'A';
    int diskBoyutu = kuleler[kaynakIndex].back();
    kuleler[hedefIndex].push_back(kuleler[kaynakIndex].back());
    kuleler[kaynakIndex].pop_back();
    cout << diskBoyutu << ". diski " << kaynak << "'dan " << hedef << "'ye tasi." << endl;
    kuleleriGoster(kuleler[0].size() + kuleler[1].size() + kuleler[2].size());
    
    // Basit bir bekleme döngüsü
    for(long long i = 0; i < 100000000; ++i) {
        // Boş döngü, işlemciyi meşgul eder
    }
}


void Hanoi(int n, char kaynak, char ara, char hedef) {
    if (n == 1) {
        diskTasi(1, kaynak, hedef);
    } else {
        Hanoi(n - 1, kaynak, hedef, ara);
        diskTasi(n, kaynak, hedef);
        Hanoi(n - 1, ara, kaynak, hedef);
    }
}

void HanoiIteratif(int n, char kaynak, char ara, char hedef) {
    stack<tuple<int, char, char, char>> hareketler;
    hareketler.push(make_tuple(n, kaynak, ara, hedef));

    while (!hareketler.empty()) {
        int diskSayisi;
        char k, a, h;
        tie(diskSayisi, k, a, h) = hareketler.top();
        hareketler.pop();

        if (diskSayisi == 1) {
            diskTasi(1, k, h);
        } else {
            hareketler.push(make_tuple(diskSayisi - 1, a, k, h));
            hareketler.push(make_tuple(1, k, a, h));
            hareketler.push(make_tuple(diskSayisi - 1, k, h, a));
        }
    }
}

int main() {
    int diskSayisi;
    cout << "Disk Sayisi: ";
    cin >> diskSayisi;

    kuleler = vector<vector<int>>(3);
    for (int i = diskSayisi; i > 0; i--) {
        kuleler[0].push_back(i);
    }

    cout << "Baslangic durumu:" << endl;
    kuleleriGoster(diskSayisi);

    // Rekürsif çözüm
    cout << "Rekursif cozum:" << endl;
    auto baslangicRekursif = chrono::high_resolution_clock::now();
    Hanoi(diskSayisi, 'A', 'B', 'C');
    auto bitisRekursif = chrono::high_resolution_clock::now();
    auto sureRekursif = chrono::duration_cast<chrono::milliseconds>(bitisRekursif - baslangicRekursif);

    // Kuleleri sıfırla
    kuleler = vector<vector<int>>(3);
    for (int i = diskSayisi; i > 0; i--) {
        kuleler[0].push_back(i);
    }

    cout << "Iteratif cozum:" << endl;
    auto baslangicIteratif = chrono::high_resolution_clock::now();
    HanoiIteratif(diskSayisi, 'A', 'B', 'C');
    auto bitisIteratif = chrono::high_resolution_clock::now();
    auto sureIteratif = chrono::duration_cast<chrono::milliseconds>(bitisIteratif - baslangicIteratif);

    // Sonuçları yazdır
    cout << "Zaman karmasikligi: O(2^n)" << endl;
    cout << "Rekursif cozum suresi: " << sureRekursif.count() << " milisaniye" << endl;
    cout << "Iteratif cozum suresi: " << sureIteratif.count() << " milisaniye" << endl;

    return 0;
}