#include <iostream>
#include <string>
#include "AuthManager.h"
#include "MessageService.h"

using namespace std;


static void showMenu()
{
    cout << "1.  Регистрация \n";
    cout << "2.  Вход \n";
    cout << "3.  Отправить личное сообщение \n";
    cout << "4.  Отправить сообщение всем \n";
    cout << "5.  Показать мои сообщения \n";
    cout << "6.  Список пользователей \n";
    cout << "7.  Очистить мои сообщения \n";
    cout << "8.  Выход \n";
    cout << "Выберите опцию: ";
}


int main()
{
    setlocale(LC_ALL, "RU");

    AuthManager authManager;
    MessageService messageService(authManager);
    User* currentUser = nullptr;

    int choice;

    string username, password, recipient, message;

    cout << "Добро пожаловать в чат! \n\n";
    cout << "Предустановленные пользователи: \n";
    cout << "- admin / admin123 \n";
    cout << "- user1 / password1 \n";
    cout << "- user2 / password2 \n\n";

    do
    {
        if (currentUser)
        {
            cout << "\n Текущий пользователь: " << currentUser->getUsername() << "\n";
        }

        showMenu();
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            system("cls");
            cout << "Введите имя пользователя: ";
            getline(cin, username);
            cout << "Введите пароль: ";
            getline(cin, password);

            if (authManager.registerUser(username, password))
            {
                system("cls");
                cout << "Регистрация успешна! \n";
                cin.get();
                system("cls");
            }
            else
            {
                system("cls");
                cout << " Пользователь уже существует! \n";
                cin.get();
                system("cls");
            }
            break;
        }

        case 2:
        {
            system("cls");

            cout << "Введите имя пользователя: ";
            getline(cin, username);
            cout << "Введите пароль: ";
            getline(cin, password);

            currentUser = authManager.login(username, password);
            if (currentUser)
            {
                system("cls");
                cout << " Успешно! Добро пожаловать, " << username << "!\n";
                cin.ignore();
                system("cls");
            }
            else
            {
                system("cls");
                cout << " Неверные учетные данные! \n Нажимите любую кнопку чтобы продолжить или начать заново...";
                cin.ignore();
                system("cls");
            }
            system("cls");
            break;
        }

        case 3:
        {
            if (!currentUser)
            {
                system("cls");
                cout << " Сначала войдите в систему! \n Нажимите любую кнопку чтобы продолжить или начать заново...";
                cin.ignore();
                system("cls");
                break;
            }
            system("cls");
            cout << "Введите получателя: ";
            getline(cin, recipient);
            cout << "Введите сообщение: ";
            getline(cin, message);

            messageService.sendPrivateMessage(currentUser->getUsername(), recipient, message);
            cin.get();
            system("cls");
            break;
        }

        case 4:
        {
            if (!currentUser)
            {
                system("cls");
                cout << " Сначала войдите в систему! \n Нажимите любую кнопку чтобы продолжить или начать заново...";
                cin.ignore();
                system("cls");
                break;
            }
            system("cls");

            cout << "Введите сообщение для всех: ";
            getline(cin, message);

            messageService.broadcastMessage(currentUser->getUsername(), message);
            cin.get();
            system("cls");
            break;
        }

        case 5:
        {
            if (!currentUser)
            {
                system("cls");
                cout << " Сначала войдите в систему! \n Нажимите любую кнопку чтобы продолжить или начать заново...";
                cin.ignore();
                system("cls");
                break;
            }
            system("cls");
            cout << "\n Ваши сообщения \n";
            auto messages = currentUser->getMessages();
            cin.ignore();
            
            if (messages.empty())
            {
                cout << "У вас нет сообщений \n";
            }
            else
            {
                for (size_t i = 0; i < messages.size(); i++)
                {
                    cout << (i + 1) << ". " << messages[i] << "\n";
                }
            }
            cin.get();
            system("cls");
            break;
        }

        case 6:
        {
            system("cls");
            authManager.listUsers();
            cout << "Нажимите любую кнопку чтобы продолжить или начать заново... ";
            cin.ignore();
            system("cls");
            break;
        }

        case 7:
        {
            if (!currentUser)
            {
                {
                    system("cls");
                    cout << " Сначала войдите в систему!\n Нажимите любую кнопку чтобы продолжить или начать заново... ";
                    cin.ignore();
                    system("cls");
                    break;
                }
            }
            currentUser->clearMessages();
            system("cls");
            cout << " Сообщения очищены \n Нажимите любую кнопку чтобы продолжить или начать заново...";
            cin.ignore();
            system("cls");
            break;
        }

        case 8:
        {
            system("cls");
            cout << "  Выход из системы... \n Нажимите любую кнопку чтобы продолжить или начать заново...";
            cin.ignore();
            system("cls");
            break;
        }

        default:
        {
            system("cls");
            cout << " Неверный выбор! \n Нажимите любую кнопку чтобы продолжить или начать заново...";
            cin.ignore();
            system("cls");
        }
        }
    }
    while (choice != 8);

    return 0;
}