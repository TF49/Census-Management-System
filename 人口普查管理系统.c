#include<stdio.h>
#include<stdlib.h>//malloc的头文件
#include<string.h> 
#define FILENAME1 "people.txt"
#define FILENAME2 "money.txt"
#define USERS_FILE "users.txt"
typedef struct pepoinfor{
	int building;//栋 
	int unit;//单元 
	int floor;//楼层
	int num;//号码
	int age;//年龄
	char IDcard[20];//ID
	char telephonenumber[15];//电话号码 
	char name[20];//使用人 
	char judge[5];//判断是否有经济来源  
	int peponum;//人口数 
	struct pepoinfor *next;//指向下一结点的指针 
}pepole;

typedef struct moneyinfor{
	int year;//年
	int month;//月
	int day;//日 
	int type;//类型 
	float amount;//金额
	char name[20];//使用人 
	char comment[100];//事项 
	struct moneyinfor *next;//指向下一结点的指针 
}money;

pepole *head1=NULL;//头指针
money *head2=NULL; 
 
void welcome();
void register_user();
void password();
void save1();//申明函数 
void save2();//申明函数 
void pepole_print();
void money_print(); 


//欢迎页
void welcome()
{
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\t\t\t\t欢迎来到人口普查管理系统\n");
        printf("\t\t        Welcome to the Census Management System\n");
        sleep(3);
        system("cls"); // 清屏
        printf("请稍后\n");
        printf("loading.....\n");
        sleep(5);
        system("cls"); // 清屏
}

//注册新用户并保存到文件
void register_user() 
{
    char username[20];
	char password[20];
    printf("请输入用户名:");
    scanf("%s", username);
    printf("请输入密码:");
    scanf("%s", password);
    
     // 判断用户名或密码是否为空
    if (strlen(username) == 0 || strlen(password) == 0)
    {
        printf("用户名或密码不能为空，请重新输入！\n");
        system("pause"); // 暂停以便用户阅读消息
        system("cls");   // 清屏
        return;
    }

    FILE *file = fopen(USERS_FILE, "a+");
    
    if (!file)
	{
        printf("未找到该用户!\n");
        return;
    }
    // 写入文件
    fprintf(file, "%s %s\n", username, password);//将用户名和密码写入文件，每行存储一对用户名和密码，并用空格分隔
    fclose(file);
    printf("注册成功!\n");
    system("pause"); // 暂停
    system("cls");   // 清屏
    
    if(login())
	{
		printf("欢迎进入系统！\n");
		system("pause"); // 暂停
	}
    else
    {
    	printf("登录失败，请重新登陆!\n");
    	system("cls");   // 清屏
    	login();
    	return;
	}
    system("cls");   // 清屏
}

void password()
{
    int choice;
	
    printf("是否为新用户(1新用户，0老用户)：");
    scanf("%d", &choice);

    if (choice == 1)
	{
        register_user();
        menu();
        system("cls");   // 清屏
    }
    else
    {
    	if(!login())
    	{
    		printf("未找到该用户！\n");
    		printf("是否需要注册新用户?(1是, 0否): ");
            scanf("%d", &choice);
            if (choice == 1)
			{
                register_user();
            }
			else
			{
                printf("请再次尝试登录。\n");
                login(); // 返回选择界面
            }
		}
	}
}

// 登录函数，从文件中读取用户信息并验证
int login()
{
	int choice;
    char input_username[20];
	char input_password[20];//密码是以字符串类型输入输出，不是整数数组，所以不能用int 
    char line[50];//定义了一个大小为50个字符的数组 line，用于保存从文件中读取的每一行内容
	//这里的大小50应该足够容纳一行中的用户名和密码，以及可能存在的空格或换行符
    char stored_username[20];//定义一个字符数组用于存储文件中的用户名 
	char stored_password[20];//定义一个字符数组用于存储文件中的密码
    int logged_in=0;//// 初始化登录状态为未登录 

    printf("请输入用户名:");
    scanf("%s",input_username);
    printf("请输入密码:");
    scanf("%s",input_password);
    
     // 判断用户名或密码是否为空
    if (strlen(username) == 0 || strlen(password) == 0)
    {
        printf("用户名或密码不能为空，请重新输入！\n");
        system("pause"); // 暂停以便用户阅读消息
        system("cls");   // 清屏
        return;
    }

    FILE *file=fopen(USERS_FILE,"r");//打开 USERS_FILE 文件读取所有已注册的用户信息。
    while(fgets(line,sizeof(line), file))//调用user.txt中的相关数据 
	{
        sscanf(line,"%s %s",stored_username,stored_password);//解析文本，将用户名和密码分别存入 stored_username 和 stored_password 变量中,对每一行数据使用 sscanf 解析出用户名和密码
        if (strcmp(input_username, stored_username) == 0 && strcmp(input_password, stored_password) == 0)//使用 strcmp 比较用户输入的凭据与文件中的记录
		{
            logged_in = 1;// 登录成功，设置标志为1
            break;//退出循环，因为已经找到了匹配项
        }
    }
    fclose(file);
    
    if (logged_in)
	{
		printf("登陆成功！\n");
		system("pause"); // 暂停
        return 1; // 登录成功
    }
	else
	{
		printf("用户名或密码错误，请重新输入！\n");
        system("pause"); // 暂停以便用户阅读消息
        system("cls");   // 清屏
        return 0;
    }
}

//系统主菜单
int menu()
{
	int n;
	system("cls");//清屏
	printf("\n\n\n\n\n");
	printf("\t\t====================================人口普查管理系统====================================");
	printf("\n");
	printf("\t\t========================================================================================");
	printf("\t\t\n\t\t||                                        菜单                                        ||\n");
	printf("\t\t||                                    1.新增人口记录                                  ||\n");
	printf("\t\t||                                    2.新增收支记录                                  ||\n");
	printf("\t\t||                                    3.显示人口记录                                  ||\n");
	printf("\t\t||                                    4.显示收支记录                                  ||\n");
	printf("\t\t||                                    5.查询人口记录                                  ||\n");
	printf("\t\t||                                    6.查询收支记录                                  ||\n");
	printf("\t\t||                                    7.删除人口记录                                  ||\n");
	printf("\t\t||                                    8.删除收支记录                                  ||\n");
	printf("\t\t||                                    9.修改人口记录                                  ||\n");
	printf("\t\t||                                    10.修改收支记录                                 ||\n");
	printf("\t\t||                                      0.退出系统                                    ||\n");
	printf("\t\t========================================================================================");
	printf("                                                                请选择您想要的功能 (0-5) :\n                            ");
	scanf("%d",&n);
	return n;
}

//人口文件读取 
void read1()
{
	FILE *fp1;
	pepole *p1;
	//参数a+，可读，可写，可追加，如果文件不存在则创建
	if((fp1=fopen(FILENAME1,"a+"))==NULL)
	{
		printf("文件打开失败！\n");
		return;
	}
	fseek(fp1,0,SEEK_END);//文件指针移动到末尾 
	int size=ftell(fp1);//移动的偏移量 
	fseek(fp1,0,SEEK_SET);//移动到头
	//如果当前文件指针fp偏移量小于总偏移量，则循环 
	while(ftell(fp1)<size)
	{
		p1=(pepole *)malloc(sizeof(struct pepoinfor));//动态分配内存空间
		fread(p1,sizeof(struct pepoinfor),1,fp1);
		p1->next=head1;//第一次时head为空，第二次开始为上一个头结点的地址 
		head1=p1;//新结点为头结点 
	}
}
//收支文件读取 
void read2()
{
	FILE *fp2;
	money *p2;
	//参数a+，可读，可写，可追加，如果文件不存在则创建
	if((fp2=fopen(FILENAME2,"a+"))==NULL)
	{
		printf("文件打开失败！\n");
		return;
	}
	fseek(fp2,0,SEEK_END);//文件指针移动到末尾 
	int size=ftell(fp2);//移动的偏移量 
	fseek(fp2,0,SEEK_SET);//移动到头
	//如果当前文件指针fp偏移量小于总偏移量，则循环 
	while(ftell(fp2)<size)
	{
		p2=(money *)malloc(sizeof(struct moneyinfor));//动态分配内存空间
		fread(p2,sizeof(struct moneyinfor),1,fp2);
		p2->next=head2;//第一次时head为空，第二次开始为上一个头结点的地址 
		head2=p2;//新结点为头结点 
	}
}
//保存人口文件
void save1()
{
	FILE *fp1;
	pepole *p1=NULL;
	//参数wb+，可读，可写，可追加，如果文件不存在则创建
	if((fp1=fopen(FILENAME1,"wb+"))==NULL)
	{
		printf("文件打开失败！\n");
		system("pause");//暂停 
		return;
	}
	for(p1=head1;p1!=NULL;p1=p1->next)
	{
		if(fwrite(p1,sizeof(struct pepoinfor),1,fp1)!=1)
		{
			printf("写入失败！\n");
			return;
		}
	}
	printf("写入成功！\n");		
	system("pause");//暂停 
	fclose(fp1);
} 

//保存收支文件
void save2()
{
	FILE *fp2;
	money *p2=NULL; 
	//参数wb+，可读，可写，可追加，如果文件不存在则创建
	if((fp2=fopen(FILENAME2,"wb+"))==NULL)
	{
		printf("文件打开失败！\n");
		system("pause");//暂停 
		return;
	}
	for(p2=head2;p2!=NULL;p2=p2->next)
	{
		if(fwrite(p2,sizeof(struct moneyinfor),1,fp2)!=1)
		{
			printf("写入失败！\n");
			return;
		}
	}
	printf("写入成功！\n");		
	system("pause");//暂停 
	fclose(fp2);
} 

//人口显示
void pepole_show()
{
	pepole *p1=head1;
    if(!head1)
    {
    	printf("当前没有信息！\n");
    	return;
	}
	system("cls");//清屏
	printf("|======================================================================================================================|\n");
	printf("|  栋  |  单元  |  楼层  |  号数  |  家庭成员姓名  |  年龄  |  是否有经济来源  |  家庭人口数  |  身份证  |   联系电话  |\n");
	printf("|======================================================================================================================|\n");
    while (p1!=NULL)
	{
        printf("   %d       %d        %d       %d          %s         %d            %s               %d  %s %s\n",p1->building,p1->unit,p1->floor,p1->num,p1->name,p1->age,p1->judge,p1->peponum,p1->IDcard,p1->telephonenumber);
        p1=p1->next;//指针移动到下一个节点 
    }
    system("pause");//暂停 
} 

//收支显示
void money_show()
{
    money *p2=head2;
    if(!head2)
    {
    	printf("当前没有信息！\n");
    	return;
	}
	system("cls");//清屏
	printf("|======================================================================================================================|\n");
	printf("|\t年\t|\t月\t|\t日\t|\t金额\t  |\t使用人\t   |   \t  状态\t   |\t   事项\t       |\n");
	printf("|======================================================================================================================|\n");
    while (p2!=NULL)
	{
       printf("\t%d \t\t%d \t\t%d\t\t%.1f\t\t  %s\t\t   %d\t\t   %s\t\t\n",p2->year,p2->month,p2->day,p2->amount,p2->name,p2->type,p2->comment);
        p2=p2->next;//指针移动到下一个节点 
    }
    system("pause");//暂停 
} 

//人口录入
void pepole_add()
{
	system("cls");//清屏
	pepole *p1=NULL;
	p1=(pepole *)malloc(sizeof(struct pepoinfor));//动态分配内存空间
	//初始化新分配的内存空间，避免“脏”数据
	memset(p1,0,sizeof(struct pepoinfor));
	printf("请输入栋："); 
	scanf("%d",&p1->building);
	printf("请输入单元："); 
	scanf("%d",&p1->unit);
	printf("请输入楼层："); 
	scanf("%d",&p1->floor);
	printf("请输入号数："); 
	scanf("%d",&p1->num);
	printf("请输入家庭成员姓名："); 
	scanf("%s",p1->name);
	printf("请输入年龄："); 
	scanf("%d",&p1->age);
	printf("请输入是否有经济来源："); 
	scanf("%s",p1->judge);
	printf("请输入家庭人口数："); 
	scanf("%d",&p1->peponum);
	printf("请输入身份证："); 
	scanf("%s",p1->IDcard);
	printf("请输入电话号码："); 
	scanf("%s",p1->telephonenumber);
	p1->next=head1;//第一次时head为空，第二次开始为上一个头结点的地址 
	head1=p1;//新结点为头结点 
	save1();//保存 
}

//收支录入
void money_add()
{
	system("cls");//清屏
	money *p2=NULL;
	p2=(money *)malloc(sizeof(struct moneyinfor));//动态分配内存空间
	//初始化新分配的内存空间，避免“脏”数据
	memset(p2,0,sizeof(struct moneyinfor));
	printf("请输入年份："); 
	scanf("%d",&p2->year);
	printf("请输入月份："); 
	scanf("%d",&p2->month);
	printf("请输入日期："); 
	scanf("%d",&p2->day);
	printf("请输入金额："); 
	scanf("%f",&p2->amount);
	printf("请输入姓名："); 
	scanf("%s",p2->name);
	printf("请输入类型(收入为1，支出为0)："); 
	scanf("%d",&p2->type);
	printf("请输入事项："); 
	scanf("%s",p2->comment);
	p2->next=head2;//第一次时head为空，第二次开始为上一个头结点的地址 
	head2=p2;//新结点为头结点 
	save2();//保存 
}

//查找
void money_search1()
{
	system("cls");//清屏
	money *p2=NULL;
	int choice,type;
	char name[20];
	if(!head1)
    {
    	printf("当前没有信息！\n");
    	system("pause"); // 暂停以便用户阅读消息
    	return;
	}
	printf("1.按姓名；2.按类型："); 
	scanf("%d",&choice);
	if(choice==1)
	{
		printf("请输入姓名：");
		scanf("%s",name);
		for(p2=head2;p2!=NULL;p2=p2->next)//遍历 `head2` 指向的链表
		{
			//第二个参数是否为第一个的子集，实现模糊查找效果 
			if(strstr(p2->name,name)!=NULL)
			{
				printf("|======================================================================================================================|\n");
				printf("|\t年\t|\t月\t|\t日\t|\t金额\t  |\t使用人\t   |   \t  状态\t   |\t   事项\t       |\n");
				printf("|======================================================================================================================|\n");
				printf("       %d \t\t%d \t\t%d\t\t%.1f\t\t%s\t\t   %d\t\t   %s\t\t\n",p2->year,p2->month,p2->day,p2->amount,p2->name,p2->type,p2->comment);
			} 
		}
	system("pause");//暂停 
	return; 
	}
	if(choice==2)
	{
		printf("请输入类型(收入为1，支出为0)：");
		scanf("%d",&type); 
		for(p2=head2;p2!=NULL;p2=p2->next)//遍历 `head2` 指向的链表
		{
			if(p2->type==type)
			{
				printf("|======================================================================================================================|\n");
 				printf("|\t年\t|\t月\t|\t日\t|\t金额\t  |\t使用人\t   |   \t  状态\t   |\t   事项\t       |\n");
				printf("|======================================================================================================================|\n");
				printf("       %d \t\t%d \t\t%d\t\t%.1f\t\t%s\t\t   %d\t\t   %s\t\t\n",p2->year,p2->month,p2->day,p2->amount,p2->name,p2->type,p2->comment);
			}
		}
	system("pause");//暂停 
	return; 
	}
	else
	{
		printf("输入错误！\n");
		system("pause");//暂停 
		return;
	} 
	 
}

//查找
void pepole_search1()
{
	system("cls");//清屏
	pepole *p1=NULL;
	int choice;
	char IDcard[20];//ID 
	char name[20];
	if(!head2)
    {
    	printf("当前没有信息！\n");
    	system("pause"); // 暂停以便用户阅读消息
    	return;
	}
	printf("1.按姓名；2.按身份证号："); 
	scanf("%d",&choice);
	if(choice==1)
	{
		printf("请输入姓名：");
		scanf("%s",name);
		for(p1=head1;p1!=NULL;p1=p1->next)//遍历 `head1` 指向的链表
		{
			//第二个参数是否为第一个的子集，实现模糊查找效果 
			if(strstr(p1->name,name)!=NULL)
			{
				printf("|======================================================================================================================|\n");
				printf("|  栋  |  单元  |  楼层  |  号数  |  家庭成员姓名  |  年龄  |  是否有经济来源  |  家庭人口数  |  身份证  |   联系电话  |\n");
				printf("|======================================================================================================================|\n");
				printf("   %d       %d        %d       %d          %s         %d            %s               %d  %s %s\n",p1->building,p1->unit,p1->floor,p1->num,p1->name,p1->age,p1->judge,p1->peponum,p1->IDcard,p1->telephonenumber);
			} 
		}
	system("pause");//暂停 
	return; 
	}
	if(choice==2)
	{
		printf("请输入身份证号：");
		scanf("%s",IDcard); 
		for(p1=head1;p1!=NULL;p1=p1->next)//遍历 `head1` 指向的链表
		{
			if(strstr(p1->IDcard,IDcard)!=NULL)
			{
				printf("|======================================================================================================================|\n");
				printf("|  栋  |  单元  |  楼层  |  号数  |  家庭成员姓名  |  年龄  |  是否有经济来源  |  家庭人口数  |  身份证  |   联系电话  |\n");
				printf("|======================================================================================================================|\n");
				printf("   %d       %d        %d       %d          %s         %d            %s               %d  %s %s\n",p1->building,p1->unit,p1->floor,p1->num,p1->name,p1->age,p1->judge,p1->peponum,p1->IDcard,p1->telephonenumber);
			}
		}
	system("pause");//暂停 
	return; 
	}
	else
	{
		printf("输入错误！\n");
		system("pause");//暂停 
		return;
	} 
} 

//人口查找模块 
void pepole_search()
{
	system("cls");//清屏
	pepole *p1=NULL;
	int choice;
	char IDcard[20];//ID
	char pepoinfor[20];
	printf("1.按姓名；2.按身份证号："); 
	scanf("%d",&choice);
	if(choice==1)
	{
		printf("请输入姓名：");
		scanf("%s",pepoinfor);
		pepole_print(choice,pepoinfor);
		system("pause");//暂停 
		return;
	}
	if(choice==2)
	{
		printf("请输入身份证号：");
		scanf("%s",IDcard);
		pepole_print(choice,pepoinfor);
		system("pause");//暂停 
		return;
	}
	else
	{
		printf("输入错误！\n");
		system("pause");//暂停 
		return;
	} 
}

//收支查找模块 
void money_search()
{
	system("cls");//清屏
	money *p2=NULL;
	int choice,type;
	char moneyinfor[20];
	printf("1.按姓名；2.按类型："); 
	scanf("%d",&choice);
	if(choice==1)
	{
		printf("请输入姓名：");
		scanf("%s",moneyinfor);
		money_print(choice,moneyinfor);
		system("pause");//暂停 
		return;
	}
	if(choice==2)
	{
		printf("请输入类型(收入为1，支出为0)：");
		scanf("%d",&type);
		//将整数（type）转为数组（由第二个参数确定），第三个数为待转数的进制 
		itoa(type,moneyinfor,10);
		money_print(choice,moneyinfor);
		system("pause");//暂停 
		return;
	}
	else
	{
		printf("输入错误！\n");
		system("pause");//暂停 
		return;
	} 
	 
}

//人口输出信息（查找，或者所有），当choice为1则pepoinfor是姓名，当choice为2则pepoinfor是身份证 
void pepole_print(int choice,const char pepoinfor[20])//前面加上 const 关键字表示这个指针所指向的数据（即字符串的内容）是常量，不能通过该指针修改。
{
	
	pepole *p1=head1;
    if(!head1)
    { 
    	printf("当前没有信息！\n");
    	system("pause");//暂停 
		return;
	}
	system("cls");//清屏
	printf("|======================================================================================================================|\n");
	printf("|  栋  |  单元  |  楼层  |  号数  |  家庭成员姓名  |  年龄  |  是否有经济来源  |  家庭人口数  |  身份证  |   联系电话  |\n");
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
	system("pause");//暂停 
}

//输出信息（查找，或者所有），当choice为1则pepoinfor是姓名，当choice为2则pepoinfor是类型
void money_print(int choice,const char moneyinfor[20])//前面加上 const 关键字表示这个指针所指向的数据（即字符串的内容）是常量，不能通过该指针修改。
{
	money *p2=head2;
	float income=0.0;
	float outgoing=0.0;
	float balance=0.0;
    if(!head2)
    { 
    	printf("当前没有信息！\n");
    	system("pause");//暂停 
		return;
	}
	system("cls");//清屏
	printf("|======================================================================================================================|\n");
	printf("|\t年\t|\t月\t|\t日\t|\t金额\t  |\t使用人\t   |   \t  状态\t   |\t   事项\t       |\n");
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
	printf("总收入: %.1f\n", income);
    printf("总支出: %.1f\n", outgoing);
    printf("净收入(收入-支出): %.1f\n", income-outgoing);
	system("pause");//暂停 
}

//人口删除模块 
void pepole_del()
{
	pepole *p1=head1;
	pepole *prev1=head1;
	char name[20];//使用人
	int choice;
	char IDcard[20];//ID
	system("cls");//清屏 
	
	if(!head1)
    {
    	printf("当前没有信息！\n");
    	system("pause"); // 暂停以便用户阅读消息
    	return;
	}
	
	printf("请输入姓名：");
	scanf("%s",name);
	printf("请输入身份证号：");
	scanf("%s",IDcard);
	
	for(;p1!=NULL;prev1=p1,p1=p1->next)
	{
		if(strcmp(p1->name,name)==0 && strcmp(p1->IDcard, IDcard) == 0)
		{
			printf("   %d       %d        %d       %d          %s         %d            %s               %d  %s %s\n",p1->building,p1->unit,p1->floor,p1->num,p1->name,p1->age,p1->judge,p1->peponum,p1->IDcard,p1->telephonenumber);
			printf("你是否要删除(1删除，0不删除)：");
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
				printf("删除成功！\n");
				save1();
				break;	
			}
			else
			{
				printf("不删除！\n");
				system("pause");
				return;
			}
		}
	}
	if(p1==NULL)
	{
		printf("未找到！\n");
		system("pause");
		return;
	}
 } 

//收支删除模块 
void money_del()
{
	money *p2=head2;
	money *prev2=head2;
	char name[20];//使用人
	int choice;
	float amount;//金额
	system("cls");//清屏 
	
	if(!head2)
    {
    	printf("当前没有信息！\n");
    	system("pause"); // 暂停以便用户阅读消息
    	return;
	}
	printf("请输入姓名：");
	scanf("%s",name);
	printf("请输入金额：");
	scanf("%f",&amount);
	
	for(;p2!=NULL;prev2=p2,p2=p2->next)
	{
		if(strcmp(p2->name,name)==0 && p2->amount==amount)
		{
			printf("       %d \t\t%d \t\t%d\t\t%.1f\t\t%s\t\t   %d\t\t   %s\t\t\n",p2->year,p2->month,p2->day,p2->amount,p2->name,p2->type,p2->comment);
			printf("你是否要删除(1删除，0不删除)：");
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
				printf("删除成功！\n");
				save2();
				break;	
			}
			else
			{
				printf("不删除！\n");
				system("pause");
				return;
			}
		}
	}
	if(p2==NULL)
	{
		printf("未找到！\n");
		system("pause");
		return;
	}
} 
 
//人口修改模块
void pepole_edit()
{
    pepole *p1=head1;
    int choice; 
    char name[20]; // 使用人
    char IDcard[20];//ID
    system("cls"); // 清屏 

    printf("请输入姓名：");
    scanf("%s",name);
    printf("请输入身份证号：");
    scanf("%s",IDcard);

    for (;p1!=NULL;p1=p1->next)
    {
        if (strcmp(p1->name,name)==0 && strcmp(p1->IDcard,IDcard)==0)
        {
            // 显示当前信息
            printf("   %d       %d        %d       %d          %s         %d            %s               %d  %s %s\n",p1->building,p1->unit,p1->floor,p1->num,p1->name,p1->age,p1->judge,p1->peponum,p1->IDcard,p1->telephonenumber);
            printf("请确认是否修改此条记录(1 确认，0 取消)：");
            scanf("%d", &choice);
            if (choice == 1)
            {
                // 获取新信息
                printf("请输入栋（当前：%d）：",p1->building); 
				scanf("%d",&p1->building);
				printf("请输入单元（当前：%d）：",p1->unit); 
				scanf("%d",&p1->unit);
				printf("请输入楼层（当前：%d）：",p1->floor); 
				scanf("%d",&p1->floor);
				printf("请输入号数（当前：%d）：",p1->num); 
				scanf("%d",&p1->num);
				printf("请输入家庭成员姓名（当前：%s）：",p1->name); 
				scanf("%s",p1->name);
				printf("请输入年龄（当前：%d）：",p1->age); 
				scanf("%d",&p1->age);
				printf("请输入是否有经济来源（当前：%s）：",p1->judge); 
				scanf("%s",p1->judge);
				printf("请输入家庭人口数（当前：%d）：",p1->peponum); 
				scanf("%d",&p1->peponum);
				printf("请输入电话号码（当前：%s）：",p1->telephonenumber); 
				scanf("%s",p1->telephonenumber);

                // 保存更改
				printf("修改成功！\n");
                save1();
                return;
            }
            else
            {
                printf("取消修改。\n");
                system("pause");
                return;
            }
        }
    }
    printf("未找到匹配记录。\n");
    system("pause"); // 暂停以便用户阅读消息
}

//收支修改模块 
void money_edit()
{
    money *p2=head2;
    int choice; 
    char name[20]; // 使用人
    float amount;  // 金额
    system("cls"); // 清屏 

    printf("请输入姓名：");
    scanf("%s", name);
    printf("请输入金额：");
    scanf("%f", &amount);

    for (;p2!=NULL;p2=p2->next)
    {
        if (strcmp(p2->name,name)==0 && p2->amount == amount)
        {
            // 显示当前信息
            printf("       %d \t\t%d \t\t%d\t\t%.1f\t\t%s\t\t   %d\t\t   %s\t\t\n",p2->year,p2->month,p2->day,p2->amount,p2->name,p2->type,p2->comment);
            printf("请确认是否修改此条记录(1 确认，0 取消)：");
            scanf("%d", &choice);
            if (choice == 1)
            {
                // 获取新信息
                printf("请输入年份（当前：%d）：", p2->year);
                scanf("%d", &p2->year);
                printf("请输入月份（当前：%d）：", p2->month);
                scanf("%d", &p2->month);
                printf("请输入日期（当前：%d）：", p2->day);
                scanf("%d", &p2->day);
                printf("请输入金额（当前：%.1f）：", p2->amount);
                scanf("%f", &p2->amount);
                printf("请输入姓名（当前：%s）：", p2->name);
                scanf("%s", p2->name);
                printf("请输入类型(收入为1，支出为0)（当前：%d）：", p2->type);
                scanf("%d", &p2->type);
                printf("请输入事项（当前：%s）：", p2->comment);
                scanf(" %s", p2->comment);

                // 保存更改 
				printf("修改成功！\n");
                save2();
                return;
            }
            else
            {
                printf("取消修改。\n");
                system("pause");
                return;
            }
        }
    }
    printf("未找到匹配记录。\n");
    system("pause"); // 暂停以便用户阅读消息
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
