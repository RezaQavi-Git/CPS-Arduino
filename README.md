# CPS-Arduino
Simple Arduino project for CPS course University of Tehran

This project consist of two main part :
  - Main board : this part consist of one Arduino Uno board to control and  apply logic in circuit, recive data form TH board(explain later), and check conditions and compute signals to send back to TH board by Bluetooth.
  - TH board : this pard consist of one Arduino Uno to connect tempereture & humadity and send this in information by bluetooth to Main board, and after recive data(motor speed) run the motor.
  
 ##Parts
  - Main board :
    - One Arduino Uno
    - One bluetooth module
    - One LCD(LM041L) [to show information]
   
  - TH board :
    - One Atduino Uno
    - One bluetooth module
    - One DC-MOTOR
    - SHT25 (tempereture & humadity sensor)
