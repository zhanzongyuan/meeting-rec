#include<iostream>
#include<fstream>
#include<sstream>
#include<cstring>
#include<string>
#include<cmath>
#include<iomanip>
#include<conio.h>
#include<vector>
#include<iterator>

using namespace std;


//int main(); 

void initial();		//载入初始化数据 
void save_data(); 		//保存数据 

int m_get_order();		//获取主界面用户操作 
void m_print(int); 		//打印主界面

void log_desk();		// 登录界面 
int log_search(string, string); 		//搜索userlist里的相应用户
 
void register_desk();		// 注册界面 
bool register_legal(string);		//判断新账号的合法性 

void user_desk(int);		// 个人界面 
int user_get_order(int);		// 获取个人界面用户操作 

#include"user.h"		//包含全局变量userlist 

int main(){
	initial();
	
	int order;
	while ((order=m_get_order())!=2) {
		switch(order) {
			case 0:{		//登陆
			    system("cls"); 
				log_desk();
			    system("cls");
				break;
			}
			case 1:{		//注册新用户
			    system("cls");
				register_desk();
			    system("cls");
				break;
			}
		}
	}
	
	save_data();
	return 0;
} 


void initial(){		//#要加入判断读写异常的情况# 
	ifstream infile;
	infile.open("user_information.txt");
	
	if (infile.is_open()){
		infile>>u_num;
		for(int i = 0; i< u_num; i++){
			string id, code;
			int order, size;
			infile>>id>>code>>order>>size;
			
			User t(id, code);
			t.set_ord(order);
			
			for(int j = 0; j<size; j++){
				Rec t_rec;
				infile>>t_rec;
				t.reclist.push_back(t_rec);
			}
			
			userlist.push_back(t);
		}
		
		infile.close();
	}
	
}

void save_data(){
	ofstream outfile;
	outfile.open("user_information.txt");
	
	outfile<<u_num<<endl;
	
	for(vector<User>::iterator i = userlist.begin(); i!=userlist.end(); i++){
		vector<Rec> &t = i->reclist;
		outfile<<i->id<<" "<<i->code<<" "<<i->order<<" "<<t.size()<<endl;
		for(vector<Rec>::iterator j = t.begin(); j!=t.end();j++)
			outfile<<*j<<endl;
	}
	
	outfile.close();
}

int m_get_order(){
	char w_button=' ';
	int mark = 0;
	do {
		switch(w_button){
			case 72:{
				mark  = (mark-1)%3;
				if (mark<0) mark = 2;
				break;
			}
			case 80:{
				mark = (mark+1)%3;
				break;
			}
			case 13:{
				return mark;
				break;
			}
		}	
		system("cls");
		m_print(mark);
	} while (w_button=getch());
}

void m_print(int m){ 
	Time now_time;
	ostringstream s;
	s<<now_time;
    cout<<left<<setw(40)<<">主页"
    	<<right<<setw(40)<<s.str()+" "
		<<endl
  	    <<setfill('-')<<setw(80)<<"-"
		<<setfill(' ')
		<<endl;
	
	cout<<endl<<setw(28)<<" "<<"--=会议管理系统 ";
	switch(m){
		case 0:{ cout<<"^ｏ^"; break;}
		case 1:{ cout<<";)"; break;}
		case 2:{ cout<<"Ｔ^Ｔ"; break;}
	}
	cout<<" =--"<<endl<<endl<<endl;
	/*cout<<setw(23)<<" "
		<<setfill('+')<<setw(30)<<"+"
		<<setfill(' ')<<endl<<endl;*/ 
		
	string order_arr1[]={"     |登录|     ", "  |注册新用户|  ", "     |退出|     "};
	string order_arr2[]={"   |> 登录 <|   ", "|> 注册新用户 <|", "   |> 退出 <|   "};
	
	for (int i = 0; i < 3; i++)
		if (i == m){
			cout<<setw(30)<<" "
				<<order_arr2[i]<<endl<<endl;
		}
		else cout<<setw(30)<<" "
				 <<order_arr1[i]<<endl<<endl;

	cout<<endl
		<<setw(23)<<" "
		<<setfill('_')<<setw(30)<<"_"
		<<setfill(' ')<<endl;		
		
	cout<<setw(23)<<" "<<"注：按方向键移动选择，按Enter键确认操作"; 
}

void log_desk(){	
    Time now_time;
	ostringstream s;
	s<<now_time;
    cout<<left<<setw(40)<<">主页>登录"
    	<<right<<setw(40)<<s.str()+" " 
		<<endl 
    	<<setfill('-')<<setw(80)<<"-"
		<<setfill(' ')
		<<endl;

	cout<<endl<<setw(30)<<" "<<"--=登录系统账户 >_< =--"<<endl<<endl;
	
	string id, code;
	
	cout<<endl<<setw(23)<<" "<<"用户名: ";
	cin>>id;
	
	cout<<endl<<setw(23)<<" "<<"密码："; 
	cin>>code;
	
	int order;
	if ((order=log_search(id, code))!=-1) user_desk(order);
	else {
		//#提示用户名密码错误 # 
		return;
	} 
	
}

//在用户数据userlist里寻找匹配的用户 
int log_search(string id, string code){
	for(vector<User>::iterator i = userlist.begin(); i!=userlist.end(); i++)
		if (i->Log(id, code)) return int(i-userlist.begin());
	return -1;
}

void register_desk(){
    Time now_time;
	ostringstream s;
	s<<now_time;
    cout<<left<<setw(40)<<">主页>注册"
    	<<right<<setw(40)<<s.str()+" " 
		<<endl 
    	<<setfill('-')<<setw(80)<<"-"
		<<setfill(' ')
		<<endl;
    
	cout<<endl<<setw(30)<<" "<<"--=注册新用户 ^3^ =--"<<endl<<endl;
	
	string id, code;
	
	cout<<endl<<setw(23)<<" "<<"用户名: ";
	cin>>id;
	
	cout<<endl<<setw(23)<<" "<<"密码："; 
	cin>>code;
	
	if (register_legal(id)){
		User t_user(id, code);
		t_user.set_ord(u_num);
		u_num++;
		userlist.push_back(t_user);
	}
	else {
		//#显示用户名重复 # 
		return;
	}
	
}

bool register_legal(string id){
	for(vector<User>::iterator i = userlist.begin(); i!=userlist.end(); i++)
		if (i->Log_name(id)) return false;
	return true;
} 

void user_desk(int u_order){
	int order;
	while ((order=user_get_order(u_order))!=2) {
		switch(order) {
			case 0:{		//创建新会议记录 
			    system("cls"); 
				userlist[u_order].new_rec();
			    system("cls");
				break;
			}
			case 1:{		//查询会议记录 
			    system("cls");
				userlist[u_order].check_rec();
			    system("cls");
				break;
			}
		}
	}
}

int user_get_order(int u_order){
	char w_button=' ';
	int mark = 0;
	do {
		switch(w_button){
			case 72:{
				mark  = (mark-1)%3;
				if (mark<0) mark = 2;
				break;
			}
			case 80:{
				mark = (mark+1)%3;
				break;
			}
			case 13:{
				return mark;
				break;
			}
		}	
		system("cls");
		userlist[u_order].u_print(mark);
	} while (w_button=getch());
}


