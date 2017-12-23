#include "BoundCtrl.hpp"

BoundCtrl::BoundCtrl()
{
    
}

void BoundCtrl::set(vector_xy *move) {
    
    if (line.OR) {
        
        LineAllCnt++;
        
        if(LineAllCnt < 10) {
            /*
             一定時間内でのライン処理
             反応した方向への逆移動
             最初の積分領域の設定
             */
            
            if (line.FL || line.FC || line.FR) {
                if(inLineArea_F < margin) inLineArea_F = margin;
                if(move->y > 0) {
                    move->y = -0.8;
                    move->x = 0;
                }
            }
            
            if (line.BL || line.BC || line.BR) {
                if(inLineArea_B < margin) inLineArea_B = margin;
                if(move->y < 0) {
                    move->y = 0.8;
                    move->x = 0;
                }
            }
            
            if (line.RF || line.RC || line.RB) {
                if(inLineArea_R < margin) inLineArea_R = margin;
                if(move->x > 0) {
                    move->x = -0.8;
                    move->y = 0;
                }
            }
            
            if (line.LF || line.LC || line.LB) {
                if(inLineArea_L < margin) inLineArea_L = margin;
                if(move->x < 0) {
                    move->x = 0.8;
                    move->y = 0;
                }
            }
        }
        else if(LineAllCnt < 150) {
            /*	積分領域の残った方向に移動 */
            if(inLineArea_F > 0) {
                move->y = -0.75;
                move->x = 0.00;
            }
            if(inLineArea_B > 0) {
                move->y = 0.75;
                move->x = 0.00;
            }
            if(inLineArea_R > 0) {
                move->x = -0.75;
                move->y = 0.00;
            }
            if(inLineArea_L > 0) {
                move->x = 0.75;
                move->y = 0.00;
            }
        }
        else {
            if(inLineArea_F > 0) {
                if (quadping.getXDiameter() > xMinDiameter) {
                    if (quadping.getXDifferential() > xMinDifferential) {
                        move->x = -0.45;
                        move->y = -0.65;
                    }
                    else if(quadping.getXDifferential() < xMinDifferential * -1) {
                        move->x =  0.45;
                        move->y = -0.65;
                    }
                    else {
                        move->x =  0.00;
                        move->y = -1.25;
                    }
                }
                else {
                    move->x =  0.00;
                    move->y = -0.55;
                }
            }
            
            if(inLineArea_B > 0) {
                if (quadping.getXDiameter() > xMinDiameter) {
                    if (quadping.getXDifferential() > xMinDifferential) {
                        move->x = -0.45;
                        move->y =  0.65;
                    }
                    else if(quadping.getXDifferential() < xMinDifferential * -1) {
                        move->x =  0.45;
                        move->y =  0.55;
                    }
                    else {
                        move->x =  0.00;
                        move->y =  1.25;
                    }
                }
                else {
                    move->x =  0.00;
                    move->y =  0.55;
                }
            }

            if(inLineArea_R > 0) {
                if (quadping.getYDiameter() > yMinDiameter) {
                    if (quadping.getYDifferential() > yMinDifferential) {
                        move->x = -0.45;
                        move->y = -0.65;
                    }
                    else if(quadping.getYDifferential() < yMinDifferential * -1) {
                        move->x = -0.45;
                        move->y =  0.65;
                    }
                    else {
                        move->x = -1.25;
                        move->y =  0.00;
                    }
                }
                else {
                    move->x =  0.00;
                    move->y =  0.00;
                }
            }
            
            if(inLineArea_L > 0) {
                if (quadping.getYDiameter() > yMinDiameter) {
                    if (quadping.getYDifferential() > yMinDifferential) {
                        move->x =  0.45;
                        move->y = -0.65;
                    }
                    else if(quadping.getYDifferential() < yMinDifferential * -1) {
                        move->x =  0.45;
                        move->y =  0.65;
                    }
                    else {
                        move->x =  1.25;
                        move->y =  0.00;
                    }
                }
                else {
                    move->x =  0.00;
                    move->y =  0.00;
                }
            }
        }

    }
    else {	//ラインを検出しない
        LineAllCnt = 0;
        
        /*  keepOut領域から無条件に抜け出す  */
        /*	領域を抜けるまではライン方向への移動をキャンセル */
        if(inLineArea_F > 0) {
            if (inLineArea_F > keepOut) {
                move->y = -0.45;
            }
            else if (move->y > 0) {
                move->y = 0;
            }
        }
        if(inLineArea_B > 0) {
            if (inLineArea_B > keepOut) {
                move->y = 0.45;
            }
            else if (move->y < 0) {
                move->y = 0;
            }
        }
        if(inLineArea_R > 0) {
            if (inLineArea_R > keepOut) {
                move->x = -0.45;
            }
            else if (move->x > 0) {
                move->x = 0;
            }
        }
        if(inLineArea_L > 0) {
            if (inLineArea_L > keepOut) {
                move->x = 0.45;
            }
            else if (move->x < 0) {
                move->x = 0;
            }
        }
        
        /*	積分領域をホイールオドメトリによって減算 */
        if(move->y < 0) {
            inLineArea_F += move->y * odmetryRatio;
        }
        if(move->y > 0) {
            inLineArea_B -= move->y * odmetryRatio;
        }
        if(move->x < 0) {
            inLineArea_R += move->x * odmetryRatio;
        }
        if(move->x > 0) {
            inLineArea_L -= move->x * odmetryRatio;
        }
        
        if (ball.getRange() < 3) {
            inLineArea_F = 0;
            inLineArea_B = 0;
            inLineArea_R = 0;
            inLineArea_L = 0;
        }
        
        if(inLineArea_L < 0) inLineArea_L = 0;
        if(inLineArea_R < 0) inLineArea_R = 0;
        if(inLineArea_F < 0) inLineArea_F = 0;
        if(inLineArea_B < 0) inLineArea_B = 0;
    }
    
    /*	現在ラインを検出中であるか否かに依存しない処理
    pc.printf("F:%d\tB:%d\tR:%d\tL:%d\n",
        (int)inLineArea_F,
        (int)inLineArea_B,
        (int)inLineArea_R,
        (int)inLineArea_L
    );
    */
}
