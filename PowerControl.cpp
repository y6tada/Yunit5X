#include "PowerControl.hpp"

PowerControl::PowerControl():battref(BATTREF_PIN) {
    
}

void PowerControl::setUnderVoltageLimit(float underVoltage) {
    underVoltageLimit = underVoltage;
}

float PowerControl::getLimitVoltage() {
    return underVoltageLimit;
}

float PowerControl::getNowVoltage() {
    return battref * 19.928;
}

float PowerControl::getSpeedRatioFromBattery(float target_voltage) {
    return smaPowerControl.addValue(target_voltage / getNowVoltage());
}
