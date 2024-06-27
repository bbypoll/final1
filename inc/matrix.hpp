#pragma once
#include <iostream>
#include <cassert>

namespace mt

{

	//#define MY_DEBUG


	using namespace std;

	template<typename T, int N, int M>
	struct MasWrapper
	{
		T mas[N][M];
	};

	template<typename T, int N, int M>
	class Matrix
	{
		//Абстаркция
		//Инкапсуляция
		//использование вне класса
	public:
		//конструктор
		Matrix()
		{
#ifdef MY_DEBUG
			cout << "Constructor" << endl;
#endif
			m_n = N;
			m_m = M;
			for (int i = 0; i < m_n;i++)
				for (int j = 0; j < m_m;j++)
					m_mat[i][j] = 0;

		}

		//Конструктор
		Matrix(const T mas[N][M])
		{
#ifdef MY_DEBUG
			cout << "Constructor" << endl;
#endif
			m_n = N;
			m_m = M;
			for (int i = 0; i < m_n;i++)
				for (int j = 0; j < m_m;j++)
					m_mat[i][j] = mas[i][j];

		}

		//Конструктор
		Matrix(const MasWrapper<T, N, M>& mas)
		{
#ifdef MY_DEBUG
			cout << "Constructor" << endl;
#endif
			m_n = N;
			m_m = M;
			for (int i = 0; i < m_n;i++)
				for (int j = 0; j < m_m;j++)
					m_mat[i][j] = mas.mas[i][j];

		}

		//Конструктор копирования

		Matrix(const Matrix<T, N, M>& mat)
		{
#ifdef MY_DEBUG
			cout << "Copy Constructor" << endl;
#endif
			m_n = mat.m_n;
			m_m = mat.m_m;

			for (int i = 0; i < m_n;i++)
				for (int j = 0; j < m_m;j++)
					m_mat[i][j] = mat.m_mat[i][j];
		}

		int getN() const { return m_n; }
		int getM() const { return m_m; }
		T get(int i, int j) const { return m_mat[i][j]; }
		void set(int i, int j, T data) { m_mat[i][j] = data; }

		//Присваивание
		template<typename T, int N, int M>
		Matrix<T, N, M>& operator=(const Matrix<T, N, M>& mat)
		{
#ifdef MY_DEBUG
			cout << "Operator =" << endl;
#endif
			m_n = mat.getN();
			m_m = mat.getM();

			for (int i = 0; i < m_n;i++)
				for (int j = 0; j < m_m;j++)
					m_mat[i][j] = mat.get(i, j);
			return *this;
		}

		//Оператор сложения
		template<typename T, int N, int M>
		Matrix<T, N, M> operator+(const Matrix<T, N, M>& mat)
		{
#ifdef MY_DEBUG
			cout << "operator+" << endl;
#endif
			Matrix<T, N, M> tmp;
			for (int i = 0;i < m_n;i++)
				for (int j = 0;j < m_m;j++)
					tmp.m_mat[i][j] = m_mat[i][j] + mat.m_mat[i][j];
			return tmp;
		}

		template<typename T, int N, int M>
		Matrix<T, N, M> operator-(const Matrix<T, N, M>& mat)
		{
#ifdef MY_DEBUG
			cout << "operator-" << endl;
#endif
			Matrix<T, N, M> tmp;

			for (int i = 0;i < m_n;i++)
			{
				for (int j = 0;j < m_m;j++)
				{
					tmp.m_mat[i][j] = m_mat[i][j] - mat.m_mat[i][j];
				}
			}
			return tmp;
		}

		template<typename T, int K>
		Matrix<T, N, K> operator*(const Matrix<T, M, K>& mat)
		{
#ifdef MY_DEBUG
			cout << "operator*" << endl;
#endif		
			Matrix<T, N, K> tmp;
			for (int i = 0;i < m_n;i++)
			{
				for (int j = 0;j < mat.getM();j++)
				{
					T sum = 0;
					for (int k = 0; k < m_m;k++)
						sum += m_mat[i][k] * mat.get(k, j);
					tmp.set(i, j, sum);
				}
			}

			return tmp;
		}

		T D()
		{
#ifdef MY_DEBUG		
			cout << "Determinate!!" << endl;
#endif
			if ((m_n != m_m) && (m_n != 2) && (m_n != 3))
			{
				cout << "This format isnt supported" << endl;
			}

			else if (m_n == 2)
			{
				double det = 0;
				det = m_mat[0][0] * m_mat[1][1] - m_mat[0][1] * m_mat[1][0];
				return det;
			}

			else if (m_n == 3)
			{
				double det = 0;
				det = m_mat[0][0] * m_mat[1][1] * m_mat[2][2] + m_mat[0][1] * m_mat[1][2] * m_mat[2][0] + m_mat[1][0] * m_mat[2][1] * m_mat[0][2] - m_mat[2][0] * m_mat[1][1] * m_mat[0][2] - m_mat[2][1] * m_mat[1][2] * m_mat[0][0] - m_mat[1][0] * m_mat[0][1] * m_mat[2][2];
				return det;
			}
		}


		Matrix<T, N, M> reverse()
		{
#ifdef MY_DEBUG
			cout << "reverse" << endl;
#endif
			int Det = D();
			Matrix<T, N, M> tmp;
			if ((m_n == m_m && m_n == 2) || (m_n == m_m && m_n == 3))
			{
				if (Det == 0)
				{
					throw exception("Zero determinant!");
				}
				else
				{
					if (m_n == 2)
					{
						tmp.m_mat[0][0] = m_mat[1][1] / Det;
						tmp.m_mat[0][1] = -m_mat[0][1] / Det;
						tmp.m_mat[1][0] = -m_mat[1][0] / Det;
						tmp.m_mat[1][1] = m_mat[0][0] / Det;
						return tmp;
					}
					else if (m_n == 3)
					{
						tmp.m_mat[0][0] = (m_mat[1][1] * m_mat[2][2] - m_mat[2][1] * m_mat[1][2]) / Det;
						tmp.m_mat[1][0] = -(m_mat[1][0] * m_mat[2][2] - m_mat[2][0] * m_mat[1][2]) / Det;
						tmp.m_mat[2][0] = (m_mat[1][0] * m_mat[2][1] - m_mat[2][0] * m_mat[1][1]) / Det;
						tmp.m_mat[0][1] = -(m_mat[0][1] * m_mat[2][2] - m_mat[2][1] * m_mat[0][2]) / Det;
						tmp.m_mat[1][1] = (m_mat[0][0] * m_mat[2][2] - m_mat[2][0] * m_mat[0][2]) / Det;
						tmp.m_mat[2][1] = -(m_mat[0][0] * m_mat[2][1] - m_mat[2][0] * m_mat[0][1]) / Det;
						tmp.m_mat[0][2] = (m_mat[0][1] * m_mat[1][2] - m_mat[1][1] * m_mat[0][2]) / Det;
						tmp.m_mat[1][2] = -(m_mat[0][0] * m_mat[1][2] - m_mat[1][0] * m_mat[0][2]) / Det;
						tmp.m_mat[2][2] = (m_mat[0][0] * m_mat[1][1] - m_mat[1][0] * m_mat[0][1]) / Det;
						return tmp;
					}
				}
			}
			else
				std::cout << "This format is not supported. " << std::endl;
		}

		Matrix<T,M,N> transposition()
		{
#ifdef MY_DEBUG
			cout << "transposition" << endl;
#endif	
			Matrix<T, M, N> tmp;

			for (int i = 0;i < M;i++)
			{
				for (int j = 0;j < N;j++)
				{
					tmp.set(i, j, m_mat[j][i]);
				}
			}

			return tmp;

		}

		
		Matrix<T, N, M> Gauss_method()

		{
			cout << "Gaus method" << endl;

			 T* x = new T[M-1];
			 T* y = new T[N];
			double max;
			int k, index;
			k = 0;
			const double eps = 0.00001;
			for (int i = 0;i < N;i++)
			{
				for (int j = 0; j <M ;j++)
				{
					y[i] = m_mat[i][j];
				}
			}
		
			while (k < N)
			{
				// Поиск строки с максимальным a[i][k]
				max = abs(m_mat[k][k]);
				index = k;
				for (int i = k + 1; i < N; i++)
				{
					if (abs(m_mat[i][k]) > max)
					{
						max = abs(m_mat[i][k]);
						index = i;
					}
				}
				// Перестановка строк
				if (max < eps)
				{
					// нет ненулевых диагональных элементов
					cout << "The system has no solutions ";
					cout << index << " matrix A" << endl;
					return 0;
				}
				for (int j = 0; j < N; j++)
				{
					double temp = m_mat[k][j];
					m_mat[k][j] = m_mat[index][j];
					m_mat[index][j] = temp;
				}
				double temp = y[k];
				y[k] = y[index];
				y[index] = temp;
				// Нормализация уравнений
				for (int i = k; i < N; i++)
				{
					double temp = m_mat[i][k];
					if (abs(temp) < eps) continue; // для нулевого коэффициента пропустить
					for (int j = 0; j < N; j++)
						m_mat[i][j] = m_mat[i][j] / temp;
					y[i] = y[i] / temp;
					if (i == k)  continue; // уравнение не вычитать само из себя
					for (int j = 0; j < N; j++)
						m_mat[i][j] = m_mat[i][j] - m_mat[k][j];
					y[i] = y[i] - y[k];
				}
				k++;
			}
			// обратная подстановка
			for (k = N - 1; k >= 0; k--)
			{
				x[k] = y[k];
				for (int i = 0; i < k; i++)
					y[i] = y[i] - m_mat[i][k] * x[k];
			}
			
			for (int i = 0; i < M - 1; i++)
			{
				cout << "[" << x[i] << "]" << endl;
			}

			return *this;

			delete[] x;
			delete[] y;

		}
			


		//Дестркутор
		~Matrix()
		{
#ifdef MY_DEBUG
			cout << "Destructor" << endl;
#endif
		}


		//friend -  позволяет функции иметь доступ к приватным полям
		template<typename T, int N, int M>
		friend istream& operator>>(istream& in, Matrix<T, N, M>& mat);
		template<typename T, int N, int M>
		friend ostream& operator<<(ostream& out, const Matrix<T, N, M>& mat);


		//использование внутри класса
	private:
		int m_n, m_m; // поле класса
		T m_mat[N][M];
	};

	// перегрузка оператора ввода
	template<typename T, int N, int M>
	istream& operator>>(istream& in, Matrix<T, N, M>& mat)
	{
		for (int i = 0;i < mat.m_n;i++)
			for (int j = 0;j < mat.m_m; j++)
				in >> mat.m_mat[i][j];
		return in;
	}

	//перегрузка оператора вывода
	template<typename T, int N, int M>
	ostream& operator<<(ostream& out, const Matrix<T, N, M>& mat)
	{
		out << "Matrix" << mat.m_n << "x" << mat.m_m << endl;
		for (int i = 0;i < mat.m_n;i++)
		{
			for (int j = 0;j < mat.m_m;j++)
			{
				out << mat.m_mat[i][j] << " ";
			}

			out << endl;
		}
		return out;
	}


	using Vec2i = Matrix<int, 2, 1>; // сокращенное удобное название
	using Vec2d = Matrix<double, 2, 1>;
	using Vec3d = Matrix<double, 3, 1>;
	using Mat22i = Matrix<int, 2, 2>;
	using Mat22d = Matrix<double, 2, 2>;
	using Mat33i = Matrix<int, 3, 3>;
	using Mat33d = Matrix<double, 3, 3>;
}