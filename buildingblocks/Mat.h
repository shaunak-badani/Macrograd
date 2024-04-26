#ifndef MAT_H
#define MAT_H
#include <iostream>
#include <vector>
#include <functional>
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

        friend std::ostream& operator<<(std::ostream &os, const Mat&a);

        Mat mapFunction(std::function<float(int, int, float)> apply) const;

        // transpose function
        Mat T();

        // assigns the value passed to all elements of the matrix
        void assignValue(float value);

};

#endif