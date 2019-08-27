#include "mydata.h"

int RINGBUF_Init(RINGBUF* r, char array[], size_t len)
{
    if (len <2 || array==NULL){
        return 0;
    }

    r->buf = array;
    r->length = len;
    r->fill_cnt = 0;
    r->head = r->tail = 0;
    return 1;
}

int RINGBUF_Put(RINGBUF* r, char data)
{
    //��tail+1����headʱ��˵����������
    if (r->fill_cnt >= r->length) {
       // printf("BUF FULL!\n");
        return 0;                  // ������������ˣ��򷵻ش���
    }
    else
    {
      r->buf[r->tail] = data;
      r->tail++;
      r->fill_cnt++;
      //����tail�Ƿ񳬳����鷶Χ������������Զ��л���0
      r->tail = r->tail % r->length;
      return 1;
    }
}

int RINGBUF_Get(RINGBUF* r, char *c, unsigned int length)
{
    //��tail����headʱ��˵�����п�
    if (r->fill_cnt<=0) {
     //   printf("BUF EMPTY!\n");
        return 0;
    }

    //���ֻ�ܶ�ȡr->length��������
    if (length > r->length) {
        length = r->length;
    }

    for (int i = 0; i<length; i++)
    {
        r->fill_cnt--;
        *c = r->buf[r->head++];                 // �������ݸ�*c
        *c++;
        //����head�ԼӺ���±��Ƿ񳬳����鷶Χ������������Զ��л���0
        r->head = r->head % r->length;
    }
    return 1;
}