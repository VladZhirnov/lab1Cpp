#include <random>
#include <iostream>
#include <cmath>

template <typename T>
struct Point {
private:
	T _x, _y;
public:
	Point();
	Point(T x, T y);
	T get_x() const;
	T get_y() const;
	double distance(const Point<T>* point);
};

template <typename T>
class broken_line {
	Point<T>** _points;
	int _size;
public:
	broken_line(const broken_line<T>& other);
	broken_line();
	broken_line(int size);
	broken_line(T low, T hight, int count);
	~broken_line();
	Point<T> operator[](int index) const;
	Point<T>& operator[](int index);
	broken_line<T>& operator=(const broken_line<T>& rhs);
	broken_line<T>& operator+=(const broken_line<T>& other);
	broken_line<T> operator+(const broken_line<T>& other);
	broken_line<T>& operator+=(const Point<T>& point);
	broken_line<T> operator+(const Point<T>& point);
	int size() const;
	void swap(broken_line<T>& other);
	void push_point(const Point<T>& point);
	double lenght();
	void make_polygon(const int N, const double radius);
};

template <typename T>
broken_line<T>::broken_line(const broken_line<T>& other) {
	_points = new Point<T>*[other._size];
	_size = other._size;
	for (int i = 0; i < _size; i++)
	{
		_points[i] = new Point<T>(other[i]);
	}
}

template <typename T>
broken_line<T>::broken_line() {
	_points = nullptr;
	_size = 0;
}

template <typename T>
broken_line<T>::broken_line(int size) {
	_size = size;
}

template <typename T>
broken_line<T>::broken_line(T low, T hight, int count) {
	std::random_device rd;
	std::mt19937 gen(rd());
	_points = new Point<T>*[count];
	for (int i = 0; i < count; i++)
	{
		std::uniform_real_distribution<> dist(low, hight);
		T x = dist(gen);
		T y = dist(gen);
		Point<T> a(x, y);
		_points[i] = new Point<T>(a);
	}
	_size = count;
}

template <typename T>
Point<T>::Point() {
	_x = 0;
	_y = 0;
}

template <typename T>
Point<T>::Point(T x, T y) {
	_x = x;
	_y = y;
}

template <typename T>
T Point<T>::get_x() const{
	return _x;
}

template <typename T>
T Point<T>::get_y() const{
	return _y;
}

template <typename T>
Point<T> broken_line<T>::operator[](int index) const {
	//if (index < 0)
	//	throw runtime_error("Input out of range");
	return *_points[index];
}


template <typename T>
Point<T>& broken_line<T>::operator[](int index)
{
	//if (index < 0)
	//	throw runtime_error("Input out of range");
	return *_points[index];
}

template <typename T>
broken_line<T>::~broken_line()
{
	for (int i = 0; i < _size; ++i) {
		delete _points[i];
	}
	delete[] _points;
}

template <typename T>
broken_line<T>& broken_line<T>::operator=(const broken_line<T>& rhs) {
	broken_line<T> copy(rhs);
	copy.swap(*this);
	return *this;
}

template <typename T>
void broken_line<T>::swap(broken_line<T>& other) {
	std::swap(_points, other._points);
	std::swap(_size, other._size);
}

template<typename T>
int broken_line<T>::size() const {
	return _size;
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Point<T>& point) {
	stream << "(" << point.get_x() << ", " << point.get_y() << ")";
	return stream;
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const broken_line<T>& line) {
	stream << "[ ";
	for (int i = 0; i < line.size(); ++i) {
		if (i == (line.size() - 1)) {
			stream << line[i];
		}
		else {
			stream << line[i] << ", ";
		}
	}
	stream << " ]";
	return stream;
}

template<typename T>
broken_line<T>& broken_line<T>::operator+=(const broken_line<T>& other) {
	int capacity = _size + other._size;
	Point<T>** temp = new Point<T>*[capacity]();
	for (int i = 0; i < _size; ++i) {
		temp[i] = _points[i];
	}
	delete[] _points;
	_points = temp;
	for (int i = 0; i < other._size; ++i) {
		*this += *other._points[i];
	}
	return *this;
}

template<typename T>
broken_line<T> broken_line<T>::operator+(const broken_line<T>& other) {
	broken_line<T> add_res(*this);
	add_res += other;
	return add_res;
}

template <typename T>
broken_line<T>& broken_line<T>::operator+=(const Point<T>& point) {
	auto new_points = new Point<T>*[_size + 1];
	for (int i = 0; i < _size; i++)
	{
		new_points[i] = _points[i];
	}
	new_points[_size] = new Point<T>(point);
	delete[] _points;
	_points = new_points;
	_size++;
	return *this;
}

template<typename T>
broken_line<T> broken_line<T>::operator+(const Point<T>& point) {
	broken_line<T> add_res(*this);
	add_res += point;
	return add_res;
}

//Добавление точки в начало
template <typename T>
void broken_line<T>::push_point(const Point<T>& point) {
	auto new_points = new Point<T>*[_size + 1];
	for (int i = 0; i < _size; i++)
	{
		new_points[i] = _points[i];
	}
	for (int i = _size; i > 0; i--)
	{
		new_points[i] = _points[i - 1];
	}
	new_points[0] = new Point<T>(point);
	_size++;
	delete[] _points;
	_points = new_points;
}

template <typename T>
double Point<T>::distance(const Point<T>* point) {
	double dx = point->get_x() - _x;
	double dy = point->get_y() - _y;
	return std::sqrt(dx * dx + dy * dy);
}

template <typename T>
double broken_line<T>::lenght() {
	double lenght_line = 0;
	for (int i = 1; i < _size; i++) {
		lenght_line += _points[i - 1]->distance(_points[i]);
	}
	return lenght_line;
}

//Задача №1
template <typename T>
void broken_line<T>::make_polygon(const int N, const double radius) {
    // N - Заданное количество вершин N для N-угольника
    // radius - Радиус окружности, вписанной в N-угольник
	broken_line<T> polygon;
	double angle = 2 * 3.14159265358979323846 / N;  // Угол между вершинами N-угольника
	for (int i = 0; i < N; i++) {
		T x = radius * std::cos(i * angle);
		T y = radius * std::sin(i * angle);
		Point<T> point(x, y);
		polygon += point;
	}
	std::cout << polygon << std::endl;
}

