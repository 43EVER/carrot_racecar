#ifndef __CAR_KEY_H__
#define __CAR_KEY_H__

#include "common.h"
#include "include.h"

//����״̬���İ���ɨ�����
typedef enum
{
  keystate0,  //�ް������µ�״̬�������ɿ���״̬
  keystate1,  //�а�������
  keystate2, // �Ӱ�������һֱ�����������������µ�״̬
  keystate3, // �������µ�״̬
}KEYSTATE;

KEY_STATUS_e key_statecheck(KEY_e key);
KEY_STATUS_e key_Timecheck(KEY_e key);
void Key_init_all();
KEY_e Key_scan();

//enum key_scan();

#endif