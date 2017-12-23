#include "Drive.hpp"

Drive::Drive()
:esc(ESC_PIN)
,kicker_R_disableTimeout()
,kicker_L_disableTimeout()
,kicker_R_readyTimeout()
,kicker_L_readyTimeout()
,kicker_R(KICKER_R_PIN)
,kicker_L(KICKER_L_PIN)
,motor(25)
{
	esc.period_ms(20);
    esc.pulsewidth(1000);
}

/* ========== Dribller control function ========== */
void Drive::RunDribbler(int pwr_0_to_1000) {
    esc.pulsewidth_us(1000 + min(pwr_0_to_1000, 1000));
}

void Drive::enableAutoDrible(int dir, int range) {
    if (abs(ball.getDir()) < dir && ball.getRange() > range) {
        RunDribbler(300);
    }
    else {
        RunDribbler(50);
    }
}

void Drive::disableAutoDrible() {
    RunDribbler(0);
}

/* ========== Kicker drive functions ========== */
void Drive::kick_R(void) {
    if (kicker_R_isReady) {
        kicker_R = 1;
        kicker_R_disableTimeout.attach_us(mbed::callback(this, &Drive::kicker_R_Flip), 20000);
        
        kicker_R_isReady = 0;
        kicker_R_readyTimeout.attach(mbed::callback(this, &Drive::kicker_R_Ready), kick_nextReady_delay);
    }
}

void Drive::kick_L(void) {
    if (kicker_L_isReady) {
        kicker_L = 1;
        kicker_L_disableTimeout.attach_us(mbed::callback(this, &Drive::kicker_L_Flip), 20000);
        
        kicker_L_isReady = 0;
        kicker_L_readyTimeout.attach(mbed::callback(this, &Drive::kicker_L_Ready), kick_nextReady_delay);
    }
}

/* ========== Motor control functions ========== */
void Drive::enable_all_motors(void) {
    motor.all_enable();
}

void Drive::disable_all_motors(void) {
    motor.all_disable();
}

/* ========== Robot movement control functions ========== */
float Drive::deg2rad(int deg1, int deg2) {
    return (float)(deg1 + deg2) * M_PI / 180.0;
}

void Drive::movePolar(float pwr, int degree, float turn) {
	motor.setRF( pwr * cos(deg2rad(-45 , degree)) + turn);
	motor.setRB( pwr * cos(deg2rad( 45 , degree)) + turn);
	motor.setLB( pwr * cos(deg2rad( 135, degree)) + turn);
	motor.setLF( pwr * cos(deg2rad(-135, degree)) + turn);
}

void Drive::moveComp(float VecX, float VecY, float turn) {
    _x = smaMoveX.addValue(VecX);
    _y = smaMoveY.addValue(VecY);
	motor.setRF(_x * -0.707 + _y *  0.707 + turn);
	motor.setLF(_x * -0.707 + _y * -0.707 + turn);
	motor.setLB(_y * -0.707 + _x *  0.707 + turn);
	motor.setRB(_y *  0.707 + _x *  0.707 + turn);
}

void Drive::moveVector(vector_xy *vec) {
    _x = smaMoveX.addValue(vec->x);
    _y = smaMoveY.addValue(vec->y);
    motor.setRF(_x * -0.707 + _y *  0.707 + vec->r);
    motor.setLF(_x * -0.707 + _y * -0.707 + vec->r);
    motor.setLB(_y * -0.707 + _x *  0.707 + vec->r);
    motor.setRB(_y *  0.707 + _x *  0.707 + vec->r);
}

void Drive::getLatestVecXY(float *x, float *y) {
    *x = _x;
    *y = _y;
}
