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

message mssg[]={"����","����","��λ����","н������","ְ�����","��Ч����","Ӧ������","��������˰","ʵ������"};
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
	node *Blink;//ǰ 
	node *Flink;//�� 
};

void add(gz *zggz);
bool createNode(node **tnode,gz *zggz,size_t zggzLength);//���ݻش� ==�޸ĵ�ַ�ϵ�ֵ
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
//����ǿ����� 



void read()
{
	FILE *read,*end;
	read=fopen("gz.dat","rb");
	if(read == NULL)  /*���ļ�ʧ��*/
    {
        printf("�ļ���ʧ��!\n");
		printf("�������Ϣ�󱣴棬�ɵõ��ļ�!\n");
    }
    else
    {
		while(1)
		{
    	if(!feof(read))//����readֻ�����һ���ͷ 
		{
			//cout<<"n:"<<n<<endl;
			node *zggzN=new node;
			gz tmp;
			fread(&zggzN->zggzData,1,sizeof(gz),read);//�����β�ͣ���β��ʱ������һ��ָ���ȡ //��gz���棬����gz��ȡ //��Ϊ�ǵ�ַ����������ÿ�Σ���Ҫ��ַ 
			//end=read+1;
			tmp=zggzN->zggzData;//Ϊ�˱���ԭ�нṹ����΢���ӡ� 
			if(createNode(&zggzN,&tmp,sizeof(gz)))
			{
				if(linkNode(zggzN))
				{
					n++;
					//printf("��Ϣ�Ѿ�¼�롣\n");
				}
			}
		} 
		else
        break; 
    	}
	}
	if(n!=0)
	{
		n--;//������һ������� ���������� //���һ����ַ�����������ļ�����//���ÿ����õ�ַƫ�ƣ�+1������� 
		
		//ɾ��β�� 
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
    	printf("û����Ϣ���Ա���\n");
    	return ;
	}
	int i;
	FILE *write;
	if((write = fopen ("gz.dat", "wb"))==NULL)
    {
        printf("�޷����ļ�\n");
        exit(0);
    }
    
	while(p!=NULL)
	{
		if(fwrite(&p->zggzData,sizeof(gz),1,write)!=1)//fwrite(const void* buffer, size_t size, size_t count, FILE* stream);
        {
        	printf("�޷�д���ļ�\n");
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
	printf("����ɹ�\n");
    	//cout<<"i:"<<i<<endl;
    fclose (write);	
    	
}
float grsds(float n)//�����������˰����
{
	//int t[8]={25,150,450,3000,5000,6000��7000��8000};
 	//ȫ��Ӧ��˰���ö� 
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
		//printf("��������Ϣ�����š���������λ���ʡ�н�����ʡ�ְ���������Ч����\n");
		
		//scanf("%s%s%g%g%g%g",&(*zggz).gonghao,&(*zggz).name,&(*zggz).gangwei_gongzi,&(*zggz).xinji_gongzi,&(*zggz).zhiwujintie,&(*zggz).jixiao_gongzi);
    	//�涨��ʽ 
    	printf("��������Ϣ������\n");
    	scanf("%s",&(*zggz).gonghao);
    	//if(sizeof((*zggz).gonghao)==0) printf("�����빤��\n");
    	printf("��������Ϣ������\n");
    	scanf("%s",&(*zggz).name);
    	//if(sizeof((*zggz).name)==0) printf("����������\n");
    	printf("��������Ϣ����λ����\n");
    	scanf("%g",&(*zggz).gangwei_gongzi);
    	//if(sizeof((*zggz).gangwei_gongzi)==0) printf("�������λ����\n");
    	printf("��������Ϣ��н������\n");
    	scanf("%g",&(*zggz).xinji_gongzi);
    	//if(sizeof((*zggz).xinji_gongzi)==0) printf("������н������\n");
    	printf("��������Ϣ��ְ�����\n");
    	scanf("%g",&(*zggz).zhiwujintie);
    	//if(sizeof((*zggz).zhiwujintie)==0) printf("������ְ�����\n");
    	printf("��������Ϣ����Ч����\n");
    	scanf("%g",&(*zggz).jixiao_gongzi);
    	//if(sizeof((*zggz).jixiao_gongzi)==0) printf("�����뼨Ч����\n");
    	
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

bool createNode(node **tnode,gz *zggz,size_t zggzLength)//���ݻش� ==�޸ĵ�ַ�ϵ�ֵ 
{
	bool IsOK=false;
	*tnode =new node;
	if(*tnode!=NULL)
	{
		//���㣬��ʼ�� 
		memset(*tnode,0,sizeof(node));//��s�е�ǰλ�ú����n���ֽ� ��typedef unsigned int size_t ���� ch �滻������ s ��
		
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

void find()//Ҫ��Ҫ���ݻش��� 
{
	node *p=head;
	char gonghao[10];
	printf("��������Ϣ������\n"); 
	scanf("%s",&gonghao);
	while(p!=NULL)
	{
		if(strcmp(p->zggzData.gonghao,gonghao)==0)
		{
			//*tmp=p->zggzData;
				printf("��ѯ�ɹ�\n");
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
	printf("û����Ϣ\n");
}

void modify()
{
	node *p=head;
	char gonghao[10];
	printf("��������Ϣ������\n"); 
	scanf("%s",&gonghao);
	while(p!=NULL)
	{
		if(strcmp(p->zggzData.gonghao,gonghao)==0)
		{
			printf("��ѯ�ɹ�\n");
		//printf("��������Ϣ�����š���������λ���ʡ�н�����ʡ�ְ���������Ч����\n");
		//scanf("%s%s%f%f%f%f",&p->zggzData.gonghao,&p->zggzData.name,&p->zggzData.gangwei_gongzi,&p->zggzData.xinji_gongzi,&p->zggzData.zhiwujintie,&p->zggzData.jixiao_gongzi);
    	printf("��������Ϣ������\n");
    	scanf("%s",&p->zggzData.gonghao);
    	printf("��������Ϣ������\n");
    	scanf("%s",&p->zggzData.name);
    	printf("��������Ϣ����λ����\n");
    	scanf("%g",&p->zggzData.gangwei_gongzi);
    	printf("��������Ϣ��н������\n");
    	scanf("%g",&p->zggzData.xinji_gongzi);
    	printf("��������Ϣ��ְ�����\n");
    	scanf("%g",&p->zggzData.zhiwujintie);
    	printf("��������Ϣ����Ч����\n");
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
		printf("�޸ĳɹ�\n");
		return ;
		}
		p=p->Flink;//next 
	}
	printf("û����Ϣ\n");
}

void list()
{
	node *p=head;
	if(p==NULL)printf("û����Ϣ\n");
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
	node *Blink;//ǰ 
	node *Flink;//�� 
	*/
	char gonghao[10];
	printf("��������Ϣ������\n"); 
	scanf("%s",&gonghao);
	node *v1;
	v1=head;
	node* v2=NULL;//�� 
	while(v1!=NULL)//���� 
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
			printf("ɾ���ɹ���\n"); 
			n--;
			return ;
		}
		else
		{
			v1=v1->Flink;
		}
	}
	delete v1;
	printf("û����Ϣ\n");
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
	printf("1.��ѯ����\n2.�޸�����\n3.�������\n4.ɾ������\n5.��������\n6.�������\n7.�˳�����\n");
	//cout<<"n:"<<n<<endl;
	printf("������ѡ��\n");
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
					printf("��Ϣ�Ѿ���ӡ�\n");
				}
			}
			//system("cls");//ִ�к����֮��û����Ϣ�� 
			break;
		}
		case 4:del();/*system("cls")*/;break;
		case 5:write();break;
		case 6:list();break;
		case 7:flag=false;break;
		default:printf("����ѡ��\n");
	}
	}
	DestroyList();
	printf("�˳��ɹ�\n");
	return 0; 
}  
