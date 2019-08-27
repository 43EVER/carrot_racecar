#include<math.h>
#define PMAX			100
#define PMIN			-100
#define DMAX			100
#define DMIN			-100
#define FMAX			100	 //���ʾ���			 
double	Fuzzy_kp(int  e, int ec);	//ģ�����㺯��
double	Fuzzy_kd(int  e, int ec);	//ģ�����㺯��

/*******************************************************************************
*Description    :ģ���㷨
*
*modification   ��
*DATA           : 2017-5-29   By: handongdong
*******************************************************************************/
double	Fuzzy_kp(int  e, int ec)	//ģ�����㺯��
{
  /*�����˵������ӵĹ���������ʱƫ����С���ʱƫ����仯*/
/* a0=0.3 ,a1=0.55 ,a2=0.74 ,a3=0.89 */
  int rule[7][7] = {
//���ı仯��NB NM NS Z PS PM PB
    { 6,5,5,5,5,4,4 },			//NB
    { 5,4,3,3,2,1,1 },			//NM
    { 2,2,1,1,1,1,1 },			//NS
    { 2,1,0,0,0,1,2 },			//Z
    { 1,1,1,1,1,2,2 },			//PS
    { 1,1,2,3,3,4,5 },			//PM
    { 4,4,5,5,5,5,6 } };		//PB
  int Pn = 0, Dn = 0;
  int Un[4] = { 0 };
  int Pf[2] = { 0 }, Df[2] = { 0 }, Uf[4] = {0};
  double KP;
  int temp1, temp2;
  int	eRule[7] = { -180,-110,-50,0,50,110,180 };  //ƫ�������
  int	ecRule[7] = { -12,-8,-4,0,4,8,12 };  //ƫ��仯�ʵ�����
  int	KP_Rule[7] = { 0,10,20,30,40,50,60 }; //KP������
  
  if (e > eRule[0] && e < eRule[6])  //���ƫ���ڷ�Χ��
  {
    if (e <= eRule[1])  //���ƫ��  < -150
    {
      Pn = 0;
      //�����Ǿ��� -230 �������ȡ���Խ��������Խ��
      Pf[0] = FMAX * ((float)(eRule[1] - e) / (eRule[1] - eRule[0])); //�����������Ŀ϶�Ҫ������
    }
    else if (e <= eRule[2])  //ƫ��С�� -70
    {
      Pn = 1;
      //�����Ǿ��� -150 �������ȡ���Խ��������Խ��
      Pf[0] = FMAX * ((float)(eRule[2] - e) / (eRule[2] - eRule[1])); //�����������Ŀ϶�Ҫ������
    }
    else if (e <= eRule[3])  //ƫ��С�� 0
    {
      Pn = 2;
      //�����Ǿ��� -70 �������ȡ���Խ��������Խ��
      Pf[0] = FMAX * ((float)(eRule[3] - e) / (eRule[3] - eRule[2])); //�����������Ŀ϶�Ҫ������
    }
    else if (e <= eRule[4]) //ƫ��С�� 70
    {
      Pn = 3;
      //�����Ǿ��� 0 �������ȡ���Խ��������Խ��
      Pf[0] = FMAX * ((float)(eRule[4] - e) / (eRule[4] - eRule[3])); //�����������Ŀ϶�Ҫ������
    }
    else if (e <= eRule[5]) //ƫ��С�� 150
    {
      Pn = 4;
      //�����Ǿ��� 70 �������ȡ���Խ��������Խ��
      Pf[0] = FMAX * ((float)(eRule[5] - e) / (eRule[5] - eRule[4])); //�����������Ŀ϶�Ҫ������
    }
    else if (e <= eRule[6]) //ƫ��С�� 230
    {
      Pn = 5;
      //�����Ǿ��� 150 �������ȡ���Խ��������Խ��
      Pf[0] = FMAX * ((float)(eRule[6] - e) / (eRule[6] - eRule[5])); //�����������Ŀ϶�Ҫ������
    }
  }
  else if (e <= eRule[0]) //ƫ��С�� -230
  {
    Pn = 0;
    Pf[0] = FMAX;
  }
  else if (e >= eRule[5]) //ƫ�����230
  {
    Pn = 5;
    Pf[0] = 0;
  }
  
  Pf[1] = FMAX - Pf[0];
  
  
  if (ec > ecRule[0] && ec < ecRule[6])  //���ƫ���ڷ�Χ��
  {
    if (ec <= ecRule[1])  //���ƫ��  < -150
    {
      Dn = 0;
      //�����Ǿ��� -230 �������ȡ���Խ��������Խ��
      Df[0] = FMAX * ((float)(ecRule[1] - ec) / (ecRule[1] - ecRule[0])); //�����������Ŀ϶�Ҫ������
    }
    else if (ec <= ecRule[2])  //ƫ��С�� -70
    {
      Dn = 1;
      //�����Ǿ��� -150 �������ȡ���Խ��������Խ��
      Df[0] = FMAX * ((float)(ecRule[2] - ec) / (ecRule[2] - ecRule[1])); //�����������Ŀ϶�Ҫ������
    }
    else if (ec <= ecRule[3])  //ƫ��С�� 0
    {
      Dn = 2;
      //�����Ǿ��� -70 �������ȡ���Խ��������Խ��
      Df[0] = FMAX * ((float)(ecRule[3] - ec) / (ecRule[3] - ecRule[2])); //�����������Ŀ϶�Ҫ������
    }
    else if (ec <= ecRule[4]) //ƫ��С�� 70
    {
      Dn = 3;
      //�����Ǿ��� 0 �������ȡ���Խ��������Խ��
      Df[0] = FMAX * ((float)(ecRule[4] - ec) / (ecRule[4] - ecRule[3])); //�����������Ŀ϶�Ҫ������
    }
    else if (ec <= ecRule[5]) //ƫ��С�� 150
    {
      Dn = 4;
      //�����Ǿ��� 70 �������ȡ���Խ��������Խ��
      Df[0] = FMAX * ((float)(ecRule[5] - ec) / (ecRule[5] - ecRule[4])); //�����������Ŀ϶�Ҫ������
    }
    else if (ec <= ecRule[6]) //ƫ��С�� 230
    {
      Dn = 5;
      //�����Ǿ��� 150 �������ȡ���Խ��������Խ��
      Df[0] = FMAX * ((float)(ecRule[6] - ec) / (ecRule[6] - ecRule[5])); //�����������Ŀ϶�Ҫ������
    }
  }
  else if (ec <= ecRule[0]) //ƫ��С�� -230
  {
    Dn = 0;
    Df[0] = FMAX;
  }
  else if (ec >= ecRule[5]) //ƫ�����230
  {
    Dn = 5;
    Df[0] = 0;
  }
  
  Df[1] = FMAX - Df[0];
  
  //���
	Un[0] = rule[Pn][Dn];
	if (Pf[0] <= Df[0])
		Uf[0] = Pf[0];
	else
		Uf[0] = Df[0];

	Un[1] = rule[Pn+1][Dn];
	if (Pf[1] <= Df[0])
		Uf[1] = Pf[1];
	else
		Uf[1] = Df[0];

	Un[2] = rule[Pn][Dn+1];
	if (Pf[0] <= Df[1])
		Uf[2] = Pf[0];
	else
		Uf[2] = Df[1];

	Un[3] = rule[Pn+1][Dn+1];
	if (Pf[1] <= Df[1])
		Uf[3] = Pf[1];
	else
		Uf[3] = Df[1];

  
  //ͬ�������������ֵ
  if (Un[0] == Un[1])
  {
    if (Uf[0] > Uf[1])
      Uf[1] = 0;  //ֱ�ӰѸ���С������
    else
      Uf[0] = 0;
  }
  if (Un[0] == Un[2])
  {
    if (Uf[0] > Uf[2])
      Uf[2] = 0;  //ֱ�ӰѸ���С������
    else
      Uf[0] = 0;
  }
  if (Un[0] == Un[3])
  {
    if (Uf[0] > Uf[3])
      Uf[3] = 0;  //ֱ�ӰѸ���С������
    else
      Uf[0] = 0;
  }
  if (Un[1] == Un[2])
  {
    if (Uf[1] > Uf[2])
      Uf[2] = 0;  //ֱ�ӰѸ���С������
    else
      Uf[1] = 0;
  }
  if (Un[1] == Un[3])
  {
    if (Uf[1] > Uf[3])
      Uf[3] = 0;  //ֱ�ӰѸ���С������
    else
      Uf[1] = 0;
  }
  if (Un[2] == Un[3])
  {
    if (Uf[2] > Uf[3])
      Uf[3] = 0;  //ֱ�ӰѸ���С������
    else
      Uf[2] = 0;
  }
  //���ķ���ģ��
  Un[0] = KP_Rule[Un[0]];
  Un[1] = KP_Rule[Un[1]];
  Un[2] = KP_Rule[Un[2]];
  Un[3] = KP_Rule[Un[3]];
  //���ܵ�ȡֵ*���ȡֵ���ܵĸ���
  temp1 = Un[0] * Uf[0] + Un[1] * Uf[1] + Un[2] * Uf[2] + Un[3] * Uf[3];
  //���п��ܵĸ���
  temp2 = Uf[0] + Uf[1] + Uf[2] + Uf[3];
  
  KP = temp1 / temp2;
  KP /= 100;
  return KP;
}
	
/*******************************************************************************
*Description    :ģ���㷨
*
*modification   ��
*DATA           : 2017-5-29   By: handongdong
*******************************************************************************/
double	Fuzzy_kd(int  e, int ec)	//ģ�����㺯��
{
	int Pn = 0, Dn = 0;
	int Un[4] = { 0 };
	int Pf[2] = { 0 }, Df[2] = { 0 }, Uf[4] = { 0 };
	double KD;
	int temp1, temp2;
	int	KD_Rule[7] = { 10,20,30,40 }; //KP������	
         /* a0=0.3 ,a1=0.55 ,a2=0.74 ,a3=0.89 */
        //D�ڳ���(ƫ���ƫ��ı仯�ʷ���)��ʱ��Ӧ�ô�һ�㣬���ƴ��
	int rule[7][7] = {
  //���ı仯��NB NM NS Z PS PM PB
		{ 2,2,1,1,1,3,3 },			//NB
		{ 3,2,1,1,1,3,3 },			//NM
		{ 2,2,1,1,1,3,3 },			//NS
		{ 1,1,0,0,0,1,1 },			//Z
		{ 3,3,1,1,1,2,2 },			//PS
		{ 3,3,1,1,1,2,3 },			//PM
		{ 3,3,1,1,1,2,2 } };		        //PB
	int	eRule[7] = { -180,-110,-50,0,50,110,180 };  //ƫ�������
	int	ecRule[7] = { -12,-8,-4,0,4,8,12 };  //ƫ��仯�ʵ�����

	if (e > eRule[0] && e < eRule[6])  //���ƫ���ڷ�Χ��
	{
		if (e <= eRule[1])  //���ƫ��  < -150
		{
			Pn = 0;
			//�����Ǿ��� -230 �������ȡ���Խ��������Խ��
			Pf[0] = FMAX * ((float)(eRule[1] - e) / (eRule[1] - eRule[0])); //�����������Ŀ϶�Ҫ������
		}
		else if (e <= eRule[2])  //ƫ��С�� -70
		{
			Pn = 1;
			//�����Ǿ��� -150 �������ȡ���Խ��������Խ��
			Pf[0] = FMAX * ((float)(eRule[2] - e) / (eRule[2] - eRule[1])); //�����������Ŀ϶�Ҫ������
		}
		else if (e <= eRule[3])  //ƫ��С�� 0
		{
			Pn = 2;
			//�����Ǿ��� -70 �������ȡ���Խ��������Խ��
			Pf[0] = FMAX * ((float)(eRule[3] - e) / (eRule[3] - eRule[2])); //�����������Ŀ϶�Ҫ������
		}
		else if (e <= eRule[4]) //ƫ��С�� 70
		{
			Pn = 3;
			//�����Ǿ��� 0 �������ȡ���Խ��������Խ��
			Pf[0] = FMAX * ((float)(eRule[4] - e) / (eRule[4] - eRule[3])); //�����������Ŀ϶�Ҫ������
		}
		else if (e <= eRule[5]) //ƫ��С�� 150
		{
			Pn = 4;
			//�����Ǿ��� 70 �������ȡ���Խ��������Խ��
			Pf[0] = FMAX * ((float)(eRule[5] - e) / (eRule[5] - eRule[4])); //�����������Ŀ϶�Ҫ������
		}
		else if (e <= eRule[6]) //ƫ��С�� 230
		{
			Pn = 5;
			//�����Ǿ��� 150 �������ȡ���Խ��������Խ��
			Pf[0] = FMAX * ((float)(eRule[6] - e) / (eRule[6] - eRule[5])); //�����������Ŀ϶�Ҫ������
		}
	}
	else if (e <= eRule[0]) //ƫ��С�� -230
	{
		Pn = 0;
		Pf[0] = FMAX;
	}
	else if (e >= eRule[5]) //ƫ�����230
	{
		Pn = 5;
		Pf[0] = 0;
	}

	Pf[1] = FMAX - Pf[0];


	if (ec > ecRule[0] && ec < ecRule[6])  //���ƫ���ڷ�Χ��
	{
		if (ec <= ecRule[1])  //���ƫ��  < -150
		{
			Dn = 0;
			//�����Ǿ��� -230 �������ȡ���Խ��������Խ��
			Df[0] = FMAX * ((float)(ecRule[1] - ec) / (ecRule[1] - ecRule[0])); //�����������Ŀ϶�Ҫ������
		}
		else if (ec <= ecRule[2])  //ƫ��С�� -70
		{
			Dn = 1;
			//�����Ǿ��� -150 �������ȡ���Խ��������Խ��
			Df[0] = FMAX * ((float)(ecRule[2] - ec) / (ecRule[2] - ecRule[1])); //�����������Ŀ϶�Ҫ������
		}
		else if (ec <= ecRule[3])  //ƫ��С�� 0
		{
			Dn = 2;
			//�����Ǿ��� -70 �������ȡ���Խ��������Խ��
			Df[0] = FMAX * ((float)(ecRule[3] - ec) / (ecRule[3] - ecRule[2])); //�����������Ŀ϶�Ҫ������
		}
		else if (ec <= ecRule[4]) //ƫ��С�� 70
		{
			Dn = 3;
			//�����Ǿ��� 0 �������ȡ���Խ��������Խ��
			Df[0] = FMAX * ((float)(ecRule[4] - ec) / (ecRule[4] - ecRule[3])); //�����������Ŀ϶�Ҫ������
		}
		else if (ec <= ecRule[5]) //ƫ��С�� 150
		{
			Dn = 4;
			//�����Ǿ��� 70 �������ȡ���Խ��������Խ��
			Df[0] = FMAX * ((float)(ecRule[5] - ec) / (ecRule[5] - ecRule[4])); //�����������Ŀ϶�Ҫ������
		}
		else if (ec <= ecRule[6]) //ƫ��С�� 230
		{
			Dn = 5;
			//�����Ǿ��� 150 �������ȡ���Խ��������Խ��
			Df[0] = FMAX * ((float)(ecRule[6] - ec) / (ecRule[6] - ecRule[5])); //�����������Ŀ϶�Ҫ������
		}
	}
	else if (ec <= ecRule[0]) //ƫ��С�� -230
	{
		Dn = 0;
		Df[0] = FMAX;
	}
	else if (ec >= ecRule[5]) //ƫ�����230
	{
		Dn = 5;
		Df[0] = 0;
	}

	Df[1] = FMAX - Df[0];

	//���
	Un[0] = rule[Pn][Dn];
	if (Pf[0] <= Df[0])
		Uf[0] = Pf[0];
	else
		Uf[0] = Df[0];

	Un[1] = rule[Pn + 1][Dn];
	if (Pf[1] <= Df[0])
		Uf[1] = Pf[1];
	else
		Uf[1] = Df[0];

	Un[2] = rule[Pn][Dn + 1];
	if (Pf[0] <= Df[1])
		Uf[2] = Pf[0];
	else
		Uf[2] = Df[1];

	Un[3] = rule[Pn + 1][Dn + 1];
	if (Pf[1] <= Df[1])
		Uf[3] = Pf[1];
	else
		Uf[3] = Df[1];

	//ͬ�������������ֵ
	if (Un[0] == Un[1])
	{
		if (Uf[0] > Uf[1])
			Uf[1] = 0;  //ֱ�ӰѸ���С������
		else
			Uf[0] = 0;
	}
	if (Un[0] == Un[2])
	{
		if (Uf[0] > Uf[2])
			Uf[2] = 0;  //ֱ�ӰѸ���С������
		else
			Uf[0] = 0;
	}
	if (Un[0] == Un[3])
	{
		if (Uf[0] > Uf[3])
			Uf[3] = 0;  //ֱ�ӰѸ���С������
		else
			Uf[0] = 0;
	}
	if (Un[1] == Un[2])
	{
		if (Uf[1] > Uf[2])
			Uf[2] = 0;  //ֱ�ӰѸ���С������
		else
			Uf[1] = 0;
	}
	if (Un[1] == Un[3])
	{
		if (Uf[1] > Uf[3])
			Uf[3] = 0;  //ֱ�ӰѸ���С������
		else
			Uf[1] = 0;
	}
	if (Un[2] == Un[3])
	{
		if (Uf[2] > Uf[3])
			Uf[3] = 0;  //ֱ�ӰѸ���С������
		else
			Uf[2] = 0;
	}
	//���ķ���ģ��
	Un[0] = KD_Rule[Un[0]];
	Un[1] = KD_Rule[Un[1]];
	Un[2] = KD_Rule[Un[2]];
	Un[3] = KD_Rule[Un[3]];
	//���ܵ�ȡֵ*���ȡֵ���ܵĸ���
	temp1 = Un[0] * Uf[0] + Un[1] * Uf[1] + Un[2] * Uf[2] + Un[3] * Uf[3];
	//���п��ܵĸ���
	temp2 = Uf[0] + Uf[1] + Uf[2] + Uf[3];

	KD = temp1 / temp2;
	KD /= 100;

	return KD;
}