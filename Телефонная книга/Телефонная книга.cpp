//Создайте приложение "Телефонная книга".Необходимо
//хранить данные об абоненте(ФИО, домашний телефон,
//рабочий телефон, мобильный телефон, дополнительная
//информация о контакте) внутри соответствующего класса.
//Наполните класс переменными - членами, функциями - членами,
//конструкторами, inline - функциями - членами,
//используйте инициализаторы, реализуйте деструктор.
//Обязательно необходимо выделять динамически память
//под ФИО.Предоставьте пользователю возможность добавлять новых
//абонентов, удалять абонентов, искать абонентов по ФИО,
//показывать всех абонентов, сохранять
//информацию в файл и загружать из файла

#include <iostream>


// не смог осуществить коректную запись и чтение из файла

class Phone_book
{
    unsigned int size{};
    char* name{};
    std::string m_phone;
    std::string h_phone;
    std::string w_phone;
    int age{};


public:

    Phone_book() : size{ 100 }, name{ new char[size] {} } {}

    Phone_book(const char* name, std::string m_phone, std::string h_phone,
        std::string w_phone, int age) :
        size{ (unsigned int)(strlen(name) + 1) },
        name{ new char[strlen(name) + 1] {} },
        m_phone{ m_phone }, h_phone{ h_phone },
        w_phone{ w_phone }, age{ age }
    {
        strcpy_s(this->name, size, name);
    }
    Phone_book& operator = (const Phone_book& c)
    {
        size = c.size;
        name = new char[size + 1];
        strcpy_s(name, size, c.name);
        m_phone = c.m_phone;
        h_phone = c.h_phone;
        w_phone = c.w_phone;
        age = c.age;

        return *this;
    }
    ~Phone_book()
    {
        delete[]name;
    }
    void setName(const char* name)
    {
        delete[] this->name;

        this->name = new char[strlen(name) + 1]{};

        strcpy_s(this->name, strlen(name) + 1, name);
    }
    const char* getName() const
    {
        return name;
    }
    void setM_phone(std::string m_phone)
    {
        this->m_phone = m_phone;
    }
    std::string getM_phone() const
    {
        return m_phone;
    }
    void setH_phone(std::string h_phone)
    {
        this->h_phone = h_phone;
    }
    std::string getH_phone() const
    {
        return h_phone;
    }
    void setW_phone(std::string w_phone)
    {
        this->w_phone = w_phone;
    }
    std::string getW_phone() const
    {
        return w_phone;
    }
    void setAge(int age)
    {
        this->age = age;
    }
    int getAge() const
    {
        return age;
    }
    int getSize() const
    {
        return size;
    }
    void print() const;
    void enter_book();
    void read_book(const char*, Phone_book*&, int&);
    void save_book(const char*, const Phone_book*, int);
};
void print(Phone_book*, int);
Phone_book* addition(Phone_book*, int&);
Phone_book* delete_ab(Phone_book*, int&);
void search_name(const Phone_book*, int);
void menu(Phone_book*&, int&);


void Phone_book::print() const
{
    std::cout << "Ф.И.О.: " << name << "\n";
    std::cout << "Номер моб.: " << m_phone << "\n";
    std::cout << "Номер дом.: " << h_phone << "\n";
    std::cout << "Номер раб.: " << w_phone << "\n";
    std::cout << "Возраст: " << age << "\n\n";
}
void Phone_book::enter_book()
{
    std::cout << "Введите Ф.И.О.: ";
    std::cin.ignore();
    std::cin.getline(name, size);
    std::cout << "Введите мобильный тел.: ";
    std::cin >> m_phone;
    std::cout << "Введите домашний тел.: ";
    std::cin >> h_phone;
    std::cout << "Введит рабочий тел.: ";
    std::cin >> w_phone;
    std::cout << "Введите возраст абонента: ";
    std::cin >> age;
}
void print(Phone_book* p, int size)
{
    std::cout << "\t\tВесь список абонентов.\n\n";

    for (int i{}; i < size; ++i)
    {
        std::cout << (i + 1) << ". ";
        p[i].print();
    }
}
Phone_book* addition(Phone_book* p, int& size1)
{
    int a{};

    std::cout << "Сколько абонентов хотите добавить?: ";
    std::cin >> a;
    std::cout << "\n";

    int new_size = size1 + a;

    Phone_book* ptr = new Phone_book[new_size]{};

    int i{};

    for (; i < size1; ++i)
    {
        ptr[i] = p[i];
    }
    for (int j{ i }; j < new_size; ++j)
    {
        ptr[j].enter_book();

        std::cout << "\n";
    }
    delete[]p;

    size1 = new_size;

    return ptr;
}
Phone_book* delete_ab(Phone_book* p, int& size1)
{
    int a{};

    print(p, size1);

    if (size1 == 0)
    {
        std::cout << "Удалять некого.";
        return 0;
    }
    std::cout << "Под каким номером удаляем абонента?: ";
    std::cin >> a;

    int new_size = size1 - 1;

    Phone_book* ptr = new Phone_book[new_size]{};

    for (int i{}, j{}; i < size1; ++i)
    {
        if (a - 1 != i)
        {
            ptr[j] = p[i];

            ++j;
        }
    }
    delete[]p;

    size1 = new_size;

    return ptr;
}
void search_name(const Phone_book* p, int size1)
{
    std::string a{};
    int count{};

    std::cout << "Введите Ф.И.О. кого ищем: ";
    std::cin >> a;
    std::cout << "\n";

    for (int i{}; i < size1; ++i)
    {
        if (p[i].getName() == a)
        {
            p[i].print();
            ++count;
        }
    }
    if (count == 0)
    {
        std::cout << "Такого абонента нет.";
    }
}
void menu(Phone_book*& p, int& size1)
{
    while (true)
    {
        int act{};

        std::cout << "1 - Добавить абонента.\n";
        std::cout << "2 - Удалить абонента.\n";
        std::cout << "3 - Поиск абонента по Ф.И.О.\n";
        std::cout << "4 - Показать всех абонентов.\n";
        std::cout << "0 - Выход.\n";
        std::cout << "Выберите один из пунктов: ";
        std::cin >> act;

        system("pause");
        system("cls");

        switch (act)
        {
        case 0:

            return;

        case 1:

            p = addition(p, size1);
            system("pause");
            system("cls");
            break;

        case 2:

            p = delete_ab(p, size1);
            system("pause");
            system("cls");
            break;

        case 3:

            search_name(p, size1);
            system("pause");
            system("cls");
            break;

        case 4:

            print(p, size1);
            system("pause");
            system("cls");
            break;
        }
    }
}
void Phone_book::read_book(const char* path, Phone_book*& p, int& size1)
{
    FILE* out;

    if (fopen_s(&out, path, "rb") != 0)
    {
        std::cout << "Файл не может быть открыт\n";
    }
    else
    {
        fread(&size1, sizeof(size1), 1, out);
        p = new Phone_book[size1];

        for (int i{}; i < size1; ++i)
        {
            fread(&(p[i].age), sizeof(int), 1, out);
            fread(&(p[i].name), sizeof(char), 1, out);

            int l;

            fread(&(l), sizeof(int), 1, out);
            char* buff = new char[l + 1]{};
            fread(buff, sizeof(char), 1, out);
            p[i].m_phone = buff;
            delete[]buff;

            fread(&(l), sizeof(int), 1, out);
            buff = new char[l + 1]{};
            fread(buff, sizeof(char), 1, out);
            p[i].h_phone = buff;
            delete[]buff;

            fread(&(l), sizeof(int), 1, out);
            buff = new char[l + 1]{};
            fread(buff, sizeof(char), 1, out);
            p[i].w_phone = buff;
            delete[]buff;
        }
        fclose(out);
    }
}
void Phone_book::save_book(const char* path, const Phone_book* p, int size1)
{
    FILE* in;

    if (fopen_s(&in, path, "wb") != 0)
    {
        std::cout << "Файл не может быть открыт\n";
    }
    else
    {
        fwrite(&size1, sizeof(size1), 1, in);

        for (int i{}; i < size1; ++i)
        {
            fwrite(&(p[i].age), sizeof(int), 1, in);
            fwrite(&(p[i].name), sizeof(char), 1, in);
            int l = p[i].m_phone.length();
            fwrite(&(l), sizeof(int), 1, in);
            fwrite(p[i].m_phone.c_str(), sizeof(char), 1, in);
            l = p[i].h_phone.length();
            fwrite(&(l), sizeof(int), 1, in);
            fwrite(p[i].h_phone.c_str(), sizeof(char), 1, in);
            l = p[i].w_phone.length();
            fwrite(&(l), sizeof(int), 1, in);
            fwrite(p[i].w_phone.c_str(), sizeof(char), 1, in);
        }
        fclose(in);
    }
}
int main()
{
    setlocale(LC_ALL, "ru");

    int size1{};
    const char path[]{ "book.txt" };

    Phone_book* p = new Phone_book[size1]
    {
        /*{"ss", "ww", "aa", "zz", 11},
        {"zz", "xx", "cc", "vv", 22}*/
    };
    Phone_book p1;

    p1.read_book(path, p, size1);
    menu(p, size1);
    p1.save_book(path, p, size1);

    delete[]p;

    return 0;
}

