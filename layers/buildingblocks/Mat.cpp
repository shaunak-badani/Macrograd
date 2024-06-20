#include "Mat.h"
#include <functional>
#include <iostream>
#include <memory>

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
    this->piece = (*originalMat.mapFunction([=](int i, int j, float k) { return initialValue; }).get()).getPiece();
}

svf Mat::getPiece()
{
    return this->piece;
}

std::shared_ptr<Mat> Mat::mapFunction(std::function<float(int, int, float)> apply) const
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
    return std::make_shared<Mat>(p);
}

void Mat::forEach(std::function<void(int, int, float)> apply) const
{
    std::pair<int, int> shape = this->getShape();
    int noOfRows = shape.first;
    int noOfColumns = shape.second;

    svf p = svf(noOfRows, std::vector<float>(noOfColumns, 0));

    for(int i = 0 ; i < noOfRows ; i++)
    {
        for(int j = 0 ; j < noOfColumns ; j++)
        {
            apply(i, j, this->piece[i][j]);
        }
    }
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

    return *mapFunction([=](int i, int j, float value) { return b.piece[i][j] + value; }).get();
}

Mat Mat::operator-(Mat const& b) const
{
    if(this->getShape() != b.getShape())
    {
        throw std::runtime_error("Matrices are not of equal size!");
    }

    return *mapFunction([=](int i, int j, float value) { return value - b.piece[i][j]; }).get();
}

Mat Mat::operator*(Mat const& b) const
{
    std::pair<int, int> aShape = this->getShape();
    std::pair<int, int> bShape = b.getShape();

    if(aShape.second != bShape.first)
    {
        throw std::runtime_error("Matrices cannot be multiplied!");
    }
    svf outputVector = svf(aShape.first, std::vector<float>(bShape.second, 0));
    Mat output(outputVector);

    return *output.mapFunction([=](int i, int j, float value)
    {
        float tmp = 0;
        for(int k = 0 ; k < aShape.second ; k++)
        {
            tmp += this->piece[i][k] * b.piece[k][j];
        }
        return tmp;
    }).get();
}

void Mat::operator+=(Mat const& b) 
{
    this->forEach([=](int i, int j, float value)
    {
        this->piece[i][j] += b.piece[i][j];
    });
}

void Mat::operator+=(float &adder) 
{
    this->forEach([=](int i, int j, float value)
    {
        this->piece[i][j] += adder;
    });
}

std::ostream& operator<<(std::ostream& os, const Mat& a)
{
    svf vec = a.piece;
    std::pair<int, int> shape = a.getShape();
    for(int i = 0 ; i < shape.first ; i++)
    {
        int j;
        for(j = 0 ; j < shape.second - 1 ; j++)
        {
            os << a.piece[i][j] << ",";
        }
        os << a.piece[i][j] << std::endl;
    }
    return os;
}


Mat Mat::T()
{
    std::pair<int, int> shape = this->getShape();
    int noOfRows = shape.first;
    int noOfColumns = shape.second;
    
    svf p = svf(noOfColumns, std::vector<float>(noOfRows, 0));
    for(int i = 0 ; i < noOfRows ; i++)
    {
        for(int j = 0 ; j < noOfColumns ; j++)
        {
            p[j][i] = this->piece[i][j];
        }
    }
    return Mat(p);
}

void operator-=(std::shared_ptr<Mat> operand, std::shared_ptr<Mat> input)
{
    operand->forEach([=](int i, int j, float value){
        operand->piece[i][j] -= input->piece[i][j];
    });
}

std::shared_ptr<Mat> operator*(float value, std::shared_ptr<Mat> input)
{
    return input->mapFunction([=](int i, int j, float p){
        return p * value;
    });
}