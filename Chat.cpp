#include "Chat.h"
using namespace std;
Chat::Chat() {};
//check user
bool Chat::parser(const char* mes)
{
	char name[20];
	char famil[20];
	char login[20];
	char pass[20];
	const char* str = strstr(mes, "_");
	if (str)
	{
		int size = strlen(mes) - strlen(str);
		strncpy(name, mes, size);
		name[size] = 0;
		str = str + 1;
		size = 0;
		const char* str1 = strstr(str, "_");
		if (str1)
		{
			size = strlen(str) - strlen(str1);
			strncpy(famil, str, size);
			famil[size] = 0;
			str1 = str1 + 1;
			size = 0;
			const char* str2 = strstr(str1, "_");
			if (str2)
			{
				size = strlen(str1) - strlen(str2);
				strncpy(login, str1, size);
				login[size] = 0;
				str2 = str2 + 1;
				size = 0;
				const char* str3 = strstr(str2, ";");
				if (str3)
				{
					size = strlen(str2) - strlen(str3);
					strncpy(pass, str2, size);
					pass[size] = 0;
				}
			}
			
		}
		
	}
	else
	{
		cout << "error" << endl;
	}
	if (check(name, famil, login, pass) == true)
	{
		return true;
	}
	
}
string Chat::get(const char* mes)
{
	char name[2500];
	const char* str = strstr(mes, "_");
	if (str)
	{
		int size = strlen(mes) - strlen(str);
		strncpy(name, mes, size);
		name[size] = 0;
	}
	return name;

}
void Chat::parser_mes(const char* mes)
{
	char name[20];
	char recieved[20];
	char text[2000];
	const char* str = strstr(mes, "_");
	if (str)
	{
		int size = strlen(mes) - strlen(str);
		strncpy(name, mes, size);
		name[size] = 0;
		str = str + 1;
		size = 0;
		const char* str1 = strstr(str, "_");
		if (str1)
		{
			size = strlen(str) - strlen(str1);
			strncpy(recieved, str, size);
			recieved[size] = 0;
			str1 = str1 + 1;
			size = 0;
			const char* str2 = strstr(str1, ";");
			if (str2)
			{
				size = strlen(str1) - strlen(str2);
				strncpy(text, str1, size);
				text[size] = 0;
			}
		}
	}
	send(name, recieved, text);

}
bool Chat::check(string name, string famil, string login, string pass)
{
    if (check_nick(name) == true)
    {
        if (check_login(login) == true)
        {
            if (check_pass(login, pass) == true)
            {
				return true;
            }
            else
            {
				return false;
            }
        }
        else
        {
			return false;
        }
    }
    else
    {
        reg(name, famil, login, pass);
		return true;
    }
}
//check nick
bool Chat::check_nick(string name)
{
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;
	string m_name;
	// Получаем дескриптор соединения
	mysql_init(&mysql);
	if (&mysql == nullptr) {
		// Если дескриптор не получен — выводим сообщение об ошибке
		cout << "Error: can't create MySQL-descriptor" << endl;
	}

	// Подключаемся к серверу
	if (!mysql_real_connect(&mysql, "localhost", "root", "12345", "sys", NULL, NULL, 0)) {
		// Если нет возможности установить соединение с БД выводим сообщение об ошибке
		cout << "Error: can't connect to database " << mysql_error(&mysql) << endl;
	}

	mysql_set_character_set(&mysql, "utf8");
	//Смотрим изменилась ли кодировка на нужную, по умолчанию идёт latin1
	//cout << "connection characterset: " << mysql_character_set_name(&mysql) << endl;
	mysql_query(&mysql, "SELECT * FROM users"); //Делаем запрос к таблице
	//Выводим все что есть в базе через цикл
	if (res = mysql_store_result(&mysql)) {
		while (row = mysql_fetch_row(res)) {
			m_name = row[1];
			if (m_name == name)
			{
				// Закрываем соединение с сервером базы данных
				mysql_close(&mysql);
				return true;
			}
			else
				continue;
		}
	}
	else
	{
		// Закрываем соединение с сервером базы данных
		mysql_close(&mysql);
		return false;
	}
		

}
//check login
bool Chat::check_login(string login)
{
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;
	string m_login;
	// Получаем дескриптор соединения
	mysql_init(&mysql);
	if (&mysql == nullptr) {
		// Если дескриптор не получен — выводим сообщение об ошибке
		cout << "Error: can't create MySQL-descriptor" << endl;
	}

	// Подключаемся к серверу
	if (!mysql_real_connect(&mysql, "localhost", "root", "12345", "sys", NULL, NULL, 0)) {
		// Если нет возможности установить соединение с БД выводим сообщение об ошибке
		cout << "Error: can't connect to database " << mysql_error(&mysql) << endl;
	}

	mysql_set_character_set(&mysql, "utf8");
	//Смотрим изменилась ли кодировка на нужную, по умолчанию идёт latin1
	//cout << "connection characterset: " << mysql_character_set_name(&mysql) << endl;
	mysql_query(&mysql, "SELECT * FROM users"); //Делаем запрос к таблице
	//Выводим все что есть в базе через цикл
	if (res = mysql_store_result(&mysql)) {
		while (row = mysql_fetch_row(res)) {
			m_login = row[3];
			if (m_login == login)
			{
				mysql_close(&mysql);
				return true;
			}
			else
				continue;
		}
	}
	else
	{
		// Закрываем соединение с сервером базы данных
		mysql_close(&mysql);
		return false;
	}
}
//check pass
bool Chat::check_pass(string login, string pass)
{
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;
	string m_login;
	string m_pass;
	// Получаем дескриптор соединения
	mysql_init(&mysql);
	if (&mysql == nullptr) {
		// Если дескриптор не получен — выводим сообщение об ошибке
		cout << "Error: can't create MySQL-descriptor" << endl;
	}

	// Подключаемся к серверу
	if (!mysql_real_connect(&mysql, "localhost", "root", "12345", "sys", NULL, NULL, 0)) {
		// Если нет возможности установить соединение с БД выводим сообщение об ошибке
		cout << "Error: can't connect to database " << mysql_error(&mysql) << endl;
	}

	mysql_set_character_set(&mysql, "utf8");
	//Смотрим изменилась ли кодировка на нужную, по умолчанию идёт latin1
	//cout << "connection characterset: " << mysql_character_set_name(&mysql) << endl;
	mysql_query(&mysql, "SELECT * FROM users"); //Делаем запрос к таблице
	//Выводим все что есть в базе через цикл
	if (res = mysql_store_result(&mysql)) {
		while (row = mysql_fetch_row(res)) {
			m_login = row[3];
			if (m_login == login)
			{
				m_pass = row[4];
				if (m_pass == pass)
				{
					mysql_close(&mysql);
					return true;
				}
			}
			else
				continue;
		}
	}
	else
	{
		// Закрываем соединение с сервером базы данных
		mysql_close(&mysql);
		return false;
	}
}
//registration
void Chat::reg(string name, string famil, string login, string pass)
{
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;

	int i = 0;

	// Получаем дескриптор соединения
	mysql_init(&mysql);
	if (&mysql == nullptr) {
		// Если дескриптор не получен — выводим сообщение об ошибке
		cout << "Error: can't create MySQL-descriptor" << endl;
	}

	// Подключаемся к серверу
	if (!mysql_real_connect(&mysql, "localhost", "root", "12345", "sys", NULL, NULL, 0)) {
		// Если нет возможности установить соединение с БД выводим сообщение об ошибке
		cout << "Error: can't connect to database " << mysql_error(&mysql) << endl;
	}
	else {
		// Если соединение успешно установлено выводим фразу — "Success!"
		cout << "Success!" << endl;
	}


	mysql_set_character_set(&mysql, "utf8");
	int n = 0;
	mysql_query(&mysql, "SELECT * FROM users"); //Делаем запрос к таблице
	if (res = mysql_store_result(&mysql))
	{
		n = mysql_num_rows(res);
	}
	n = n + 1;
	cout << "Count: " << n << endl;
	string str_n = to_string(n);
	str_n = str_n + " ";
	string s = "', '";
	string s1 = "')";
	string str = "INSERT INTO users(id, name, famil, login, pass) values('" + str_n + s + name + s + famil + s + login + s + pass + s1;

	mysql_query(&mysql, str.c_str()); //Делаем запрос к таблице

	// Закрываем соединение с сервером базы данных
	mysql_close(&mysql);

}
//print
string Chat::print()
{
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;

	int i = 0;

	// Получаем дескриптор соединения
	mysql_init(&mysql);
	if (&mysql == nullptr) {
		// Если дескриптор не получен — выводим сообщение об ошибке
		cout << "Error: can't create MySQL-descriptor" << endl;
	}

	// Подключаемся к серверу
	if (!mysql_real_connect(&mysql, "localhost", "root", "12345", "sys", NULL, NULL, 0)) {
		// Если нет возможности установить соединение с БД выводим сообщение об ошибке
		cout << "Error: can't connect to database " << mysql_error(&mysql) << endl;
	}
	
	string users;
	mysql_set_character_set(&mysql, "utf8");
	mysql_query(&mysql, "SELECT * FROM users"); //Делаем запрос к таблице
	//Выводим все что есть в базе через цикл
	if (res = mysql_store_result(&mysql)) {
		while (row = mysql_fetch_row(res)) {
			users.append(row[1]);
			users.append(" ");
		}
	}
	else
		cout << "Ошибка MySql номер " << mysql_error(&mysql);

	return users;
	mysql_close(&mysql);
}
string Chat::id(string name)
{
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;
	string m_name;
	int n;
	// Получаем дескриптор соединения
	mysql_init(&mysql);
	if (&mysql == nullptr) {
		// Если дескриптор не получен — выводим сообщение об ошибке
		cout << "Error: can't create MySQL-descriptor" << endl;
	}

	// Подключаемся к серверу
	if (!mysql_real_connect(&mysql, "localhost", "root", "12345", "sys", NULL, NULL, 0)) {
		// Если нет возможности установить соединение с БД выводим сообщение об ошибке
		cout << "Error: can't connect to database " << mysql_error(&mysql) << endl;
	}
	string id;
	mysql_set_character_set(&mysql, "utf8");
	//Смотрим изменилась ли кодировка на нужную, по умолчанию идёт latin1
	//cout << "connection characterset: " << mysql_character_set_name(&mysql) << endl;
	mysql_query(&mysql, "SELECT * FROM users"); //Делаем запрос к таблице
	//Выводим все что есть в базе через цикл
	if (res = mysql_store_result(&mysql)) {
		while (row = mysql_fetch_row(res)) {
			m_name = row[1];
			if (m_name == name)
			{
				 id = row[0];
				 return id;
				// Закрываем соединение с сервером базы данных
				mysql_close(&mysql);
			}
			else
				continue;
		}
	}
	else
	{
		// Закрываем соединение с сервером базы данных
		mysql_close(&mysql);
		return "-1";
	}
}
string Chat::send(string sender, string recivered, string text)
{
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;


	// Получаем дескриптор соединения
	mysql_init(&mysql);
	if (&mysql == nullptr) {
		// Если дескриптор не получен — выводим сообщение об ошибке
		cout << "Error: can't create MySQL-descriptor" << endl;
	}

	// Подключаемся к серверу
	if (!mysql_real_connect(&mysql, "localhost", "root", "12345", "sys", NULL, NULL, 0)) {
		// Если нет возможности установить соединение с БД выводим сообщение об ошибке
		cout << "Error: can't connect to database " << mysql_error(&mysql) << endl;
	}
	else {
		// Если соединение успешно установлено выводим фразу — "Success!"
		cout << "Success!" << endl;
	}


	mysql_set_character_set(&mysql, "utf8");
	int n = 0;
	mysql_query(&mysql, "SELECT * FROM message"); //Делаем запрос к таблице
	if (res = mysql_store_result(&mysql))
	{
		n = mysql_num_rows(res);
	}
	n = n + 1;
	string str_n = to_string(n);
	str_n = str_n + " ";
	string s = "', '";
	string s1 = "')";
	string s2 = "', ";
	string idsender = id(sender);
	string idreciver = id(recivered);
	
		//string str = "INSERT INTO message(idmes, idsender, idrecivered, `text`, `DATE`, send, delivered) values(2, 1, 2, 'hello', CURRENT_TIMESTAMP, 0, '0')"; 
	string str1 = "INSERT INTO message(idmes, idsender, idrecivered, `text`, `DATE`, send, delivered) values(" + str_n + ", " + idsender + ", " + idreciver + ", '" + text + s2 + "CURRENT_TIMESTAMP" + ", " + to_string(0) + ", '" + "0" + s1;
	mysql_query(&mysql, str1.c_str()); //Делаем запрос к таблице
	// Закрываем соединение с сервером базы данных
	mysql_close(&mysql);
	return text;
}
string Chat::get_name(string id)
{
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;

	string str_id;
	string user;
	// Получаем дескриптор соединения
	mysql_init(&mysql);
	if (&mysql == nullptr) {
		// Если дескриптор не получен — выводим сообщение об ошибке
		cout << "Error: can't create MySQL-descriptor" << endl;
	}

	// Подключаемся к серверу
	if (!mysql_real_connect(&mysql, "localhost", "root", "12345", "sys", NULL, NULL, 0)) {
		// Если нет возможности установить соединение с БД выводим сообщение об ошибке
		cout << "Error: can't connect to database " << mysql_error(&mysql) << endl;
	}
	mysql_set_character_set(&mysql, "utf8");

	mysql_query(&mysql, "SELECT * FROM users"); //Делаем запрос к таблице
	if (res = mysql_store_result(&mysql)) {
		while (row = mysql_fetch_row(res)) {
			str_id = row[0];
			if (str_id == id)
			{
				user = row[1];
				// Закрываем соединение с сервером базы данных
				mysql_close(&mysql);
				return user;
			}
			else
				continue;
		}
	}
	else
	{
		// Закрываем соединение с сервером базы данных
		mysql_close(&mysql);
		cout << "error" << endl;
	}
}
string Chat::receive(string name)
{
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;


	// Получаем дескриптор соединения
	mysql_init(&mysql);
	if (&mysql == nullptr) {
		// Если дескриптор не получен — выводим сообщение об ошибке
		cout << "Error: can't create MySQL-descriptor" << endl;
	}

	// Подключаемся к серверу
	if (!mysql_real_connect(&mysql, "localhost", "root", "12345", "sys", NULL, NULL, 0)) {
		// Если нет возможности установить соединение с БД выводим сообщение об ошибке
		cout << "Error: can't connect to database " << mysql_error(&mysql) << endl;
	}
	

	string s_name = id (name);
	string m_name;
	string sender;
	string text;
	string date;
	mysql_set_character_set(&mysql, "utf8");
	
	mysql_query(&mysql, "SELECT * FROM message"); //Делаем запрос к таблице
	if (res = mysql_store_result(&mysql)) {
		while (row = mysql_fetch_row(res)) {
			m_name = row[2];
			if (m_name == s_name)
			{
				sender = get_name(row[1]);
				text = row[3];
				date = row[4];
				// Закрываем соединение с сервером базы данных
				mysql_close(&mysql);
				string ret = date + " " + sender + ": " + text;
				return ret;
			}
			else
				continue;
		}
	}
	else
	{
		// Закрываем соединение с сервером базы данных
		mysql_close(&mysql);
		cout << "no Message!" << endl;
	}
}