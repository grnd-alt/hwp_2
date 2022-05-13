#include <b15f/b15f.h>
#include <cmath>
#include <iostream>

int main(){
	B15F& drv = B15F::getInstance();
	std::ofstream file;
	file.open("dataMos4.txt");
	//writing
	drv.analogWrite1(0); // AA1 set to 0V - changing in loop
	//reading
	double AE0 = drv.analogRead(0); // reading AE0
	double AE1 = drv.analogRead(1); // reading AE1
	double AE2 = drv.analogRead(2); // reading AE2
	double AE3 = drv.analogRead(3); //reading AE3
	std::string filestring ="";
	for (int i = 0; i < 1023;i+=8){
		drv.analogWrite0(i);
		double AE0 = drv.analogRead(0); // reading AE0
		double AE1 = drv.analogRead(1); // reading AE1
		double U1 = ((AE0 - AE1)*5.0)/1024;
		double current = (U1 / 100) * 1000;
		std::cout<< std::to_string(U1) + ";"+std::to_string((i*5.0)/1024)+";"+std::to_string(current)<<std::endl;
		filestring += std::to_string(U1) + ";" + std::to_string((i*5.0)/1024) + ";" + std::to_string(current) + "\n";
	}
	file << filestring;
	drv.analogWrite0(0);
	drv.analogWrite1(0);
}

