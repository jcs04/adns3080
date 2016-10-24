/*** Adns3080.cpp 
 *** Software to communicate with ADNS3080 mouse sensor, by Jennifer Caballero, 
 *** based in the code by Randy Mackay.
 ***/



#include "Adns3080_registers.h"
#include "Adns3080.h"
#include "Arduino.h"
#include "SPI.h"

/*! Method that selects the Adns3080 by setting to low the chip select pin */
void Adns3080::select() {

	digitalWrite(adns3080_ncs,LOW);

}

/*! Method that deselects the Adns3080 by setting to high the chip select pin */
void Adns3080::deselect() {

	digitalWrite(adns3080_ncs,HIGH);

}

/*! Method that resets the Adns3080 by sending a high pulse of 10us to the reset pin */
void Adns3080::reset() {

	digitalWrite(adns3080_reset,HIGH);
	delayMicroseconds(10);  //Min reset pulsewidth
	digitalWrite(adns3080_reset,LOW);
	delayMicroseconds(500); //Max input delay after reset (NPD,MOSI,NCS,SCLK)

}

/*! Method that checks if the serial communication with the Adns3080 is working, returns true if it's working */
bool Adns3080::check() {

	byte product_id = 0;
	this -> select();  //Select ADNS3080
	SPI.transfer(ADNS3080_PRODUCT_ID);
	delayMicroseconds(50);  //tSRAD
	product_id = SPI.transfer(0x00);
	this -> deselect();  //Deselect ADNS3080
	if (product_id == 0x17) { 
		return true;
	} else {
		return false;
	}

}

/*! Method that configures the Adns3080 with the parameters specified */
void Adns3080::configure() {

	byte data = 0;
	this -> select();  //Select ADNS3080

	//Reads the config_bits register
	SPI.transfer(ADNS3080_CONFIGURATION_BITS);
	delayMicroseconds(50);  //tSRAD
 	data = SPI.transfer(0x00);
	if (adns3080_led_mode) {	
		data = data | 0x40;  //Mask to put a 1 in the led mode bit
	} else {
		data = data & 0xbf;  //Mask to put a 0 in the led mode bit
	}
	
	if(adns3080_resolution) {
		data = data | 0x10;  //Mask to put a 1 in the res bit
	} else {
		data = data & 0xef;  //Mask to put a 0 in the res bit
	}
	//Writes the config_bits register
	delayMicroseconds(3);  //tSRW > 250 ns, set to 3us because is the smallest possible delay with the function delayMicroseconds
	SPI.transfer(ADNS3080_CONFIGURATION_BITS | 0x80);
	SPI.transfer(data);


	//Reads the extended_config register
	delayMicroseconds(50);  //tSWR ≥ 50µs 
	SPI.transfer(ADNS3080_EXTENDED_CONFIG);
	delayMicroseconds(50);  //tSRAD 
 	data = SPI.transfer(0x00);
	if (adns3080_serial_npu) {	
		data = data | 0x04;  //Mask to put a 1 in the serial no-pull up bit
	} else {
		data = data & 0xfb;  //Mask to put a 0 in the serial no-pull up bit
	}

	if (adns3080_nagc) {	
		data = data | 0x02;  //Mask to put a 1 in the no automatic gain control bit
	} else {
		data = data & 0xfd;  //Mask to put a 0 in the no automatic gain control bit
	}

	if (adns3080_fixed_fr) {	
		data = data | 0x01;  //Mask to put a 1 in the fixed frame-rate bit
	} else {
		data = data & 0xfe;  //Mask to put a 0 in the fixed frame-rate bit
	}

	//Writes the extended config register
	delayMicroseconds(3);  //tSRW > 250 ns, set to 3us because is the smallest possible delay with the function delayMicroseconds
	SPI.transfer(ADNS3080_EXTENDED_CONFIG | 0x80);
	SPI.transfer(data);


	//Set Framerate and shutter

	if (adns3080_fixed_fr == 0) {
		//FRAME_PERIOD_MIN_BOUND_LOWER, 0x7e0e is the min allowed (743 fps)
		busy();
		delayMicroseconds(3);  //tSRW > 250 ns, set to 3us because is the smallest possible delay with the function delayMicroseconds
		SPI.transfer(ADNS3080_FRAME_PERIOD_MIN_BOUND_LOWER | 0x80);
		SPI.transfer(frame_period_min_bound_lower);
		//SPI.transfer(0x0E);


		//FRAME_PERIOD_MIN_BOUND_UPPER
		busy();
		delayMicroseconds(3);  //tSRW > 250 ns, set to 3us because is the smallest possible delay with the function delayMicroseconds
		SPI.transfer(ADNS3080_FRAME_PERIOD_MIN_BOUND_UPPER | 0x80);
		SPI.transfer(frame_period_min_bound_upper);
		//SPI.transfer(0x7E);

	}


	//SHUTTER_MAX_BOUND_LOWER
	busy();
	delayMicroseconds(3);  //tSRW > 250 ns, set to 3us because is the smallest possible delay with the function delayMicroseconds
	SPI.transfer(ADNS3080_SHUTTER_MAX_BOUND_LOWER | 0x80);
	SPI.transfer(shutter_max_bound_lower);
	//SPI.transfer(0XD8);


	//SHUTTER_MAX_BOUND_UPPER
	busy();
	delayMicroseconds(3);  //tSRW > 250 ns, set to 3us because is the smallest possible delay with the function delayMicroseconds
	SPI.transfer(ADNS3080_SHUTTER_MAX_BOUND_UPPER | 0x80);
	SPI.transfer(shutter_max_bound_upper);
	//SPI.transfer(0X0F);

	//FRAME_PERIOD_MAX_BOUND_LOWER
	busy();
	delayMicroseconds(3);  //tSRW > 250 ns, set to 3us because is the smallest possible delay with the function delayMicroseconds
	SPI.transfer(ADNS3080_FRAME_PERIOD_MAX_BOUND_LOWER | 0x80);
	SPI.transfer(frame_period_max_bound_lower);
	//SPI.transfer(0xC0);


	//FRAME_PERIOD_MAX_BOUND_UPPER
	busy();
	delayMicroseconds(3);  //tSRW > 250 ns, set to 3us because is the smallest possible delay with the function delayMicroseconds
	SPI.transfer(ADNS3080_FRAME_PERIOD_MAX_BOUND_UPPER | 0x80);
	SPI.transfer(frame_period_max_bound_upper);
	//SPI.transfer(0x12);

        this -> deselect();  //Deselect ADNS3080

}


/*! Method that checks if writting to the registers Shutter_Max_Bound_Upper and Lower, Frame_Period_Min_Bound_Upper and Lower and 
Frame_Period_Max_Bound_Upper and Lower is allowed, if not make a loop until it is allowed */
void Adns3080::busy() {
	byte data = 0;
	delayMicroseconds(50);  //tSWR ≥ 50µs 
	SPI.transfer(ADNS3080_EXTENDED_CONFIG);
	delayMicroseconds(50);  //tSRAD 
 	data = SPI.transfer(0x00);
	while ((data & 0x80) != 0x00) {
		Serial.println("Registers not ready");
	}

}


/*! Method that returns true if motion was detected, also if there was motion, reads the motion data, surface quality and overflow bit */
bool Adns3080::motion() {
	this -> select();  //Select ADNS3080
        unsigned char motion;

	//Read the motion register
	SPI.transfer(ADNS3080_MOTION);
	delayMicroseconds(50);  //tSRAD
	motion = SPI.transfer(0x00);

	//Check if there is overflow
	if (motion & 0x10) {
		Serial.println("OVERFLOW DETECTED!");
		overflow = 1;
	} else {
		overflow = 0;
	}

	//Check if there was motion
	if (motion & 0x80) {
		//Serial.println("Motion Detected");

		//Read x
		SPI.transfer(ADNS3080_DELTA_X);
		delayMicroseconds(50);  //tSRAD
		delta_x = SPI.transfer(0x00);


		//Read y
		SPI.transfer(ADNS3080_DELTA_Y);
		delayMicroseconds(50);  //tSRAD
		delta_y = SPI.transfer(0x00);


		//Read surface Quality, max is 169
		SPI.transfer(ADNS3080_SQUAL);
		delayMicroseconds(50);  //tSRAD
		surface_quality = SPI.transfer(0x00);
		this -> deselect();  //Deselect ADNS3080
		return true;

	} else {
		//Serial.println("No Motion Detected");
		this -> deselect();  //Deselect ADNS3080
		return false;
	}

}
