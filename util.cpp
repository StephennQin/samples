/*
 * ʹ��goto�����д����ж�
 * ���ַ�ʽ�������˳�ʱ��Ҫ����������,���û����Ҫ������������ݣ��Ϳ���ֱ��ʹ��return false����
 * ��ʼ��Ϊtrue; ����д��������Ϊfalse
 */


bool fun()
{
	//p��ʼ��Ϊtrue
	bool nRet = true;
	if(!fun1())
	{
		nRet = false;
		goto err;
	}
	if(!fun2())
	{
		nRet = false;
		goto err;
	}
err:
	return nRet;
	//������
}