/*
 * bmp.h
 *
 *  Created on: 2019年12月18日
 *      Author: SkingWei
 */

#ifndef SRC_BMP_H_
#define SRC_BMP_H_
#include    <intrinsics.h>
/*BMP*/
unsigned char logo_GEM[]={
/*--  调入了一幅图像：F:\20191217_MCU_course\参考数据\GEM2.bmp  --*/
/*--  宽度x高度=64x48  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0x7C,
0xBC,0xBC,0xBC,0xBC,0xBC,0xBC,0xBC,0xBC,0xBC,0xBC,0xBC,0xBC,0xBC,0xBC,0xBC,0xBC,
0xBC,0xBC,0xBC,0xBC,0xBC,0xBC,0xBC,0xBC,0xBC,0xBC,0xBC,0xBC,0xFC,0xFC,0xFC,0x3C,
0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0x7E,0xBF,0xDF,0xEF,0xF7,0xFB,0xBD,0x9E,0x8F,
0x87,0x03,0x01,0x01,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,
0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x83,0x83,0x03,0x03,0x03,0x81,0x80,
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,
0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7E,0xFD,0xFB,0xF7,0xEF,0xDF,0xBD,0x79,0xF1,
0xE1,0xC1,0x80,0x00,0x00,0x07,0x1F,0x7F,0xFD,0xE1,0xC1,0x01,0x01,0x01,0xFF,0xFF,
0xFF,0x01,0x01,0x01,0x81,0xE1,0xF9,0x7F,0x1F,0x07,0x01,0x00,0x80,0xC3,0xE3,0xF3,
0xFB,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,0x1F,0x0F,0x07,0x03,0x01,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7E,
0xFD,0xFB,0xF7,0xEF,0xDE,0xBC,0x78,0xF0,0xE1,0xC3,0x87,0x00,0x00,0x00,0xFF,0xFF,
0xFF,0x00,0x00,0x00,0x07,0x87,0xE1,0xF0,0xF8,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0x7F,
0x3F,0x1F,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7E,0xFD,0xFB,0xF7,0xFF,0xDE,0xFC,0xF9,0xF1,
0xF9,0xFC,0xFC,0xFE,0xFF,0xFF,0xFF,0x7F,0x3F,0x1F,0x0F,0x07,0x03,0x01,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x3F,
0x3F,0x1F,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00

};


#endif /* SRC_BMP_H_ */
