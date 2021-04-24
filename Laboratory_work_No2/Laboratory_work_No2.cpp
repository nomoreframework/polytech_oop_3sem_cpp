#include <iostream>
#include <string>
#include <vector>
using namespace std;
using  std::cout;
using  std::cin;

class matrix
{
public:
	matrix(int* matrix[], int square_matrix_size)
	{
		sq_matrix = matrix;
		this->square_matrix_size = square_matrix_size;
	}
	int** get_matrix() { return sq_matrix; }
	int get_trA()
	{
		int result = 0;
		for (int i = 0; i < square_matrix_size;++i) result += sq_matrix[i][i];
		return result;
	}
private:
	int** sq_matrix;
	int square_matrix_size;
};
class console_worker
{
public:
	console_worker(){}
	~console_worker(){}
	const string i_demension = "Enter the dimension of the matrix";
	const string i_inverse = "tr(A) of matrix = ";
	const string o_matrix = "--- Your Matrix ---";
	const string exit = "For exit press 'q'";

	template<typename T>
	T static read(T arg)
	{
		cin >> arg;
		return arg;
	}
	template<typename V>
	void static write(V args)
	{
		cout << args;
	}
	static int**  get_sq_matrix(int* arr[], int size)
	{
		int arg = 0;
		int count = 1;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cout << "A(" << i << "," << j << ") = ";								
				arr[i][j] = read(arg);
				cout << "...elements - " << count << "/" << size * size <<"\n";
				++count;
			}
		}
		return arr;
	}
	void static print_matrix(int *arr [], int size)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				write(arr[i][j]);
				write(' ');
			}
			write("\n");
		}
	}
};
int main ()
{
	console_worker* c_w = new console_worker();
	cout << c_w->i_demension
		<< "\n";
	int arg = 0;
	int size = console_worker::read(arg);
	int** arr = new int* [size]();
	for (int i = 0; i < size; ++i)
	{
		arr[i] = new int[size]();
    }
	matrix m(console_worker::get_sq_matrix(arr, size), size);
	cout << c_w->o_matrix << endl;
	console_worker::print_matrix(m.get_matrix(), size);
	cout << c_w->i_inverse << m.get_trA() << "\n";
	delete[] arr;
	char q = ' ';
	while (q != 'q') { cin >> q; 	cout << c_w->exit << "\n";}
	delete c_w;
	return 0;
}
