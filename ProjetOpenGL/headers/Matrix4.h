#pragma once


class Matrix4
{
	private:
		float* matrix;

	public:
		Matrix4(float*);
		~Matrix4();
		float* getMatrixValue();
		void setMatrixValue(float*);
		static Matrix4 getTranslationMatrix(float , float , float );
		static Matrix4 getRotationMatrix(float , float , float , float );
		static Matrix4 getScaleMatrix(float , float , float );
		static Matrix4 getProjectionMatrix(float , float , float , float );
};