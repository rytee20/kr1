#include <iostream>

using namespace std;

template<class Type>
class OurVector {

private:
    long size;                                                             //размер массива
    long count;                                                            //количество элементов в массиве
    Type* element;                                                         //указатель на начало массива

public:

    //конструкторы-деструкторы
    OurVector();
    ~OurVector();


    //функции
    long GetSize() const;                                                  //получаем размер массива
    long GetCount() const;                                                 //получаем количество элементов в массиве
    bool isEmpty() const;                                                  //узнаем пуст ли массив
    void add_element();                                                    //добавляем элемент в конец массива + выдкляем память с запасом, если нужно
    void delete_element();                                                 //удаляем последний элемент
    void print();                                                          //печать


//операторы
    //friend ostream& operator<< (ostream& out, OurVector<Type>& equal);   //вывод (почему-то говорит, что эте нерезрешенный внешний элемент)
    friend istream& operator>> (istream& in, OurVector<Type>& equal);      //ввод (почему-то говорит, что эте нерезрешенный внешний элемент)
    OurVector<Type>& operator=(const OurVector& equal);                    //присваивание
    Type& operator[](long index);                                          //возвращает обычную ссылку на элемент
    const Type& operator[](long index) const;                              //возвращает константную ссылку на элемент
};

//проверочки
long ControlCount() //проверка количества 
{
    cout << "Введите количество элементов, которые хотите добавить: ";

    while (true) { // цикл продолжается до тех пор, пока пользователь не введет корректное значение

        long check;
        cin >> check;

        if (cin.fail()) // если предыдущее извлечение оказалось неудачным,
        {
            cin.clear(); // то возвращаем cin в 'обычный' режим работы
            cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
            throw runtime_error("некорректный ввод: следует ввести число");
        }
        else if (check <= 0)
        {
            cin.clear();
            cin.ignore(32767, '\n');
            throw runtime_error("некорректный ввод: число должно быть больше 0");
        }
        else // если всё хорошо, то возвращаем check
        {
            return check;
            cin.clear();
            cin.ignore(32767, '\n');
        }
    }
}
int ControlChoise() //проверка согласия 
{
    cout << "Введите 1, если да, и 0, если нет: ";
    while (true) { // цикл продолжается до тех пор, пока пользователь не введет корректное значение

        long check;
        cin >> check;

        if (cin.fail()) // если предыдущее извлечение оказалось неудачным,
        {
            cin.clear(); // то возвращаем cin в 'обычный' режим работы
            cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
            throw runtime_error("некорректный ввод: следует ввести число");
        }
        else if (check < 0)
        {
            cin.clear();
            cin.ignore(32767, '\n');
            throw runtime_error("некорректный ввод: число должно быть равно либо 0, либо 1");
        }
        else if (check > 1)
        {
            cin.clear();
            cin.ignore(32767, '\n');
            throw runtime_error("некорректный ввод: число должно быть равно либо 0, либо 1");
        }
        else // если всё хорошо, то возвращаем check
        {
            return check;
            cin.clear();
            cin.ignore(32767, '\n');
        }
    }
}

//конструктор-деструктор
template<class Type>
OurVector<Type>::OurVector() {
    element = new Type[1];
    size = 1;
}
template<class Type>
OurVector<Type>::~OurVector() {
    if (element) delete[] element;
    cout << endl << "Деструктор сработал" << endl;
}

//функции
template<class Type>
long OurVector<Type>::GetSize() const
{
    return size;
}
template<class Type>
long OurVector<Type>::GetCount() const
{
    return count;
}
template<class Type>
bool OurVector<Type>::isEmpty() const
{
    return count == 0;
}
template<class Type>
void OurVector<Type>::add_element() {
    OurVector tmpelement;
    cin >> tmpelement;
    if (tmpelement.count+count >= size)
    {
        //увеличиваем размер массива       
        OurVector tmp(*this);
        if (element) delete[] element;
        size = size + tmpelement.count + 1;
        element = new Type[size];
        for (int i = 0; i < tmp.count; ++i)
            element[i] = tmp.element[i];
    }
    for (int i = count + 1; i < tmpelement.count + count; i++)
    {
        for (int j = 0; j < tmpelement.count; j++)
        {
            element[i] = tmpelement.element[j];
        }
    }
}
template<class Type>
void OurVector<Type>::delete_element() {
    if (count)
        element[--count] = 0;    //удалить последний элемент (если массив не пустой)

    else
        cout << "Массив пуст" << endl;
}
template<class Type>
void OurVector<Type>::print() {
    cout << endl << "Элементы массива:" << endl;
    for (int i = 0; i < equal.count; ++i)
        cout << equal.element[i] << " ";
    cout << endl;
}

//операторы
/*template<class Type>
ostream& operator<< (ostream& out, OurVector<Type>& equal)
{
    cout << endl << "Элементы массива:" << endl;
    for (int i = 0; i < equal.count; ++i)
        cout << equal.element[i] << " ";
    cout << endl;
    return out;
}*/
template<class Type>
istream& operator>> (istream& in, OurVector<Type>& equal)
{
    bool not_ok = true;
    while (not_ok) {
        try
        {
            equal.count = ControlCount();
            not_ok = false;
        }
        catch (const exception& ex)
        {
            cout << "Ошибка: " << ex.what() << std::endl;
            not_ok = true;
        }
    }
    for (int i = 0; i < equal.count; i++)
    {
        cout << endl << "Введите элемент" << endl;
        cin >> equal.element[i];
    }

    return in;
}
template<class Type>
OurVector<Type>&
OurVector<Type>::operator=(const OurVector& equal)
{
    if (this != &equal) {       //чтобы избежать присваивания самому себе
        size = equal.size;
        count = equal.count;
        if (element) delete[] element;
        element = new Type[size];
        for (int i = 0; i < count; ++i)
            element[i] = equal.element[i];
    }
    return *this;
}
template<class Type>
Type& OurVector<Type>::operator[](long index)
{
    return element[index];
}
template<class Type>
const Type& OurVector<Type>::operator[](long index) const
{
    return element[index];
}

int main()
{
    int choise;
    bool not_ok;
    setlocale(LC_ALL, "Russian");
    OurVector<int> massive;
    if (massive.isEmpty()) {
        cout << "Массив пуст, хотите добавить элементы?" << endl;
        not_ok = true;
        while (not_ok) {
            try
            {
                choise = ControlChoise();
                not_ok = false;
            }
            catch (const exception& ex)
            {
                cout << "Ошибка: " << ex.what() << std::endl;
                not_ok = true;
            }
        }
        //int tmp;
        if (choise == 1) {
            //cin >> massive;
            //cin >> tmp;
            massive.add_element();
        }

        cout << "Хотите вывести?" << endl;
        not_ok = true;
        while (not_ok) {
            try
            {
                choise = ControlChoise();
                not_ok = false;
            }
            catch (const exception& ex)
            {
                cout << "Ошибка: " << ex.what() << std::endl;
                not_ok = true;
            }
        }
        if (choise == 1) {
            cout << massive;
        }
    }
    else
    {
        cout << "В массиве что-то есть" << endl;
        cout << "Хотите вывести?" << endl;
        not_ok = true;
        while (not_ok) {
            try
            {
                choise = ControlChoise();
                not_ok = false;
            }
            catch (const exception& ex)
            {
                cout << "Ошибка: " << ex.what() << std::endl;
                not_ok = true;
            }
        }
        if (choise == 1) {
            cout << massive;
        }
    }
    return 0;
}
