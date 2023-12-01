#define tlacitko 2
#define led 15


// programové proměné
const int LEDPin = 15;
TaskHandle_t Task1;
int LEDBlink = 0;
int Range = 40;  //sensor range setting
int hodnota_cary = 1000;  // určuje zdali je barva spíš bílá nebo černá
int laser_number;  // třídící proměná TF_lun
int start_control = 0;
