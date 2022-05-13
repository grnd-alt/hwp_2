#include <b15f/b15f.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>

int main(){
	B15F& drv = B15F::getInstance();
	std::ofstream file;
	file.open("data.txt");
	int storage = 0;
	double volt = 0;
	std::string filestring = "";
	for (int i = 0; i < 24; i++){
		//std::cout<<"Storage: "<<storage<<std::endl;
		std::cout<<"Input: "<<volt<<" V"<<std::endl;
		drv.analogWrite0(storage);
		std::cout<<"Output: "<< (drv.analogRead(0)*5.0)/1024.0<<" V"<<std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		filestring += std::to_string(volt) + ";" + std::to_string((drv.analogRead(0)*5.0)/1024) + "\n";
		storage += 41;
                volt += 0.2;
	}
	file << filestring;
	drv.analogWrite0(1023);
	filestring += std::to_string(5) + ";" + std::to_string((drv.analogRead(0)*5.0)/1024) + "\n";
	file << filestring;
	std::cout<<"Input: "<<"5 V"<<std::endl;
	std::cout<<"Output: "<<(drv.analogRead(0)*5.0)/1024.0<<" V"<<std::endl;

	drv.analogWrite0(0);
}
