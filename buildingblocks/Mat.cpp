#include "Mat.h"
#include <functional>
#include <iostream>

std::pair<int, int> Mat::getShape() const
{
    int m = this->piece.size();
    if(!m)
    {
        return {0, 0};
    }
    int n = this->piece[0].size();
    return {m, n};
}

Mat::Mat(svf p) : piece(p) 
{

}

Mat::Mat(Mat& originalMat, const float initialValue)
{
    this->piece = originalMat.mapFunction([=](int i, int j, float k) { return initialValue; }).getPiece();
}

svf Mat::getPiece()
{
    return this->piece;
}

Mat Mat::mapFunction(std::function<float(int, int, float)> apply) const
{
    std::pair<int, int> shape = this->getShape();
    int noOfRows = shape.first;
    int noOfColumns = shape.second;

    svf p = svf(noOfRows, std::vector<float>(noOfColumns, 0));

    for(int i = 0 ; i < noOfRows ; i++)
    {
        for(int j = 0 ; j < noOfColumns ; j++)
        {
            p[i][j] = apply(i, j, this->piece[i][j]);
        }
    }
    return Mat(p);
}

void Mat::assignValue(float value)
{
    std::pair<int, int> shape = this->getShape();
    int noOfRows = shape.first;
    int noOfColumns = shape.second;


    for(int i = 0 ; i < noOfRows ; i++)
    {
        for(int j = 0 ; j < noOfColumns ; j++)
        {
            this->piece[i][j] = value;
        }
    }
}

Mat Mat::operator+(Mat const& b) const
{
    if(this->getShape() != b.getShape())
    {
        throw std::runtime_error("Matrices are not of equal size!");
    }

    return mapFunction([=](int i, int j, float value) { return b.piece[i][j] + value; });
}

Mat Mat::operator-(Mat const& b) const
{
    if(this->getShape() != b.getShape())
    {
        throw std::runtime_error("Matrices are not of equal size!");
    }

    return mapFunction([=](int i, int j, float value) { return value - b.piece[i][j]; });
}

Mat Mat::operator*(Mat const& b) const
{
    std::pair<int, int> aShape = this->getShape();
    std::pair<int, int> bShape = b.getShape();

    if(aShape.second != bShape.first)
    {
        throw std::runtime_error("Matrices cannot be multiplied!");
    }

    return mapFunction([=](int i, int j, float value)
    {
        float tmp = 0;
        for(int k = 0 ; k < aShape.second ; k++)
        {
            tmp += this->piece[i][k] * b.piece[k][j];
        }
        return tmp;
    });
}

std::ostream& operator<<(std::ostream& os, const Mat& a)
{
    a.mapFunction([=](int i, int j, float value) { std::cout << a.piece[i][j] << " "; return 1.0; });
    return os;
}