#pragma once


class Matrix4
{
	private:
		float* matrix;

	public:
		Matrix4(float*);
		Matrix4(Matrix4 const& other);
		Matrix4& operator=(Matrix4 other);
		void swap(Matrix4& m);
		~Matrix4();
		float* getMatrixValue();
		void setMatrixValue(float*);
		//On return la matrice pour pouvoir chainer les opérations
		Matrix4 inverse();
		Matrix4 transpose();
		Matrix4 operator*(Matrix4 mat);

		static Matrix4 getTranslationMatrix(float , float , float );
		static Matrix4 getRotationMatrix(float , float , float , float );
		static Matrix4 getScaleMatrix(float , float , float );
		static Matrix4 getProjectionMatrix(float , float , float , float );
};