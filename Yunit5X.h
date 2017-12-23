#ifndef Yunit5X_h
#define Yunit5X_h

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))

/* ========== Ultrasonic-sensor control parameters ========== */
#define SEND_SONIC_PERIOD   50000

/* ========== Motor driver control parameters ========== */
#define MOTOR_PWM_PERIOD            50
#define MOTOR_PWM_PERIOD_LAP_MODE   20

/* ========== On-board led pins ========== */
#define LED1_PIN        PC_13
#define LED2_PIN        PC_14
#define LED3_PIN        PC_15

/* ========== DigitalInOut control pins for Ultrasonic sensors ========== */
#define USD_F_PIN       PA_6
#define USD_B_PIN       PC_1
#define USD_R_PIN       PA_7
#define USD_L_PIN       PC_3

/* ========== UART data input from IMU ========== */
#define IMU_TX_PIN      PC_6
#define IMU_RX_PIN      PC_7
#define IMU_NUM_OF_SMA  5
#define IMU_BAUD        115200

/* ========== UART data input from Ball-sensor ========== */
#define BALL_TX_PIN     PA_9
#define BALL_RX_PIN     PA_10
#define BALL_BAUD       115200

/* ========== UART data input from Line-sensor and UI MCU ========== */
#define TEENSY_TX_PIN   PC_10
#define TEENSY_RX_PIN   PC_11
#define TEENSY_BAUD     460800

/* ========== Pixy sensor UART input pins ========== */
#define PIXY_TX_PIN     PC_12
#define PIXY_RX_PIN     PD_2
#define PIXY_BAUD       115200
/* ========== Pixy camera signature number ========== */
#define PIXY_BALL_SIGN          1
#define PIXY_YELLOW_GOAL_SIGN   2
#define PIXY_BLUE_GOAL_SIGN     3

/* ========== Kicker control pins ========== */
#define KICKER_R_PIN    PB_12
#define KICKER_L_PIN    PA_11
#define HOLD_SENSOR_PIN PB_4

/* ========== Dribller control pins ========== */
#define ESC_PIN         PA_0

/* ========== Motor driver control pins ========== */
#define M1D_PIN         PB_0    // PWM 1/2N
#define M2D_PIN         PB_1    // PWM 1/3N
#define M3D_PIN         PB_6    // PWM 4/1
#define M4D_PIN         PB_7    // PWM 4/2

#define M1P_PIN         PB_13
#define M2P_PIN         PB_14
#define M3P_PIN         PB_15
#define M4P_PIN         PC_8

/* ========== Battery reference input pin ========== */
#define BATTREF_PIN     PA_4

/* ========== Toggle switches input from UI ========== */
#define SW_LEFT_PIN     PB_9
#define SW_RIGHT_PIN    PB_8

/* ========= Serial debug ========== */
#define PC_BAUD         115200

#endif /* Yunit5X_h */
