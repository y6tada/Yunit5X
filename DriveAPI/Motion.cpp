#include "Motion.hpp"

Motion::Motion()
{
    
}

void Motion::setSpeed(float speed) {
    m_speed = speed;
}

void Motion::setOfset(int8_t ofset) {
    m_ofset = ofset;
}

void Motion::ballTracking(vector_xy *move) {
    // ボールを検出
    if(ball.getRange() > 0) {
        float ballRawDegree = (float)motion.getBallTrackDegree(15);
        int   ballTrackDegree = smaBallDeg.addValue(ballRawDegree);
        *move = makeXYFromRT(m_speed, ballTrackDegree);
        
        // 自動ドリブルを有効化
        drive.enableAutoDrible(2, 3);
        
        // ホールドセンサ処理
        if (ball.getHold() > 0) {
            drive.RunDribbler(400);
            if(move->y > 0) move->y *= m_forwardRation;
            if (quadping.getXDifferential() >  15) { move->x =  0.3; }
            if (quadping.getXDifferential() < -15) { move->x = -0.3; }
//            imu.setOfset(m_ofset);
            
            // キッカー制御
            m_holdCount += ball.getHold();
            if (m_holdCount > m_holdCountLimit) {
                drive.kick_R();
                drive.kick_L();
                m_holdCount = 0;
            }
        }
        else {
            m_ofset = 0;
        }
    }
    // ボールを非検出
    else {
        move->x = 0;
        move->y = 0;
        backOwnGoal(move, 15, 15);
        drive.disableAutoDrible();
    }
}

int Motion::getBallTrackDegree(uint16_t back_limit) {
    int rslt;
    if(quadping.getB() < back_limit) {
        // ゴール前
        switch (abs(ball.getDir())) {
            case 0: rslt = 0;   break;
            case 1: rslt = 40;  break;
            case 2: rslt = 60;  break;
            case 3: rslt = 90;  break;
            case 4: rslt = 90;  break;
            case 5: rslt = 90;  break;
            case 6: rslt = 90;  break;
            case 7: rslt = 90;  break;
            case 8: rslt = 90;  break;
            default:            break;
        }
    }
    else {
        if (ball.getRange() > 4) {
            // 近距離
            switch (abs(ball.getDir())) {
                case 0: rslt = 0;    break;
                case 1: rslt = 45;   break;
                case 2: rslt = 90;   break;
                case 3: rslt = 110;  break;
                case 4: rslt = 130;  break;
                case 5: rslt = 150;  break;
                case 6: rslt = 170;  break;
                case 7: rslt = -170; break;
                case 8: rslt = -150; break;
            }
        }
        else if(ball.getRange() > 2) {
            // 中距離
            switch (abs(ball.getDir())) {
                case 0: rslt = 0;    break;
                case 1: rslt = 40;   break;
                case 2: rslt = 70;   break;
                case 3: rslt = 100;  break;
                case 4: rslt = 120;  break;
                case 5: rslt = 140;  break;
                case 6: rslt = 160;  break;
                case 7: rslt = 180;  break;
                case 8: rslt = -160; break;
            }
        }
        else {
            // 遠距離
            switch (abs(ball.getDir())) {
                case 0: rslt = 0;  break;
                case 1: rslt = 30;  break;
                case 2: rslt = 50;  break;
                case 3: rslt = 70;  break;
                case 4: rslt = 90;  break;
                case 5: rslt = 110;  break;
                case 6: rslt = 130;  break;
                case 7: rslt = 150;  break;
                case 8: rslt = 170;  break;
            }
        }
    }
    return (ball.getDir() > 0) ? rslt : -rslt;
}

void Motion::backOwnGoal(vector_xy *move, int x_margin, int y_margin) {
    
    if(abs(quadping.getXDifferential()) > x_margin || abs(quadping.getYDifferential() > y_margin)) {
        move->x = (double)quadping.getXDifferential() / 60.0;
        move->y = ((double)quadping.getB() - 40.0) / -90.0;
    }
    else {
        move->x = 0;
        move->y = 0;
    }
}

void Motion::wallBreak(vector_xy *move) {
    if (move->y > 0 && quadping.getF() < 20) {
        move->y *= 0.65;
    }
    if (move->y < 0 && quadping.getB() < 20) {
        move->y *= 0.65;
    }
    
    if (move->x > 0 && quadping.getR() < 50) {
        move->x *= 0.65;
    }
    if (move->x < 0 && quadping.getL() < 50) {
        move->x *= 0.65;
    }
}

