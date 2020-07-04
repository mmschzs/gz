//gz.h
#include<memory.h>
#include<math.h>
#include<string.h>
#include<stdio.h>
#include <fstream>
typedef struct
{
	char s[20];
}message;

message mssg[]={"工号","姓名","岗位工资","薪级工资","职务津贴","绩效工资","应发工资","个人所得税","实发工资"};
message mes[]={"gonghao","name","gangwei_gongzi","xinji_gongzi","zhiwujintie","jixiao_gongzi"};
int n=0;
struct gz
{
	char gonghao[10];
	char name[10];
	
	float gangwei_gongzi;
	float xinji_gongzi;
	float zhiwujintie;
	float jixiao_gongzi;
	
	float yingfa_gongzi;
	float gerensuodeshui;
	float shifa_gongzi;
};
struct node
{
    gz zggzData;
	node *Blink;//前 
	node *Flink;//后 
};

void add(gz *zggz);
bool createNode(node **tnode,gz *zggz,size_t zggzLength);//数据回传 ==修改地址上的值
bool linkNode(node *tnode);

void find(gz *tmp);
void modify();
void del();
void conclusionInfo();

void list();
void DestroyList();

void read();
void write();

//gz.cpp
//#include"gz.h"

node *head=NULL;
node *tail=NULL;
//这就是空链表 



void read()
{
	FILE *read,*end;
	read=fopen("gz.dat","rb");
	if(read == NULL)  /*打开文件失败*/
    {
        printf("文件打开失败!\n");
		printf("请添加信息后保存，可得到文件!\n");
    }
    else
    {
		while(1)
		{
    	if(!feof(read))//这里read只到最后一组的头 
		{
			//cout<<"n:"<<n<<endl;
			node *zggzN=new node;
			gz tmp;
			fread(&zggzN->zggzData,1,sizeof(gz),read);//不会过尾巴，到尾巴时，用上一个指针读取 //以gz保存，就以gz读取 //因为是地址操作，所以每次，都要换址 
			//end=read+1;
			tmp=zggzN->zggzData;//为了保存原有结构，稍微复杂。 
			if(createNode(&zggzN,&tmp,sizeof(gz)))
			{
				if(linkNode(zggzN))
				{
					n++;
					//printf("信息已经录入。\n");
				}
			}
		} 
		else
        break; 
    	}
	}
	if(n!=0)
	{
		n--;//还是有一组废数据 ，就这样吧 //最后一个地址，并不代表文件结束//觉得可以用地址偏移（+1）解决。 
		
		//删除尾巴 
		tail->Blink->Flink=NULL;
		tail=tail->Blink;
		
	}
    //cout<<"n:"<<n<<endl;
	fclose(read);
}

void write()
{
	//cout<<"n:"<<n<<endl;
	node *p=head;
    if(p==NULL)
    {
    	printf("没有信息可以保存\n");
    	return ;
	}
	int i;
	FILE *write;
	if((write = fopen ("gz.dat", "wb"))==NULL)
    {
        printf("无法打开文件\n");
        exit(0);
    }
    
	while(p!=NULL)
	{
		if(fwrite(&p->zggzData,sizeof(gz),1,write)!=1)//fwrite(const void* buffer, size_t size, size_t count, FILE* stream);
        {
        	printf("无法写入文件\n");
        	fclose (write);	
        	return ;
		}
		/* 
		printf("%s\t%s\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n",
		p->zggzData.gonghao,
    	p->zggzData.name,
    	p->zggzData.gangwei_gongzi,
    	p->zggzData.xinji_gongzi,
    	p->zggzData.zhiwujintie,
    	p->zggzData.jixiao_gongzi,
    	p->zggzData.yingfa_gongzi,
    	p->zggzData.gerensuodeshui,
    	p->zggzData.shifa_gongzi);
    	*/ 
		i++;
    	p=p->Flink;
	}
	printf("保存成功\n");
    	//cout<<"i:"<<i<<endl;
    fclose (write);	
    	
}
float grsds(float n)//计算个人所得税函数
{
	//int t[8]={25,150,450,3000,5000,6000，7000，8000};
 	//全月应纳税所得额 
 	float tax,k;
 	if(n<=500) 
 	{
 		k=5.00/100.00;
 		tax=n*k;
	}
 	
 	if(500<n&&n<=2000)
 	{
 	k=10.00/100.00;
 		tax=(n-500)*k+25;
	}
 	if(2000<n&&n<=5000)
 	{
 	k=15.00/100.00;
 		tax=(n-2000)*k+175;
	}
 	if(5000<n&&n<=20000)
 	{
 	k=20.00/100.00;
 		tax=(n-5000)*k+625;
	}
 	if(20000<n&&n<=40000)
 	{
 	k=25.00/100.00;
 		tax=(n-20000)*k+3625;
	}
 	if(40000<n&&n<=60000)
 	{
 	k=30.00/100.00;
 		tax=(n-40000)*k+8625;
	}
	if(60000<n&&n<=80000)
 	{
 	k=35.00/100.00;
 		tax=(n-60000)*k+14625;
	}
	if(80000<n&&n<=100000)
 	{
 	k=40.00/100.00;
 		tax=(n-80000)*k+21625;
	}
 	if(100000<n)
 	{
 	k=45.00/100.00;
 		tax=(n-100000)*k+29625;
	}
	//printf("%f\n",&tax);
	return tax;
} 

void add(gz *zggz)
{
		n++;
		//cout<<"n:"<<n<<endl;
		//printf("请输入信息：工号、姓名、岗位工资、薪级工资、职务津贴、绩效工资\n");
		
		//scanf("%s%s%g%g%g%g",&(*zggz).gonghao,&(*zggz).name,&(*zggz).gangwei_gongzi,&(*zggz).xinji_gongzi,&(*zggz).zhiwujintie,&(*zggz).jixiao_gongzi);
    	//规定格式 
    	printf("请输入信息：工号\n");
    	scanf("%s",&(*zggz).gonghao);
    	//if(sizeof((*zggz).gonghao)==0) printf("请输入工号\n");
    	printf("请输入信息：姓名\n");
    	scanf("%s",&(*zggz).name);
    	//if(sizeof((*zggz).name)==0) printf("请输入姓名\n");
    	printf("请输入信息：岗位工资\n");
    	scanf("%g",&(*zggz).gangwei_gongzi);
    	//if(sizeof((*zggz).gangwei_gongzi)==0) printf("请输入岗位工资\n");
    	printf("请输入信息：薪级工资\n");
    	scanf("%g",&(*zggz).xinji_gongzi);
    	//if(sizeof((*zggz).xinji_gongzi)==0) printf("请输入薪级工资\n");
    	printf("请输入信息：职务津贴\n");
    	scanf("%g",&(*zggz).zhiwujintie);
    	//if(sizeof((*zggz).zhiwujintie)==0) printf("请输入职务津贴\n");
    	printf("请输入信息：绩效工资\n");
    	scanf("%g",&(*zggz).jixiao_gongzi);
    	//if(sizeof((*zggz).jixiao_gongzi)==0) printf("请输入绩效工资\n");
    	
    	(*zggz).yingfa_gongzi=
		(*zggz).gangwei_gongzi+
    	(*zggz).xinji_gongzi+
    	(*zggz).zhiwujintie+
    	(*zggz).jixiao_gongzi;
    	
    	(*zggz).gerensuodeshui=grsds((*zggz).yingfa_gongzi);
    	
    	(*zggz).shifa_gongzi=
		(*zggz).yingfa_gongzi-
		(*zggz).gerensuodeshui;
}

bool createNode(node **tnode,gz *zggz,size_t zggzLength)//数据回传 ==修改地址上的值 
{
	bool IsOK=false;
	*tnode =new node;
	if(*tnode!=NULL)
	{
		//清零，初始化 
		memset(*tnode,0,sizeof(node));//将s中当前位置后面的n个字节 （typedef unsigned int size_t ）用 ch 替换并返回 s 。
		
		memcpy(&((*tnode)->zggzData),zggz,zggzLength);
		IsOK=true;
	}
	return IsOK;
} 

bool linkNode(node *tnode)
{
	if(tnode==NULL)
	{
		return false;
	}
	if(head==NULL)
	{
		head=tail=tnode;
	}
	else 
	{
		tail->Flink=tnode;
		tnode->Blink=tail;
		
		tail=tnode;
	}
	return true;
}

void find()//要不要数据回传？ 
{
	node *p=head;
	char gonghao[10];
	printf("请输入信息：工号\n"); 
	scanf("%s",&gonghao);
	while(p!=NULL)
	{
		if(strcmp(p->zggzData.gonghao,gonghao)==0)
		{
			//*tmp=p->zggzData;
				printf("查询成功\n");
			for(short i=0;i<sizeof(mssg)/sizeof(message);i++)
		printf("%10s\t",&mssg[i]);
		printf("\n");
		printf("%10s\t%10s\t%10g\t%10g\t%10g\t%10g\t%10g\t%10g\t%10g\t\n",
		p->zggzData.gonghao,
    	p->zggzData.name,
    	p->zggzData.gangwei_gongzi,
    	p->zggzData.xinji_gongzi,
    	p->zggzData.zhiwujintie,
    	p->zggzData.jixiao_gongzi,
    	p->zggzData.yingfa_gongzi,
    	p->zggzData.gerensuodeshui,
    	p->zggzData.shifa_gongzi);
		return ;
		}
		p=p->Flink;//next 
	}
	printf("没有信息\n");
}

void modify()
{
	node *p=head;
	char gonghao[10];
	printf("请输入信息：工号\n"); 
	scanf("%s",&gonghao);
	while(p!=NULL)
	{
		if(strcmp(p->zggzData.gonghao,gonghao)==0)
		{
			printf("查询成功\n");
		//printf("请输入信息：工号、姓名、岗位工资、薪级工资、职务津贴、绩效工资\n");
		//scanf("%s%s%f%f%f%f",&p->zggzData.gonghao,&p->zggzData.name,&p->zggzData.gangwei_gongzi,&p->zggzData.xinji_gongzi,&p->zggzData.zhiwujintie,&p->zggzData.jixiao_gongzi);
    	printf("请输入信息：工号\n");
    	scanf("%s",&p->zggzData.gonghao);
    	printf("请输入信息：姓名\n");
    	scanf("%s",&p->zggzData.name);
    	printf("请输入信息：岗位工资\n");
    	scanf("%g",&p->zggzData.gangwei_gongzi);
    	printf("请输入信息：薪级工资\n");
    	scanf("%g",&p->zggzData.xinji_gongzi);
    	printf("请输入信息：职务津贴\n");
    	scanf("%g",&p->zggzData.zhiwujintie);
    	printf("请输入信息：绩效工资\n");
    	scanf("%g",&p->zggzData.jixiao_gongzi);
    	p->zggzData.yingfa_gongzi=
		p->zggzData.gangwei_gongzi+
    	p->zggzData.xinji_gongzi+
    	p->zggzData.zhiwujintie+
    	p->zggzData.jixiao_gongzi;
    	
    	p->zggzData.gerensuodeshui=grsds(p->zggzData.yingfa_gongzi);
    	
    	p->zggzData.shifa_gongzi=
		p->zggzData.yingfa_gongzi-
		p->zggzData.gerensuodeshui;
		printf("修改成功\n");
		return ;
		}
		p=p->Flink;//next 
	}
	printf("没有信息\n");
}

void list()
{
	node *p=head;
	if(p==NULL)printf("没有信息\n");
	if(p!=NULL)
	{
		for(short i=0;i<sizeof(mssg)/sizeof(message);i++)
		printf("%10s\t",&mssg[i]);
		printf("\n");
	}
	
	while(p!=NULL)
	{
		printf("%10s\t%10s\t%10g\t%10g\t%10g\t%10g\t%10g\t%10g\t%10g\t\n",
		p->zggzData.gonghao,
    	p->zggzData.name,
    	p->zggzData.gangwei_gongzi,
    	p->zggzData.xinji_gongzi,
    	p->zggzData.zhiwujintie,
    	p->zggzData.jixiao_gongzi,
    	p->zggzData.yingfa_gongzi,
    	p->zggzData.gerensuodeshui,
    	p->zggzData.shifa_gongzi);
    	p=p->Flink;
	}
}

void del()
{
	/*
	node *Blink;//前 
	node *Flink;//后 
	*/
	char gonghao[10];
	printf("请输入信息：工号\n"); 
	scanf("%s",&gonghao);
	node *v1;
	v1=head;
	node* v2=NULL;//？ 
	while(v1!=NULL)//遍历 
	{
		if(strcmp(v1->zggzData.gonghao,gonghao)==0)
		{
			v2=v1->Flink;
			if(v1==head)
			{
					if(v2==NULL)
					{
						head=tail=NULL; 
					}
					else
					{
						v1->Flink->Blink=NULL;
						v1->Flink=NULL;
						head=v2; 
					} 
			}
			else if(v1==tail)
			{
				v1->Blink->Flink=NULL;
				tail=v1->Blink;
			}
			else 
			{
				v2=v1->Flink;
				v1->Blink->Flink=v1->Flink;
				v1->Flink->Blink=v1->Blink;
			}
			v1=NULL;
			printf("删除成功。\n"); 
			n--;
			return ;
		}
		else
		{
			v1=v1->Flink;
		}
	}
	delete v1;
	printf("没有信息\n");
}

void DestroyList()
{
	node *v1=head;
	node *v2=NULL;
	while(v1!=NULL)
	{
		v2=v1->Flink;
		delete v1;
		v1=v2;
	}
	head=tail=NULL;
	n=0;
}
//main
//#include"gz.h"
//#include"gz.cpp"
int main()
{
	read();
	int choice;
	bool flag=true;
	while(flag)
	{
	printf("1.查询命令\n2.修改命令\n3.添加命令\n4.删除命令\n5.保存命令\n6.浏览命令\n7.退出命令\n");
	//cout<<"n:"<<n<<endl;
	printf("请输入选择\n");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:find();break;
		case 2:
		{
			modify();
			break;
		}
		case 3:
		{
			node *zggzN;
			gz tmp;
			add(&tmp);
			if(createNode(&zggzN,&tmp,sizeof(gz)))
			{
				if(linkNode(zggzN))
				{
					printf("信息已经添加。\n");
				}
			}
			//system("cls");//执行后操作之后没有信息。 
			break;
		}
		case 4:del();/*system("cls")*/;break;
		case 5:write();break;
		case 6:list();break;
		case 7:flag=false;break;
		default:printf("错误选择\n");
	}
	}
	DestroyList();
	printf("退出成功\n");
	return 0; 
}  
