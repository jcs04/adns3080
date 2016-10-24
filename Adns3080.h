#ifndef ADNS3080_CLASS
#define ADNS3080_CLASS

/*!  Class Adns3080 */

class Adns3080 {
    
    public:
	//Adns3080 pins
	int adns3080_miso;  //! Master Input, Slave Output pin from adns3080 to microcontroller
	int adns3080_mosi;  //! Master Output, Slave Input pin from microcontroller to adns3080
	int adns3080_sclk;  //! Slave Clock pin from microcontroller to adns3080
	int adns3080_ncs;  //! Chip-Select pin from microcontroller to adns3080, active low
	int adns3080_reset;  //! Reset pin from microcontroller to adns3080, active high

	//Configuration parameters
	bool adns3080_led_mode;  //! 0 = Led always on, 1 = Led on when illumination is required.
	bool adns3080_resolution;  //! Resolution in counts per inch, 0 = 400, 1 = 1600.
	bool adns3080_serial_npu;  //! 1 to disable port pull-up current sources.
	bool adns3080_nagc;  //! 1 to disable Automatic Gain Control, Shutter will be set to the value in the Shutter_Max_Bound registers.
	bool adns3080_fixed_fr; //! 1 for fixed frame rate, the frame rate is determined by Frame_Period_Max_Bound register.
	unsigned char frame_period_min_bound_lower;  //! Sets the maximum frame rate lower byte, Frame_rate_max = Clk_rate/frame_period_min_bound 
	unsigned char frame_period_min_bound_upper;  //! Sets the maximum frame rate upper byte, Frame_rate_max = Clk_rate/frame_period_min_bound 
	unsigned char shutter_max_bound_lower;  //! Sets the maximum allowable shutter lower byte value in clock cycles 
	unsigned char shutter_max_bound_upper;  //! Sets the maximum allowable shutter upper byte value in clock cycles 
	unsigned char frame_period_max_bound_lower;  //! Sets the minimum frame rate lower byte, Frame_rate_min = Clk_rate/frame_period_min_bound
	unsigned char frame_period_max_bound_upper;  //! Sets the minimum frame rate upper byte, Frame_rate_min = Clk_rate/frame_period_min_bound

	//Adns3080 output data
	int surface_quality = 0;
	signed char delta_x = 0;
	signed char delta_y = 0;
	bool overflow;

 
	void select();  //! Selects Adns3080.
	void deselect();  //! Deselects Adns3080.
        void reset();  //! Resets Adns3080.
	bool check();  //! Checks if microcontroller communication with Adns3080 is working.
	void configure();  //!  Write registers of Adns3080 with configuration parameters.
	void busy();  //!  Checks if it's safe to write to the Frame_Period_Max_Bound_Upper and Lower, Frame_Period_Min_Bound_Upper and Lower, Shutter_Max_Bound_Upper and Lower registers.
	bool motion();  //! Returns true if there was motion, sets delta_x, delta_y, overflow and surface quality.

};

#endif
