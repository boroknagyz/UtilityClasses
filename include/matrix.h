// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#pragma once

template <typename T>
class Matrix {
private:
    friend class RowProxy;
    friend class ConstRowProxy;

    class RowProxy {
    public:
        RowProxy(Matrix& m, int rowNo) :
            matrix(m),
            rowNo(rowNo) {
        }

        T& operator[](int colNo) {
            return matrix.data[matrix.colSize * rowNo + colNo];
        }
    private:
        Matrix& matrix;
        int rowNo;
    };

    class ConstRowProxy {
    public:
        ConstRowProxy(const Matrix& m, int rowNo) :
            matrix(m),
            rowNo(rowNo) {
        }

        T operator[](int colNo) const {
            return matrix.data[matrix.colSize * rowNo + colNo];
        }
    private:
        const Matrix& matrix;
        int rowNo;
    };

public:
    Matrix() = default;
    Matrix(int rowSize, int colSize, const T& defaultVal = T()) :
        rowSize(rowSize),
        colSize(colSize),
        data(rowSize * colSize, defaultVal) {
    }
    Matrix(const Matrix& other) = default;
    Matrix(Matrix&& temp) = default;

    Matrix& operator=(const Matrix& other) = default;
    Matrix& operator=(Matrix&& temp) = default;

    RowProxy operator[](int rowNo) {
        return RowProxy(*this, rowNo);
    }
    ConstRowProxy operator[](int rowNo) const {
        return ConstRowProxy(*this, rowNo);
    }
    int rowCount() const { return rowSize; }
    int colCount() const { return colSize; }
private:
    int rowSize = 0;
    int colSize = 0;
    std::vector<T> data;
};


