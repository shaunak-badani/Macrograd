#ifndef MAT_H
#define MAT_H
#include <iostream>
#include <vector>
#include <functional>
#include <memory>
typedef std::vector<std::vector<float>> svf;


class Mat
{
    private:
        svf piece;
    public:
        svf getPiece();
        std::pair<int, int> getShape() const;

        Mat(svf p);

        // parameterized copy constructor
        // Will create a matrix of similar size,
        // and initialize all values to `initialValue`
        Mat(Mat& originalMat, float initialValue);

        Mat operator+(Mat const& b) const;

        Mat operator-(Mat const& b) const;

        Mat operator*(Mat const& b) const;

        void operator+=(Mat const& b);
        void operator+=(float &value);

        friend std::ostream& operator<<(std::ostream &os, const Mat&a);
        friend void operator-=(std::shared_ptr<Mat> operand, std::shared_ptr<Mat> input);
        friend std::shared_ptr<Mat> operator*(float value, std::shared_ptr<Mat> input);
        friend std::shared_ptr<Mat> operator/(std::shared_ptr<Mat> input, float value);


        std::shared_ptr<Mat> mapFunction(std::function<float(int, int, float)> apply) const;

        void forEach(std::function<void(int, int, float)> apply) const;

        // transpose function
        Mat T();

        // assigns the value passed to all elements of the matrix
        void assignValue(float value);

};

#endif