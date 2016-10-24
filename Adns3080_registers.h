//Clock Frequency of Adns3080
#define ADNS3080_FSCLK		2000000  //Max is 2MHz

// Register Map for the ADNS3080 Optical OpticalFlow Sensor
#define ADNS3080_PRODUCT_ID            0x00	//R
#define ADNS3080_REVISION_ID           0x01	//R
#define ADNS3080_MOTION                0x02	//R
#define ADNS3080_DELTA_X               0x03	//R
#define ADNS3080_DELTA_Y               0x04	//R
#define ADNS3080_SQUAL                 0x05	//R
#define ADNS3080_PIXEL_SUM             0x06	//R
#define ADNS3080_MAXIMUM_PIXEL         0x07	//R
#define ADNS3080_CONFIGURATION_BITS    0x0a	//RW
#define ADNS3080_EXTENDED_CONFIG       0x0b	//RW
#define ADNS3080_DATA_OUT_LOWER        0x0c	//R
#define ADNS3080_DATA_OUT_UPPER        0x0d	//R
#define ADNS3080_SHUTTER_LOWER         0x0e	//R
#define ADNS3080_SHUTTER_UPPER         0x0f	//R
#define ADNS3080_FRAME_PERIOD_LOWER    0x10	//R
#define ADNS3080_FRAME_PERIOD_UPPER    0x11	//R
#define ADNS3080_MOTION_CLEAR          0x12	//W
#define ADNS3080_FRAME_CAPTURE         0x13	//RW
#define ADNS3080_SROM_ENABLE           0x14	//W
#define ADNS3080_FRAME_PERIOD_MAX_BOUND_LOWER      0x19		//RW
#define ADNS3080_FRAME_PERIOD_MAX_BOUND_UPPER      0x1a		//RW
#define ADNS3080_FRAME_PERIOD_MIN_BOUND_LOWER      0x1b		//RW
#define ADNS3080_FRAME_PERIOD_MIN_BOUND_UPPER      0x1c		//RW
#define ADNS3080_SHUTTER_MAX_BOUND_LOWER           0x1d		//RW
#define ADNS3080_SHUTTER_MAX_BOUND_UPPER           0x1e		//RW
#define ADNS3080_SROM_ID               0x1f	//R
#define ADNS3080_OBSERVATION           0x3d	//RW
#define ADNS3080_INVERSE_PRODUCT_ID    0x3f	//R
#define ADNS3080_PIXEL_BURST           0x40	//R
#define ADNS3080_MOTION_BURST          0x50	//R
#define ADNS3080_SROM_LOAD             0x60	//W



