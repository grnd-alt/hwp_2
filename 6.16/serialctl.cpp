#include <stdio.h>   /* Standard input/output definitions */
#include <iostream> 
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <b15f/b15f.h>
#include <chrono>
#include <thread>
#include <fstream>
using namespace std;
#define WR_BUFFER_LEN 32
#define RD_BUFFER_LEN 32

/*
 * 'open_port()' - Open serial port 1.
 *
 * Returns the file descriptor on success or -1 on error.
 */

int
open_port(void)
{
  int fd; /* File descriptor for the port */
	struct termios options;

  fd = open("/dev/ttyUSB1", O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1)
  {
    cout<<"open_port: Unable to open \n";
  }
  else {
  	// setting terminal options
    fcntl(fd, F_SETFL, FNDELAY);
		tcgetattr(fd, &options);
		cfsetispeed(&options, B115200);
		cfsetospeed(&options, B115200);
		options.c_cflag |= (CLOCAL | CREAD);
		options.c_cflag &= ~PARENB;
		options.c_cflag &= ~CSTOPB;
		options.c_cflag &= ~CSIZE;
		options.c_cflag |= CS8;
		tcsetattr(fd, TCSANOW, &options);
  	return (fd);
  }
  return 0;
}

/*
*
*main function
*/
int main(){
	int fd,n;
	B15F& drv = B15F::getInstance();
	drv.analogWrite0(1023);
	//:w21=1 set waveform to square
//":w23=26786,0.\r\n"; // set freq to 26786Hz
	fd=open_port();
	uint8_t write_buffer[WR_BUFFER_LEN]=":w21=1.\r\n";
	std::string output;
	std::ofstream file("dataTiefpass.txt");	
	std::string filestring;
	for (uint64_t freq = 1;freq<1000000; freq += std::ceil(pow(10,std::to_string(freq).size() -1) / 2.0f)){
		std::cout<<freq<<std::endl;
		output = ":w23=" + std::to_string(freq) + "00,0.\r\n";
		strcpy((char*)write_buffer,output.c_str());
		n = write(fd, write_buffer, WR_BUFFER_LEN);
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		int AE0max = 0;
		for(int i = 0; i< 10; i++){
			int AE0 = drv.analogRead(0);
			std::this_thread::sleep_for(std::chrono::milliseconds((uint64_t)((1000.0f / (float)freq)/10.0f)));
			if (AE0 > AE0max) {
				AE0max = AE0;
			}
		}
		std::cout<<freq<<";"<<AE0max<<std::endl;
		file<<freq<<";"<<AE0max<<std::endl;
		
	}
	file.close();
	strcpy((char*)write_buffer,":w23=20000,0.\r\n");
	uint8_t read_buffer[RD_BUFFER_LEN];
	n = write(fd, write_buffer, WR_BUFFER_LEN);
	if (n < 0){ 
		cout<<"write() failed!\n";
	}else{
		cout<<"write done\n";
	}
	read(fd,read_buffer,RD_BUFFER_LEN);// get answer from function generator
	cout << read_buffer<< endl;
	close(fd);
}
