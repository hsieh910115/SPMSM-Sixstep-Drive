/*
 1101_AC & DC DRIVERS
 proj.MID Sixstep01 IOver
 input_
 GPIO6_pin80_MOTOR YELLOW LINE
 GPIO7_pin79_MOTOR ?????? LINE
 GPIO8_pin78_MOTOR ?????? LINE

 output_
 GPIO0_pin40_U+
 GPIO1_pin39_U-
 GPIO2_pin38_V+
 GPIO3_pin37_V-
 GPIO4_pin36_W+
 GPIO5_pin35_W-

 GPIO34_TEST
 GPIO31_TEST
*/

#include "F28x_Project.h"

// 全域變數
int state;         // 記錄當前的驅動狀態
int direction = 1; // 1 表示順時針 (CW)，0 表示逆時針 (CCW)
int prev_direction = 1; // 記錄上一次的方向
int brake=0;

void brake_motor(void)
{
    // 啟動煞車邏輯
    GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
    GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;
    GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
    GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
    GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;
    GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;

    DELAY_US(500000); // 延遲 500ms 讓馬達停止
}

void main(void)
{
   InitSysCtrl();
   DINT;
   InitPieCtrl();
   IER = 0x0000;
   IFR = 0x0000;
   InitPieVectTable();

   EALLOW;
   // 初始化霍爾訊號輸入 (GPIO6, GPIO7, GPIO8)
   GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;
   GpioCtrlRegs.GPAGMUX1.bit.GPIO6 = 0;
   GpioCtrlRegs.GPAQSEL1.bit.GPIO6 = 0;
   GpioCtrlRegs.GPADIR.bit.GPIO6 = 0;

   GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;
   GpioCtrlRegs.GPAGMUX1.bit.GPIO7 = 0;
   GpioCtrlRegs.GPAQSEL1.bit.GPIO7 = 0;
   GpioCtrlRegs.GPADIR.bit.GPIO7 = 0;

   GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;
   GpioCtrlRegs.GPAGMUX1.bit.GPIO8 = 0;
   GpioCtrlRegs.GPAQSEL1.bit.GPIO8 = 0;
   GpioCtrlRegs.GPADIR.bit.GPIO8 = 0;

   // 初始化輸出 (GPIO0 ~ GPIO5)
   GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;
   GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;
   GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;

   GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;
   GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;
   GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;

   GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;
   GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;
   GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;

   GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;
   GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;
   GpioCtrlRegs.GPADIR.bit.GPIO3 = 1;

   GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;
   GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0;
   GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;

   GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;
   GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;
   GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;

   // 初始化測試 LED (GPIO31, GPIO34)
   GpioCtrlRegs.GPBPUD.bit.GPIO34 = 0;
   GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;
   GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;

   GpioCtrlRegs.GPAPUD.bit.GPIO31 = 0;
   GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0;
   GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;
   GpioDataRegs.GPASET.bit.GPIO31 = 1;
   GpioDataRegs.GPBSET.bit.GPIO34 = 1;
   EDIS;

   for (;;)
   {
       EALLOW;

       // 檢查煞車狀態
       if (brake == 1)
       {
           brake_motor(); // 呼叫煞車函數
       }
       else if (brake == 0)
       {
           // 馬達正常運行邏輯
           if (prev_direction != direction)
           {
               brake_motor(); // 觸發煞車
               prev_direction = direction; // 更新方向變數
           }

           if (direction == 1)
           {
               // 順時針 (CW) 的馬達控制邏輯
               if (GpioDataRegs.GPADAT.bit.GPIO6 == 0 && GpioDataRegs.GPADAT.bit.GPIO7 == 0 && GpioDataRegs.GPADAT.bit.GPIO8 == 1)
               {
                   GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
                   GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;
                   GpioDataRegs.GPASET.bit.GPIO2 = 1; // V+
                   GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
                   GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;
                   GpioDataRegs.GPASET.bit.GPIO5 = 1; // W-
                   state = 1;
               }
               else if (GpioDataRegs.GPADAT.bit.GPIO6 == 0 && GpioDataRegs.GPADAT.bit.GPIO7 == 1 && GpioDataRegs.GPADAT.bit.GPIO8 == 1)
               {
                   GpioDataRegs.GPASET.bit.GPIO0 = 1; // U+
                   GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;
                   GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
                   GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
                   GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;
                   GpioDataRegs.GPASET.bit.GPIO5 = 1; // W-
                   state = 2;
               }
               else if (GpioDataRegs.GPADAT.bit.GPIO6 == 0 && GpioDataRegs.GPADAT.bit.GPIO7 == 1 && GpioDataRegs.GPADAT.bit.GPIO8 == 0)
               {
                   GpioDataRegs.GPASET.bit.GPIO0 = 1; // U+
                   GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;
                   GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
                   GpioDataRegs.GPASET.bit.GPIO3 = 1; // V-
                   GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;
                   GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;
                   state = 3;
               }
               else if (GpioDataRegs.GPADAT.bit.GPIO6 == 1 && GpioDataRegs.GPADAT.bit.GPIO7 == 1 && GpioDataRegs.GPADAT.bit.GPIO8 == 0)
               {
                   GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
                   GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;
                   GpioDataRegs.GPASET.bit.GPIO3 = 1; // V-
                   GpioDataRegs.GPASET.bit.GPIO4 = 1; // W+
                   GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;
                   state = 4;
               }
               else if (GpioDataRegs.GPADAT.bit.GPIO6 == 1 && GpioDataRegs.GPADAT.bit.GPIO7 == 0 && GpioDataRegs.GPADAT.bit.GPIO8 == 0)
               {
                   GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
                   GpioDataRegs.GPASET.bit.GPIO1 = 1; // U-
                   GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
                   GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
                   GpioDataRegs.GPASET.bit.GPIO4 = 1; // W+
                   state = 5;
               }
               else if (GpioDataRegs.GPADAT.bit.GPIO6 == 1 && GpioDataRegs.GPADAT.bit.GPIO7 == 0 && GpioDataRegs.GPADAT.bit.GPIO8 == 1)
               {
                   GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
                   GpioDataRegs.GPASET.bit.GPIO1 = 1; // U-
                   GpioDataRegs.GPASET.bit.GPIO2 = 1; // V+
                   GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
                   GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;
                   GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;
                   state = 6;
               }
           }
           else
           {
               // 逆時針 (CCW) 的馬達控制邏輯
               if (GpioDataRegs.GPADAT.bit.GPIO6 == 0 && GpioDataRegs.GPADAT.bit.GPIO7 == 0 && GpioDataRegs.GPADAT.bit.GPIO8 == 1)
               {
                   GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
                   GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;
                   GpioDataRegs.GPASET.bit.GPIO3 = 1; // V-
                   GpioDataRegs.GPASET.bit.GPIO4 = 1; // W+
                   GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;
                   state = 4;
               }
               else if (GpioDataRegs.GPADAT.bit.GPIO6 == 0 && GpioDataRegs.GPADAT.bit.GPIO7 == 1 && GpioDataRegs.GPADAT.bit.GPIO8 == 1)
               {
                   GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
                   GpioDataRegs.GPASET.bit.GPIO1 = 1; // U-
                   GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
                   GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
                   GpioDataRegs.GPASET.bit.GPIO4 = 1; // W+
                   state = 5;
               }
               else if (GpioDataRegs.GPADAT.bit.GPIO6 == 0 && GpioDataRegs.GPADAT.bit.GPIO7 == 1 && GpioDataRegs.GPADAT.bit.GPIO8 == 0)
               {
                   GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
                   GpioDataRegs.GPASET.bit.GPIO1 = 1; // U-
                   GpioDataRegs.GPASET.bit.GPIO2 = 1; // V+
                   GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
                   GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;
                   GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;
                   state = 6;
               }
               else if (GpioDataRegs.GPADAT.bit.GPIO6 == 1 && GpioDataRegs.GPADAT.bit.GPIO7 == 1 && GpioDataRegs.GPADAT.bit.GPIO8 == 0)
               {
                   GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
                   GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;
                   GpioDataRegs.GPASET.bit.GPIO2 = 1; // V+
                   GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
                   GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;
                   GpioDataRegs.GPASET.bit.GPIO5 = 1; // W-
                   state = 1;
               }
               else if (GpioDataRegs.GPADAT.bit.GPIO6 == 1 && GpioDataRegs.GPADAT.bit.GPIO7 == 0 && GpioDataRegs.GPADAT.bit.GPIO8 == 0)
               {
                   GpioDataRegs.GPASET.bit.GPIO0 = 1; // U+
                   GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;
                   GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
                   GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
                   GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;
                   GpioDataRegs.GPASET.bit.GPIO5 = 1; // W-
                   state = 2;
               }
               else if (GpioDataRegs.GPADAT.bit.GPIO6 == 1 && GpioDataRegs.GPADAT.bit.GPIO7 == 0 && GpioDataRegs.GPADAT.bit.GPIO8 == 1)
               {
                   GpioDataRegs.GPASET.bit.GPIO0 = 1; // U+
                   GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;
                   GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
                   GpioDataRegs.GPASET.bit.GPIO3 = 1; // V-
                   GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;
                   GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;
                   state = 3;
               }
           }
       }

       EDIS;
   }
}
