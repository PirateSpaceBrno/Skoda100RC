enum DrivingMotorMode {
  STOP,
  DOPREDU,
  DOZADU
};

void setupMotors();
void controlDrivingMotor();
void controlSteeringMotor(int angle);

extern DrivingMotorMode drivingMotorMode;
