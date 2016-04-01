/**========================================================================================================================**\
	Transform Matrix
\**========================================================================================================================**/

#ifndef __TRANSFORM_MATRIX__
#define __TRANSFORM_MATRIX__

namespace proimage
{
	class TransformMatrix
	{

	private:


	public:

		TransformMatrix();
		~TransformMatrix();

		double m_matrix[3][3];
		double m_invmatrix[3][3];

		static void mul(double left[3][3], double right[3][3], double out[3][3]);
		void set_matrix(double mx[3][3]);
		void set_invmatrix(double invmx[3][3]);
		void add_matrix(double mx[3][3], bool prepend);
		void add_invmatrix(double mx[3][3], bool prepend);

		/*--------------------------------------------------------------------------------*\
			void set_transform(double mx[3][3], double inv_mx[3][3]);

			set the transfomration matrix, matrix used matrix, inv_mx is the transfomration backwards.
		\*--------------------------------------------------------------------------------*/
		void set_matrix(double mx[3][3], double inv_mx[3][3]);

		/*--------------------------------------------------------------------------------*\
			void add_transform(double mx[3][3], double inv_mx[3][3]);

			add a custom transformation to the matrix, inv_mx is the transfomration backwards.
		\*--------------------------------------------------------------------------------*/
		void add_matrix(double mx[3][3], double inv_mx[3][3], bool prepend = true);

		void get_matrix(double mx[3][3]);
		void get_invmatrix(double invmx[3][3]);

		/*--------------------------------------------------------------------------------*\
			void add_translation(size_t x, size_t y, int append=1)

			matrix is added infront (left) by default, so calculated last
			if append == -1 matrix is added at the back (right), so calculated first
		\*--------------------------------------------------------------------------------*/
		void add_translation(double x, double y, bool prepend=true);
		void add_scaling(double fact_x, double fact_y, bool prepend=true);
		
		void add_rotation_rad(double angle, bool prepend=true);
		void add_rotation_rad(double angle, double center_x, double center_y, bool prepend = true);
		void add_rotation(double angle, bool prepend = true);
		void add_rotation(double angle, double center_x, double center_y, bool prepend = true);

		void add_shear_x(double shear_x, bool prepend = true);
		void add_shear_y(double shear_y, bool prepend = true);

		void calc_matrix(double x, double y, double* _x, double* _y);
		void calc_invmatrix(double x, double y, double* _x, double* _y);
		/*--------------------------------------------------------------------------------*\
			void calc_newsize(double mx[3][3], unsigned int width, unsigned int height, unsigned int* new_width, unsigned int* new_height)
		\*--------------------------------------------------------------------------------*/
		static void calc_matrix(double mx[3][3], double x, double y, double* _x, double* _y);
		static void calc_newsize(double mx[3][3], unsigned int width, unsigned int height, int *offset_x, int *offset_y, unsigned int* new_width, unsigned int* new_height);
	};
}


#endif // #ifndef __TRANSFORM_MATRIX__