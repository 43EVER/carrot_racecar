#ifndef  __MYDATA_H__
#define   __MYDATA_H__

#include "common.h"

typedef struct{
  char *buf;                   //ָ����������ָ��
  uint16 length;               //���ݴ�С
  uint16 head;                 //ͷ��ָ�룬ʵ�ʲ�����ָ�����ͣ�����һ�����
  uint16 tail;                 //β��ָ�룬ʵ�ʲ�����ָ�����ͣ�����һ�����
  int fill_cnt;                //���м���
}RINGBUF;

int RINGBUF_Init(RINGBUF* r, char array[], size_t len);//��ʼ������
int RINGBUF_Put(RINGBUF* r, char data);//������
int RINGBUF_Get(RINGBUF* r, char *c, unsigned int length);//ȡ����


#endif