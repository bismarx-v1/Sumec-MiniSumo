#include <Arduino.h>
#include <EEPROM.h>


//Function for saveing data

struct Data
{
    //save state
    uint16_t value;
    //time
    unsigned long miliseconds;
    unsigned long seconds;
    unsigned long minutes;
    //Line senzors
    bool lineL;
    bool lineR;
    //Distance senzors
    int distanceL;
    int distanceM;
    int distanceR;
};




class Black_box
{
    private:
        uint16_t previousParameter;
        Data *datasArray;

    public:
        unsigned long dataNumber = 0;
        Black_box();
        ~Black_box();
        void DataRecorder(uint16_t parameter, bool R_line, bool L_line, int L_distance, int M_distance, int R_distance);
        void DataPrint();
};


Black_box::Black_box()
{
    datasArray = (Data*)malloc(sizeof(Data)*dataNumber); 
    //EEPROM.begin(4096);
}

Black_box::~Black_box()
{
    // must be edited for all
   free(datasArray); 
}

void Black_box::DataRecorder(uint16_t parameter, bool R_line, bool L_line, int L_distance, int M_distance, int R_distance)
{
    if(parameter != previousParameter)
    {
        unsigned long actual_time = millis();

        dataNumber++;
        datasArray = (Data*)realloc(0, dataNumber*sizeof(Data));

        datasArray[dataNumber-1].value = parameter;
        datasArray[dataNumber-1].miliseconds = actual_time%1000;
        datasArray[dataNumber-1].seconds = (actual_time - datasArray[dataNumber-1].miliseconds)%60000;
        datasArray[dataNumber-1].minutes = (actual_time -(datasArray[dataNumber-1].miliseconds + datasArray[dataNumber-1].seconds))/60000;
        datasArray[dataNumber-1].lineL = L_line;
        datasArray[dataNumber-1].lineR = R_line;
        datasArray[dataNumber-1].distanceL = L_distance;
        datasArray[dataNumber-1].distanceM = M_distance;
        datasArray[dataNumber-1].distanceR = R_distance;


        previousParameter = parameter;
    }
}


void Black_box::DataPrint()
{
    Serial.println("miliseconds / seconds / minutes / Left_QRE / Right_QRE / Left_Luna / Middle_Luna / Right_Luna");
    Serial.println();

    for(unsigned long i = 0; i < dataNumber; i++)
    {
        Serial.printf("%lu ms  ", datasArray[i].miliseconds);
        Serial.printf("%lu s  ", datasArray[i].seconds);
        Serial.printf("%lu min  ", datasArray[i].minutes);
        Serial.printf("%d y/n  ", datasArray[i].lineL);
        Serial.printf("%d y/n  ", datasArray[i].lineR);
        Serial.printf("%d cm  ", datasArray[i].distanceL);
        Serial.printf("%d cm  ", datasArray[i].distanceM);
        Serial.printf("%d cm  ", datasArray[i].distanceR);
        Serial.println();
    }

    Serial.println("==============================================");
}





int adressRecords[4] {4, 5, 6, 7};
int freeRecorders = 7;
bool enableSaveing = 0;


void recordManaging(Black_box new_Record)
{


    EEPROM.put(freeRecorders, new_Record);

}


/*void saveRecord(Black_box saving_Record)
{

}*/