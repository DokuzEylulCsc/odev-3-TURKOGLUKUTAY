#include <iostream>
#include <fstream>
#include <vector>
#include <string>
//Gurbuz Kutay Turkoglu
//2019280075
using namespace std;

int main(){
	ifstream infile("input.txt");
	string a, cevap_anahtari;
	int satir = 1, ogrenci_sayisi, puan;
	vector <string> ogrenciler, ogrencilerin_advepuanlari, ogrencilerin_numaralari, ogrencilerin_cevaplari;
	vector <int> ogrencilerin_puanlari;
	while (infile >> a) {   //https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c
	if (satir==1) {
		ogrenci_sayisi = stoi(a); //https://www.techiedelight.com/convert-string-to-int-cpp/
		satir++;
		continue;
	}
	if (satir==2) { 
		cevap_anahtari = a;
		satir++;
		continue;
	}
	ogrenciler.push_back(a);
	satir++;
	}
	int virgul;
	string ogrenci_numarasi;

	for(int i=0; i<ogrenciler.size(); i++) {
		virgul = ogrenciler[i].find(",");
		ogrenci_numarasi = ogrenciler[i][0];

		for(int j=1; j< virgul; j++) {
			ogrenci_numarasi = ogrenci_numarasi + ogrenciler[i][j];
		}
		ogrencilerin_numaralari.push_back(ogrenci_numarasi);
		string ogrenci_cevaplari;

		for (int k=virgul+1; k<ogrenciler[i].length(); k++) {
			ogrenci_cevaplari = ogrenci_cevaplari + ogrenciler[i][k];
		}
		ogrencilerin_cevaplari.push_back(ogrenci_cevaplari);
	}

	int toplampuan = 0;
	for(int i=0; i<cevap_anahtari.length(); i++) {
		string tempk;
		tempk.push_back(cevap_anahtari[i]);
		if(tempk != ",") toplampuan += 4;
	} 

	for(int i=0; i<ogrenciler.size(); i++) {
		puan = 0;
		for (int j=0; j<ogrencilerin_cevaplari[i].length(); j++) {
			string k;
			k.push_back(ogrencilerin_cevaplari[i][j]);
			if (k == " " || k == ",") puan +=0;
			else if(ogrencilerin_cevaplari[i][j] == cevap_anahtari[j]) puan +=4;
			else puan += -1;
		}
		if (puan < 0) puan = 0;
		puan = 100 * puan / toplampuan;
		string temppuan = ogrencilerin_numaralari[i] + " : " + to_string(puan); //http://www.cplusplus.com/reference/string/to_string/
		ogrencilerin_puanlari.push_back(puan);
		ogrencilerin_advepuanlari.push_back(temppuan);
	}

	float ortalama = 0, medyan;
	int maxpuan = 0, minpuan = 10000, aciklik;
	for(int i=0; i<ogrencilerin_puanlari.size(); i++) {
		if(maxpuan < ogrencilerin_puanlari[i]) maxpuan = ogrencilerin_puanlari[i];	
		if(minpuan > ogrencilerin_puanlari[i]) minpuan = ogrencilerin_puanlari[i];
		ortalama += ogrencilerin_puanlari[i];
	}
	ortalama = ortalama / ogrenciler.size();

	vector <int> temppuan = ogrencilerin_puanlari;
	for(int i=0; i<temppuan.size(); i++) {
		for (int j=0; j<temppuan.size()-1;j++) {
			if(temppuan[j]>temppuan[j+1]){
				swap(temppuan[j+1],temppuan[j]);
			}
		}
	}
	
	int i = temppuan.size();
	if (ogrenci_sayisi % 2 == 0) medyan = (temppuan[i/2]+temppuan[(i/2)-1]) / 2.0f;
	else medyan = temppuan[(i/2)-0.5];
	aciklik = temppuan[i-1] - temppuan[0];

	ofstream myfile;
	myfile.open("output.txt");
	myfile <<ogrenci_sayisi << "\n";
	myfile <<cevap_anahtari << "\n";

	for(int i= 0; i<ogrenciler.size(); i++) {
		myfile << ogrenciler[i] << "\n";
	}
	for(int i = 0; i<ogrencilerin_advepuanlari.size(); i++) {
		myfile << ogrencilerin_advepuanlari[i] << "\n";
	}

	myfile<<"Sinif ortalamasi: "<<ortalama<<"\n";
	myfile<<"en yuksek puan: "<<maxpuan<<"\n";
	myfile<<"En dusuk puan: "<<minpuan<<"\n";
	myfile<<"Medyan:"<<medyan<<"\n";
	myfile<<"Aciklik:"<<aciklik<<"\n";
	myfile.close();

	return 0;
	}
