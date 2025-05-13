#include<stdio.h>
#include<stdlib.h>//malloc��ͷ�ļ�
#include<string.h> 
#define FILENAME1 "people.txt"
#define FILENAME2 "money.txt"
#define USERS_FILE "users.txt"
typedef struct pepoinfor{
	int building;//�� 
	int unit;//��Ԫ 
	int floor;//¥��
	int num;//����
	int age;//����
	char IDcard[20];//ID
	char telephonenumber[15];//�绰���� 
	char name[20];//ʹ���� 
	char judge[5];//�ж��Ƿ��о�����Դ  
	int peponum;//�˿��� 
	struct pepoinfor *next;//ָ����һ����ָ�� 
}pepole;

typedef struct moneyinfor{
	int year;//��
	int month;//��
	int day;//�� 
	int type;//���� 
	float amount;//���
	char name[20];//ʹ���� 
	char comment[100];//���� 
	struct moneyinfor *next;//ָ����һ����ָ�� 
}money;

pepole *head1=NULL;//ͷָ��
money *head2=NULL; 
 
void welcome();
void register_user();
void password();
void save1();//�������� 
void save2();//�������� 
void pepole_print();
void money_print(); 


//��ӭҳ
void welcome()
{
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\t\t\t\t��ӭ�����˿��ղ����ϵͳ\n");
        printf("\t\t        Welcome to the Census Management System\n");
        sleep(3);
        system("cls"); // ����
        printf("���Ժ�\n");
        printf("loading.....\n");
        sleep(5);
        system("cls"); // ����
}

//ע�����û������浽�ļ�
void register_user() 
{
    char username[20];
	char password[20];
    printf("�������û���:");
    scanf("%s", username);
    printf("����������:");
    scanf("%s", password);
    
     // �ж��û����������Ƿ�Ϊ��
    if (strlen(username) == 0 || strlen(password) == 0)
    {
        printf("�û��������벻��Ϊ�գ����������룡\n");
        system("pause"); // ��ͣ�Ա��û��Ķ���Ϣ
        system("cls");   // ����
        return;
    }

    FILE *file = fopen(USERS_FILE, "a+");
    
    if (!file)
	{
        printf("δ�ҵ����û�!\n");
        return;
    }
    // д���ļ�
    fprintf(file, "%s %s\n", username, password);//���û���������д���ļ���ÿ�д洢һ���û��������룬���ÿո�ָ�
    fclose(file);
    printf("ע��ɹ�!\n");
    system("pause"); // ��ͣ
    system("cls");   // ����
    
    if(login())
	{
		printf("��ӭ����ϵͳ��\n");
		system("pause"); // ��ͣ
	}
    else
    {
    	printf("��¼ʧ�ܣ������µ�½!\n");
    	system("cls");   // ����
    	login();
    	return;
	}
    system("cls");   // ����
}

void password()
{
    int choice;
	
    printf("�Ƿ�Ϊ���û�(1���û���0���û�)��");
    scanf("%d", &choice);

    if (choice == 1)
	{
        register_user();
        menu();
        system("cls");   // ����
    }
    else
    {
    	if(!login())
    	{
    		printf("δ�ҵ����û���\n");
    		printf("�Ƿ���Ҫע�����û�?(1��, 0��): ");
            scanf("%d", &choice);
            if (choice == 1)
			{
                register_user();
            }
			else
			{
                printf("���ٴγ��Ե�¼��\n");
                login(); // ����ѡ�����
            }
		}
	}
}

// ��¼���������ļ��ж�ȡ�û���Ϣ����֤
int login()
{
	int choice;
    char input_username[20];
	char input_password[20];//���������ַ���������������������������飬���Բ�����int 
    char line[50];//������һ����СΪ50���ַ������� line�����ڱ�����ļ��ж�ȡ��ÿһ������
	//����Ĵ�С50Ӧ���㹻����һ���е��û��������룬�Լ����ܴ��ڵĿո���з�
    char stored_username[20];//����һ���ַ��������ڴ洢�ļ��е��û��� 
	char stored_password[20];//����һ���ַ��������ڴ洢�ļ��е�����
    int logged_in=0;//// ��ʼ����¼״̬Ϊδ��¼ 

    printf("�������û���:");
    scanf("%s",input_username);
    printf("����������:");
    scanf("%s",input_password);
    
     // �ж��û����������Ƿ�Ϊ��
    if (strlen(username) == 0 || strlen(password) == 0)
    {
        printf("�û��������벻��Ϊ�գ����������룡\n");
        system("pause"); // ��ͣ�Ա��û��Ķ���Ϣ
        system("cls");   // ����
        return;
    }

    FILE *file=fopen(USERS_FILE,"r");//�� USERS_FILE �ļ���ȡ������ע����û���Ϣ��
    while(fgets(line,sizeof(line), file))//����user.txt�е�������� 
	{
        sscanf(line,"%s %s",stored_username,stored_password);//�����ı������û���������ֱ���� stored_username �� stored_password ������,��ÿһ������ʹ�� sscanf �������û���������
        if (strcmp(input_username, stored_username) == 0 && strcmp(input_password, stored_password) == 0)//ʹ�� strcmp �Ƚ��û������ƾ�����ļ��еļ�¼
		{
            logged_in = 1;// ��¼�ɹ������ñ�־Ϊ1
            break;//�˳�ѭ������Ϊ�Ѿ��ҵ���ƥ����
        }
    }
    fclose(file);
    
    if (logged_in)
	{
		printf("��½�ɹ���\n");
		system("pause"); // ��ͣ
        return 1; // ��¼�ɹ�
    }
	else
	{
		printf("�û���������������������룡\n");
        system("pause"); // ��ͣ�Ա��û��Ķ���Ϣ
        system("cls");   // ����
        return 0;
    }
}

//ϵͳ���˵�
int menu()
{
	int n;
	system("cls");//����
	printf("\n\n\n\n\n");
	printf("\t\t====================================�˿��ղ����ϵͳ====================================");
	printf("\n");
	printf("\t\t========================================================================================");
	printf("\t\t\n\t\t||                                        �˵�                                        ||\n");
	printf("\t\t||                                    1.�����˿ڼ�¼                                  ||\n");
	printf("\t\t||                                    2.������֧��¼                                  ||\n");
	printf("\t\t||                                    3.��ʾ�˿ڼ�¼                                  ||\n");
	printf("\t\t||                                    4.��ʾ��֧��¼                                  ||\n");
	printf("\t\t||                                    5.��ѯ�˿ڼ�¼                                  ||\n");
	printf("\t\t||                                    6.��ѯ��֧��¼                                  ||\n");
	printf("\t\t||                                    7.ɾ���˿ڼ�¼                                  ||\n");
	printf("\t\t||                                    8.ɾ����֧��¼                                  ||\n");
	printf("\t\t||                                    9.�޸��˿ڼ�¼                                  ||\n");
	printf("\t\t||                                    10.�޸���֧��¼                                 ||\n");
	printf("\t\t||                                      0.�˳�ϵͳ                                    ||\n");
	printf("\t\t========================================================================================");
	printf("                                                                ��ѡ������Ҫ�Ĺ��� (0-5) :\n                            ");
	scanf("%d",&n);
	return n;
}

//�˿��ļ���ȡ 
void read1()
{
	FILE *fp1;
	pepole *p1;
	//����a+���ɶ�����д����׷�ӣ�����ļ��������򴴽�
	if((fp1=fopen(FILENAME1,"a+"))==NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		return;
	}
	fseek(fp1,0,SEEK_END);//�ļ�ָ���ƶ���ĩβ 
	int size=ftell(fp1);//�ƶ���ƫ���� 
	fseek(fp1,0,SEEK_SET);//�ƶ���ͷ
	//�����ǰ�ļ�ָ��fpƫ����С����ƫ��������ѭ�� 
	while(ftell(fp1)<size)
	{
		p1=(pepole *)malloc(sizeof(struct pepoinfor));//��̬�����ڴ�ռ�
		fread(p1,sizeof(struct pepoinfor),1,fp1);
		p1->next=head1;//��һ��ʱheadΪ�գ��ڶ��ο�ʼΪ��һ��ͷ���ĵ�ַ 
		head1=p1;//�½��Ϊͷ��� 
	}
}
//��֧�ļ���ȡ 
void read2()
{
	FILE *fp2;
	money *p2;
	//����a+���ɶ�����д����׷�ӣ�����ļ��������򴴽�
	if((fp2=fopen(FILENAME2,"a+"))==NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		return;
	}
	fseek(fp2,0,SEEK_END);//�ļ�ָ���ƶ���ĩβ 
	int size=ftell(fp2);//�ƶ���ƫ���� 
	fseek(fp2,0,SEEK_SET);//�ƶ���ͷ
	//�����ǰ�ļ�ָ��fpƫ����С����ƫ��������ѭ�� 
	while(ftell(fp2)<size)
	{
		p2=(money *)malloc(sizeof(struct moneyinfor));//��̬�����ڴ�ռ�
		fread(p2,sizeof(struct moneyinfor),1,fp2);
		p2->next=head2;//��һ��ʱheadΪ�գ��ڶ��ο�ʼΪ��һ��ͷ���ĵ�ַ 
		head2=p2;//�½��Ϊͷ��� 
	}
}
//�����˿��ļ�
void save1()
{
	FILE *fp1;
	pepole *p1=NULL;
	//����wb+���ɶ�����д����׷�ӣ�����ļ��������򴴽�
	if((fp1=fopen(FILENAME1,"wb+"))==NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		system("pause");//��ͣ 
		return;
	}
	for(p1=head1;p1!=NULL;p1=p1->next)
	{
		if(fwrite(p1,sizeof(struct pepoinfor),1,fp1)!=1)
		{
			printf("д��ʧ�ܣ�\n");
			return;
		}
	}
	printf("д��ɹ���\n");		
	system("pause");//��ͣ 
	fclose(fp1);
} 

//������֧�ļ�
void save2()
{
	FILE *fp2;
	money *p2=NULL; 
	//����wb+���ɶ�����д����׷�ӣ�����ļ��������򴴽�
	if((fp2=fopen(FILENAME2,"wb+"))==NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		system("pause");//��ͣ 
		return;
	}
	for(p2=head2;p2!=NULL;p2=p2->next)
	{
		if(fwrite(p2,sizeof(struct moneyinfor),1,fp2)!=1)
		{
			printf("д��ʧ�ܣ�\n");
			return;
		}
	}
	printf("д��ɹ���\n");		
	system("pause");//��ͣ 
	fclose(fp2);
} 

//�˿���ʾ
void pepole_show()
{
	pepole *p1=head1;
    if(!head1)
    {
    	printf("��ǰû����Ϣ��\n");
    	return;
	}
	system("cls");//����
	printf("|======================================================================================================================|\n");
	printf("|  ��  |  ��Ԫ  |  ¥��  |  ����  |  ��ͥ��Ա����  |  ����  |  �Ƿ��о�����Դ  |  ��ͥ�˿���  |  ���֤  |   ��ϵ�绰  |\n");
	printf("|======================================================================================================================|\n");
    while (p1!=NULL)
	{
        printf("   %d       %d        %d       %d          %s         %d            %s               %d  %s %s\n",p1->building,p1->unit,p1->floor,p1->num,p1->name,p1->age,p1->judge,p1->peponum,p1->IDcard,p1->telephonenumber);
        p1=p1->next;//ָ���ƶ�����һ���ڵ� 
    }
    system("pause");//��ͣ 
} 

//��֧��ʾ
void money_show()
{
    money *p2=head2;
    if(!head2)
    {
    	printf("��ǰû����Ϣ��\n");
    	return;
	}
	system("cls");//����
	printf("|======================================================================================================================|\n");
	printf("|\t��\t|\t��\t|\t��\t|\t���\t  |\tʹ����\t   |   \t  ״̬\t   |\t   ����\t       |\n");
	printf("|======================================================================================================================|\n");
    while (p2!=NULL)
	{
       printf("\t%d \t\t%d \t\t%d\t\t%.1f\t\t  %s\t\t   %d\t\t   %s\t\t\n",p2->year,p2->month,p2->day,p2->amount,p2->name,p2->type,p2->comment);
        p2=p2->next;//ָ���ƶ�����һ���ڵ� 
    }
    system("pause");//��ͣ 
} 

//�˿�¼��
void pepole_add()
{
	system("cls");//����
	pepole *p1=NULL;
	p1=(pepole *)malloc(sizeof(struct pepoinfor));//��̬�����ڴ�ռ�
	//��ʼ���·�����ڴ�ռ䣬���⡰�ࡱ����
	memset(p1,0,sizeof(struct pepoinfor));
	printf("�����붰��"); 
	scanf("%d",&p1->building);
	printf("�����뵥Ԫ��"); 
	scanf("%d",&p1->unit);
	printf("������¥�㣺"); 
	scanf("%d",&p1->floor);
	printf("�����������"); 
	scanf("%d",&p1->num);
	printf("�������ͥ��Ա������"); 
	scanf("%s",p1->name);
	printf("���������䣺"); 
	scanf("%d",&p1->age);
	printf("�������Ƿ��о�����Դ��"); 
	scanf("%s",p1->judge);
	printf("�������ͥ�˿�����"); 
	scanf("%d",&p1->peponum);
	printf("���������֤��"); 
	scanf("%s",p1->IDcard);
	printf("������绰���룺"); 
	scanf("%s",p1->telephonenumber);
	p1->next=head1;//��һ��ʱheadΪ�գ��ڶ��ο�ʼΪ��һ��ͷ���ĵ�ַ 
	head1=p1;//�½��Ϊͷ��� 
	save1();//���� 
}

//��֧¼��
void money_add()
{
	system("cls");//����
	money *p2=NULL;
	p2=(money *)malloc(sizeof(struct moneyinfor));//��̬�����ڴ�ռ�
	//��ʼ���·�����ڴ�ռ䣬���⡰�ࡱ����
	memset(p2,0,sizeof(struct moneyinfor));
	printf("��������ݣ�"); 
	scanf("%d",&p2->year);
	printf("�������·ݣ�"); 
	scanf("%d",&p2->month);
	printf("���������ڣ�"); 
	scanf("%d",&p2->day);
	printf("�������"); 
	scanf("%f",&p2->amount);
	printf("������������"); 
	scanf("%s",p2->name);
	printf("����������(����Ϊ1��֧��Ϊ0)��"); 
	scanf("%d",&p2->type);
	printf("���������"); 
	scanf("%s",p2->comment);
	p2->next=head2;//��һ��ʱheadΪ�գ��ڶ��ο�ʼΪ��һ��ͷ���ĵ�ַ 
	head2=p2;//�½��Ϊͷ��� 
	save2();//���� 
}

//����
void money_search1()
{
	system("cls");//����
	money *p2=NULL;
	int choice,type;
	char name[20];
	if(!head1)
    {
    	printf("��ǰû����Ϣ��\n");
    	system("pause"); // ��ͣ�Ա��û��Ķ���Ϣ
    	return;
	}
	printf("1.��������2.�����ͣ�"); 
	scanf("%d",&choice);
	if(choice==1)
	{
		printf("������������");
		scanf("%s",name);
		for(p2=head2;p2!=NULL;p2=p2->next)//���� `head2` ָ�������
		{
			//�ڶ��������Ƿ�Ϊ��һ�����Ӽ���ʵ��ģ������Ч�� 
			if(strstr(p2->name,name)!=NULL)
			{
				printf("|======================================================================================================================|\n");
				printf("|\t��\t|\t��\t|\t��\t|\t���\t  |\tʹ����\t   |   \t  ״̬\t   |\t   ����\t       |\n");
				printf("|======================================================================================================================|\n");
				printf("       %d \t\t%d \t\t%d\t\t%.1f\t\t%s\t\t   %d\t\t   %s\t\t\n",p2->year,p2->month,p2->day,p2->amount,p2->name,p2->type,p2->comment);
			} 
		}
	system("pause");//��ͣ 
	return; 
	}
	if(choice==2)
	{
		printf("����������(����Ϊ1��֧��Ϊ0)��");
		scanf("%d",&type); 
		for(p2=head2;p2!=NULL;p2=p2->next)//���� `head2` ָ�������
		{
			if(p2->type==type)
			{
				printf("|======================================================================================================================|\n");
 				printf("|\t��\t|\t��\t|\t��\t|\t���\t  |\tʹ����\t   |   \t  ״̬\t   |\t   ����\t       |\n");
				printf("|======================================================================================================================|\n");
				printf("       %d \t\t%d \t\t%d\t\t%.1f\t\t%s\t\t   %d\t\t   %s\t\t\n",p2->year,p2->month,p2->day,p2->amount,p2->name,p2->type,p2->comment);
			}
		}
	system("pause");//��ͣ 
	return; 
	}
	else
	{
		printf("�������\n");
		system("pause");//��ͣ 
		return;
	} 
	 
}

//����
void pepole_search1()
{
	system("cls");//����
	pepole *p1=NULL;
	int choice;
	char IDcard[20];//ID 
	char name[20];
	if(!head2)
    {
    	printf("��ǰû����Ϣ��\n");
    	system("pause"); // ��ͣ�Ա��û��Ķ���Ϣ
    	return;
	}
	printf("1.��������2.�����֤�ţ�"); 
	scanf("%d",&choice);
	if(choice==1)
	{
		printf("������������");
		scanf("%s",name);
		for(p1=head1;p1!=NULL;p1=p1->next)//���� `head1` ָ�������
		{
			//�ڶ��������Ƿ�Ϊ��һ�����Ӽ���ʵ��ģ������Ч�� 
			if(strstr(p1->name,name)!=NULL)
			{
				printf("|======================================================================================================================|\n");
				printf("|  ��  |  ��Ԫ  |  ¥��  |  ����  |  ��ͥ��Ա����  |  ����  |  �Ƿ��о�����Դ  |  ��ͥ�˿���  |  ���֤  |   ��ϵ�绰  |\n");
				printf("|======================================================================================================================|\n");
				printf("   %d       %d        %d       %d          %s         %d            %s               %d  %s %s\n",p1->building,p1->unit,p1->floor,p1->num,p1->name,p1->age,p1->judge,p1->peponum,p1->IDcard,p1->telephonenumber);
			} 
		}
	system("pause");//��ͣ 
	return; 
	}
	if(choice==2)
	{
		printf("���������֤�ţ�");
		scanf("%s",IDcard); 
		for(p1=head1;p1!=NULL;p1=p1->next)//���� `head1` ָ�������
		{
			if(strstr(p1->IDcard,IDcard)!=NULL)
			{
				printf("|======================================================================================================================|\n");
				printf("|  ��  |  ��Ԫ  |  ¥��  |  ����  |  ��ͥ��Ա����  |  ����  |  �Ƿ��о�����Դ  |  ��ͥ�˿���  |  ���֤  |   ��ϵ�绰  |\n");
				printf("|======================================================================================================================|\n");
				printf("   %d       %d        %d       %d          %s         %d            %s               %d  %s %s\n",p1->building,p1->unit,p1->floor,p1->num,p1->name,p1->age,p1->judge,p1->peponum,p1->IDcard,p1->telephonenumber);
			}
		}
	system("pause");//��ͣ 
	return; 
	}
	else
	{
		printf("�������\n");
		system("pause");//��ͣ 
		return;
	} 
} 

//�˿ڲ���ģ�� 
void pepole_search()
{
	system("cls");//����
	pepole *p1=NULL;
	int choice;
	char IDcard[20];//ID
	char pepoinfor[20];
	printf("1.��������2.�����֤�ţ�"); 
	scanf("%d",&choice);
	if(choice==1)
	{
		printf("������������");
		scanf("%s",pepoinfor);
		pepole_print(choice,pepoinfor);
		system("pause");//��ͣ 
		return;
	}
	if(choice==2)
	{
		printf("���������֤�ţ�");
		scanf("%s",IDcard);
		pepole_print(choice,pepoinfor);
		system("pause");//��ͣ 
		return;
	}
	else
	{
		printf("�������\n");
		system("pause");//��ͣ 
		return;
	} 
}

//��֧����ģ�� 
void money_search()
{
	system("cls");//����
	money *p2=NULL;
	int choice,type;
	char moneyinfor[20];
	printf("1.��������2.�����ͣ�"); 
	scanf("%d",&choice);
	if(choice==1)
	{
		printf("������������");
		scanf("%s",moneyinfor);
		money_print(choice,moneyinfor);
		system("pause");//��ͣ 
		return;
	}
	if(choice==2)
	{
		printf("����������(����Ϊ1��֧��Ϊ0)��");
		scanf("%d",&type);
		//��������type��תΪ���飨�ɵڶ�������ȷ��������������Ϊ��ת���Ľ��� 
		itoa(type,moneyinfor,10);
		money_print(choice,moneyinfor);
		system("pause");//��ͣ 
		return;
	}
	else
	{
		printf("�������\n");
		system("pause");//��ͣ 
		return;
	} 
	 
}

//�˿������Ϣ�����ң��������У�����choiceΪ1��pepoinfor����������choiceΪ2��pepoinfor�����֤ 
void pepole_print(int choice,const char pepoinfor[20])//ǰ����� const �ؼ��ֱ�ʾ���ָ����ָ������ݣ����ַ��������ݣ��ǳ���������ͨ����ָ���޸ġ�
{
	
	pepole *p1=head1;
    if(!head1)
    { 
    	printf("��ǰû����Ϣ��\n");
    	system("pause");//��ͣ 
		return;
	}
	system("cls");//����
	printf("|======================================================================================================================|\n");
	printf("|  ��  |  ��Ԫ  |  ¥��  |  ����  |  ��ͥ��Ա����  |  ����  |  �Ƿ��о�����Դ  |  ��ͥ�˿���  |  ���֤  |   ��ϵ�绰  |\n");
	printf("|======================================================================================================================|\n");
	for(p1=head1;p1!=NULL;p1=p1->next)
	{
		switch(choice)
		{
			case 1:
				if(strstr(p1->name,pepoinfor)!=NULL)
				{
					goto printinfor;
				}
				break;
			case 2:
				if(strcmp(p1->IDcard,pepoinfor)==0)
				{
					goto printinfor;
				}
				break;
			case 99:
				goto printinfor;
				
			printinfor:
			printf("   %d       %d        %d       %d          %s         %d            %s               %d  %s %s\n",p1->building,p1->unit,p1->floor,p1->num,p1->name,p1->age,p1->judge,p1->peponum,p1->IDcard,p1->telephonenumber);
		}
		continue;
	}
	system("pause");//��ͣ 
}

//�����Ϣ�����ң��������У�����choiceΪ1��pepoinfor����������choiceΪ2��pepoinfor������
void money_print(int choice,const char moneyinfor[20])//ǰ����� const �ؼ��ֱ�ʾ���ָ����ָ������ݣ����ַ��������ݣ��ǳ���������ͨ����ָ���޸ġ�
{
	money *p2=head2;
	float income=0.0;
	float outgoing=0.0;
	float balance=0.0;
    if(!head2)
    { 
    	printf("��ǰû����Ϣ��\n");
    	system("pause");//��ͣ 
		return;
	}
	system("cls");//����
	printf("|======================================================================================================================|\n");
	printf("|\t��\t|\t��\t|\t��\t|\t���\t  |\tʹ����\t   |   \t  ״̬\t   |\t   ����\t       |\n");
	printf("|======================================================================================================================|\n");
	for(p2=head2;p2!=NULL;p2=p2->next)
	{
		switch(choice)
		{
			case 1:
				if(strstr(p2->name,moneyinfor)!=NULL)
				{
					goto printinfor;
				}
				break;
			case 2:
				if(p2->type==atoi(moneyinfor))
				{
					goto printinfor;
				}
				break;
			case 99:
				if(p2->type==1)
				{
					income+=p2->amount;
				}
				else
				{
					outgoing+=p2->amount;
				}
				goto printinfor;
				
			printinfor:
			printf("       %d \t\t%d \t\t%d\t\t%.1f\t\t%s\t\t   %d\t\t   %s\t\t\n",p2->year,p2->month,p2->day,p2->amount,p2->name,p2->type,p2->comment);
		}
		continue;
	}
	printf("������: %.1f\n", income);
    printf("��֧��: %.1f\n", outgoing);
    printf("������(����-֧��): %.1f\n", income-outgoing);
	system("pause");//��ͣ 
}

//�˿�ɾ��ģ�� 
void pepole_del()
{
	pepole *p1=head1;
	pepole *prev1=head1;
	char name[20];//ʹ����
	int choice;
	char IDcard[20];//ID
	system("cls");//���� 
	
	if(!head1)
    {
    	printf("��ǰû����Ϣ��\n");
    	system("pause"); // ��ͣ�Ա��û��Ķ���Ϣ
    	return;
	}
	
	printf("������������");
	scanf("%s",name);
	printf("���������֤�ţ�");
	scanf("%s",IDcard);
	
	for(;p1!=NULL;prev1=p1,p1=p1->next)
	{
		if(strcmp(p1->name,name)==0 && strcmp(p1->IDcard, IDcard) == 0)
		{
			printf("   %d       %d        %d       %d          %s         %d            %s               %d  %s %s\n",p1->building,p1->unit,p1->floor,p1->num,p1->name,p1->age,p1->judge,p1->peponum,p1->IDcard,p1->telephonenumber);
			printf("���Ƿ�Ҫɾ��(1ɾ����0��ɾ��)��");
			scanf("%d", &choice);
			if(choice==1)
			{
				if(p1==head1)
				{
					head1=p1->next;
				} 
				else
				{
					prev1->next=p1->next;
					
				}
				free(p1);
				printf("ɾ���ɹ���\n");
				save1();
				break;	
			}
			else
			{
				printf("��ɾ����\n");
				system("pause");
				return;
			}
		}
	}
	if(p1==NULL)
	{
		printf("δ�ҵ���\n");
		system("pause");
		return;
	}
 } 

//��֧ɾ��ģ�� 
void money_del()
{
	money *p2=head2;
	money *prev2=head2;
	char name[20];//ʹ����
	int choice;
	float amount;//���
	system("cls");//���� 
	
	if(!head2)
    {
    	printf("��ǰû����Ϣ��\n");
    	system("pause"); // ��ͣ�Ա��û��Ķ���Ϣ
    	return;
	}
	printf("������������");
	scanf("%s",name);
	printf("�������");
	scanf("%f",&amount);
	
	for(;p2!=NULL;prev2=p2,p2=p2->next)
	{
		if(strcmp(p2->name,name)==0 && p2->amount==amount)
		{
			printf("       %d \t\t%d \t\t%d\t\t%.1f\t\t%s\t\t   %d\t\t   %s\t\t\n",p2->year,p2->month,p2->day,p2->amount,p2->name,p2->type,p2->comment);
			printf("���Ƿ�Ҫɾ��(1ɾ����0��ɾ��)��");
			scanf("%d", &choice);
			if(choice==1)
			{
				if(p2==head2)
				{
					head2=p2->next;
				} 
				else
				{
					prev2->next=p2->next;
					
				}
				free(p2);
				printf("ɾ���ɹ���\n");
				save2();
				break;	
			}
			else
			{
				printf("��ɾ����\n");
				system("pause");
				return;
			}
		}
	}
	if(p2==NULL)
	{
		printf("δ�ҵ���\n");
		system("pause");
		return;
	}
} 
 
//�˿��޸�ģ��
void pepole_edit()
{
    pepole *p1=head1;
    int choice; 
    char name[20]; // ʹ����
    char IDcard[20];//ID
    system("cls"); // ���� 

    printf("������������");
    scanf("%s",name);
    printf("���������֤�ţ�");
    scanf("%s",IDcard);

    for (;p1!=NULL;p1=p1->next)
    {
        if (strcmp(p1->name,name)==0 && strcmp(p1->IDcard,IDcard)==0)
        {
            // ��ʾ��ǰ��Ϣ
            printf("   %d       %d        %d       %d          %s         %d            %s               %d  %s %s\n",p1->building,p1->unit,p1->floor,p1->num,p1->name,p1->age,p1->judge,p1->peponum,p1->IDcard,p1->telephonenumber);
            printf("��ȷ���Ƿ��޸Ĵ�����¼(1 ȷ�ϣ�0 ȡ��)��");
            scanf("%d", &choice);
            if (choice == 1)
            {
                // ��ȡ����Ϣ
                printf("�����붰����ǰ��%d����",p1->building); 
				scanf("%d",&p1->building);
				printf("�����뵥Ԫ����ǰ��%d����",p1->unit); 
				scanf("%d",&p1->unit);
				printf("������¥�㣨��ǰ��%d����",p1->floor); 
				scanf("%d",&p1->floor);
				printf("�������������ǰ��%d����",p1->num); 
				scanf("%d",&p1->num);
				printf("�������ͥ��Ա��������ǰ��%s����",p1->name); 
				scanf("%s",p1->name);
				printf("���������䣨��ǰ��%d����",p1->age); 
				scanf("%d",&p1->age);
				printf("�������Ƿ��о�����Դ����ǰ��%s����",p1->judge); 
				scanf("%s",p1->judge);
				printf("�������ͥ�˿�������ǰ��%d����",p1->peponum); 
				scanf("%d",&p1->peponum);
				printf("������绰���루��ǰ��%s����",p1->telephonenumber); 
				scanf("%s",p1->telephonenumber);

                // �������
				printf("�޸ĳɹ���\n");
                save1();
                return;
            }
            else
            {
                printf("ȡ���޸ġ�\n");
                system("pause");
                return;
            }
        }
    }
    printf("δ�ҵ�ƥ���¼��\n");
    system("pause"); // ��ͣ�Ա��û��Ķ���Ϣ
}

//��֧�޸�ģ�� 
void money_edit()
{
    money *p2=head2;
    int choice; 
    char name[20]; // ʹ����
    float amount;  // ���
    system("cls"); // ���� 

    printf("������������");
    scanf("%s", name);
    printf("�������");
    scanf("%f", &amount);

    for (;p2!=NULL;p2=p2->next)
    {
        if (strcmp(p2->name,name)==0 && p2->amount == amount)
        {
            // ��ʾ��ǰ��Ϣ
            printf("       %d \t\t%d \t\t%d\t\t%.1f\t\t%s\t\t   %d\t\t   %s\t\t\n",p2->year,p2->month,p2->day,p2->amount,p2->name,p2->type,p2->comment);
            printf("��ȷ���Ƿ��޸Ĵ�����¼(1 ȷ�ϣ�0 ȡ��)��");
            scanf("%d", &choice);
            if (choice == 1)
            {
                // ��ȡ����Ϣ
                printf("��������ݣ���ǰ��%d����", p2->year);
                scanf("%d", &p2->year);
                printf("�������·ݣ���ǰ��%d����", p2->month);
                scanf("%d", &p2->month);
                printf("���������ڣ���ǰ��%d����", p2->day);
                scanf("%d", &p2->day);
                printf("���������ǰ��%.1f����", p2->amount);
                scanf("%f", &p2->amount);
                printf("��������������ǰ��%s����", p2->name);
                scanf("%s", p2->name);
                printf("����������(����Ϊ1��֧��Ϊ0)����ǰ��%d����", p2->type);
                scanf("%d", &p2->type);
                printf("�����������ǰ��%s����", p2->comment);
                scanf(" %s", p2->comment);

                // ������� 
				printf("�޸ĳɹ���\n");
                save2();
                return;
            }
            else
            {
                printf("ȡ���޸ġ�\n");
                system("pause");
                return;
            }
        }
    }
    printf("δ�ҵ�ƥ���¼��\n");
    system("pause"); // ��ͣ�Ա��û��Ķ���Ϣ
} 

int main()
{
	int n;
	welcome();
	password();
	read1();
	read2();
	do{
		n=menu();
		switch(n)
		{
			case 1:
				pepole_add();
				break;
			case 2:
				money_add();
				break;
			case 3:
				//pepole_show();
				pepole_print(99,NULL);
				break;
			case 4:
				//money_show();
				money_print(99,NULL);
				break;
			case 5:
				//pepole_search();
				pepole_search1();
				break;
			case 6:
				//money_search();
				money_search1();
				break; 
			case 7:
				pepole_del();
				break;
			case 8:
				money_del();
				break;
			case 9:
				pepole_edit();
				break;
			case 10:
				money_edit();
				break;
		}
	}while(n);
	return 0;
}
