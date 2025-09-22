#include<iostream>
#include<string>
using namespace std;
bool Started = false;//��Ϸ״̬���� 
bool Key = false;
bool Usb = false;
bool Paper = false;
bool item = false;
string currentRoom = "central";
int wrongPasswordCount = 0;
//��ʾ������Ϣ 
void Help(){
	cout << "start - ��ʼ��Ϸ" << endl;
	cout << "go(left/right)�����䷽����" << endl;
	cout << "get(Key/Usb/Paper���ռ�����" << endl;
	cout << "use(Usb) ʹ�õ��ߴ�����ͨ��" << endl;
	cout << "look paper �鿴ֽ���ϵ�����" << endl;
	cout << "inventory �鿴������Ʒ" << endl;
	cout << "quit �˳���Ϸ" << endl;
	
}
//��ʾ���� 
void Inventory(){
	cout << "����������......" << endl;
	if(Key){
		cout << "һ�������Կ�ף��ƺ���������ʲô��........" << endl;
	}
	if(Usb){
		cout << "һ�����������u��" << endl;
	}
	if(Paper){
		cout << "һ�Ŵ��������ֽ��" << endl;
	}
	else{
		cout << "��ı�����û���������" << endl;
	}
}
//��ǰ�������� 
	void Show() {
	if (currentRoom == "central"){
		cout << "��վ���������룬�����һ�����ŵĴ��ţ��Ҳ����ǲ����������ʾ��" << endl;
	}
   else if (currentRoom == "control"){
	    cout << "����Ҫ�ҵ�u�̲��һ�ô������ܵ�������" << endl;
    }
    else if (currentRoom == "escape"){
    	cout << "��ϲ����������ͨ�����ɹ��ӳ����ң���" << endl;
	}
}
//�������ָ�� 
void HandleCommand(string cmd){
	if (cmd == "start"){
		Started = true;
		cout << "��Ϸ��ʼ,�뾡ȫ���ӳ�������Ұ�" << endl;
		Show();
    }
    else if (!Started){
    	cout << "��������start��ʼ��Ϸ" << endl;
    	return;
	}
//��ת�������ҳ�� 
	else if (cmd == "help"){
		Help();
	}
	else if (cmd == "inventory"){
		Inventory();
	}
	else if (cmd == "show"){
		Show();
	}
	else if (cmd.find("go ") == 0){
		string direction = cmd.substr(3);
		
		if(currentRoom == "central"){
		    if(direction == "left"){
				if(Key){
					currentRoom = "control";
					cout << "open door" << endl;
					cout << "������˿�����" << endl; 
					Show();
				}else {
					cout << "��·��ͨ�����ҵ�Կ�״򿪿����Ҵ���" << endl;
				}
			}
			else if(direction == "right"){
				cout << "��·��ͨ�����ҵ��ؼ����ߣ�" << endl; 
			}
			else{
				cout << "��·��ͨ����������ȷ����left/right" << endl;
			}
	}
		else if(currentRoom == "control"){
			cout << "���Ѿ�λ�ڿ������ˣ����ҵ�������ӳ�ͨ����" << endl;
		}
}
//�����ȡ�����߼� 
	else if (cmd.find("get ") == 0){
		string item = cmd.substr(4);
		
		if(currentRoom == "central" && item == "key"){
			if(!Key) {
				Key = true;
				cout << "������һ�������Կ�ף��ƺ���������ʲô��......." << endl;
			}else {
				cout << "���Ѿ�ӵ��Կ����" << endl;
				
			}
		}
	
		else if(currentRoom == "control" && item == "usb"){
		    if(!Usb) {
				Usb = true;
				cout << "������u��,��������ȡ��ֽ���������ͨ��������" << endl; 
			}
			else {
				cout << "���Ѿ�ӵ��u����" << endl;
			}
		}
		else if(currentRoom == "control" && item == "paper"){
			if(!Paper) {
				Paper = true;
				cout << "�����˴��������ֽ��" << endl;
			}else {
				cout << "���Ѿ�ӵ����ֽ��" << endl;
			}
		}
		else {
			cout << "����ʲô��û�У������Ұ�" << item << endl;
		}
		
	} 
//����ʹ�õ����߼� 
	else if (cmd.find("use ") == 0){
		string item = cmd.substr(4);
		
		if (item == "usb" && currentRoom == "control" && Usb){
//������������������޶� 
			if (wrongPasswordCount >= 3){
				cout << "�Ѿ������������ˣ���Ϸʧ�ܣ�����" << endl;
				return;
			}
			cout << "������4λ����" << endl;
			string password;
			cin >> password;
			if(password == "1024"){
				cout << "������ȷ����ϲ�������ͨ��" << endl;
				currentRoom = "escape";
				Show();
			}
			else{
				wrongPasswordCount++;
				cout << "������󣬻�ʣ" << 3 - wrongPasswordCount << "�λ���" << endl;
				if (wrongPasswordCount >= 3){
				cout << "������������ʧ��" << endl;
				exit(0);
				} 
			}
		}
		else{
			cout << "���ﲻ��ʹ�õ��ߣ���ǰ��controlRoom" << endl;
		}
	}
	else if (cmd.find("look ") == 0){
		string item = cmd.substr(5);
		
		if(item == "paper" && Paper){
			cout << "�����ǣ�1024" << endl;
		}
		else{
			cout << "û��ʲô����" << endl;
		}
	}
	else if (cmd == "quit"){
		cout << "�˳���Ϸ" << endl;
		exit(0);
	}
else{
	cout << "��Чָ������롮help���鿴˵����Ѱ�����" << endl; 
 }
}
int main(){	
    cout << "��ӭ����ð��������Ϸ" << endl;
    cout << "���롮start����ʼ��Ϸ" << endl;
	cout << "���롮help���鿴ָ��˵��" << endl;
	cout << "���롮quit���˳���Ϸ" << endl; 
	
string input;//������ѭ�� 
while (true) {
	cout << "������� " << endl;
	getline(cin, input);//��ȡ���� 
	
	if(!input.empty()) {
		HandleCommand(input);//��������� 
	}
}
	return 0;
}


