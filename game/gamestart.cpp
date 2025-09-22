#include<iostream>
#include<string>
using namespace std;
bool Started = false;//游戏状态变量 
bool Key = false;
bool Usb = false;
bool Paper = false;
bool item = false;
string currentRoom = "central";
int wrongPasswordCount = 0;
//显示帮助信息 
void Help(){
	cout << "start - 开始游戏" << endl;
	cout << "go(left/right)往房间方向走" << endl;
	cout << "get(Key/Usb/Paper）收集道具" << endl;
	cout << "use(Usb) 使用道具打开逃生通道" << endl;
	cout << "look paper 查看纸条上的密码" << endl;
	cout << "inventory 查看背包物品" << endl;
	cout << "quit 退出游戏" << endl;
	
}
//显示背包 
void Inventory(){
	cout << "背包里面有......" << endl;
	if(Key){
		cout << "一把生锈的钥匙，似乎是用来打开什么的........" << endl;
	}
	if(Usb){
		cout << "一个闪着蓝光的u盘" << endl;
	}
	if(Paper){
		cout << "一张带有密码的纸条" << endl;
	}
	else{
		cout << "你的背包还没有这个道具" << endl;
	}
}
//当前场景描述 
	void Show() {
	if (currentRoom == "central"){
		cout << "你站在密室中央，左侧有一扇锁着的大门，右侧则是布满代码的显示屏" << endl;
	}
   else if (currentRoom == "control"){
	    cout << "你需要找到u盘并且获得打开逃生密道的密码" << endl;
    }
    else if (currentRoom == "escape"){
    	cout << "恭喜你来到逃生通道，成功逃出密室！！" << endl;
	}
}
//处理玩家指令 
void HandleCommand(string cmd){
	if (cmd == "start"){
		Started = true;
		cout << "游戏开始,请尽全力逃出这个密室吧" << endl;
		Show();
    }
    else if (!Started){
    	cout << "请先输入start开始游戏" << endl;
    	return;
	}
//跳转进入帮助页面 
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
					cout << "你进入了控制室" << endl; 
					Show();
				}else {
					cout << "此路不通，请找到钥匙打开控制室大门" << endl;
				}
			}
			else if(direction == "right"){
				cout << "此路不通，请找到关键道具！" << endl; 
			}
			else{
				cout << "此路不通！请输入正确方向left/right" << endl;
			}
	}
		else if(currentRoom == "control"){
			cout << "你已经位于控制室了，请找到密码打开逃出通道吧" << endl;
		}
}
//处理获取道具逻辑 
	else if (cmd.find("get ") == 0){
		string item = cmd.substr(4);
		
		if(currentRoom == "central" && item == "key"){
			if(!Key) {
				Key = true;
				cout << "你获得了一把生锈的钥匙，似乎是用来打开什么的......." << endl;
			}else {
				cout << "你已经拥有钥匙了" << endl;
				
			}
		}
	
		else if(currentRoom == "control" && item == "usb"){
		    if(!Usb) {
				Usb = true;
				cout << "你获得了u盘,可以用来取得纸条获得逃生通道的密码" << endl; 
			}
			else {
				cout << "你已经拥有u盘了" << endl;
			}
		}
		else if(currentRoom == "control" && item == "paper"){
			if(!Paper) {
				Paper = true;
				cout << "你获得了带有密码的纸条" << endl;
			}else {
				cout << "你已经拥有了纸条" << endl;
			}
		}
		else {
			cout << "这里什么都没有，再找找吧" << item << endl;
		}
		
	} 
//处理使用道具逻辑 
	else if (cmd.find("use ") == 0){
		string item = cmd.substr(4);
		
		if (item == "usb" && currentRoom == "control" && Usb){
//对于密码输入次数的限定 
			if (wrongPasswordCount >= 3){
				cout << "已经超过最大次数了！游戏失败！！！" << endl;
				return;
			}
			cout << "请输入4位密码" << endl;
			string password;
			cin >> password;
			if(password == "1024"){
				cout << "密码正确，恭喜你打开逃生通道" << endl;
				currentRoom = "escape";
				Show();
			}
			else{
				wrongPasswordCount++;
				cout << "密码错误，还剩" << 3 - wrongPasswordCount << "次机会" << endl;
				if (wrongPasswordCount >= 3){
				cout << "警报响起，任务失败" << endl;
				exit(0);
				} 
			}
		}
		else{
			cout << "这里不能使用道具，请前往controlRoom" << endl;
		}
	}
	else if (cmd.find("look ") == 0){
		string item = cmd.substr(5);
		
		if(item == "paper" && Paper){
			cout << "密码是：1024" << endl;
		}
		else{
			cout << "没有什么线索" << endl;
		}
	}
	else if (cmd == "quit"){
		cout << "退出游戏" << endl;
		exit(0);
	}
else{
	cout << "无效指令，请输入‘help’查看说明，寻求帮助" << endl; 
 }
}
int main(){	
    cout << "欢迎来到冒险逃生游戏" << endl;
    cout << "输入‘start’开始游戏" << endl;
	cout << "输入‘help’查看指令说明" << endl;
	cout << "输入‘quit’退出游戏" << endl; 
	
string input;//主输入循环 
while (true) {
	cout << "输入命令： " << endl;
	getline(cin, input);//读取输入 
	
	if(!input.empty()) {
		HandleCommand(input);//调用命令函数 
	}
}
	return 0;
}


