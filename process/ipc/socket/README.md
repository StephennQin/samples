- ������TCP����UDP������������ʹ�÷����������ú󡣶�����������-1.���ǿ���ʹ��
WSAGetLastErrorҲ��ȡ��״̬��  
- ��WSAGetLastError()��ȡ��WSAEWOULDBLOCKʱ��������ʹ��select()��һ������.  
����select����ʱҪ���ݲ�ͬ����������ѡ��ͬ�Ĳ������������ó�ʱ��ʱ��һ��Ҫ��΢  
���ֵ��Ҫ����������벻���Ľ������

           fd_set rfds;
           struct timeval tv;
           int retval;
 
           /* Watch stdin (fd 0) to see when it has input. */
           FD_ZERO(&rfds);
           FD_SET(socket, &rfds);
		   /*FD_CLR �� FD_SET�෴*/
 
           /* Wait up to five seconds. */
           tv.tv_sec = 5;
           tv.tv_usec = 0;
 
           /*ע������Ķ����Ĳ�������ͬ������������Ӧ��ͬ��*/
           retval = select(0, &rfds, NULL, NULL, &tv);
           /* Don��t rely on the value of tv now! */
 
           if (retval == -1)
               perror("select()");
           else if (retval == 0)
               printf("No data within five seconds.\n");
           else /*����0*/
		   {
			   printf("Data is available now.\n");
		       if(FD_ISSET(socket, &rfds))
			   /* ���ֻ��һ��socket�Ͳ�����һ���ˣ���Ȼ����0�˾�˵��Ψһ����һ��׼�����ˣ�*/
			   {
					printf("socket is ready");
			   }
		   }