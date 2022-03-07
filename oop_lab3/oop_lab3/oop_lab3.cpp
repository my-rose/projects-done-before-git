
#include <iostream>
#include <assert.h>
using namespace std;

template <class T, int w, int h>
class Image {
private:
    int m_width;
    int m_height;
    T m_data[w][h];
public:
        //конструкторы
        Image() {
            m_height = h;
            m_width = w;
        }
        Image(Image<T, w, h>*new_im) {
            m_height = h;
            m_width = w;
            for (int i = 0; i < w; i++) {
                for (int j = 0; j < h; j++) {
                    m_data[i][j] = new_im[i][j];
                }
            }
        }        //копирования
        Image(T znach) {
            m_height = h;
            m_width = w;
            for (int i = 0; i < w; i++) {
                for (int j = 0; j < h; j++) {
                    m_data[i][j] = znach;
                }
            }
        }
        Image(T znach, T znach2) { //наглядный конструктор
            m_height = h;
            m_width = w;
            for (int i = 0; i < w; i++) {
                for (int j = 0; j < h; j++) {
                    m_data[i][j] = i + j + 0.5;
                }
            }
        }

        //2.копирование с новым типом
        template <typename NewType>
        Image<NewType, w, h> changeType() {
            Image<NewType, w, h> a;
            for (int i = 0; i < w; i++) {
                for (int j = 0; j < h; j++) {
                    a[i][j] = static_cast<NewType>(m_data[i][j]);
                }
            }
            return a;
        }

        //3.получение ширина и высота
        T pixel(int inp_w, int inp_h) {
            if (inp_w < 0 and inp_h >= 0) return m_data[m_width - inp_w - 1][inp_h];
            else if (inp_w >= 0 and inp_h < 0) return m_data[inp_w][m_height - inp_h - 1];
            else if (inp_w < 0 and inp_h < 0) return m_data[m_width - inp_w - 1][m_height - inp_h - 1];
            return m_data[inp_w][inp_h];
        }

        T* operator[](int index)
        {
            return m_data[index];
        }

        //4.арифметические операции
        template<typename Mult>
        void operator*(Mult a) {
            for (int i = 0; i < w; i++) {
                for (int j = 0; j < h; j++) {
                    m_data[i][j] *= a;
                }
            }
        }
        template<typename Mult>
        void operator*(Image<Mult, w, h> new_im) {
            for (int i = 0; i < w; i++) {
                for (int j = 0; j < h; j++) {
                    m_data[i][j] *= new_im[i][j];
                }
            }
        }
        template<typename Mult>
        void operator/(Mult a) {
            for (int i = 0; i < w; i++) {
                for (int j = 0; j < h; j++) {
                    m_data[i][j] /= a;
                }
            }
        }
        template<typename Mult>
        void operator/(Image<Mult, w, h> new_im) {
            for (int i = 0; i < w; i++) {
                for (int j = 0; j < h; j++) {
                    m_data[i][j] /= new_im[i][j];
                }
            }
        }
        template<typename Mult>
        void operator+(Mult a) {
            for (int i = 0; i < w; i++) {
                for (int j = 0; j < h; j++) {
                    m_data[i][j] += a;
                }
            }
        }
        template<typename Mult>
        void operator+(Image<Mult, w, h> new_im) {
            for (int i = 0; i < w; i++) {
                for (int j = 0; j < h; j++) {
                    m_data[i][j] += new_im[i][j];
                }
            }
        }
        template<typename Mult>
        void operator-(Mult a) {
            for (int i = 0; i < w; i++) {
                for (int j = 0; j < h; j++) {
                    m_data[i][j] -= a;
                }
            }
        }
        template<typename Mult>
        void operator-(Image<Mult, w, h> new_im) {
            for (int i = 0; i < w; i++) {
                for (int j = 0; j < h; j++) {
                    m_data[i][j] -= new_im[i][j];
                }
            }
        }

        //5.шаблон методу увеличения размера
        /*template<int new_w, int new_h>
        Image<T, w* new_w, h* new_h> beBigger() {
            Image<T, w*new_w, h*new_h> new_im;
            for (int i = 0; i < w; i++) {
                for (int new_i = 0; new_i < new_w; new_i++) {
                    for (int j = 0; j < h; j++) {
                        for (int new_j = 0; new_j < new_h; new_j++) {
                            new_im[i+new_i][j + new_j] = m_data[i][j];
                        }
                    }
                }
            }
            return new_im;
        }*/
        template<int new_w, int new_h>
        Image<T, w* new_w, h* new_h> beBigger() {
            if (new_w < 0 or new_h < 0) throw "things must be bigger than 0";
            Image<T, w* new_w, h* new_h> new_im;
            for (int i = 0; i < w * new_w; i++) {
                for (int j = 0; j < h * new_h; j++) {
                    new_im[i][j] = m_data[int(i / new_w)][int(j / new_h)];
                }
            }
            return new_im;
        }

        //6.шаблон метода получения куска изображения
        /*int a = abs(((h1 < 0) ? (h - h1) : (h1)) - ((h2 < 0) ? (h - h2) : (h2)))
            ((w1 < 0) ? (w - w1) : (w1))*/
            /*template<int w11, int h11, int w22, int h22>
            Image<T, abs(((w11 < 0) ? (w + w11) : (w11)) - ((w22 < 0) ? (w + w22) : (w22))), abs(((h11 < 0) ? (h + h11) : (h11)) - ((h22 < 0) ? (h + h22) : (h22)))> cropCrop() {
                int w1 = ((w11 < 0) ? (w + w11) : (w11));
                int w2 = ((w22 < 0) ? (w + w22) : (w22));
                int h1 = ((h11 < 0) ? (h + h11) : (h11));
                int h2 = ((h22 < 0) ? (h + h22) : (h22));
                Image<T, abs(((w11 < 0) ? (w + w11) : (w11)) - ((w22 < 0) ? (w + w22) : (w22))), abs(((h11 < 0) ? (h + h11) : (h11)) - ((h22 < 0) ? (h + h22) : (h22)))> new_im;

                for (int i = 0; i < abs(w1 - w2); i++) {
                    for (int j = 0; j < abs(h1 - h2); j++) {
                        new_im[i][j] = m_data[i+w1][j+h1];
                    }
                }
                return new_im;
            }*/
        template<int w11, int h11, int w22, int h22>
        Image<T, w22 - w11 + 1, h22 - h11 + 1> chopChop() {
            if (w11 > w22 or h11 > h22) throw"w11 is more than w22 or elsse";
            int w1 = w11;
            int w2 = w22;
            int h1 = h11;
            int h2 = h22;
            Image<T, w22 - w11 + 1, h22 - h11 + 1> new_im;

            for (int i = 0; i <= abs(w1 - w2); i++) {
                for (int j = 0; j <= abs(h1 - h2); j++) {
                    new_im[i][j] = m_data[i + w1][j + h1];
                }
            }
            return new_im;
        }

        //7.соединение двух изображений
        template<typename NewType, int new_w, int new_h>
        Image<T, w + new_w, h> merge_vertical(Image<NewType, new_w, new_h> new_im) {
            if (h != new_h) throw "Can merge only images of the same height";
            Image<T, w + new_w, h> final_im;
            for (int i = 0; i < w; i++) {
                for (int j = 0; j < h; j++) {
                    final_im[i][j] = m_data[i][j];
                }
            }
            for (int i = 0; i < w; i++) {
                for (int j = 0; j < h; j++) {
                    final_im[i + w][j] = new_im[i][j];
                }
            }
            return final_im;
        }
        template<typename NewType, int new_w, int new_h>
        Image<T, w, h + new_h> merge_horizontal(Image<NewType, new_w, new_h> new_im) {
            if (w != new_w) throw "Cant merge images with different width sry.........~~";
            Image<T, w, h + new_h> final_im;
            for (int i = 0; i < w; i++) {
                for (int j = 0; j < h; j++) {
                    final_im[i][j] = m_data[i][j];
                }
            }
            for (int i = 0; i < w; i++) {
                for (int j = 0; j < h; j++) {
                    final_im[i][j + h] = new_im[i][j];
                }
            }
            return final_im;
        }

        //misc
        void getSize() { cout << "Image: " << m_width << "x" << m_height << "\n"; }
        void printImage() {
            cout << "\n";
            for (int i = 0; i < w; i++) {
                for (int j = 0; j < h; j++) {
                    cout << m_data[i][j] << " ";
                }
                cout << "\n";
            }
        }
};

int main()
{
    try {
        Image<int, 5, 5> im(3, 3);
        //im.getSize();
        im.printImage();
        Image<int, 5, 5> im2(im);
        //Image<float, 5, 5> im2(3, 3);
        Image<int, 5, 10> im3 = im2.merge_horizontal(im);
        //Image<int, 9, 4> im2 = im.beBigger<3, 2>();
        //Image <float, 3, 5> im2 = im.changeType<float>();
        //Image<int, 3, 3>im2 = im.chopChop<1, 2, 3, 4>();
        //im2.printImage();
        im3.printImage();
        //im.pixel(2, 3) = 5;
        //im[2][3] = 5;
        //cout << im.pixel(2, 3);
        //im*3;
        //im.printImage();
    }
    catch (const char* exception)
    {
        cerr << "Error: " << exception << endl;
    }
}

