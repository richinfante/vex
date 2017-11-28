/*
 LCD Screen Routines
 Copyright 2014 Vexy^2 Masuk Robotics. All Rights Reserved.

  _     ____ ____    ____                           
 | |   / ___|  _ \  / ___|  ___ _ __ ___  ___ _ __  
 | |  | |   | | | | \___ \ / __| '__/ _ \/ _ \ '_ \ 
 | |__| |___| |_| |  ___) | (__| | |  __/  __/ | | |
 |_____\____|____/  |____/ \___|_|  \___|\___|_| |_|

 */

bool isLCDDirty = true;

void clearLCD(){
    clearLCDLine(0);     
    clearLCDLine(1);
    bLCDBacklight = false;
    isLCDDirty = false;
}

void displayBatteryStatus(){
    bLCDBacklight = true;

    string mainBattery,backupBattery;
    float powerExpander = SensorValue[in1] / 275;

    //Display the Primary Robot battery voltage
    displayLCDString(0, 0, "Batt: ");
    
    float batteryLevelVolts = nImmediateBatteryLevel / 1000.0;
    //float batteryLevel = batteryLevelVolts / 7.2;
    //int mainPercent = (batteryLevel * 100);
    
    float expanderLevelVolts = powerExpander;
    //float expanderLevel = expanderLevelVolts / 7.2;
    //int powerExpanderPercent = (expanderLevel * 100);
    
    float backupBatteryLevelVolts = BackupBatteryLevel/1000.0;
   // float backupBatteryLevel = backupBatteryLevelVolts / 9;
    //int backupBatteryPercent  = (backupBatteryLevel * 100);
    
    string mainStatus = "GOOD";
    string backupStatus = "GOOD";
    string expanderStatus = " GOOD";
    
    if(batteryLevelVolts<6.5){
        mainStatus = "BAD";
    }
    
    if(expanderLevelVolts<6.5) {
        expanderStatus = " BAD";
    }
    
    if(backupBatteryLevelVolts<8.7) {
        backupStatus = "BAD";
    }
    
    //sprintf(mainBattery, "%d%c ,%d%c",mainPercent,'%', powerExpanderPercent, '%'); //Build the value to be displayed
   mainBattery = mainStatus + expanderStatus;
    
    // sprintf(mainBattery, "%d , %d",mainStatus, expanderStatus); //Build the value to be displayed
    displayNextLCDString(mainBattery);
        
    //Display the Backup battery voltage
    displayLCDString(1, 0, "Backup: ");
    //  sprintf(backupBattery, "%d%c", backupBatteryPercent, '%');    //Build the value to be displayed
    backupBattery = backupStatus;
    displayNextLCDString(backupBattery); 
    
    isLCDDirty = true;
}


