#include <iostream>
#include <string>
#include "AuthManager.h"
#include "MessageService.h"

using namespace std;


void showMenu()
{
    cout << "\n===  Система сообщений ===\n";
    cout << "1.  Регистрация\n";
    cout << "2.  Вход\n";
    cout << "3.  Отправить личное сообщение\n";
    cout << "4.  Отправить сообщение всем\n";
    cout << "5.  Показать мои сообщения\n";
    cout << "6.  Список пользователей\n";
    cout << "7.  Очистить мои сообщения\n";
    cout << "8.  Выход\n";
    cout << "Выберите опцию: ";
}
string username, password, recipient, message;

int main()
{
    AuthManager authManager;
    MessageService messageService(authManager);
    User* currentUser = nullptr;

    int choice;
    

    cout << "Добро пожаловать в систему сообщений!\n";
    cout << "Предустановленные пользователи:\n";
    cout << "- admin / admin123\n";
    cout << "- user1 / password1\n";
    cout << "- user2 / password2\n";

    do
    {
        if (currentUser) 
        {
            cout << "\nТекущий пользователь: " << currentUser->getUsername() << "\n";
        }

        showMenu();
        cin >> choice;
        cin.ignore(); 
       
        switch (choice)
        {
        case 1: 
            cout << "Введите имя пользователя: ";
            getline(cin, username);
            cout << "Введите пароль: ";
            getline(cin, password);

            if (authManager.registerUser(username, password)) 
            {
                cout << " Регистрация успешна!\n";
            }
            else 
            {
                cout << " Пользователь уже существует!\n";
            }
            break;

        case 2: 
            cout << "Введите имя пользователя: ";
            getline(cin, username);
            cout << "Введите пароль: ";
            getline(cin, password);

            currentUser = authManager.login(username, password);
            if (currentUser) 
            {
                cout << " Вход выполнен успешно! Добро пожаловать, " << username << "!\n";
            }
            else 
            {
                cout << " Неверные учетные данные!\n";
            }
            break;

        case 3: 
            if (!currentUser)
            {
                cout << " Сначала войдите в систему!\n";
                break;
            }

            cout << "Введите получателя: ";
            getline(cin, recipient);
            cout << "Введите сообщение: ";
            getline(cin, message);

            messageService.sendPrivateMessage(currentUser->getUsername(), recipient, message);
            break;

        case 4: 
            if (!currentUser) 
            {
                cout << " Сначала войдите в систему!\n";
                break;
            }

            cout << "Введите сообщение для всех: ";
            getline(cin, message);

            messageService.broadcastMessage(currentUser->getUsername(), message);
            break;

        case 5: 
            if (!currentUser) 
            {
                cout << " Сначала войдите в систему!\n";
                break;
            }

            cout << "\n---  Ваши сообщения ---\n";
            auto messages = currentUser->getMessages();
            if (messages.empty()) 
            {
                cout << "У вас нет сообщений\n";
            }
            else {
                for (size_t i = 0; i < messages.size(); i++) 
                {
                    cout << (i + 1) << ". " << messages[i] << "\n";
                }
            }
            break;

        case 6: 
            authManager.listUsers();
            break;

        case 7: 
            if (!currentUser)
            {
                cout << " Сначала войдите в систему!\n";
                break;
            }
            currentUser->clearMessages();
            cout << " Сообщения очищены\n";
            break;

        case 8:
            cout << " Выход из системы...\n";
            break;

        default:
            cout << " Неверный выбор!\n";
        }
    } while (choice != 8);

    return 0;9
}